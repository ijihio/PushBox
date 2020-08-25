#include"GLFW/glfw3.h"
class GameBase
{
public:
    virtual void keycallback(
        GLFWwindow* window,
        int key,
        int scancode,
        int action,
        int mods) = 0; /* purely abstract function */

    static GameBase* event_handling_instance;
    // technically setEventHandling should be finalized so that it doesn't
    // get overwritten by a descendant class.
    virtual void setEventHandling() { event_handling_instance = this; }

    static void  keycallback_dispatch(
        GLFWwindow* window,
        int key,
        int scancode,
        int action,
        int mods)
    {
        if (event_handling_instance)
            event_handling_instance->keycallback(window, key, scancode, action, mods);
    }
};