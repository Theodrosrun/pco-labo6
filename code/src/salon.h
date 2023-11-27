//     ____  __________ ___   ____ ___  ___
//    / __ \/ ____/ __ \__ \ / __ \__ \|__ \
//   / /_/ / /   / / / /_/ // / / /_/ /__/ /
//  / ____/ /___/ /_/ / __// /_/ / __// __/
// /_/    \____/\____/____/\____/____/____/
//
// Rien à modifier

#ifndef SALON_H
#define SALON_H

#include "salonbarberinterface.h"
#include "salonclientinterface.h"

class Salon : public SalonBarberInterface, public SalonClientInterface
{
public:
    /*!
     * \brief endService Permet au barbier de fermer le salon
     */
    virtual void endService() = 0;
};

#endif // SALON_H
