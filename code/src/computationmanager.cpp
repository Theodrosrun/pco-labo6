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

//    monitorIn();

//    int id = nextId++;
//    requestQueue.push_back(Request(c, id));
//    signal(condition);

//    monitorOut();

//    return id;

}

void ComputationManager::abortComputation(int id) {

//    monitorIn();

//    for (auto it = requestQueue.begin(); it != requestQueue.end(); ++it) {
//        if (it->getId() == id) {
//            requestQueue.erase(it);
//            break;
//        }
//    }

//    monitorOut();

}

Result ComputationManager::getNextResult() {

    monitorIn();

    int pos;

     while((pos = searchId()) != -1) {
        wait(resultsNotEmpty);
    }

    Result result = results[pos];
    results.erase(results.begin() + pos);

    monitorOut();

    return result;

//    monitorIn();

//    while (requestQueue.empty()) {
//        wait(condition);
//    }

//    Request nextRequest = requestQueue.front();
//    requestQueue.pop_front();

//    // Création du résultat correspondant
//    Result nextResult = Result(nextRequest.getId(), 4.0);

//    monitorOut();

//    return nextResult;

}

Request ComputationManager::getWork(ComputationType computationType) {

    monitorIn();

    const unsigned type = static_cast<unsigned>(computationType);

    if (requests[type].size() == 0) {
       wait(requestsNotEmpty[type]);
    }

    Request request = requests[type].front();
    requests[type].pop_back();

    signal(requestsNotFull[type]);

    monitorOut();

    return request;

//    monitorIn(); // Entrée dans le moniteur pour protéger l'accès concurrentiel

//    while(requestQueue.empty()) {
//        wait(condition);
//    }

//    Request foundRequest;

//    for (auto it = requestQueue.begin(); it != requestQueue.end(); ++it) {
//        if (it->data) {
//            foundRequest = *it;
//            requestQueue.erase(it); // Supprimer la requête trouvée de la file d'attente
//            break;
//        }
//    }

//    monitorOut(); // Sortie du moniteur après l'opération critique

//    return foundRequest;

}

bool ComputationManager::continueWork(int id) {

//    monitorIn();

//    for (auto it = requestQueue.begin(); it != requestQueue.end(); ++it) {
//        if (it->getId() == id) {
//            // Ici, vous pouvez effectuer le traitement de la demande en fonction de certains critères
//            // Par exemple, marquer la demande pour continuer à travailler ou non

//            monitorOut();

//            return true; // ou false en fonction de la logique que vous voulez implémenter
//        }
//    }

//    monitorOut();

    return true;
}

void ComputationManager::provideResult(Result result) {

    monitorIn();

    results.push_back(result);

    signal(resultsNotEmpty);

    monitorOut();

}

void ComputationManager::stop() {
    // TODO
}

int ComputationManager::searchId() {
    for (size_t i = 0; i < results.size(); ++i) {
        if (results[i].getId() == requestsID.front()) {
            return i;
        }
    }
    return -1;
}
