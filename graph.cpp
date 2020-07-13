#include "graph.h"
#include <ctime>   // for time for seeding the rand function
#include <stdlib.h> //for srand() and rand()


graph::graph( int _vertices , double density  )
	:vertices{ _vertices }, num_of_edges{ 0 }
{
	edges = std::vector<std::vector<int>>{ static_cast< const unsigned int >(vertices) };
	for (auto& elem : edges)
		elem = std::vector<int>( vertices, 0 );
	
	if (density >= 0 && density <= 1)
		randomise_graph( density );
}

graph::graph( graph& _graph )
	:vertices{ _graph.vertices }, num_of_edges{ _graph.num_of_edges }
{
	this->edges = _graph.edges;
}

void graph::randomise_graph( double density ) {
	if (density < 0 && density > 1)
		throw "invalid density";
	num_of_edges = 0;
	if (density == 0) {
		for (int i = 0; i < vertices; ++i)
			for (int j = 0; j < vertices; ++j)
				edges.at( i ).at( j ) = 0;
		return;
	}
	//seeding time and then adding new values to the matrix
	std::srand( static_cast< size_t >(time( 0 )) );
	for (int i = 0; i < vertices; ++i)
		for (int j = 0; j < vertices; ++j) {

			if (i == j) {
				edges.at( i ).at( j ) = 0;
				continue;
			}


			double probablity = (rand() % 100) / 100;
			int value = (rand() % 10);
			if (probablity < density) {
				edges.at( i ).at( j ) = 0;
				++num_of_edges;
			}
			else
				edges.at( i ).at( j ) = 0;
		}
}

bool graph::add( int x, int y, int value ) {
	if (x < 0 && x > vertices && y < 0 && y > vertices)
		return false;
	if (edges.at(x).at(y) == 0 && edges.at( x ).at( y ) == 0) {
		edges.at( x ).at( y ) = edges.at( y ).at( x ) = value;
		++num_of_edges;
		return true;
	}
	return false;
}

bool graph::remove( int x, int y ) {
	if (x < 0 && x > vertices && y < 0 && y > vertices)
		return false;
	if (edges.at( x ).at( y ) != 0 ) {
		edges.at( x ).at( y ) = edges.at( x ).at( y ) = 0;
		--num_of_edges;
		return true;
	}
	return false;
}

int graph::get_edge_value( int x, int y ) {
	if (x < 0 && x > vertices && y < 0 && y > vertices)
		throw "out_of_range";
	return edges.at( x ).at( y );
}

bool graph::set_edge_value( int x, int y, int value ) {
	if (x < 0 && x > vertices && y < 0 && y > vertices)
		throw "out_of_range";
	edges.at( x ).at( y ) = edges.at( y ).at( x ) = value;
	return true;
}


bool adjacent( graph& _graph, int x, int y ) {
	if (x > _graph.vertices && x<0 && y>_graph.vertices && y < 0)
		throw "out_of_range";
	if (_graph.edges.at( x ).at( y ) != 0 || _graph.edges.at( y ).at( x ) != 0)
		return true;
	return false;
}

std::vector<int> neighbors( graph& _graph, int x ) {
	if (x > _graph.vertices && x < 0)
		throw "out_of_range";
	std::vector<int> temp;
	for (int i = 0; i < _graph.vertice_num(); ++i)
		if (_graph.edges.at( x ).at( i ) != 0)
			temp.push_back( i );
	return temp;
}

void graph::print() {
	for (int i = 0; i < vertices; ++i)
		std::cout << "  " << i + 1;
	std::cout << "\n\n";

	for (int i = 0; i < vertices; ++i) {
		std::cout << i + 1 << " ";
		for (int j = 0; j < vertices; ++j)
			std::cout << edges.at( i ).at( j ) << " "
			         << std::endl;
	}
}