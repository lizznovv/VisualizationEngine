
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL.h>
#include "CameraClass.h"
#include "Shader.h"
#include "Lamprey.h"
#include "CPG.h"


Camera* camera = new Camera();

bool keys[1024];

GLfloat deltaTime = 0.0f;	// Время, прошедшее между последним и текущим кадром
GLfloat lastFrame = 0.0f;  	// Время вывода последнего кадра

GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);    

    if (action == GLFW_PRESS)
        keys[key] = true;
    else if (action == GLFW_RELEASE)
        keys[key] = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera->ProcessMouseScroll(yoffset);
}

void do_movement()
{
    // Camera controls
  GLfloat cameraSpeed = 5.0f * deltaTime;
    if (keys[GLFW_KEY_W])
        camera->ProcessKeyboard(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S])
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A])
        camera->ProcessKeyboard(LEFT, deltaTime);
    if (keys[GLFW_KEY_D])
        camera->ProcessKeyboard(RIGHT, deltaTime);
    if (keys[GLFW_KEY_R])
        camera->ProcessKeyboard(UP, deltaTime);
    if (keys[GLFW_KEY_F])
        camera->ProcessKeyboard(DOWN, deltaTime);
}

int main() {

    Lamprey lamprey(10);
    CPG cpg(10);
    
    //initialize GLFW
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
	    std::cout << "Failed to create GLFW window" << std::endl;
	    glfwTerminate();
	    return -1;
    }

    //create context
    glfwMakeContextCurrent(window);
    //захват мыши
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   
    //Соединяем GLAD и GLFW, чтобы GLAD смог получить адреса функций OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to init GLAD\n";
        return -1;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    Shader* shader = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    Shader* light_shader = new Shader("shaders/vertex_light.glsl", "shaders/fragment_light.glsl");


    int width, height;
    //спрашиваем у GLFW размеры окна
    glfwGetFramebufferSize(window, &width, &height);
    //сообщаем OpenGL об этом размере
    glViewport(0, 0, width, height);
     //передаем ф-ю обратного вызова в glfw
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);


    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    //индексы
    GLuint indices[] = {  // начинаем с 0
        0, 1, 3,  
        1, 2, 3
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);

    GLuint EBO;
    glGenBuffers(1, &EBO);


    //создаем vao
    GLuint VAO;
    glGenVertexArrays(1, &VAO);

    //привязываем Vao
    glBindVertexArray(VAO);

    // Копируем наши вершины в буфер для OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Копируем наши индексы в буфер для OpenGL
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    

    //ТЕКСТУРЫ
    //создаем объект текстуры
    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    //загружаем картинку
    int width2, height2;
    unsigned char* image = SOIL_load_image("C:\\Users\\lizan\\C++\\repos\\OpenGL\\OpenGL\\textures\\images.jpg", &width2, &height2, 0, SOIL_LOAD_RGB);
    if (!image)
        std::cout << "Failed to load texture\n";

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //генерируем текстуру
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Устанавливаем указатели на вершинные атрибуты 
    // Атрибут с координатами
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    //  Атрибут с текстурой
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //Отвязываем VAO
    glBindVertexArray(0);

    //освобождение памяти и отвязка текстур
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
   
    //включаем проверку глубины
    glEnable(GL_DEPTH_TEST);

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    //считываем из шейдера объекта
    GLint modelLoc = glGetUniformLocation(shader->Program, "model");
    GLint viewLoc = glGetUniformLocation(shader->Program, "view");
    GLint projectionLoc = glGetUniformLocation(shader->Program, "projection");
    GLint objectColorLoc = glGetUniformLocation(shader->Program, "objectColor");
    GLint lightColorLoc = glGetUniformLocation(shader->Program, "lightColor");

    //считываем из шейдера освещения
    GLint lightModelLoc = glGetUniformLocation(light_shader->Program, "model");
    GLint lightViewLoc = glGetUniformLocation(light_shader->Program, "view");
    GLint lightProjLoc = glGetUniformLocation(light_shader->Program, "projection");


    //Создаем новый VAO для освещения 
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // Так как VBO объекта-контейнера уже содержит все необходимые данные, то нам нужно только связать с ним новый VAO 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Настраиваем атрибуты (нашей лампе понадобятся только координаты вершин)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

  //до тех пор пока не скажем GLFW остановиться
    while (!glfwWindowShouldClose(window)) {
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //время, затраченное на визуализацию последнего выведенного кадра
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glm::mat4 trans;        //создаем матрицу трансформации
        glm::mat4 view;        //матрица вида
        view = camera->GetViewMatrix();
        glm::mat4 projection;        //матрица перспективной проекции
        projection = glm::perspective(camera->GetFov(), (float)width / (float)height, 0.1f, 100.0f);

        // Активируем шейдерную программу объекта
        shader->Use();

        glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
        glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

        //передаем матрицы в шейдер
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        //// Обновляем цвет формы
        //GLfloat timeValue = glfwGetTime();
        //GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
        //GLint vertexColorLocation = glGetUniformLocation(shader->Program, "ourColor");
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);


        float time = glfwGetTime();

        //вызываем апдейт и отрисовку сегментов
        cpg.step(deltaTime);
        lamprey.angles = cpg.getAngles();
        lamprey.drawSegments(modelLoc);

        // Активируем шейдерную программу освещения
        light_shader->Use();
        
        // создаем матрицу модели для лампы
        glm::mat4 lightModel;
        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

        lightModel = glm::mat4();
        lightModel = glm::translate(lightModel, lightPos);
        lightModel = glm::scale(lightModel, glm::vec3(0.2f));

        glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, glm::value_ptr(lightModel));
        glUniformMatrix4fv(lightViewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(lightProjLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        ////10 одинаковых кубов с разными мировыми координатами
        //for (GLuint i = 0; i < 10; i++)
        //{
        //    //матрица модели - преобразовываем в мировые координаты
        //    glm::mat4 model;
        //    model = glm::translate(model, cubePositions[i]);
        //    GLfloat angle = (GLfloat)glfwGetTime() * 50.0f;
        //    model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
        //    //передаем матрицу модели в шейдер
        //    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        //   glDrawArrays(GL_TRIANGLES, 0, 36);
        //}
        //lPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        glBindVertexArray(0);
        
        // Проверяем события и вызываем функции обратного вызова.
        glfwPollEvents();
        do_movement();
        glfwSwapBuffers(window);
    }

    //очистим выделенные ресурсы
    glfwTerminate();
    delete camera;
    delete shader;
    delete light_shader;

    return 0;
}

