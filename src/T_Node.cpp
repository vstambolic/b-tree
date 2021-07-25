#include "..\h\T_Node.h"

T_Node * T_Node::leftmost(T_Node* ptr) const {
	T_Node* tmp = ptr;
	while (!tmp->is_leaf())
		tmp = tmp->P[0];

	return tmp;
}

T_Node * T_Node::successor(int pos) const {
	if (is_leaf())
		return nullptr;
	else
		return leftmost(P[pos + 1]);

}





