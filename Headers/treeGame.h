#ifndef TREEGAME_H
#define TREEGAME_H

#include <iostream>
#include <fstream>
#include "tree.h"
#include "game.h"

class TreeGame : Tree<Game> {

    public:

        TreeGame() {};
        ~TreeGame();

        bool compare(Game* a, Game* b) {return a->equals(b);};
        void save(string str);

    private:

        void saveNodes(ofstream &arq);
        void saveEdges(ofstream &arq);
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
    this->saveNodes(outFile);
    this->saveEdges(outFile);
    outFile << "}";
}

void TreeGame::saveNodes(ofstream &arq){
    Node<Game>* node = this->getRaiz();
    while(node != NULL){
        arq << node->getIndex() << " [label=" << node->getElement()->board << "]";
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
        }
        node = node->getProx();
    }
}

#endif //TREGAME_H