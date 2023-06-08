#include "Node.h"
#include <iostream>

using namespace std;

//? Construtor e Destrutor ---------------------------------------------------

Node::Node (int id, int pos, char color) {
    this->id = id;
    this->pos = pos;
    this->color = color;
    
    this->cost = 0;
    this->esq = nullptr;
    this->dir = nullptr;
}

Node::~Node () {
    delete this->esq;
    delete this->dir;
}

//? Getters ------------------------------------------------------------------

int Node::getId () {
    return this->id;
}

int Node::getPos () {
    return this->pos;
}

int Node::getCost () {
    return this->cost;
}

char Node::getColor () {
    return this->color;
}

Node* Node::getEsq () {
    return this->esq;
}

Node* Node::getDir () {
    return this->dir;
}

//? Setters ------------------------------------------------------------------

void Node::setCost (int cost) {
    this->cost = cost;
}

void Node::setColor (char color) {
    this->color = color;
}

void Node::setEsq (Node* node) {
    this->esq = node;
}

void Node::setDir (Node* node) {
    this->dir = node;
}