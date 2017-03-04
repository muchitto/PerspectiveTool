#include "mainwindow.h"
#include "perspectiveeditor.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->perspectiveSelectGroup, SIGNAL(buttonClicked(int)), ui->perspectiveEditor, SLOT(perspectivePointsSelected(int)));
    connect(ui->antialiasingCheckBox, SIGNAL(clicked(bool)), ui->perspectiveEditor, SLOT(setAntialiasing(bool)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionCopy_to_clipboard_triggered() {
    QApplication::clipboard()->setImage(ui->perspectiveEditor->canvas_image, QClipboard::Clipboard);
}
