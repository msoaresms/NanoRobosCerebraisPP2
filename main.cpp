#include <iostream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <limits>

#include "Grafo.h"
#include "Vertice.h"
#include "Heap.h"
#include "Aresta.h"
#include "UnionFind.h"

using namespace std;

const bool DOENTE = true;
const bool SAUDAVEL = false;
const int NULO = -1;
const int INFINITO = numeric_limits<int>::max();
//----------------------------------------------------------------------------------------------------------------------
vector<string> leitura() {
    string entrada = "";
    char * entradaChar;
    vector<string> entradaSplit;

    getline(cin, entrada);
    entradaChar = strtok(&entrada[0], " ");
    while (entradaChar != nullptr) {
        string split(entradaChar);
        entradaSplit.push_back(split);
        entradaChar = strtok(nullptr, " ");
    }
    return entradaSplit;
}

Grafo<Grafo<bool>> lerCerebro() {
    vector<string> entrada;
    int ordemCerebro, tamanhoCerebro = NULO;

    entrada = leitura();
    ordemCerebro = stoi(entrada[0]);
    tamanhoCerebro = stoi(entrada[1]);

    Grafo<Grafo<bool>> cerebro(ordemCerebro);

    for (int i = 1; i <= tamanhoCerebro; i++){
        entrada = leitura();
        int u = stoi(entrada[0]);
        int v = stoi(entrada[1]);
        float w = stof(entrada[2]);

        cerebro.inserirAresta(u, v, w);
    }
    return cerebro;
}

void lerBlocos(Grafo<Grafo<bool>> &cerebro) {
    vector<string> entrada;
    int ordemCerebro = cerebro.getOrdem();

    for (int i = 1; i <= ordemCerebro; i++) {
        int ordemBloco, tamanhoBloco = NULO;
        vector<int> doentes;

        entrada = leitura();
        ordemBloco = stoi(entrada[0]);
        tamanhoBloco = stoi(entrada[1]);

        Grafo<bool> bloco(ordemBloco);

        entrada = leitura();
        for (string x : entrada) {
            doentes.push_back(stoi(x));
        }

        for (int j = 1; j <= tamanhoBloco; j++) {
            entrada = leitura();
            int u = stoi(entrada[0]);
            int v = stoi(entrada[1]);
            float w = stof(entrada[2]);

            bloco.inserirAresta(u, v, w);
        }

        int k = 0;
        for (int j = 1; j <= ordemBloco; j++) {
            if (j == doentes[k] && k < doentes.size()) {
                bloco.inserirItem(DOENTE, j);
            } else {
                bloco.inserirItem(SAUDAVEL, j);
            }
            k++;
        }

        cerebro.inserirItem(bloco, i);

    }
}

vector<int> adjDeU(vector<float> aux) {
    vector<int> adjU;
    for (int i = 1; i < aux.size(); i++) {
        if (aux[i] != 0.0) {
            adjU.push_back(i);
        }
    }
    return adjU;
}

int posNoHeap(Vertice *v, int tam, int n) {
    for (int i = 1; i <= tam; i++) {
        if (n == v[i].getNumVertice()) {
            return i;
        }
    }
    return -1;
}

void selectionSort(vector<Aresta> &v) {
    for (int i = 1; i < v.size(); i++){
        int min = i;
        for (int j = i+1; j < v.size(); j++){
            if (v[j].getPeso() < v[min].getPeso()){
                min = j;
            }
        }
        Aresta temp = v[i];
        v[i] = v[min];
        v[min] = temp;
    }
}

template <typename T>
vector<Vertice> Dijkstra(Grafo<T> grafo, int inicio) {
    Vertice Q[grafo.getOrdem()+1];
    vector<Vertice> S;
    vector<int> adjU;
    vector<float> *matriz = grafo.getMatriz();
    Heap prioridade;

    for (int i = 1; i <=grafo.getOrdem(); i++) {
        Q[i] = Vertice(INFINITO, NULO, i);
    }

    Q[inicio].setDistancia(0.0);
    prioridade.constroiHeap(Q, grafo.getOrdem());

    while (prioridade.getTamanhoHeap() > 0) {
        Vertice u = prioridade.extrairMenor(Q);
        S.push_back(u);


        adjU = adjDeU(matriz[u.getNumVertice()]);

        for (int x : adjU) {
            int v = posNoHeap(Q, grafo.getOrdem(), x);
            if (Q[v].getDistancia() > u.getDistancia() + (matriz[u.getNumVertice()][Q[v].getNumVertice()])) {
                Q[v].setDistancia(u.getDistancia() + (matriz[u.getNumVertice()][Q[v].getNumVertice()]));
                Q[v].setPredecessor(u.getNumVertice());
                prioridade.heapfica(Q, 1);
            }
        }
    }
    return S;
}

template <typename T>
vector<Aresta> Kruskal(Grafo<T> grafo) {
    vector<Aresta> A;
    vector<Aresta> saida;
    UnionFind conjuntos(grafo.getOrdem());

    vector<float> *matriz = grafo.getMatriz();

    for (int i = 1; i <= grafo.getOrdem(); i++) {
        for (int j = 1; j <= grafo.getOrdem(); j++) {
            if (j > i && matriz[i][j] != 0.0) {
                A.push_back(Aresta(i, j, matriz[i][j]));
            }
        }
    }

    selectionSort(A);

    while (A.size() > 0) {
        Aresta aux = A[0];
        A.erase(A.begin()+0);

        if (!conjuntos.conectados(aux.getU(), aux.getV())) {
            saida.push_back(aux);
            conjuntos.uniao(aux.getU(), aux.getV());
        }
    }

    return saida;

}
//----------------------------------------------------------------------------------------------------------------------
int main() {

    vector<string> entrada;
    Grafo<Grafo<bool>> cerebro;
    int inicio, fim = NULO;

    cerebro = lerCerebro();

    entrada = leitura();
    inicio = stoi(entrada[0]);
    fim = stoi(entrada[1]);

    lerBlocos(cerebro);

    vector<Vertice> resultD = Dijkstra(cerebro, inicio);

    //------------------------------------------------------------------------------------------------------------------

    vector<int> blocosV;
    int aux = fim;
    while (aux != NULO) {
        for (Vertice x : resultD) {
            if (aux == x.getNumVertice()) {
                blocosV.push_back(x.getNumVertice());
                aux = x.getPredecessor();
                break;
            }
        }
    }


    vector<Grafo<bool>> blocos;
    for (int x : blocosV) {
        Grafo<bool> bloco = cerebro.getItem(x);
        for (int i = 1; i <= bloco.getOrdem(); i++) {
            bool aux = bloco.getItem(i);
            if (aux) {
                blocos.push_back(bloco);
                break;
            }
        }
    }

    float saida = 0.0;

    for (Grafo<bool> x : blocos) {
        vector<Aresta> resultKruskal = Kruskal(x);

        for (Aresta y : resultKruskal) {
            saida += y.getPeso();
        }
    }

    cout << saida << endl;


    cout << "\n---------------------------------------------------------";

    return 0;
}