#include "Trabalho.h"

using namespace std;

vector <vector <pair <string, int>>> Grafo;
vector <string> sempre;
vector <vector <pair <string, int>>> Criticos;
map <string, bool> visited;
map <string, bool> visited2;
map <string, int> lugar;
vector <string> top;
vector <vector <pair <string, int>>> tres_maiores;

/**
 *    @brief A funcao pega as informacoes do arquivo .txt e coloca em uma estrutura.
 */

void criar_grafo(){
    string materia;
    int credito;
    int i = 32;

    ifstream fin("Grafo.txt");  // Abre o arquivo txt.

    while(i--){
        fin.ignore(2048, '\n'); // Ignora as linhas que nao fazem parte do grafo.
    }

    Grafo.resize(32);
    for(int i = 0; i < Grafo.size(); i++){  // Pega a lista de adjacencia do arquivo e coloca em uma estrutura.
        fin >> materia >> credito;          
        Grafo[i].pb(mp(materia, credito));
        lugar[materia] = i;
        visited[materia] = false;           // Marca os lugares de um map como 'false' para evitar erros na busca em profundidade.
        visited2[materia] = false;
        if(i != Grafo.size()-1){
            while(fin.peek() != '\n'){
                fin >> materia >> credito;
                Grafo[i].pb(mp(materia, credito));
            }
        }
    }

    fin.close();
}

/**
 *    @brief Aplicacao do algoritmo de busca em profundidade, para a execucao da ordenacao topologica.
 */

void dfs(string v, int i){
    vector <pair<string , int> > u = Grafo[i]; 
    visited[v] = true;
    for(int w = 0; w < Grafo[i].size(); w++){
        if(!visited[u[w].first]){
            dfs(u[w].first, lugar[u[w].first]);  // Tchama a dfs, caso o vertice nao esteja verificado ainda.
        }
    }

    top.pb(v);    // Insere em uma pilha os vertices visitados que nao possuem mais nenhum vertice filho.
}

/**
 *    @brief Funcao inicia uma ordenacao topologica chamando uma busca em profundidade nos vertices iniciais.
 */

void ord_topologica(){
    for (int i = 0; i < 32; i++){
        if (!visited[Grafo[i][0].first]){
            dfs(Grafo[i][0].first, i); 
        }
    }

    reverse(top.begin(), top.end());
}


/**
 *    @brief Funcao que imprime na tela a ordenação topologica.
 * 
 */

void print_topologica(){
    for(int i = 0; i < 32 ; i++){
        cout << top[i] << endl;
    }
}

/**
 *    @brief Funcao que separa os vertices sem pre-requisito para analise dos caminhos criticos.
 */

void cria_caminhos(string str){
    int ocr = 0;
    for(int i = 0 ; i < Grafo.size(); i++){
        for(int k = 0; k < Grafo[i].size(); k++){
            if(str == Grafo[i][k].first){   // Calcula a quantidade de ocorrencias da mesma disciplina para checar pre-requisitos.
                ocr++;
            }
        }  
    }

    if(ocr == 1){       // Se o numero for 1 eh que a disciplina nao tem pre-requisito.
        sempre.pb(str);
    }
}
/**
 *    @brief Funcao manda os vertices para analise de pre-requisito.
 */

void manda_pra_cria(){
    for(int i = 0; i < 32; i++){
        string aux = Grafo[i][0].first;
        cria_caminhos(aux);
    }
}


/**
 *    @brief Funcao recursiva que caminha em profundidade o grafo marcando os caminhos criticos.
 */

