#include "vars.h"

//construtor com as varaiveis membros inicializadas
Vars::Vars():start(false),sty(false),heat(false),vp(false)
{

}

//definicao das funcoes membro

bool Vars::get_start()
{
    return start;
}

bool Vars::get_sty()
{
    return sty;
}

bool Vars::get_heat()
{
    return heat;
}

bool Vars::get_vp()
{
    return vp;
}

void Vars::set_start(bool value)
{
    start = value;
}

void Vars::set_sty(bool value)
{
    sty = value;
}

void Vars::set_heat(bool value)
{
    heat = value;
}

void Vars::set_vp(bool value)
{
    vp = value;
}
void Vars::toggle_start()
{
    start = !start;
}

void Vars::toggle_sty()
{
    sty = !sty;
}

void Vars::toggle_heat()
{
    heat = !heat;
}

void Vars::toggle_vp()
{
    vp = !vp;
}
