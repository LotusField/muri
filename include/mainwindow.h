#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "preprocessorwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *event);

private slots:

    void on_actionShow_triggered();

private:

    Ui::MainWindow *ui;
    QPixmap background;
    PreprocessorWindow *preprocessorWindow = nullptr;
};
#endif // MAINWINDOW_H
