/** @author Carlos Eduardo de Oliveira Ribeiro - 180099094
 *  @author Joao Gabriel Ferreira Saraiva - 180103016
 *
 */

#ifndef TRABALHO_H
#define TRABALHO_H

#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <graphviz/gvc.h>

using namespace std;

#define vi vector <int>
#define ll long long
#define ii pair<int,int>
#define pb push_back
#define mp make_pair
#define si pair<string,int>
#define endl "\n"

void criar_grafo();

void ord_topologica();
void dfs(string, int, int);
void print_topologica();

void manda_pra_cria();
void chama_caminha();
void caminha(string v, int i, int y);
void caminhocritico();

bool ord(pair <int,int> i, pair <int,int> j);
bool check(vector <vector <pair <string, int>>> tres, vector <pair <string, int>> v1);

void criticos_png();
void grafo_png();
void topologica_png();

void mostra_topologica();
void mostra_grafo();
void mostra_criticos();

void print_disciplinas();
void print_caminhoscriticos();

#endif