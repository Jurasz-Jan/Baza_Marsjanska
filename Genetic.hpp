#pragma once
#include "BaseManager.hpp"
#include "Randomizer.hpp"

//wrapper for base manager
class GeneticAlgorithm: public BaseManager
{
public:
	//0 habitat is always root
	std::vector<int> parents;

public:

	GeneticAlgorithm(BaseManager _base)
	{
		parents = std::vector<int>();
		//at start relation is ->->->->->
		for (int i = 0; i < habitats.size(); ++i)
		{
			parents.push_back(i - 1);
		}
	}

	void RedistributeTasks()
	{
		//clear last tasks settings
		for (int i = 0; i < parents.size(); ++i)
		{
			habitats[i].takenTasks.clear();
			habitats[i].tasksRedistributed = false;
		}
		//root has always all tasks at start
		for (int i = 0; i < taskGraph.size(); ++i)
		{
			habitats[0].takenTasks.push_back(i);
		}
		habitats[0].tasksRedistributed = true;

		//redistributing
		for (int i = 1; i < parents.size(); ++i)
		{
			int fakeReq = i;
			while (habitats[parents[fakeReq]].tasksRedistributed == false)
			{
				
			}
		}
	}

	void RedistributeTasksInner(int hab)
	{
		if (habitats[parents[hab]].tasksRedistributed == false)
		{
			RedistributeTasksInner(parents[hab]);
		}
		//actual redistribution
	}

	//crossing on tree relation

	//crossing on channels

	//mutation on task percentage

	//mutation on channels
};
