#include "binary_tree.h"

/* TEMPLATE RED_BLACK-TREE CLASS */

template <typename T>
class RB_tree : public Binary_tree<T>
{
private:
	enum color {RED, BLACK};
	
	struct	tree_node
	{
		T	key;
		int	color;
		tree_node* left;
		tree_node* right;
		tree_node* parent;
	};

private:
	tree_node* root;
	int rotations;

	bool find_node(tree_node* node, T val);
	int	 get_color(tree_node* &node);
	void rotate_left(tree_node* &node);
	void rotate_right(tree_node* &node);
	void delete_tree(tree_node* node);
	void fix_insert(tree_node* &node);
	void fix_delete(tree_node* &node);
	void set_color(tree_node* &node, int color);
	void tree_print(tree_node* curr, int depth);
	tree_node* create_node(T val);
	tree_node* find_min(tree_node* &node);
	tree_node* delete_bst(tree_node* &root, T data);
	tree_node* delete_node(tree_node* node, T val);
	tree_node* insert_bst(tree_node* &root, tree_node* &node);

public:
    RB_tree(StrategyComparator<T>* compare) : Binary_tree<T>::Binary_tree(compare)
    {
        root = nullptr;
        rotations = 0;
    }
    ~RB_tree()
    {
        if (root != nullptr)
            delete_tree(this->root);
    }

	bool find_node(T &&val) override;
    void add_node(T &&val) override;
	void delete_node(T &&val) override;
	bool is_empty();
	void print_tree();
	void clear_tree();
	
	unsigned int	get_rotations();
};


template <typename T>
bool RB_tree<T>::find_node(tree_node* node, T val)
{
	if (node != nullptr) {
		if (this->comparator->compare(val, (*node).key) == 0)
			return (true);
		if (this->comparator->compare(val, (*node).key) < 0)
			return find_node(node->left, val);
		else
			return find_node(node->right, val);
	}
	return (false);
}

template <typename T>
int RB_tree<T>::get_color(tree_node* &node)
{
    if (node == nullptr)
        return (BLACK);
    return (node->color);
}

template <typename T>
void RB_tree<T>::rotate_left(tree_node* &node)
{
    tree_node* r_child = node->right;

    node->right = r_child->left;
    if (node->right != nullptr)
        node->right->parent = node;
    r_child->parent = node->parent;

    if (node->parent == nullptr)
        root = r_child;
    else if (node == node->parent->left)
        node->parent->left = r_child;
    else
        node->parent->right = r_child;

    r_child->left = node;
    node->parent = r_child;
	rotations++;
}

template <typename T>
void RB_tree<T>::rotate_right(tree_node* &node)
{
    tree_node* l_child = node->left;

    node->left = l_child->right;
    if (node->left != nullptr)
        node->left->parent = node;
    l_child->parent = node->parent;

    if (node->parent == nullptr)
        root = l_child;
    else if (node == node->parent->left)
        node->parent->left = l_child;
    else
        node->parent->right = l_child;

    l_child->right = node;
    node->parent = l_child;
	rotations++;
}

template <typename T>
void RB_tree<T>::delete_tree(tree_node* node)
{
	if (node != nullptr)
	{
		delete_tree(node->left);
		delete_tree(node->right);
		delete node;
	}
}

