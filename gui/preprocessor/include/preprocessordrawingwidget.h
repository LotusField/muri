#ifndef PREPROCESSORDRAWINGWIDGET_H
#define PREPROCESSORDRAWINGWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class PreprocessorDrawingWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:

    explicit PreprocessorDrawingWidget(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:

    void on_actionShowPreprocessor_triggered();
    void drawAxes();
};

#endif // PREPROCESSORDRAWINGWODGET_H
