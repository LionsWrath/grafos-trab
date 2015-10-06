#ifndef GRAFO_H_
#define GRAFO_H_
#include <iostream>

using std::cout;
using std::endl;

namespace matrizadj {

        /* Definição do Header da Classe Grafo */
	class Grafo {

	public:

	class Aresta {
        private:

	    int v1;
	    int v2;
	    int peso;
 
	public:
 
            /* Definição da Classe Aresta */
	    Aresta (int v1, int v2, int peso) {
		this->v1 = v1;
		this->v2 = v2; 
		this->peso = peso;
	    }

	    ~Aresta () {}

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

	    int **mat;
    	    int numVertices;
    	    int *pos; 

	public:

            /* Protótipos das Funções */
    	    Grafo (int numVertices);	  
    	    Grafo (int numVertices, int numArestas);
	    ~Grafo ();
	  
	    void insereAresta (int v1, int v2, int peso);
	    bool existeAresta (int v1, int v2) const;
	    bool listaAdjVazia (int v) const;
	    Aresta *primeiroListaAdj (int v);
	    Aresta *proxAdj (int v);
	    Aresta *retiraAresta (int v1, int v2);
	    void imprime () const ;
	    int _numVertices () const;

            Grafo *grafoTransposto ();	  
	};
        /* Fim do Header da Classe Grafo */

        //-------------[ Implementação ]

        /* Construtor com número de vértices */
	Grafo::Grafo (int numVertices) {
            /* Construindo a matriz */
            this->mat = new int*[numVertices];

    	    for (int i = 0; i < numVertices; i++) {
      	        this->mat[i] = new int[numVertices];
	    }

	    this->pos = new int[numVertices]; 
    	    this->numVertices = numVertices;
 
            /* Inicializando a matriz com 0 */
    	    for (int i = 0; i < this->numVertices; i++) {
      	        for (int j = 0; j < this->numVertices; j++) {
		    this->mat[i][j] = 0;
		}
	        this->pos[i] = -1;
            }
        }

        /* Construtor com número de vértices e arestas */
        Grafo::Grafo (int numVertices, int numArestas) {
            this->mat = new int*[numVertices];

            for (int i = 0; i < numVertices; i++) {
                this->mat[i] = new int[numVertices];
            }
    
            this->pos = new int[numVertices]; 
            this->numVertices = numVertices; 
    
            for (int i = 0; i < this->numVertices; i++) {
                for (int j = 0; j < this->numVertices; j++) { 
                    this->mat[i][j] = 0; 
                }
                this->pos[i] = -1;
            }
        }

        /* Destrutor da classe */
        Grafo::~Grafo () {
  	    for (int i = 0; i < numVertices; i++) {
                delete [] this->mat[i];
            }
            delete [] this->mat;
            delete [] this->pos;
        }

        /*--- Funções de manipulação do Grafo ---*/

        void Grafo::insereAresta (int v1, int v2, int peso) {
            this->mat[v1][v2] = peso; 
        }
  
        bool Grafo::existeAresta (int v1, int v2) const {
            return (this->mat[v1][v2] > 0);
        }

        /* Verifica se a Lista de Adjacência está vazia */
        bool Grafo::listaAdjVazia (int v) const {
            for (int i = 0; i < this->numVertices; i++) {
                if (this->mat[v][i] > 0) return false;
            }
            return true;
        }

        /* Pega a primeira aresta da lista de adjacência */
        Grafo::Aresta *Grafo::primeiroListaAdj (int v) {
            this->pos[v] = -1; return this->proxAdj (v);
        }

        /* Pega a próxima aresta da lista de adjacência */
        Grafo::Aresta *Grafo::proxAdj (int v) { 
            this->pos[v] ++;

            while ((this->pos[v] < this->numVertices) && (this->mat[v][this->pos[v]] == 0)) {
                this->pos[v]++;
            }

            if (this->pos[v] == this->numVertices) {
                return NULL;
            } else { 
                return new Aresta (v, this->pos[v], this->mat[v][this->pos[v]]);
            }
        }

        /* Retira a aresta da matriz */
        Grafo::Aresta *Grafo::retiraAresta (int v1, int v2) {
            if (this->mat[v1][v2] == 0) {
                return NULL;
            } else {
                Aresta *aresta = new Aresta (v1, v2, this->mat[v1][v2]);
                this->mat[v1][v2] = 0; 
                return aresta;
            }
        }

        /* Imprime a matriz */
        void Grafo::imprime () const {
            cout << "   ";
            for (int i = 0; i < this->numVertices; i++) {
                cout << i << "   "; 
            }
            cout << endl;

            for (int i = 0; i < this->numVertices; i++) { 
                cout << i <<  "  ";
                for (int j = 0; j < this->numVertices; j++) {
                    cout << this->mat[i][j] << "   ";
                }
                cout << endl;
            }
        }

        /* GetVertices */
        int Grafo::_numVertices () const {
            return this->numVertices; 
        }

        /* Calcular o grafo transposto */
        Grafo *Grafo::grafoTransposto () {
            Grafo *grafoT = new Grafo (this->numVertices);

            for (int v = 0; v < this->numVertices; v++)
                if (!this->listaAdjVazia (v)) {
                    Aresta *adj = this->primeiroListaAdj (v);
                    while (adj != NULL) {
                        grafoT->insereAresta (adj->_v2 (), adj->_v1 (), adj->_peso ());
                        cout << adj->_v2() << "," << adj->_v1 << endl;
                        delete adj;
                        adj = this->proxAdj (v);
                    }
                }
            return grafoT;
        }
  
}

#endif 

		
