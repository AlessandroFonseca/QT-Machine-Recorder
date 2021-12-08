#ifndef VARS_H
#define VARS_H

// definicao da classe
class Vars
{
    // variaveis privadas da classe
    bool start;
    bool sty;
    bool heat;
    bool vp;
public:
    Vars(); //Construtor

    // funcoes para ler as variaveis
    bool get_start();
    bool get_sty();
    bool get_heat();
    bool get_vp();

    // funcoes para escrever as variaveis
    void set_start(bool value);
    void set_sty(bool value);
    void set_heat(bool value);
    void set_vp(bool value);

    // foncoes para inverter as variaveis
    void toggle_start();
    void toggle_sty();
    void toggle_heat();
    void toggle_vp();
};

#endif // VARS_H
