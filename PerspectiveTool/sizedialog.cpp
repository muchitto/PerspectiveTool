#include "sizedialog.h"
#include "ui_sizedialog.h"

SizeDialog::SizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SizeDialog)
{
    ui->setupUi(this);

    copy_canvas_size.setWidth(ui->widthSize->text().toInt());
    copy_canvas_size.setHeight(ui->heightSize->text().toInt());

    connect(ui->widthSize, SIGNAL(textChanged(QString)), this, SLOT(setCopyWidth(QString)));
    connect(ui->heightSize, SIGNAL(textChanged(QString)), this, SLOT(setCopyHeight(QString)));
}

SizeDialog::~SizeDialog() {
    delete ui;
}

QRectF SizeDialog::getCanvasSize() {
    return QRectF(0, 0, copy_canvas_size.width(), copy_canvas_size.height());
}

void SizeDialog::setCopyWidth(QString width) {
    copy_canvas_size.setWidth(width.toInt());
}

void SizeDialog::setCopyHeight(QString height) {
    copy_canvas_size.setHeight(height.toInt());
}
