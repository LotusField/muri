#include "preprocessordrawingwidget.h"
#include <QOpenGLFunctions_3_3_Core>
#include "ui_preprocessorwindow.h"
#include <array>
#include <iostream>

/*
 * 📦 Optional Enhancements
Feature                     |How
----------------------------|-------------------------------------------------------
Load shaders from files     |Read them from disk, compile in initShaders()
Shader abstraction          |Create a Shader class (e.g., for easier management)
VBO/VAO abstraction         |Use wrapper classes or RAII types
Add uniform support         |Store model/view/projection matrices
Add drawTriangle()          |Encapsulate the drawing logic if you plan to reuse it*/


/// Tell where the x,y,z are
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

/// Tell where r,g,b,a are
//glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), offsetof(Vertex, r));

PreprocessorDrawingWidget::PreprocessorDrawingWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{}

PreprocessorDrawingWidget::~PreprocessorDrawingWidget()
{
    makeCurrent();
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shaderProgram);
    doneCurrent();
}

void PreprocessorDrawingWidget::initializeGL()
{
    // create, link, and compile shaders (only called when creating the widget)
    // set shaders here
    // look at this for initializeGL https://www.khronos.org/opengl/wiki/Shader_Compilation

    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);

    initShaders();
    initBuffers();

    initializeOpenGLFunctions();
}

void PreprocessorDrawingWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void PreprocessorDrawingWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // bind shaders
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, numLineVertices);
    glBindVertexArray(0);
    glUseProgram(0);
}

void PreprocessorDrawingWidget::drawAxes()
{

}

void PreprocessorDrawingWidget::initShaders()
{
    const char *vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec4 aColor;

    out vec4 vertexColor;

    void main() {
        gl_Position = vec4(aPos, 1.0);
        vertexColor = aColor;
    }
)";

    const char *fragmentShaderSource = R"(
    #version 330 core
    in vec4 vertexColor;
    out vec4 FragColor;

    void main() {
        FragColor = vertexColor;
    }
)";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    char log[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, log);
        qWarning("Vertex shader error:\n%s", log);
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, log);
        qWarning("Fragment shader error:\n%s", log);
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, log);
        qWarning("Shader link error:\n%s", log);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void PreprocessorDrawingWidget::initBuffers()
{
    struct Vertex {
        float x, y, z;
        uint8_t r, g, b, a;
    };

    Vertex vertices[] = {
        { 0.0f, 0.0f, 0.0f, 255, 0,     0,   255 },
        { 1.0f, 0.0f, 0.0f, 255, 0,     0,   255 },
        { 0.0f, 0.0f, 0.0f, 0,   255,   0,  255 },
        { 0.0f, 1.0f, 0.0f, 0,   255,   0,  255 },
        { 0.0f, 0.0f, 0.0f, 0,   0,   255,  255 },
        { 0.0f, 0.0f, 1.0f, 0,   0,   255,  255 },
    };

    /* add grid
    for(unsigned int idx = 0; idx <= 10; ++idx)
    {
        for(unsigned int idy = 0; idy <= 10; idy+=10)
        {
            vertices[1].x = 1;
            vertices[1].y = 1;
        }
    }*/

    const unsigned int numPosParam(3);
    const unsigned int numColorParam(4);

    numLineVertices = sizeof(vertices) / sizeof(vertices[0]);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, numPosParam, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, x)));

    // color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, numColorParam, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, r)));

    glBindVertexArray(0);
}
