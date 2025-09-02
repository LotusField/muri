#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QLabel>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    background.load("../../pictures/bg.jpg");

    // Connect the ui exit button to the exit command (close)
    connect(ui->actionExit, &QAction::triggered, this, &QMainWindow::close);

    connect(ui->actionShow, &QAction::triggered,
            this, &MainWindow::on_actionShow_triggered);

    QLabel *label = new QLabel(this);
    label->setTextFormat(Qt::RichText);
    label->setTextInteractionFlags(Qt::TextBrowserInteraction); // redirect to url on click
    label->setOpenExternalLinks(true);
    label->setText(R"(
        <p style='font-size:13px; margin: 0;'>
            <b>Simulation programm for 3D heat and vapor static diffusion in orthogonal construction details in building science<b><br>
            <a href='https://github.com/LotusField/muri'>Open GitHub Repository in browser</a>
        </p>
    )");

    // Create a layout and set it on the central widget
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label, 0, Qt::AlignTop | Qt::AlignLeft); // text and position

    layout->setContentsMargins(10, 10, 0, 0); // Margin
    layout->setSpacing(5);

    ui->centralwidget->setLayout(layout);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);  // Call implementation in mother class

    if (!background.isNull()) {
        QPainter painter(this);

        QPixmap scaled = background.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

        int x = (width() - scaled.width()) / 2;
        int y = (height() - scaled.height()) / 2;

        painter.drawPixmap(x, y, scaled);
    }
}

void MainWindow::on_actionShow_triggered()
{
    if (!preprocessorWindow) {
        preprocessorWindow = new PreprocessorWindow();
        preprocessorWindow->setAttribute(Qt::WA_DeleteOnClose); // when preprocessorWindow is closed, delete the widget from the heap memory

        connect(preprocessorWindow, &QObject::destroyed, this, [=]() {
            preprocessorWindow = nullptr;
        }); // handles end life cycle and reset it to nullptr to prevent accessing an already deleted preprocessorWindow
    }
    preprocessorWindow->show();
    preprocessorWindow->raise();  // Bring to front
    preprocessorWindow->activateWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}
