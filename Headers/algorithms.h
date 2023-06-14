#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <fstream>
#include <list>
#include <tuple>
#include <vector>
#include <utility>
#include "game.h"

using namespace std;

bool searchTree(vector<Game *> &three, Game* puzzle){

    for(Game* game : three){
        if(game->equals(puzzle)){
            return true;
        }
    }
    return false;
}

/**
 * @brief Algoritmo de busca não informado Backtracking;
 * 
 * @param puzzle  Tabuleiro inicial do jogo;
 * @param three   Árvore com o caminho da solução;
 * @return true   Retorna verdadeiro se encontra solução;
 * @return false  Retorna falso se não encontra solução;
 */
bool backtracking (Game *puzzle, vector<Game *> &three){
    three.push_back(puzzle);              // Adicionando tabuleiro inicial no nó da árvore;
    if(puzzle->verify_win()){return true;}  // Verificando condição de vitória inicial;

    Game *child = puzzle->build_child();     // Criando nó filho;
    std::vector<std::pair<int, int>> possible_moves = child->possible_moves(three);

    for(auto currentTuple : possible_moves){
        // Avança
        child->move(get<0>(currentTuple), get<1>(currentTuple));

        if(!searchTree(three,child)){
            if(backtracking(child, three)){
                return true;
            }
        }

        // Retorna
        child->move(get<1>(currentTuple), get<0>(currentTuple));
    }

    three.pop_back();
    delete child;

    return false;
}

#endif