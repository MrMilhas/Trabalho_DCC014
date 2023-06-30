#ifndef TREEGAME_H
#define TREEGAME_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include "tree.h"
#include "game.h"

class TreeGame : public Tree<Game> {

    public:

        TreeGame(Game* game) : Tree(game->build_child()) {nodes_expandidos = 0;};
        ~TreeGame() {nodes_expandidos = 0;};

        bool compare(Game* a, Game* b) {return a->equals(b);};
        void save(string str);
        void print();
        vector<Game*> caminho_win();
        int custo_win();

        int nodes_expandidos;

    private:

        void saveNodes(ofstream &arq);
        void saveEdges(ofstream &arq);
        string board_to_string(Game* game);
};

/**
 * @brief Salva a árvore em linguagem DOT.
 * @param str endereço do arquivo de saída
*/
void TreeGame::save(string str){

    ofstream outFile(str);

    if(!outFile){
        return;
    }
    outFile.seekp(0);
    outFile << "graph{\n";
    outFile << "node [shape=box style=filled]\n";
    this->saveNodes(outFile);
    this->saveEdges(outFile);
    outFile << "}";

    outFile.close();
}

void TreeGame::saveNodes(ofstream &arq){
    Node<Game>* node = this->getRaiz();
    vector<Game*> caminho = this->caminho_win();
    while(node != NULL){
        arq << node->getIndex() << " [";
        if(std::find(caminho.begin(),caminho.end(),node->getElement()) != caminho.end()){
            arq << " fillcolor=yellow color=red";
        }
        arq << " label=\"" << this->board_to_string(node->getElement()) << "\"]\n";
        node = node->getProx();
    }
}

void TreeGame::saveEdges(ofstream &arq){
    Node<Game>* node = this->getRaiz();
    while(node != NULL){    
        Edge<Game>* edge = node->getEdge();
        while(edge != NULL){
            arq << edge->getInit()->getIndex();
            arq << " -- " << edge->getFinal()->getIndex();
            arq << "\n";
            edge = edge->getProx();
        }
        node = node->getProx();
    }
}

string TreeGame::board_to_string(Game* game){
    string str = "";
    for(int i = 0; i < game->size_board; i++){
        str += game->board[i];
    }
    return str;
}

/**
 * @brief Retorna o caminho da raiz até o tabuleiro vitorioso
 * @return vector contendo o caminho para a vitoria
*/
vector<Game*> TreeGame::caminho_win(){
    vector<Game*> caminho;
    Node<Game>* node = this->getRaiz();

    while(!node->getElement()->verify_win()){
        node = node->getProx();
    }

    while(node != NULL){
        caminho.push_back(node->getElement());
        node = node->getParent();
    }
    std::reverse(caminho.begin(), caminho.end());
    return caminho;
}
/**
 * @brief Retorna o custo do caminho da raiz até o tabuleiro vitorioso
 * @return custo do caminho até o tabuleiro vitorioso. Se não for encontrado, retorna INT_MAX
*/
int TreeGame::custo_win(){
    Node<Game>* node = this->getRaiz();
    while(!node->getElement()->verify_win()){
        node = node->getProx();
    }
    
    if(node == NULL){   
        return INT_MAX;
    }
    
    return node->getCost();
}

void TreeGame::print(){
    cout << "--------------------------------" << endl;
    cout << "Ordem: " << this->getOrdem() << endl;

    Node<Game>* node = this->getRaiz();
    while(node != NULL){
        node->getElement()->print_board();
        Edge<Game>* edge = node->getEdge();
        while(edge != NULL){
            cout << " - ";
            edge->getFinal()->getElement()->print_board();
            edge = edge->getProx();
        }

        cout << " Custo: " << node->getCost();
        
        Node<Game>* pai = node->getParent();
        cout << " Pai: ";
        if(pai != NULL){
            pai->getElement()->print_board();
        }else{
            cout << " --- \n";
        }

        node = node->getProx();
    }
    cout << "--------------------------------" << endl;
}

#endif //TREGAME_H