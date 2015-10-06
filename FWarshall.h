#ifndef FWARSHALL_H_
#define FWARSHALL_H_
#include "listaAdj/Grafo.h"
#include <float.h>
#include <iostream>
#include <iomanip>

#define INF 99999

using std::cout;
using std::endl;
using listaAdj::Grafo;

namespace grafos {

    /* Definição do Header da classe FWarshall */
    class FWarshall {
    private:
    
        int **matD;
        int **pred;

        int n;
        bool id;

    public:

        Grafo *grafo;

        /* Protótipo das Funções */
        FWarshall (Grafo *grafo);
        FWarshall ();
        ~FWarshall ();

        void obterArvore () throw (logic_error);
        void imprime () const;
        void imprimePred () const;
        void imprimeCaminho (int i, int j);

    };
    /* Fim da definição do header da classe FWarshall */

    //---------[ Implementação ]

    /* Construtor */
    FWarshall::FWarshall (Grafo *grafo) {
        this->grafo = grafo;
        this->n = this->grafo->_numVertices ();
    
        this->pred = new int*[n];
        for (int i = 0; i < n; i++) {
            this->pred[i] = new int[n];
        } 

        /* Criando as matrizes */
        this->matD = new int*[n];
        for (int i = 0; i < n; i++) {
            this->matD[i] = new int[n];
        }

        /* Inicializando a matriz */
        for (int i = 0 ; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    matD[i][j] = 0;
                } else {
                    matD[i][j] = INF;
                }
            }
        }

        for (int j = 0; j < this->n; j++) {
            Grafo::Aresta *adj = grafo->primeiroListaAdj(j);
            while (adj != NULL) {
                int v = adj->_v2 ();

                matD[j][v] = adj->_peso ();

                delete adj;

                adj = grafo->proxAdj(j);
            }
        }

        for (int j = 0; j < this->n; j++) {
            for (int i = 0; i < this->n; i++) {
                if (i == j || matD[j][i] == INF) {
                    this->pred[j][i] = -1;
                } else {
                    this->pred[j][i] = i;
                }
            }
        }
    }

    /* Construtor (sem o grafo) */
    FWarshall::~FWarshall () {
        this->grafo = NULL;

        for (int i = 0; i < this->n; i++) {
            delete [] this->matD[i];
            delete [] this->pred[i];
        }
    }

    /* Algoritmo de Floyd Warshall */
    void FWarshall::obterArvore () throw (logic_error) {

        for (int k = 0; k < this->n; ++k) {
            for (int i = 0; i < this->n; ++i) {
                for (int j = 0; j < this->n; ++j) {
                    if (matD[i][j] > matD[i][k] + matD[k][j]) {
                        matD[i][j] = matD[i][k] + matD[k][j];
                        pred[i][j] = pred[k][j];
                    }
                }    
            }
        }
            this->id = !this->id;
    }

    /* Imprime o Grafo */
    void FWarshall::imprime () const {
        cout << std::setw(5);
        cout << "-" << " |";
        for (int i = 0; i < this->n; i++) {
            cout << std::setw(6);
            cout << "______";
            cout << std::setw(1);
            cout << i+1 << "|";
        }
        cout << endl;
        for (int i = 0; i < this->n; i++) {
            cout << std::setw(5);
            cout << i+1 << " | ";
            for (int j = 0; j < this->n; j++) {
                if (matD[i][j] != 99999) {
                    cout << std::setw(5);
                    cout << matD[i][j] << " | ";
                } else {
                    cout << std::setw(5);
                    cout << "INF" << " | ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    /* Imprime a matriz predecessora */
    void FWarshall::imprimePred () const {
        for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->n; j++) {
                if (pred[i][j] != -1) {
                    cout << std::setw(5);
                    cout << pred[i][j] << " | ";
                } else {
                    cout << std::setw(5);
                    cout << "NIL" << " | ";
                }
            }
            cout << endl;
        } 
        cout << endl;
    }

    /* Imprime o Caminho mínimo */
    void FWarshall::imprimeCaminho (int i, int j) {
//        if (i != j && pred[i][j] != -1) {
//            int aux = pred[i][j];
//            FWarshall::imprimeCaminho (i, aux);
//            cout << " -> " << j;
//        } else if (i == j) {
//            cout << j; 
//        } else {
//           cout << "Não possui caminho"; 
//        }
//        cout << endl;
    }

}
#endif
