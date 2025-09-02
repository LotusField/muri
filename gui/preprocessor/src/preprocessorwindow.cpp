#include "preprocessorwindow.h"
#include "preprocessordrawingwidget.h"
#include "ui_preprocessorwindow.h"

PreprocessorWindow::PreprocessorWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PreprocessorWindow)
{
    ui->setupUi(this);
}

PreprocessorWindow::~PreprocessorWindow()
{
    delete ui;
}
