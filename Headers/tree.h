#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <limits.h>

/*
    A classe Tree é a classe base para a implementação de uma árvore.
    Para implementar Tree é presciso herdar a classe base e implementar
    a função "compare".

    Para que Tree seja uma árvore, ela segue as seguintes restrições:
    - Todo vértice, exceto a raiz, possui um pai;
    - Nenhum vértice é descendente de si próprio;
    - Nenhum vértice tem mais de um pai.
*/

#define COST 1

using namespace std;

template <class> class Node;
template <class> class Edge;

template <class T>
class Tree{
    
    public:

        Tree(T* element);
        Tree();
        ~Tree();

        Node<T>* add(Node<T>* parent, T* filho, int cost = COST);
        Node<T>* search(T* element);
        Node<T>* search(int index);
        void remove(Node<T>* folha);          

        int getOrdem() {return this->ordem;};
        Node<T>* getRaiz()  {return this->raiz;};

        virtual bool compare(T* a_element, T* b_element) = 0;

    private:

        Node<T>* raiz;
        int      ordem;

        void initTree(Node<T>* element);
        void mallocEdges(Node<T>* node);
        void removeEdge(Node<T>* node, T* element);
        bool verificaDescendentes(Node<T>* parent, T* element);
};


// Construtor padrão. Inicia a árvore com "element" como raiz
template <class T>
Tree<T>::Tree(T* element){
    this->initTree(new Node<T>(element,0));
}

// Inicia a árvore vazia
template <class T>
Tree<T>::Tree(){
    this->raiz = NULL;
    this->ordem = 0;
}

template <class T>
void Tree<T>::initTree(Node<T>* node){
    if(this->raiz != NULL)
        return;
    
    if(node == NULL){
        return;
    }

    this->raiz = node;
    this->ordem = 1;
    node->edge = NULL;
    node->parent = NULL;
    node->prox = NULL;
    node->index = 0;
    node->num_filhos = 0;
}

/** @brief Adiciona um novo filho na árvore.
 * 
 *  @return Vértice contendo filho. Caso a inserção falhe, retorna NULL.
 * 
 *  @param parent vértice pai de filho
 *  @param filho  elemento a ser adicionado
 *  @param cost   custo do pai até filho
 */
template <class T>
Node<T>* Tree<T>::add(Node<T>* parent, T* filho, int cost){
     
    if(parent == NULL)
        return NULL;

    if(this->raiz == NULL){
        this->initTree(parent);
    }

    if(parent->parent == NULL && this->raiz != parent)
        return NULL;

    if(this->verificaDescendentes(parent,filho))
        return NULL;
    
    Node<T>* node_filho = new Node(filho,this->ordem,cost);
    node_filho->parent = parent;
    node_filho->prox = parent->prox;
    parent->prox = node_filho;
    ordem++;

    Edge<T>* edge = new Edge(parent,node_filho);
    edge->prox = parent->edge;
    parent->edge = edge;
    parent->num_filhos++;

    return node_filho;
}

template <class T>
bool Tree<T>::verificaDescendentes(Node<T>* parent, T* element){
    Node<T>* n = parent;
    while(n != NULL){
        if(this->compare(n->element, element)){
            return true;
        }
        n = n->parent;
    }
    return false;
}

/**
 * @brief Busca pelo vértice contendo element
 * @param element alvo da busca
 * @return Retorna o vértice contendo element. Caso a busca falhe, retorna NULL.
*/
template <class T>
Node<T>* Tree<T>::search(T* element){
    Node<T>* n = this->raiz;
    while(n != NULL){
        if(this->compare(n->element, element))
            return n;
        n = n->prox;
    }
    return NULL;
}

/**
 * @brief Busca pelo vértice com o índice correspondente.
 * @param index índice alvo da busca
 * @return Retorna o vértice o índice correspondente. Caso a busca falhe, retorna NULL.
*/
template <class T>
Node<T>* Tree<T>::search(int index){
    Node<T>* n = this->raiz;
    while(n != NULL){
        if(n->index == index){
            return n;
        }
        n = n->prox;
    }
    return NULL;
}

/**
 * @brief Remove um vértice folha da árvore.
 * @param folha vértice a ser removido
*/
template <class T>
void Tree<T>::remove(Node<T>* folha){
    
    if(folha == NULL)
        return;
    
    if(folha->edge != NULL)
        return;

    this->removeEdge(folha->parent,folha->element);
    folha->parent->prox = folha->prox;
    delete folha->element;
    delete folha;
    this->ordem--;
}

template <class T>
void Tree<T>::removeEdge(Node<T>* node, T* element){
    
    if(node == NULL)
        return;
    
    Edge<T>* edge = node->edge;
    if(edge == NULL)
        return;

    if(this->compare(edge->final->element,element)){
        delete edge;
        node->edge = NULL;
        return;
    }

    Edge<T>* prox = edge->prox;
    while(prox != NULL){
        if(this->compare(prox->final->element,element)){
            edge->prox = prox->prox;
            delete prox;
            return;
        }
        edge = prox;
        prox = prox->prox;
    }
}

template <class T>
Tree<T>::~Tree(){
    Node<T>* n = this->raiz;
    Node<T>* prox;
    while(n != NULL){
        prox = n->prox;
        this->mallocEdges(n);
        delete n->element;
        delete n;
        n = prox;
    }
}

template <class T>
void Tree<T>::mallocEdges(Node<T>* node){
    Edge<T>* edge = node->edge;
    Edge<T>* prox; 
    while(edge != NULL){
        prox = edge->prox;
        delete edge;
        edge = prox;
    }
}


template <class T>
class Node{

    template<class> friend class Tree;

    private:

        T* element;
        int index;
        int cost;       //custo até a raiz
        int num_filhos;
        Node<T>* parent;
        Node<T>* prox;
        Edge<T>* edge;

        int calcCost(int cost);

    public:

        Node(T* element, int index = 0, int cost = COST){
            this->element = element;
            this->index = index;
            this->num_filhos = 0;
            this->parent = NULL;
            this->prox = NULL;
            this->edge = NULL;
            this->cost = this->calcCost(cost);
        };
        ~Node() {};

        T* getElement()       {return this->element;};
        int getIndex()       {return this->index;};
        int getNumFilhos()   {return this->num_filhos;};
        Node<T>* getParent() {return this->parent;};
        Node<T>* getProx()   {return this->prox;};
        Edge<T>* getEdge()   {return this->edge;};

        // void setParent(Node<T>* parent) {this->parent = parent;};
        // void setProx(Node<T>* prox)     {this->prox = prox;};
        // void setEdge(Edge<T>* edge)     {this->edge = edge;};
};

template <class T>
int Node<T>::calcCost(int cost){

    if(this->parent == NULL){
        return 0;
    }

    return this->parent->cost + cost;
}

template <class T>
class Edge{

    template <class> friend class Tree;

    private:

        Node<T>* init;
        Node<T>* final;
        Edge<T>* prox;

    public:

        Edge(Node<T>* init, Node<T>* final){
            this->init = init;
            this->final = final;
            this->prox = NULL;

        };
        ~Edge() {};

        Node<T>* getInit()  {return this->init;};
        Node<T>* getFinal() {return this->final;};
        Edge<T>* getProx()  {return this->prox;};

        void setProx(Edge<T>* prox) {this->prox = prox;};
};

#endif //TREE_H