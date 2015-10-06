#ifndef GRAFO_H_
#define GRAFO_H_
#include "../lista/Lista.h"
#include <iostream>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::ostream;
using std::map;
using std::string;
using lista_autoreferencia::Lista; 

namespace listaAdj {
        
        /* Definição do Header da Classe Grafo */
        class Grafo {

	public:

            /* Definição da Classe Aresta */
            class Aresta {
	    private:

	        int v1;
                int v2;
                int peso; 

            public:
 
                Aresta (int v1, int v2, int peso) {
	            this->v1 = v1;
                    this->v2 = v2;
                    this->peso = peso;
	        }

                ~Aresta(){}

                /* GetPeso */
	        int _peso () { 
                    return this->peso; 
                }

                /* GetV1 */
	        int _v1 () { 
                    return this->v1; 
                }

                /* GetV2 */
	        int _v2 () { 
                    return this->v2; 
                }
	    
	    };
          /* Fim da definição da Classe Aresta */

            private:

	        class Celula {

                    /* Classe Grafo "Amiga" */
                    friend class Grafo;
                    friend ostream& operator<< (ostream& out, const Celula& celula) {
                        out << "vertice:" << celula.vertice << endl;
                        out << "peso:"    << celula.peso    << endl;
                        return out;
                    }

	    	    private:

	                int vertice;
                        int peso;

	            public:

                        /* Definição da Classe Aresta  */
	                Celula (int v, int p) {
	    	            this->vertice = v; 
                            this->peso = p;
	                }

                        ~Celula () {}

	                Celula (const Celula& cel) { 
                            *this = cel; 
                        }

                        /* Overloaded Operator  */
                        bool operator== (const Celula& celula) const {
                            return this->vertice == celula.vertice;
                        }

                        /* Overloaded Operator  */
                        bool operator!= (const Celula& celula) const {
                            return this->vertice != celula.vertice;
                        }

                        /* Overloaded Operator  */
                        const Celula& operator= (const Celula& cel) {     
                            this->vertice = cel.vertice; 
                            this->peso = cel.peso;
                            return *this;
                        }      	    
	        };
                /* Fim da definição da Classe Aresta  */

                Lista<Celula> *adj;
				std::map<int, string> id;
                int numVertices;

            public:

                /* Protótipos das Funções  */
                Grafo (int numVertices);	  
                Grafo (int numVertices, int numArestas);
                ~Grafo ();	

	        void insereAresta (int v1, int v2, int peso);
			void insereVertice (int v1, string id);
	        bool existeAresta (int v1, int v2) const;
	        bool listaAdjVazia (int v) const;
	        Aresta *primeiroListaAdj (int v);
	        Aresta *proxAdj (int v);
	        Aresta *retiraAresta (int v1, int v2);
	        void imprime () ;
			string _id (int b);
	        int _numVertices () const;
	        
                Grafo *grafoTransposto ();     
            };
            /* Fim do Header da Classe Aresta  */

            //------------[ Implementação  ]
            /* Construtor com número de vértices  */
            Grafo::Grafo (int numVertices) {
  	        this->adj = new Lista<Celula>[numVertices]; 
  	        this->numVertices = numVertices; 	  	
            }

            /* Construtor com número de vértices e arestas  */
            Grafo::Grafo (int numVertices, int numArestas) {
  	        this->adj = new Lista<Celula>[numVertices]; 
  	        this->numVertices = numVertices; 	  	
            }

            /* Destrutor  */
            Grafo::~Grafo () {
                delete [] this->adj;
            }

            /*--- Funções de manipulação do Grafo ---*/

            /* Insere uma Aresta no Grafo */
            void Grafo::insereAresta (int v1, int v2, int peso) {
                Celula item (v2, peso); 
                this->adj[v1].insere (item); 
            }

	    /* Insere id da Aresta */
	        void Grafo::insereVertice (int v1, string id) {
                this->id.insert (std::pair<int, string> (v1, id));
            }

            /* Verifique se a aresta existe */
            bool Grafo::existeAresta (int v1, int v2) const {
                Celula item (v2, 0);
                return (this->adj[v1].pesquisa (item) != NULL);
            }

            /* Verifica se a Lista de Adjacência está vazia  */
            bool Grafo::listaAdjVazia (int v) const {
		return this->adj[v].vazia ();  
            }


            /* Pega a primeira aresta da lista de adjacência */
            Grafo::Aresta *Grafo::primeiroListaAdj (int v) { 
                Celula *item = this->adj[v]._primeiro ();    
                return item != NULL ? new Aresta(v,item->vertice,item->peso) : NULL;
            }

            /* Pega a próxima aresta da lista de adjacência */
            Grafo::Aresta *Grafo::proxAdj (int v) {
                Celula *item = this->adj[v].proximo ();    
                return item != NULL ? new Aresta(v,item->vertice,item->peso) : NULL;
            }

            /* Retira a aresta da matriz */
            Grafo::Aresta *Grafo::retiraAresta (int v1, int v2) {
                Celula chave (v2, 0);
                Celula *item = this->adj[v1].retira (chave);
                Aresta *aresta = item != NULL ? new Aresta(v1,v2,item->peso) : NULL;
                delete item; 
                return aresta;
            }

            /* Imprime a matriz */
            void Grafo::imprime () {
                for (int i = 0; i < this->numVertices; i++) { 
                    cout << "Vertice " << i << "Id " << _id(i) << ":" << endl;
                    Celula *item = this->adj[i]._primeiro ();
                    while (item != NULL) {
                        cout << "  " << item->vertice << " (" <<item->peso<< ")" << endl;
                        item = this->adj[i].proximo ();
                    }
                }
            }

            /* GetVertices */
            int Grafo::_numVertices () const { 
                return this->numVertices; 
            }

	    /* Retorna o nome do vértice v */
		string Grafo::_id (int v) {
                return this->id[v];
            }

            /* Calcular o grafo transposto */
            Grafo *Grafo::grafoTransposto () {
                //cout << "Check" << endl;
                Grafo *grafoT = new Grafo (this->numVertices); 
                //cout << "Check" << endl;
                for (int v = 0; v < this->numVertices; v++) {
                    if (!this->listaAdjVazia (v)) {
                        Aresta *adj = this->primeiroListaAdj (v);
                        while (adj != NULL) {
                            grafoT->insereAresta (adj->_v2 (), adj->_v1 (), adj->_peso ()); 
                            delete adj;
                            adj = this->proxAdj (v);
                        }
                    }
                }
                return grafoT;
            }
             
}

#endif 

		
