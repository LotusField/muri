#ifndef PREPROCESSORDRAWINGWIDGET_H
#define PREPROCESSORDRAWINGWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QMouseEvent>
#include <QMatrix4x4>

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

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:

    void on_actionShowPreprocessor_triggered();

    void initShaders();
    void initBuffers();

    GLuint vbo;
    GLuint vao;
    GLuint shaderProgram;
    int numLineVertices;

    QPoint lastMousePosition;
    float xRot, yRot;
    float xPan, yPan;
    QMatrix4x4 projection;

    float cameraDistance;  // default distance
    float fieldOfView;    // in degrees, must match projection.perspective()
    float aspectRatio;     // updated in resizeGL

    static constexpr float minCameraDistance = 0.01f;
    static constexpr float maxCameraDistance = 10.0f;
};

#endif // PREPROCESSORDRAWINGWODGET_H
