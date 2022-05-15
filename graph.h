#pragma once
using namespace std;
//Klasa implementujaca reprezentacje grafu jak i metody jego tworzenia i wyswietlania
class Graph{
private:


public:
    //Struktura macierzy incydencji
    struct IncidenceMatrix
    {
        signed char ** matrix;
        int pointNb;
        int edgeNb;
    } incidenceMatrix;

    //Struktura elementu listy sasiedztwa
    struct AdjacencyListEl
    {
      AdjacencyListEl * next;
      int endPoint;
      int weight;
    } adjacencyListEl;

    //Struktura listy sasiedztwa
    struct AdjacencyList
    {
        AdjacencyListEl ** aList;
        int pointNb;
        int edgeNb;
    } adjacencyList;

    //konstruktor bezargumentowy
    Graph();
    int createIncidenceMatrix(string,IncidenceMatrix&); //Funkcja tworzaca macierz incydencji
    int printIncidenceMatrix(IncidenceMatrix&); //Funkcja wyswietlajaca macierz incydencji
    int createAdjacencyList(string,AdjacencyList&); //Funkcja tworzaca liste sasiedztwa
    int printAdjacencyList(AdjacencyList&); //Funkcja wyswietlajaca liste sasiedztwa
    int generateGraph(int,float); //Funkcja generujaca dowolny graf wedlug zadanych parametrow
    int mixTable(int[],int); //Funkcja mieszajaca tablice
    int checkEdge(string,string); //Funkcja sprawdzajaca czy istnieje juz taka krawedz w grafie
    //destruktor
    ~Graph( );
};
