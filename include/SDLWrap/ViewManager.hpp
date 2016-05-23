
#ifndef SDLWRAP_VIEW_MANAGER_HPP
#define SDLWRAP_VIEW_MANAGER_HPP

#include <cstddef>
#include <vector>

namespace sdl {
    class View;
    
    class ViewManager {
    public:
        ViewManager();
        virtual ~ViewManager();
        
        /**
         * \brief Push a new view onto the stack.
         */
        void push(View &v);
        
        /**
         * \brief Pop views off of the stack.
         * 
         * Removes views from the top of the stack. For each view removed this
         * will call their stop method in order (top to bottom).
         * 
         * \param \c views The number of Views to remove.
         */
        void pop(std::size_t views=1);
        
        /**
         * \brief Change the topmost element for the given view.
         *
         * This is faster than a pop and push combo, as it does not call the
         * resume method of the view which would be revealed by the pop.
         *
         * For views which do significant work on being resumed or paused, this
         * saves a call to both methods.
         * 
         * \param \c v The view to swap onto the stack
         */
        void swap(View &v);
        
        /**
         * \brief Get the topmost item off the stack, offset by \c depth.
         * 
         * The default value of back gives the topmost element on the stack.
         * 
         * \param \c depth The depth of the view to return
         * \return A reference to the view at the given depth
         */
        View & peek(std::size_t depth=0);
        const View & peek(std::size_t depth=0) const;
        
        /**
         * \brief Remove all views from this stack.
         */
        void clear();
        
        /**
         * \brief Get the number of elements on the stack.
         * 
         * \return The number of elements on the stack.
         */
        std::size_t size() const;
    protected:
        std::vector<View *> mViews;
    };
}

#endif
