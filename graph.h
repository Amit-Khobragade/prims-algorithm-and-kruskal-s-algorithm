#pragma once
#include <iostream>
#include <vector>


class graph {
public:
	graph( int _vertices = 0, double density = 0 );
	graph( graph& _graph );  //deep copy needed due to the use of smart pointers
	int vertice_num() { return vertices; }
	int edge_num() { return num_of_edges;}
	void randomise_graph( double density = 0 );
	friend bool adjacent( graph& _graph, int x, int y );
	friend std::vector<int> neighbors( graph& _graph, int x );
	bool add( int x, int y, int value );
	bool remove( int x, int y );
	int get_edge_value( int x, int y );
	bool set_edge_value( int x, int y, int value );
	void print();

private:
	int vertices;
	int num_of_edges;
	std::vector<std::vector<int>> edges;
};
