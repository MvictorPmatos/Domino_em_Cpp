#include <iostream>
#include "tadTile.h"

// CLASSES COMPONENTES 
    
    // Classe que guarda a lista e os métodos das pedras
    class Deck{
        private:
            cTile* head; // Aponta para o endereço do começo da lista

        public:
            Deck(); // [MÉTODO INTERNO] Inicializa a lista vazia com head apontando para NULL
            bool make(int r, int l); // [MÉTODO INTERNO] Insere valores no lado direito e esquedo das pedras, um a um
            void createTile(); // [MÉTODO EXTERNO] Cria os valores e insere nas pedras de forma ordenada
            void shuffle(); // [MÉTODO EXTERNO] Cria os valores e insere nas pedras de forma "embaralhada"
            void print(); // [MÉTODO EXTERNO] Exibe a pedras na saída/terminal
            int backR(int i); // [MÉTODO INTERNO] Retorna o valor do lado direito de uma pedra segundo sua posição
            int backL(int k); // [MÉTODO INTERNO] Retorna o valor do lado esquerdo de uma pedra segundo sua posição
    };

    // Classe que guarda a lista do cava
    class Stock {
        private:
            cTile* top;
            int numStock;
        public:
            Stock(); // [MÉTODO EXTERNO] Inicializa o cava
            void insertStockOne(Deck s, int index); // [MÉTODO INTERNO] Insere pedras 1 a 1
            void insertStock(Deck s, int numPlayers); // [MÉTODO INTERNO] Insere as pedras no cava de acordo com a quantidade de jogadores
            int backStockR(); // [MÉTODO INTERNO] Retorna o valor direito da primeira pedra do cava
            int backStockL(); // [MÉTODO INTERNO] Retorna o valor esquerdo da primeira pedra do cava
            cTile* unStockOne(); // [MÉTODO INTERNO] Apaga o primeiro elemento da lista
            void printStock(); // [MÉTODO EXTERNO] Exibe o cava
            cTile* theTop(); // [MÉTODO INTERNO] Retorna a 1º pedra da lista
    };

    // Classe que guarda a lista e os métodos dos jogadores
    class Player{
        private:
            cTile* headP; // Aponta para o endereço de começo da lista mão
            cTile* endP; // Aponta para o endereço de final da lista mão
            int qtElP; // Quantidade de pedras na mão
        public:
            Player(); // [MÉTODO INTERNO] Inicializa a lista 
            int numHand(); // [MÉTODO INTERNO] Retorna a quantidade de pedras na mão do jogador
            int backRR(int i); // [MÉTODO INTERNO] Retorna o valor do lado direito de uma pedra segundo sua posição
            int backLL(int k); // [MÉTODO INTERNO] Retorna o valor do lado esquerdo de uma pedra segundo sua posição
            bool insertP(Deck s, int index); // [MÉTODO INTERNO] Insere pedras do deck "embaralhado" na mão
            bool stockToHand(Stock stock); //[MÉTODO INTERNO] Insere pedras do cava na mão
            bool makePlayer(Deck s, int j); // [MÉTODO INTERNO] Automatiza a inserção das pedras de acordo com o jogador
            void players(Player p1, Player p2, Player p3, Player p4, Deck s, int numPlayers); // [MÉTODO EXTERNO] De acordo com o número de jogadores aleatório, insere pedras na mão dos jogadores válidos
            bool deleteTile(int i); // [MÉTODO INTERNO] Deleta pedra de acordo com index
            int largets(); // [MÉTODO INTERNO] Encontra a maior soma em uma mão de jogador
            bool emptyHand(); // [MÉTODO INTERNO] Verifica e retorna se mão é vazia
            int PlayerPosition(Player p1,Player p2,Player p3,Player p4,Deck s, int numPlayers); // [MÉTODO EXTERNO] Retona o player com maior pedra no começo
            int StonePosition(Player p,Player p1,Player p2,Player p3,Player p4,Deck s, int numPlayers); // [MÉTODO EXTERNO] Consegue a posição da pedra, com base no jogador com a maior pedra.
            cTile* beginHand(); // [MÉTODO INTERNO] Retorna o começo da mão do jogador
            void printHand(); // [MÉTODO INTERNO] Exibe as mão dos jogadores
            void printPlayers(Player p1, Player p2, Player p3, Player p4, int numPlayers); // [MÉTODO EXTERNO] Printa os jogadores


    };

    // Classe que guarda a lista e os métodos do tabuleiro
    class Board{
        private:
            cTile* tip; // Guarda o endereço do início da lista
            int qtElB; // Quantidade de pedras na lista
        public:
            Board(); // [MÉTODO INTERNO] Inicializa a lista

            int backTipR(); // [MÉTODO INTERNO] Retorna o valor da ponta direita (Em relação ao monitor)
            int backTipL(); // [MÉTODO INTERNO] Retorna o valor da ponta esquerda (Em relação ao monitor)

            bool insertStart(Player p, Deck s, int index); // [MÉTODO INTERNO] Insere a 1° pedra da partida

            bool insertEnd(Player p, Deck s, int index, bool spin); // [MÉTODO INTERNO] Insere uma pedra na 2º ponta do tabuleiro

            bool insertBegin(Player p, Deck s, int index, bool spin); // [MÉTODO INTERNO] Insere uma pedra na 1º ponta do tabuleiro

            int NextPlayer(int turn, int numPlayers); // [METODO INTERNO] Descobre quem é o próximo jogador.
            
            bool Tocompare(Deck s,Player p); // [METODO INTERNO] Comparar pedra da mão com a da mesa
            
            int positionTile(Deck s, Player p); // [MÉTODO INTERNO] Retorna a posição da pedra a ser jogada
            
            bool beginEnd(Deck s, Player p); // [MÉTODO INTERNO] Verifica se a pedra deve ser jogada no início ou no fim
            
            bool shouldSpin(Deck s, Player p); // [MÉTODO INTERNO] Verifica se a pedra deve ser girada para ser jogada
            
            int beginGame(int turn, int position, Player p1, Player p2, Player p3, Player p4, Deck s); // [MÉTODO EXTERNO] Faz o primeiro lance do jogo
            
            int round(int turn, int numPlayers, Deck s, Player p, Stock stock); // [MÉTODO EXTERNO] Faz jogada por jogador
            
            int endGame(int numPlayers, Player p1, Player p2, Player p3, Player p4); // [MÉTODO INTERNO] Soma pedras na mão e retorna a mão com menor valor de soma
            
            void printBoard(); // [MÉTODO EXTERNO] Exibe o tabuleiro

    };

    // Classe que simula o jogo a partir dos método criados em outras classes
    class Game{
        public:
            void moves(int turn, int numPlayers, Deck s, Player p1, Player p2, Player p3, Player p4, Stock stock, Board table); // [MÉTODO EXTERNO] Tenta simular as jogadas e determinar vencedor
    };