//     ____  __________ ___   ____ ___  ___
//    / __ \/ ____/ __ \__ \ / __ \__ \|__ \
//   / /_/ / /   / / / /_/ // / / /_/ /__/ /
//  / ____/ /___/ /_/ / __// /_/ / __// __/
// /_/    \____/\____/____/\____/____/____/
//
// Rien à modifier

#ifndef CLIENT_H
#define CLIENT_H

#include "utils/launchable.h"
#include "utils/graphicsaloninterface.h"
#include "salon.h"

class Client : public Launchable
{
public:
    Client(GraphicSalonInterface *interface, std::shared_ptr<SalonClientInterface> salon);

    /*!
     * \brief Fonction lancée par le thread, représente le comportement du client
     */
    void run() override;

    /*!
     * \brief Message affiché lors du démarrage du thread
     */
    void printStartMessage() override {qDebug() << "[START] Thread du client" << _clientId << "lancé";}

    /*!
     * \brief Message affiché lorsque le thread a terminé
     */
    void printCompletionMessage() override {qDebug() << "[STOP] Thread du client" << _clientId << "a terminé";}

private:
    GraphicSalonInterface *_interface;
    std::shared_ptr<SalonClientInterface> _salon;

    /*!
     * \brief L'identificateur du Client
     */
     int _clientId;

    /*!
     * \brief L'identificateur pour le prochain Client créé
     */
    static int _nextId;
};

#endif // CLIENT_H
