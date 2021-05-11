#include "Trabalho.h"

using namespace std;

vector< ii > Professor(100, mp(0,0));                       //Vetor de par que armazena o numero do professor e sua habilitação
vector< vi > Professore(100);                               //Vetor que armazena para quais escolas o professor deseja ir
vector< vi > Escola(50);                                    //Vetor que armazena as habilitações que a escola prefere

vector <bool> free_agent(100, true);                        //Vetor de booleanos para mostrar se os professores estão livres ou se já estão em alguma escola 
vector <pair<bool, bool>> vagas (50, mp(true, true));       //Vetor de par booleanos para saber se a escola está com as vagas preenchidas
vector <vector<pair<int, pair <int, int>>> > match(50);     //Vetor de vetor de par com inteiro e par de inteiros, para armazenar a escola, suas vagas caso tenha mais de uma, preferencia do professor, professor e escola.

void criar_grafo(){
    string str1;
    int prof = 0, esco = 0;
    
    ifstream fin("arquivo.txt");      // Abre o arquivo txt com as informacoes dos professores e escolas
    
    while(fin.peek() == '/'){
        fin.ignore(2048, '\n');
    }

    fin.ignore(2048, '\n');

    while(fin.peek() == '('){       // Loop que pega as informacoes dos professores no txt e armazena nos vetores
        int i;
        getline(fin, str1);
        string aux;
        int j = 0;
        for(i = 1; str1[i] != ','; i++){
            if(str1[i] != 'P'){
                aux[j] = str1[i];
                j++;
            }
        }

        int a = stoi(aux);
        aux = "NULL";
        j = 0;
        while(str1[i] != ')'){
            if(str1[i] >= '0' && str1[i] <= '9'){
                aux[j] = str1[i];
                j++;
            }
            i++;
        }

        int b = stoi(aux);
        aux = "NULL";
        Professor[prof].first = a;
        Professor[prof].second = b;
        j = 0;
        i++;
        
        while(str1[i] != ')'){
            
            if(str1[i] >= '0' && str1[i] <= '9'){
                aux[j] = str1[i];
                j++;
                
            }else if(str1[i] == ','){
                int auxp = stoi(aux);
                Professore[prof].pb(auxp);
                aux = "NULL";
                j = 0;
            }
            
            i++;
        }

        int auxp = stoi(aux);
        Professore[prof].pb(auxp);
        aux = "NULL";
        
        prof++;
    }
    fin.ignore(2048, '\n');
    
    while(fin.peek() == '/'){
        fin.ignore(2048, '\n');
    }
    
    while(fin.peek() == '('){           // Loop que pega as informacoes das escolas do txt e coloca nos vetores
        int i = 0, j = 0;
        getline(fin, str1);
        string aux = "NULL";
        while(str1[i] != ':'){
            i++;
        }

        while(str1[i] != '\0'){
            if(str1[i] >= '0' && str1[i] <= '9'){
                aux[j] = str1[i];
                j++;      
            }else if(str1[i] == ')'){
                int auxp = stoi(aux);
                Escola[esco].pb(auxp);
                aux = "NULL";
                j = 0;
            }
            i++;
        }
        esco++;
    }
    
}

