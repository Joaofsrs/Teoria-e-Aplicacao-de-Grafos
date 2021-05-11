/** @author Carlos Eduardo de Oliveira Ribeiro - 180099094
 *  @author Joao Gabriel Ferreira Saraiva - 180103016
 *
 */

#ifndef TRABALHO_H
#define TRABALHO_H
#include <bits/stdc++.h>
#include <fstream>
#include <algorithm>

using namespace std;

#define vi vector <int>
#define ll long long
#define pb push_back
#define mp make_pair
#define ii pair<int,int>

void imprime_grafo();

void imprime_cliques();

vector <int> intersecao(vector <int> v1, vector <int> v2);

vector <int> uniao(vector <int> v1, vector <int> v2);

vector <int> remove_vertice(vector <int> v1, vector<int> v2);

void imprime_coeficiente(vector <double> CAG);

void coeficiente_de_aglomeracao(vector <int> vtriangulos);

bool verifica(vector <int> n, vector <vector<int>> japassou);

void verifica_triangulos(vector <vector<int>> japassou);

void triangulos();

void BronKerbosch1(vector<int> R, vector<int> P, vector<int> X);

void BronKeborsch0();

void criar_grafo();

#endif