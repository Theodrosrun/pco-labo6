//     ____  __________ ___   ____ ___  ___
//    / __ \/ ____/ __ \__ \ / __ \__ \|__ \
//   / /_/ / /   / / / /_/ // / / /_/ /__/ /
//  / ____/ /___/ /_/ / __// /_/ / __// __/
// /_/    \____/\____/____/\____/____/____/
//
// Rien à modifier

#ifndef BARBER_H
#define BARBER_H

#include "utils/launchable.h"
#include "utils/graphicsaloninterface.h"
#include "salon.h"

class Barber : public Launchable
{
public:
    Barber(GraphicSalonInterface *interface, std::shared_ptr<SalonBarberInterface> salon);

    /*!
     * \brief Fonction lancée par le thread, représente le comportement du télécabine
     */
    void run() override;

    /*!
     * \brief Message affiché au lancement du thread
     */
    void printStartMessage() override {qDebug() << "[START] Thread du barbier lancé";}

    /*!
     * \brief Message affiché après la fin du thread
     */
    void printCompletionMessage() override {qDebug() << "[STOP] Thread du barbier a terminé";}

private:
    GraphicSalonInterface *_interface;
    std::shared_ptr<SalonBarberInterface> _salon;

};

#endif // BARBER_H
