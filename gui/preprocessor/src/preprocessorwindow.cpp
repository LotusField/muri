#include "preprocessorwindow.h"
#include <QOpenGLFunctions>

PreprocessorWindow::PreprocessorWindow(QWidget *parent)
    : QOpenGLWidget(parent)
{}

void PreprocessorWindow::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);  // Dark blue background
}

void PreprocessorWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void PreprocessorWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
