#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class TreeNode
{
public:
	T data;
	std::vector<std::unique_ptr<TreeNode<T>>> children;

	explicit TreeNode(const T& value) : data(value) {}
};

template <typename T>
class Tree
{
public:
	Tree() = default;

	bool isEmpty() const { return root == nullptr; }

	void insert(const T& value)
	{
		if (isEmpty())
		{
			root = std::make_unique<TreeNode<T>>(value);
		}
		else
		{
			insertRecursive(value, root);
		}
	}

	void insertRecursive(const T& value, std::unique_ptr<TreeNode<T>>& node)
	{
		if (node == nullptr)
		{
			node = std::make_unique<TreeNode<T>>(value);
			return;
		}

		// Choose the appropriate child node based on your algorithm's criteria
		// Here, we simply add the new node as a child
		node->children.push_back(std::make_unique<TreeNode<T>>(value));
	}

	void swapSubtrees() { swapSubtreesRecursive(root); }

	void swapSubtreesRecursive(std::unique_ptr<TreeNode<T>>& node)
	{
		if (node == nullptr)
		{
			return;
		}

		// Swap the children of the current node
		std::reverse(node->children.begin(), node->children.end());

		for (auto& child : node->children)
		{
			swapSubtreesRecursive(child);
		}
	}

private:
	std::unique_ptr<TreeNode<T>> root = nullptr;
};
