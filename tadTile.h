#pragma once
#include <iostream>
//Classe da Pedra de Dominó
class cTile{
    private:
        int right; // Valor direito da pedra
        int left; // Valor esquerdo da pedra
        cTile* next; // Aponta para o próximo
        cTile* prev; // Aponta para o anterior
    public:
        cTile(int r, int l); // [MÉTODO INTERNO] Inicializa a pedra
        void setTile(int r, int l); // [MÉTODO INTERNO] Seta valores na pedra (Lado direito e esquerdo)
        void setNex(cTile* nex); // [MÉTODO INTERNO] Seta para o próximo
        int getR(); // [MÉTODO INTERNO] Retorna o valor do lado direito da pedra
        int getL(); // [MÉTODO INTERNO] Retorna o valor do lado esquerdo da pedra
        cTile* getNex(); // [MÉTODO INTERNO] Retorna o endereço da próxima pedra 
        void setPrev(cTile* pre); // [MÉTODO INTERNO] Seta para o anterior
        cTile* getPrev(); // [MÉTODO INTERNO] Retorna o endereço da pedra anterior
        
};