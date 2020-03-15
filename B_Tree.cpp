#include "B_TREE.h"
#include "Queue.h"
#include "T_Node.h"


void print_array(int *K, int n) {
	cout << "[ ";
	for (int i = 0; i < n; i++) {
		cout << K[i];
		if (i + 1 != n) cout << " | ";
	}
	cout << " ]";
}
int bin_search_next_larger(int * K, int n, int key) {
	int low = 0, high = n, mid;

	while (low <= high) {
		mid = (low + high) >> 1;
		if (K[mid] == key)
			return mid;
		else
			if (key < K[mid])
				high = mid - 1;

			else
				low = mid + 1;
	}

	if (high < 0)
		return 0;
	else
		if (low > n - 1)
			return n;
		else
			return low;

}

/*Array modifications*/
void move_up(int * V, int n, int pos) {
	for (int i = n; i > pos; i--) {
		V[i] = V[i - 1];
	}
}
void move_up(Pointer *V, int n, int pos) {
	for (int i = n; i > pos; i--) {
		V[i] = V[i - 1];
	}
}
void move_down(int *V, int n, int pos) {
	for (int i = pos; i < n - 1; i++) {
		V[i] = V[i + 1];
	}
}
void move_down(Pointer *V, int n, int pos) {
	for (int i = pos; i < n - 1; i++) {
		V[i] = V[i + 1];
	}
}


void insert_in_array(int *K, int n, int key) {
	int pos = bin_search_next_larger(K, n, key);
	move_up(K, n, pos);
	K[pos] = key;
}
void delete_from_array(int *K, int n, int key) {
	int pos = bin_search_next_larger(K, n, key);
	move_down(K, n, pos);
}

void B_Tree::initialize() {
	cout << "Enter tree degree:" << endl;
	while (1) {
		cin >> m;
		if (m >= 3 && m <= 10)
			break;
		else
			cout << "Enter the value in domain [3,10]" << endl;

	}
}

void B_Tree::delete_tree() {
	if (!root) return;
	Queue q;
	Pointer tmp = root;


	q.insert_in_queue(root, 0);
	while (!q.is_empty()) {
		tmp = q.delete_from_queue().node_ptr;



		int i = 0;
		while (tmp->P[i] != nullptr && i < tmp->k + 1) {
			q.insert_in_queue(tmp->P[i]);
			i++;
		}
		delete tmp;
	}
	root = nullptr;
	n = 0;
	h = 0;

}
B_Tree::~B_Tree() {
	delete_tree();
}
void B_Tree::insert_from_file() {
	cout << "Enter the source file name: " << endl;

	string str;
	cin >> str;

	ifstream f;
	f.open(str);
	if (!f.is_open()) {
		cout << "Error with opening the source file" << endl;
		return;
	}

	int key;
	while (f >> key) {
		insert_key(key);
	}

	f.close();
}

void B_Tree::print() const {
	if (!root) return;
	Queue q;
	Node_Info info;
	Pointer tmp = root;
	int level = 0;

	cout << endl << endl << endl << "____________________________________________ Tree ____________________________________________" << endl << endl;
	cout << "Nivo " << level << ":" << endl;

	q.insert_in_queue(root, 0);
	while (!q.is_empty()) {
		info = q.delete_from_queue();
		if (info.node_i > level) {
			level++;
			cout << endl << "------------------------------------------------------------------------------------------------------" << endl;
			cout << "Nivo " << level << ":" << endl;
		}

		print_array(info.node_ptr->K, info.node_ptr->k);
		cout << "   ";
		int i = 0;
		while (info.node_ptr->P[i] != nullptr && i < info.node_ptr->k + 1) {
			q.insert_in_queue(info.node_ptr->P[i], level + 1);
			i++;
		}
	}
	cout << endl << endl << endl << endl << "___________________________________________________________________________________________________" << endl << endl;

}

