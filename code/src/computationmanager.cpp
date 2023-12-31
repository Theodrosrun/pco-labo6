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
    // TODO
}

int ComputationManager::requestComputation(Computation c) {
    requestQueue.push_back(Request(c, nextId++));
    return nextId;
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
    monitorOut();
    return nextRequest;
}

Request ComputationManager::getWork(ComputationType computationType) {
    // TODO
    // Replace all of the code below by your code

    // Filled with arbitrary code in order to make the callers wait
    monitorIn();
    auto c = Condition();
    wait(c);
    monitorOut();

    return Request(Computation(computationType), -1);
}

bool ComputationManager::continueWork(int id) {
    // TODO
    return true;
}

void ComputationManager::provideResult(Result result) {
    // TODO
}

void ComputationManager::stop() {
    // TODO

}
