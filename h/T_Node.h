#pragma once
#ifndef T_NODE_H
#define T_NODE_H
#include <iostream>
using namespace std;

class T_Node {
private:
	unsigned int k;
	int * K;
	T_Node ** P;
	T_Node * father;
public:
	T_Node(int m) : k(0), K(new int[m - 1]), P(new T_Node*[m]), father(nullptr) {
		for (int i = 0; i < m; i++) {
			P[i] = nullptr;
		}
	};

	T_Node * leftmost(T_Node* ptr) const;
		
	T_Node * successor(int) const;
	bool is_leaf() const {
		if (P[0] == nullptr)
			return true;
		else
			return false;
	}
	friend class B_Tree;

	~T_Node() {
		delete[] K;
		delete[] P;
	}
};
typedef T_Node * Pointer;

#endif