void caminha(string v, int i, int y){
    vector <pair<string, int>> u = Grafo[i];
    visited2[v] = true;
    for(int w = 0; w < Grafo[i].size(); w++){
        if(!visited2[u[w].first]){
            caminha(u[w].first, lugar[u[w].first], y);  //A unica coisa que diferencia a funcao caminha da funcao dfs e o break, pois usamos ele pra percorrer apenas um caminho critico 
            break;                                      //chegando ao final, no vertice mais profundo ele para de rodar a recursiva, nao pegando outro caminho possivel, assim retornando com um dos caminhos criticos.
        }
    }
    int aux = lugar[v];
    pair<string, int> auxp = mp(v, Grafo[aux][0].second);
    Criticos[y].pb(auxp);
}

/**
 *    @brief funcao usada para achar todos os caminhos criticos possiveis 
 */

void chama_caminha(){
    int y = 0;
    Criticos.resize(40);
    for(int i = 0; i < sempre.size(); i++){
        int w = lugar[sempre[i]];
        while(!visited2[sempre[i]]){
            string aux = sempre[i];
            caminha(aux, w, y);
            for(int q = 0; q < 32; q++){                //Aqui ele coloca como false todos os elementos ja verificados.
                visited2[Grafo[q][0].first] = false;
            }
            string j = sempre[i];
            for(int q = 0; q < y+1; q++){               //Aqui colocamos true em todos os ultimos elementos visitados, tirando assim umas das os vertices mais na ponta do grafo, e assim forcando a funcao a percorres outros caminhos criticos.
                int f = Criticos[q].size() - 1;
                string k = Criticos[q][f].first;
                if(j == k){
                    visited2[Criticos[q][0].first] = true;
                }
            }
            y++;
        }
        for(int q = 0; q < 32; q++){
            visited2[Grafo[q][0].first] = false;
        }
    }
    for(int i = 0; i < 39; i++){
        reverse(Criticos[i].begin(), Criticos[i].end());
    }
    caminhocritico();
}


/**
 *    @brief Funcao que garante que nenhum caminho critico possua vertices iguais.
 */

bool check(vector <vector <pair <string, int>>> tres, vector <pair <string, int>> v1){
    for(int i = 0; i < tres.size(); i++){
        for(int j = 0; j < tres[i].size(); j++){
            for(int k = 0; k < v1.size(); k++){
                if(v1[k].first == tres[i][j].first){  // Analisa cada vertice para garantir que nenhum vertice repetido seja colocado nos caminhos criticos.
                    return false;
                }
            }
        }
    }

    return true;
}


/**
 *    @brief Funcao para escolher a forma de ordenacao para os pontos criticos.
 */


bool ord(pair <int,int> i, pair <int,int> j){
    return j.first < i.first;
}

/**
 *    @brief Funcao avalia cada caminho para verificar os maiores e que nao sao repetidos.
 */

void caminhocritico(){
    vector <ii> ValordosCriticos(38, mp(0, 0));

    for(int i = 0; i < 38; i++){
        for(int j = 0; j < Criticos[i].size(); j++){
            ValordosCriticos[i].first += Criticos[i][j].second; // Conta os pesos de cada disciplina para saber os caminhos mais longos.
        }
        ValordosCriticos[i].second = i;
    }
    
    sort(ValordosCriticos.begin(), ValordosCriticos.end(), ord); // Ordena para ver quais sao os maiores caminhos.

    while(tres_maiores.size() < 3){  // Coloca os tres maiores caminhos dentro do vetor.
        for(int i = 0; i < ValordosCriticos.size(); i++){
            if(tres_maiores.empty()){ // Se nao possuir nenhum, coloca o primeiro.
                tres_maiores.pb(Criticos[ValordosCriticos[i].second]);
            }else{
                if(check(tres_maiores, Criticos[ValordosCriticos[i].second])){ // Checa para ver se nenhum vertice se repete nos caminhos criticos ja colocados no vetor.
                    tres_maiores.pb(Criticos[ValordosCriticos[i].second]);
                }
            }
        }
    }
}

void print_caminhoscriticos(){
    cout << "-----Tres maiores caminhos criticos-----" << endl;
    for(int i = 0; i < 3; i++){
        cout << i+1 << " - ";
        for(int j = 0; j < tres_maiores[i].size();j++){
            cout << tres_maiores[i][j].first << " ";
        }
        cout << endl;
    }
}

