#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QClipboard>

#include "sizedialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionCopy_to_clipboard_triggered();

    void on_actionCopy_to_clipboard_with_size_triggered();
private:
    Ui::MainWindow *ui;

public slots:
};

#endif // MAINWINDOW_H
