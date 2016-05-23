
#include "SDLWrap/ViewManager.hpp"
#include "SDLWrap/View.hpp"

using namespace sdl;

ViewManager::ViewManager() { }
ViewManager::~ViewManager() {
    clear();
}

void ViewManager::push(View &v) {
    // If we already have an active view, pause it
    if(mViews.size() > 0) {
        mViews.back()->pause();
    }
    // Push the new view on the stack and start it
    mViews.push_back(&v);
    v._start(*this);
}

void ViewManager::pop(std::size_t nviews) {
    if(nviews > 0) {
        // Make sure that the number of views to pop is less than or equal to
        // the number of views in our vector.
        if(nviews > mViews.size()) {
            nviews = mViews.size();
        }
        // Iterate over the vector popping the requested number of views.
        for(std::size_t i = 0; i < nviews; ++i) {
            // Make sure to call the internal method _stop on each view.
            mViews.back()->_stop();
            mViews.pop_back();
        }
        // If we still have views on the stack, call the resume method on the
        // topmost view.
        if(mViews.size() > 0) {
            mViews.back()->resume();
        }
    }
}

void ViewManager::swap(View & v) {
    // If we already have a view on the stack, stop it and pop it.
    if(mViews.size() > 0) {
        mViews.back()->_stop();
        mViews.pop_back();
    }
    // Push the new view and start it
    mViews.push_back(&v);
    v._start(*this);
}

View & ViewManager::peek(std::size_t depth) {
    if(mViews.size() > depth) {
        return *mViews[mViews.size() - 1 - depth];
    }
    throw "Peek depbh exceeds size of View stack";
}

const View & ViewManager::peek(std::size_t depth) const {
    if(mViews.size() > depth) {
        return *mViews[mViews.size() - 1 - depth];
    }
    throw "Peek depth exceeds size of View stack";
}

void ViewManager::clear() {
    mViews.clear();
}

std::size_t ViewManager::size() const {
    return mViews.size();
}
