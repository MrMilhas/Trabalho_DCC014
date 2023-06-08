#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

using namespace std;

#define BLACK b;
#define WHITE w;

class Node {

    private:
        Node *esq;   // Casa da esquerda;
        Node *dir;   // Casa da direita;

        int id;      // Id do nó;
        int pos;     // Guarda a posição do nó na lista;
        int cost;    // Custo para o nó;
        char color;  // Cor da peça nesta casa;

    public:
        Node(int id, int pos, char color);  // Construtor;
        ~Node();                            // Destrutor;

        //? Getters --------------------------------------
        int getId ();
        int getPos ();
        int getCost ();
        char getColor ();
        Node *getEsq ();
        Node *getDir ();

        //? Setters --------------------------------------
        void setCost (int cost);
        void setColor (char color);
        void setEsq (Node *node);
        void setDir (Node *node);
};

#endif