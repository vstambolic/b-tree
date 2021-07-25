#include "../h/B_Tree.h"

void print_menu(void) {

	cout << " ____________________________________________________________________________________________________________\n";
	cout << "|                                                     MENU                                                   |\n";
	cout << "|                                                                                                            |\n";
	cout << "| 1. Create new B-Tree                                                                                       |\n";
	cout << "| 2. Insert keys from file                                                                                   |\n";
	cout << "| 3. Print tree level by level                                                                               |\n";
	cout << "| 4. Get tree height                                                                                         |\n";
	cout << "| 5. Get number of nodes                                                                                     |\n";
	cout << "| 6. Find key                                                                                                |\n";
	cout << "| 7. Insert key                                                                                              |\n";
	cout << "| 8. Delete key                                                                                              |\n";
	cout << "| 9. Transform tree (maximum capacity)                                                                       |\n";
	cout << "| 10. Delete B-Tree                                                                                          |\n";
	cout << "|                                                                                                            |\n";
	cout << "|                                                                                                            |\n";
	cout << "| 0. Exit                                                                                                    |\n";
	cout << "|____________________________________________________________________________________________________________|\n";

	cout << "\nChoose any option:\n" ;

}

int main(void) {

	B_Tree tree;

	print_menu();
	putchar('\n');
	while (1) {

		int x;
		cin >> x;
		putchar('\n');
		switch (x)
		{
		case 1: {
			if (!tree.is_empty()) {
				tree.delete_tree();
			}
			tree.initialize();
			cout << "Tree successfully initialized." << endl;
			break;
		}
		case 2: {
			tree.insert_from_file();
			break;
		}
		case 3: {
			if (!tree.is_empty()) {
				tree.print();
				tree.print_detailed();
			}
			else
				cout << "Tree is empty." << endl;
			break;
		
		}

		case 4: {
			if (tree.is_empty()) {
				cout << "Tree is empty." << endl;
			}
			else
				cout << "Tree height: h = " << tree.get_height() << endl;
			break;
		}
		case 5: {
			if (tree.is_empty()) {
				cout << "Tree is empty." << endl;
			}
			else
				cout << "Number of keys in tree: n = " << tree.get_key_num() << endl;
			break;
		}
		case 6: {
			if (tree.is_empty()) { 
				cout << "Tree is empty." << endl;
			}
			else {
				int key;
				cout << "Enter key:" << endl;
				cin >> key;
				
				Pointer ptr = tree.find_key(key).node_ptr;			

				if (ptr == nullptr)
					cout << "Key is not present in the tree." << endl;
				else
				{
					cout << "Key successfully found at the location: " << ptr << endl;
				}
			
			}
			break;

		}
		case 7: {
			cout << "Enter the number of keys that need to be inserted:" << endl;
			cin >> x;
			for (int i = 0; i < x; i++) {
				cout << "Enter " << i + 1 << ". key:" << endl;
				int key;
				cin >> key;
				tree.insert_key(key); 
				tree.print();
			}
			break;

		}
		case 8: {
			if (tree.is_empty()) {
				cout << "Tree is empty." << endl;
			}
			else {
				int key;
				cout << "Enter the key which needs to be deleted: " << endl;
				cin >> key;


				if (tree.delete_key(key))
					cout << "Key " << key << " succssesfully deleted from the tree." << endl;
				else
					cout << "Key " << key << " isn't present in the tree" << endl;

			}
			break;
		}

		case 9: {
			if (tree.is_empty()) 
				cout << "Tree is empty." << endl;
			else
				tree.transform();
			break;
		}
		case 10: {
			if (tree.is_empty()) 
				cout << "Tree is empty." << endl;
			else {
				cout << "Deleting the tree..." << endl;
				tree.delete_tree();
				cout << "Tree successfully deleted." << endl;
			}
			break;
		}
		case 0: {
			cout << "Goodbye." << endl;
			tree.delete_tree();
			exit(EXIT_SUCCESS);
		}

		default: {
			cout << "Selected option doesn't exist. Repeat the input:"; 
			continue;
		}
		}

		cout << "\nPress any key to continue.\n";
		cin.get();
		cin.get();

		cout << endl;
		print_menu();

	}

	return 0;
}