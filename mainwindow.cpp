// Bibliotecas padrões
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <wiringPi.h>
#include <QDebug>

bool start = false;

// Pinos dos 4 leds
const int START_STOP = 29, INTRO_MARK = 28, LOCK_GROOVE = 30, FWD = 27, BWD = 26, HOME = 25, HEATER_STYLUS = 24, HEATER_LAMP = 23, VACUM_PAMP = 22, F_INI = 10, F_FIM = 11;

// Assinatura da função update
void updateStatusLabel(const bool, QLabel *);
void updateLabelButtons(const bool, QLabel *);
void updateLabel(const int , QLabel *);
void setPins(Ui::MainWindow *);

// Construtor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // Iniciamos a interface
    ui->setupUi(this);

    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(MyTimerSlot()));

    timer->start(100);

//    connect(timer, SIGNAL(timeout()), this, SLOT(MyTimerSlot()));

    // Configuramos a tela fixa 1024x600
    setFixedSize(1024, 600);

    // Setamos os pinos
    setPins(ui);
}

// Destrutor
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MyTimerSlot()
{
    if(digitalRead(F_FIM) == LOW)
    {
        start = false;
        updateStatusLabel(start, ui->func);
    }

    if (digitalRead(F_INI) == LOW)
    {
        start = false;
        updateStatusLabel(start, ui->func);
    }
}

// Função que seta os pinos dos leds e atualiza a tela com o status atual ao iniciar o programa
void setPins(Ui::MainWindow *ui)
{
    wiringPiSetup();

    pinMode(START_STOP, OUTPUT);
    pinMode(INTRO_MARK, OUTPUT);
    pinMode(LOCK_GROOVE, OUTPUT);
    pinMode(HOME, OUTPUT);
    pinMode(FWD, OUTPUT);
    pinMode(BWD, OUTPUT);
    pinMode(HEATER_LAMP, OUTPUT);
    pinMode(HEATER_STYLUS, OUTPUT);
    pinMode(VACUM_PAMP, OUTPUT);

    pinMode(F_FIM, INPUT);
    pinMode(F_INI, INPUT);


}


// Atualizamos os labels dos botões de acordo com o sinal dos pinos
void updateStatusLabel(const bool estado, QLabel *label)
{
    if(estado)
    {
        label->setText("RUNNING...");
        label->setStyleSheet("QLabel { color : green; }");
    }
    else
    {
        label->setText("STOPPED!!!");
        label->setStyleSheet("QLabel { color : red; }");
    }
}

void updateLabelButtons(const bool estado, QLabel *label)
{
    if(estado)
    {
        label->setText("ON");
        label->setStyleSheet("QLabel { color : green; }");
    }
    else
    {
        label->setText("OFF");
        label->setStyleSheet("QLabel { color : red; }");
    }
}

void updateLabel(const int PIN, QLabel *label)
{
    if(digitalRead(PIN))
    {
        label->setText("ON");
        label->setStyleSheet("QLabel { color : green; }");
    }
    else
    {
        label->setText("OFF");
        label->setStyleSheet("QLabel { color : red; }");
    }
}

void MainWindow::on_btnBWD_pressed()
{
    if (digitalRead(F_INI) == HIGH && start == false)
    {
        digitalWrite(BWD, HIGH);

        updateLabel(BWD, ui->lblBWD);
    }
}

void MainWindow::on_btnBWD_released()
{
    digitalWrite(BWD, LOW);

    updateLabel(BWD, ui->lblBWD);
}

void MainWindow::on_btnFWD_pressed()
{
    if (digitalRead(F_FIM) == HIGH && start == false)
    {
        digitalWrite(FWD, HIGH);

        updateLabel(FWD, ui->lblFWD);
    }
}

void MainWindow::on_btnFWD_released()
{
    digitalWrite(FWD, LOW);

    updateLabel(FWD, ui->lblFWD);
}

void MainWindow::on_btnSTART_pressed()
{
    if (digitalRead(F_FIM) == HIGH)
    {
        digitalWrite(START_STOP, HIGH);

        start = !start;

        updateStatusLabel(start, ui->func);
        updateLabelButtons(start, ui->lblSTAR);
    }
}

void MainWindow::on_btnSTART_released()
{
    digitalWrite(START_STOP, LOW);

    updateLabelButtons(start, ui->lblSTAR);
}

void MainWindow::on_btnSTYLUS_clicked()
{
    digitalWrite(HEATER_STYLUS, !digitalRead(HEATER_STYLUS));

    updateLabel(HEATER_STYLUS, ui->lblSTYLUS);
}

void MainWindow::on_btnLAMP_clicked()
{
    digitalWrite(HEATER_LAMP, !digitalRead(HEATER_LAMP));

    updateLabel(HEATER_LAMP, ui->lblLAMP);
}

void MainWindow::on_btnVACUM_clicked()
{
    digitalWrite(VACUM_PAMP, !digitalRead(VACUM_PAMP));

    updateLabel(VACUM_PAMP, ui->lblVACUM);
}

void MainWindow::on_btnINTRO_MARK_pressed()
{
    if (start == true)
    {
        digitalWrite(INTRO_MARK, HIGH);
    }
}

void MainWindow::on_btnINTRO_MARK_released()
{
    if (start == true)
    {
       digitalWrite(INTRO_MARK, LOW);
    }
}

void MainWindow::on_btnLOCK_pressed()
{
    if (start == true)
    {
        digitalWrite(LOCK_GROOVE, HIGH);
    }
}

void MainWindow::on_btnLOCK_released()
{
    if (start == true)
    {
        digitalWrite(LOCK_GROOVE, LOW);
    }
}
