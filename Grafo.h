#ifndef NANOROBOSCEREBRAIS_GRAFO_H
#define NANOROBOSCEREBRAIS_GRAFO_H

#include <iostream>
#include <vector>
#include <iomanip> //será removido--------------------------------------------------------------------------------------
using namespace std;

template <class T>
class Grafo {
private:
    vector<T> itens;
    vector<float> *matriz;
    int ordem, tamanho;

public:
    Grafo() { Grafo(0); }
    Grafo(int pOrdem) {
        this-> ordem = pOrdem;
        this->tamanho = 0;
        inicializar();
    }

    void inicializar();
    void inserirAresta(int, int, float);
    void mostrar();
    void inserirItem(T, int);
    T getItem(int);

    vector<T> getItens() { return this->itens; }
    vector<float> *getMatriz() { return this->matriz; }
    int getOrdem() { return this->ordem; }
    int getTamanho() { return this->tamanho; }
};

template <typename T>
void Grafo<T>::inicializar() {
    this->itens.resize(this->ordem+1);
    this->matriz = new vector<float>[this->ordem+1];
    for (int i = 0; i <= this->ordem; i++) { matriz[i].assign(this->ordem+1, 0); }
}

template <typename T>
void Grafo<T>::inserirAresta(int u, int v, float w){
    this->matriz[u][v] = w;
    this->matriz[v][u] = w;
    this->tamanho++;
}

template <typename T>
void Grafo<T>::inserirItem(T pItem, int pVertice) { this->itens[pVertice] = pItem; }

template <typename T>
T Grafo<T>::getItem(int n) {
    return this->itens[n];
}

//será removido---------------------------------------------------------------------------------------------------------
template <typename T>
void Grafo<T>::mostrar() {
    int k = 8;
    cout << "   ";
    for (int j = 1; j <= this->ordem; j++){
        cout << setw(k) << j;
    }
    cout << endl;
    for (int j = 1; j <= (this->ordem*k+3); j++){
        cout << "-";
    }
    cout << endl;
    for (int i = 1; i <= this->ordem; i++){
        cout << setw(1) << i;
        cout << " |";
        for (int j = 1; j <= this->ordem; j++){
            cout << setw(k) << matriz[i][j];
        }
        cout << endl;
    }
}

#endif //NANOROBOSCEREBRAIS_GRAFO_H
