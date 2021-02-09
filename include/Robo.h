
#ifndef ROBO_H
#define ROBO_H

#include <iostream>

using namespace std;

struct Vector2D
{
public:
    int X = 0;
    int Y = 0;
} typedef Vector2D;

class Robo
{
private:
    bool EmMissao = false;
    Vector2D MyPosition;
    Vector2D PosToMove;
    int ContadorDeColeta = 0;
    int ContadorDeAliens = 0;
    string Historico;
public:
    Vector2D GetPosToMove() { return PosToMove; }
    Vector2D GetCurrentPos() { return MyPosition; }
    int MyId;
    void RegistrarMove(bool Priority, bool Success, int X, int Y);
    bool RegistrarColetar(bool Priority, string* Map);
    bool RegistrarEliminar(bool Priority, string* Map);
    string Ativar();
    string Executar();
    string PrintFailExecutar();
    string PrintHistorico();
    string Retornar();
    bool IsInMission() const { return EmMissao; }
};

#endif