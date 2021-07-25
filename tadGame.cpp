#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <cstdlib>
#include <assert.h>
#include <tuple>
#include "tadGame.h"

using namespace std;

// MÉTODOS DO DECK

    // [MÉTODO INTERNO] Inicializa a lista vazia com head apontando para NULL
    Deck::Deck(){
        head = NULL;
    }

    // [MÉTODO INTERNO] Insere valores no lado direito e esquedo das pedras, um a um
    bool Deck::make(int r, int l){
        cTile* pt = new cTile( r, l);

        pt->setTile(r, l);
        pt->setNex(NULL);

        if(head == NULL)
            head = pt;
        else {
            pt->setNex(head);
            head = pt;
        }

        return true;

    }

    // [MÉTODO EXTERNO] Cria os valores e insere nas pedras de forma ordenada
    void Deck::createTile(){
        int j;
        int i;
        int w = 0;
        //Algoritmo gerador dos valores das pedras
            for(j = 7; j > 0; j--){
                while(w < 7){
                    for(i = w; i < j; i++){
                        make(i, w);
                    }
                    w++;
                }
            }
    }

    // [MÉTODO EXTERNO] Cria os valores e insere nas pedras de forma "embaralhada"
    void Deck::shuffle(){
        int j, i,h,b;
        vector<int> r;
        vector<int> l;
        int w = 0;
        //Algoritmo gerador dos valores das pedras
        for(j = 7; j > 0; j--){
            while(w < 7){
                for(i = w; i < j; i++){
                    r.push_back(i);
                    l.push_back(w);
                }
                w++;
            }
        }

        srand((unsigned)time(0));
        for(int c =0;c < 28; c++){
            int aleat = rand()%28;
            int temp = r[c];
            r[c] = r[aleat];
            r[aleat] = temp;

            int temp2 = l[c];
            l[c] = l[aleat];
            l[aleat] = temp2;

        }

        for(int k; k < 28; k++){
            h = r[k];
            b = l[k];
            make(h,b);
        }
    }

    // [MÉTODO EXTERNO] Exibe a pedras na saída/terminal
    void Deck::print(){
        cTile* leitor = head;
        while(leitor != nullptr){
            cout << "| " << leitor->getR() << " | " << leitor->getL() << " |" << endl;
            leitor = leitor->getNex();
        }
    }

    //[MÉTODO INTERNO] Retorna o valor do lado direito de uma pedra segundo sua posição
    int Deck::backR(int i){
        cTile* current = head;
        int cont = 0;
        while(current != NULL){
            if(cont == i)
                return current->getR();
            cont++;
            current = current->getNex();
        }
      assert(0);
    }

    //[MÉTODO INTERNO] Retorna o valor do lado esquerdo de uma pedra segundo sua posição
    int Deck::backL(int k){
        cTile* current = head;
        int cont = 0;
        while(current != NULL){
            if(cont == k)
                return current->getL();
            cont++;
            current = current->getNex();
        }
        assert(0);
    }

