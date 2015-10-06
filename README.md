--------------------------------------------------------------------------------

    Trabalho baseado nos algoritmos mostrados nos livros Projeto de Algoritmos
    (Ziviani), Algoritmos (Cormen) e Algoritmos (Sedgewick).

--------------------------------------------------------------------------------

    Todos os algoritmos estão implementados direto nos headers. Para
    Compilá-los, use o sequinte comando:
    
        g++ Main.cpp -o main -std=c++0x

    Para testá-los basta executar o comando "./main" com as seguintes flags:

        -m  |   Para imprimir o grafo criado do arquivo tgf(opcional)
        -i  |   Passe o arquivo tgf
        -a  |   Passe qual algoritmo quer testar. As opções são:
                  |  bfs - Para Busca em Largura
                  |  dfs - Para Busca em Profundidade
                  |  tp  - Para Ordenação Topológica
                  |  scc - Para Componentes Fortemente Conexos
                  |  dk  - Para Dijkstra
                  |  bm  - Para Bellman-Ford
                  |  fw  - Para Floyd-Warshall
        -r  |   Usado para passar a vértice inicial. Necessário somente para 
            |   a Busca em Largura, Dijkstra e Bellman-Ford.(Valor Default = 1)

--------------------------------------------------------------------------------
