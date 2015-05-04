
#ifndef SDLWRAP_VIEW_HPP
#define SDLWRAP_VIEW_HPP

namespace sdl {
    class Event;
    class Graphics;
    class ViewManager;
    
    class View {
    public:
        virtual ~View();
        
        /**
         * \brief Internal interface for the ViewManager class.
         */
        void _start(ViewManager &m);
        /**
         * \brief Internal interface for the ViewManager class.
         */
        void _stop();
        
        /**
         * \brief Initialize the view.
         * 
         * This is called by the view manager when the view is initally pushed
         * onto the stack. This should do any initialization that should last
         * for the lifetime of the object.
         */
        virtual void start();
        
        /**
         * \brief 
         * 
         * This is called by the view manager when the view is covered by
         * a push onto the stack.
         */
        virtual void pause();
        
        /**
         * \brief Reinitialize view when uncovered on stack.
         * 
         * This is called by the view manager when the view is uncovered by
         * a pop from the view stack.
         */
        virtual void resume();
        
        /**
         * \brief 
         * 
         * Called by the view manager when the view is removed from the view
         * stack by a pop or swap.
         */
        virtual void stop();
        
        /**
         * \brief Render this view to the given graphics context.
         * 
         * The view should not call the present method of the graphics context
         * given to it; this is handled by the Application instance. This
         * allows views to render views below themselves on the ViewManager's
         * stack. Useful for menus which want to render a previous View,
         * fade it, then draw itself.
         * 
         * The graphics context must be initialized by the caller of this
         * method. For normal instances this is done by the Application
         * context. If a view is being rendered to a texture target, this
         * should be done by the view which is is calling this method.
         * 
         * \param \c g The graphics context to render to.
         */
        virtual void render(Graphics &g);
        
        /**
         * \brief Handle the given event
         * 
         * Handle an event polled from the SDL subsystems. If the view has
         * handled the event it should return true, false otherwise. If this
         * method returns false the Application instance will attempt to handle
         * the event.
         * 
         * The default behavior of the Application instance is to only handle
         * quit events, which terminates the entire application immediately.
         * 
         * \param \c e The event to handle
         * \return If the event was handled
         */
        virtual bool handle(Event &e);
    protected:
        View();
        
        ViewManager *mManager;
    };
}

#endif
