#pragma once

#include <iostream>

struct Task
{
public:
	std::vector<double> dataToTransfer;
	std::vector<unsigned int> children;

	Task(unsigned int _type, unsigned int _id) : type(_type), id(_id) {}

	Task(std::string name, unsigned int _id)
	{
		id = _id;
		try
		{
			type = TaskType.GetId(name);
		} catch (const std::out_of_range& message)
		{
			type = 0;
			std::cout << message.what() << std::endl;
		}
	}

	unsigned int GetType()
	{
		return type;
	}

	unsigned int GetId()
	{
		return id;
	}

private:
	unsigned int type;
	unsigned int id;
};

struct TaskGraph
{
public:
	friend class FileInterpreter; //file can load into taskGraph
	friend int main();

	//Tree<Task> graph;
private:
	//this is used for faster comunication
	//between habitats and task graph
	std::vector<Task> taskList;

public:
	Task& operator[](unsigned int i)
	{
		return taskList[i];
	}

	unsigned int size()
	{
		return taskList.size();
	}
};

//actually the class is not a singleton, but our program
//uses only ONE task graph, soooo
TaskGraph taskGraph;