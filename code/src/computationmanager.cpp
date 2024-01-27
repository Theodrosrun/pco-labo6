//_______________________________________________________________________________________________
//
//! \file    computationmanager.cpp
//! \brief   Fichier source de la classe ComputationManager
//!
//! \author  Bugna Valentin, Theodros Mulugeta
//_______________________________________________________________________________________________

// A vous de remplir les méthodes, vous pouvez ajouter des attributs ou méthodes pour vous aider
// déclarez les dans ComputationManager.h et définissez les méthodes ici.
// Certaines fonctions ci-dessous ont déjà un peu de code, il est à remplacer, il est là temporairement
// afin de faire attendre les threads appelants et aussi afin que le code compile.

#include "computationmanager.h"
#include <algorithm>


ComputationManager::ComputationManager(int maxQueueSize): MAX_TOLERATED_QUEUE_SIZE(maxQueueSize)
{
}

// Client Interface

int ComputationManager::requestComputation(Computation c) {

    monitorIn();

    const unsigned id = nextId++;
    const unsigned type = static_cast<unsigned>(c.computationType);

    preStopCheck();

    // Wait if the requests vector is full
    if (requests[type].size() >= MAX_TOLERATED_QUEUE_SIZE)
        wait(requestsNotFull[type]);

    postStopCheck(requestsNotFull[type]);

    // Add the request
    requests[type].push_back(Request(c, id));
    requestsID.push_back(id);

    signal(requestsNotEmpty[type]);

    monitorOut();

    return id;
}

void ComputationManager::abortComputation(int id) {
    monitorIn();

    // Delete the request
    for(unsigned i = 0; i < NUM_OF_TYPES; i++){
        const auto itRequest = std::find_if(requests[i].begin(), requests[i].end(), [id](const Request& request) { return request.getId() == id; });
        if (itRequest != requests[i].end())
        {
            requests[i].erase(itRequest);
            signal(requestsNotFull[i]);
            break;
        }
    }

    // Delete the ID of the request
    const auto itRequestId = std::find(requestsID.begin(), requestsID.end(), id);
    if(itRequestId != requestsID.end())
        requestsID.erase(itRequestId);

    // Delete the result
    const auto itResult = std::find_if(results.begin(), results.end(), [id](const Result& result) { return result.getId() == id; });
    if (itResult != results.end())
    {
        results.erase(itResult);
        // Signal if the ID of the first element in the results vector is the awaited result
        if (results.front().getId() == requestsID.front())
            signal(resultsNotEmpty);
    }

    monitorOut();
}

Result ComputationManager::getNextResult() {

    monitorIn();

    preStopCheck();

    // Wait if the results vector is empty or if the first result in the results vector is not the awaited result
    if((results.empty()) || (results.front().getId() != requestsID.front()))
        wait(resultsNotEmpty);

    postStopCheck(resultsNotEmpty);

    const Result result = results.front();

    // Remove the result and the request ID
    results.erase(results.begin());
    requestsID.erase(requestsID.begin());

    monitorOut();

    return result;

}

// Compute Engine Interface

Request ComputationManager::getWork(ComputationType computationType) {

    monitorIn();

    const unsigned type = static_cast<unsigned>(computationType);

    preStopCheck();

    // Wait if the requests vector is empty
    if (requests[type].size() == 0)
       wait(requestsNotEmpty[type]);

    postStopCheck(requestsNotEmpty[type]);

    // Get the request and remove it
    const Request request = requests[type].front();
    requests[type].erase(requests[type].begin());

    signal(requestsNotFull[type]);

    monitorOut();

    return request;

}

bool ComputationManager::continueWork(int id) {

    monitorIn();

    // Check if no stop was requested and if the computation is still awaited
    const bool continueWork = !stopped && (std::find(requestsID.begin(), requestsID.end(), id) != requestsID.end());

    monitorOut();

    return continueWork;
}

void ComputationManager::provideResult(Result result) {

    monitorIn();

    results.push_back(result);

    // Sort the vector based on the IDs of the Result objects
    std::sort(results.begin(), results.end(), [](const Result& a, const Result& b) { return a.getId() < b.getId(); });

    // Signal if the ID of the first element in the results vector is the awaited result
    if(results.front().getId() == requestsID.front())
        signal(resultsNotEmpty);

    monitorOut();

}

// Control Interface

void ComputationManager::stop() {
     monitorIn();

     stopped = true;

     // Signal all threads
     for (auto& condition: requestsNotFull)
         signal(condition);

     for (auto& condition: requestsNotEmpty)
         signal(condition);

     for (auto& condition: resultsNotFull)
         signal(condition);

     signal(resultsNotEmpty);

     monitorOut();
}

void ComputationManager::preStopCheck() {
    if (stopped)
    {
        monitorOut();
        throwStopException();
    }
}

void ComputationManager::postStopCheck(Condition& condition) {
    if (stopped)
    {
        // Signal the next awaiting thread
        signal(condition);
        monitorOut();
        throwStopException();
    }
}
