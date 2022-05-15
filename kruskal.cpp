//#pragma once
#include <iostream>
#include "graph.h"
#include "datastruct.h"
#include "kruskal.h"
#include <bits/stdc++.h>

using namespace std;


Kruskal::kruskalList(Graph::AdjacencyList adjacencyList)
{

    Edge edge;
    Graph::AdjacencyListEl *adjacencyListEl;
    DSStruct Z ( adjacencyList.pointNb );        // Struktura zbior�w roz��cznych
    Queue Q ( adjacencyList.edgeNb );           // Kolejka priorytetowa oparta na kopcu
    MSTree T ( adjacencyList.pointNb );          // Minimalne drzewo rozpinaj�ce


    for(int i = 0; i < adjacencyList.pointNb; i++ )
    Z.MakeSet ( i );       // Dla ka�dego wierzcho�ka tworzymy osobny zbi�r

    for(int i = 0; i < adjacencyList.pointNb; i++ )
    {
        adjacencyListEl = adjacencyList.aList [ i ];
        while( adjacencyListEl )
        {
            edge.startPoint = i;
            edge.endPoint = adjacencyListEl->endPoint;
            edge.weight = adjacencyListEl->weight;
            adjacencyListEl = adjacencyListEl->next;
            Q.push ( edge );   // umieszczanie krawedzi w kolejce priorytetowej
        }
    }


    for(int i = 1; i <  adjacencyList.pointNb ; i++ ) // P�tla wykonuje si� n - 1 razy !!!
    {
    do
    {
      edge = Q.front( );      // Pobieramy z kolejki kraw�d�
      Q.pop( );            // Kraw�d� usuwamy z kolejki
    } while( Z.FindSet ( edge.startPoint ) == Z.FindSet ( edge.endPoint ) );
    T.addEdge ( edge );       // Dodajemy kraw�d� do drzewa
    Z.UnionSets ( edge );     // Zbiory z wierzcho�kami ��czymy ze sob�
    }


    // Wyswietlamy wyniki
    cout <<endl<< "Algorytm Kruskala dla reprezentacji listowej:"<<endl<<endl;
    T.print( );

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

Kruskal::kruskalMatrix(Graph::IncidenceMatrix incidenceMatrix)
{

    Edge edge;
    DSStruct Z ( incidenceMatrix.pointNb );        // Struktura zbior�w roz��cznych
    Queue Q ( incidenceMatrix.edgeNb );           // Kolejka priorytetowa oparta na kopcu
    MSTree T ( incidenceMatrix.pointNb );          // Minimalne drzewo rozpinaj�ce


    for(int i = 0; i < incidenceMatrix.pointNb; i++ )
    Z.MakeSet ( i );       // Dla ka�dego wierzcho�ka tworzymy osobny zbi�r

    for(int i = 0; i < incidenceMatrix.edgeNb; i++ )
    {
        for(int j = 0; j < incidenceMatrix.pointNb;j++)
        {
            if (incidenceMatrix.matrix[j][i]>0)
            {
                edge.startPoint = j;
                edge.weight = incidenceMatrix.matrix[j][i];
            }
            else if(incidenceMatrix.matrix[j][i]<0)
                    edge.endPoint = j;
        }
        Q.push ( edge );
    }


    for(int i = 1; i <  incidenceMatrix.pointNb ; i++ ) // P�tla wykonuje si� n - 1 razy !!!
    {
    do
    {
      edge = Q.front( );      // Pobieramy z kolejki kraw�d�
      Q.pop( );            // Kraw�d� usuwamy z kolejki
    } while( Z.FindSet ( edge.startPoint ) == Z.FindSet ( edge.endPoint ) );
    T.addEdge ( edge );       // Dodajemy kraw�d� do drzewa
    Z.UnionSets ( edge );     // Zbiory z wierzcho�kami ��czymy ze sob�
    }


    // Wyswietlamy wyniki
    cout <<endl<< "Algorytm Kruskala dla reprezentacji macierzowej:"<<endl<<endl;
    T.print( );

    return 0;
}
