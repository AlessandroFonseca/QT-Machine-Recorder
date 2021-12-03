#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

      namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTimer *timer;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void MyTimerSlot();

    void on_btnBWD_pressed();

    void on_btnBWD_released();

    void on_btnFWD_pressed();

    void on_btnFWD_released();

    void on_btnSTART_pressed();

    void on_btnSTART_released();

    void on_btnSTYLUS_clicked();

    void on_btnLAMP_clicked();

    void on_btnVACUM_clicked();

    void on_btnINTRO_MARK_pressed();

    void on_btnINTRO_MARK_released();

    void on_btnLOCK_pressed();

    void on_btnLOCK_released();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
