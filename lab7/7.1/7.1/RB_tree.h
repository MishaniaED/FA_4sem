#pragma once

#include "binary_tree.h"

/* TEMPLATE RED_BLACK-TREE CLASS */

template <typename T>
class	Red_black_tree : public Binary_tree<T>
{
private:
	enum 			color {RED, BLACK};
	
	struct			tree_node
	{
		T			data;
		int			color;
		tree_node	*left;
		tree_node	*right;
		tree_node	*parent;
		
		//
	};

private:
	tree_node		*root;
	unsigned int	rotations;

	bool			find_node(tree_node *node, T val);
	int				get_color(tree_node *&node);
	void 			rotate_left(tree_node *&node);
	void 			rotate_right(tree_node *&node);
	void			delete_tree(tree_node *node);
	void			fix_insert(tree_node *&node);
	void			fix_delete(tree_node *&node);
	void			set_color(tree_node *&node, int color);
	void			tree_pretty_print(tree_node *curr, int depth);
	tree_node		*create_node(T val);
	tree_node		*find_min(tree_node *&node);
	tree_node		*delete_bst(tree_node *&root, T data);
	tree_node		*delete_node(tree_node *node, T val);
	tree_node		*insert_bst(tree_node *&root, tree_node *&node);

public:
	Red_black_tree(StrategyComparator<T> *compare);
	~Red_black_tree();

	bool			find_node(T &&val) override;
	bool			is_empty();
	void			print_tree();
	void			clear_tree();
	void			add_node(T &&val) override;
	void			delete_node(T &&val) override;
	unsigned int	get_rotations();
};

/* Constructors and destructors */

template <typename T>
Red_black_tree<T>::Red_black_tree(StrategyComparator<T> *compare) : Binary_tree<T>::Binary_tree(compare)
{
	root = nullptr;
	rotations = 0;
}

template <typename T>
Red_black_tree<T>::~Red_black_tree()
{
	if (root != nullptr)
		delete_tree(this->root);
}

/* Private methods (secondary) */

template <typename T>
bool									Red_black_tree<T>::find_node(tree_node *node, T val)
{
	if (node != nullptr)
	{
		if (this->comparator->compare(val, (*node).data) == 0)
			return (true);
		if (this->comparator->compare(val, (*node).data) < 0)
			return find_node(node->left, val);
		else
			return find_node(node->right, val);
	}
	return (false);
}

template <typename T>
int										Red_black_tree<T>::get_color(tree_node *&node)
{
    if (node == nullptr)
        return (BLACK);
    return (node->color);
}

template <typename T>
void									Red_black_tree<T>::rotate_left(tree_node *&node)
{
    tree_node	*right_child = node->right;

    node->right = right_child->left;
    if (node->right != nullptr)
        node->right->parent = node;
    right_child->parent = node->parent;

    if (node->parent == nullptr)
        root = right_child;
    else if (node == node->parent->left)
        node->parent->left = right_child;
    else
        node->parent->right = right_child;

    right_child->left = node;
    node->parent = right_child;
	rotations++;
}

template <typename T>
void									Red_black_tree<T>::rotate_right(tree_node *&node)
{
    tree_node	*left_child = node->left;

    node->left = left_child->right;
    if (node->left != nullptr)
        node->left->parent = node;
    left_child->parent = node->parent;

    if (node->parent == nullptr)
        root = left_child;
    else if (node == node->parent->left)
        node->parent->left = left_child;
    else
        node->parent->right = left_child;

    left_child->right = node;
    node->parent = left_child;
	rotations++;
}

template <typename T>
void									Red_black_tree<T>::delete_tree(tree_node *node)
{
	if (node != nullptr)
	{
		delete_tree(node->left);
		delete_tree(node->right);
		delete node;
	}
}

