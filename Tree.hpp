#pragma once

#include <iostream>
#include <utility>
#include <vector>

template <typename T>
class TreeNode
{
public:
	T data;
	std::vector<TreeNode<T> *> children;

	explicit TreeNode(T x) : data(x) {}
};

// ||--------------------------------------------------------------------------------||
// ||              Tree data structure for use in the genetic algorithm              ||
// ||--------------------------------------------------------------------------------||

template <typename T>
class Tree
{
public:
	Tree() = default;
	~Tree() { destroyTree(root); }

	Tree(const Tree &other) { root = copyTree(other.root); }
	Tree &operator=(const Tree &other)
	{
		if (this != &other)
		{
			destroyTree(root);
			root = copyTree(other.root);
		}
		return *this;
	}

	void insert(const T &value, const T &parent)
	{
		if (search(value) != nullptr)
			return;  // do nothing if node with given value already exists

		TreeNode<T> *newNode    = new TreeNode<T>(value);
		TreeNode<T> *parentNode = search(parent);

		if (parentNode == nullptr)
		{
			if (root != nullptr)
				return;  // do nothing if root already exists
			root = newNode;
		}
		else
		{
			parentNode->children.push_back(newNode);
		}
	}

	void insert(const std::vector<std::pair<T, T>> &edge)
	{
		TreeNode<T> *newNode    = new TreeNode<T>(edge.second);
		TreeNode<T> *parentNode = search(edge.first);

		if (parentNode == nullptr)
			root = newNode;

		else
			parentNode->children.push_back(newNode);
	}

	void swapSubtrees(Tree<T> &other, const T &value1, const T &value2)
	{
		TreeNode<T> *node1 = search(value1);
		TreeNode<T> *node2 = other.search(value2);

		if (node1 == nullptr || node2 == nullptr)
			return;  // do nothing if any of the nodes don't exist

		// Swap the subtrees by swapping the children pointers
		std::swap(node1->children, node2->children);
	}

	// Perform crossover operation to create offspring from selected parents
	TreeNode<T> *crossover(const std::vector<TreeNode<T> *> &parents, int randomValue)
	{
		TreeNode<T> *offspring = nullptr;

		if (parents.size() < 2)
			return TreeNode<T>();  // do nothing if there aren't enough parents

		// Choose a random parent as the root of the offspring tree
		int randomIndex = randomValue % parents.size();
		offspring       = new TreeNode<T>(parents[randomIndex]->data);

		// Recursively copy the children of the selected parents
		for (const TreeNode<T> *child : parents[randomIndex]->children)
		{
			TreeNode<T> *childCopy = copyTree(child);
			offspring->children.push_back(childCopy);
		}

		// Combine the children from other parents randomly
		for (size_t i = 0; i < parents.size(); ++i)
		{
			if (i != randomIndex)
			{
				for (const TreeNode<T> *child : parents[i]->children)
				{
					if (randomValue % 2 == 0)  // Randomly choose whether to include the child
					{
						TreeNode<T> *childCopy = copyTree(child);
						offspring->children.push_back(childCopy);
					}
				}
			}
		}

		return offspring;
	}

	void destroyTree()
	{
		destroyTreeFromNode(root);
		root = nullptr;
	}

	void destroyTreeFrom(const T &value)
	{
		TreeNode<T> *node = search(value);

		if (node != nullptr)
		{
			for (TreeNode<T> *child : node->children)
			{
				destroyTreeFromNode(child);
			}
			delete node;
		}
	}

	void print() { printFromNode(root); }

private:
	TreeNode<T> *root = nullptr;

	void insertNode(const T &value, TreeNode<T> *parent)
	{
		TreeNode<T> *newNode = new TreeNode<T>(value);
		if (parent == nullptr)
			root = newNode;

		else
			parent->children.push_back(newNode);
	}

	TreeNode<T> *copyTree(const TreeNode<T> *node)
	{
		if (node == nullptr)
			return nullptr;

		TreeNode<T> *newNode = new TreeNode<T>(node->data);

		for (const TreeNode<T> *child : node->children)
		{
			TreeNode<T> *childCopy = copyTree(child);
			newNode->children.push_back(childCopy);
		}

		return newNode;
	}

	void destroyTreeFromNode(TreeNode<T> *node)
	{
		if (node != nullptr)
		{
			for (TreeNode<T> *child : node->children)
			{
				destroyTreeFromNode(child);
			}
			delete node;
		}
	}

	TreeNode<T> *search(const T &value) { return searchNode(root, value); }

	TreeNode<T> *searchNode(TreeNode<T> *node, const T &value)
	{
		if (node == nullptr)
			return nullptr;

		if (node->data == value)
			return node;

		for (TreeNode<T> *child : node->children)
		{
			TreeNode<T> *result = searchNode(child, value);
			if (result != nullptr)
				return result;
		}

		return nullptr;
	}

	void printFromNode(TreeNode<T> *node, int indentation = 0)
	{
		if (node != nullptr)
		{
			std::cout << std::string(indentation, '\t') << "TreeNode: " << node->data << "\t\tChildren:\n";

			for (TreeNode<T> *child : node->children)
			{
				std::cout << std::string(indentation + 1, '\t') << child->data << std::endl;
			}

			for (TreeNode<T> *child : node->children)
			{
				printFromNode(child, indentation + 1);
			}
		}
	}
};
