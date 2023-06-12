#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <tuple>
#include <list>
#include "../Headers/game.h"

using namespace std;

//? Constructor and Destructor--------------------------------
Game::Game(std::istream &input){
    input >> this->n_pieces;
    this->size_board = (2*n_pieces) + 1;
    board = new char[0];
    for (int i=0; i<this->size_board; i++){
        input >> board[i];
    }
    this->count_white = n_pieces;
    this->count_move = 0;
}

Game::~Game(){
    delete this->board;
}

//? Methods --------------------------------------------------
void Game::print_board(){
    cout << "[ ";
    for(int i=0; i<this->size_board; i++){
        cout << board[i] << " ";
    }
    cout << "]" << endl;
}

bool Game::verify_win(){
    return count_white == 0;
}

Game *Game::build_child(){
    Game *aux;

    aux->n_pieces = this->n_pieces;
    aux->size_board = this->size_board;
    aux->count_white = this->count_white;
    aux->count_move = this->count_move;
    aux->board = new char[this->n_pieces];

    for(int i=0; i<this->size_board; i++){
        aux->board[i] = this->board[i];
    }

    return aux;
}

/**
 * @brief Verifica os movimentos possíveis a partir de uma conifugração de tabuleiro;
 * 
 * @param three            Recebe a árvore da solução;
 * @return list<tuple<int, int>>  Retorna a lista de movimentos possíveis;
 */
list<tuple<int, int>> Game::possible_moves(list<Game *> *three){
    list<tuple<int, int>> moves;

    for(int i=0; i<this->size_board; i++){
        if(this->board[i] != '-' && this->board[i+1] == '-'){
            Game *aux = this->build_child();
            aux->board[i+1] = aux->board[i];
            aux->board[i] = '-';

            if(!(std::find(three->begin(), three->end(), aux->board) != three->end())){
                moves.push_back(tuple<int, int>(i, i+1));
            }
        }

        if(this->board[i] != '-' && this->board[i+2] == '-'){
            Game *aux = this->build_child();
            aux->board[i+2] = aux->board[i];
            aux->board[i] = '-';

            if(!(std::find(three->begin(), three->end(), aux->board) != three->end())){
                moves.push_back(tuple<int, int>(i, i+2));
            }
        }

        if(this->board[i] != '-' && this->board[i-1] == '-'){
            Game *aux = this->build_child();
            aux->board[i-1] = aux->board[i];
            aux->board[i] = '-';

            if(!(std::find(three->begin(), three->end(), aux->board) != three->end())){
                moves.push_back(tuple<int, int>(i, i-1));
            }
        }

        if(this->board[i] != '-' && this->board[i-2] == '-'){
            Game *aux = this->build_child();
            aux->board[i-2] = aux->board[i];
            aux->board[i] = '-';

            if(!(std::find(three->begin(), three->end(), aux->board) != three->end())){
                moves.push_back(tuple<int, int>(i, i-2));
            }
        }
    }

    return moves;
}
