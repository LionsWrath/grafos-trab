#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_
#include "listaAdj/Grafo.h" 
#include "heap/FPHeapMinIndireto.h"
#include <float.h>
#include <iostream>

using std::cout;
using std::endl;
using listaAdj::Grafo;

namespace grafos {
    
    /* Definição do Header da Classe Dijkstra */
    class Dijkstra {
    private:
    
        int *antecessor;
	double *p;
        int raiz;
	Grafo *grafo;
    
    public:

        /* Protótipos das funções */
	Dijkstra (Grafo *grafo, int raiz);
	~Dijkstra ();
        
        void obterArvoreCMC () throw (logic_error);
	int _antecessor (int u) const;
	double _peso (int u) const;
	void imprime ();
        int calcularDistancia (int origem, int v);
	void imprimeCaminho (int origem, int v) const;
	
    };
    /* Fim da definição do Header ca classe Dijkstra */

    //---------[ Implementação ]

    /* Construtor */
    Dijkstra::Dijkstra (Grafo *grafo, int raiz) { 
        this->grafo = grafo;
        this->raiz = raiz-1;
        this->antecessor = NULL; 
        this->p = NULL;
    }

    /* Destrutor */
    Dijkstra::~Dijkstra () { 
        this->grafo = NULL;    	
        
        if (this->p) { 
            delete [] this->p;
        }

  	if (this->antecessor) { 
            delete [] this->antecessor;
        }
    }

    /* Constrói o Heap e gera o Caminho */
    void Dijkstra::obterArvoreCMC () throw (logic_error) {
        int n = this->grafo->_numVertices();
        
        //Reinicia o vetor de pesos
        if (this->p) { 
            delete [] this->p;
        }
        
        this->p = new double[n]; 
        int *vs = new int[n+1];

        //Reinicia o vetor de antecessores
        if (this->antecessor) { 
            delete [] this->antecessor;
        }

        this->antecessor = new int[n];
    
        /* Inicializando (Initializing Single Source) */
        for (int u = 0; u < n; u ++) {
            this->antecessor[u] = -1;
            p[u] = DBL_MAX;
            vs[u+1] = u;
        }
        p[raiz] = 0;

        FPHeapMinIndireto heap (p, vs, n); 
        heap.constroi ();
        while (!heap.vazio ()) {
            //Método guloso, retira o menor
            int u = heap.retiraMin (); 
            if (!this->grafo->listaAdjVazia (u)) {
                Grafo::Aresta *adj = grafo->primeiroListaAdj (u);
                while (adj != NULL) {
                    int v = adj->_v2 ();
                    //Relax
                    if (this->p[v] > (this->p[u] + adj->_peso ())) {
                        antecessor[v] = u; 
                        heap.diminuiChave (v, this->p[u] + adj->_peso ());
                    }
                    delete adj; 
                    adj = grafo->proxAdj (u);
                }
            }
        }
        delete [] vs;
    }

    /* GetAntecessor */
    int Dijkstra::_antecessor (int u) const { 
        return this->antecessor[u]; 
    }

    /* GetPeso */
    double Dijkstra::_peso (int u) const { 
        return this->p[u]; 
    }

    int Dijkstra::calcularDistancia (int origem, int v) {
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

    /* Imprime Arestas com os pesos */
    void Dijkstra::imprime () {
        int d;
        for (int u = 0; u < this->grafo->_numVertices (); u++) {
            d = calcularDistancia (this->raiz, u);
            if (d >= 0) {
                cout << "Vértice: " << u+1 << " Id: " << this->grafo->_id(u) <<
                " Distância de " << this->raiz+1 << ": " << d << endl;
            } else {
                cout << "Vértice: " << u+1 << " Id: " << this->grafo->_id(u) <<
                " Distância de " << this->raiz+1 << ": NIL" << endl;
            }
        }
    }

    /* Imprime caminho mínimo */
    void Dijkstra::imprimeCaminho (int origem, int v) const {
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
