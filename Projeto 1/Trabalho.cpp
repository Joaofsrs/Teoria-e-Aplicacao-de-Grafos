#include "Trabalho.h"

ifstream fin("soc-dolphins.mtx");

vector <vector <int> > cliques;
vector <vector <int> > grafo;

int vertices;
int arestas;

/**
 *    @brief A funcao imprime_grafo imprime os vertices, seus graus e seus adjacentes
 */
void imprime_grafo(){
    cout << "----Vertices----" << endl  << endl;
    for(int i = 1; i < grafo.size(); i++){
        cout << "Vertice " << i << " : ";
        for(int j = 0; j < grafo[i].size(); j++){
            if(j == grafo[i].size() - 1){
                cout << grafo[i].at(j);
            }else{
                cout << grafo[i].at(j) << " - ";
            }          
        }
        cout << endl << "Grau V(" << i << "):" << grafo[i].size() << endl;
        cout << endl;
    }
}

/**
 *  @brief A funcao imprime_cliques imprime o numero de cliques existentes e tambem imprime os cliques e seus tamanhos
 */
void imprime_cliques(){
    cout << "----Cliques Maximais----" << endl << endl;
    cout << "Total de cliques: " << cliques.size() << endl;
    for(int i = 0; i < cliques.size(); i++){
        cout << "Clique: " << i+1 << endl;
        cout << "Tamanho do clique: " << cliques[i].size() << endl;
        for(int j = 0; j < cliques[i].size(); j++){
            cout << cliques[i][j] << " ";
        }

        cout << endl << endl;
    }
}

/**
 *   @brief A funcao intersecao verifica se existe um vertice do v1 em v2
 */
vector <int> intersecao(vector <int> v1, vector <int> v2){
    vector <int> aux1;

    sort(v2.begin(), v2.end());

    for(auto i : v1){
        if(binary_search(v2.begin(), v2.end(), i)){
            aux1.pb(i);
        }
    }
    return aux1;
}

/**
 *    @brief A funcao uniao insere o ultimo valor de v2 em v1 usando a funcao push_back
 */
vector <int> uniao(vector <int> v1, vector <int> v2){
    v1.pb(v2.back());
    return v1;
}

/**
 *    @brief A funcao remove_vertice remove um elemento de v1 caso seja igual ao ultimo elemento de v2
 */
vector <int> remove_vertice(vector <int> v1, vector<int> v2){
    vector <int> aux;
    aux = v1;

    for(int i = 0; i < aux.size(); i++){
        if(aux[i] == v2.back()){
            aux.erase((aux.begin() + i));
        }
    }

    return aux;
}

/**
 *    @brief A funcao imprime_coeficiente imprime o coeficiente de aglomeracao do vertice e o coeficiente de aglomeracao medio do grafo
 */
void imprime_coeficiente(vector <double> CAG){
    double CMAG = 0;

    cout << "----Coeficiente de Aglomeracao----" << endl << endl;
    for(int j = 0; j < CAG.size(); j++){
        cout << "Vertice: " << j + 1 << " - " << CAG.at(j) << endl;
        CMAG += CAG.at(j);
    }
    cout << endl << "Coeficiente de Aglomeracao Medio do Grafo: ";
    cout << (double)CMAG/vertices << endl;
}

/**
 *    @brief A funcao coeficiente_de_aglomeracao recebe um vetor com todos os triangulos possiveis e faz o calculo do coeficiente de aglomeracao
 */
void coeficiente_de_aglomeracao(vector <int> vtriangulos){
    vector <double> CAG;
    double aux, aux1;
    int contador = 0;

    for(int i = 1; i < vtriangulos.size(); i++){
        aux = grafo[i].size();                                           // Faz o calculo do coeficiente de aglomeracao
        aux1 = (aux * (aux - 1))/2;                                      // (n * (n - 1))/2
        if((double)(aux = vtriangulos[i]/aux1) > 0) CAG.pb(aux);         
        else{
            aux = 0;
            CAG.pb(aux);
        }
    }
    imprime_coeficiente(CAG);
}

/**
 *    @brief Verifica se o triangulo ja existe no vetor de triangulos (para nao colocar triangulos repetidos).
 */
bool verifica(vector <int> triangulo, vector <vector<int>> japassou){
    if(japassou.size() == 0){
        return true;
    }

    for(int i = 0; i < japassou.size(); i++){
        if(triangulo == japassou[i]){
            return false;
        }
    }

    return true;
}
/**
 *    @brief Funcao que verifica quantos triangulos tem um vertice.
 */
