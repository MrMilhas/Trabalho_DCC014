#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <stack>
#include <fstream>
#include <list>
#include <tuple>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits.h>
#include "game.h"
#include "treeGame.h"

using namespace std;


// Funções auxiliares
int calc_func(Node<Game>* node);
Game* escolhe_filho(TreeGame* tree,Game* game);


// Algoritmos de busca
bool backtracking (TreeGame* tree){
    Node<Game>* node = tree->getRaiz();
    bool sucesso = false;
    while(!sucesso){
        Game* child = escolhe_filho(tree,node->getElement());
        if(child != NULL){
            node = tree->add(node,child);
            if(node->getElement()->verify_win()){
                sucesso = true;
            }
        }else{
            if(node == tree->getRaiz()){
                return false;
            }else{
                node = node->getParent();
            }
        }
    }
    tree->nodes_expandidos = tree->getOrdem();
    return true;
}

bool buscaLargura(TreeGame* tree){
    std::list<Node<Game>*> abertos = {tree->getRaiz()};
    std::list<Node<Game>*> fechados;

    Node<Game>* node;
    bool sucesso = false;
    while(!sucesso){
        if(abertos.empty())
            return false;
        
        node = abertos.front();
        Game* game = node->getElement();

        if(game->verify_win()){
            sucesso = true;
        }else{
            std::vector<std::pair<int,int>> possible_moves = game->possible_moves();
            for(auto move : possible_moves){
                Game* child = game->build_child();
                child->move(get<0>(move),get<1>(move));
                if(tree->search(child) == NULL){  // Verifica se o vértice já está na arvore
                    abertos.push_back(tree->add(node,child));
                }else{
                    delete child;
                }
            }
            fechados.push_back(node);
            tree->nodes_expandidos++;
            abertos.pop_front();
        }
    }
    return true;
}

bool buscaProfundidade(TreeGame* tree){
    std::list<Node<Game>*> abertos = {tree->getRaiz()};
    std::list<Node<Game>*> fechados;

    Node<Game>* node;
    bool sucesso = false;
    while(!sucesso){
        if(abertos.empty())
            return false;
        
        node = abertos.front();
        Game* game = node->getElement();

        if(game->verify_win()){
            sucesso = true;
        }else{
            std::vector<std::pair<int,int>> possible_moves = game->possible_moves();
            for(auto move : possible_moves){
                Game* child = game->build_child();
                child->move(get<0>(move),get<1>(move));
                Node<Game>* search = tree->search(child);
                if(search == NULL){  // Verifica se o vértice já está na arvore                    
                    abertos.push_front(tree->add(node,child));
                }else{
                    delete child;
                }
            }
            fechados.push_back(node);
            tree->nodes_expandidos++;
            abertos.remove(node);
        }
    }
    return true;
}

bool buscaOrdenada(TreeGame *tree){
    std::list<Node<Game>*> abertos = {tree->getRaiz()};
    std::list<Node<Game>*> fechados;

    Node<Game>* node;
    Game *game = new Game();
    bool sucesso = false;
    while(!sucesso){
        if(abertos.empty())
            return false;

        long int inf = 999;  // Variável auxiliar para encontrar o menor custo na lista de abertos;

        // Obtem o nó com menor custo total da lista de abertos;
        for(auto open : abertos){
            if(open->getElement()->cost < inf){
                inf = open->getElement()->cost;
                node = open;
                game = open->getElement();
            }
        }

        if(game->verify_win()){
            return true;
        }
        else{
            std::vector<std::pair<int,int>> possible_moves = game->possible_moves();
            for(auto move : possible_moves){
                Game* child = game->build_child();
                child->move(get<0>(move),get<1>(move));
                child->cost = abs(get<1>(move) - get<0>(move)) + game->cost;  // Calcula o custo total do nó;
                Node<Game>* search = tree->search(child);
                if(search == NULL){  // Verifica se o vértice já está na arvore                    
                    abertos.push_back(tree->add(node,child));
                }else{
                    delete child;
                }
            }
            fechados.push_back(node);
            tree->nodes_expandidos++;
            abertos.remove(node);
        }
    }
    return true;
}

