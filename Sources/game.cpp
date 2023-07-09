#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <utility>
#include <vector>
#include "../Headers/game.h"

using namespace std;

//? Constructor and Destructor--------------------------------
Game::Game(){
    
}

Game::~Game(){
    delete [] this->board;
    delete [] this->board_win;
}

//? Methods --------------------------------------------------
void Game::print_board(){
    cout << "[ ";
    for(int i=0; i<this->size_board; i++){
        cout << board[i] << " ";
    }
    cout << "]" << endl;
}

void Game::print_solution(){
    cout << "[ ";
    for(int i=0; i<this->size_board; i++){
        cout << board_win[i] << " ";
    }
    cout << "]" << endl;
}

void Game::build_board(std::istream &input){
    input >> this->n_pieces;
    this->size_board = (2*n_pieces) + 1;
    board = new char[this->size_board];
    board_win = new char[this->size_board];
    for (int i=0; i<this->size_board; i++){
        input >> board[i];
        if(i<n_pieces){board_win[i] = BLACK;}
        else{
            if(i == n_pieces){board_win[i] = '-';}
            else{board_win[i] = WHITE;}
        }
    }
    this->cost = 0;
    this->count_move = 0;
}

bool Game::verify_win(){
    for(int i=0; i<this->size_board; i++){
        if(board[i] != board_win[i]){
            return false;
        }
    }
    return true;
}

Game *Game::build_child(){
    Game *aux = new Game();

    aux->n_pieces = this->n_pieces;
    aux->size_board = this->size_board;
    aux->cost = this->cost;
    aux->count_move = this->count_move;
    aux->board = new char[this->size_board];
    aux->board_win = new char[this->size_board];

    for(int i=0; i<this->size_board; i++){
        aux->board[i] = this->board[i];
        aux->board_win[i] = this->board_win[i];
    }
    return aux;
}

/**
 * @brief Verifica os movimentos possíveis a partir de uma configuração de tabuleiro;
 * 
 * @param three                   Recebe a árvore da solução;
 * @return list<tuple<int, int>>  Retorna a lista de movimentos possíveis;
 */
std::vector<pair<int, int>> Game::possible_moves(){
    vector<std::pair<int, int>> moves;
    int indexVazio = 0;
    for(int i = 0; i < this->size_board; i++){
        if(this->board[i] == '-'){
            indexVazio = i;
            break;
        }
    }

    if(indexVazio + 1 < this->size_board){
        moves.push_back(pair<int,int>(indexVazio,indexVazio + 1));
    }

    if(indexVazio - 1 >= 0){
        moves.push_back(pair<int,int>(indexVazio,indexVazio - 1));
    }

    if(indexVazio + 2 < this->size_board){
        moves.push_back(pair<int,int>(indexVazio,indexVazio + 2));
    }

    if(indexVazio - 2 >= 0){
        moves.push_back(pair<int,int>(indexVazio,indexVazio - 2));
    }

    return moves;
}

void Game::move(int id, int target){
    char aux = this->board[target];
    this->board[target] = this->board[id];
    this->board[id] = aux;
}

bool Game::equals(Game *g){
    for (int i = 0; i < this->size_board; i++){
        if (this->board[i] != g->board[i])
            return false;
    }
    return true;
}

int Game::calc_heuristic(){
    int cost = 0;
    Game* child = this->build_child();

    int indice_vazio;
    for(int i = 0; i < this->size_board; i++){
        if(this->board[i] == '-'){
            indice_vazio = i;
            break;
        }
    }
    if(indice_vazio != this->n_pieces){
        child->move(indice_vazio,this->n_pieces);
        cost++;
    }

    for(int i = this->size_board - 1; i > this->size_board/2; i--){
        if(child->board[i] != child->board_win[i]){
            cost++;
        }
    }

    delete child;
    // for(int i=0; i<this->size_board; i++){
    //     if(this->board[i] != this->board_win[i]){
    //         cost++;
    //     }
    // }
    return cost;
}
