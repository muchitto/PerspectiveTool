#include "mainwindow.h"
#include "perspectiveeditor.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->perspectiveSelectGroup, SIGNAL(buttonClicked(int)), ui->perspectiveEditor, SLOT(perspectivePointsSelected(int)));

    ui->perspectiveEditor->setFocus();
}

MainWindow::~MainWindow() {
    delete ui;
}
