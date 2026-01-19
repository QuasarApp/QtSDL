//#
//# Copyright (C) 2026-2026 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef QSDLGAMEPADINPUTEVENT_H
#define QSDLGAMEPADINPUTEVENT_H
#include "qsdlevent.h"

namespace QtSDL {

/**
 * @brief The QSDLGamepadInputEvent class this is a base class for all input events of gamepad.
 * Supported features:
 *    - modifiers
 *
 */
class QTSDL_EXPORT QSDLGamepadInputEvent: public QSDLEvent
{
public:

    /**
     * @brief The Modifiers enum is a bit mask of modifiers.
     */
    enum Modifiers {
        None = 0x0,

        L1 = 0x01000000,
        L2 = 0x02000000,
        L3 = 0x04000000,

        R1 = 0x08000000,
        R2 = 0x10000000,
        R3 = 0x20000000,

        Reserved0  = 0x40000000,
        Reserved1  = 0x80000000,
    };

    QSDLGamepadInputEvent(SDL_Event event, SDL_EventType type);

    /**
     * @brief modifiers is a bit mask of modifiers
     * @return modifiers.
     */
    int modifiers() const;

protected:

    /**
     * @brief setModifiers sets new modifiers for this event.
     * @param newModifiers this is a new modifiers bit mask.
     */
    void setModifiers(int newModifiers);

private:
    friend class SDLEventManager;

    int _modifiers = None;
};
}
#endif // QSDLGAMEPADINPUTEVENT_H
