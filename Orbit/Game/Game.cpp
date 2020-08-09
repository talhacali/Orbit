#include "Game.h"

namespace Orbit
{
    Game* gameInstance;

    float lastX = 1280 / 2.0f;
    float lastY = 720 / 2.0f;
    bool isMouseFirst = true;

    // timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void Game::Init()
	{
        gameInstance = this;

        /* Initialize the library */
        if (!glfwInit())
            return;

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(1280, 720, "Orbit", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        if (glewInit() != GLEW_OK)
            std::cout << "Error!" << std::endl;

        glfwSetKeyCallback(window, key_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glEnable(GL_DEPTH_TEST);

	}

	//Main loop of the game.
	void Game::MainLoop()
	{

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            glfwPollEvents();

            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
	}


    

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            gameInstance->camera.Move(CAMERA_MOVE_DIRECTION::FORWARD,10, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            gameInstance->camera.Move(CAMERA_MOVE_DIRECTION::BACKWARD, 10, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            gameInstance->camera.Move(CAMERA_MOVE_DIRECTION::LEFT, 10, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            gameInstance->camera.Move(CAMERA_MOVE_DIRECTION::RIGHT, 10, deltaTime);
    }

    void mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {

        if (isMouseFirst)
        {
            lastX = xpos;
            lastY = ypos;
            isMouseFirst = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        std::cout << "mouse" << std::endl;

        //gameInstance->camera.Rotate(

    }
    
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}