void emparelhamento(){

    /* Criacao do vetor de pares das combinacoes de professor e escola*/
    
    for(int i = 0; i < 50; i++){
        if(Escola[i].size() == 2){
            match[i].resize(2, mp(0, mp(0, 0)));
        }else{
            match[i].resize(1, mp(0, mp(0, 0)));
        }
    }
    
    /*  Inicio do emparelhamento estavel */

    /*  Loop para preenchimento das primeiras vagas das ecolas com a habilitacao igual ao do professor */
    for(int i = 0; i < Professore.size(); i++){
        if(free_agent[i]){
            for(int j = 0; j < Professore[i].size(); j++){

                /* Verifica se o professor tem exatamente a habilitacao que a escola pede */

                if(vagas[Professore[i][j]-1].first == true && Escola[Professore[i][j]-1][0] == Professor[i].second){
                    match[Professore[i][j]-1][0] = mp(j+1, mp(i, (Professore[i][j]-1)));
                    vagas[Professore[i][j]-1].first = false;
                    free_agent[i] = false;
                    break;
                    
                }
                
                /*  Analisa se existe algum professor com a preferencia maior querendo a mesma escola. 
                    Caso exista, encontra uma nova escola para o professor.
                */
               
                else if(!(vagas[Professore[i][j]-1].first) && j+1 < match[Professore[i][j]-1][0].first && Escola[Professore[i][j]-1][0] == Professor[i].second){
                    int w = i;
                    i = match[Professore[i][j]-1][0].second.first;
                    match[Professore[w][j]-1][0] = mp(j+1, mp(w, Professore[w][j]-1));
                    free_agent[w] = false;
                    free_agent[i] = true;
                    break;
                }
            } 
        }
    }

    /*  Loop para preenchimento das segundas vagas das escolas com a habilitacao do professor igual ao da escola */

    for(int i = 0; i < Professore.size(); i++){
        if(free_agent[i]){
            for(int j = 0; j < Professore[i].size(); j++){

                /* Verifica se o professor tem exatamente a habilitacao que a escola pede */

                if(Escola[Professore[i][j]-1].size() == 2){
                    if(vagas[Professore[i][j]-1].second == true && Escola[Professore[i][j]-1][1] == Professor[i].second){
                        match[Professore[i][j]-1][1] = mp(j+1, mp(i, (Professore[i][j]-1)));
                        vagas[Professore[i][j]-1].second = false;
                        free_agent[i] = false;
                        break;

                    }
                    
                    /*  Analisa se existe algum professor com a preferencia maior querendo a mesma escola. 
                        Caso exista, encontra uma nova escola para o professor. 
                    */

                    else if(!(vagas[Professore[i][j]-1].second) && j+1 < match[Professore[i][j]-1][1].first && Escola[Professore[i][j]-1][1] == Professor[i].second){
                        int w = i;
                        i = match[Professore[i][j]-1][1].second.first;
                        match[Professore[w][j]-1][1] = mp(j+1, mp(w, Professore[w][j]-1));
                        free_agent[w] = false;
                        free_agent[i] = true;
                        break;
                    }
                }
            } 
        }
    }

    /*  Loop para preenchimento da primeira vaga de uma escola, caso o professor tenha uma habilitacao maior do que a escola pede */

    for(int i = 0; i < Professore.size(); i++){
        if(free_agent[i]){
            for(int j = 0; j < Professore[i].size(); j++){

                /* Verifica se o professor eh qualificado para ser alocado na escola */
                if(vagas[Professore[i][j]-1].first == true && Escola[Professore[i][j]-1][0] < Professor[i].second){
                    match[Professore[i][j]-1][0] = mp(j+1, mp(i, (Professore[i][j]-1)));
                    vagas[Professore[i][j]-1].first = false;
                    free_agent[i] = false;
                    break;                
                }
            } 
        }
    }


    for(int i = 0; i < Professore.size(); i++){
        if(free_agent[i]){
            for(int j = 0; j < Professore[i].size(); j++){

                /* Verifica se o professor eh qualificado para ser alocado na escola */
                if(Escola[Professore[i][j]-1].size() == 2){
                    if(vagas[Professore[i][j]-1].second == true && Escola[Professore[i][j]-1][1] < Professor[i].second){
                        match[Professore[i][j]-1][1] = mp(j+1, mp(i, (Professore[i][j]-1)));
                        vagas[Professore[i][j]-1].second = false;
                        free_agent[i] = false;
                        break;
                    }
                }
            }
        }
    }

    print_emparelhamento();

}

void emparelhamento_maximo(){    

    /*  
        Nessa funcao nos alocamos os professores mesmo sem esses professores darem preferencia para escola, 
        apenas para ocupar o maximo de vagas seguindo os requisitos das escolas.
    */

    /*   Esse for, esta verificando se o professor esta livre, caso esteja, ele eh alocado para uma escola que não contem professor    */

    for(int i = 0; i < Professore.size(); i++){
        if(free_agent[i]){
            for(int j = 0; j < match.size(); j++){
                if(Escola[j].size() == 2){
                    if((match[j][0].first == 0) && (match[j][1].first == 0)){
                        if(vagas[j].first == true && Escola[j][0] <= Professor[i].second){
                            match[j][0] = mp(-1 , mp(i, (j)));
                            vagas[j].first = false;
                            free_agent[i] = false;
                            break;

                        }else if(vagas[j].second == true && Escola[j][1] <= Professor[i].second){
                            match[j][1] = mp(-1 , mp(i, (j)));
                            vagas[j].second = false;
                            free_agent[i] = false;
                            break;
                        }
                    }
                }else{
                    if(match[j][0].first == 0){
                        if(vagas[j].first == true && Escola[j][0] <= Professor[i].second){
                            match[j][0] = mp(-1 , mp(i, (j)));
                            vagas[j].first = false;
                            free_agent[i] = false;
                            break;
                        }
                    }
                }
            }
        }
    }

    /*
        Esse for preenche as vagas que estão vazias, assim preenchendo o maximo de vagas possível, já que com o for anterior temos a 
        certeza de que não existe mais escolas sem professor
    */

    for(int i = 0; i < Professore.size(); i++){
        if(free_agent[i]){
            for(int j = 0; j < match.size(); j++){
                if(Escola[j].size() == 2){
                    if(vagas[j].first == true && Escola[j][0] <= Professor[i].second){
                        match[j][0] = mp(-1 , mp(i, (j)));
                        vagas[j].first = false;
                        free_agent[i] = false;
                        break;
                    }else if(vagas[j].second == true && Escola[j][1] <= Professor[i].second){
                        match[j][1] = mp(-1 , mp(i, (j)));
                        vagas[j].second = false;
                        free_agent[i] = false;
                        break;
                    }
                }else{
                    if(vagas[j].first == true && Escola[j][0] <= Professor[i].second){
                        match[j][0] = mp(-1 , mp(i, (j)));
                        vagas[j].first = false;
                        free_agent[i] = false;
                        break;
                    }
                }
            }
        }
    }

    print_maximo();

    cout << endl;
    
}

