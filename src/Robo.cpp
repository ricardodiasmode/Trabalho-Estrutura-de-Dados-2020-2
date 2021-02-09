#include "Robo.h"

void Robo::RegistrarMove(bool Priority, bool Success, int X, int Y) 
{
    if (Success)
    {
        if (Priority)
        {
            MyPosition.X = X;
            MyPosition.Y = Y;
            string RegistroMove;
            RegistroMove.append("\nROBO " + to_string(MyId) + ": MOVEU PARA (" + to_string(X) + "," + to_string(Y) + ")");
            Historico.insert(0, RegistroMove);
        }
        else
        {
            PosToMove.X = X;
            PosToMove.Y = Y;
            Historico.append("\nROBO " + to_string(MyId) + ": MOVEU PARA (" + to_string(X) + "," + to_string(Y) + ")");
        }
    }
    else
    {
        if (Priority)
        {
            string RegistroMove;
            RegistroMove.append("\nROBO " + to_string(MyId) + ": IMPOSSIVEL MOVER PARA (" + to_string(X) + "," + to_string(Y) + ")");
            Historico.insert(0, RegistroMove);
        }
        else
            Historico.append("\nROBO " + to_string(MyId) + ": IMPOSSIVEL MOVER PARA (" + to_string(X) + "," + to_string(Y) + ")");
    }
}

bool Robo::RegistrarColetar(bool Priority, string* Map)
{
    bool Success;
    if (Priority)
    {
        Success = Map[MyPosition.X][MyPosition.Y] == 'R';
        if (Success)
        {
            string RegistroColetar;
            RegistroColetar.append("\nROBO " + to_string(MyId) + ": RECURSOS COLETADOS EM (" + to_string(MyPosition.X) + "," + to_string(MyPosition.Y) + ")");
            Historico.insert(0, RegistroColetar);
            ContadorDeColeta++;
            return true;
        }
        else
        {
            string RegistroColetar;
            RegistroColetar.append("\nROBO " + to_string(MyId) + ": IMPOSSIVEL COLETAR RECURSOS EM (" + to_string(PosToMove.X) + "," + to_string(PosToMove.Y) + ")");
            Historico.insert(0, RegistroColetar);
            return false;
        }
    }
    else
    {
        Success = Map[PosToMove.X][PosToMove.Y] == 'R';
        if (Success)
        {
            ContadorDeColeta++;
            Historico.append("\nROBO " + to_string(MyId) + ": RECURSOS COLETADOS EM (" + to_string(PosToMove.X) + "," + to_string(PosToMove.Y) + ")");
            return true;
        }
        else
        {
            Historico.append("\nROBO " + to_string(MyId) + ": IMPOSSIVEL COLETAR RECURSOS EM (" + to_string(PosToMove.X) + "," + to_string(PosToMove.Y) + ")");
            return false;
        }
    }
}

bool Robo::RegistrarEliminar(bool Priority, string* Map)
{
    bool Success;
    if (Priority)
    {
        Success = Map[MyPosition.X][MyPosition.Y] == 'H';
        if (Success)
        {
            string RegistroEliminar;
            RegistroEliminar.append("\nROBO " + to_string(MyId) + ": ALIEN ELIMINADO EM (" + to_string(MyPosition.X) + "," + to_string(MyPosition.Y) + ")");
            Historico.insert(0, RegistroEliminar);
            ContadorDeAliens++;
            return true;
        }
        else
        {
            string RegistroEliminar;
            RegistroEliminar.append("\nROBO " + to_string(MyId) + ": IMPOSSIVEL ELIMINAR ALIEN EM (" + to_string(MyPosition.X) + "," + to_string(MyPosition.Y) + ")");
            Historico.insert(0, RegistroEliminar);
            return false;
        }
    }
    else
    {
        Success = Map[PosToMove.X][PosToMove.Y] == 'H';
        if (Success)
        {
            Historico.append("\nROBO " + to_string(MyId) + ": ALIEN ELIMINADO EM (" + to_string(PosToMove.X) + "," + to_string(PosToMove.Y) + ")");
            ContadorDeAliens++;
            return true;
        }
        else
        {
            Historico.append("\nROBO " + to_string(MyId) + ": IMPOSSIVEL ELIMINAR ALIEN EM (" + to_string(PosToMove.X) + "," + to_string(PosToMove.Y) + ")");
            return false;
        }
    }
}

string Robo::Ativar()
{
    if (EmMissao)
        return "\nBASE: ROBO " + to_string(MyId) + " JA ESTA EM MISSAO";
    EmMissao = true;
    return "\nBASE: ROBO " + to_string(MyId) + " SAIU EM MISSAO";
}

string Robo::Executar()
{
    if (Historico.find("MOVEU") != std::string::npos)
    {
        MyPosition = PosToMove;
    }
    string aux = Historico;
    Historico = "";
    return aux;
}

string Robo::PrintFailExecutar()
{
    return "\nBASE: ROBO " + to_string(MyId) + " NAO ESTA EM MISSAO";
}

string Robo::PrintHistorico()
{
    return Historico;
}

string Robo::Retornar()
{
    string aux;
    if (EmMissao)
    {
        MyPosition.X = 0;
        MyPosition.Y = 0;
        PosToMove.X = 0;
        PosToMove.Y = 0;
        aux.append("\nBASE: ROBO " + to_string(MyId) + " RETOURNOU ALIENS " + to_string(ContadorDeAliens) + " RECURSOS " + to_string(ContadorDeColeta));
        ContadorDeColeta = 0;
        ContadorDeAliens = 0;
    }
    else
        aux.append("\nBASE: ROBO " + to_string(MyId) + " NAO ESTA EM MISSAO");
    Historico = "";
    EmMissao = false;
    return aux;
}