// MÉTODOS DA STOCK
    
    // [MÉTODO EXTERNO] Inicializa o cava
    Stock::Stock(){
        top = NULL;
        numStock = 0;
    }

    // [MÉTODO INTERNO] Insere pedras 1 a 1
    void Stock::insertStockOne(Deck s, int index){
        cTile* pt = new cTile(s.backR(index), s.backL(index));
        cTile* last = top;
        pt->setTile(s.backR(index), s.backL(index));

        if(top == NULL){
            top = pt;
            return;
        } else{
           while(last->getNex() != NULL)
                last = last->getNex();
            last->setNex(pt);
            pt->setPrev(last);
        }
        return;
    }

    // [MÉTODO INTERNO] Insere as pedras no cava de acordo com a quantidade de jogadores
    void Stock::insertStock(Deck s, int numPlayers){
        switch (numPlayers){
            case 2:
                for(int i = 12; i < 28; i++){
                    insertStockOne(s, i);
                    numStock++;
                }
                break;
            case 3:
                for(int i = 18; i < 28; i++){
                    insertStockOne(s, i);
                    numStock++;
                }
                break;
            case 4:
                for(int i = 24; i < 28; i++){
                    insertStockOne(s, i);
                    numStock++;
                }
                break;
        }
    }

    // [MÉTODO INTERNO] Retorna o valor direito da primeira pedra do cava
    int Stock::backStockR(){
        cTile* current = top;
        return current->getR(); 
    }
    
    // [MÉTODO INTERNO] Retorna o valor esquerdo da primeira pedra do cava
    int Stock::backStockL(){
        cTile* current = top;
        return current->getL(); 
    }

    // [MÉTODO INTERNO] Apaga o primeiro elemento da lista
    cTile* Stock::unStockOne(){
        if(top == NULL)
            return NULL;
        cTile* temp = top;
        top = top->getNex();
        delete temp;
        return top;
    }
    
    // [MÉTODO EXTERNO] Exibe o cava
    void Stock::printStock(){
        cTile* leitor = top;
        cout << " " << endl;
        cout << "===========================" << endl;
        cout << "Cava: " << endl;
        cout << "===========================" << endl;
        cout << " " << endl;
        while(leitor != NULL){
            cout << "| " << leitor->getR() << " | " << leitor->getL() << " |" << endl;
            leitor = leitor->getNex();
        }
        cout << " " << endl;
        cout << "===========================" << endl;
    }

    // [MÉTODO INTERNO] Retorna a 1º pedra da lista
    cTile* Stock::theTop(){
        return top;
    }