void B_Tree::print_detailed() const {
	if (!root) return;
	Queue q;
	Node_Info info;
	Pointer tmp = root;
	int level = 0;
	int k = 0;
	cout << endl << endl << endl << "____________________________________________ Tree ____________________________________________" << endl << endl;
	cout << "Nivo " << level << ":" << endl;

	q.insert_in_queue(root, 0);
	while (!q.is_empty()) {
		info = q.delete_from_queue();
		if (info.node_i > level) {
			level++;
			cout << endl << "------------------------------------------------------------------------------------------------------" << endl;
			cout << "Nivo " << level << ":" << endl;
		}


		k++;
		cout << "Node: " << k << endl;
		cout << "Info: " << endl << '\t';
		print_array(info.node_ptr->K, info.node_ptr->k);

		cout << endl;
		cout << "Parent:" << endl << '\t';
		if (info.node_ptr->father != nullptr)
			print_array(info.node_ptr->father->K, info.node_ptr->father->k);
		else
			cout << "nullptr";
		cout << endl;

		cout << "Its children:" << endl;

		int i = 0;
		while (i < m) {
			cout << '\t';

			if (info.node_ptr->P[i] != nullptr  && i < info.node_ptr->k + 1) {
				print_array(info.node_ptr->P[i]->K, info.node_ptr->P[i]->k);
			}
			else
				cout << "nullptr";
			cout << endl;
			i++;
		}



		i = 0;
		while (info.node_ptr->P[i] != nullptr && i < info.node_ptr->k + 1) {
			q.insert_in_queue(info.node_ptr->P[i], level + 1);
			i++;
		}
	}
	cout << endl << endl << endl << endl << "___________________________________________________________________________________________________" << endl << endl;

}

int B_Tree::get_key_num() const {
	return n;
}

void B_Tree::insert_key(int key) {
	Pointer p = root;
	Pointer q = nullptr;
	Pointer tmp = nullptr;
	int pos;
	while (p != nullptr) {
		tmp = p;
		pos = bin_search_next_larger(p->K, p->k, key);
		if (p->K[pos] == key) {
			cout << "Key " << key << " isn't present in the tree." << endl;
			return;
		}
		else {
			p = p->P[pos];
		}
	}
	n++;


	int x = key;
	while ((tmp != nullptr) && (tmp->k == m - 1)) {
		int * V = new int[m];
		for (int i = 0; i < m - 1; i++)
			V[i] = tmp->K[i];
		move_up(V, m - 1, pos);
		V[pos] = x;

		Pointer * P = new Pointer[m + 1];
		for (int i = 0; i < m; i++)
			P[i] = tmp->P[i];
		move_up(P, m, pos + 1);
		P[pos + 1] = q;

		q = split(tmp, V, P);
		p = tmp;


		tmp = tmp->father;

		x = V[m / 2];
		if (tmp) pos = bin_search_next_larger(tmp->K, tmp->k, x);
		free(V);


	}

	if (tmp == nullptr) {
		root = new T_Node(m);
		root->K[0] = x;
		root->k++;
		if (p != nullptr) {
			root->P[0] = p;
			root->P[1] = q;
			p->father = q->father = root;
		}
		h++;
		return;
	}
	else {
		move_up(tmp->K, tmp->k, pos);
		tmp->K[pos] = x;

		if (p != nullptr) {
			move_up(tmp->P, tmp->k + 1, pos + 1);
			tmp->P[pos + 1] = q;
		}
		tmp->k++;
	}




}

Pointer B_Tree::split(Pointer p, int* V, Pointer * P) {
	Pointer q = new T_Node(m);
	q->father = p->father;
	int k = m / 2;

	p->k = k;
	q->k = (m % 2) ? k : k - 1;
	for (int i = 0; i < k; i++) {
		p->K[i] = V[i];
	}
	for (int i = 0; i <= k; i++) {
		p->P[i] = P[i];
		if (P[i]) P[i]->father = p;
	}
	for (int i = k + 1, j = 0; i < m; i++, j++) {
		q->K[j] = V[i];

	}
	for (int i = k + 1, j = 0; i < m + 1; i++, j++) {
		q->P[j] = P[i];
		if (P[i]) P[i]->father = q;

	}
	return q;


}

Node_Info B_Tree::find_key(int key) const {
	Pointer tmp = root;
	int pos;
	while (tmp != nullptr) {
		pos = bin_search_next_larger(tmp->K, tmp->k, key);
		if (pos != tmp->k && key == tmp->K[pos])
			return { tmp,pos };
		else
			tmp = tmp->P[pos];

	}
	return { nullptr,0 };
}


