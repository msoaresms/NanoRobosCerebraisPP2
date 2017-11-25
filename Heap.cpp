#include "Heap.h"

void Heap::heapfica(Vertice *v, int i) {
    int esq = esquerda(i);
    int dir = direita(i);
    int menor;

    if (esq <= this->tamanhoHeap && (v[esq].getDistancia() < v[i].getDistancia())) {
        menor = esq;
    } else {
        menor = i;
    }

    if (dir <= this->tamanhoHeap && (v[dir].getDistancia() < v[menor].getDistancia())) {
        menor = dir;
    }

    if (menor != i) {
        Vertice vAux = v[i];
        v[i] = v[menor];
        v[menor] = vAux;
        this->heapfica(v, menor);
    }

}

void Heap::constroiHeap(Vertice *vec, int pTamArray) {
    this->tamArray = pTamArray;
    this->tamanhoHeap = this->tamArray;

    for (int i = floor(this->tamArray/2); i > 0; i--) {
        this->heapfica(vec, i);
    }
}

Vertice Heap::extrairMenor(Vertice *vec) {
    Vertice menor = vec[1];
    vec[1] = vec[this->tamanhoHeap];
    this->tamanhoHeap--;
    this->heapfica(vec, 1);
    return menor;
}