void print_emparelhamento(){
    int cont = 0;

    /* Mostra na tela as combinacoes de professor e escola pos emparelhamento estavel*/

    cout << "Emparelhamento estavel: " << endl;
    for(int i = 0; i < match.size(); i++){
        if(match[i].size() == 1){
            if(match[i][0].first == 0){
                cout << "Escola - " << i+1  << " | " << "Sem Professor" << endl;

            }else{
                cout << "Escola - " << i+1  << " | " << "Professor - " << match[i][0].second.first+1 << endl;
            }
        }else{
            if((match[i][0].first == 0) && (match[i][1].first == 0)){
                cout  << "Escola - " << i+1  << " | " << "Sem Professor  |" << " Sem Professor" << endl;

            }else if((match[i][0].first != 0) && (match[i][1].first == 0)){
                cout  << "Escola - " << i+1  << " | " << "Professor - " << match[i][0].second.first+1;
                cout  << " | " << "Sem Professor" << endl;

            }else if((match[i][0].first == 0) && (match[i][1].first != 0)){
                cout  << "Escola - " << i+1  << " | " << "Sem Professor ";
                cout  << " | " << "Professor - " << match[i][1].second.first+1 << endl;

            }else{
                cout  << "Escola - " << i+1  << " | " << "Professor - " << match[i][0].second.first+1;
                cout  << " | " << "Professor - " << match[i][1].second.first+1 << endl;
            }
        }   
    }
    
    /* Professores sem escola*/
    
    cout << endl;
    cout << "Professores que ficaram sem escola pos emparelhamento estavel: " << endl;
    for(int i = 0; i < 100; i++){
        if(free_agent[i]){
            cout << "Professor(" << i+1 << ")" << endl;
            cont++;
        }
    }

    cout << endl;

    /* Escolas que ficaram sem professor */

    cout << "Escolas que ficaram vazias pos emparalhemento estavel: " << endl;
    for(int i = 0; i < Escola.size(); i++){
        if(Escola[i].size() == 2 && match[i][0].first == 0 && match[i][1].first == 0){
            cout << "Escola(" << i+1 << ")" << endl;
        }else if(Escola[i].size() == 1 && match[i][0].first == 0){
            cout << "Escola(" << i+1 << ")" << endl;
        }
    }
    cout << endl;

    cout << "Numero maximo de professores que podem ser emparelhados: " << 100-cont << endl;
    cout << endl;
}

void print_maximo(){

    /* Mostra na tela as combinacoes de professor e escola pos emparelhamento maximo */
    cout << "Emparelhamento maximo: " << endl;
    for(int i = 0; i < match.size(); i++){
        if(match[i].size() == 1){
            if(match[i][0].first == 0){
                cout << "Escola - " << i+1  << " | " << "Sem Professor" << endl;

            }else{
                cout << "Escola - " << i+1  << " | " << "Professor - " << match[i][0].second.first+1 << endl;
            }
        }else{
            if((match[i][0].first == 0) && (match[i][1].first == 0)){
                cout  << "Escola - " << i+1  << " | " << "Sem Professor  |" << " Sem Professor" << endl;

            }else if((match[i][0].first != 0) && (match[i][1].first == 0)){
                cout  << "Escola - " << i+1  << " | " << "Professor - " << match[i][0].second.first+1;
                cout  << " | " << "Sem Professor" << endl;

            }else if((match[i][0].first == 0) && (match[i][1].first != 0)){
                cout  << "Escola - " << i+1  << " | " << "Sem Professor ";
                cout  << " | " << "Professor - " << match[i][1].second.first+1 << endl;

            }else{
                cout  << "Escola - " << i+1  << " | " << "Professor - " << match[i][0].second.first+1;
                cout  << " | " << "Professor - " << match[i][1].second.first+1 << endl;
            }
        }   
    }

    cout << endl;

    /* Professores sem escola */
    
    cout << "Professores que ficaram sem escola pos emparelhamento maximo: " << endl;
    for(int i = 0; i < 100; i++) if(free_agent[i]) cout << "Professor(" << i+1 << ")" << endl;

    cout << endl;

    /* Escolas com apenas uma vaga disponivel */

    cout << "Escolas que ficaram com apenas uma vaga pos emparalhemento maximo: " << endl;
    for(int i = 0; i < Escola.size(); i++){
        if(Escola[i].size() == 2)
            if(match[i][0].first == 0 || match[i][1].first == 0) cout << "Escola(" << i+1 << ")" << endl;
        else if(Escola[i].size() == 1)
            if(match[i][0].first == 0) cout << "Escola(" << i+1 << ")" << endl;
    }

}