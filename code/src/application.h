//     ____  __________ ___   ____ ___  ___
//    / __ \/ ____/ __ \__ \ / __ \__ \|__ \
//   / /_/ / /   / / / /_/ // / / /_/ /__/ /
//  / ____/ /___/ /_/ / __// /_/ / __// __/
// /_/    \____/\____/____/\____/____/____/
//
// Rien à modifier

#ifndef APPLICATION_H
#define APPLICATION_H

#include "utils/graphicsaloninterface.h"
#include "utils/launchable.h"

class Application : public Launchable
{
public:
    Application(GraphicSalonInterface *interface, unsigned nbPlaces, unsigned nbClients);

    /*!
     * \brief Fonction principale du programme
     */
    void run() override;

    /*!
     * \brief Message affiché lors du démarrage du thread
     */
    void printStartMessage() override {qDebug() << "[START] Application lancée";}

    /*!
     * \brief Message affiché lorsque le thread a terminé
     */
    void printCompletionMessage() override {qDebug() << "[STOP] L'application est terminé";}

private:
    GraphicSalonInterface *_interface;
    unsigned _nbPlaces;
    unsigned _nbClients;
};

#endif // APPLICATION_H
