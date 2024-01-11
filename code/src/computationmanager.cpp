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

int ComputationManager::requestComputation(Computation c) {

    monitorIn();

    const unsigned id = nextId++;
    const unsigned type = static_cast<unsigned>(c.computationType);

    if (requests[type].size() >= MAX_TOLERATED_QUEUE_SIZE) {
        wait(requestsNotFull[type]);
    }

    requests[type].push_back(Request(c, id));
    requestsID.push_back(id);

    signal(requestsNotEmpty[type]);

    monitorOut();

    return id;
}

void ComputationManager::abortComputation(int id) {
}

Result ComputationManager::getNextResult() {

    monitorIn();

    if(results[0].getId() != requestsID[0]) {
        wait(resultsNotEmpty);
    }

    Result result = results[0];

    results.erase(results.begin());
    requestsID.erase(requestsID.begin());

    monitorOut();

    return result;

}

Request ComputationManager::getWork(ComputationType computationType) {

    monitorIn();

    const unsigned type = static_cast<unsigned>(computationType);

    if (requests[type].size() == 0) {
       wait(requestsNotEmpty[type]);
    }

    Request request = requests[type][0];
    requests[type].erase(requests[type].begin());

    signal(requestsNotFull[type]);

    monitorOut();

    return request;

}

bool ComputationManager::continueWork(int id) {

    return true;
}

void ComputationManager::provideResult(Result result) {

    monitorIn();

    results.push_back(result);

    std::sort(results.begin(), results.end(), [](const Result& a, const Result& b) { return a.getId() < b.getId(); });

    if(results[0].getId() == requestsID[0])
        signal(resultsNotEmpty);

    monitorOut();

}

void ComputationManager::stop() {
    // TODO
}
