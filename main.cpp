#include <iostream>
#include "graph.h"
#include "tree.h"

using namespace std;

void prims_test();
void kruskal_test();

int main() {
	//prims_test();
	kruskal_test();
}


void prims_test() {
	graph temp( 3 );
	temp.set_edge_value( 0, 1, 1 );
	temp.set_edge_value( 0, 2, 6 );
	temp.set_edge_value( 1, 2, 5 );
	tree t( temp );
	t.create_prims_mst();
	cout << t;
}

void kruskal_test() {
	graph temp( 3 );
	temp.set_edge_value( 0, 1, 1 );
	temp.set_edge_value( 0, 2, 6 );
	temp.set_edge_value( 1, 2, 5 );
	tree t( temp );
	t.create_kruskal_tree();
	cout << t;
}