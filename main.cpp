#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glob.h>

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
bool swapCubeTextures = true;
bool swapSkyboxTextures = true;
bool isRotating = false;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool init_shaders();
bool init_objects();
bool init_textures();

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
    glfwSetScrollCallback(window, scroll_callback); CHECK_GL_ERROR();

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    glEnable(GL_DEPTH_TEST); CHECK_GL_ERROR();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); CHECK_GL_ERROR();

    glEnable(GL_BLEND); CHECK_GL_ERROR();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); CHECK_GL_ERROR();

    glEnable(GL_CULL_FACE); CHECK_GL_ERROR();
    glCullFace(GL_BACK); CHECK_GL_ERROR();

    if (!init_shaders())
    {
        std::cerr << "ERROR::OBJECTS::INIT_FAILED" << std::endl;
        return false;
    }

    if (!init_objects())
    {
        std::cerr << "ERROR::OBJECTS::INIT_FAILED" << std::endl;
        return false;
    }

    if (!init_textures())
    {
        std::cerr << "ERROR::TEXTURES::INIT_FAILED" << std::endl;
        return false;
    }

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); CHECK_GL_ERROR();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); CHECK_GL_ERROR();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f); CHECK_GL_ERROR();

        // Skybox
        glDepthFunc(GL_LEQUAL); CHECK_GL_ERROR();
        SkyboxProgram->use(); CHECK_GL_ERROR();
        SkyboxProgram->set_uniform_Mat4fv("view", glm::mat4(glm::mat3(camera.GetViewMatrix()))); CHECK_GL_ERROR();
        SkyboxProgram->set_uniform_Mat4fv("projection", projection); CHECK_GL_ERROR();
        glBindVertexArray(skybox.vao); CHECK_GL_ERROR();
        glActiveTexture(GL_TEXTURE0); CHECK_GL_ERROR();
        glDrawArrays(GL_TRIANGLES, 0, skybox.vertices_position.size()); CHECK_GL_ERROR();
        glBindVertexArray(0); CHECK_GL_ERROR();
        glDepthFunc(GL_LESS); CHECK_GL_ERROR();

        CubeProgram->use();
        // Rubiks Cube
        for (int i = 0; i < rubiks_cube.cubes.size(); i++)
        {
            Cube cube = rubiks_cube.cubes[i];
            glBindVertexArray(rubiks_cube.cubes[i].vao); CHECK_GL_ERROR();
        
            CubeProgram->set_uniform_Mat4fv("model", rubiks_cube.cubes[i].get_model()); CHECK_GL_ERROR();
            CubeProgram->set_uniform_Mat4fv("view", camera.GetViewMatrix()); CHECK_GL_ERROR();
            CubeProgram->set_uniform_Mat4fv("projection", projection); CHECK_GL_ERROR();

            CubeProgram->set_uniform_1f("opacity", rubiks_cube.opacity); CHECK_GL_ERROR();

            glDrawArrays(GL_TRIANGLES, 0, rubiks_cube.cubes[i].vertices_position.size()); CHECK_GL_ERROR();
        }

        glBindVertexArray(0); CHECK_GL_ERROR();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

bool init_shaders()
{
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

    return true;
}

