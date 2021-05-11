#include "Trabalho.h"

using namespace std;

vector <vector <pair <int, bool>>> aux(5);
vector <vector<ii>> semestre(9);
vector <vector <pair<int, pair <string, string> >>> onde(9);
vector <vi> cor(9); 

void criar_grafo(){
    string aux;
    ifstream fin("arquivo.txt");      // Abre o arquivo txt com as informacoes dos professores e escolas

    for(int i = 0; i < 9; i++){
        while(fin.peek() != 10){       // Loop que pega as informacoes das materias
            int auxc, auxm = 0, t = 100000;
            string auxma;
            getline(fin, aux);
            for(int j = 0; j < 6;j++){
                auxm += ((aux[j] - 48) * t);
                t = t/10;
            }
            int in = aux.length() - 1;
            auxc = aux[in] - 48;
            semestre[i].pb(mp(auxm,auxc));
        }
        fin.ignore(2048, '\n');
    }

    fin.close();

}

/* Funcao para mostrar as materias na tela*/
void print_materias(){
    /* Loop que percorerre os semestres mostrando suas matérias e a quantidade de crédito de cada */
    string aux;
    ifstream fin("arquivo.txt");

    for(int i = 0; i < 9; i++){
        cout << i+1 <<  " - Semestre " << endl;
        while(fin.peek() != 10){
            getline(fin, aux);
            cout << aux << " creditos" << endl;   
        }
        cout << endl;
        fin.ignore(2048, '\n');
    }


    fin.close();
}

/* Funcao de ordenacao para termos prioridades em materias com a quantidade de creditos maior */
bool ord(ii x, ii y){ return (x.second > y.second); }

/* Funcao que executa o algoritmo de atribuição de cores e horarios/dias das aulas */ 

