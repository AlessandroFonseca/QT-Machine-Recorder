#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "vars.h"

      namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    // declaracao de objeto da classe Qtimer
    QTimer *timer;

    // declaracao de objeto da classe Vars
    Vars controle;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void MyTimerSlot();

    void InitLabels();

    void on_btnBWD_pressed();

    void on_btnBWD_released();

    void on_btnFWD_pressed();

    void on_btnFWD_released();

    void on_btnSTART_pressed();
    
    void on_btnSTART_released();

    void on_btnINTRO_MARK_pressed();

    void on_btnINTRO_MARK_released();

    void on_btnLOCK_pressed();

    void on_btnLOCK_released();

    void on_btnHOME_pressed();

    void on_btnHOME_released();

    void on_btnSTYLUS_pressed();

    void on_btnSTYLUS_released();

    void on_btnLAMP_pressed();

    void on_btnLAMP_released();

    void on_btnVACUM_pressed();

    void on_btnVACUM_released();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
