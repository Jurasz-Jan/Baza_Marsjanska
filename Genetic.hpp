#pragma once
#include "BaseManager.hpp"
#include "Randomizer.hpp"

//wrapper for base manager
class GeneticAlgorithm : public BaseManager
{
public:
    friend int main();
    //0 habitat is always root
    std::vector<int> parents;

public:
    /*
    GeneticAlgorithm()
    {
        parents = std::vector<int>();
        //at start relation is ->->->->->
        for (int i = 0; i < habitats.size(); ++i)
        {
            parents.push_back(i - 1);
            std::cout << "parents ";
            std::cout << parents[parents.size() - 1] << " ";
        }
    }
    */

    void AddHabitat(Habitat newHabitat) override
    {
        habitats.push_back(newHabitat);
        parents.push_back(parents.size() - 1);
    }

    void MutateParents()  //niepotrzebne
    {
        if (parents.size() <= 0)
        {
            return;
        }
        int i = RandomGenerator.RandomIntRange(1, parents.size() - 1);
        int randomValue = RandomGenerator.RandomIntRange(1, parents.size() - 1);

        while (randomValue == i)
        {
            randomValue = RandomGenerator.RandomIntRange(1, parents.size() - 1);
        }

        parents[i] = randomValue;
    }

    void MutateHabitat()
    {
        if (parents.size() <= 0)
        {
            return;
        }
        for (int i = 0; i < habitats.size();++i)
        {
            if (RandomGenerator.RandomDoublePercent() > 0.9)
            {
                int o = RandomGenerator.RandomIntRange(1, 3);
                if (o == 1)
                {
                    habitats[i].taskPercentage = RandomGenerator.RandomDoublePercent();
                    //habitats[i].comChannels[RandomGenerator.RandomIntRange(0, ChannelType.GetSize() - 1)];
                }
            }
        }
    }



    void Crossover()//call Crossover(SelectionWorst,SelectionBest)
    {
        int worst = SelectionWorst();
        int best = SelectionBest();
        int crossoverPoint = RandomGenerator.RandomIntRange(0, ChannelType.GetSize() - 1);
            if (RandomGenerator.RandomIntRange(0, 1))
            {
                for (int i = 0; i < crossoverPoint; ++i)
                {
                    if (i < best)
                    {
                        habitats[worst].comChannels[i] = habitats[best].comChannels[i];
                    }
                }
            }
            else
            {
                for (int i = crossoverPoint; i < habitats.size(); ++i)
                {
                    if (i > best)
                    {
                        habitats[worst].comChannels[i] = habitats[best].comChannels[i];
                    }
                }
            }
            habitats[worst].taskPercentage = (habitats[worst].taskPercentage + habitats[best].taskPercentage) / 2;
    }




    void RedistributeTasks()
    {
        for (int i = 0; i < habitats.size(); ++i)
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

        //*
        //redistributing
        for (int i = 1; i < habitats.size(); ++i)
        {
            RedistributeTasksInner(i);
        }
        //*/
    }

    private:

        void RedistributeTasksInner(int hab)
        {
            if (habitats[parents[hab]].tasksRedistributed == false)
            {
                std::cout << "go to parent" << std::endl;
                RedistributeTasksInner(parents[hab]);
            }
            //actual redistribution
            int maxTake = (int)((double)habitats[parents[hab]].takenTasks.size() / habitats[hab].taskPercentage);
            std::cout << "actual take " << maxTake << std::endl;
            int currentTake = 0;
            for (int i = 0; i < habitats[parents[hab]].takenTasks.size(); ++i)
            {
                std::vector<int> possibleTypes = BaseData.HabitatTasks(hab);
                for (int j = 0; j < possibleTypes.size(); ++j)
                {
                    //can add only tasks desirable to habitat
                    if (taskGraph[habitats[parents[hab]].takenTasks[i]].GetType() == possibleTypes[j])
                    {
                        if (currentTake < maxTake)
                        {
                            habitats[hab].takenTasks.push_back(habitats[parents[hab]].takenTasks[i]);
                            habitats[parents[hab]].takenTasks.erase(habitats[parents[hab]].takenTasks.begin() + i);
                            currentTake += 1;
                        }
                    }
                }
            }
            //habitats[hab].takenTasks = habitats[parents[hab]].takenTasks;
            habitats[hab].tasksRedistributed = true;
        }

        int SelectionWorst()
        {
            int min_rating = habitats[0].takenTasks.size();
            int o = 0;
            for (int i = 1; i < habitats.size();++i)
            {
                if (habitats[i].takenTasks.size() < min_rating)
                {
                        o = i;
                        min_rating = habitats[i].takenTasks.size();
                }
            }
            return o;//index of worst
        }

        int SelectionBest()
        {
            int min_rating = habitats[0].takenTasks.size();
            int o = 0;
            for (int i = 1; i < habitats.size();++i)
            {
                if (habitats[i].takenTasks.size() > min_rating)
                {
                        o = i;
                        min_rating = habitats[i].takenTasks.size();
                }
            }
            return o;//index of best
        }

    //crossing


    //crossing on channels
    /*
    void RunAlgorithm()
    {
        bool runFurther = true;
        int time1, time2, time3;
        while (runFurther)
        {
            Crossover(SelectionWorst, SelectionNext);
            MutateHabitat();
            time3 = GetTime();
            if (time3 >= 0.99 * time2 && time3 >= 0.99time1)
            {
                runFurther = false;
            }

        }

    }
    */


    //jak robić geneticalgorithm
    //Crossover(SelectionWorst,SelectionNext)
    //Mutate()
    //thats all folks
    //ChannelType.GetSize()//zwraca ilość kanałów komunikacyjnych
};
