#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGLFrame;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *evt);

private:
    Ui::MainWindow *ui;
    QGLFrame *GLFrame;
};

#endif // MAINWINDOW_H
