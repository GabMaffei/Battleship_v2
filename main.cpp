#include <iostream>
#include <windows.h> ///para usar as funções Sleep() e system()
#include <time.h> ///para usar a função time
#include <ctype.h> ///para transformar em maiúscula
#include <locale.h>
using namespace std;

/**ESSE JOGO NECESSITA DA SUA AJUDA
            - Permita que o usuário informe as coordenadas de lançamento do torpedo (tx e ty)
                - Se a coordenada escolhida for a de um navio mapa[tx][ty]=={2, 3, 4 ou 5} escreva o número 8 naquela posição.
                - Se a coordenada escolhida for a de um navio mapa[tx][ty]==0 escreva 7 no mapa naquela posição
                - Acertando ou não um torpedo deve ser gasto torpedos--
            - O jogo deve terminar quando todos os torpedos 15 forem gastos
            - Ao final informe quantos torpedos acertaram o alvo
            - Desafio: Informe todos os navios afundados (aqueles que foram acertados em todas as suas coordenadas)
*/

/**
    Batalha naval com matrizes

    legenda do mapa
        0 vazio
        2 navio de tamanho 2
        3 navio de tamanho 3
        4 navio de tamanho 4
        5 navio de tamanho 5
        7 torpedo errando o alvo
        8 torpedo acertando o alvo
*/
int main()
{
    cout << "Sejam bem-vindos a batalha das suas vidas!" << endl;
    Sleep(2000); ///esse comando serve para pausar por x milisegundos
    system("cls"); ///esse comando serve para limpar a tela.

    srand(time(NULL)); ///gerar uma nova semente


    ///criação e preenchimento padrão do mapa, será diferente no jogo final
                           ///1 2 3 4 5 6 7 8 9 10
    int mapa[12][12] = {    9,9,9,9,9,9,9,9,9,9,9,9,
                            9,0,0,0,0,0,0,0,0,0,0,9, ///1
                            9,0,0,0,0,0,0,0,0,0,0,9, ///2
                            9,0,0,0,0,0,0,0,0,0,0,9, ///3
                            9,0,0,0,0,0,0,0,0,0,0,9, ///4
                            9,0,0,0,0,0,0,0,0,0,0,9, ///5
                            9,0,0,0,0,0,0,0,0,0,0,9, ///6
                            9,0,0,0,0,0,0,0,0,0,0,9, ///7
                            9,0,0,0,0,0,0,0,0,0,0,9, ///8
                            9,0,0,0,0,0,0,0,0,0,0,9, ///9
                            9,0,0,0,0,0,0,0,0,0,0,9, ///10
                            9,9,9,9,9,9,9,9,9,9,9,9 };

    int px,py,pz; ///para posicionamento dos barcos
    int tx, ty; ///para posicionamento dos torpedos
    char eu; ///entrada do usuário
    int erro; ///essa variável vai ser zero enquanto não colidir (usada para verificar se o navio está em uma posição válida)
    bool cheats = false;

    int n2 = 0,n3 = 0,n4 = 0,n5 = 0,torpedos=0, acertos = 0;

    for (int navio=2;navio<6;navio++){ ///para inserir os navios no mapa
        do {
            px=rand()%10+1; ///escolhe aleatoriamente um valor de zero a nove e soma um
            py=rand()%10+1;
            pz=rand()%2; ///zero horizontal e 1 vertical

            erro=0; ///inicia o erro em zero

            for(int i=0; i<navio; i++){
                if (pz==0){ /// teste horizontal
                    if(mapa[px][py+i]!=0){
                        erro=1;
                    }
                } else {      /// teste vertical
                    if(mapa[px+i][py]!=0){
                        erro=1;
                    }
                }
            }
            //cout<<"x: "<<px<<"\ny: "<<py<<"\nz: "<<pz<<"\nerro: "<<erro<<"\n";
        } while (erro==1);
        ///inserção do barco naquela posição
        for(int i=0; i<navio; i++){
            if (pz==0){ /// teste horizontal
                mapa[px][py+i]=navio;
            } else {      /// teste vertical
                mapa[px+i][py]=navio;
            }
        }
    }

    ///o 1 do while deve ser trocado pela condição de fim de jogo
    while (torpedos != 15){
        setlocale(LC_ALL, "C");
        system("cls");
        ///IMPRESSÃO DO MAPA
        for(int linha=0; linha<12; linha++){
            if (linha==0){
                cout<<"  0123456789\n ";
            } else if (linha>=1 and linha<=10) {
                cout<<char(64+linha);
            } else {
                cout<<" ";
            }
            for(int coluna=0; coluna<12; coluna++){
                if(mapa[linha][coluna]==0){
                    cout<<" ";
                } else if (mapa[linha][coluna]==9){
                    cout<<char(219);
                } else if (mapa[linha][coluna]==7){
                    cout<<"-";
                } else if (mapa[linha][coluna]==8){
                    cout<<"+";
                } else { ///quando for testar substituir o COUT do else
                    if(cheats){
                        cout<<mapa[linha][coluna];
                    } else{
                        cout<<" ";
                    }
                }
            }
            cout<<"\n";
        }
        ///FIM DA IMPRESSÃO DO MAPA
        do{
            cout << "Insira a letra da linha: "; ///Entrada e verificação torpedo x (tx)
            cin >> eu;
            eu = toupper(eu);
            if(eu != 'A' && eu != 'B' && eu != 'C' && eu != 'D' && eu != 'E' && eu != 'F' && eu != 'G' && eu != 'H' && eu != 'I' && eu != 'J'){
                cout << "Por favor insira uma das letras: A B C D E F G H I J" << endl;
            } else{
                break;
            }
        } while(true);
        setlocale(LC_ALL, "Portuguese");
        erro = true;
        do{
            cout << "Insira o número da coluna: "; ///Entrada e verificação torpedo y (ty)
            cin >> tx;
            for(int num = 0; num < 10; num++){
                if(tx == num){
                    erro = false;
                    break;
                } else if (num == 9){
                    if(tx == 17 && eu == 'G'){
                        cout << "Códigos hábilitados!" << endl;
                        cheats = true;
                    } else{
                    cout << "Por favor digite um numero entre 0 e 9" << endl;
                    }
                }
            }
        } while(erro);
        torpedos++;
        tx++; ///Preparação TX
        if(eu == 'A'){ ///Preparação TY
            ty = 1;
        } else if (eu == 'B'){
            ty = 2;
        } else if (eu == 'C'){
            ty = 3;
        } else if (eu == 'D'){
            ty = 4;
        } else if (eu == 'E'){
            ty = 5;
        } else if (eu == 'F'){
            ty = 6;
        } else if (eu == 'G'){
            ty = 7;
        } else if (eu == 'H'){
            ty = 8;
        } else if (eu == 'I'){
            ty = 9;
        } else{
            ty = 10;
        }
        for(int navio = 2; navio < 6; navio++){
            if(mapa[ty][tx] == navio){
                mapa[ty][tx] = 8;
                acertos++;
            } else if(navio == 5){
                mapa[ty][tx] = 7;
            }
            if(mapa[ty][tx] == 8){
                if(navio == 2){
                    n2++;
                    break;
                } else if(navio == 3){
                    n3++;
                    break;
                } else if(navio == 4){
                    n4++;
                    break;
                } else if(navio == 5){
                    n5++;
                    break;
                }
            }
        }
    }
    if(n2 != 2 && n3 != 3 && n4 != 4 && n5 != 5){
        cout << "\nSeus torpedos acabaram. Você não afundou nenhum navio." << "\nVocê acertou " << acertos << " alvos.\n";
    } else{
        cout << "\nSeus torpedos acabaram." << "\nVocê acertou " << acertos << " alvos.\n";
    }
    if(n2 == 2){
        cout << "Parabéns!!! Você acertou o submarino!" << endl;
    }
    if(n3 == 3){
        cout << "Parabéns!!! Você acertou o contratorpedeiro!" << endl;
    }
    if(n4 == 4){
        cout << "Parabéns!!! Você acertou o navio-tanque!" << endl;
    }
    if(n5 == 5){
        cout << "Parabéns!!! Você acertou o porta-aviôes!" << endl;
    }
    system("pause");
    return 0;
}