void coloracao(){
    /**
     * O algoritmo de coloracao utilizado funciona da seguinte forma:
     * Pegamos as materias com a maior quantidade de horas do semestre, e atribuimos ao primeiro dia livre,
     * procuramos sempre os primeiros horarios disponiveis para tentar cobrir o maior numero possivel de janelas.
     * Ao terminar os horarios da manha, eh incluido o horario da tarde. 
     * Priorizando sempre ter dias vagos, incluindo as materias com um intervalo de 48 horas. 
     * E buscando colocar materias uma seguida das outras para evitar as janelas de horarios.
     * Ao escolher o dia e o horario da aula, eh atribuido uma cor aos dias da semana e horario dessa mesma aula.
     * Tomando sempre o cuidado para que essas cores nao se repitam.
     * 
     */


    for(int i = 0; i < 5; i++){
    	aux[i].resize(4,mp(0,false));
    }

    for(int i = 0; i < semestre.size(); i++){
        //onde[i].resize(semestre[i].size());
        sort(semestre[i].begin(), semestre[i].end(), ord);      
        for(int j = 0; j < semestre[i].size(); j++){
            bool flag = true;
            if(semestre[i][j].second == 6){ /* Priorizacao de materias com a maior quantidade de horas */
                for(int k = 0; k < aux.size(); k++){
                    for(int l = 0; l < aux[k].size(); l++){
                        if(!aux[k][l].second or !aux[k+2][l].second or !aux[k+4][l].second){
                            aux[k][l].first = semestre[i][j].first;
                            aux[k+2][l].first = semestre[i][j].first;
                            aux[k+4][l].first = semestre[i][j].first;
                            aux[k][l].second = true;
                            aux[k+2][l].second = true;
                            aux[k+4][l].second = true;
                            flag = false;
                            if(k == 0){
                                if(l == 0){ /* Proucura de horarios disponiveis */
                                    onde[i].pb(mp(semestre[i][j].first, mp("Seg/Qua/Sex", "8:00 - 9:50")));
                                    cor[i].pb(j);
                                }else if(l == 1){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Seg/Qua/Sex", "10:00 - 11:50")));
                                    cor[i].pb(j);
                                }else if(l == 2){   
                                    onde[i].pb(mp(semestre[i][j].first, mp("Seg/Qua/Sex", "14:00 - 15:50")));
                                    cor[i].pb(j);
                                }else if(l == 3){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Seg/Qua/Sex", "16:00 - 17:50")));
                                    cor[i].pb(j);
                                }
                            }
                            break;
                        }
                    }
                    if(!flag) break;
                }
            }else if(semestre[i][j].second == 4){ /* Materias com 4 creditos */
                for(int k = 0; k < aux.size(); k++){
                    for(int l = 0; l < aux[k].size(); l++){
                        if(!aux[k][l].second or !aux[k+2][l].second){
                            aux[k][l].first = semestre[i][j].first;
                            aux[k+2][l].first = semestre[i][j].first;
                            aux[k][l].second = true;
                            aux[k+2][l].second = true;
                            flag = false;
                            if(k == 0){ /* Procura de horarios caso seg/qua esteja vago*/
                                if(l == 0){ /* Procura de horarios disponiveis */
                                    onde[i].pb(mp(semestre[i][j].first, mp("Seg/Qua", "8:00 - 9:50")));
                                    cor[i].pb(j);
                                }else if(l == 1){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Seg/Qua", "10:00 - 11:50")));
                                    cor[i].pb(j);
                                }else if(l == 2){   
                                    onde[i].pb(mp(semestre[i][j].first, mp("Seg/Qua", "14:00 - 15:50")));
                                    cor[i].pb(j);
                                }else if(l == 3){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Seg/Qua", "16:00 - 17:50")));
                                    cor[i].pb(j);
                                }
                            }else if(k == 1){ /* Procura de horarios caso seg/qua estaja ocupado e ter/qui esteja vago. */
                                if(l == 0){ 
                                    onde[i].pb(mp(semestre[i][j].first, mp("Ter/Qui", "8:00 - 9:50")));  
                                    cor[i].pb(j);                                  
                                }else if(l == 1){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Ter/Qui", "10:00 - 11:50")));
                                    cor[i].pb(j);
                                }else if(l == 2){   
                                    onde[i].pb(mp(semestre[i][j].first, mp("Ter/Qui", "14:00 - 15:50")));
                                    cor[i].pb(j);
                                }else if(l == 3){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Ter/Qui", "16:00 - 17:50")));
                                    cor[i].pb(j);
                                }
                            }
                            break;
                        }
                    }
                    if(!flag) break;
                }
            }else if(semestre[i][j].second == 2){ /* Atribuicao de materias com apenas 2 creditos */
                for(int k = 0; k < aux.size(); k++){
                    for(int l = 0; l < aux[k].size(); l++){
                        if(!aux[k][l].second){
                            aux[k][l].first = semestre[i][j].first;
                            aux[k][l].second = true;
                            flag = false;
                            if(k == 0){
                                if(l == 0){ /*Seguindo a ordem dos dias da semana para saber em qual dia alocar */
                                    onde[i].pb(mp(semestre[i][j].first, mp("Seg", "8:00 - 9:50")));
                                    cor[i].pb(j);
                                }else if(l == 1){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Seg", "10:00 - 11:50")));
                                    cor[i].pb(j);
                                }else if(l == 2){   
                                    onde[i].pb(mp(semestre[i][j].first, mp("Seg", "14:00 - 15:50")));
                                    cor[i].pb(j);
                                }else if(l == 3){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Seg", "16:00 - 17:50")));
                                    cor[i].pb(j);
                                }
                            }else if(k == 1){
                                if(l == 0){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Ter", "8:00 - 9:50")));
                                    cor[i].pb(j);
                                }else if(l == 1){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Ter", "10:00 - 11:50")));
                                    cor[i].pb(j);
                                }else if(l == 2){   
                                    onde[i].pb(mp(semestre[i][j].first, mp("Ter", "14:00 - 15:50")));
                                    cor[i].pb(j);
                                }else if(l == 3){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Ter", "16:00 - 17:50")));
                                    cor[i].pb(j);
                                }
                            }else if(k == 2){
                                if(l == 0){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Qua", "8:00 - 9:50")));
                                    cor[i].pb(j);
                                }else if(l == 1){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Qua", "10:00 - 11:50")));
                                    cor[i].pb(j);
                                }else if(l == 2){   
                                    onde[i].pb(mp(semestre[i][j].first, mp("Qua", "14:00 - 15:50")));
                                    cor[i].pb(j);
                                }else if(l == 3){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Qua", "16:00 - 17:50")));
                                    cor[i].pb(j);
                                }
                            }else if(k == 3){
                                if(l == 0){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Qui", "8:00 - 9:50")));
                                    cor[i].pb(j);
                                }else if(l == 1){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Qui", "10:00 - 11:50")));
                                    cor[i].pb(j);
                                }else if(l == 2){   
                                    onde[i].pb(mp(semestre[i][j].first, mp("Qui", "14:00 - 15:50")));
                                    cor[i].pb(j);
                                }else if(l == 3){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Qui", "16:00 - 17:50")));
                                    cor[i].pb(j);
                                }
                            }else if(k == 4){
                                if(l == 0){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Sex", "8:00 - 9:50")));
                                    cor[i].pb(j);
                                }else if(l == 1){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Sex", "10:00 - 11:50")));
                                    cor[i].pb(j);
                                }else if(l == 2){   
                                    onde[i].pb(mp(semestre[i][j].first, mp("Sex", "14:00 - 15:50")));
                                    cor[i].pb(j);
                                }else if(l == 3){
                                    onde[i].pb(mp(semestre[i][j].first, mp("Sex", "16:00 - 17:50")));
                                    cor[i].pb(j);
                                }
                            }
                            break;
                        }
                    }
                    if(!flag) break;
                }
            }
        }

        for(int w = 0; w < aux.size(); w++){ /* Zerar a semana caso o semestre ja esteja preenchido */
            for(int k = 0; k < aux[w].size(); k++){
                aux[w][k] = mp(0,false);
            }
        }
    }

    
}

