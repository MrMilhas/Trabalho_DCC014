#ifndef GAME_H
#define GAME_H

#include <iostream>

#define BLACK 'B' // Fichas pretas;
#define WHITE 'W' // Fichas brancas;

class Game {

    public:
        int n_pieces;     // Quantidade de peças de cada cor;
        int size_board;   // Tamanho do tabuleiro: (2 * n_pieces) + 1;

        char *board;      // Tabuleiro;

        int count_white;  // Qauntidade de peças brancas fora do lugar;
        int count_move;   // Contador de movimentos;

        //? Constructor and Destructor ---------------------------------
        Game(int n_pieces);
        ~Game();

        //? Methods ----------------------------------------------------
        bool possible_move(int id, int target);
        bool verify_win();

        void move(int id, int target);
        void print_board();

        int calc_estimate_cost();
        int calc_objective();
};

#endif