/**
 *    @brief Funcao que cria o arquivo .dot dos caminhos criticos.
 */

void criticos_png(){
    ofstream crit;

    crit.open("criticos.dot");

    crit << "digraph Cr {" << endl;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < tres_maiores[i].size(); j++){
            if(j != tres_maiores[i].size() - 1){
                crit << "    " << tres_maiores[i][j].first << " -> " << tres_maiores[i][j+1].first << "[" << "label=\"" << tres_maiores[i][j].second << "\",weight=\"" << tres_maiores[i][j].second << "\"];" << endl;
            }
        }
    }

    crit << "}";
    crit.close();
}

/**
 *    @brief Funcao que cria o arquivo .dot do grafo completo.
 */

void grafo_png(){
    ofstream ofs;

    ofs.open("digrafo.dot");

    ofs << "digraph P {" << endl;

    for(int i = 0; i < Grafo.size(); i++){
        if(Grafo[i].size() != 1){
            for(int j = 1; j < Grafo[i].size(); j++){
                ofs << "    " << Grafo[i][0].first << " -> " << Grafo[i][j].first << "[" << "label=\"" << Grafo[i][0].second << "\",weight=\"" << Grafo[i][0].second << "\"];" << endl;
            }
        }else{
            ofs << "    " << Grafo[i][0].first << ";" << endl;
        }
    }
    ofs << "}";
    ofs.close();
}

/**
 *    @brief Funcao que cria o arquivo .dot da ordenacao topologica.
 */

void topologica_png(){
    ofstream topo;

    topo.open("topologica.dot");

    topo << "digraph T {" << endl;
    topo << "    {" << endl << "       rank=same" << endl;
    topo << "       node [shape=circle]" << endl;
    topo << "       ";
    for(int i = 0; i < Grafo.size(); i++) topo << Grafo[i][0].first << " ";
    topo << endl;
    topo << "    }" << endl;
    
    for(int i = 0; i < Grafo.size(); i++){
        int aux = lugar[top[i]];
        if(Grafo[aux].size() != 1){
            for(int j = 1; j < Grafo[aux].size(); j++){
                topo << "    " << Grafo[aux][0].first << " -> " << Grafo[aux][j].first << "[" << "label=\"" << Grafo[aux][0].second << "\",weight=\"" << Grafo[aux][0].second << "\"];" << endl;
            }
        }else{
            topo << "    " << Grafo[aux][0].first << ";" << endl;
        }
    }
    

    topo << "}";
    topo.close();
}

/**
 *    @brief Funcao que cria o arquivo .png da ordenacao topologica a partir do arquivo .dot e executa.
 */

void mostra_topologica(){
    system("dot -Tpng topologica.dot -o topologica.png");
    system("display topologica.png");
}

/**
 *    @brief Funcao que cria o arquivo .png do grafo completo do curso a partir do arquivo .dot e executa.
 */

void mostra_grafo(){
    system("dot -Tpng digrafo.dot -o digrafo.png");
    system("display digrafo.png");
}

/**
 *    @brief Funcao que cria o arquivo .png dos caminhos criticos a partir do arquivo .dot e executa.
 */

void mostra_criticos(){
    system("dot -Tpng criticos.dot -o criticos.png");
    system("display criticos.png");
}

/**
 *    @brief Funcao que imprime na tela as disciplinas e o nome do curso.
 */

void print_disciplinas(){
    string achou;
    string query;

    ifstream fin("Grafo.txt"); 	// Abre o arquivo
    cout << "\tCiencia da Computacao" << endl;
    for(int i = 0; i < 32; i++){
        getline(fin, achou);    // Percorre o arquivo pegando os cursos.
        cout << achou << endl;
    }

    
    fin.close();
}