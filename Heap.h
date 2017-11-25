#ifndef NANOROBOSCEREBRAIS_HEAP_H
#define NANOROBOSCEREBRAIS_HEAP_H

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

#include <vector>
#include <math.h>
#include "Vertice.h"
using namespace std;

class Heap {
private:
    int tamanhoHeap;
    int tamArray;

    int esquerda(int i) { return i * 2; }

    int direita(int i) { return ((i * 2) + 1); }

    int pai(int i) { return floor(i / 2); }

public:
    int getTamanhoHeap() { return this->tamanhoHeap; }

    void heapfica(Vertice *, int);

    void constroiHeap(Vertice *, int);

    Vertice extrairMenor(Vertice *);

};


#endif //NANOROBOSCEREBRAIS_HEAP_H
