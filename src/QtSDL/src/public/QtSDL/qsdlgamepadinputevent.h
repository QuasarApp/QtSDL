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
     * @note the modifier mask take into account the Qt KeyboardModifiers mask that is 0xfe000000.
     *  (So you can use Qt::KeyboardModifiers together with this modifiers)
     */
    enum Modifiers {
        None = 0x0,

        L1 = 0x00010000,
        L2 = 0x00020000,
        L3 = 0x00040000,

        R1 = 0x00080000,
        R2 = 0x00100000,
        R3 = 0x00200000,

        Reserved0  = 0x00400000,
        Reserved1  = 0x00800000,
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
