#include<GL/glew.h>
#include <GLFW/glfw3.h>

#include<iostream>

#include"Renderer.h"
#include"VertexBuffer.h"
#include"VertexBufferLayout.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"Texture.h"
#include"Map.h"

#include"vendor/glm/glm.hpp"
#include"vendor/glm/gtc/matrix_transform.hpp"

struct vertex
{
    float positions[2];
    float texcoor[2];
    float texid;

};




void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(550, 550, "Hello World", NULL, NULL);
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
    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions[] = {
            // positions        // texture coords
             -0.5f, -0.5f,  0.0f,0.0f,
              0.5f, -0.5f,  1.0f,0.0f,
              0.5f,  0.5f,  1.0f,1.0f,
             -0.5f,  0.5f,  0.0f,1.0f
        };


        unsigned int indices[] = {
            0, 1, 2, // first triangle
            2, 3, 0  // second triangle
        };

        //GLCall(glEnable(GL_BLEND));
        //GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        Texture texture1("res/texture/1.png");
        Texture texture2("res/texture/2.png");

        Shader shader("res/shader/shader.shader");
        shader.Bind();
       
        
        texture1.Bind();
        texture2.Bind();


        Map map("res/map/", 1);
        shader.SetUniform1i("texture1", 0);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            processInput(window);

            /* Render here */
            renderer.Clear();
          //  shader.Bind();
            renderer.Draw(va, ib, shader);



            glfwSwapBuffers(window);
            glfwPollEvents();
            
        }

    }


    glfwTerminate();
    return 0;
}