void verifica_triangulos(vector <vector<int>> japassou){
    vector<int> vaux;
    
    vaux.resize(vertices + 1);

    for(int i = 0; i < japassou.size(); i++){           // Loop que percorre os vertices verificando 
        for(int j = 0; j < japassou[i].size(); j++){    // quantos triangulos tem em cada um.
            for(int k = 1; k <= vertices; k++){
                if((japassou[i][j] == k) == true){
                    vaux[k]++;
                }
            }
        }
    }
    
    coeficiente_de_aglomeracao(vaux);        // Envia um vetor que contem quantos triangulos tem cada vertice.
}

/**
 *    @brief Funcao que calcula os triangulos do grafo a partir dos cliques. Para calcular o coeficiente de aglomeracao.
 */

void triangulos(){
    int contador = 0;
    vector <int> triangulo;
    vector <int> ntriangulo;
    vector <vector <int> > japassou;
    
    triangulo.resize(vertices + 1);
    ntriangulo.resize(vertices + 1);

    for(int i = 0; i < cliques.size(); i++){      // Loop que verifica os triangulos de cada clique.

        if(cliques[i].size() == 3){                                         // Clique com três vertices.
            triangulo = {cliques[i][0], cliques[i][1], cliques[i][2]};      // Fica trocando todos os valores possiveis dos triangulos 
            sort(triangulo.begin(), triangulo.end());                       // Ordena os valores do triangulo
            if(verifica(triangulo, japassou) == true){                      // Verifica se ele ja foi contabilizado
                japassou.pb(triangulo);
            }

        }else if(cliques[i].size() == 4){        // Clique com quatro vertices.
            for(int j = 0; j < 4; j++){
                for(int w = 0; w < 4; w++){
                    for(int l = 0; l < 4; l++){
                        if(j != w and j != l and w != l){
                            triangulo = {cliques[i][j], cliques[i][w], cliques[i][l]}; // Fica trocando todos os valores possiveis dos triangulos 
                            sort(triangulo.begin(), triangulo.end());                  // Ordena os valores do triangulo
                            if(verifica(triangulo, japassou) == true){                 // Verifica se ele ja foi contabilizado
                                japassou.pb(triangulo);
                            }  
                        }  
                    }
                }
            }

        }else if(cliques[i].size() == 5){       // Clique com cinco vertices.
            for(int j = 0; j < 5; j++){
                for(int k = 0; k < 5; k++){
                    for(int l = 0; l < 5; l++){
                        if(j != k and j != l and k != l){
                            triangulo = {cliques[i][j], cliques[i][k], cliques[i][l]};  // Fica trocando todos os valores possiveis dos triangulos
                            sort(triangulo.begin(), triangulo.end());                   // Ordena os valores do triangulo
                            if(verifica(triangulo, japassou) == true){                  // Verifica se ele ja foi contabilizado
                                japassou.pb(triangulo);
                            }
                        }
                    }
                }
            }
        }
    }

    verifica_triangulos(japassou);  // Manda os triangulos para verificar quantos triangulos tem o vertice.
}

/**
 *  @brief Funcao que executa o algoritmo de BronKerbosch descricao do algoritmo:
 *       algoritmo BronKerbosch1 (R, P, X) é 
 *        se P e X são ambos vazios, então 
 *          relatar R como um clique máximo
 *        para cada vértice v  em  P  do 
 *            BronKerbosch( R ⋃ { v }, P ⋂ N ( v ), X ⋂ N ( v ))
 *            P  : = P \ { v }
 *            X  : = X ⋃ { v }
 */
void BronKerbosch1(vector<int> R, vector<int> P, vector<int> X){
    vector<int> nR, nX, nP;

    if(P.empty() && X.empty()){
        cliques.pb(R);
    }else{
        vector <int> v2(1);
        while(!P.empty()){
            v2.front() = P.back();
            nR = uniao(R, v2);
            nP = intersecao(P, grafo[v2.front()]);
            nX = intersecao(X, grafo[v2.front()]);
            BronKerbosch1(nR, nP, nX);
            P = remove_vertice(P, v2);
            X = uniao(X, v2);         
        }
    }

}

/** 
 *    @brief Funcao que inicia o vetor de vertices e manda para a funcao que executa o algoritmo de BronkerBosch
 */
void BronKeborsch0(){
    vector <int> R, P, X;
    
    for(int i = 1; i <= vertices; i++){
        P.pb(i);
    }   

    BronKerbosch1(R, P, X);
    R.clear();
    P.clear();
    X.clear();
}

/**
 *    @brief Funcao que retira os valores do arquivo ".mtx" e insere no grafo.
 */

void criar_grafo(){
    int verticeb, verticea;
    
    while(fin.peek() == '%'){
        fin.ignore(2048, '\n');
    }
    
    fin >> verticea >> verticeb >> arestas;
    vertices = verticea;

    grafo.resize(vertices + 1);

    while(arestas--){
        fin >> verticea >> verticeb;

        grafo[verticea].pb(verticeb);
        grafo[verticeb].pb(verticea);
    }
}