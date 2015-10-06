#ifndef CFC_H_
#define CFC_H_
#include "listaAdj/Grafo.h"
#include "BuscaEmProfundidade.h"
#include <iostream>

using std::cout;
using std::endl;
using listaAdj::Grafo; 

namespace grafos {
    
    /* Definição do Header da classe Cfc */
    class Cfc	{
    
    private:
        
        /* Definição da classe tempo término */
        class TempoTermino {
	    friend class Cfc;
	    private:

	        int numRestantes, numVertices, *t;
	        bool *restantes;

	    public:

                /* Construtor */
	        TempoTermino (int numVertices) {
	            this->t = new int[numVertices];      
	            this->restantes = new bool[numVertices];
	            this->numVertices = this->numRestantes = numVertices;
	        }

                /* Destrutor */
                ~TempoTermino () {
	    	    delete [] t; 
                    delete [] restantes;
	        }

                /* Retorna o maior tempo de termino */
	        int maxTT () {
	            int vMax = 0;

	            while (!this->restantes[vMax]) { 
                        vMax++;
                    }

	            for (int i = 0; i < this->numVertices; i ++) {
	                if (this->restantes[i]) {
	                    if (this->t[i] > this->t[vMax]) { 
                                vMax = i;
                            }
	                }
	            }
	            return vMax;
	        } 
	};
        /* Fim da definição da classe TT */

	Grafo *grafo;

        /* Protótipos das Funções */
	void visitaDfs (Grafo *grafo, int u, TempoTermino *tt) const;
	
        public:
            
	    Cfc (Grafo *grafo);
            ~Cfc ();

	    void obterCfc () const;   
    };
    /* Fim da definição da classe Cfc */

    //--------------[ Implementação ]
    
    /* Função recursiva de Visita do DFS */
    void Cfc::visitaDfs (Grafo *grafo, int u, TempoTermino *tt) const {
        tt->restantes[u] = false; 
        (tt->numRestantes) --;    
        cout << u+1 << " ";
   
        if (!grafo->listaAdjVazia(u)) {
            Grafo::Aresta *a = grafo->primeiroListaAdj (u);
            while (a != NULL) {
                int v = a->_v2 ();
                if (tt->restantes[v]) { 
                    this->visitaDfs (grafo, v, tt); 
                }
                delete a; 
                a = grafo->proxAdj (u);
            }
        }
    }

    /* Contrutor do Cfc */
    Cfc::Cfc (Grafo *grafo) { 
        this->grafo = grafo; 
    }

    /* Destrutor */
    Cfc::~Cfc () { 
        this->grafo = NULL; 
    }

    /* Verificar Cfc */
    void Cfc::obterCfc () const {
        BuscaEmProfundidade dfs (this->grafo);
        dfs.buscaEmProfundidade ();

        TempoTermino *tt = new TempoTermino (this->grafo->_numVertices ());
        
        for (int u = 0; u < this->grafo->_numVertices (); u++) {
            tt->t[u] = dfs._t (u); 
            tt->restantes[u] = true;
        }

        Grafo *grafoT = this->grafo->grafoTransposto ();
    
        while (tt->numRestantes > 0) {
            int vRaiz = tt->maxTT ();
            cout << "CFC : ";
            this->visitaDfs (grafoT, vRaiz, tt);
            cout << endl;
        }

        delete tt; 
        delete grafoT;
    }  
    
}
#endif 
