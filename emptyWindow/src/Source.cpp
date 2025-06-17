#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "../vendor/stb_image.h"
#include "Shaders/Shader.h"
#include <cmath>
#include <Eigen/Dense>
#include <../glm/glm.hpp>
#include <../glm/gtc/matrix_transform.hpp>
#include <../glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Constants.h"
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool firstMouse = true;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;


float deltaTime = 0.0f;	
float lastFrame = 0.0f;
int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // GLAD
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Shader ourShader;

    //---FACE
    float vertices[] = {
        // front face
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  // top right
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // bottom right
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  // bottom left
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  // top left

        // back face
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  // top right
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  // bottom right
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // bottom left
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  // top left

        // left face
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  // top right
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // bottom right
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // bottom left
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  // top left

        // right face
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  // top right
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // bottom right
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // bottom left
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  // top left

         // top face
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  // top right
         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  // top left
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // bottom left
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // bottom right

          // bottom face
           0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  // top right
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // top left
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // bottom left
           0.5f, -0.5f, -0.5f,  1.0f, 1.0f   // bottom right
    };

    unsigned int indices[] = {
        // front face
        0, 3, 1, 
        1, 3, 2,

        // back face
        4, 5, 7,
        5, 6, 7,

        // left face
        8, 11, 9,
        9, 11, 10,

        // right face
        12, 13, 15,
        13, 14, 15,

        // top face
        16, 19, 17,
        17, 19, 18,

        // bottom face
        20, 21, 23,
        21, 22, 23
    };

    unsigned int VBO = 0, VAO = 0, EBO = 0;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 120 * sizeof(float), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //--- TEXTURES!!!
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char* data = stbi_load("Grass_Texture.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);



    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, texture);  
        ourShader.use();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, 0.0f, glm::vec3(0.5f, 1.0f, 0.0f));

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)Constants::SCREEN_WIDTH / (float)Constants::SCREEN_HEIGHT, 0.1f, 100.0f);

        glm::mat4 view = camera.GetViewMatrix();

        int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);  

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;
    camera.ProcessMouseMovement(xoffset, yoffset);
}
