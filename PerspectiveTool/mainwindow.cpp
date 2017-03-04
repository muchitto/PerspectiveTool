#include "mainwindow.h"
#include "perspectiveeditor.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->perspectiveSelectGroup, SIGNAL(buttonClicked(int)), ui->perspectiveEditor, SLOT(perspectivePointsSelected(int)));
    connect(ui->antialiasingCheckBox, SIGNAL(clicked(bool)), ui->perspectiveEditor, SLOT(setAntialiasing(bool)));

    connect(ui->perspectiveEditor, SIGNAL(setLines(int)), ui->lineAmountSlider, SLOT(setValue(int)));
    connect(ui->perspectiveEditor, SIGNAL(setOpacity(int)), ui->opacitySlider, SLOT(setValue(int)));

    connect(ui->perspectiveEditor, SIGNAL(perspectivePointActivationState(bool)), ui->lineAmountSlider, SLOT(setEnabled(bool)));
    connect(ui->perspectiveEditor, SIGNAL(perspectivePointActivationState(bool)), ui->opacitySlider, SLOT(setEnabled(bool)));

    connect(ui->lineAmountSlider, SIGNAL(valueChanged(int)), ui->perspectiveEditor, SLOT(setCurrentLines(int)));
    connect(ui->opacitySlider, SIGNAL(valueChanged(int)), ui->perspectiveEditor, SLOT(setCurrentOpacity(int)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionCopy_to_clipboard_triggered() {
    QApplication::clipboard()->setImage(ui->perspectiveEditor->canvas_image, QClipboard::Clipboard);
}
