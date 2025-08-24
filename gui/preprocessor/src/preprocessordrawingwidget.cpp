#include "preprocessordrawingwidget.h"
#include <QOpenGLFunctions>
#include "ui_preprocessorwindow.h"
#include <array>

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

PreprocessorDrawingWidget::PreprocessorDrawingWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{}

void PreprocessorDrawingWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);  // Dark blue background
}

void PreprocessorDrawingWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void PreprocessorDrawingWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PreprocessorDrawingWidget::drawAxes()
{

}
