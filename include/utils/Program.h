#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "Error.h"

class Program
{
public:
    struct Shaders
    {
        std::string vertex_shader_path;
        std::string fragment_shader_path;
    };

public:
    Program()
    {
        m_ProgramID = glCreateProgram(); CHECK_GL_ERROR();
    }

    static Program *make_program(std::string &vertex_shader_path, std::string &fragment_shader_path)
    {
        Program* program = new Program();
        Shaders shaders = program->storeShaders(vertex_shader_path, fragment_shader_path);
        GLuint vertex_shader = program->compileShader(GL_VERTEX_SHADER, shaders.vertex_shader_path);
        GLuint fragment_shader = program->compileShader(GL_FRAGMENT_SHADER, shaders.fragment_shader_path);

        glAttachShader(program->m_ProgramID, vertex_shader); CHECK_GL_ERROR();
        glAttachShader(program->m_ProgramID, fragment_shader); CHECK_GL_ERROR();
        glLinkProgram(program->m_ProgramID); CHECK_GL_ERROR(); CHECK_GL_ERROR();

        if (!program->is_ready())
        {
            std::cerr << "ERROR::PROGRAM::LINKING_FAILED" << std::endl;
            char* log = program->get_log();
            std::cerr << log << std::endl;
            delete[] log;
            delete program;
            return nullptr;
        }

        glDeleteShader(vertex_shader); CHECK_GL_ERROR();
        glDeleteShader(fragment_shader); CHECK_GL_ERROR();

        return program;
    }

    char* get_log()
    {
        int length;
        glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &length); CHECK_GL_ERROR(); 
        char* log = new char[length];
        glGetProgramInfoLog(m_ProgramID, length, &length, log); CHECK_GL_ERROR();
        return log;
    }
    
    bool is_ready()
    {
        int status;
        glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &status); CHECK_GL_ERROR();
        return status == GL_TRUE;
    }   

    void use()
    {
        glUseProgram(m_ProgramID); CHECK_GL_ERROR();
    }

    inline GLuint get_program_id() const { return m_ProgramID; }

    void delete_program()
    {
        glDeleteProgram(m_ProgramID); CHECK_GL_ERROR();
    }

    int getUniformLocation(const std::string& name)
    {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
            return m_UniformLocationCache[name];
        
        int location = glGetUniformLocation(m_ProgramID, name.c_str()); CHECK_GL_ERROR();
        if (location == -1)
            std::cerr << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

        m_UniformLocationCache[name] = location;
       
        return location;
    }

    void set_uniform_1i(const std::string& name, int value)
    {
        glUniform1i(getUniformLocation(name), value); CHECK_GL_ERROR();
    }

    void set_uniform_Mat4fv(const std::string& name, const glm::mat4& matrix, GLboolean transpose = GL_FALSE)
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, transpose, &matrix[0][0]); CHECK_GL_ERROR();
    }

private:

    Shaders storeShaders(std::string& vertex_shader_path, std::string& fragment_shader_path)
    {
        std::string vertex_shader_code;
        std::string fragment_shader_code;
        std::ifstream vertex_shader_file;
        std::ifstream fragment_shader_file;

        vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            vertex_shader_file.open(vertex_shader_path);
            fragment_shader_file.open(fragment_shader_path);

            std::stringstream vertex_shader_stream, fragment_shader_stream;

            vertex_shader_stream << vertex_shader_file.rdbuf();
            fragment_shader_stream << fragment_shader_file.rdbuf();

            vertex_shader_file.close();
            fragment_shader_file.close();

            vertex_shader_code = vertex_shader_stream.str();
            fragment_shader_code = fragment_shader_stream.str();
        }
        catch (const std::exception& e)
        {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }

        return { vertex_shader_code, fragment_shader_code };
    }

    bool is_shader_ready(GLuint shader_id)
    {
        int status;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status); CHECK_GL_ERROR();
        return status == GL_TRUE;
    }

    char* get_shader_log(GLuint shader_id)
    {
        int length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length); CHECK_GL_ERROR();
        char* log = new char[length];
        glGetShaderInfoLog(shader_id, length, &length, log); CHECK_GL_ERROR();
        return log;
    }

    GLuint compileShader(GLuint type, const std::string& source)
    {
        GLuint id = glCreateShader(type); CHECK_GL_ERROR();
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr); CHECK_GL_ERROR();
        glCompileShader(id); CHECK_GL_ERROR();

        if (!is_shader_ready(id))
        {
            std::cerr << "ERROR::SHADER::COMPILATION_FAILED" << std::endl;
            std::cerr << "Shader type: " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
            char* log = get_shader_log(id);
            std::cerr << log << std::endl;
            glDeleteShader(id); CHECK_GL_ERROR();
            delete log;
            return EXIT_FAILURE;
        }

        return id;
    }

private:
    GLuint m_ProgramID;
    std::unordered_map<std::string, int> m_UniformLocationCache;
};

static Program* CubeProgram;
static Program* SkyboxProgram;