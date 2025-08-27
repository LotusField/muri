#ifndef PREPROCESSORDRAWINGWIDGET_H
#define PREPROCESSORDRAWINGWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>

class PreprocessorDrawingWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:

    explicit PreprocessorDrawingWidget(QWidget *parent = nullptr);

    ~PreprocessorDrawingWidget();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:

    void on_actionShowPreprocessor_triggered();
    void drawAxes();

    void initShaders();
    void initBuffers();

    GLuint vbo;
    GLuint vao;
    GLuint shaderProgram;
    int numLineVertices;
};

#endif // PREPROCESSORDRAWINGWODGET_H