bool B_Tree::delete_key(int key) {
	Node_Info info = find_key(key);
	Pointer tmp = info.node_ptr;
	int pos = info.node_i;

	if (tmp == nullptr)
		return false;

	Pointer succ = tmp->successor(pos);
	if (succ != nullptr) {
		cout << "Succsessor:" << succ->K[0];
		int t = tmp->K[pos];
		tmp->K[pos] = succ->K[0];
		succ->K[0] = t;
		tmp = succ;
		pos = 0;
	}
	move_down(tmp->K, tmp->k, pos);
	tmp->k--;

	while ((tmp->k < m / 2 - !(m % 2))) {
		if (tmp == root) {
			if (tmp->k == 0) {
				root = root->P[0];
				if (root) root->father = nullptr;
				delete tmp;
				h--;
			}
			break;
		}
		else {

			Pointer fat = tmp->father;
			Pointer bro = nullptr;
			pos = 0;

			while (pos < fat->k + 1 && fat->P[pos] != tmp)
				pos++;

			if (pos != fat->k && !(fat->P[pos + 1]->k - 1 < m / 2 - !(m % 2))) {
				bro = fat->P[pos + 1];
				insert_in_array(tmp->K, tmp->k, fat->K[pos]);
				fat->K[pos] = bro->K[0];
				move_down(bro->K, bro->k, 0);

				/*Updating pointers*/
				tmp->P[tmp->k + 1] = bro->P[0];
				if (tmp->P[tmp->k + 1]) tmp->P[tmp->k + 1]->father = tmp;
				move_down(bro->P, bro->k + 1, 0);
				bro->P[bro->k] = nullptr;

				tmp->k++;
				bro->k--;


			}
			else
				if (pos != 0 && !(fat->P[pos - 1]->k - 1 < m / 2 - !(m % 2))) {		// Does current node have left brother
					bro = fat->P[pos - 1];

					insert_in_array(tmp->K, tmp->k, fat->K[pos - 1]);
					fat->K[pos - 1] = bro->K[bro->k - 1];

					move_up(tmp->P, tmp->k + 1, 0);
					tmp->P[0] = bro->P[bro->k];
					if (tmp->P[0]) tmp->P[0]->father = tmp;
					bro->P[bro->k] = nullptr;


					tmp->k++;
					bro->k--;


				}
				else { /*Merge*/
					if (pos != fat->k) {
						bro = fat->P[pos + 1];
					}
					else {
						bro = tmp;
						tmp = fat->P[pos - 1];
						pos--;

					}
					merge(tmp, fat->K[pos], bro);
					tmp->k = m - 1;
					delete bro;

					move_down(fat->K, fat->k, pos);
					move_down(fat->P, fat->k + 1, pos + 1);
					fat->P[fat->k] = nullptr;
					fat->k--;
					tmp = fat;


				}
		}

	}
	n--;
	return true;
}

Pointer B_Tree::merge(Pointer p, int x, Pointer q) {
	p->K[p->k] = x;
	int i, j;
	for (i = p->k + 1, j = 0; j < q->k; i++, j++) {
		p->K[i] = q->K[j];
		p->P[i] = q->P[j];
		if (p->P[i]) p->P[i]->father = p;

	}
	p->P[i] = q->P[j];
	if (p->P[i]) p->P[i]->father = p;

	for (i = 0; i < m - 1; i++)
		cout << p->K[i] << " ";


	return p;
}

