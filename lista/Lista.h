#ifndef LISTA_H_
#define LISTA_H_
#include <stdexcept>
#include <iostream>

using std::logic_error;
using std::cout;
using std::endl;

namespace lista_autoreferencia {
    template <class T> class Lista {
        /* Definição do header da classe Lista */
        private:

            /* Implementação da Classe Celula */
            class Celula {
                friend class Lista<T>;

	        private:
		    T *item;
	            Celula *prox;

		    Celula () {
                        item = 0; 
                        prox = 0; 
                    }

		    ~Celula () { 
                        if (item != 0) {
                            delete item;
                        }
                    }
	    };
            /* Fim da implementação da Classe Celula */

	    Celula *primeiro, *ultimo, *pos;

	public:

            /* Protótipos das Funções */
	    Lista ();
		Lista (const Lista<T>& ls);
            ~Lista ();
		Lista<T>& operator=(const Lista<T>& ls);

	    T *pesquisa (const T& chave) const;
	    void insere (const T& x);
	    void inserePrimeiro (T& item);
	    T *retira (const T& chave) throw ( logic_error );
	    T *retiraPrimeiro () throw ( logic_error );
            T *_primeiro ();
            T *proximo ();
	    bool vazia () const;
	    void imprime () const;
    };
    /* Fim da Definição do Header da classe Lista */

    //--------------[ Implementação ]

    /* Implementação das Funções de Manipulaçao da Lista */

    /* Construtor */
    template <class T> Lista<T>::Lista () {
	this->primeiro = new Celula ();
        this->pos = this->primeiro;
	this->ultimo = this->primeiro;
        this->primeiro->prox = 0;
    }

	/*--- Copy constructor ---*/
	template <class T> Lista<T>::Lista (const Lista<T>& ls) {
		*this = ls;
	}

    /* Destrutor */
    template <class T> Lista<T>::~Lista () {
	  Celula *aux = this->primeiro;
	  while (aux != 0) {
	  	this->primeiro = this->primeiro->prox;
	  	delete aux; aux = this->primeiro;
	  }
	}

	template <class T> Lista<T>& Lista<T>::operator=(const Lista<T>& ls) {
		this->primeiro = ls.primeiro;
		this->ultimo = ls.ultimo;
		this->pos = ls.pos;

		return *this;
	}

    /* Insere um objeto na lista  */
    template <class T>	
        void Lista<T>::insere (const T& x) {  
	    this->ultimo->prox = new Celula (); 
	    this->ultimo = this->ultimo->prox; 
	    this->ultimo->item = new T (x);
            this->ultimo->prox = 0;
	}

    /* Insere um Objeto na primeira posição */
    template <class T>	
        void Lista<T>::inserePrimeiro (T& item) {
            Celula *aux =  this->primeiro->prox;
            this->primeiro->prox = new Celula ();
            this->primeiro->prox->item = new T(item);
            this->primeiro->prox->prox = aux;
        }

    /* Pesquisa um por um objeto na lista usando uma chave */
    template <class T>	
	T *Lista<T>::pesquisa (const T& chave) const {
	    if (this->vazia ()) { 
                return 0;
            }

	    Celula *aux = this->primeiro;
	    while (aux->prox != 0) {
	        if (*(aux->prox->item) == chave) return aux->prox->item;
	        aux = aux->prox;
	    }
	    return 0;
	}

    /* Retira um objeto da Lista usando uma chave */
    template <class T>	
        T *Lista<T>::retira (const T& chave) throw ( logic_error ) {
	    if (this->vazia ()) {
                throw logic_error ("Erro: A lista esta vazia");
            }

	    Celula *aux = this->primeiro;
	    while (aux->prox != 0 && *(aux->prox->item) != chave) {
                aux=aux->prox;
            }
	  
            if (aux->prox == 0) { 
                return 0; 
            }

	    Celula *q = aux->prox;
	    T *item = q->item; 
            aux->prox = q->prox;
	    q->item = 0;
	    
            if (aux->prox == 0){
                this->ultimo = aux;
            }

	    delete q;
            return item;
	}		
    
    /* Retira o primeiro item da lista */
    template <class T>	
        T *Lista<T>::retiraPrimeiro () throw ( logic_error ) {
	    if (this->vazia ()) {
                throw logic_error ("Erro: A lista esta vazia");
            }

	    Celula *aux = this->primeiro;
	    Celula *q = aux->prox;
	    T *item = q->item; 
            aux->prox = q->prox;
	    q->item = 0;

	    if (aux->prox == 0) {
                this->ultimo = aux;
            }

	    delete q; 
            return item;
        }
    
    /* Get primeiro elemento */
    template <class T> T *Lista<T>::_primeiro () {
        this->pos = this->primeiro; 
        return this->proximo ();
    }

    /* Retorna o próximo elemento de acordo com a variável pos */
    template <class T> T *Lista<T>::proximo () {
        this->pos = this->pos->prox;
        if (this->pos == NULL) {
            return NULL;
        } else { 
            return this->pos->item;
        }
    }

    /* Verifica se a lista está vazia */
    template <class T>
	bool Lista<T>::vazia () const { 
	    return (this->primeiro == this->ultimo);
	}

    /* Imprime a lista */
    template <class T>	
	void Lista<T>::imprime () const {
	    Celula *aux = this->primeiro->prox;
	    while (aux != 0) {
                cout << *(aux->item) << endl; 
                aux = aux->prox; 
                }
	}

}
#endif 
