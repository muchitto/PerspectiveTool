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
    connect(ui->perspectiveEditor, SIGNAL(setCenterRemoval(int)), ui->centerRemovalSlider, SLOT(setValue(int)));

    connect(ui->perspectiveEditor, SIGNAL(perspectivePointActivationState(bool)), ui->lineAmountSlider, SLOT(setEnabled(bool)));
    connect(ui->perspectiveEditor, SIGNAL(perspectivePointActivationState(bool)), ui->opacitySlider, SLOT(setEnabled(bool)));
    connect(ui->perspectiveEditor, SIGNAL(perspectivePointActivationState(bool)), ui->centerRemovalSlider, SLOT(setEnabled(bool)));

    connect(ui->lineAmountSlider, SIGNAL(valueChanged(int)), ui->perspectiveEditor, SLOT(setCurrentLines(int)));
    connect(ui->opacitySlider, SIGNAL(valueChanged(int)), ui->perspectiveEditor, SLOT(setCurrentOpacity(int)));
    connect(ui->centerRemovalSlider, SIGNAL(valueChanged(int)), ui->perspectiveEditor, SLOT(setCurrentCenterRemoval(int)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionCopy_to_clipboard_triggered() {
   // ui->perspectiveEditor->renderImage();

    QImage image = ui->perspectiveEditor->renderImage(ui->perspectiveEditor->canvas.width(), ui->perspectiveEditor->canvas.height());
    QApplication::clipboard()->setImage(image, QClipboard::Clipboard);
}

void MainWindow::on_actionCopy_to_clipboard_with_size_triggered() {
    SizeDialog dialog;

    dialog.exec();

    QImage image = ui->perspectiveEditor->renderImage(dialog.getCanvasSize().width(), dialog.getCanvasSize().height());
    QApplication::clipboard()->setImage(image, QClipboard::Clipboard);
}
