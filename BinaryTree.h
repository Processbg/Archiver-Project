#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include "Pair.h"
#include "Vector.hpp"

template<class T>
class BinaryTree
{
private:

	struct Node
	{
		Node() : left(0), right(0){}

		Node(const Pair<T>& key, Node* left, Node* right) :
			data(key), left(left), right(right){}

		Pair<T> data;
		Node* left;
		Node* right;

	};
	int size;
	Node* root;

	Node* copyTree(Node* root)
	{
		if (root)
		{
			return new Node(root->data,
				copyTree(root->left), copyTree(root->right));
		}

		return root;
	}

	void findAndSetPathInTree(Node*&, Vector<bool>&, Vector<Vector<bool>>&);
	bool find(Node*&, const Vector<bool>&, const T&);
	void destroyTree(Node*);

public:

	BinaryTree(){ root = new Node; }
	BinaryTree(const Pair<T>& pair): size(0){ root = new Node(pair, nullptr, nullptr); }
	BinaryTree(const BinaryTree<T>&);
	BinaryTree<T>& operator=(const BinaryTree<T>&);
	~BinaryTree(){ destroyTree(root); }

	bool operator<(const BinaryTree<T>&) const;
	bool operator>(const BinaryTree<T>&) const;

	static void mergeTrees(BinaryTree<T> &current, BinaryTree<T> &other, BinaryTree<T> &result)
	{
		if (!current.root)
		{
			if (!other.root)
			{
				return;
			}
		}

		if (!other.root)
		{
			if (current.root)
			{
				result.root = current.root;
				current.root = nullptr;
				return;
			}
		}

		if (!current.root)
		{
			if (other.root)
			{
				result.root = other.root;
				other.root = nullptr;
				return;
			}
		}

		if (current.getRootData() == other.getRootData())
		{
			return;
		}

		result.root->data = current.root->data + other.root->data;

		result.root->left = current.root;
		current.root = nullptr;
		result.root->right = other.root;
		other.root = nullptr;
	}

	int getSize() const { return size; }
	Pair<T> getRootData() const { return root->data; }

	bool find(const Vector<bool>&, const T&);
	void findAndSetPathsInTree(Vector<bool>& path, Vector<Vector<bool>>& allpaths)
	{
		findAndSetPathInTree(root, path, allpaths);
	}

};

#endif // !_BINARY_TREE_H_
