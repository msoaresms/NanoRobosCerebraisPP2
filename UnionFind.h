#ifndef NANOROBOSCEREBRAIS_UNIONFIND_H
#define NANOROBOSCEREBRAIS_UNIONFIND_H

#include <vector>
#include <iostream>
using namespace std;

class UnionFind {
private:
    vector<int> conjuntos;
    int tamanho;

public:
    UnionFind(int pTamanho) {
        this->tamanho = pTamanho;
        this->conjuntos.resize(tamanho+1);
        for (int i = 0; i < this->conjuntos.size(); i++){
            this->conjuntos[i] = i;
        }
    }

    int procurar(int);
    bool conectados(int, int);
    void uniao(int, int);

};


#endif //NANOROBOSCEREBRAIS_UNIONFIND_H
