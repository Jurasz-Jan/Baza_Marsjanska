#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

template <typename T>
struct WeightedGraphEdge
{
	T from;
	T to;
	int weight;

	WeightedGraphEdge(const T& _from, const T& _to, int _weight) : from(_from), to(_to), weight(_weight) {}
};

// ||--------------------------------------------------------------------------------||
// ||                       WeightedGraph for use as TaskGraph                       ||
// ||--------------------------------------------------------------------------------||
//
// !! important
// let me know if you need any more functionality, will be happy to help
template <typename T>
class WeightedGraph
{
public:
	std::vector<WeightedGraphEdge<T>> > &operator[](const T& vertex) { return vertexMap[vertex]; }

	auto begin() const { return vertexMap.begin(); }
	auto end() const { return vertexMap.end(); }

	// Doesn't allow multiple edges between same vertices.
	// Kinda obvious, but maybe somebody would want to have different edges with different weights IDK.
	// It can't happen there though.
	void addEdge(const T& from, const T& to, int weight)
	{
		// TODO: copypaste from my different program, keeping it here but should be removed.
		// // if we don't already have this connection
		//// if (std::find(vertexMap[from].begin(), vertexMap[from].end(), to) == vertexMap[from].end())
		//// 	vertexMap[from].push_back(to);

		// // otherwise do nothing

		// if we don't already have this connection
		if (!hasConnection(from, to))
		{
			WeightedGraphEdge<T> edge(from, to, weight);
			vertexMap[from].push_back(edge);
		}
		// otherwise do nothing

		// if the "to" vertex doesn't already exist, create one without any connections.
		if (!hasVertex(to))
		{
			std::vector<WeightedGraphEdge<T>> > dummy;
			vertexMap[to] = dummy;
		}
	}

	// Will always remove just this one edge (provided it does exist).
	// Will not change anything else, so the node "to" can become another root node
	// and have it's own baby graph below it.
	void removeEdgeDirty(const T& from, const T& to)
	{
		if (hasConnection(from, to))
		{
			for (auto& edge : from.second)
			{
				if (edge.to == to)
				{
					from.second.erase(edge);
					break;
				}
			}
		}
	}

	std::vector<T> getRoots() const
	{
		std::vector<T> roots;

		for (const auto& pair : vertexMap)
		{
			if (isRoot(pair.first))
				roots.push_back(pair.first);
		}

		return roots;
	}

	std::vector<T> getChildren(const T& parentVertex) const
	{
		std::vector<T> children;

		for (const auto& edge : vertexMap[parentVertex].second)
		{
			children.push_back(edge.to);
		}

		return children;
	}

	std::vector<T> getWeights(const T& parentVertex) const
	{
		std::vector<T> weights;

		for (const auto& edge : vertexMap[parentVertex].second)
		{
			weights.push_back(edge.weight);
		}

		return weights;
	}

	// Returns -1 if connection doesn't exist.
	int getConnectionWeight(const T& from, const T& to) const
	{
		if (!hasConnection(from, to))
			return -1;

		for (const auto& edge : VertexMap[from].second)
		{
			if (edge.to == to)
				return edge.weight;
		}

		return -1;  // just 2B sure
	}

	bool hasVertex(const T& vertex) const
	{
		if (vertexMap.find(vertex) == vertexMap.end())
			return false;
		return true;
	}

	bool hasConnection(const T& from, const T& to) const
	{
		if (!hasVertex(from))
			return false;

		for (const auto& edge : VertexMap[from].second)
		{
			if (edge.to == to)
				return true;
		}

		return false;
	}

	bool isRoot(const T& vertex) const
	{
		if (!hasVertex(vertex))
			return false;

		for (const auto& pair : vertexMap)
		{
			const std::vector<WeightedGraphEdge<T>>& edges = pair.second;

			for (const WeightedGraphEdge<T>& edge : edges)
			{
				if (edge.to == vertex)
					return false;
			}
		}
		return true;
	}

	bool isLeaf(const T& vertex) const
	{
		if (!hasVertex(vertex))
			return false;

		return vertexMap[vertex].size() == 0;
	}

	int size() const { return vertexMap.size(); }

	//* -------------
	//*   PRINTING
	//* -------------
	void printGraph()
	{
		for (const auto& pair : vertexMap)
		{
			const T& vertex                                = pair.first;
			const std::vector<WeightedGraphEdge<T>>& edges = pair.second;

			std::cout << "Vertex " << vertex << " is connected to:\n";
			for (const WeightedGraphEdge<T>& edge : edges)
			{
				std::cout << "  -> to: " << edge.to << ", Weight: " << edge.weight << "\n";
			}
			std::cout << std::endl;
		}
	}

	//* -------------
	//*   SEARCHING
	//* -------------

	//TODO: everything (if it will be ever needed, let me know).

private:
	std::unordered_map<T, std::vector<WeightedGraphEdge<T>>> vertexMap;
};