# QSDL Wrapper
This is small qt lib for handle raw sdl events:


## Short example of use: 

initialise listner manager

``` cpp
#include "sdleventmanager.h"
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

