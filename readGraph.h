#ifndef READG_H_
#define READG_H_
#include "listaAdj/Grafo.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using listaAdj::Grafo;

namespace readI {

	class readGraph {
	private:
	    int numV;
	    int u,v,p;
            string id;
	    Grafo *grafo;

	public:

            void readName(string s);
	    readGraph(string s);
	    ~readGraph();

	    Grafo *_grafo();
	};

        void readGraph::readName(string s) {
            std::ifstream tgf(s);
            string line, word;

            numV = 0;
            bool found_del = false;
            if(tgf.is_open()) {
                while(getline(tgf, line)) {
                    if(line == "#") {
                        found_del = true;
                    } else {
                        if (!found_del) {
                            std::istringstream iss(line);
 
                            iss >> word;
                            u = std::atoi(word.c_str());
                            word.clear();

                            iss >> word;
                            id = word;
                            word.clear();

                            grafo->insereVertice (u-1, id);
                        }
                    }
                }
            }
        }

	readGraph::readGraph(string s) {
	    std::ifstream tgf(s);
	    string line, word;
	
	    numV = 0; 
	    bool found_del = false;
	    if(tgf.is_open()) {
	        while(getline(tgf, line)) {
	            if(line == "#") { 
		        found_del = true;
			grafo = new Grafo (numV);
		    } else {
	                if(!found_del) { 
			    numV++;

			} else {
			    std::istringstream iss(line);

			    iss >> word;
			    u = std::atoi(word.c_str());
			    word.clear();

			    iss >> word;
			    v = std::atoi(word.c_str());
			    word.clear();

			    iss >> word;
			    p = std::atoi(word.c_str());
			    word.clear(); 

			    if (!grafo->existeAresta(u-1,v-1)) {
			        grafo->insereAresta(u-1,v-1,p);
			    } else {
				cout << "Arestas repetidas! Ignorando recorrências. \n";
			    }
			}
	       	    } 
	        }
	    } else {
	   	cout << "Can´t open textfile!" << endl;
	    }
	}

	readGraph::~readGraph() {
	    this->grafo = NULL;
	}

	Grafo *readGraph::_grafo() {
	    return this->grafo;
	}
   
}
#endif
