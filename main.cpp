#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Error.h"
#include "Program.h"
#include "Texture.h"
#include "Camera.h"
#include "RubiksCube.h"
#include "Skybox.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = (float)SCREEN_WIDTH / 2.0;
float lastY = (float)SCREEN_HEIGHT / 2.0;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

static RubiksCube rubiks_cube;
static SkyBox skybox;

bool init_objects();
void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return EXIT_FAILURE;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); CHECK_GL_ERROR();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); CHECK_GL_ERROR();
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); CHECK_GL_ERROR();

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RubiksCube - David Chemaly & Ulysse Baud", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window); CHECK_GL_ERROR();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); CHECK_GL_ERROR();
    glfwSetCursorPosCallback(window, mouse_callback); CHECK_GL_ERROR();
    glfwSetScrollCallback(window, scroll_callback); CHECK_GL_ERROR();

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    glEnable(GL_DEPTH_TEST); CHECK_GL_ERROR();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); CHECK_GL_ERROR();
    glEnable(GL_CULL_FACE); CHECK_GL_ERROR();

    std::string cube_vertex_shader_path = "shaders/RubiksCubeVS.glsl";
    std::string cube_fragment_shader_path = "shaders/RubiksCubeFS.glsl";
    CubeProgram = Program::make_program(cube_vertex_shader_path, cube_fragment_shader_path);
    if (!CubeProgram)
    {
        std::cerr << "ERROR::SHADERS::INIT_FAILED::CUBE" << std::endl;
        return false;
    }

    std::string skybox_vertex_shader_path = "shaders/SkyboxVS.glsl";
    std::string skybox_fragment_shader_path = "shaders/SkyboxFS.glsl";

    SkyboxProgram = Program::make_program(skybox_vertex_shader_path, skybox_fragment_shader_path);
    if (!SkyboxProgram)
    {
        std::cerr << "ERROR::SHADERS::INIT_FAILED::SKYBOX" << std::endl;
        return false;
    }

    if (!init_objects())
    {
        std::cerr << "ERROR::OBJECTS::INIT_FAILED" << std::endl;
        return false;
    }

    unsigned int cubemap_texture = loadCubemapTexture(faces);

    SkyboxProgram->use();
    SkyboxProgram->set_uniform_1i("skybox", 0);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); CHECK_GL_ERROR();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); CHECK_GL_ERROR();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f); CHECK_GL_ERROR();

        CubeProgram->use();

        // Rubiks Cube
        for (int i = 0; i < rubiks_cube.cubes.size(); i++)
        {
            Cube cube = rubiks_cube.cubes[i];
            glBindVertexArray(rubiks_cube.cubes[i].vao); CHECK_GL_ERROR();
        
            CubeProgram->set_uniform_Mat4fv("model", rubiks_cube.cubes[i].model); CHECK_GL_ERROR();
            CubeProgram->set_uniform_Mat4fv("view", camera.GetViewMatrix()); CHECK_GL_ERROR();
            CubeProgram->set_uniform_Mat4fv("projection", projection); CHECK_GL_ERROR();

            glDrawArrays(GL_TRIANGLES, 0, rubiks_cube.cubes[i].vertices_position.size()); CHECK_GL_ERROR();
        }

        glBindVertexArray(0); CHECK_GL_ERROR();

        // Skybox
        glDepthFunc(GL_LEQUAL); CHECK_GL_ERROR();
        SkyboxProgram->use(); CHECK_GL_ERROR();
        SkyboxProgram->set_uniform_Mat4fv("view", glm::mat4(glm::mat3(camera.GetViewMatrix()))); CHECK_GL_ERROR();
        SkyboxProgram->set_uniform_Mat4fv("projection", projection); CHECK_GL_ERROR();
        glBindVertexArray(skybox.vao); CHECK_GL_ERROR();
        glActiveTexture(GL_TEXTURE0); CHECK_GL_ERROR();
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture); CHECK_GL_ERROR();
        glDrawArrays(GL_TRIANGLES, 0, skybox.vertices_position.size()); CHECK_GL_ERROR();
        glBindVertexArray(0); CHECK_GL_ERROR();
        glDepthFunc(GL_LESS); CHECK_GL_ERROR();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

