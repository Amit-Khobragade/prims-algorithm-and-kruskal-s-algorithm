#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "priority_queue.h"
#include "graph.h"

//individual nodes for the tree 
struct branches {
	int start, end;
	int value;
	branches(int _start,int _end,int _value=0 )
		:start{ _start }, end{ _end }, value{ _value }
	{}
	bool operator==( branches other ) {
		if (this->start == other.start && this->end == other.end)
			return true;
		return false;
		
	}
};

class tree {
public:
	tree( graph _graph );
	void create_prims_mst();
	void create_kruskal_tree();
	bool add_branch( int x, int y, int value );
	bool edit_branch( int x, int y, int new_value );
	bool delete_branch( int x, int y );

	inline std::vector<branches>::iterator find_branch( int x, int y ) {
		branches temp{ x,y };
		return std::find( MST.begin(), MST.end(), temp );
	}
	friend std::ostream& operator<<( std::ostream& os, tree& T );

private:
	std::vector<branches> MST;
	std::vector<std::pair<int, std::string>> point_name;
	int total;
	graph G;
};
