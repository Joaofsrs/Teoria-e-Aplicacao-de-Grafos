/**
 * @file Trabalho.h
 * @author Joao Gabriel Ferreira Saraiva - 180103016
 * @author Carlos Eduardo de Oliveira Ribeiro - 180099094
 * @version 0.1
 * @date 2020-11-27
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <bits/stdc++.h>
#include <fstream>
#include <sstream>

#define vi vector <int>
#define vl vector <long long>
#define ll long long
#define pb push_back
#define mp make_pair
#define ii pair <int,int>
#define endl "\n"
#define qu queue <int>
#define qmax priority_queue <int>
#define qmin priority_queue <int, vector<int>,greater<int>>

using namespace std;

void criar_grafo();
void print_materias();

void coloracao();

void criar_dot_coloracao();
void mostrar_dot_com_cor();

void criar_dot_sem_coloracao();
void mostrar_dot_sem_cor();