/* Funcao que cria o arquivo para ser criado o grafo graficamente sem cor */
void criar_dot_sem_coloracao(){
    ofstream ofs;
    int i;
    ofs.open("dog.dot");
    int cont = 1;

    ofs << "graph Z {" << endl;

    for(int i = 0; i < semestre.size(); i++){
        for(int j = 0; j < semestre[i].size(); j++){
            ofs << "    M" << cont << "[label=\""<< semestre[i][j].first << "\\n" << semestre[i][j].second << "\\n\"" << "] " << endl;
            cont++;
        }
    }

    /* Faz as ligacoes dos grafos */

    ofs << "    subgraph cluster_0{" << endl;
	ofs << "        label=\"Primeiro Semestre\";" << endl;
    ofs << "        M1 -- M2 -- M3 -- M1;" << endl;
    ofs << "        color=black;" << endl;
	ofs << "    }" << endl;
    ofs << "    subgraph cluster_1 {" << endl;
	ofs << "        label=\"Segundo Semestre\";" << endl;
    ofs << "        M4 -- {M5 -- M6 -- M7};" << endl;
    ofs << "        M5 -- M7;" << endl;
    ofs << "        color=black;" << endl;
	ofs << "    }" << endl;
    ofs << "    subgraph cluster_2 {" << endl;
	ofs << "        label=\"Teceiro Semestre\";" << endl;
    ofs << "        M8 -- {M9 -- M10 -- M11 -- M12};" << endl;
    ofs << "        M10 -- M12 -- M9 -- M11;" << endl;
    ofs << "        color=black;" << endl;
	ofs << "    }" << endl;
    ofs << "    subgraph cluster_3 {" << endl;
	ofs << "        label=\"Quarto Semestre\";" << endl;
    ofs << "        M13 -- {M14 -- M15 -- M16};" << endl;
    ofs << "        M16 -- M14;" << endl;
    ofs << "        color=black;" << endl;
	ofs << "    }" << endl;
    ofs << "    subgraph cluster_4{" << endl;
	ofs << "        label=\"Quinto Semestre\";" << endl;
    ofs << "        M17 -- {M18 -- M19 -- M20 -- M21};" << endl;
    ofs << "        M19 -- M21 -- M18 -- M20;" << endl;
    ofs << "        color=black;" << endl;
	ofs << "    }" << endl;
    ofs << "    subgraph cluster_5{" << endl;
	ofs << "        label=\"Sexto Semestre\";" << endl;
    ofs << "        M22 -- {M23 -- M24 -- M25 -- M26};" << endl;
    ofs << "        M25 -- M23 -- M26 -- M24;" << endl;
    ofs << "        color=black;" << endl;
	ofs << "    }" << endl;
    ofs << "    subgraph cluster_6{" << endl;
	ofs << "        label=\"Setimo Semestre\";" << endl;
    ofs << "        M27 -- {M28 -- M29 -- M30};" << endl;
    ofs << "        M28 -- M30;" << endl;
    ofs << "        color=black;" << endl;
	ofs << "    }" << endl;
    ofs << "    subgraph cluster_7 {" << endl;
	ofs << "        label=\"Oitavo Semestre\";" << endl;
    ofs << "        M31 -- M32;" << endl;
    ofs << "        color=black;" << endl;
	ofs << "    }" << endl;
    ofs << "    subgraph cluster_8 {" << endl;
	ofs << "        label=\"Nono Semestre\";" << endl;
    ofs << "        M33;" << endl;
    ofs << "        color=black;" << endl;
	ofs << "    }" << endl;
    
    ofs << "}";
    ofs.close();
}

