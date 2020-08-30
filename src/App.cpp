#include<iostream>

#include"Game.h"


int main(void)
{
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "use [up][down][right][left] to control " << std::endl;
    std::cout << "[r] to reset " << std::endl;
    std::cout << "[page up] and [page down] to switch level" << std::endl;
    std::cout << "[backspace] to go back to previous step " << std::endl;
    std::cout << "-------------------------------------------" << std::endl;


    GLFWwindow* window;

    
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(544, 644, "PushBox", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);





    GLenum err = glewInit();
    if (GLEW_OK != err)
        std::cout << "err" << std::endl;
   // std::cout << glGetString(GL_VERSION) << std::endl;
   
    Game game("res/map/", "res/texture/bmp/", "res/shader/App.shader", 1);
    game.Init();
  
    game.setEventHandling();

    glfwSetKeyCallback(window, GameBase::keycallback_dispatch);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
                    
            game.DrawMap();


            glfwSwapBuffers(window);
            glfwPollEvents();
           
           

        }
    glfwTerminate();
    return 0;
}