//MÉTODOS DO PLAYER

    // [MÉTODO INTERNO] Inicializa a lista 
    Player::Player(){
        headP = NULL;
        endP = NULL;
        qtElP = 0;
    }

    // [MÉTODO INTERNO] Retorna a quantidade de pedras na mão do jogador
    int Player::numHand(){
        return qtElP;
    }

    // [MÉTODO INTERNO] Retorna o valor do lado direito de uma pedra segundo sua posição
    int Player::backRR(int i){
        cTile* current = headP;
        int cont = 0;
        while(current != NULL){
            if(cont == i)
                return current->getR();
            cont++;
            current = current->getNex();
        }
        return -1;
    }

    // [MÉTODO INTERNO] Retorna o valor do lado esquerdo de uma pedra segundo sua posição
    int Player::backLL(int k){
        cTile* current = headP;
        int cont = 0;
        while(current != NULL){
            if(cont == k)
                return current->getL();
            cont++;
            current = current->getNex();
        }
        return -1;  //assert(0);
    }

    // [MÉTODO INTERNO] Insere pedras do deck "embaralhado" na mão
    bool Player::insertP(Deck s, int index){
        cTile* pt = new cTile(s.backR(index), s.backL(index));
        cTile* last = headP;
        pt->setTile(s.backR(index), s.backL(index));

        if(headP == NULL){
            headP = pt;
            return true;
        } else{
           while(last->getNex() != NULL)
                last = last->getNex();
            last->setNex(pt);
            pt->setPrev(last);
        }
        return true;
    }
    
    //[MÉTODO INTERNO] Insere pedras do cava na mão
    bool Player::stockToHand(Stock stock){
        cTile* pt = new cTile(stock.backStockR(), stock.backStockL());
        cTile* last = headP;
        if(stock.theTop() == NULL){
            return false;
        }
        pt->setTile(stock.backStockR(), stock.backStockL());
        while(last->getNex() != NULL)
            last = last->getNex();
        last->setNex(pt);
        pt->setPrev(last);
        
        qtElP++;
        stock.unStockOne();

        return true;
    }

    // [MÉTODO INTERNO] Automatiza a inserção das pedras de acordo com o jogador
    bool Player::makePlayer(Deck s, int j){
        switch(j){
            case 1:
                for(int i =0; i < 6; i++){
                    insertP(s, i);
                    qtElP++;
                }
                break;
            case 2:
                for(int i = 6; i < 12; i++){
                    insertP(s, i);
                    qtElP++;
                }
                break;
            case 3:
                for(int i = 12; i < 18; i++){
                    insertP(s, i);
                    qtElP++;
                }
                break;
            case 4:
                for(int i = 18; i < 24; i++){
                    insertP(s, i);
                    qtElP++;
                }
                break;
            default:
                return false;

        }
        return true;
    }
    
    // [MÉTODO EXTERNO] De acordo com o número de jogadores aleatório, insere pedras na mão dos jogadores válidos
    void Player::players(Player p1, Player p2, Player p3, Player p4, Deck s, int numPlayers){

        cout << " " << endl;
        cout << "===========================" << endl;
        cout << "Quantidade de Jogadores: " << numPlayers << endl;
        cout << "===========================" << endl;

        switch(numPlayers){
            case 2:
                p1.makePlayer(s,1);
                p2.makePlayer(s,2);
                break;
            case 3:
                p1.makePlayer(s,1);
                p2.makePlayer(s,2);
                p3.makePlayer(s,3);
                break;
            case 4:
                p1.makePlayer(s,1);
                p2.makePlayer(s,2);
                p3.makePlayer(s,3);
                p4.makePlayer(s,4);
                break;
            default:
                p1.makePlayer(s,1);
                p2.makePlayer(s,2);
                p3.makePlayer(s,3);
                p4.makePlayer(s,4);
        }
    }   

    // [MÉTODO INTERNO] Deleta pedra de acordo com index
    bool Player::deleteTile(int index){
        
        cTile* temp = headP;
        if(headP == NULL )
            return false;

        if(index == 0){
            headP = temp->getNex();
            free(temp);
            return true;
        }

        for(int i = 0; temp != NULL && i < index - 1; i++){
            temp = temp->getNex();
        }

        if(temp == NULL || temp->getNex() == NULL)
            return false;

        cTile* p = temp->getNex()->getNex();

        free(temp->getNex());

        temp->setNex(p);

        qtElP--;

        return true;

    }

    // [MÉTODO INTERNO] Encontra a maior soma em uma mão de jogador
    int Player::largets(){
        cTile* curr = headP;
        int maxR = 0;
        int maxL = 0;
        int sum;
        while(curr != NULL){
            if((maxR + maxL) < (curr->getR() + curr->getL())){
                maxR = curr->getR();
                maxL = curr->getL();
            } 
            curr = curr->getNex();
        }
        sum = maxR + maxL;
        return sum;

    }

    // [MÉTODO INTERNO] Verifica e retorna se mão é vazia
    bool Player::emptyHand(){
        if(headP == NULL){
            return false;
        }
        return true;
    }

    // [MÉTODO EXTERNO] Retona o player com maior pedra no começo
    int Player::PlayerPosition(Player p1,Player p2,Player p3,Player p4,Deck s, int numPlayers){
        int maxP1 = p1.largets();
        int maxP2 = p2.largets();
        int maxP3 = p3.largets();
        int maxP4 = p4.largets();

        if(numPlayers == 2){
            if(maxP1 > maxP2)
                return 1;
            else
                return 2;
        } else if (numPlayers == 3){
            if((maxP1 > maxP2) && (maxP1 > maxP3))
                return 1;
            else if ((maxP2 > maxP1) && (maxP2 > maxP3))
                return 2;
            else
                return 3;
        } else if (numPlayers == 4){
            if((maxP1 > maxP2) && (maxP1 > maxP3) && (maxP1 > maxP2))
                return 1;
            else if ((maxP2 > maxP1) && (maxP2 > maxP3) && (maxP2 > maxP4))
                return 2;
            else if ((maxP3 > maxP1) && (maxP3 > maxP2) && (maxP3 > maxP4))
                return 3;
            else    
                return 4;
            
        }
        return 0; 
    }

    // [MÉTODO EXTERNO] Consegue a posição da pedra, com base no jogador com a maior pedra.
    int Player::StonePosition(Player p,Player p1,Player p2,Player p3,Player p4,Deck s, int numPlayers){
        int playerMax = p.PlayerPosition(p1,p2,p3,p4,s,numPlayers);
        int position;
        int large = 0;
        cTile* curr1 = p1.headP;
        cTile* curr2 = p2.headP;
        cTile* curr3 = p3.headP;
        cTile* curr4 = p4.headP;
        vector<int> sums; 
        if(playerMax == 1){
            while(curr1 != NULL){
                sums.push_back(curr1->getR() + curr1->getL());
                curr1 = curr1->getNex();
            }
            int tam = sums.size();
            int aux;
            for(int i = 0; i < tam; i++){
                if(sums[i] > large){
                    large = sums[i];
                    aux = i;
                }
            }
            position = aux;
            return position;
        }

        if(playerMax == 2){
           while(curr2 != NULL){
                sums.push_back(curr2->getR() + curr2->getL());
                curr2 = curr2->getNex();
            }
            int tam = sums.size();
            int aux;
            for(int i = 0; i < tam; i++){
                if(sums[i] > large){
                    large = sums[i];
                    aux = i;
                }
            }
            position = aux;
            return position;
        }

        if(playerMax == 3){
            while(curr3 != NULL){
                sums.push_back(curr3->getR() + curr3->getL());
                curr3 = curr3->getNex();
            }
            int tam = sums.size();
            int aux;
            for(int i = 0; i < tam; i++){
                if(sums[i] > large){
                    large = sums[i];
                    aux = i;
                }
            }
            position = aux;
            return position;
        }

        if(playerMax == 4){
            while(curr4 != NULL){
                sums.push_back(curr4->getR() + curr4->getL());
                curr4 = curr4->getNex();
            }
            int tam = sums.size();
            int aux;
            for(int i = 0; i < tam; i++){
                if(sums[i] > large){
                    large = sums[i];
                    aux = i;
                }
            }
            position = aux;
            return position;
            
        }

        return 0;
    }

    // [MÉTODO INTERNO] Retorna o começo da mão do jogador
    cTile* Player::beginHand(){
        return headP;
    }

    // [MÉTODO INTERNO] Exibe as mão dos jogadores
    void Player::printHand(){
        cTile* leitor = headP;
        cout << "===========================" << endl;
        cout << " " << endl;
        while(leitor != NULL){
            cout << "| " << leitor->getR() << " | " << leitor->getL() << " |" << endl;
            leitor = leitor->getNex();
        }
    }

    // [MÉTODO EXTERNO] Printa os jogadores
    void Player::printPlayers(Player p1, Player p2, Player p3, Player p4, int numPlayers){
        switch(numPlayers){
            case 2:
                cout << " " << endl;
                cout << "===========================" << endl;
                cout << "player 1" << endl;
                p1.printHand();
                cout << " " << endl;
                cout << "===========================" << endl;
                cout << "player 2" << endl;
                p2.printHand();
                break;
            case 3:
                cout << " " << endl;
                cout << "===========================" << endl;
                cout << "player 1" << endl;
                p1.printHand();
                cout << " " << endl;
                cout << "===========================" << endl;
                cout << "player 2" << endl;
                p2.printHand();
                cout << " " << endl;
                cout << "===========================" << endl;
                cout << "player 3" << endl;
                p3.printHand();
                break;
            case 4:
                cout << " " << endl;
                cout << "===========================" << endl;
                cout << "player 1" << endl;
                p1.printHand();
                cout << " " << endl;
                cout << "===========================" << endl;
                cout << "player 2" << endl;
                p2.printHand();
                cout << " " << endl;
                cout << "===========================" << endl;
                cout << "player 3" << endl;
                p3.printHand();
                cout << " " << endl;
                cout << "===========================" << endl;
                cout << "player 4" << endl;
                p4.printHand();
                break;
        }
    }
    

