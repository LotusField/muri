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
    : QOpenGLWidget(parent), xRot(0), yRot(0), xPan(0), yPan(0), cameraDistance(5.0f), fieldOfView(45.0f), aspectRatio(1.0f)
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
    glEnable(GL_DEPTH_TEST);

    initShaders();
    initBuffers();

    initializeOpenGLFunctions();
}

void PreprocessorDrawingWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    aspectRatio = float(w) / float(h);
    projection.setToIdentity();
    projection.perspective(fieldOfView, aspectRatio, 0.1f, 100.0f);
}

void PreprocessorDrawingWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // bind shaders

    QMatrix4x4 modelView;
    modelView.translate(xPan, yPan, -cameraDistance);
    modelView.rotate(xRot, 1.0f, 0.0f, 0.0f);
    modelView.rotate(yRot, 0.0f, 1.0f, 0.0f);

    QMatrix4x4 mvp = projection * modelView;

    glUseProgram(shaderProgram);

    // Pass the MVP matrix to shader
    GLint mvpLoc = glGetUniformLocation(shaderProgram, "mvp");
    if (mvpLoc == -1) {
        qWarning("Vertex shader error: paintGL() could not find the mvp 4x4 QMatrix");
    }
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, mvp.constData());

    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, numLineVertices);
    glBindVertexArray(0);
    glUseProgram(0);
}

void PreprocessorDrawingWidget::initShaders()
{
    const char *vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec4 aColor;

    uniform mat4 mvp;

    out vec4 vertexColor;

    void main() {
        gl_Position = mvp * vec4(aPos, 1.0);
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

void PreprocessorDrawingWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastMousePosition = event->pos();
    }
}

void PreprocessorDrawingWidget::mouseMoveEvent(QMouseEvent *event){

    QPoint delta = event->pos() - lastMousePosition;

    if (event->buttons() & Qt::LeftButton) {

        float sensitivity = 0.5f;

        // Update rotation angles
        xRot += sensitivity * delta.y();
        yRot += sensitivity * delta.x();

        // Keep angles within 0-360
        xRot = std::fmod(xRot, 360.0f);
        yRot = std::fmod(yRot, 360.0f);
    }
    else if (event->buttons() & Qt::RightButton) {

        float tanFov = std::tan(qDegreesToRadians(fieldOfView / 2.0f));
        // Multiply by 2 to get full view height from half-angle tangent
        float viewHeight = 2.0f * cameraDistance * tanFov;
        float viewWidth = viewHeight * aspectRatio;

        float dx = delta.x() * (viewWidth / float(width()));
        float dy = delta.y() * (viewHeight / float(height()));

        xPan += dx;
        yPan -= dy;  // invert Y to match screen direction
    }

    lastMousePosition = event->pos();

    update();  // Request repaint
}

void PreprocessorDrawingWidget::wheelEvent(QWheelEvent *event)
{
    // Zoom speed factor — tweak this for sensitivity
    const float zoomSpeed = 0.5f;

    // event->angleDelta().y() gives wheel delta in "eighths of a degree" units
    // Positive means wheel scrolled up (zoom in), negative is down (zoom out)
    float delta = event->angleDelta().y() / 120.0f;  // 120 is standard for one notch

    // Update cameraDistance, but clamp it to avoid going too close or too far
    cameraDistance -= delta * zoomSpeed;
    cameraDistance = std::clamp(cameraDistance, 0.5f, 50.0f);

    update();  // Request redraw
}
