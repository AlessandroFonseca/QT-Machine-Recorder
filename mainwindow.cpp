// Bibliotecas padrões
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <wiringPi.h>

//bool start = false, sty = false, heat = false, vp = false;

// definicao dos pinos
const int START_STOP = 29, INTRO_MARK = 28, LOCK_GROOVE = 30, FWD = 27, BWD = 26, HOME = 25,
          HEATER_STYLUS = 24, HEATER_LAMP = 23, VACUM_PUMP = 22, F_INI = 10, F_FIM = 11;

// Assinatura das funcoes
void updateStatusLabel(const bool, QLabel *);
void updateLabelButtons(const bool, QLabel *);
void updateLabel(const int , QLabel *);
void setPins(Ui::MainWindow *);

// Construtor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // Inicializacao da interface
    ui->setupUi(this);

    // inicializacao de objeto timer
    timer = new QTimer(this);

    // conexao da classe Qtimer para acionar a funcao MyTimerSlot()
    connect(timer, SIGNAL(timeout()), this, SLOT(MyTimerSlot()));

    // inicia timer com 100 ms
    timer->start(100);

    // Configuramos a tela fixa 1024x600
    setFixedSize(1024, 600);

    // Setamos os pinos
    setPins(ui);

    InitLabels();
}

// Destrutor
MainWindow::~MainWindow()
{
    delete ui;
}

// funcao para leitura dos inputs... apos o timer contar o tempo programado
void MainWindow::MyTimerSlot()
{
    if(digitalRead(F_FIM) == HIGH)
    {
        //start = false;
        controle.set_start(false);
        updateStatusLabel(/*start*/controle.get_start(), ui->func);
        updateLabelButtons(/*start*/controle.get_start(), ui->lblSTAR);
    }

    if (digitalRead(F_INI) == HIGH)
    {
        //start = false;
        controle.set_start(false);
        updateStatusLabel(/*start*/controle.get_start(), ui->func);
    }
}

// Função que seta os pinos e atualiza a tela com o status atual ao iniciar o programa
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
    pinMode(VACUM_PUMP, OUTPUT);

    pinMode(F_FIM, INPUT);
    pinMode(F_INI, INPUT);

}

// funcao inicializa os estados dos labels
void MainWindow::InitLabels()
{
    updateLabel(BWD, ui->lblBWD);
    updateLabel(FWD, ui->lblFWD);
    updateStatusLabel(controle.get_start(), ui->func);
    updateLabelButtons(controle.get_start(), ui->lblSTAR);
    updateLabelButtons(controle.get_vp(), ui->lblSTYLUS);
    updateLabelButtons(controle.get_vp(), ui->lblLAMP);
    updateLabelButtons(controle.get_vp(), ui->lblVACUM);
}

// atualiza labels em relacao a estado e coloca como RUNNING... ou STOPPED!!!
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

// atualiza labels em relacao a estado e coloca como ON ou OFF
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

// atualiza labels em relacao a saida e coloca como ON ou OFF
void updateLabel(const int PIN, QLabel *label)
{
    if (PIN == BWD) {
        label->setText("BACKWARD");
    }
    else {
        label->setText("FORWARD");
    }

    if(digitalRead(PIN))
    {
        //label->setText("");
        label->setStyleSheet("QLabel { color : blue; }");
    }
    else
    {
        //label->setText("OFF");
        label->setStyleSheet("QLabel { color : grey; }");
    }
}

//funcoes dos botoes
void MainWindow::on_btnBWD_pressed()
{
    if (digitalRead(F_INI) == LOW && /*start*/controle.get_start() == false)
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
    if (digitalRead(F_FIM) == LOW && /*start*/controle.get_start() == false)
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
    if (digitalRead(F_FIM) == LOW)
    {
        digitalWrite(START_STOP, HIGH);

        //start = !start;
        controle.toggle_start();

        updateStatusLabel(/*start*/controle.get_start(), ui->func);
        updateLabelButtons(/*start*/controle.get_start(), ui->lblSTAR);
    }
}

void MainWindow::on_btnSTART_released()
{
    digitalWrite(START_STOP, LOW);

    updateLabelButtons(/*start*/controle.get_start(), ui->lblSTAR);
}

void MainWindow::on_btnINTRO_MARK_pressed()
{
    if (/*start*/controle.get_start() == true)
    {
        digitalWrite(INTRO_MARK, HIGH);
    }
}

void MainWindow::on_btnINTRO_MARK_released()
{
    if (/*start*/controle.get_start() == true)
    {
       digitalWrite(INTRO_MARK, LOW);
    }
}

void MainWindow::on_btnLOCK_pressed()
{
    if (/*start*/controle.get_start() == true)
    {
        digitalWrite(LOCK_GROOVE, HIGH);
    }
}

void MainWindow::on_btnLOCK_released()
{
    if (/*start*/controle.get_start() == true)
    {
        digitalWrite(LOCK_GROOVE, LOW);
    }
}

void MainWindow::on_btnHOME_pressed()
{
    if (/*start*/controle.get_start() == false && digitalRead(F_INI) == LOW)
    {
       digitalWrite(HOME, HIGH);
    }
}

void MainWindow::on_btnHOME_released()
{
    digitalWrite(HOME, LOW);
}

void MainWindow::on_btnSTYLUS_pressed()
{
    digitalWrite(HEATER_STYLUS, HIGH);

    updateLabelButtons(/*sty*/controle.get_sty(), ui->lblSTYLUS);
}

void MainWindow::on_btnSTYLUS_released()
{
    digitalWrite(HEATER_STYLUS, LOW);
    //sty = !sty;
    controle.toggle_sty();
}

void MainWindow::on_btnLAMP_pressed()
{
    digitalWrite(HEATER_LAMP, HIGH);

    updateLabelButtons(/*heat*/controle.get_heat(), ui->lblLAMP);
}

void MainWindow::on_btnLAMP_released()
{
    digitalWrite(HEATER_LAMP, LOW);
    //heat = !heat;
    controle.toggle_heat();
}

void MainWindow::on_btnVACUM_pressed()
{
    digitalWrite(VACUM_PUMP, HIGH);

    updateLabelButtons(/*vp*/controle.get_vp(), ui->lblVACUM);
}

void MainWindow::on_btnVACUM_released()
{
    digitalWrite(VACUM_PUMP, LOW);
    //vp = !vp;
    controle.toggle_vp();
}
