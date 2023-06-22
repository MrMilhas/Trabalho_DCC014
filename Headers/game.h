#ifndef GAME_H
#define GAME_H

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
#include <list>
#include <utility>
#include <vector>

using namespace std;

#define BLACK 'B' // Fichas pretas;
#define WHITE 'W' // Fichas brancas;

class Game {

    public:
        int n_pieces;     // Quantidade de peças de cada cor;
        int size_board;   // Tamanho do tabuleiro: (2 * n_pieces) + 1;

        char *board;      // Tabuleiro;
        char *board_win;  // Tabuleiro objetivo;

        int cost;         // Custo total até chegar nesse nó (Baseado na quantidade de peças fora do lugar);
        int count_move;   // Contador de movimentos;

        //? Constructor and Destructor ---------------------------------
        Game();
        ~Game();

        //? Methods ----------------------------------------------------
        //bool possible_move(int id, int target);
        bool verify_win();
        bool equals(Game *g);
        
        void print_board();
        void print_solution();
        void move(int id, int target);
        void build_board(std::istream &input);

        Game *build_child();
        
        int calc_estimate_cost();
        int calc_objective();
        int calc_cost();

        std::vector<std::pair<int, int>> possible_moves();

};

#endif