
#include "SDLWrap/Event.hpp"

using namespace sdl;

#define CAST_TO_EVENT(u32) \
    (*((Event::Type *)((void*)(&(u32)))))

Event::Event() { }
Event::Event(const Event &source) {
    mEvent = source.mEvent;
}
Event::~Event() { }

Event & Event::operator=(const Event &event) {
    mEvent = event.mEvent;
    return *this;
}

Event::Type Event::type() const {
    return ((Event::Type)(mEvent.type));
}

CommonEvent & Event::common() {
    return mEvent.common;
}
const CommonEvent & Event::common() const {
    return mEvent.common;
}

WindowEvent & Event::window() {
    return mEvent.window;
}
const WindowEvent & Event::window() const {
    return mEvent.window;
}

KeyboardEvent & Event::keyboard() {
    return mEvent.key;
}
const KeyboardEvent & Event::keyboard() const {
    return mEvent.key;
}

TextEditingEvent & Event::textEdit() {
    return mEvent.edit;
}
const TextEditingEvent & Event::textEdit() const {
    return mEvent.edit;
}

TextInputEvent & Event::textInput() {
    return mEvent.text;
}
const TextInputEvent & Event::textInput() const {
    return mEvent.text;
}

MouseMotionEvent & Event::mouseMotion() {
    return mEvent.motion;
}
const MouseMotionEvent & Event::mouseMotion() const {
    return mEvent.motion;
}

MouseButtonEvent & Event::mouseButton() {
    return mEvent.button;
}
const MouseButtonEvent & Event::mouseButton() const {
    return mEvent.button;
}

MouseWheelEvent & Event::mouseWheel() {
    return mEvent.wheel;
}
const MouseWheelEvent & Event::mouseWheel() const {
    return mEvent.wheel;
}

JoyAxisEvent & Event::joyAxis() {
    return mEvent.jaxis;
}
const JoyAxisEvent & Event::joyAxis() const {
    return mEvent.jaxis;
}

JoyBallEvent & Event::joyBall() {
    return mEvent.jball;
}
const JoyBallEvent & Event::joyBall() const {
    return mEvent.jball;
}

JoyHatEvent & Event::joyHat() {
    return mEvent.jhat;
}
const JoyHatEvent & Event::joyHat() const {
    return mEvent.jhat;
}

JoyButtonEvent & Event::joyButton() {
    return mEvent.jbutton;
}
const JoyButtonEvent & Event::joyButton() const {
    return mEvent.jbutton;
}

JoyDeviceEvent & Event::joyDevice() {
    return mEvent.jdevice;
}
const JoyDeviceEvent & Event::joyDevice() const {
    return mEvent.jdevice;
}

ControllerAxisEvent & Event::controllerAxis() {
    return mEvent.caxis;
}
const ControllerAxisEvent & Event::controllerAxis() const {
    return mEvent.caxis;
}

ControllerButtonEvent & Event::controllerButton() {
    return mEvent.cbutton;
}
const ControllerButtonEvent & Event::controllerButton() const {
    return mEvent.cbutton;
}

ControllerDeviceEvent & Event::controllerDevice() {
    return mEvent.cdevice;
}
const ControllerDeviceEvent & Event::controllerDevice() const {
    return mEvent.cdevice;
}

QuitEvent & Event::quit() {
    return mEvent.quit;
}
const QuitEvent & Event::quit() const {
    return mEvent.quit;
}

UserEvent & Event::user() {
    return mEvent.user;
}
const UserEvent & Event::user() const {
    return mEvent.user;
}

SysWMEvent & Event::sysWM() {
    return mEvent.syswm;
}
const SysWMEvent & Event::sysWM() const {
    return mEvent.syswm;
}

TouchEvent & Event::touch() {
    return mEvent.tfinger;
}
const TouchEvent & Event::touch() const {
    return mEvent.tfinger;
}

MultiGestureEvent & Event::multiGesture() {
    return mEvent.mgesture;
}
const MultiGestureEvent & Event::multiGesture() const {
    return mEvent.mgesture;
}

GestureEvent & Event::gesture() {
    return mEvent.dgesture;
}
const GestureEvent & Event::gesture() const {
    return mEvent.dgesture;
}

DropFileEvent & Event::drop() {
    return mEvent.drop;
}
const DropFileEvent & Event::drop() const {
    return mEvent.drop;
}
