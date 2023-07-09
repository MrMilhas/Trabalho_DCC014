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
Game* escolhe_filho(TreeGame* tree, Node<Game>* node);
Game* escolhe_filho_nao_repetido(TreeGame* tree, Node<Game>* node);

Node<Game>* searchList(std::list<Node<Game>*> list, Game* game){
    for(auto open : list){
        if(open->getElement()->equals(game)){
            return open;
        }
    }
    return NULL;
}

// Algoritmos de busca
bool backtracking (TreeGame* tree){
    Node<Game>* node = tree->getRaiz();
    bool sucesso = false;
    while(!sucesso){
        
        Game* child = escolhe_filho_nao_repetido(tree, node);
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
                if(search == NULL){
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
    bool sucesso = false;
    while(!sucesso){
        if(abertos.empty())
            return false;

        long int inf = INT_MAX;  // Variável auxiliar para encontrar o menor custo na lista de abertos;

        // Obtem o nó com menor custo total da lista de abertos;
        for(auto open : abertos){
            int cost = open->getCost();
            if(cost < inf){
                inf = cost;
                node = open;
            }
        }
        
        Game *game = node->getElement();
        if(game->verify_win()){
            sucesso = true;
        }
        else{
            std::vector<std::pair<int,int>> possible_moves = game->possible_moves();
            for(auto move : possible_moves){
                Game* child = game->build_child();
                child->move(get<0>(move),get<1>(move));
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
    bool sucesso = false;
    while(!sucesso){
        if(abertos.empty())
            return false;

        long int inf = INT_MAX;  // Variável auxiliar para encontrar o menor custo na lista de abertos;

        // Obtem o nó com menor valor heurístico da lista de abertos;
        for(auto open : abertos){
            int heuristica = open->getElement()->calc_heuristic();
            if(heuristica < inf){
                inf = heuristica;
                node = open;
            }
        }

        Game* game = node->getElement();
        if(game->verify_win()){
            sucesso = true;        }
        else{
            std::vector<std::pair<int,int>> possible_moves = game->possible_moves();
            for(auto move : possible_moves){
                Game* child = game->build_child();
                child->move(get<0>(move),get<1>(move));
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

    bool sucesso = false;
    while(!sucesso){
        if(abertos.empty())
            return false;

        long int inf = INT_MAX;  // Variável auxiliar para encontrar o menor custo na lista de abertos;

        // Obtem o nó com menor custo total da lista de abertos;
        for(auto open : abertos){
            if(open->getElement()->cost < inf){
                inf = open->getElement()->cost;
                node = open;
            }
        }

        Game* game = node->getElement();
        if(game->verify_win()){
            sucesso = true;
        }
        else{
            std::vector<std::pair<int,int>> possible_moves = game->possible_moves();
            for(auto move : possible_moves){
                Game* child = game->build_child();
                child->move(get<0>(move),get<1>(move));
                Node<Game>* search = tree->search(child);
                if(search == NULL){
                    Node<Game>* node_child = tree->add(node,child);
                    child->cost = child->calc_heuristic() + node_child->getCost();
                    abertos.push_back(node_child);  
                }else{
                    if(searchList(fechados,child) != NULL || tree->verificaAncestrais(node,child)){
                        delete child;
                    }else{
                        int func_child = node->getCost() + 1 + child->calc_heuristic();
                        if(func_child < search->getElement()->cost){
                            Node<Game>* node_child = tree->add(node,child);
                            child->cost = child->calc_heuristic() + node_child->getCost();
                            abertos.push_back(node_child);  
                            abertos.remove(search);
                        } else{
                            delete child;
                        }
                    }
                }
            }
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
                    func_avaliacao = calc_func(node);
                }else{
                    Game* child = escolhe_filho(tree, node);
                    if(child != NULL){
                        node = tree->add(node,child);
                        func_avaliacao = calc_func(node); 
                    }else{
                        if(node == tree->getRaiz()){
                            patamar_old = patamar;
                            patamar = min_descartados;
                            min_descartados = INT_MAX;
                            tree->clear();
                        }else{
                            node = node->getParent();
                            func_avaliacao = calc_func(node);
                        }
                    }
                }
            }
        }
    }
    tree->nodes_expandidos = tree->getOrdem();
    return true;
}

//Implementação funções auxiliares
int calc_func(Node<Game>* node){
   Game* game = node->getElement();
   return node->getCost() + game->calc_heuristic();
}

Game* escolhe_filho(TreeGame* tree, Node<Game>* node){
    Game* game = node->getElement();
    std::vector<std::pair<int,int>> possible_moves = game->possible_moves();
    Game* child = game->build_child();
    for(auto move : possible_moves){
        child->move(get<0>(move),get<1>(move));
        if(!tree->verificaAncestrais(node,child)){
            if(!tree->verificaFilhos(node,child)){
                return child;
            }
        }
        child->move(get<0>(move),get<1>(move));
    }
    delete child;
    return NULL;
}

Game* escolhe_filho_nao_repetido(TreeGame* tree, Node<Game>* node){
    Game* game = node->getElement();
    std::vector<std::pair<int,int>> possible_moves = game->possible_moves();
    Game* child = game->build_child();
    for(auto move : possible_moves){
        child->move(get<0>(move),get<1>(move));
        if(tree->search(child) == NULL){
            return child;
        }
        child->move(get<0>(move),get<1>(move));
    }
    delete child;
    return NULL;
}


#endif