bool buscaGulosa(TreeGame *tree){
    std::list<Node<Game>*> abertos = {tree->getRaiz()};
    std::list<Node<Game>*> fechados;

    Node<Game>* node;
    Game *game = new Game();
    bool sucesso = false;
    while(!sucesso){
        if(abertos.empty())
            return false;

        long int inf = 999;  // Variável auxiliar para encontrar o menor custo na lista de abertos;

        // Obtem o nó com menor custo total da lista de abertos;
        for(auto open : abertos){
            if(open->getElement()->cost < inf){
                inf = open->getElement()->cost;
                node = open;
                game = open->getElement();
            }
        }

        if(game->verify_win()){
            return true;
        }
        else{
            std::vector<std::pair<int,int>> possible_moves = game->possible_moves();
            for(auto move : possible_moves){
                Game* child = game->build_child();
                child->move(get<0>(move),get<1>(move));
                child->cost = child->calc_heuristic() + game->cost;  // Calcula o custo total do nó;
                Node<Game>* search = tree->search(child);
                if(search == NULL){  // Verifica se o vértice já está na arvore                    
                    abertos.push_back(tree->add(node,child));
                }else{
                    delete child;
                }
            }
            fechados.push_back(node);
            tree->nodes_expandidos++;
            abertos.remove(node);
        }
    }
    return true;
}

bool buscaAEstrela(TreeGame *tree){
    std::list<Node<Game>*> abertos = {tree->getRaiz()};
    std::list<Node<Game>*> fechados;

    Node<Game>* node;
    Game *game = new Game();
    bool sucesso = false;
    while(!sucesso){
        if(abertos.empty())
            return false;

        long int inf = 999;  // Variável auxiliar para encontrar o menor custo na lista de abertos;

        // Obtem o nó com menor custo total da lista de abertos;
        for(auto open : abertos){
            if(open->getElement()->cost < inf){
                inf = open->getElement()->cost;
                node = open;
                game = open->getElement();
            }
        }

        if(game->verify_win()){
            return true;
        }
        else{
            std::vector<std::pair<int,int>> possible_moves = game->possible_moves();
            for(auto move : possible_moves){
                Game* child = game->build_child();
                child->move(get<0>(move),get<1>(move));
                child->cost = child->calc_heuristic() + game->cost + abs(get<1>(move) - get<0>(move));  // Calcula o custo total do nó;
                Node<Game>* search = tree->search(child);
                if(search == NULL){  // Verifica se o vértice já está na arvore                    
                    abertos.push_back(tree->add(node,child));
                }else{
                    delete child;
                }
            }
            fechados.push_back(node);
            tree->nodes_expandidos++;
            abertos.remove(node);
        }
    }
    return true;
}

bool buscaIDAEstrela(TreeGame* tree){
    Node<Game>* node = tree->getRaiz();
    std::stack<Game*> filhos;
    int min_descartados = INT_MAX;
    int func_avaliacao = calc_func(node);
    int patamar = func_avaliacao;
    int patamar_old = -1;
    bool sucesso = false;
    
    while(!sucesso){
        if(patamar_old == patamar){
            return false;
        }else{
            if(node->getElement()->verify_win() && (func_avaliacao <= patamar)){
                sucesso = true;
            }else{
                if(func_avaliacao > patamar){
                    if(func_avaliacao < min_descartados){
                        min_descartados = func_avaliacao;
                    }
                    node = node->getParent();
                }
                Game* child = escolhe_filho(tree,node->getElement());
                if(child != NULL){
                    node = tree->add(node,child);
                    func_avaliacao = calc_func(node); 
                }else{
                    if(node == tree->getRaiz()){
                        patamar_old = patamar;
                        patamar = min_descartados;
                        min_descartados = INT_MAX;
                        Game* raiz = node->getElement();
                        tree->clear();
                    }else{
                        node = node->getParent();
                        func_avaliacao = calc_func(node);
                    }
                }
            }
        }
    }
    tree->nodes_expandidos = tree->getOrdem();
    return true;
}

int calc_func(Node<Game>* node){
   Game* game = node->getElement();
   return node->getCost() + game->calc_heuristic();
}

Game* escolhe_filho(TreeGame* tree,Game* game){
    std::vector<std::pair<int,int>> possible_moves = game->possible_moves();
    Game* child = game->build_child();
    for(auto move : possible_moves){
        child->move(get<0>(move),get<1>(move));
        if(tree->search(child) == NULL){                    
            return child;
        }
        child->move(get<0>(move),get<1>(move));
    }
    return NULL;
}


#endif