template <typename T>
void RB_tree<T>::fix_insert(tree_node* &node)
{
    tree_node* parent = nullptr;
    tree_node* grandpa = nullptr;

    while (node != root && get_color(node) == RED && get_color(node->parent) == RED) {
        parent = node->parent;
        grandpa = parent->parent;
        if (parent == grandpa->left) {
            tree_node* uncle = grandpa->right;

            if (get_color(uncle) == RED) {
                set_color(uncle, BLACK);
                set_color(parent, BLACK);
                set_color(grandpa, RED);
                node = grandpa;
            }
			else {
                if (node == parent->right) {
                    rotate_left(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotate_right(grandpa);
                swap(parent->color, grandpa->color);
                node = parent;
            }
        }
		else {
           tree_node* uncle = grandpa->left;

            if (get_color(uncle) == RED) {
                set_color(uncle, BLACK);
                set_color(parent, BLACK);
                set_color(grandpa, RED);
                node = grandpa;
            }
			else {
                if (node == parent->left) {
                    rotate_right(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotate_left(grandpa);
                swap(parent->color, grandpa->color);
                node = parent;
            }
        }
    }
    set_color(root, BLACK);
}

template <typename T>
void RB_tree<T>::fix_delete(tree_node* &node)
{
    if (node == nullptr)
        return ;
    if (node == root) {
        root = nullptr;
        return ;
    }
    if (get_color(node) == RED || get_color(node->left) == RED || get_color(node->right) == RED) {
        tree_node* child = node->left;
        child != nullptr ? node->left : node->right;

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            set_color(child, BLACK);
            delete node;
        }
		else {
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            set_color(child, BLACK);
            delete node;
        }
    }
	else {
        tree_node* sibling = nullptr;
        tree_node* parent = nullptr;
        tree_node* ptr = node;

        set_color(ptr, BLACK);
        while (ptr != root && get_color(ptr) == BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (get_color(sibling) == RED) {
                    set_color(sibling, BLACK);
                    set_color(parent, RED);
                    rotate_left(parent);
                }
				else {
                    if (get_color(sibling->left) == BLACK && get_color(sibling->right) == BLACK) {
                        set_color(sibling, RED);
                        if(get_color(parent) == RED)
                            set_color(parent, BLACK);
                        else
                            set_color(parent, BLACK);
                        ptr = parent;
                    }
					else {
                        if (get_color(sibling->right) == BLACK) {
                            set_color(sibling->left, BLACK);
                            set_color(sibling, RED);
                            rotate_right(sibling);
                            sibling = parent->right;
                        }
                        set_color(sibling, parent->color);
                        set_color(parent, BLACK);
                        set_color(sibling->right, BLACK);
                        rotate_left(parent);
                        break;
                    }
                }
            }
			else {
                sibling = parent->left;
                if (get_color(sibling) == RED) {
                    set_color(sibling, BLACK);
                    set_color(parent, RED);
                    rotate_right(parent);
                }
				else {
                    if (get_color(sibling->left) == BLACK && get_color(sibling->right) == BLACK) {
                        set_color(sibling, RED);
                        if (get_color(parent) == RED)
                            set_color(parent, BLACK);
                        else
                            set_color(parent, BLACK);
                        ptr = parent;
                    }
					else {
                        if (get_color(sibling->left) == BLACK) {
                            set_color(sibling->right, BLACK);
                            set_color(sibling, RED);
                            rotate_left(sibling);
                            sibling = parent->left;
                        }
                        set_color(sibling, parent->color);
                        set_color(parent, BLACK);
                        set_color(sibling->left, BLACK);
                        rotate_right(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete node;
        set_color(root, BLACK);
    }
}

template <typename T>
void RB_tree<T>::set_color(tree_node *&node, int color)
{
    if (node == nullptr)
        return ;
    node->color = color;
}

template <typename T>
void RB_tree<T>::tree_print(tree_node* curr, int depth)
{
    int i;
	int loc[1000];

    if (curr == nullptr)
		return;

    for (i = 0; i < depth; i++) {
        if (i == depth - 1)
            cout << (loc[depth - 1] ? " L " : " | ") << "------";
        else
            cout << (loc[i] ? "      " : "  ") << "   ";
    }

	cout << " " << *(curr->key) << ((curr->color == 0) ? " (RED) " : " (BLACK) ") << "\n\n";
    loc[depth] = 1;
    tree_print(curr->left,depth+1);
    loc[depth] = 0;
    tree_print(curr->right,depth+1);
}

template <typename T>
typename RB_tree<T>::tree_node* RB_tree<T>::create_node(T val)
{
    tree_node* node = new tree_node;

	if (node != nullptr) {
    	node->key = val;
		node->color = RED;
		node->left = nullptr;
		node->right = nullptr;
		node->parent = nullptr;
	}
    return node;
}

template <typename T>
typename RB_tree<T>::tree_node* RB_tree<T>::find_min(tree_node *&node)
{
    tree_node *ptr = node;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}

template <typename T>
typename RB_tree<T>::tree_node* RB_tree<T>::delete_bst(tree_node *&root, T data)
{
    if (root == nullptr)
        return root;
    if (this->comparator->compare(data, (*root).key) < 0)
        return delete_bst(root->left, data);
    if (this->comparator->compare(data, (*root).key) > 0)
        return delete_bst(root->right, data);
    if (root->left == nullptr || root->right == nullptr)
        return root;

    tree_node* temp = find_min(root->right);

    root->key = temp->key;
    return delete_bst(root->right, temp->key);
}

template <typename T>
typename RB_tree<T>::tree_node* RB_tree<T>::insert_bst(tree_node *&root, tree_node *&node)
{
    if (root == nullptr)
        return node;

    if (this->comparator->compare((*node).key, (*root).key) < 0) {
        root->left = insert_bst(root->left, node);
        root->left->parent = root;
    }
	else if (this->comparator->compare((*node).key, (*root).key) >= 0) {
        root->right = insert_bst(root->right, node);
        root->right->parent = root;
    }
    return root;
}


template <typename T>
bool RB_tree<T>::find_node(T &&val)
{
	return find_node(root, val);
}

template <typename T>
bool RB_tree<T>::is_empty()
{
	return (root == nullptr);
}

template <typename T>
void RB_tree<T>::add_node(T &&val)
{
	tree_node* node = create_node(val);

	if (node != nullptr) {
		root = insert_bst(root, node);
		fix_insert(node);
	}
}

template <typename T>
void RB_tree<T>::delete_node(T &&val)
{
	tree_node* node = delete_bst(root, val);
    fix_delete(node);
}

template <typename T>
void RB_tree<T>::print_tree()
{
	if (root != nullptr)
		tree_print(this->root, 0);
}

template <typename T>
void RB_tree<T>::clear_tree()
{
	if (root != nullptr)
		delete_tree(root);
	root = nullptr;
	rotations = 0;
}

template <typename T>
unsigned int RB_tree<T>::get_rotations()
{
	return rotations;
}