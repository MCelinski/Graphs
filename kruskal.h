    #pragma once
    using namespace std;
    #include "graph.h"

    //Klasa implementujaca algorytm Kruskala dla odpowiedniej reprezentacji grafu
    class Kruskal
    {
        public:
        static int kruskalList(Graph::AdjacencyList adjacencyList); //Metoda wykonujaca algorytm Kruskala dla reprezentacji listowej
        static int kruskalMatrix(Graph::IncidenceMatrix incidenceMatrix); //Metoda wykonujaca algorytm Kruskala dla reprezentacji macierzowej
    };



