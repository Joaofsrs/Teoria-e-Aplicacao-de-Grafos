#include "Trabalho.h"

using namespace std;

int main(){
    int opcao;

    criar_grafo();
    ord_topologica();
    manda_pra_cria();
    chama_caminha();

    while(opcao != 0){
        cout << endl;
        cout << "1 - Digite 1 caso deseje imprimir nome e codigo das disciplinas e o nome do cruso" << endl;
        cout << "2 - Digite 2 caso deseje imprimir a topologica e os tres maiores caminhos criticos" << endl;
        cout << "3 - Digite 3 caso deseje criar os arquivos .dot e .png" << endl;
        cout << "0 - Digite 0 para sair" << endl << endl;

        cin >> opcao;
        switch(opcao){
            case 1 :
                print_disciplinas();
                cout << endl;
                break;

            case 2:
                cout << "\t Ordenacao Topologica" << endl;
                print_topologica();
                cout << endl;
                print_caminhoscriticos();
                cout << endl;
                break;

            case 3:
                criticos_png();
                topologica_png();
                grafo_png();
                mostra_grafo();
                mostra_topologica();
                mostra_criticos();
                cout << endl;
                break;

            case 0:
                break;
        }
    }
    return 0;
}