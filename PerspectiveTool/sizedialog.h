#ifndef SIZEDIALOG_H
#define SIZEDIALOG_H

#include <QDialog>
#include <QRectF>

namespace Ui {
class SizeDialog;
}

class SizeDialog : public QDialog
{
    Q_OBJECT

    QRectF copy_canvas_size;
public:
    explicit SizeDialog(QWidget *parent = 0);
    ~SizeDialog();

    QRectF getCanvasSize();
public slots:
    void setCopyWidth(QString width);
    void setCopyHeight(QString height);

private:
    Ui::SizeDialog *ui;
};

#endif // SIZEDIALOG_H
