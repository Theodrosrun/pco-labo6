//     ____  __________     ___   ____ ___  _____ //
//    / __ \/ ____/ __ \   |__ \ / __ \__ \|__  / //
//   / /_/ / /   / / / /   __/ // / / /_/ / /_ <  //
//  / ____/ /___/ /_/ /   / __// /_/ / __/___/ /  //
// /_/    \____/\____/   /____/\____/____/____/   //
// Auteurs : Prénom Nom, Prénom Nom


// A vous de remplir les méthodes, vous pouvez ajouter des attributs ou méthodes pour vous aider
// déclarez les dans ComputationManager.h et définissez les méthodes ici.
// Certaines fonctions ci-dessous ont déjà un peu de code, il est à remplacer, il est là temporairement
// afin de faire attendre les threads appelants et aussi afin que le code compile.

#include "computationmanager.h"


ComputationManager::ComputationManager(int maxQueueSize): MAX_TOLERATED_QUEUE_SIZE(maxQueueSize)
{
    requestQueue = std::deque<Request>();
    resultQueue = std::deque<Result>();
    // TODO
}

int ComputationManager::requestComputation(Computation c) {
    monitorIn();
    int id = nextId++;
    requestQueue.push_back(Request(c,id));
    signal(condition);
    monitorOut();
    return id;
}

void ComputationManager::abortComputation(int id) {
    for (auto it = requestQueue.begin(); it != requestQueue.end(); ++it) {
        if (it->getId() == id) {
            requestQueue.erase(it);
            break;
        }
    }
}

Result ComputationManager::getNextResult() {
    // TODO
    // Replace all of the code below by your code

    // Filled with some code in order to make the thread in the UI wait
    monitorIn();
    while (requestQueue.empty()) {
        wait(condition);
    }
    Request nextRequest = requestQueue.front();
    requestQueue.pop_front();

    // Création du résultat correspondant
    Result nextResult = Result(nextRequest.getId(), 4.0);// Fonction pour traiter le résultat suivant de la file d'attente
    monitorOut();
    return nextResult;
}

Request ComputationManager::getWork(ComputationType computationType) {
    // TODO
    // Replace all of the code below by your code

    // Filled with arbitrary code in order to make the callers wait


    monitorIn(); // Entrée dans le moniteur pour protéger l'accès concurrentiel

    while(requestQueue.empty()) {
        wait(condition);
    }

    Request foundRequest;

    for (auto it = requestQueue.begin(); it != requestQueue.end(); ++it) {
        if (it->data) {
            foundRequest = *it;
            requestQueue.erase(it); // Supprimer la requête trouvée de la file d'attente
            break;
        }
    }

    monitorOut(); // Sortie du moniteur après l'opération critique

    return foundRequest;
}

bool ComputationManager::continueWork(int id) {
    // TODO

    monitorIn(); // Entrée dans le moniteur pour protéger l'accès concurrentiel

    // Recherche de la requête associée à l'ID donné dans la file d'attente
    for (auto it = requestQueue.begin(); it != requestQueue.end(); ++it) {
        if (it->getId() == id) {
            // Traitement de la demande en fonction de certains critères
            // Par exemple, marquer la demande pour continuer à travailler ou non
            // return true; // ou false en fonction de la logique que tu veux implémenter
        }
    }

    monitorOut(); // Sortie du moniteur après l'opération critique

    // Retourne une valeur par défaut si l'ID n'est pas trouvé ou si le traitement est terminé
    return false; // ou true en fonction de la logique que tu veux implémenter
    return true;
}

void ComputationManager::provideResult(Result result) {
    // TODO
    monitorIn();
    resultQueue.push_back(result); // Ajouter le résultat à la file d'attente
    signal(condition); // Signaler qu'un résultat est disponible
    monitorOut();
}

void ComputationManager::stop() {
    // TODO

}
