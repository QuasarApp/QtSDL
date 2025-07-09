//#
//# Copyright (C) 2025-2025 QuasarApp.
//# Distributed under the lGPLv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#


#ifndef QSDLEVENT_H
#define QSDLEVENT_H
#include <QEvent>
#include <SDL3/SDL.h>

/**
 * @brief The QSDLEvent class this is event implementation of sdl signals
 */
class QSDLEvent: public QEvent
{
public:
    enum Type {
        SDLType = QEvent::Type::User
    };

    explicit QSDLEvent(SDL_Event event, SDL_EventType type);

    // QEvent interface
    void setAccepted(bool accepted) override;
    QEvent *clone() const override;

    SDL_Event data() const;
    void setData(const SDL_Event &newData);

    SDL_EventType sdlType() const;
    void setSdlType(SDL_EventType newSdlType);

private:
    SDL_Event _data;
    SDL_EventType _sdlType;
};

#endif // QSDLEVENT_H
