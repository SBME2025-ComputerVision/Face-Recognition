#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qpushbutton.h"
#include <QMainWindow>
#include "Helpers/gui_helper.h"
#include "Views/livecamerawidget.h"
#include "config.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_liveCameraBtn_clicked();

    void on_faceRecognitionBtn_clicked();

    void on_dataAndModelBtn_clicked();

private:

    Ui::MainWindow *ui;
    int index;
    QList<QPushButton*> menuBtns;
    QWidget* liveCameraWidget;
};
#endif // MAINWINDOW_H
