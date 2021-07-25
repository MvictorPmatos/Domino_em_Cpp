/*[LEIA AQUI]:
        É DE EXTREMA IMPORTÂNCIA QUE LEIAM O DOCUMENTO GUIA DO CÓDIGO PARA QUE A GENTE 
        NÃO ACABE SE DESORGANIZANDO MUITO NA CRIAÇÃO DO PROGRAMA.
        O LINK PARA O DOCUMENTO É: https://docs.google.com/document/d/1Ts9gMTCnvewz2krlvY3bWzMoD98BHiAKzk4NCll4PTU/edit
*/ 

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "tadGame.h"

using namespace std;

int main(){
    int numPlayers; // Guardará o número de jogadores
    Deck s; // Cria um objeto do tipo Deck
    Player p, p1, p2, p3, p4; // Cria 5 objetos do tipo player, 4 são para os 4 jogadores e 1 para chamar o método que utiliza os 4 objetos players
    Board Table; // Cria um objeto do tipo board
    Stock stock; // Cria um objeto do tipo stock
    Game game; // Cria um objeto do tipo game
    

    s.shuffle(); // Chama o método Shuffle que cria os valores e insere nas pedras de forma "embaralhada"

    
    cout << " " << endl;
    cout << "===========================" << endl;
    cout << "Numero de jogadores: ";
    cin >> numPlayers; //Visualização do número de jogadores e inserção do mesmo
    cout << "===========================" << endl;

    
    switch(numPlayers){ // Chamada para criação e inserção de pedras nos jogadores
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
    
    stock.insertStock(s, numPlayers); // Criação do cava
    
    p.printPlayers(p1,p2,p3,p4, numPlayers); // Printa a mão dos jogadores
    stock.printStock(); // Printa o cava
   
    int turn = p.PlayerPosition(p1,p2,p3,p4,s, numPlayers); // Saber qual o jogador com a maior peça.
    cout << "Jogador numero: " << turn << " ";
    int position = p.StonePosition(p,p1,p2,p3,p4,s, numPlayers); // Saber qual é a maior pedra na mão do jogador encontrado anteriormente, fiz isso pois não consegui dar return de dois int.
    cout <<"tem a maior pedra, na posicao: " << position  << endl;
    cout << "===========================" << endl;

    Table.beginGame(turn,position,p1,p2,p3,p4,s); // Inicia o jogo colocando a maior pedra no tabuleiro
    turn = Table.NextPlayer(turn,numPlayers); // Turn armazena o próximo jogador depois do início 
   

    if (turn == 1){                                     // Essas condicionais servem para fazer uma segunda jogada
        turn = Table.round(turn,numPlayers,s,p1,stock);
    } else if (turn == 2){
        turn = Table.round(turn,numPlayers,s,p2,stock);
    } else if (turn == 3){
        turn = Table.round(turn,numPlayers,s,p3,stock);
    } else if (turn == 4){
        turn = Table.round(turn,numPlayers,s,p4,stock);
    }
        
    
    //game.moves(turn, numPlayers, s, p1, p2, p3, p4, stock,Table); // Chama as jogadas até condição de vitória

    Table.printBoard(); // Printa o tabuleiro na tela

    return 0;
}