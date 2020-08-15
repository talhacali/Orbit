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

    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void key_input(GLFWwindow* window);

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

        //glfwSetKeyCallback(window, key_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glEnable(GL_DEPTH_TEST);


        glm::vec3 position(0.0f, 1.0f, -4.0f), position1(0.0f, 1.0f, -10.0f), position2(-3.0f, 1.0f, -7.0f), position3(3.0f, 1.0f, -7.0f), rotation(0.0f, 0.0f, 1.0f);
        glm::vec3 direction(-0.2f, -1.0f, -0.3f);
        glm::vec3 ambient(0.05f, 0.05f, 0.05f);
        glm::vec3 diffuse(0.4f, 0.4f, 0.4f);
        glm::vec3 specular(0.5f, 0.5f, 0.5f);

        Shader shader("Dependencies\\Resources\\Shaders\\vertex_shader.glsl", "Dependencies\\Resources\\Shaders\\fragment_shader.glsl");
        Shader shaderLightSource("Dependencies\\Resources\\Shaders\\light_vertex_shader.glsl", "Dependencies\\Resources\\Shaders\\light_fragment_shader.glsl");
        Texture diffuseMap("Dependencies\\Resources\\Textures\\container2.png", GL_RGB, GL_RGBA, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
        Texture specularMap("Dependencies\\Resources\\Textures\\container2_specular.png", GL_RGB, GL_RGBA, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

        DirectionalLight dirLight(direction, ambient, diffuse, specular);

        glm::vec3 pointLightPositions[] = {
        glm::vec3(0.0f, 1.0f, -7.0f),
        };

        camera = std::make_shared<FlyCamera>(glm::vec3(0.0f, 0.0f, 3.0f));

        PointLight pointLight(shaderLightSource, pointLightPositions[0], ambient, diffuse, specular, 1.0f, 0.09f, 0.032f, camera);

        pointLight.Init();

        pointLights.push_back(pointLight);

        Material material(shader, diffuseMap, specularMap, dirLight, pointLights, 2.0f);

        ECS::EntityHandle cube1 = ecs.CreateEntity<Cube>();
        ECS::EntityHandle cube2 = ecs.CreateEntity<Cube>();
        ECS::EntityHandle cube3 = ecs.CreateEntity<Cube>();
        ECS::EntityHandle cube4 = ecs.CreateEntity<Cube>();

        cubes.push_back(cube1);
        cubes.push_back(cube2);
        cubes.push_back(cube3);
        cubes.push_back(cube4);

        ECS::ComponentHandle renderable1 = ecs.CreateComponent<Renderable, Cube>(cubes[0], material, 1280.0f, 720.0f, camera);
        ECS::ComponentHandle renderable2 = ecs.CreateComponent<Renderable, Cube>(cubes[1], material, 1280.0f, 720.0f, camera);
        ECS::ComponentHandle renderable3 = ecs.CreateComponent<Renderable, Cube>(cubes[2], material, 1280.0f, 720.0f, camera);
        ECS::ComponentHandle renderable4 = ecs.CreateComponent<Renderable, Cube>(cubes[3], material, 1280.0f, 720.0f, camera);

        renderables.push_back(renderable1);
        renderables.push_back(renderable2);
        renderables.push_back(renderable3);
        renderables.push_back(renderable4);

        ECS::ComponentHandle transform1 = ecs.CreateComponent<Transform, Cube>(cubes[0], position, rotation, 20.0f);
        ECS::ComponentHandle transform2 = ecs.CreateComponent<Transform, Cube>(cubes[1], position1, rotation, 12.0f);
        ECS::ComponentHandle transform3 = ecs.CreateComponent<Transform, Cube>(cubes[2], position2, rotation, 42.0f);
        ECS::ComponentHandle transform4 = ecs.CreateComponent<Transform, Cube>(cubes[3], position3, rotation, 130.0f);
        
        transforms.push_back(transform1);
        transforms.push_back(transform2);
        transforms.push_back(transform3);
        transforms.push_back(transform4);

        /*
        cube = ecs.CreateEntity<Cube>();

        renderable = ecs.CreateComponent<Renderable,Cube>(cube, material, 1280.0f, 720.0f, camera);
        transform = ecs.CreateComponent<Transform, Cube>(cube, position, rotation, 2.0f);
        */

        render = ecs.CreateSystem<Render>(&ecs);

        ecs.RegisterEntity<Render>(render, cubes[0]);
        ecs.RegisterEntity<Render>(render, cubes[1]);
        ecs.RegisterEntity<Render>(render, cubes[2]);
        ecs.RegisterEntity<Render>(render, cubes[3]);

        ecs.Init();
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

            key_input(window);
            
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            ecs.Update(deltaTime);

            pointLights[0].Render();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
	}


    void key_input(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            (*(gameInstance->camera)).Move(CAMERA_MOVE_DIRECTION::FORWARD, 5, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            (*(gameInstance->camera)).Move(CAMERA_MOVE_DIRECTION::BACKWARD, 5, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            (*(gameInstance->camera)).Move(CAMERA_MOVE_DIRECTION::LEFT, 5, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            (*(gameInstance->camera)).Move(CAMERA_MOVE_DIRECTION::RIGHT, 5, deltaTime);
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

        float sensitivity = 0.1f;

       (*(gameInstance->camera)).Rotate(yoffset * sensitivity, xoffset * sensitivity);
       

    }
    
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}