template <typename T>
void									Red_black_tree<T>::fix_insert(tree_node *&node)
{
    tree_node	*parent = nullptr;
    tree_node	*grandparent = nullptr;

    while (node != root && get_color(node) == RED && get_color(node->parent) == RED)
	{
        parent = node->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left)
		{
            tree_node	*uncle = grandparent->right;

            if (get_color(uncle) == RED)
			{
                set_color(uncle, BLACK);
                set_color(parent, BLACK);
                set_color(grandparent, RED);
                node = grandparent;
            }
			else
			{
                if (node == parent->right)
				{
                    rotate_left(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotate_right(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
		else
		{
           tree_node	*uncle = grandparent->left;

            if (get_color(uncle) == RED)
			{
                set_color(uncle, BLACK);
                set_color(parent, BLACK);
                set_color(grandparent, RED);
                node = grandparent;
            }
			else
			{
                if (node == parent->left)
				{
                    rotate_right(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotate_left(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }
    set_color(root, BLACK);
}

template <typename T>
void									Red_black_tree<T>::fix_delete(tree_node *&node)
{
    if (node == nullptr)
        return ;
    if (node == root)
	{
        root = nullptr;
        return ;
    }
    if (get_color(node) == RED || get_color(node->left) == RED || get_color(node->right) == RED)
	{
        tree_node	*child = node->left != nullptr ? node->left : node->right;

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            set_color(child, BLACK);
            delete node;
        }
		else
		{
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            set_color(child, BLACK);
            delete node;
        }
    }
	else
	{
        tree_node	*sibling = nullptr;
        tree_node	*parent = nullptr;
        tree_node	*ptr = node;

        set_color(ptr, BLACK);
        while (ptr != root && get_color(ptr) == BLACK)
		{
            parent = ptr->parent;
            if (ptr == parent->left)
			{
                sibling = parent->right;
                if (get_color(sibling) == RED)
				{
                    set_color(sibling, BLACK);
                    set_color(parent, RED);
                    rotate_left(parent);
                }
				else
				{
                    if (get_color(sibling->left) == BLACK && get_color(sibling->right) == BLACK)
					{
                        set_color(sibling, RED);
                        if(get_color(parent) == RED)
                            set_color(parent, BLACK);
                        else
                            set_color(parent, BLACK);
                        ptr = parent;
                    }
					else
					{
                        if (get_color(sibling->right) == BLACK)
						{
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
			else
			{
                sibling = parent->left;
                if (get_color(sibling) == RED)
				{
                    set_color(sibling, BLACK);
                    set_color(parent, RED);
                    rotate_right(parent);
                }
				else
				{
                    if (get_color(sibling->left) == BLACK && get_color(sibling->right) == BLACK)
					{
                        set_color(sibling, RED);
                        if (get_color(parent) == RED)
                            set_color(parent, BLACK);
                        else
                            set_color(parent, BLACK);
                        ptr = parent;
                    }
					else
					{
                        if (get_color(sibling->left) == BLACK)
						{
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
void									Red_black_tree<T>::set_color(tree_node *&node, int color)
{
    if (node == nullptr)
        return ;
    node->color = color;
}

template <typename T>
void									Red_black_tree<T>::tree_pretty_print(tree_node *curr, int depth)
{
    int 	i;
	int 	rec[1000];

    if (curr == nullptr)
		return;
    for (i = 0; i < depth; i++)
	{
        if (i == depth - 1)
			std::cout << (rec[depth-1] ? "  \u0371" : "  \u221F") << "\u2014\u2014\u2014";
        else
			std::cout << (rec[i] ? "\u23B8" : "  ") << "   ";
	}
	std::cout << " " << *(curr->data) << ((curr->color == 0) ? " (RED) " : " (BLACK) ") << std::endl;
    rec[depth] = 1;
    tree_pretty_print(curr->left,depth+1);
    rec[depth] = 0;
    tree_pretty_print(curr->right,depth+1);
}

template <typename T>
typename Red_black_tree<T>::tree_node	*Red_black_tree<T>::create_node(T val)
{
    tree_node	*node = new tree_node;

	if (node != nullptr)
	{
    	node->data = val;
		node->color = RED;
		node->left = nullptr;
		node->right = nullptr;
		node->parent = nullptr;
	}
    return (node);
}

template <typename T>
typename Red_black_tree<T>::tree_node	*Red_black_tree<T>::find_min(tree_node *&node)
{

    tree_node *ptr = node;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}

template <typename T>
typename Red_black_tree<T>::tree_node	*Red_black_tree<T>::delete_bst(tree_node *&root, T data)
{
    if (root == nullptr)
        return root;
    if (this->comparator->compare(data, (*root).data) < 0)
        return delete_bst(root->left, data);
    if (this->comparator->compare(data, (*root).data) > 0)
        return delete_bst(root->right, data);
    if (root->left == nullptr || root->right == nullptr)
        return root;

    tree_node	*temp = find_min(root->right);

    root->data = temp->data;
    return delete_bst(root->right, temp->data);
}

template <typename T>
typename Red_black_tree<T>::tree_node	*Red_black_tree<T>::insert_bst(tree_node *&root, tree_node *&node)
{
    if (root == nullptr)
        return (node);

    if (this->comparator->compare((*node).data, (*root).data) < 0)
	{
        root->left = insert_bst(root->left, node);
        root->left->parent = root;
    }
	else if (this->comparator->compare((*node).data, (*root).data) >= 0)
	{
        root->right = insert_bst(root->right, node);
        root->right->parent = root;
    }
    return (root);
}

/* Public methods */

template <typename T>
bool									Red_black_tree<T>::find_node(T &&val)
{
	return (find_node(root, val));
}

template <typename T>
bool									Red_black_tree<T>::is_empty()
{
	return (root == nullptr);
}

template <typename T>
void									Red_black_tree<T>::add_node(T &&val)
{
	tree_node	*node = create_node(val);

	if (node != nullptr)
	{
		root = insert_bst(root, node);
		fix_insert(node);
	}
}

template <typename T>
void									Red_black_tree<T>::delete_node(T &&val)
{
	tree_node	*node = delete_bst(root, val);

    fix_delete(node);
}

template <typename T>
void									Red_black_tree<T>::print_tree()
{
	if (root != nullptr)
		tree_pretty_print(this->root, 0);
}

template <typename T>
void									Red_black_tree<T>::clear_tree()
{
	if (root != nullptr)
		delete_tree(root);
	root = nullptr;
	rotations = 0;
}

template <typename T>
unsigned int							Red_black_tree<T>::get_rotations()
{
	return (rotations);
}