// MÉTODOS DO BOARD

    // [MÉTODO INTERNO] Inicializa a lista
    Board::Board(){
        tip = NULL;
        qtElB = 0;
    }

    // [MÉTODO INTERNO] Retorna o valor da ponta direita (Em relação ao monitor)
    int Board::backTipR(){
        return tip->getR();
    }

    // [MÉTODO INTERNO] Retorna o valor da ponta esquerda (Em relação ao monitor)
    int Board::backTipL(){
        cTile* current = tip;
        while(current != NULL)
            current = current->getNex();
        return current->getL();
    }
    
    // [MÉTODO INTERNO] Insere a 1° pedra da partida 
    bool Board::insertStart(Player p, Deck s, int index){
        cTile* pt = new cTile(p.backRR(index), p.backLL(index));
        cTile* last = tip;

        pt->setTile(p.backRR(index),p.backLL(index));
        
        if(tip == NULL){
            tip = pt;
            return true;
        } else{
           while(last->getNex() != NULL)
                last = last->getNex();
            last->setNex(pt);
            pt->setPrev(last);
        }
        return true;
       
    }

  // [MÉTODO INTERNO] Insere uma pedra na 2º ponta do tabuleiro
    bool Board::insertEnd(Player p, Deck s, int index, bool spin){
     cTile* pt = new cTile(p.backRR(index), p.backLL(index));
        cTile* last = tip;
        if(spin == true){
           pt->setTile(p.backLL(index),p.backRR(index));
        } else {
            pt->setTile(p.backRR(index),p.backLL(index));
        }
        while(last->getNex() != NULL)
            last = last->getNex();
        last->setNex(pt);
        pt->setPrev(last);

        return true;
    }
    
    // [MÉTODO INTERNO] Insere uma pedra na 1º ponta do tabuleiro
    bool Board::insertBegin(Player p, Deck s, int index, bool spin){
        cTile* pt = new cTile(p.backRR(index), p.backLL(index));
        if(spin == true){
            pt->setTile(p.backLL(index), p.backRR(index));
        } else {
            pt->setTile(p.backRR(index),p.backLL(index));
        }
        pt->setNex(tip);
        tip = pt;
        return true;
    }

    // [METODO INTERNO] Descobre quem é o próximo jogador.
    int Board::NextPlayer(int turn, int numPlayers){
        switch(numPlayers){
            case 2:
                if(turn == 1){
                  turn = 2;
                  break;
                } else if(turn == 2){
                  turn = 1;
                  break;
                }
            case 3:
                if(turn == 1){
                  turn = 2;
                  break;
                }if(turn == 2){
                  turn = 3;
                  break;
                }if(turn == 3){
                   turn = 1;
                   break;
                }

            case 4:
                if(turn== 1){
                  turn = 2;
                  break;
                }if(turn == 2){
                  turn = 3;
                  break;
                }if(turn == 3){
                  turn = 4;
                  break;
                }if(turn == 4){
                  turn = 1;
                  break; 
                }
        }
        return turn;
    }
    
    // [METODO INTERNO] Comparar pedra da mão com a da mesa
    bool Board::Tocompare(Deck s,Player p){
        cTile* curr = p.beginHand();
        int Tright = backTipR();
        int Tleft = backTipL();
        int i = 0;   

        while(curr != NULL){
            int right = p.backRR(i);  
            int left = p.backLL(i);
            curr = curr->getNex();
            i++;
            if(right == Tright || right == Tleft || left == Tright || left == Tleft){ 
                return true;
            }
        }
        return false;
    }

    // [MÉTODO INTERNO] Retorna a posição da pedra a ser jogada
    int Board::positionTile (Deck s, Player p){
        cTile* curr = p.beginHand();
        int Tright = backTipR();
        int Tleft = backTipL();
        int i = 0;   

        while(curr != NULL){
            int right = p.backRR(i);  
            int left = p.backLL(i);
            if(right == Tright || right == Tleft || left == Tright || left == Tleft){ 
                return i;
            }
            curr = curr->getNex();
            i++;
        }
        return -1;
    }

    // [MÉTODO INTERNO] Verifica se a pedra deve ser jogada no início ou no fim
    bool Board::beginEnd(Deck s, Player p){
        cTile* curr = p.beginHand();
        int Tright = backTipR();
        int i = 0;   

        while(curr != NULL){
            int right = p.backRR(i);  
            int left = p.backLL(i);
            curr = curr->getNex();
            i++;
            if(right == Tright || left == Tright){ 
                return true;
            }
        }
        return false;
    }

    // [MÉTODO INTERNO] Verifica se a pedra deve ser girada para ser jogada
    bool Board::shouldSpin(Deck s, Player p){
        cTile* curr = p.beginHand();
        int Tright = backTipR();
        int Tleft = backTipL();
        int i = 0;

        while(curr != NULL){
            int right = p.backRR(i);  
            int left = p.backLL(i);
            curr = curr->getNex();
            i++;
            if(right == Tright || left == Tleft){ 
                return true;
            } else {
                return false;
            }
        }
        return true;
    }

    // [MÉTODO EXTERNO] Faz o primeiro lance do jogo
    int Board::beginGame(int turn, int position,Player p1, Player p2, Player p3, Player p4, Deck s){
        if(turn == 1){
            insertStart(p1,s,position);
            p1.deleteTile(position);
        }
        if(turn == 2){
            insertStart(p2,s,position);
            p2.deleteTile(position);
        }
        if(turn == 3){
            insertStart(p3,s,position);
            p3.deleteTile(position);
        }
        if(turn == 4){
            insertStart(p4,s,position);
            p4.deleteTile(position);
        }
        return 0;
    }

    // [MÉTODO EXTERNO] Faz jogada por jogador
    int Board::round(int turn, int numPlayers, Deck s, Player p,Stock stock){
        int next = NextPlayer(turn,numPlayers);
        bool spin = shouldSpin(s,p);
        int index = positionTile(s,p);
        if(Tocompare(s,p)){
            if(beginEnd(s,p)){
                insertBegin(p,s,index,spin);
                p.deleteTile(index);
            } else {
                insertEnd(p,s,index,spin);
                p.deleteTile(index);
            }
        } else {
            if(p.stockToHand(stock))
                round(turn, numPlayers,s,p,stock);
            else{
                return -1;
            }
        }

        return next;
    }

    // [MÉTODO INTERNO] Soma pedras na mão e retorna a mão com menor valor de soma
    int Board::endGame(int numPlayers, Player p1, Player p2, Player p3, Player p4){
        int sum1 = 0;
        int sum2 = 0;
        int sum3 = 0;
        int sum4 = 0;
        cTile* curr1 = p1.beginHand();
        cTile* curr2 = p2.beginHand();
        cTile* curr3 = p3.beginHand();
        cTile* curr4 = p4.beginHand();
        if(numPlayers == 2){
            while(curr1 != NULL){
                sum1 = curr1->getR() + curr1->getL();
                curr1 = curr1->getNex();
            }
            while(curr2 != NULL){
                sum2 = curr2->getR() + curr2->getL();
                curr2 = curr2->getNex();
            }
            if(sum1 < sum2){
                return 1;
            } else {
                return 2;
            }
        }

        if(numPlayers == 3){
            while(curr1 != NULL){
                sum1 = curr1->getR() + curr1->getL();
                curr1 = curr1->getNex();
            }
            while(curr2 != NULL){
                sum2 = curr2->getR() + curr2->getL();
                curr2 = curr2->getNex();
            }
            while(curr3 != NULL){
                sum3 = curr3->getR() + curr3->getL();
                curr3 = curr3->getNex();
            }
            if((sum1 < sum2) && (sum1 < sum3)){
                return 1;
            } else if ((sum2 < sum1) && (sum2 < sum3)) {
                return 2;
            } else {
                return 3;
            }
        }

        if(numPlayers == 4){
            while(curr1 != NULL){
                sum1 = curr1->getR() + curr1->getL();
                curr1 = curr1->getNex();
            }
            while(curr2 != NULL){
                sum2 = curr2->getR() + curr2->getL();
                curr2 = curr2->getNex();
            }
            while(curr3 != NULL){
                sum3 = curr3->getR() + curr3->getL();
                curr3 = curr3->getNex();
            }
            while(curr4 != NULL){
                sum4 = curr4->getR() + curr4->getL();
                curr4 = curr4->getNex();
            }
            if((sum1 < sum2) && (sum1 < sum3) && (sum1 < sum4)){
                return 1;
            } else if ((sum2 < sum1) && (sum2 < sum3) && (sum2 < sum4)) {
                return 2;
            } else if ((sum3 < sum1) && (sum3 < sum2) && (sum3 < sum4)){
                return 3;
            } else {
                return 4;
            }
        }
    }

    //[MÉTODO EXTERNO] Exibe o tabuleiro
    void Board::printBoard(){
        cTile* leitor = tip;
        cout << " " << endl;
        cout << "===========================" << endl;
        cout << "Tabuleiro: " << endl;
        cout << "===========================" << endl;

        while(leitor != nullptr){
            cout << " | " << leitor->getR() << " | " << leitor->getL() << " | ";
            leitor = leitor->getNex();
        }
    }