bool init_objects()
{
    // Rubiks Cube
    for (int i = 0; i < rubiks_cube.cubes.size(); i++)
    {
        int nb_buffer = 0;
        int index_buffer = 0;

        glGenVertexArrays(1, &rubiks_cube.cubes[i].vao); CHECK_GL_ERROR();
        glBindVertexArray(rubiks_cube.cubes[i].vao); CHECK_GL_ERROR();

        GLint cube_vbo_position = glGetAttribLocation(CubeProgram->get_program_id(), "position"); CHECK_GL_ERROR();
        GLint cube_vbo_color = glGetAttribLocation(CubeProgram->get_program_id(), "color"); CHECK_GL_ERROR();

        if (cube_vbo_position != -1) nb_buffer++;
        if (cube_vbo_color != -1) nb_buffer++;

        GLuint vbos[nb_buffer];

        glGenBuffers(nb_buffer, vbos); CHECK_GL_ERROR();

        if (cube_vbo_position == -1)
        {
            std::cerr << "ERROR::SHADERS::POSITION_NOT_FOUND" << std::endl;
            return false;
        }
        else
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbos[index_buffer++]); CHECK_GL_ERROR();
            glBufferData(GL_ARRAY_BUFFER, rubiks_cube.cubes[i].vertices_position.size() * sizeof(float), rubiks_cube.cubes[i].vertices_position.data(), GL_STATIC_DRAW); CHECK_GL_ERROR();

            glVertexAttribPointer(cube_vbo_position, 3, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERROR();
            glEnableVertexAttribArray(cube_vbo_position); CHECK_GL_ERROR();
        }

        if (cube_vbo_color == -1)
        {
            std::cerr << "ERROR::SHADERS::COLOR_NOT_FOUND" << std::endl;
            return false;
        }
        else
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbos[index_buffer++]); CHECK_GL_ERROR();
            glBufferData(GL_ARRAY_BUFFER, rubiks_cube.cubes[i].colors.size() * sizeof(float), rubiks_cube.cubes[i].colors.data(), GL_STATIC_DRAW); CHECK_GL_ERROR();

            glVertexAttribPointer(cube_vbo_color, 3, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERROR();
            glEnableVertexAttribArray(cube_vbo_color); CHECK_GL_ERROR();
        }

        glBindVertexArray(0); CHECK_GL_ERROR();
    }

    // Skybox
    glGenVertexArrays(1, &skybox.vao); CHECK_GL_ERROR();
    glBindVertexArray(skybox.vao); CHECK_GL_ERROR();

    GLint skybox_vbo_position = glGetAttribLocation(SkyboxProgram->get_program_id(), "position"); CHECK_GL_ERROR();

    if (skybox_vbo_position == -1)
    {
        std::cerr << "ERROR::SHADERS::POSITION_NOT_FOUND" << std::endl;
        return false;
    }
    else
    {
        GLuint skybox_vbo;

        glGenBuffers(1, &skybox_vbo); CHECK_GL_ERROR();

        glBindBuffer(GL_ARRAY_BUFFER, skybox_vbo); CHECK_GL_ERROR();
        glBufferData(GL_ARRAY_BUFFER, skybox.vertices_position.size() * sizeof(float), skybox.vertices_position.data(), GL_STATIC_DRAW); CHECK_GL_ERROR();

        glVertexAttribPointer(skybox_vbo_position, 3, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERROR();
        glEnableVertexAttribArray(skybox_vbo_position); CHECK_GL_ERROR();
    }

    glBindVertexArray(0); CHECK_GL_ERROR();

    return true;
}

void processInput(GLFWwindow *window)
{
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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}