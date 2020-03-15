#ifndef B_TREE_H
#define B_TREE_H

#include <iostream>
#include <string>
#include <fstream>
#include "Queue.h"
#include "T_Node.h"

/**********************************************           B-TREE                 **********************************************************/

class B_Tree {

private:
	unsigned int m;  // Degree
	int h;			// Height
	int n;			// Number of nodes
	Pointer root;  // Root

public:

	B_Tree() : m(0), h(-1), root(nullptr), n(0) {};

	void initialize();
	void insert_from_file();
	void print() const;
	void print_detailed() const;
	int get_height() const {
		return h;
	}
	int get_key_num() const;
	Node_Info find_key(int) const;
	void insert_key(int key);
	bool delete_key(int key);
	void transform();
	bool is_empty() const {
		if (root == nullptr)
			return true;
		else
			return false;

	}
	void delete_tree();

	~B_Tree();

	/*Additional methods*/
	Pointer split(Pointer, int*, Pointer *);
	Pointer merge(Pointer, int, Pointer);
	int * extract(void);

};




#endif // !B_TREE_H
