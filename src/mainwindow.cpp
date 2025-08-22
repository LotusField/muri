#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    background.load("../../pictures/bg.jpg");

    // Connect the ui exit button to the exit command (close)
    connect(ui->actionExit, &QAction::triggered, this, &QMainWindow::close);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);  // Call base implementation

    if (!background.isNull()) {
        QPainter painter(this);

        QPixmap scaled = background.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

        int x = (width() - scaled.width()) / 2;
        int y = (height() - scaled.height()) / 2;

        painter.drawPixmap(x, y, scaled);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
