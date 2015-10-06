#include "Bellman.h"
#include "BuscaEmProfundidade.h"
#include "Dijkstra.h"
#include "FWarshall.h"
#include "BuscaEmLargura.h"
#include "Cfc.h"
#include "Topological.h"
#include "listaAdj/Grafo.h"
#include "readGraph.h"

#include <string>
#include <iostream>
#include <unistd.h>

using readI::readGraph;
using std::cout;
using std::cin;
using std::endl;
using grafos::BuscaEmProfundidade;
using grafos::BuscaEmLargura;
using grafos::Topological;
using grafos::Cfc;
using grafos::Dijkstra;
using grafos::Bellman;
using grafos::FWarshall;

int main (int argc, char *argv[]) {
    string filename;
    Grafo *grafo;

    int oc;
    int raiz = 1;
    string id;
    bool pm = false;

    while ((oc = getopt(argc, argv, "ma:i:r:")) != -1) {
        switch (oc) {
            case 'm':
                pm = true;
                break;
            case 'a':
                id = optarg;
                break;
            case 'i':
                filename = optarg;
                break;
            case 'r':
                raiz = std::atoi(optarg);
                break;
            case ':':
                cout << argv[0] << ": Opção -" << optopt << " precisa de um argumento." << endl;
                break;
            case '?':
            default:
                cout << argv[0] << ": Opção -" << optopt << " inválida! Ignorada." << endl;
                id = "BEM";
                break;

        }
    }

    //cout << "Digite o nome do arquivo: ";
    //cin >> filename;
    //cout << endl;

    readGraph rd (filename);
    rd.readName(filename);
    grafo = rd._grafo();

    if (pm) {
        grafo->imprime();
        cout << endl;
    }

    if (id.compare("dfs") == 0) {

        BuscaEmProfundidade dfs (grafo);
        dfs.buscaEmProfundidade ();
        dfs.imprime ();

    } else if (id.compare("bfs") == 0) {

        BuscaEmLargura bfs (grafo, raiz);
        bfs.buscaEmLargura ();
        bfs.imprime ();
    
    } else if (id.compare("tp") == 0) {

        Topological tp (grafo);
        tp.obterTopological ();
        tp.imprime();

    } else if (id.compare("scc") == 0) {
    
        Cfc cfc (grafo);
        cfc.obterCfc ();

    } else if (id.compare("dk") == 0) {
    
        Dijkstra dj (grafo,raiz);
        dj.obterArvoreCMC ();
        dj.imprime();
    
    } else if (id.compare("bm") == 0) {

        Bellman bm (grafo, raiz);
        bm.obterArvore();
        bm.imprime();

    } else if (id.compare("fw") == 0) {
    
        FWarshall fw (grafo);
        fw.imprime ();

    } else {

        cout << "Opção " << id << " incorreta!" << endl;
    
    }

    delete grafo;
    return 0;
}