/* Funcao para criar o arquivo de criacao do grafo antes da coloracao graficamente e mostra na tela */
void mostrar_dot_sem_cor(){
    system("dot -Tpng dog.dot -o grafo1.png");
    system("display grafo1.png");
}

/* Funcao que cria o arquivo para ser criado o grafo graficamente com cor */
void criar_dot_coloracao(){
    ofstream ofs;
    int i;
    ofs.open("dig.dot");
    int cont = 1;
    vector<string> cores{"darkred","orange","yellow","green","purple","brown","ligthgrey", "blue"};


    ofs << "graph P {" << endl;
    /* Escolhe as cores dos nos */

    for(int i = 0; i < onde.size(); i++){
        for(int j = 0; j < onde[i].size(); j++){
            ofs << "    M" << cont << "[label=\""<< onde[i][j].first << "\\n" << onde[i][j].second.first << "\\n " << onde[i][j].second.second;
            ofs << "\",style=filled, color=" << cores[cor[i][j]] << "] " << endl;
            cont++;
        }
    }

    /* Faz as ligacoes dos grafos */

    ofs << "    subgraph cluster_0{" << endl;
	ofs << "        label=\"Primeiro Semestre\";" << endl;
    ofs << "        M1 -- M2 -- M3 -- M1;" << endl;
    ofs << "        color=pink;" << endl;
	ofs << "    }" << endl;
    ofs << "    subgraph cluster_1 {" << endl;
	ofs << "        label=\"Segundo Semestre\";" << endl;
    ofs << "        M4 -- {M5 -- M6 -- M7};" << endl;
    ofs << "        M5 -- M7;" << endl;
    ofs << "        color=pink;" << endl;
	ofs << "    }" << endl;
    ofs << "    subgraph cluster_2 {" << endl;
	ofs << "        label=\"Teceiro Semestre\";" << endl;
    ofs << "        M8 -- {M9 -- M10 -- M11 -- M12};" << endl;
    ofs << "        M10 -- M12 -- M9 -- M11;" << endl;
    ofs << "        color=pink;" << endl;
	ofs << "    }" << endl;
    ofs << "    subgraph cluster_3 {" << endl;
	ofs << "        label=\"Quarto Semestre\";" << endl;
    ofs << "        M13 -- {M14 -- M15 -- M16};" << endl;
    ofs << "        M16 -- M14;" << endl;
    ofs << "        color=pink;" << endl;
	ofs << "    }" << endl;
    ofs << "    subgraph cluster_4{" << endl;
	ofs << "        label=\"Quinto Semestre\";" << endl;
    ofs << "        M17 -- {M18 -- M19 -- M20 -- M21};" << endl;
    ofs << "        M19 -- M21 -- M18 -- M20;" << endl;
    ofs << "        color=pink;" << endl;
	ofs << "    }" << endl;
    ofs << "    subgraph cluster_5{" << endl;
	ofs << "        label=\"Sexto Semestre\";" << endl;
    ofs << "        M22 -- {M23 -- M24 -- M25 -- M26};" << endl;
    ofs << "        M25 -- M23 -- M26 -- M24;" << endl;
    ofs << "        color=pink;" << endl;
	ofs << "    }" << endl;
    ofs << "    subgraph cluster_6{" << endl;
	ofs << "        label=\"Setimo Semestre\";" << endl;
    ofs << "        M27 -- {M28 -- M29 -- M30};" << endl;
    ofs << "        M28 -- M30;" << endl;
    ofs << "        color=pink;" << endl;
	ofs << "    }" << endl;
    ofs << "    subgraph cluster_7 {" << endl;
	ofs << "        label=\"Oitavo Semestre\";" << endl;
    ofs << "        M31 -- M32;" << endl;
    ofs << "        color=pink;" << endl;
	ofs << "    }" << endl;
    ofs << "    subgraph cluster_8 {" << endl;
	ofs << "        label=\"Nono Semestre\";" << endl;
    ofs << "        M33;" << endl;
    ofs << "        color=pink;" << endl;
	ofs << "    }" << endl;
        
    
    ofs << "}";
    ofs.close();
}

/* Funcao para criar o arquivo de criacao do grafo depois da coloracao graficamente e mostra na tela */
void mostrar_dot_com_cor(){
    system("dot -Tpng dig.dot -o grafo.png");
    system("display grafo.png");
}