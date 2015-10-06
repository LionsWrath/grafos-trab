#ifndef BELLMAN_H_
#define BELLMAN_H_
#include "listaAdj/Grafo.h"
#include <float.h>
#include <iostream>

#define INF 99999

using std::cout;
using std::endl;
using listaAdj::Grafo;

namespace grafos {

    /* Definição do Header da Classe Bellman */
    class Bellman {
    private:

        int *antecessor;
        double *p;
        int raiz;
        Grafo *grafo;

    public:
       
        /* Protótipos das Funções */
        Bellman (Grafo *grafo, int raiz);
        ~Bellman ();
    
        bool obterArvore () throw (logic_error);
        int _antecessor (int u) const;
        double _peso (int u) const;
        int calcularDistancia (int origem, int v);
        void imprime (); 
        void imprimeCaminho (int origem, int v) const;

    };
    /* Fim da definição do Header da Classe Bellman */

    //-----------[ Implementação ]

    /* Construtor */
    Bellman::Bellman (Grafo *grafo, int raiz) {
        this->grafo = grafo;
        this->raiz = raiz-1;
        this->antecessor = NULL;
        this->p = NULL;
    }

    /* Destrutor */
    Bellman::~Bellman () {
        this->grafo = NULL;
        if (this->p) {
            delete [] this->p;
        }

        if (this->antecessor) {
            delete [] this->antecessor;
        }
    }

    /* Aplicar Bellman-Ford */
    bool Bellman::obterArvore () throw (logic_error) {
        int n = this->grafo->_numVertices();
        
        //Reinicia o vetor de pesos
        if (this->p) {
            delete [] this->p;
        }
        this->p = new double[n];
        
        //Reinicia o vetor de antecessores
        if (this->antecessor) {
            delete [] this->antecessor;
        }
        this->antecessor = new int[n];

        /* Inicializando (Initializing Single Source) */
        for (int u = 0; u < n; u++) {
            this->antecessor[u] = -1;
            p[u] = INF;
        }
        p[raiz] = 0;


        for (int i = 0; i < n-1; i++) {
            for (int j = 0; j < n; j++) {
                Grafo::Aresta *adj = grafo->primeiroListaAdj(j);
                while(adj != NULL) { 
                    int v = adj->_v2 ();
                    
                    //Relax
                    if (this->p[v] > (this->p[j] + adj->_peso ())) {
                        this->p[v] = p[j] + adj->_peso ();
                        this->antecessor[v] = j;
                    }

                    delete adj;
                    adj = grafo->proxAdj(j);
                }
            }               
        }

        /* Verifica arestas negativas */
        for (int j = 0; j < n; j++) {
            Grafo::Aresta *adj = grafo->primeiroListaAdj(j);
            while (adj != NULL) {
                int v = adj->_v2 ();

                if (this->p[v] > (this->p[j] + adj->_peso ())) { 
                    return false;
                }
                delete adj;
                adj = grafo->proxAdj(j);
            }
        }
        return true;
    }

    /* GetAntecessor */
    int Bellman::_antecessor (int u) const {
        return this->antecessor[u];
    }

    /* GetPeso */
    double Bellman::_peso (int u) const {
        return this->p[u];
    }

    int Bellman::calcularDistancia (int origem, int v) {
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

    /* Imprime o grafo */
    void Bellman::imprime () {
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

    /* Imprime o Caminho Mínimo */
    void Bellman::imprimeCaminho (int origem, int v) const {
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
