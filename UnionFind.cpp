#include "UnionFind.h"

int UnionFind::find(int p) {
    while (p != this->conjunto[p]) {
        p = this->conjunto[p];
    }
    return p;
}

bool UnionFind::conectados(int p, int q) {
    return this->find(p) == this->find(q);
}

void UnionFind::uniao(int p, int q) {
    int raizP = this->find(p);
    int raizQ = this->find(q);
    if (raizP == raizQ) { return; }
    this->conjunto[raizP] = raizQ;
    this->tamanho--;
}
