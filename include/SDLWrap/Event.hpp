
#ifndef SDLWRAP_EVENT_HPP
#define SDLWRAP_EVENT_HPP

#include "SDL_events.h"

namespace sdl {
    typedef SDL_CommonEvent CommonEvent;
    typedef SDL_WindowEvent WindowEvent;
    typedef SDL_KeyboardEvent KeyboardEvent;
    typedef SDL_TextEditingEvent TextEditingEvent;
    typedef SDL_TextInputEvent TextInputEvent;
    typedef SDL_MouseMotionEvent MouseMotionEvent;
    typedef SDL_MouseButtonEvent MouseButtonEvent;
    typedef SDL_MouseWheelEvent MouseWheelEvent;
    typedef SDL_JoyAxisEvent JoyAxisEvent;
    typedef SDL_JoyBallEvent JoyBallEvent;
    typedef SDL_JoyHatEvent JoyHatEvent;
    typedef SDL_JoyButtonEvent JoyButtonEvent;
    typedef SDL_JoyDeviceEvent JoyDeviceEvent;
    typedef SDL_ControllerAxisEvent ControllerAxisEvent;
    typedef SDL_ControllerButtonEvent ControllerButtonEvent;
    typedef SDL_ControllerDeviceEvent ControllerDeviceEvent;
    typedef SDL_TouchFingerEvent TouchEvent;
    typedef SDL_MultiGestureEvent MultiGestureEvent;
    typedef SDL_DollarGestureEvent GestureEvent;
    typedef SDL_DropEvent DropFileEvent;
    typedef SDL_QuitEvent QuitEvent;
    typedef SDL_OSEvent OSEvent;
    typedef SDL_UserEvent UserEvent;
    typedef SDL_SysWMEvent SysWMEvent;
    
    class Event {
    public:
        // Remap SDL_EventType to Event::... enum values
        enum Type {
            Quit = SDL_QUIT,
            
            // Mobile Events
            App_Terminating = SDL_APP_TERMINATING,
            App_LowMemory = SDL_APP_LOWMEMORY,
            App_WillEnterBackground = SDL_APP_WILLENTERBACKGROUND,
            App_DidEnterBackground = SDL_APP_DIDENTERBACKGROUND,
            App_WillEnterForeground = SDL_APP_WILLENTERFOREGROUND,
            App_DidEnterForeground = SDL_APP_DIDENTERFOREGROUND,
            
            // Window events
            Window = SDL_WINDOWEVENT,
            SysWM = SDL_SYSWMEVENT,
            
            // Keyboard Events
            KeyDown = SDL_KEYDOWN,
            KeyUp = SDL_KEYUP,
            TextEditing = SDL_TEXTEDITING,
            TextInput = SDL_TEXTINPUT,
            
            // Mouse Events
            MouseMotion = SDL_MOUSEMOTION,
            MouseButtonDown = SDL_MOUSEBUTTONDOWN,
            MouseButtonUp = SDL_MOUSEBUTTONUP,
            MouseWheel = SDL_MOUSEWHEEL,
            
            // Joystick Events
            JoyAxisMotion = SDL_JOYAXISMOTION,
            JoyBallMotion = SDL_JOYBALLMOTION,
            JoyHatMotion = SDL_JOYHATMOTION,
            JoyButtonDown = SDL_JOYBUTTONDOWN,
            JoyButtonUp = SDL_JOYBUTTONUP,
            JoyAdded = SDL_JOYDEVICEADDED,
            JoyRemoved = SDL_JOYDEVICEREMOVED,
            
            // Game Controller
            ControllerAxisMotion = SDL_CONTROLLERAXISMOTION,
            ControllerButtonDown = SDL_CONTROLLERBUTTONDOWN,
            ControllerButtonUp = SDL_CONTROLLERBUTTONUP,
            ControllerAdded = SDL_CONTROLLERDEVICEADDED,
            ControllerRemoved = SDL_CONTROLLERDEVICEREMOVED,
            ControllerRemapped = SDL_CONTROLLERDEVICEREMAPPED,
            
            // Touch Events
            FingerDown = SDL_FINGERDOWN,
            FingerUp = SDL_FINGERUP,
            FingerMotion = SDL_FINGERMOTION,
            
            // Gesture Events
            DollarGesture = SDL_DOLLARGESTURE,
            DollarRecord = SDL_DOLLARRECORD,
            MultiGesture = SDL_MULTIGESTURE,
            ClipboardUpdate = SDL_CLIPBOARDUPDATE,
            DropFile = SDL_DROPFILE,
            RenderTargetsReset = SDL_RENDER_TARGETS_RESET,
            User = SDL_USEREVENT,
            LastEvent = SDL_LASTEVENT
        };
        
        /**
         * \brief Remove all events that match the given type from the queue.
         * 
         * Wraps \c SDL_FlushEvent(SDL_EventType)
         * 
         * \arg \c type The type of the event to clear.
         */
        static void Flush(Event::Type type);
        
