#ifndef PREPROCESSORWINDOW_H
#define PREPROCESSORWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class PreprocessorWindow;
}
QT_END_NAMESPACE

class PreprocessorWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit PreprocessorWindow(QWidget *parent = nullptr);
    ~PreprocessorWindow();

private:

    Ui::PreprocessorWindow *ui;
};

#endif // PREPROCESSORWINDOW_H
