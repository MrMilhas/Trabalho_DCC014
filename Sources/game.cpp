#include <iostream>
#include <string>
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
