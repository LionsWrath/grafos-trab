#ifndef FPHEAPMININDIRETO_H_
#define FPHEAPMININDIRETO_H_

#include <iostream>
#include <stdexcept> 

using std::logic_error;
using std::cout;
using std::endl;

namespace grafos {

    /* Definição do Header da Classe FPHeapMinIndireto */
    class FPHeapMinIndireto {
    private:

        double *p; 
        int n, *pos, *fp;

    public:

        /* Protótipo das Funções */
        FPHeapMinIndireto (double *p, int *v, int n);
	~FPHeapMinIndireto ();
        
        void refaz (int esq, int dir) const;
	void constroi () const;
	int retiraMin () throw (logic_error);
	void diminuiChave (int i, double chaveNova) throw (logic_error);
	bool vazio () const;
	void imprime () const;
	
    };
    /* Fim da Definição do Header da Classe FPHeapMinIndireto */

    //-----------[ Implementação ]

    /* Construtor */
    FPHeapMinIndireto::FPHeapMinIndireto (double *p, int *v, int n) { 
        this->p = p; 
        this->fp = v; 
        this->n = n;
	this->pos = new int[this->n];

	for (int u = 0; u < this->n; u++) { 
            this->pos[u] = u+1;
        }
    }

    /* Destrutor */
    FPHeapMinIndireto::~FPHeapMinIndireto () {
        this->p = NULL; 
        this->fp = NULL; 
        delete [] this->pos;
    }

    /*--- Funções para manipulação do Heap ---*/

    /* Reconfigura o Heap */
    void FPHeapMinIndireto::refaz (int esq, int dir) const {
        int j = esq * 2;
        int x = this->fp[esq];
        
        while (j <= dir) {
            if ((j < dir) && (this->p[fp[j]] > this->p[fp[j + 1]])) { 
                j++;
            }

            if (this->p[x] <= this->p[fp[j]]) { 
                break;
            }

            this->fp[esq] = this->fp[j]; 
            this->pos[fp[j]] = esq; 
            esq = j; 
            j = esq * 2;
        }

    this->fp[esq] = x; 
    this->pos[x] = esq;
    }

    /* Chama a função refaz para cada nó da árvore, reogarnizando-a */
    void FPHeapMinIndireto::constroi () const {
        int esq = n / 2 + 1;
        while (esq > 1) { 
            esq--; 
            this->refaz (esq, this->n); 
        }
    }
 
    /* Retira o menor elemento do Heap */
    int FPHeapMinIndireto::retiraMin () throw (logic_error) {
        int minimo;
        if (this->n < 1) { 
            throw logic_error ("Erro: heap vazio");
        } else {
            minimo = this->fp[1]; 
            this->fp[1] = this->fp[this->n];
            this->pos[fp[(this->n)--]] = 1; 
            this->refaz (1, this->n);
        }
        return minimo;
    }

    /* Muda a chave atual com a chave nova */ 
    void FPHeapMinIndireto::diminuiChave (int i, double chaveNova) throw (logic_error) {
	    i = this->pos[i]; 
            int x = fp[i];
	    
            if (chaveNova < 0) {
	        throw logic_error ("Erro: chaveNova com valor incorreto");
            }

            this->p[x] = chaveNova;
	    while ((i > 1) && (this->p[x] <= this->p[fp[i / 2]])) {
	        this->fp[i] = this->fp[i / 2]; 
                this->pos[fp[i / 2]] = i; 
                i /= 2;
            }
	    
            this->fp[i] = x; 
            this->pos[x] = i;
    }

    /* Verifica se o Heap está vazio */
    bool FPHeapMinIndireto::vazio () const { 
        return this->n == 0; 
    }

    /* Imprime o Heap */
    void FPHeapMinIndireto::imprime () const {
        for (int i = 1; i <= this->n; i++) {
	    cout << this->p[fp[i]] << " ";
        }
	cout << endl;
    }

}

#endif 
