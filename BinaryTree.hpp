#ifndef _BINARY_TREE_HPP_
#define _BINARY_TREE_HPP_

#include <iostream>
#include "BinaryTree.h"

template <class T>
inline void BinaryTree<T>::destroyTree(Node* root)
{
	if (root)
	{
		destroyTree(root->left);
		destroyTree(root->right);
		delete root;
	}
}

template <class T>
inline BinaryTree<T>::BinaryTree(const BinaryTree<T>& other)
{
	root = nullptr;
	root = copyTree(other.root);
}

template <class T>
inline BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other)
{
	if (this != &other)
	{
		destroyTree(root);
		root = nullptr;
		root = copyTree(other.root);
	}

	return *this;
}

template <class T>
inline bool BinaryTree<T>::operator<(const BinaryTree<T>& other) const
{
	if (root->data < other.root->data)
	{
		return true;
	}

	return false;
}

template <class T>
inline bool BinaryTree<T>::operator>(const BinaryTree<T>& other) const
{
	if (!(*this < other))
	{
		return true;
	}

	return false;
}

template <class T>
inline bool BinaryTree<T>::find(const Vector<bool>& path, const T& key)
{
	if (find(root, path, key))
	{
		return true;
	}

	return false;
}

template <class T>
inline bool BinaryTree<T>::find(Node*& root, const Vector<bool>& path, const T& key)
{
	if (root)
	{
		if (root->data.getData() == key)
		{
			return true;
		}
		
		int sizeOfPath = path.getNumberOfElements();
		
		for (int i = 0; i < sizeOfPath; ++i)
		{
			if (!path[i])
			{
				if (root->left)
				{
					if (root->left->data.getData() == key)
					{
						return true;
					}

					return find(root->left, path, key);
				}
			}

			if (root->right)
			{
				if (root->right->data.getData() == key)
				{
					return true;
				}

				return find(root->right, path, key);
			}
		}
	}

	return false;
}

template <class T>
inline void BinaryTree<T>::findAndSetPathInTree(Node*& root, Vector<bool>& path, Vector<Vector<bool>>& allpaths)
{
	if (root)
	{
		path.pushBack(0);
		findAndSetPathInTree(root->left, path, allpaths);
		if (!root->left)
		{
			path.pop();
		}

		path.pushBack(1);
		findAndSetPathInTree(root->right, path, allpaths);
		if (!root->right)
		{
			path.pop();
		}

		if (!root->left)
		{
			if (!root->right)
			{
				allpaths.pushBack(path);
			}
		}
	}
}

#endif // !_BINARY_TREE_HPP_
