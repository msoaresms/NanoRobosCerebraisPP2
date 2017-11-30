#include "Heap.h"

void Heap::troca(Vertice *v, int i, int j) {
    Vertice vAux = v[i];
    v[i] = v[j];
    v[j] = vAux;

    int aux = this->posParaId[i];
    this->posParaId[i] = this->posParaId[j];
    this->posParaId[j] = aux;

    aux = this->IdParaPos[this->posParaId[i]];
    this->IdParaPos[this->posParaId[i]] = this->IdParaPos[this->posParaId[j]];
    this->IdParaPos[this->posParaId[j]] = aux;
}

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
        this->troca(v, i, menor);
        this->heapfica(v, menor);
    }

}

void Heap::constroiHeap(Vertice *vec, int pTamArray) {
    this->tamArray = pTamArray;
    this->tamanhoHeap = this->tamArray;

    this->IdParaPos = new int[this->tamArray+1];
    this->posParaId = new int[this->tamArray+1];

    for (int i = 0; i <= this->tamArray; i++) {
        this->IdParaPos[i] = i;
        this->posParaId[i] = i;
    }

    for (int i = floor(this->tamArray/2); i > 0; i--) {
        this->heapfica(vec, i);
    }
}

Vertice Heap::extrairMenor(Vertice *vec) {

    Vertice menor = vec[1];
    vec[1] = vec[this->tamanhoHeap];

    int id = this->posParaId[this->tamanhoHeap];
    this->IdParaPos[id] = 1;
    this->posParaId[1] = id;

    this->tamanhoHeap--;

    this->heapfica(vec, 1);

    return menor;
}

void Heap::alterarChave(Vertice * vec, int vert, float peso) {
    vec[vert].setDistancia(peso);

    while(vert > 1 && vec[pai(vert)].getDistancia() > vec[vert].getDistancia()) {
        this->troca(vec, vert, pai(vert));
        vert = pai(vert);
    }
}

int Heap::posNoHeap(int vertice) {
    return this->IdParaPos[vertice];
}
