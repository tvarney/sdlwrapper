
#include "SDLWrap/View.hpp"

#include "SDLWrap/Graphics.hpp"

using namespace sdl;

View::View() { }
View::~View() { }

void View::_start(ViewManager &m) {
    this->mManager = &m;
    this->start();
}
void View::_stop() {
    this->stop();
    this->mManager = nullptr;
}

void View::start() { }
void View::pause() { }
void View::resume() { }
void View::stop() { }

void View::render(Graphics &g) { }

bool View::handle(Event &e) {
    return false;
}
