#include <iostream>
#include <vector>
#include <algorithm>
#include "avl_tree.h"
#include "red-black_tree.h"
#include "relation.h"

using namespace std;

int	main()
{
	
	StrategyComparator<int*>* comp = new Comparator_ptr_int;
	AVL_tree<int*>	avl(comp);
	RB_tree<int*> rb(comp);
	Relation<int> rt;
	vector<int> vec;

	for (int i = 0; i < 10; ++i) 
		vec.push_back(rand() % 1001 - 500);

	vec.clear();

	/*srand(time(NULL));
	for (int i = 0; i < 10; ++i) {
		vec.push_back(rand() % 1001);
		avl.add_node(&vec[i]);
	}

	vec.clear();
	for (int i = 0; i < 10; ++i) {
		vec.push_back(rand() % 1001 - 500);
		rb.add_node(&vec[i]);
	}

	vec.clear();*/

	srand(time(NULL));
	for (int i = 0; i < 10; ++i) {
		vec.push_back(rand() % 1001);
		rt.add_data(vec[i]);
	}
	rt.print_data();
	rt.delete_data(vec[3]);
	rt.delete_data(vec[9]);
	rt.add_index(&avl);
	rt.add_index(&rb);
	rt.print_data();
	//avl.print_tree();
	//rb.print_tree();

	return 0;
}