bool init_textures()
{
    // Rubiks Cube
    glob_t glob_result;
    glob("RubiksCubeTextures/*", GLOB_TILDE, NULL, &glob_result);

    for (unsigned int i = 0; i < glob_result.gl_pathc; ++i)
    {
        loadBasicTexture(glob_result.gl_pathv[i]);
    }

    glBindTexture(GL_TEXTURE_2D, rubiks_cube.get_next_texture_id()); CHECK_GL_ERROR();
    CubeProgram->use(); CHECK_GL_ERROR();
    CubeProgram->set_uniform_1i("tex", 0); CHECK_GL_ERROR();

    // Skybox
    skybox.current_texture_id = loadCubemapTexture(Skyfaces);
    skybox.current_texture_id = loadCubemapTexture(Volcanofaces);
    skybox.current_texture_id = loadCubemapTexture(Blackfaces);
    SkyboxProgram->use();
    SkyboxProgram->set_uniform_1i("skybox", 0);

    return true;
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
        GLint cube_vbo_texture = glGetAttribLocation(CubeProgram->get_program_id(), "texture_uv"); CHECK_GL_ERROR();

        if (cube_vbo_position != -1) nb_buffer++;
        if (cube_vbo_texture != -1) nb_buffer++;

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

        if (cube_vbo_texture == -1)
        {
            std::cerr << "ERROR::SHADERS::TEXTURE_NOT_FOUND" << std::endl;
            return false;
        }
        else
        {
            glBindBuffer(GL_ARRAY_BUFFER, vbos[index_buffer++]); CHECK_GL_ERROR();
            glBufferData(GL_ARRAY_BUFFER, rubiks_cube.cubes[i].texture_coords.size() * sizeof(float), rubiks_cube.cubes[i].texture_coords.data(), GL_STATIC_DRAW); CHECK_GL_ERROR();

            glVertexAttribPointer(cube_vbo_texture, 2, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERROR();
            glEnableVertexAttribArray(cube_vbo_texture); CHECK_GL_ERROR();
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

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if ( glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE &&
        glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE &&
        glfwGetKey(window, GLFW_KEY_U) == GLFW_RELEASE &&
        glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE &&
        glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE &&
        glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE)
    {
        isRotating = false;
    }

    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && isRotating == false)
    {
        isRotating = true;

        start_time = std::chrono::system_clock::now();
        rubiks_cube.rotate_face(glm::vec3(0.0f, 1.0f, 0.0f), -90);
    }

    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && isRotating == false)
    {
        isRotating = true;

        start_time = std::chrono::system_clock::now();
        rubiks_cube.rotate_face(glm::vec3(0.0f, 1.0f, 0.0f), 90);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && isRotating == false)
    {
        isRotating = true;

        start_time = std::chrono::system_clock::now();
        rubiks_cube.rotate_face(glm::vec3(0.0f, -1.0f, 0.0f), 90);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && isRotating == false)
    {
        isRotating = true;

        start_time = std::chrono::system_clock::now();
        rubiks_cube.rotate_face(glm::vec3(0.0f, -1.0f, 0.0f), -90);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && isRotating == false)
    {
        isRotating = true;

        float z = std::round(camera.Front.z);
        float x = std::round(camera.Front.x);

        float max = std::max(std::abs(x), std::abs(z));

        glm::vec3 axis = glm::vec3(0.0f, 0.0f, 0.0f);

        if (max == std::abs(z))
        {
            axis = glm::vec3(-z, 0.0f, 0.0f);
        }
        else
        {
            axis = glm::vec3(0.0f, 0.0f, x);
        }

        start_time = std::chrono::system_clock::now();
        rubiks_cube.rotate_face(axis, 90);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && isRotating == false)
    {
        isRotating = true;

        float z = std::round(camera.Front.z);
        float x = std::round(camera.Front.x);

        float max = std::max(std::abs(x), std::abs(z));

        glm::vec3 axis = glm::vec3(0.0f, 0.0f, 0.0f);

        if (max == std::abs(z))
        {
            axis = glm::vec3(-z, 0.0f, 0.0f);
        }
        else
        {
            axis = glm::vec3(0.0f, 0.0f, x);
        }

        start_time = std::chrono::system_clock::now();
        rubiks_cube.rotate_face(axis, -90);
    }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && isRotating == false)
    {
        isRotating = true;

        float z = std::round(camera.Front.z);
        float x = std::round(camera.Front.x);

        float max = std::max(std::abs(x), std::abs(z));

        glm::vec3 axis = glm::vec3(0.0f, 0.0f, 0.0f);

        if (max == std::abs(z))
        {
            axis = glm::vec3(z, 0.0f, 0.0f);
        }
        else
        {
            axis = glm::vec3(0.0f, 0.0f, -x);
        }

        start_time = std::chrono::system_clock::now();
        rubiks_cube.rotate_face(axis, 90);
    }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && isRotating == false)
    {
        isRotating = true;

        float z = std::round(camera.Front.z);
        float x = std::round(camera.Front.x);

        float max = std::max(std::abs(x), std::abs(z));

        glm::vec3 axis = glm::vec3(0.0f, 0.0f, 0.0f);

        if (max == std::abs(z))
        {
            axis = glm::vec3(z, 0.0f, 0.0f);
        }
        else
        {
            axis = glm::vec3(0.0f, 0.0f, -x);
        }

        start_time = std::chrono::system_clock::now();
        rubiks_cube.rotate_face(axis, -90);
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && isRotating == false)
    {
        isRotating = true;

        float z = std::round(camera.Front.z);
        float x = std::round(camera.Front.x);

        float max = std::max(std::abs(x), std::abs(z));

        glm::vec3 axis = glm::vec3(0.0f, 0.0f, 0.0f);

        if (max == std::abs(x))
        {
            axis = glm::vec3(-x, 0.0f, 0.0f);
        }
        else
        {
            axis = glm::vec3(0.0f, 0.0f, -z);
        }

        start_time = std::chrono::system_clock::now();
        rubiks_cube.rotate_face(axis, 90);
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && isRotating == false)
    {
        isRotating = true;

        float z = std::round(camera.Front.z);
        float x = std::round(camera.Front.x);

        float max = std::max(std::abs(x), std::abs(z));

        glm::vec3 axis = glm::vec3(0.0f, 0.0f, 0.0f);

        if (max == std::abs(x))
        {
            axis = glm::vec3(-x, 0.0f, 0.0f);
        }
        else
        {
            axis = glm::vec3(0.0f, 0.0f, -z);
        }

        start_time = std::chrono::system_clock::now();
        rubiks_cube.rotate_face(axis, -90);
    }

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && isRotating == false)
    {
        isRotating = true;

        float z = std::round(camera.Front.z);
        float x = std::round(camera.Front.x);

        float max = std::max(std::abs(x), std::abs(z));

        glm::vec3 axis = glm::vec3(0.0f, 0.0f, 0.0f);

        if (max == std::abs(x))
        {
            axis = glm::vec3(x, 0.0f, 0.0f);
        }
        else
        {
            axis = glm::vec3(0.0f, 0.0f, z);
        }

        start_time = std::chrono::system_clock::now();
        rubiks_cube.rotate_face(axis, 90);
    }

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && isRotating == false)
    {
        isRotating = true;

        float z = std::round(camera.Front.z);
        float x = std::round(camera.Front.x);

        float max = std::max(std::abs(x), std::abs(z));

        glm::vec3 axis = glm::vec3(0.0f, 0.0f, 0.0f);

        if (max == std::abs(x))
        {
            axis = glm::vec3(x, 0.0f, 0.0f);
        }
        else
        {
            axis = glm::vec3(0.0f, 0.0f, z);
        }

        start_time = std::chrono::system_clock::now();
        rubiks_cube.rotate_face(axis, -90);
    }

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    {
        rubiks_cube.opacity = 0.5f;
        glDisable(GL_DEPTH_TEST);
    }

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        rubiks_cube.opacity = 1.0f;
        glEnable(GL_DEPTH_TEST);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        if (swapCubeTextures)
        {        
            glBindTexture(GL_TEXTURE_2D, rubiks_cube.get_next_texture_id()); CHECK_GL_ERROR();
            CubeProgram->use(); CHECK_GL_ERROR();
            CubeProgram->set_uniform_1i("tex", 0); CHECK_GL_ERROR();
        }
        swapCubeTextures = false;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
    {
        swapCubeTextures = true;
    }

    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        if (swapSkyboxTextures)
        {
            glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.get_next_texture_id()); CHECK_GL_ERROR();
            SkyboxProgram->use(); CHECK_GL_ERROR();
            SkyboxProgram->set_uniform_1i("skybox", 0); CHECK_GL_ERROR();
        }
        swapSkyboxTextures = false;
    }

    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_RELEASE)
    {
        swapSkyboxTextures = true;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        rubiks_cube.shuffle();
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        if (firstMouse)
        {
            lastX = static_cast<float>(xpos);
            lastY = static_cast<float>(ypos);
            firstMouse = false;
        }
        else
        {
            float xoffset = static_cast<float>(xpos - lastX);
            float yoffset = static_cast<float>(lastY - ypos);

            lastX = xpos;
            lastY = ypos;

            camera.ProcessMouseMovement(xoffset, yoffset, deltaTime);
        }
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        firstMouse = true;
    }

    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        camera.Reset();
    }
    
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
    {
        rubiks_cube.reset();
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}