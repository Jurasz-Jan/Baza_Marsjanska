#pragma once

#include <iostream>
#include <utility>
#include <vector>

template <typename T>
class TreeNode
{
public:
	T data;
	std::vector<TreeNode *> children;

	explicit TreeNode(T x) : data(x) {}
};

// ||--------------------------------------------------------------------------------||
// ||              Tree data structure for use in the genetic algorightm             ||
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

		TreeNode *newNode    = new TreeNode(value);
		TreeNode *parentNode = search(parent);

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
		TreeNode *newNode    = new TreeNode(edge.second);
		TreeNode *parentNode = search(edge.first);

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
	TreeNode *crossover(const std::vector<TreeNode *> &parents, int randomValue)
	{
		TreeNode *offspring = nullptr;

		if (parents.size() < 2)
			return;  // do nothing if there aren't enough parents

		// Choose a random parent as the root of the offspring tree
		int randomIndex = randomValue % parents.size();
		offspring       = new TreeNode(parents[randomIndex]->data);

		// Recursively copy the children of the selected parents
		for (const TreeNode *child : parents[randomIndex]->children)
		{
			TreeNode *childCopy = copyTree(child);
			offspring->children.push_back(childCopy);
		}

		// Combine the children from other parents randomly
		for (size_t i = 0; i < parents.size(); ++i)
		{
			if (i != randomIndex)
			{
				for (const TreeNode *child : parents[i]->children)
				{
					if (rand() % 2 == 0)  // Randomly choose whether to include the child
					{
						TreeNode *childCopy = copyTree(child);
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
		TreeNode *node = search(value);

		if (node != nullptr)
		{
			for (TreeNode *child : node->children)
			{
				destroyTreeFromNode(child);
			}
			delete node;
		}
	}

	void print() { printFromNode(root); }

private:
	TreeNode *root = nullptr;

	void insertNode(const T &value, TreeNode *parent)
	{
		TreeNode *newNode = new TreeNode(value);
		if (parent == nullptr)
			root = newNode;

		else
			parent->children.push_back(newNode);
	}

	TreeNode *copyTree(const TreeNode *node)
	{
		if (node == nullptr)
			return nullptr;

		TreeNode *newNode = new TreeNode(node->data);

		for (const TreeNode *child : node->children)
		{
			TreeNode *childCopy = copyTree(child);
			newNode->children.push_back(childCopy);
		}

		return newNode;
	}

	void destroyTreeFromNode(TreeNode *node)
	{
		if (node != nullptr)
		{
			for (TreeNode *child : node->children)
			{
				destroyTreeFromNode(child);
			}
			delete node;
		}
	}

	TreeNode *search(const T &value) { return searchNode(root, value); }

	TreeNode *searchNode(TreeNode *node, const T &value)
	{
		if (node == nullptr)
			return nullptr;

		if (node->data == value)
			return node;

		for (TreeNode *child : node->children)
		{
			TreeNode *result = searchNode(child, value);
			if (result != nullptr)
				return result;
		}

		return nullptr;
	}

	void printFromNode(TreeNode *node, int indentation = 0)
	{
		if (node != nullptr)
		{
			std::cout << std::string(indentation, '\t') << "TreeNode: " << node->data << "\t\tChildren:\n";

			for (TreeNode *child : node->children)
			{
				std::cout << std::string(indentation + 1, '\t') << child->data << std::endl;
			}

			for (TreeNode *child : node->children)
			{
				printFromNode(child, indentation + 1);
			}
		}
	}
};
