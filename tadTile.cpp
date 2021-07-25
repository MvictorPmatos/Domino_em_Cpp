#include <iostream>
#include "tadTile.h"

// MÉTODOS DA PEDRA

    // [MÉTODO INTERNO] Inicializa a pedra
    cTile::cTile(int r, int l){
        this->right = r;
        this->left = l;
        this->next = NULL;
    }

    // [MÉTODO INTERNO] Seta valores na pedra (Lado direito e esquerdo)
    void cTile::setTile(int r, int l){
        right = r;
        left = l;
    }

    // [MÉTODO INTERNO] Seta para o próximo
    void cTile::setNex(cTile* nex){
        next = nex;
    }

    // [MÉTODO INTERNO] Seta para o anterior
    void cTile::setPrev(cTile* pre){
        prev = pre;
    }

    // [MÉTODO INTERNO] Retorna o valor do lado direito da pedra
    int cTile::getR(){
        return right;
    }

    // [MÉTODO INTERNO] Retorna o valor do lado esquerdo da pedra
    int cTile::getL(){
        return left;
    }

    // [MÉTODO INTERNO] Retorna o endereço da próxima pedra
    cTile* cTile::getNex(){
        return next;
    }

    // [MÉTODO INTERNO] Retorna o endereço da pedra anterior
    cTile* cTile::getPrev(){
        return prev;
    }


