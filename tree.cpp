#include "tree.h"	

tree::tree( graph G )
	:total{ 0 }, G{ G }
{
	//loop to assign each and every element a string name
	char ch = 'A';
	int count{ 1 };
	for (int i = 0; i < G.vertice_num(); ++i) {
		std::stringstream ss;
		ss.clear();
		ss << ch << count;
		point_name.emplace_back( i, ss.str() );
		if (ch == 'Z') {
			++count;
			ch = 'A';
		}
		else ++ch;
	}
}

bool tree::add_branch( int x, int y, int value ) {
	if (find_branch( x, y ) == MST.end()) {
		MST.emplace_back( x, y, value );
		total += value;
		return true;
	}
	return false;
}

bool tree::edit_branch( int x, int y, int new_value ) {
	auto it=find_branch( x, y );
	if (it == MST.end())
		return false;
	total = total - it->value + new_value;
	it->value = new_value;
	return true;
}

bool tree::delete_branch( int x, int y ) {
	auto it = find_branch( x, y );
	if (it == MST.end())
		return false;
	total -= it->value;
	for (; it != MST.end(); ++it) 
		std::swap( *it, *(it + 1) );
	MST.pop_back();
	return true;
}

std::ostream& operator<<( std::ostream& os, tree& T ) {
	if (T.MST.size() == 0) {
		os << "no elements found";
		return os;
	}
	std::for_each( T.MST.begin(), T.MST.end(), [&]( branches& B ) {
		os <<"("<< T.point_name.at( B.start ).second
			<< "->" << T.point_name.at( B.end ).second << ")  ";
		} );
	os << "\nthe total cost is: " << T.total;
	return os;
}

//prim's algorithm
void tree::create_prims_mst() {
	Priority_Queue<std::pair<int, int >> Q;
	total = 0;
	MST.clear();
	std::vector<std::pair<int, int>> contents;
	for (int i = 0; i < G.vertice_num()-1; ++i) {
		auto temp = neighbors( G, i );
		for (auto s : temp) {
			queue_element<std::pair<int, int>> q_elm{ std::make_pair( i, s ), G.get_edge_value( i, s ) };
			Q.insert( q_elm );
		}
		while (Q.size()!=0) {
			auto top = Q.top();
			Q.pop();
			bool condition{ 0 };
			for (auto a : contents) {
				if (!condition)
					condition = ((a.first == top.key.first && a.second == top.key.second) || (a.second == top.key.first && a.first == top.key.second));
				else
					break;
			}
			if (!condition) {
				branches B{ top.key.first,top.key.second,top.priority };
				MST.push_back( B );
				contents.emplace_back( top.key.first, top.key.second );
				total += top.priority;
				break;
			}
		}
	}
}

void tree::create_kruskal_tree() {
	total = 0;
	MST.clear();
	Priority_Queue<std::pair<int, int>> Q;
	//for making the queue
	for (int i = 0; i < G.vertice_num(); ++i) {
		auto temp = neighbors( G, i );
		for(auto a:temp)
			if (i < a) {
				queue_element<std::pair<int, int>> temp{ std::make_pair( i, a ), G.get_edge_value( i, a ) };
				Q.insert( temp );
			}
	}
	std::vector<int> contents;
	while (Q.size()!=0||contents.size()<G.vertice_num()) {
		auto temp = Q.top();
		Q.pop();
		bool cond_1{ false }, cond_2{ false };
		for (int a : contents) {
			if (a == temp.key.first)
				cond_1 = true;
			if (a == temp.key.second)
				cond_2 = true;
		}
		if (!(cond_1 && cond_2)) {
			branches B{ temp.key.first,temp.key.second,temp.priority };
			MST.push_back( B );
			contents.push_back( temp.key.first );
			contents.push_back( temp.key.second );
			total += temp.priority;
		}
	}
}
