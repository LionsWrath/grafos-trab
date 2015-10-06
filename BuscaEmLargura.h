#ifndef BUSCAEMLARGURA_H_
#define BUSCAEMLARGURA_H_
#include "fila/Fila.h"
#include "listaAdj/Grafo.h"
#include <iostream>
#include <stdexcept> 
#include <limits.h>
#include <iomanip>

#define INF 99999

using std::logic_error;
using std::cout;
using std::endl;
using fila_autoreferencia::Fila;
using listaAdj::Grafo; 

namespace grafos {
    
    /* Definição do Header da Classe BuscaEmLargura */
    class BuscaEmLargura {

    public:

        static const unsigned char branco;
        static const unsigned char cinza;
        static const unsigned char preto;
  
    private:

        int raiz;
        int *d; 
        int *antecessor;
        Grafo *grafo;

    public:

        /* Protótipos das Funções */
	BuscaEmLargura (Grafo *grafo, int raiz);
        ~BuscaEmLargura ();

	void buscaEmLargura () throw (logic_error);
	int _d (int v) const;
	int _antecessor (int v) const; 
        int calcularDistancia (int origem, int v);
        void imprime ();
	void imprimeCaminho (int origem, int v) const ;
	
    };
    /* Fim da definição do Header da Classe BuscaEmLargura */

    //----------[ Implementação ]

    /* Definição das Constantes */
    const unsigned char BuscaEmLargura::branco = 0;
    const unsigned char BuscaEmLargura::cinza  = 1;
    const unsigned char BuscaEmLargura::preto  = 2;

    /* Construtor da Busca */
    BuscaEmLargura::BuscaEmLargura (Grafo *grafo,int raiz) {
        this->grafo = grafo; 
        this->raiz = raiz-1;
        int n = this->grafo->_numVertices();
        this->d = new int[n]; 
        this->antecessor = new int[n];
    }

    /* Construtor da Busca(Sem o grafo) */
    BuscaEmLargura::~BuscaEmLargura () {
        this->grafo = NULL; 
        delete [] this->d; 
        delete [] this->antecessor;
    }

    /* Inicia a Busca */
    void BuscaEmLargura::buscaEmLargura () throw (logic_error) {
        unsigned char *cor = new unsigned char[this->grafo->_numVertices ()];
        Fila<int> fila;

        for (int u = 0; u < grafo->_numVertices (); u++) {
            cor[u] = branco; 
            this->d[u] = INF; 
            this->antecessor[u] = -1;
        }
       
        int u = this->raiz;

        cor[u] = cinza;
        this->d[u] = 0;

        fila.enfileira (u);
        while (!fila.vazia()) {
            int *aux = fila.desenfileira ();
            u = *aux;
            delete aux;

            if (!this->grafo->listaAdjVazia(u)) {
                Grafo::Aresta *a = this->grafo->primeiroListaAdj (u);
                while (a != NULL) {
                    int v = a->_v2 ();

                    if (cor[v] == branco) {
                        cor[v] = cinza;
                        this->d[v] = this->d[u] + 1;
                        this->antecessor[v] = u;
                        fila.enfileira (v);
                    }
                    delete a;
                    a = this->grafo->proxAdj (u);
                }
            }
            cor[u] = preto;
        }
        delete [] cor;
    }

    /* getD */
    int BuscaEmLargura::_d (int v) const { 
        return this->d[v]; 
    }

    /* getAntecessor */
    int BuscaEmLargura::_antecessor (int v) const { 
  	return this->antecessor[v]; 
    }

    int BuscaEmLargura::calcularDistancia (int origem, int v) {
        int aux;
        if (origem == v) {
            return 0;
        } else if (this->antecessor[v] == -1) {
            return -99999;
        } else {
            aux = calcularDistancia (origem, this->antecessor[v]);
            return ++aux;
        }
    }

    void BuscaEmLargura::imprime () {
        int d;
        for (int u = 0; u < this->grafo->_numVertices (); u++) {
            cout << "Vertice: "; 
            cout << std::setw (2) << u+1 << " Predecessor: "; 
            if (antecessor[u] != -1) {
                cout << std::setw (3) <<  antecessor[u]+1 << " Distância de ";
            } else {
                cout << std::setw (3) << "NIL" << " Distância de "; 
            }
            cout << std::setw (2) << this->raiz+1 << ": ";
            
            d = calcularDistancia(this->raiz, u);
            if (d >= 0){
                cout << std::setw (3) << d << endl;
            } else {
                cout << std::setw (3) << "INF" << endl;
            }
        }
    }

    /* Imprime o caminho */
    void BuscaEmLargura::imprimeCaminho (int origem, int v) const {
        if (origem == v) {
            cout << origem << endl;
        } else if (this->antecessor[v] == -1) {
            cout << "Nao existe caminho de " << origem << " ate " << v << endl;
        } else {
            imprimeCaminho (origem, this->antecessor[v]);
            cout << v << endl;
        }    
    }
  
}

#endif
