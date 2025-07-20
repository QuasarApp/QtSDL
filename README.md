# QSDL Wrapper
This is a small Qt library designed to handle raw SDL events. It provides a bridge between SDL's low-level event system and Qt's high-level event loop, ensuring safe and convenient integration.


## SDLEventManager
The SDLEventManager is a pivotal class that manages SDL events by redirecting them to Qt's event loop.

This class inherits from QThread and runs its own dedicated event loop to continuously poll for SDL events. Upon receiving an SDL event, it intelligently wraps it into a custom QSDLEvent or one of its specialized derived classes and posts it to the main Qt application's event queue. This design ensures that all SDL events are processed within the Qt event handling mechanism, guaranteeing thread safety and seamless integration of low-level SDL input (e.g., keyboard, mouse, game controllers) with Qt's GUI and application logic.

It also handles the lifecycle of connected gamepads, opening and closing them in response to SDL device connection/disconnection events.


## Supported Event Types
The SDLEventManager wraps the following specialized SDL event types into their corresponding Qt event classes:

- QSDLGamepadAxisEvent (for SDL_EVENT_GAMEPAD_AXIS_MOTION)
- QSDLGamepadButtonEvent (for SDL_EVENT_GAMEPAD_BUTTON_DOWN, SDL_EVENT_GAMEPAD_BUTTON_UP)
- QSDLGamepadEvent (for SDL_EVENT_GAMEPAD_ADDED, SDL_EVENT_GAMEPAD_REMOVED)
- QSDLGamepadSensorEvent (for SDL_EVENT_GAMEPAD_SENSOR_UPDATE)
- QSDLGamepadTouchpadEvent (for SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN, SDL_EVENT_TOUCHPAD_MOTION, SDL_EVENT_TOUCHPAD_UP)


## Important Notes

This manager should be initialized and started early in your application's lifecycle.

Crucially, ensure that QtSDL::init() has been successfully invoked before using this class.

## Short example of use: 

initialise listner manager

``` cpp

#include "sdleventmanager.h"

QtSDL::init();

QtSDL::SDLEventManager* manager = new QtSDL::SDLEventManager();
manager.start();

```

handle events: 

``` cpp

class QObjectChild: public QObject {
...

    bool event(QEvent* ev) override {
        if (auto sdl = dynamci_cast<QSDLEvent>(ev)) {
            ...
        }
    }
...
}

```

