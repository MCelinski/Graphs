#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include <string>
#include "graph.h"
using namespace std;


Graph::Graph()
{

}

/////////////////////////////////////////////////////////////////////////////
///////////////////////////MACIERZ INCYDENCJI////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
Graph::createIncidenceMatrix(string filePath,IncidenceMatrix &incidenceMatrix)
{

    int startPoint, endPoint,weight;
    fstream plik;
    plik.open( filePath, ios::in );
    if( plik.good() )
    {
        plik >> incidenceMatrix.pointNb;
        plik >> incidenceMatrix.edgeNb;
        incidenceMatrix.matrix = new signed char * [ incidenceMatrix.pointNb ];  // Tworzymy tablice wska�nikew
        for(int i = 0; i < incidenceMatrix.pointNb; i++ )
            incidenceMatrix.matrix [ i ] = new signed char [ incidenceMatrix.edgeNb ]; // Tworzymy wiersze

        // Macierz wypelniamy zerami
        for(int i = 0; i < incidenceMatrix.pointNb; i++ )
            for(int j = 0; j < incidenceMatrix.edgeNb; j++ )
                incidenceMatrix.matrix [ i ][ j ] = 0;

        // Odczytujemy kolejne definicje krawedzi
        for(int i = 0; i < incidenceMatrix.edgeNb; i++ )
        {
            plik >> startPoint >> endPoint >> weight;    // Wierzcholek startowy i koncowy krawedzi
            incidenceMatrix.matrix [ startPoint ][ i ] = weight;  // Wierzcholek startowy
            incidenceMatrix.matrix [ endPoint ][ i ] = weight*(-1); // Wierzcholek koncowy
        }
        plik.close();
    }
    else
        cout << "Error! Nie udalo otworzyc sie pliku!" << endl;
    return 0;
}

Graph::printIncidenceMatrix(IncidenceMatrix &incidenceMatrix)
{
    cout << endl;

    // Wypisujemy zawartosc macierzy incydencji
    cout << "   ";
    for(int i = 0; i < incidenceMatrix.edgeNb; i++ )
        cout << setw ( 3 ) << i;

    cout << endl << endl;

    for(int i = 0; i < incidenceMatrix.pointNb; i++ )
    {
        cout << setw ( 3 ) << i;
        for( int j = 0; j < incidenceMatrix.edgeNb; j++ )
            cout << setw ( 3 ) << ( int ) incidenceMatrix.matrix [ i ][ j ];
        cout << endl;
    }
    cout << endl;
    return 0;
}

/////////////////////////////////////////////////////////////////////////////
///////////////////////////LISTA SASIEDZTWA//////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
Graph::createAdjacencyList(string filePath,AdjacencyList &adjacencyList)
{
    int startPoint, endPoint,weight;
    AdjacencyListEl *p;

    fstream plik;
    plik.open( filePath, ios::in );

    if( plik.good() )
    {
        plik >> adjacencyList.pointNb;
        plik >> adjacencyList.edgeNb;

        adjacencyList.aList = new AdjacencyListEl * [ adjacencyList.pointNb ]; // Tworzymy tablicę list sąsiedztwa

        // Tablicę wypełniamy pustymi listami

        for(int i = 0; i < adjacencyList.pointNb; i++ )
            adjacencyList.aList [ i ] = NULL;

        // Odczytujemy kolejne definicje krawędzi

        for(int i = 0; i < adjacencyList.edgeNb; i++ )
        {
            plik >> startPoint >> endPoint >> weight;    // Wierzchołek startowy i końcowy krawędzi
            p = new AdjacencyListEl;    // Tworzymy nowy element
            p->endPoint = endPoint;
            p->weight = weight;
            p->next = adjacencyList.aList [ startPoint ]; // Dodajemy go na początek listy A [ v1 ]
            adjacencyList.aList[ startPoint ] = p;
        }
        plik.close();
    }
    else
        cout << "Error! Nie udalo otworzyc sie pliku!" << endl;
    return 0;
}