// MÉTODOS DO GAME

    // [MÉTODO EXTERNO] Tenta simular as jogadas e determinar vencedor
    void Game::moves(int turn, int numPlayers, Deck s, Player p1, Player p2, Player p3, Player p4, Stock stock, Board table){
        int done = 0;
        int winner = 0;
        if(numPlayers == 2){
            while((p1.emptyHand()) && (p2.emptyHand()) && (done != -1)){
                if(turn == 1){
                    done = table.round(turn, numPlayers, s, p1, stock);
                    turn = table.NextPlayer(turn,numPlayers);
                } else if (turn == 2){
                    done = table.round(turn, numPlayers, s, p2, stock);
                    turn = table.NextPlayer(turn,numPlayers);
                }
            }
            if(!p1.emptyHand()){
                cout << " Jogador 1 venceu" << endl;
                return;
            } else if (!p2.emptyHand()){
                cout << " Jogador 2 venceu" << endl;
                return;
            } else if (done == -1){
                winner = table.endGame(numPlayers,p1,p2,p3,p4);
                if(winner == 1){
                    cout << " Jogador 1 venceu" << endl;
                    return;
                } else{
                    cout << " Jogador 2 venceu" << endl;
                    return;
                }
            }


        }

        if(numPlayers == 3){
            while((p1.emptyHand()) && (p2.emptyHand()) && (p3.emptyHand())){
                if(turn == 1){
                    turn = table.round(turn, numPlayers, s, p1, stock);
                } else if (turn == 2){
                    turn = table.round(turn, numPlayers, s, p2, stock);
                }else if (turn == 3){
                    turn = table.round(turn, numPlayers, s, p3, stock);
                }
            }
            if(!p1.emptyHand()){
                cout << " Jogador 1 venceu" << endl;
                return;
            } else if (!p2.emptyHand()){
                cout << " Jogador 2 venceu" << endl;
                return;
            } else if (!p3.emptyHand()){
                cout << " Jogador 3 venceu" << endl;
                return;
            }
        }

        if(numPlayers == 4){
            while((p1.emptyHand()) && (p2.emptyHand()) && (p3.emptyHand()) && (p4.emptyHand())){
                if(turn == 1){
                    turn = table.round(turn, numPlayers, s, p1, stock);
                } else if (turn == 2){
                    turn = table.round(turn, numPlayers, s, p2, stock);
                }else if (turn == 3){
                    turn = table.round(turn, numPlayers, s, p3, stock);
                } else if (turn == 4){
                    turn = table.round(turn, numPlayers, s, p4, stock);
                }
            }
            if(!p1.emptyHand()){
                cout << " Jogador 1 venceu" << endl;
                return;
            } else if (!p2.emptyHand()){
                cout << " Jogador 2 venceu" << endl;
                return;
            } else if (!p3.emptyHand()){
                cout << " Jogador 3 venceu" << endl;
                return;
            } else if (!p4.emptyHand()){
                cout << " Jogador 3 venceu" << endl;
                return;
            }
        }
    }