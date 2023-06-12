#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "../Headers/game.h"
#include "./game.cpp"

using namespace std;

int main () {
    cout << "============================= WELLCOME =============================" << endl;
    cout << "                        ...lendo arquivo...                         " << endl;
    cout << endl;

    ifstream arq;
    arq.open("../input.txt");

    if(!arq){
        cout << " => Nao foi possivel ler o arquivo." << endl;
        cout << "====================================================================" << endl;
        return -1;
    }
    else{
        cout << "                   ...arquivo lido com sucesso...                   " << endl;
        cout << endl;
        Game *puzzle = new Game(arq);
        cout << " => Tabuleiro Inicial: ";
        puzzle->print_board();
        cout << endl;
        cout << "------------------------------------------" << endl;

        int option = 9000;
        std::chrono::time_point<std::chrono::system_clock> init, final;

        while (option != 0){
            cout << "Funcionalidades: " << endl;
            cout << "   - 1 - Backtracking;" << endl;
            cout << "   - 2 - Busca em Profundidade" << endl;
            cout << "   - 3 - Busca em Largura" << endl;
            cout << "   - 4 - Busca Ordenada" << endl;
            cout << "   - 5 - Busca Gulosa" << endl;
            cout << "   - 6 - Busca A*" << endl;
            cout << "   - 7 - Busca IDA*" << endl;
            cout << "   - 0 - Sair do Programa" << endl;
            cout << "-------------------------------" << endl;
            cout << "Escolha uma opcao: ";
            cin >> option;
            cout << endl;
            cout << "------------------------------------------" << endl;

            switch (option){
                case 1:
                    init = chrono::high_resolution_clock::now();
                    // Chamar algoritmo aqui;
                    final = chrono::high_resolution_clock::now();
                    break;
                case 2:
                    init = chrono::high_resolution_clock::now();
                    // Chamar algoritmo aqui;
                    final = chrono::high_resolution_clock::now();
                    break;
                case 3:
                    init = chrono::high_resolution_clock::now();
                    // Chamar algoritmo aqui;
                    final = chrono::high_resolution_clock::now();
                    break;
                case 4:
                    init = chrono::high_resolution_clock::now();
                    // Chamar algoritmo aqui;
                    final = chrono::high_resolution_clock::now();
                    break;
                case 5:
                    init = chrono::high_resolution_clock::now();
                    // Chamar algoritmo aqui;
                    final = chrono::high_resolution_clock::now();
                    break;
                case 6:
                    init = chrono::high_resolution_clock::now();
                    // Chamar algoritmo aqui;
                    final = chrono::high_resolution_clock::now();
                    break;
                case 7:
                    init = chrono::high_resolution_clock::now();
                    // Chamar algoritmo aqui;
                    final = chrono::high_resolution_clock::now();
                    break;
                case 0:
                    cout << "                            ...Saindo...                            " << endl;
                    cout << "================================ BY ================================" << endl;
                    continue;
                default:
                    cout << "Opcao invalida." << endl;
                    cout << "-------------------------------" << endl;
                    continue;
            }
        }

        return 0;
    }

}