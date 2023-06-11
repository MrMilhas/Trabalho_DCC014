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
    ifstream arq;
    arq.open("input.txt");

    if(!arq){
        cout << "Não foi possível ler o arquivo" << endl;
    }
    else{
        int n;
        arq >> n;
        cout << n << endl; 
    }

    //Game *puzzle = new Game(4);
    //puzzle->print_board();

    return 0;
}