#pragma once
#include "BaseManager.hpp"
#include "Randomizer.hpp"

//wrapper for base manager
class GeneticAlgorithm : public BaseManager
{
public:
//0 habitat is always root
std::vector<int> parents;

public:
Habitat StartGeneticAlgorithm(BaseManager _base)
{
parents = std::vector<int>();
//at start relation is ->->->->->
for (int i = 0; i < habitats.size(); ++i)
{
parents.push_back(i - 1);
}
}

void MutateParents(std::vector<int>& parents)
{
    std::uniform_int_distribution<> indexDis(0, parents.size() - 1);
    int i = indexDis(gen);

    std::uniform_int_distribution<> valueDis(0, parents.size() - 1);
    int randomValue = valueDis(gen);

    while (randomValue == i)
    {
        randomValue = valueDis(gen);
    }

    parents[i] = randomValue;
}

void RedistributeTasks()
{
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
        RedistributeTasksInner(i);
    }
}

void RedistributeTasksInner(int hab)
{
    if (habitats[parents[hab]].tasksRedistributed == false)
    {
        RedistributeTasksInner(parents[hab]);
    }
    //actual redistribution
    habitats[hab].takenTasks = habitats[parents[hab]].takenTasks;
    habitats[hab].tasksRedistributed = true;
}

//crossing on tree relation

//crossing on channels

//mutation on task percentage

//mutation on channels
