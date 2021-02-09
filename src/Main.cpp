#include "Robo.h"
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

int GetXY(string CurrentCommand, bool IsX)
{
    for (int i = 0; i < (int)CurrentCommand.length(); i++)
    {
        // check if is already in the parentesis
        if (CurrentCommand[i] == '(')
        {
            int somador = 0;
            // check if the number 'x' has 2 digits
            if (CurrentCommand[i + 2] != ',')
                somador++;
            if (IsX)
            {
                if (somador == 0)
                    return (int)CurrentCommand[i + 1] - 48;
                else
                {
                    string aux;
                    aux = aux + (CurrentCommand[i + 1]);
                    aux = aux + (CurrentCommand[i + 1 + somador]);
                    return stoi(aux);
                }
            }
            else
            {
                // check if the number 'y' has 1 digit
                if (CurrentCommand[i + 4 + somador] == ')')
                    return (int)CurrentCommand[i + 3 + somador] - 48;
                // if number 'y' has 2 digits
                else
                {
                    string aux;
                    aux = aux + (CurrentCommand[i + 3 + somador]);
                    aux = aux + (CurrentCommand[i + 4 + somador]);
                    return stoi(aux);
                }
            }
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
#pragma region Inicializando variaveis e abrindo arquivos.
    // Criando todos os robos
    Robo AllRobots[50];
    // Atribuindo IDS
    for (int i = 0; i < (int)(sizeof(AllRobots)/sizeof(*AllRobots)); i++)
    {
        AllRobots[i].MyId = i;
    }
    // Criando variaveis da base
    int RecursosBase = 0;
    int AliensBase = 0;
    // Abrindo mapa e pegando suas dimensoes
    ifstream MapFile(argv[1]);
    if (!MapFile)
    {
        cout << "Impossivel abrir map file";
        return -1;
    }
    string MapDimentions;
    getline(MapFile, MapDimentions);
    // Criando array de string para ter armazenado o mapa
    string MapArray[stoi(MapDimentions)];
    int j = 0;
    while (getline(MapFile, MapArray[j]))
    {
        j++;
        if(j >= stoi(MapDimentions))
            break;
    }
    for (int i = 0; i < (int)(sizeof(MapArray) / sizeof(*MapArray)); i++)
    {
        std::string::iterator end_pos = std::remove(MapArray[i].begin(), MapArray[i].end(), ' ');
        MapArray[i].erase(end_pos, MapArray[i].end());
    }
    // Fechando mapa
    MapFile.close();
    // Abrindo comandos
    ifstream CommandsFile(argv[2]);
    if (!CommandsFile)
    {
        cout << "Impossivel abrir commands file";
        return -1;
    }
#pragma endregion

#pragma region Lendo comandos
    string CurrentCommand;
    // Criando string para segurar os relatorios dos robos
    string Relatorio;
    // Lendo comandos
    while (getline(CommandsFile, CurrentCommand))
    {
        if (CurrentCommand.find("ATIVAR") != std::string::npos)
        {
            int RobotID = stoi(CurrentCommand.substr(7, 2));
            Relatorio.append(AllRobots[RobotID].Ativar());
            continue;
        }
        if (CurrentCommand.find("*MOVER") != std::string::npos)
        {
            int RobotID = stoi(CurrentCommand.substr(7, 2));
            int MoveX;
            int MoveY;
            if (RobotID > 9)
            {
                MoveX = GetXY(CurrentCommand, true);
                MoveY = GetXY(CurrentCommand, false);
            }
            else
            {
                MoveX = GetXY(CurrentCommand, true);
                MoveY = GetXY(CurrentCommand, false);
            }
            bool CanMove = true;
            if (MapArray[MoveX][MoveY] == 'O')
                CanMove = false;
            AllRobots[RobotID].RegistrarMove(true, CanMove, MoveX, MoveY);
            continue;
        }
        else if (CurrentCommand.find("MOVER") != std::string::npos)
        {
            int RobotID = stoi(CurrentCommand.substr(6, 2));
            int MoveX;
            int MoveY;
            if (RobotID > 9)
            {
                MoveX = GetXY(CurrentCommand, true);
                MoveY = GetXY(CurrentCommand, false);
            }
            else
            {
                MoveX = GetXY(CurrentCommand, true);
                MoveY = GetXY(CurrentCommand, false);
            }
            bool CanMove = true;
            if (MapArray[MoveX][MoveY] == 'O')
                CanMove = false;
            AllRobots[RobotID].RegistrarMove(false, CanMove, MoveX, MoveY);
            continue;
        }

        if (CurrentCommand.find("EXECUTAR") != std::string::npos)
        {
            int RobotID = stoi(CurrentCommand.substr(9, 2));
            if (AllRobots[RobotID].IsInMission())
            {
                Relatorio.append(AllRobots[RobotID].Executar());
            }
            else
                Relatorio.append(AllRobots[RobotID].PrintFailExecutar());
            continue;
        }

        if (CurrentCommand.find("*COLETAR") != std::string::npos)
        {
            int RobotID = stoi(CurrentCommand.substr(9, 2));
            if (AllRobots[RobotID].RegistrarColetar(true, MapArray))
            {
                MapArray[AllRobots[RobotID].GetCurrentPos().X][AllRobots[RobotID].GetCurrentPos().Y] = '.';
                RecursosBase++;
            }
            continue;
        }

        else if (CurrentCommand.find("COLETAR") != std::string::npos)
        {
            int RobotID = stoi(CurrentCommand.substr(8, 2));
            if (AllRobots[RobotID].RegistrarColetar(false, MapArray))
            {
                MapArray[AllRobots[RobotID].GetPosToMove().X][AllRobots[RobotID].GetPosToMove().Y] = '.';
                RecursosBase++;
            }
            continue;
        }

        if (CurrentCommand.find("*ELIMINAR") != std::string::npos)
        {
            int RobotID = stoi(CurrentCommand.substr(10, 2));
            if (AllRobots[RobotID].RegistrarEliminar(true, MapArray))
            {
                MapArray[AllRobots[RobotID].GetCurrentPos().X][AllRobots[RobotID].GetCurrentPos().Y] = '.';
                AliensBase++;
            }
            continue;
        }

        else if (CurrentCommand.find("ELIMINAR") != std::string::npos)
        {
            int RobotID = stoi(CurrentCommand.substr(9, 2));
            if (AllRobots[RobotID].RegistrarEliminar(false, MapArray))
            {
                MapArray[AllRobots[RobotID].GetPosToMove().X][AllRobots[RobotID].GetPosToMove().Y] = '.';
                AliensBase++;
            }
            continue;
        }

        if (CurrentCommand.find("RELATORIO") != std::string::npos)
        {
            int RobotID = stoi(CurrentCommand.substr(10, 2));
            Relatorio.append(AllRobots[RobotID].PrintHistorico());
            continue;
        }

        if (CurrentCommand.find("RETORNAR") != std::string::npos)
        {
            int RobotID = stoi(CurrentCommand.substr(9, 2));
            Relatorio.append(AllRobots[RobotID].Retornar());
        }
    }
    // Fechando comandos
    CommandsFile.close();
#pragma endregion

    std::ofstream outfile{ "saida.txt" };
    Relatorio.erase(0, 1);
    outfile << Relatorio << endl;
    outfile << "BASE: TOTAL DE ALIENS " << AliensBase << " RECURSOS " << RecursosBase << endl;
    cout << Relatorio << endl << "BASE: TOTAL DE ALIENS " << AliensBase << " RECURSOS " << RecursosBase << endl;
    outfile.close();
    return 0;
}