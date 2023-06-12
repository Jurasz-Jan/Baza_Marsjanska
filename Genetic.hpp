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
GeneticAlgorithm()
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
    

    int i = RandomGenerator.RandomIntRange(1, parents.size());
    int randomValue = RandomGenerator.RandomIntRange(0,parents.size());

    while (randomValue == i)    
    {
        randomValue = RandomGenerator.RandomIntRange(1,parents.size());
    }

    parents[i] = randomValue;
}

void MutateHabitat()
{

    for (int i; i<habitats.size();++i)
    {
        if (RandomGenerator.RandomDoublePercent() > 0.9)
        {
            int o=RandomGenerator.RandomIntRange(1,3);
            if (o==1)
                {
                    habitats[i].taskPercentage=RandomGenerator.RandomDoublePercent();
                    habitats[i].comChannels[RandomGenerator.RandomIntRange(0,ChannelType.GetSize())]
                }
        }
    }
}

int SelectionWorst(){
    int min_rating=habitats[0].takentasks;
    int o=0;
    for (int i=1; i<habitats.size();++i)
        {
            if(habitats[i]).takentasks<min_rating
            {
                o=i;
                min_rating=habitats[i]).takentasks;
                
            
            }
        }
        return o;//index of worst
    }
    
int SelectionBest(){
    int max_rating=habitats[0].takentasks;
    int o=0;
    for (int i=1; i<habitats.size();++i)
        {
            if(habitats[i]).takentasks>max_rating
            {
                o=i;
                min_rating=habitats[i]).takentasks;
                
            
            }
        }
        return o;//index of best
    }
    


Crossover(worst,best)//call Crossover(SelectionWorst,SelectionBest)
{
    crossoverPoint(= RandomGenerator.RandomIntRange(0, ChannelType.GetSize()//);
    if(RandomIntRange(1, 0)
    {
        for (int i = 0; i < crossoverPoint; ++i)
            {
                if (i < best.size())
                {
                    habitats[worst].comChannels[i] = habitats[best].comChannels[i];
                }
            }

            
    }


    else
    {
        for (int i = crossoverPoint; i < habitats.size(); ++i)
            {
                if (i < best.size())
                {
                    habitats[worst].comChannels[i] = habitats[best].comChannels[i];
                }
            }

            
    }
        worstTaskPercentage = (bestTaskPercentage + worstTaskPercentage) / 2;
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
