#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include "T_Node.h"
using namespace std;

typedef struct node_info {      //Node with its level
	Pointer node_ptr;
	int node_i;
} Node_Info;


typedef struct field {		// Queue element
	Node_Info info;
	field * next;
} Field;
typedef Field * Field_Pointer;

class Queue {
private:
	Field_Pointer h;
public:
	Queue() : h(nullptr) {};
	void insert_in_queue(Pointer x, int level = 0) {
	Field_Pointer p = new (Field);
	p->info = { x,level };
	p->next = nullptr;


	if (h == nullptr) {
		h = p;
	}
	else {
		Field_Pointer tmp = h;
		while (tmp->next != nullptr) {
			tmp = tmp->next;
		}
		tmp->next = p;
	}

}
	Node_Info delete_from_queue() {
		if (is_empty()) {
			cout << "ERROR: Underflow" << endl;
			exit(EXIT_FAILURE);
		}
		else {
			Field_Pointer tmp = h;
			Node_Info x = h->info;
			h = h->next;
			free(tmp);
			return x;
		}

	}
	bool is_empty() {
		if (h == nullptr)
			return true;
		else
			return false;
	}

};




#endif