Graph::printAdjacencyList(AdjacencyList &adjacencyList)
{
    AdjacencyListEl *adjacencyListEl;
    cout << endl;

    // Wypisujemy zawartość tablicy list sąsiedztwa

    for(int i = 0; i < adjacencyList.pointNb; i++ )
    {
        cout << "A [ " << i << " ] =";
        adjacencyListEl = adjacencyList.aList [ i ];
        while( adjacencyListEl )
        {
            cout << setw ( 3 ) << adjacencyListEl->endPoint << "(" << adjacencyListEl->weight << ")";
            adjacencyListEl = adjacencyListEl->next;
        }
        cout << endl;
    }


    cout << endl;
    return 0;
}


/////////////////////////////////////////////////////////////////////////////
///////////////////////////LOSOWY GRAF//////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

Graph::generateGraph(int nodes,float density)
{
    int actualEdgesNumber=0;
    ofstream graphFile;
    graphFile.open ("rand_graph.txt");


    int edges = (int ) (( float ) ( nodes *( nodes -1) /2) * density /100) ;

    graphFile << nodes << " " << edges << endl;

    int * table = new int [ nodes ];
    for ( int i = 0; i < nodes ; i ++)
        table [ i ] = i ;
    // Tasowanie indeks ów wierzchołków
    mixTable ( table, nodes ) ;

    int n = 0;
    // Tworzenie tablicy indeksów wierzchołków należących do grafu
    int * table2 = new int [ nodes ];
    int tab2_len = 0;
    // Pętla tworząca graf spójny
    while ( n < nodes - 1 && actualEdgesNumber < edges )
    {
        table2 [ tab2_len ++] = table [ n ++];
        // Pobranie indeksu wierzcho łka nie połą czonego jeszcze z grafem
        int start = table [ n ];
        // Losowanie wierzchołka należącego do grafu
        int end = table2 [ rand () % tab2_len ];
        // Losowanie wartości wagi krawędzi
        int value =  rand () %10+1;
        // Dodanie krawędzi
        graphFile << start << " " << end << " " << value << endl;
        actualEdgesNumber++;
    }
    // Usuwanie zbędnej tablicy
    delete [] table2 ;


    // Pę tla dodająca pozostałe krawędzie
    while ( actualEdgesNumber < edges )
    {
        // Tasowanie indeksów wierzchołków
        mixTable ( table, nodes ) ;
        for (int i = 0, j = 1; i < nodes -1 && j < nodes && actualEdgesNumber < edges ; i ++)
        {
            // Pobranie pierwsszego wierzchołka
            int a = table [ i ];
            int r;
            // Losowanie liczby nowych krawędzi wychodzących z danego wierzchołka
            if( edges - actualEdgesNumber - 1 )
            {
                r = rand () % ( edges - actualEdgesNumber - 1) + 1;
                if( r > 0.4* nodes && nodes > 9)
                    r = r %( int ) (0.1*( float ) nodes );
            }
            else
                r = 1;
            while ( r > 0 && j < nodes )
            {
                int b = table [ j ++];
                if (! checkEdge (to_string(a), to_string(b) ))
                {
                    int value = rand () %10 + 1;
                    graphFile << a << " " << b << " " << value << endl;
                    actualEdgesNumber++;
                    r--;
                }
            }
            j = i +2;
        }
        for ( int i = 0; i < nodes ; i ++)
            table [ i ] = i ;
    }
    delete [] table ;
    graphFile.close();
    return 0;
}

Graph::mixTable(int table[],int nodes)
{
    for(int i=0; i<nodes; i++)
    {
        int randNode=rand () % nodes;
        if (randNode!=i)
        {
            swap(table[i],table[randNode]);
        }
    }
    return 0;
}

Graph::checkEdge(string start,string end)
{
    ifstream graphFile;
    graphFile.open ("rand_graph.txt");
    string searchString = start + " " + end;
    string line;
    size_t pos;
    while(getline(graphFile,line))
    {
        pos = line.find(searchString);
        if(pos!=string::npos) // string::npos is returned if string is not found
        {
            return true;
        }
    }
    return false;
}

