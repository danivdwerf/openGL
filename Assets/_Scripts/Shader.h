#ifndef SHADER_H
#define SHADER_H


#include <string>
#include <iostream>

#include "../includes/glad.h"
#include "./utils/File.h"

class Shader
{
    private: unsigned int id;
    public: unsigned int ID()const{return this->id;}

    public: enum AttrType
    {
        INT = (1<<0),
        BOOL = (1<<1),
        FLOAT = (1<<2)
    };

    public: Shader(const char* vertexPath, const char* fragmentPath)
    {
        std::string vertexCode = Utilities::File::getFileContent(vertexPath);
        std::string fragmentCode = Utilities::File::getFileContent(fragmentPath);
        bool valid = this->compileShaders(vertexCode.c_str(), fragmentCode.c_str());

        if(!valid)
        {
            std::cout << "Shader.h: FAILED TO CONSTRUCT" << '\n';
            delete this;
        }

        // this->setAttribute("test", 10, INT);
    }

    private: bool compileShaders(const char* vertexCode, const char* fragmentCode)
    {
        int success;
        char errormsg[512];

        unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexCode, NULL);
        glCompileShader(vertex);

        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            std::cout << "Shader.h: FAILED TO COMPILE VERTEX SHADER" << '\n';
            return false;
        }

        unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentCode, NULL);
        glCompileShader(fragment);

        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(this->id, 512, NULL, errormsg);
            std::cout << "Shader.h: FAILED TO COMPILE FRAGMENT SHADER:\n" << errormsg << '\n';
            return false;
        }

        this->id = glCreateProgram();
        glAttachShader(this->id, vertex);
        glAttachShader(this->id, fragment);
        glLinkProgram(this->id);
        glGetProgramiv(this->id, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(this->id, 512, NULL, errormsg);
            std::cout << "Shader.h: FAILED TO LINK SHADERS:\n" << errormsg << '\n';
            return false;
        }
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return true;
    }

    public: void use()
    {
        glUseProgram(this->id);
    }

    public: template<typename T>bool setAttribute(const char* attrName, T value, AttrType type)
    {
        if(type == (1<<0) || type == (1<<1))
        {
            try{glUniform1i(glGetUniformLocation(this->id, attrName), (int)value);}
            catch(std::exception e){return false;}
        }

        if(type == (1<<2))
        {
            try{glUniform1f(glGetUniformLocation(this->id, attrName), (float)value);}
            catch(std::exception e){return false;}
        }
        return true;
    }
};
#endif