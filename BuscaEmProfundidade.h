#ifndef BUSCAEMPROFUNDIDADE_H_
#define BUSCAEMPROFUNDIDADE_H_
#include "listaAdj/Grafo.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using listaAdj::Grafo;

namespace grafos {

    /* Definição do Header de Busca em Profundidade  */
    class BuscaEmProfundidade {

    public:

        static const unsigned char branco;
        static const unsigned char cinza;
        static const unsigned char preto;

    private:

        int *d, *t, *antecessor;
        Grafo *grafo;
        int visitaDfs (int u, int tempo, unsigned char *cor) const;
        
    public:

        /* Protótipo das Funções  */
        BuscaEmProfundidade (Grafo *grafo);
        ~BuscaEmProfundidade ();

	void buscaEmProfundidade () const;
	int _d (int v) const;
	int _t (int v) const;
	int _antecessor (int v) const; 
        void imprime ();
    };
    /* Fim da definição do Header de Busca em Profundidade  */

    //--------------[ Implementação ]

    /* Definição das Constantes  */
    const unsigned char BuscaEmProfundidade::branco = 0;
    const unsigned char BuscaEmProfundidade::cinza  = 1;
    const unsigned char BuscaEmProfundidade::preto  = 2;

    /* Função recursiva que visita cada nó do grafo */
    int BuscaEmProfundidade::visitaDfs (int u, int tempo, unsigned char *cor) const {
        cor[u] = cinza; 
        this->d[u] = ++tempo;
        if (!this->grafo->listaAdjVazia (u)) {
            Grafo::Aresta *a = this->grafo->primeiroListaAdj (u);
            while (a != NULL) {
                int v = a->_v2 ();
                if (cor[v] == branco) {
                    
                    this->antecessor[v] = u;
                    tempo = this->visitaDfs (v, tempo, cor);
                }
            delete a; 
            a = this->grafo->proxAdj (u);
            }
        }

        cor[u] = preto; 
        this->t[u] = ++tempo;
        return tempo;
    }

    /* Construtor da Busca  */
    BuscaEmProfundidade::BuscaEmProfundidade (Grafo *grafo) {
        this->grafo = grafo; 
        int n = this->grafo->_numVertices ();
        d = new int[n]; 
        t = new int[n];
        antecessor = new int[n];
    }

    /* Construtor da Busca(Sem o grafo) */
    BuscaEmProfundidade::~BuscaEmProfundidade () {
        this->grafo = NULL; 
        delete [] this->d;
        delete [] this->t; 
        delete [] this->antecessor;
    }

    /* Inicia a busca  */
    void BuscaEmProfundidade::buscaEmProfundidade () const {
        int tempo = 0; 
        unsigned char *cor = new unsigned char[this->grafo->_numVertices ()]; 
        
        for (int u = 0; u < grafo->_numVertices (); u++) {
            cor[u] = branco; 
            this->antecessor[u] = -1;
        }

        for (int u = 0; u < grafo->_numVertices (); u++) {
            if (cor[u] == branco){
                tempo = this->visitaDfs (u, tempo, cor);
            }
        }

        delete [] cor;
    }

    /* getD */
    int BuscaEmProfundidade::_d (int v) const { 
        return this->d[v]; 
    }

    /* getT */
    int BuscaEmProfundidade::_t (int v) const { 
        return this->t[v]; 
    }

    /* getAntecessor */
    int BuscaEmProfundidade::_antecessor (int v) const { 
  	return this->antecessor[v]; 
    }

    void BuscaEmProfundidade::imprime () {
        for (int u = 0; u < this->grafo->_numVertices (); u++) {
            cout << "Vértice: ";
            cout << std::setw(2) << u+1 << " Tempo de Descoberta: "; 
            cout << std::setw(2) << d[u] << " Tempo de Término: "; 
            cout << std::setw(2) << t[u] << " Predecessor: ";
            
            if (antecessor[u] >= 0){
                cout << std::setw(3) << antecessor[u]+1 << endl;
            } else {
                cout << std::setw(3) << "NIL" << endl;
            }
        }
    }

}
#endif
