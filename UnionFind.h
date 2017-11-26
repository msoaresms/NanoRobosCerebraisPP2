#ifndef NANOROBOSCEREBRAIS_UNIONFIND_H
#define NANOROBOSCEREBRAIS_UNIONFIND_H

#include <vector>
#include <iostream>
using namespace std;

class UnionFind {
private:
    vector<int> conjunto;
    int tamanho;

public:
    UnionFind(int pTamanho) {
        this->tamanho = pTamanho+1;
        this->conjunto.resize(tamanho);
        for (int i = 0; i < this->conjunto.size(); i++){
            this->conjunto[i] = i;
        }
    }

    int find(int);
    bool conectados(int, int);
    void uniao(int, int);

};


#endif //NANOROBOSCEREBRAIS_UNIONFIND_H
