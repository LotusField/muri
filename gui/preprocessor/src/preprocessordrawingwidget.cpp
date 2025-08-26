#include "preprocessordrawingwidget.h"
#include <QOpenGLFunctions>
#include "ui_preprocessorwindow.h"
#include <array>

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0"; // will be returned by the gpu as a glprogram

PreprocessorDrawingWidget::PreprocessorDrawingWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{}

void PreprocessorDrawingWidget::initializeGL()
{
    // create, link, and compile shaders (only called when creating the widget)
    // set shaders here
    // look at this for initializeGL https://www.khronos.org/opengl/wiki/Shader_Compilation

    //VBO
    //glGenBuffers
    //glBindBuffer
    //glBufferData

    //glmapbuffer to modify an existing buffer (returns the buffer adress)

    /// Tell where the x,y,z are
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    /// Tell where r,g,b,a are
    //glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), offsetof(Vertex, r));

    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);  // Dark blue background
}

void PreprocessorDrawingWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void PreprocessorDrawingWidget::paintGL()
{
    // bind shaders
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PreprocessorDrawingWidget::drawAxes()
{

}
