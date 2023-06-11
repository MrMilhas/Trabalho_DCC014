#include <chrono>
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

        

        return 0;
    }

}