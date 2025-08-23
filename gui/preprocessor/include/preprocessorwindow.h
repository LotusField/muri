#ifndef PREPROCESSORWINDOW_H
#define PREPROCESSORWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class PreprocessorWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:

    PreprocessorWindow(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:

    void on_actionShowPreprocessor_triggered();
};

#endif // PREPROCESSORWINDOW_H