        /**
         * \brief Remove all events whose type falls between min and max.
         * 
         * Wraps \c SDL_FlushEvent(SDL_EventType, SDL_EventType)
         * This function is good for clearing all events from a input source,
         * such as clearing all keyboard input. Calling the function as:
         *   Event::Flush(Event::KeyDown, Event::TextInput)
         * will remove all instance of any key or text event.
         * 
         * \arg \c minType The initial type to start at
         * \arg \c maxType The highest type to clear.
         */
        static void Flush(Event::Type minType, Event::Type maxType);
        
        /**
         * \brief Check if there are any events in the queue which match the
         * type.
         * 
         * Wraps SDL_HasEvent(SDL_EventType)
         * 
         * \arg \c type The type of event to check for.
         * \return If the given type of event is present in the queue.
         */
        static bool Has(Event::Type type);
        
        /**
         * \brief Check if any event on the queue matches the given range.
         * 
         * Wraps SDL_HasEvent(SDL_EventType, SDL_EventType)
         * Good for checking if the queue holds any events from a given input
         * source. For example, calling this as:
         *   Event::Has(Event::KeyDown, Event::TextInput)
         * will check if any keyboard or text event has happened.
         * 
         * \arg \c minType The start of the range to check the queue for.
         * \arg \c maxType The end of the range to check the queue for.
         * 
         * \return If any event in the queue falls in the given range.
         */
        static bool Has(Event::Type minType, Event::Type maxType);
        
        /**
         * \brief Remove and return the oldest event on the queue.
         * 
         * Wraps SDL_PollEvent(SDL_Event *)
         * 
         * \arg \c event The event to store the information in.
         * \return If this call resulted in removing an event from the queue.
         */
        static bool Poll(Event &event);
        
        /**
         * \brief Remove and return an event from the queue, waiting if needed.
         * 
         * Wraps SDL_WaitEvent(SDL_Event *)
         * 
         * \arg \c event The event to store the information in.
         * \return If an event was retrieved.
         */
        static bool Wait(Event &event);
        
        /**
         * \brief Remove and return an event, waiting for the given timeout.
         * 
         * Wraps SDL_WaitEventTimeout(SDL_Event *, int)
         * 
         * \arg \c event The event to store the information in.
         * \return If an event was retrieved.
         */
        static bool Wait(Event &event, int milliseconds);
        
        /**
         * \brief Put an event on the event queue.
         * 
         * Wraps SDL_PushEvent(SDL_Event *)
         * 
         * \arg \c event The event to copy to the queue.
         */
        static void Push(Event &event);
    
    public:
        Event();
        Event(const Event &source);
        ~Event();
        
        Event & operator=(const Event &source);
        
        Event::Type  type() const;
        
        CommonEvent & common();
        const CommonEvent & common() const;
        
        WindowEvent & window();
        const WindowEvent & window() const;
        
        KeyboardEvent & keyboard();
        const KeyboardEvent & keyboard() const;
        
        TextEditingEvent & textEdit();
        const TextEditingEvent & textEdit() const;
        
        TextInputEvent & textInput();
        const TextInputEvent & textInput() const;
        
        MouseMotionEvent & mouseMotion();
        const MouseMotionEvent & mouseMotion() const;
        
        MouseButtonEvent & mouseButton();
        const MouseButtonEvent & mouseButton() const;
        
        MouseWheelEvent & mouseWheel();
        const MouseWheelEvent & mouseWheel() const;
        
        JoyAxisEvent & joyAxis();
        const JoyAxisEvent & joyAxis() const;
        
        JoyBallEvent & joyBall();
        const JoyBallEvent & joyBall() const;
        
        JoyHatEvent & joyHat();
        const JoyHatEvent & joyHat() const;
        
        JoyButtonEvent & joyButton();
        const JoyButtonEvent & joyButton() const;
        
        JoyDeviceEvent & joyDevice();
        const JoyDeviceEvent & joyDevice() const;
        
        ControllerAxisEvent & controllerAxis();
        const ControllerAxisEvent & controllerAxis() const;
        
        ControllerButtonEvent & controllerButton();
        const ControllerButtonEvent & controllerButton() const;
        
        ControllerDeviceEvent & controllerDevice();
        const ControllerDeviceEvent & controllerDevice() const;
        
        QuitEvent & quit();
        const QuitEvent & quit() const;
        
        UserEvent & user();
        const UserEvent & user() const;
        
        SysWMEvent & sysWM();
        const SysWMEvent & sysWM() const;
        
        TouchEvent & touch();
        const TouchEvent & touch() const;
        
        MultiGestureEvent & multiGesture();
        const MultiGestureEvent & multiGesture() const;
        
        GestureEvent & gesture();
        const GestureEvent & gesture() const;
        
        DropFileEvent & drop();
        const DropFileEvent & drop() const;
    private:
        SDL_Event mEvent;
    };
}

#endif
