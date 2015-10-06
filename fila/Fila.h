#ifndef FILA_H_
#define FILA_H_
#include <stdexcept> 
#include<iostream>

using std::logic_error;
using std::cout;
using std::endl;

namespace fila_autoreferencia {

    /* Definição do Header da Classe Fila */
    template <class T> class Fila {
    private:

        /* Definição da Classe Fila */
        class Celula {

	    friend class Fila<T>;

	private:

	    T *item; Celula *prox;
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
        /* Fim da Definição da Classe Fila */

	    Celula *frente, *tras;
	
        public:

            /* Protótipos das Funções */
	    Fila ();
            ~Fila ();

	    void enfileira (const T& x);
	    T *desenfileira () throw ( logic_error );
	    bool vazia () const;
	    void imprime () const;

    };
    /* Fim da definição do Header da Classe Fila */

    //----------[ Implementação ]

    /* Construtor - Cria uma fila vazia */
    template <class T>
    Fila<T>::Fila () { 
	this->frente = new Celula ();
	this->tras = this->frente; 
        this->frente->prox = 0;
    }

    /* Destrutor */  
    template <class T>	
    Fila<T>::~Fila () {		
        Celula *aux = this->frente;
        while (aux != 0) {
      	this->frente = this->frente->prox; 
            delete aux;
            aux = this->frente;
        }
    }

    /* Pega o parâmeto e enfileira */
    template <class T>	
    void Fila<T>::enfileira (const T& x) {
	this->tras->prox = new Celula ();
        this->tras = this->tras->prox; 
        this->tras->item = new T (x); 
	this->tras->prox = 0;
    }

    /* Retira o próximo item da fila */
    template <class T>	
    T *Fila<T>::desenfileira () throw ( logic_error ) {
        if (this->vazia ()) { 
            throw logic_error ("Erro: A fila esta vazia");
        }
	    
        Celula *aux = this->frente;
        this->frente = this->frente->prox;
	T *item = this->frente->item;
	this->frente->item = 0;

	delete aux;
	return item;
    }

    /* Verifica se a fila está vazia */
    template <class T>
    bool Fila<T>::vazia () const {
    	return (this->frente == this->tras);
    }

    /* Imprime a Fila */
    template <class T>	
    void Fila<T>::imprime () const {
        Celula *aux = this->frente->prox;
        while (aux != 0) {
            cout << *(aux->item) << endl; 
            aux = aux->prox;
	}
    }

}
#endif 
