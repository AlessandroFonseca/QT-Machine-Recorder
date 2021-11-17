// Bibliotecas padrões
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <wiringPi.h>
// Biblioteca referentes as funções de GPIOs do raspberry


// Pinos dos 4 leds
const int LED1 = 29, LED2 = 28, LED3 = 25, LED4 = 27;

// Assinatura da função update
void updateStatusLabel(const int, QLabel *);

// Função que seta os pinos dos leds e atualiza a tela com o status atual ao iniciar o programa
void setPins(Ui::MainWindow *ui)
{
    wiringPiSetup();

    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);

    updateStatusLabel(LED1, ui->lblLED1);
    updateStatusLabel(LED2, ui->lblLED2);
    updateStatusLabel(LED3, ui->lblLED3);
    updateStatusLabel(LED4, ui->lblLED4);
}

// Construtor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // Iniciamos a interface
    ui->setupUi(this);

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

// Atualizamos os labels dos botões de acordo com o sinal dos pinos
void updateStatusLabel(const int LED, QLabel *label)
{
    if(digitalRead(LED) == HIGH)
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

// Evento do botão 1
void MainWindow::on_btnLED1_clicked()
{
    // Mudamos o estado do pino
    digitalWrite(LED1, !digitalRead(LED1));

    // Atualizamos a label
    updateStatusLabel(LED1, ui->lblLED1);
}

// Evento do botão 2
void MainWindow::on_btnLED2_clicked()
{
    // Mudamos o estado do pino
    digitalWrite(LED2, !digitalRead(LED2));

    // Atualizamos a label
    updateStatusLabel(LED2, ui->lblLED2);
}

// Evento do botão 3
void MainWindow::on_btnLED3_clicked()
{
    // Mudamos o estado do pino
    digitalWrite(LED3, !digitalRead(LED3));

    // Atualizamos a label
    updateStatusLabel(LED3, ui->lblLED3);
}

// Evento do botão 4
void MainWindow::on_btnLED4_clicked()
{
    // Mudamos o estado do pino
    digitalWrite(LED4, !digitalRead(LED4));

    // Atualizamos a label
    updateStatusLabel(LED4, ui->lblLED4);
}



void MainWindow::on_lblLED2_linkActivated(const QString &link)
{

}
