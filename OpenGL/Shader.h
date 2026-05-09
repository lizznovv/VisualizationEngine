#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	GLuint Program;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {

        //СЧИТЫВАНИЕ
        // вершинный шейдер - он просто получает вершины из vbo
        std::string vertexShaderSourceObj = TextFromFile(vertexPath);
        const char* vertexShaderSource = vertexShaderSourceObj.c_str();

        //фрагментный шейдер - вычисляет цвета пикселей
        std::string fragmentShaderSourceObj = TextFromFile(fragmentPath);
        const char* fragmentShaderSource = fragmentShaderSourceObj.c_str();

        //СБОРКА
        //создаем объект вершинного шейдера с типом gl unsigned int
        GLuint vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        //ошибка если шейдер не собрался
        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        //сборка фрагментного шейдера
        GLuint fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        //СОЗДАНИЕ ШЕЙДЕРНОЙ ПРОГРАММЫ
        this->Program = glCreateProgram();
        //присоединяем к программе шейдеры
        glAttachShader(this->Program, vertexShader);
        glAttachShader(this->Program, fragmentShader);
        glLinkProgram(this->Program);

        glGetProgramiv(this->Program, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
            std::cout << "ERROR::PROGRAM::LINKING::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        //удаляем шейдеры
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

	}
    void Use() { glUseProgram(this->Program); }
private:

    std::string TextFromFile(const GLchar* path)
    {
        std::ifstream file(path);
        std::string line, result = "";
        if (file.is_open()) {
            while (std::getline(file, line)) {
                result += line;
                result += '\n';
            }
        }
        return result;
    }
};