void B_Tree::transform() {
	int * V = extract();
	print_array(V, n);

	h = static_cast<int>(ceil(log(n + 1) / log(m)) - 1);
	cout << endl << h << endl;

	int ** level = new int*[h + 1];
	int * level_size = new int[h + 1];


	/*Space alocation */
	for (int i = h, sum = 0; i >= 0; i--) {

		level_size[i] = static_cast<int>(ceil(1.0* (n - sum) / m * (m - 1)));
		level[i] = new int[level_size[i]];
		cout << "\tLevel " << i << ": " << level_size[i] << endl;
		sum += level_size[i];
	}


	//Building level hierarchy
	int * tmp_state = new int[h + 1];
	for (int i = 0; i < h + 1; i++)
		tmp_state[i] = 0;
	int * full = new int[h + 1];
	for (int i = 0; i < h + 1; i++)
		full[i] = 0;


	for (int i = 0; i < n; i++) {
		int j = h;
		while (full[j]) {
			full[j] = 0;
			j--;
		}
		level[j][tmp_state[j]] = V[i];
		tmp_state[j]++;
		if (tmp_state[j] % (m - 1) == 0)
			full[j] = 1;

	}
	free(tmp_state);
	free(full);


	//Print by level
	for (int i = h; i >= 0; i--) {
		cout << "Level " << i << ":\n";
		for (int j = 0; j < level_size[i]; j++)
			cout << level[i][j] << " ";
		cout << endl;
	}


	Pointer tmp;
	Pointer ** node = new Pointer*[h + 1];
	int * node_num = new int[h + 1];

	for (int i = h; i >= 0; i--) {

		node_num[i] = ceil(1.0*level_size[i] / (m - 1));

		node[i] = new Pointer[node_num[i]];
		for (int j = 0; j < node_num[i]; j++)
			node[i][j] = new T_Node(m);

		cout << "\tLevel " << i << ": " << node_num[i] << endl;
	}


	/*Loading with keys*/
	for (int i = 0; i <= h; i++) {
		int cnt = -1;
		for (int j = 0; j < level_size[i]; j++) {
			if (!(j % (m - 1))) {
				cnt++;
			}
			node[i][cnt]->K[j % (m - 1)] = level[i][j];
			node[i][cnt]->k++;
		}
		if (node[i][cnt]->k < m / 2) {

		}
	}

	for (int i = h; i >= 0; i--) {
		cout << "Nivo " << i << ":\n";
		int cnt = -1;
		for (int j = 0; j < level_size[i]; j++) {
			if (!(j % (m - 1))) {
				cnt++;
				cout << " | ";
			}
			cout << node[i][cnt]->K[j % (m - 1)] << " ";
		}
		cout << endl;
	}

	/*Connecting nodes*/
	for (int i = 0; i < h; i++) {
		int j = 0;
		int nextnode = 1;
		int pos;
		for (int k = 0; k < node_num[i + 1]; k++) {
			if (nextnode) {
				pos = 0;
				nextnode = 0;
			}

			else {
				pos++;
			}


			node[i][j]->P[pos] = node[i + 1][k];
			node[i + 1][k]->father = node[i][j];

			if (pos == node[i][j]->k) {

				if (j == node_num[i] - 1 && node[i + 1][k]->k < m / 2) {
					int t = node[i][j]->K[node[i][j]->k - 1];
					node[i][j]->K[node[i][j]->k - 1] = node[i + 1][k - 1]->K[node[i + 1][k - 1]->k / 2];
					move_down(node[i + 1][k - 1]->K, node[i + 1][k - 1]->k, node[i + 1][k - 1]->k / 2);
					node[i + 1][k - 1]->K[node[i + 1][k - 1]->k - 1] = t;

					while (node[i + 1][k]->k < m / 2) {
						insert_in_array(node[i + 1][k]->K, node[i + 1][k]->k, node[i + 1][k - 1]->K[node[i + 1][k - 1]->k - 1]);
						node[i + 1][k]->k++;
						node[i + 1][k - 1]->k--;
					}

				}


				nextnode = 1;
				j++;
			}
			else
				if (k + 1 == node_num[i + 1]) { 

					int t = node[i][j]->K[node[i][j]->k - 1];
					node[i][j]->K[node[i][j]->k - 1] = node[i + 1][k]->K[node[i + 1][k]->k / 2]; 
					move_down(node[i + 1][k]->K, node[i + 1][k]->k, node[i + 1][k]->k / 2);
					node[i + 1][k]->K[node[i + 1][k]->k - 1] = t;


					/*RESIZE*/
					int dim = node_num[i + 1] + 1;
					Pointer * tmp = new Pointer[dim];
					for (int l = 0; l < dim - 1; l++) {
						tmp[l] = node[i + 1][l];
					}

					tmp[dim - 1] = new T_Node(m);

					for (int l = m / 2; l < m - 1; l++) {
						tmp[dim - 1]->K[tmp[dim - 1]->k] = tmp[dim - 2]->K[l];
						tmp[dim - 1]->k++;
						tmp[dim - 2]->k--;
					}


					free(node[i + 1]);
					node[i + 1] = tmp;
					node_num[i + 1] = dim;
				}
		}

	}
	root = node[0][0];
	root->father = nullptr;


	print();
	print_detailed();


}

int * B_Tree::extract(void) {
	int * V = new int[n];
	Queue q;
	Pointer tmp = root;
	int i = 0;
	q.insert_in_queue(tmp);

	while (!q.is_empty()) {
		tmp = q.delete_from_queue().node_ptr;

		for (int j = 0; j < tmp->k; j++) {
			insert_in_array(V, i, tmp->K[j]);
			i++;
		}

		int j = 0;
		while (tmp->P[j] != nullptr && j < tmp->k + 1) {
			q.insert_in_queue(tmp->P[j]);
			j++;
		}

	}

	return V;
}
