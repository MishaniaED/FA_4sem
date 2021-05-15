#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "avl_tree.h"
#include "red-black_tree.h"

using namespace std;


int	main()
{	
	StrategyComparator<int *> *comp = new Comparator_ptr_int;
	AVL_tree<int *>	avl(comp);
	RB_tree<int *> rb(comp);
	
	vector<int> vec;
	for (int i = 0; i < 10; ++i) {
		vec.push_back(rand() % 1001 - 500);
	}
	vec.clear();

	srand(time(NULL));
	clock_t t = clock();
	for (int i = 0; i < 10; ++i) {
		vec.push_back(rand() % 1001);
		avl.add_node(&vec[i]);
	}
	cout << "AVL tree:\n";
	avl.print_tree();
	cout << "Time: " << double(clock() - t) / CLOCKS_PER_SEC << endl;
	cout << "Rotations: " << avl.get_rotations() << "\n\n";

	//vec.clear();
	t = clock();
	for (int i = 0; i < 10; ++i) {
		//vec.push_back(rand() % 1001 - 500);
		rb.add_node(&vec[i]);
	}
	cout << "RB tree:\n";
	rb.print_tree();
	cout << "Time: " << double(clock() - t) / CLOCKS_PER_SEC << endl;
	cout << "Rotatioms: " << rb.get_rotations() << endl;

	delete comp;

	return 0;
}