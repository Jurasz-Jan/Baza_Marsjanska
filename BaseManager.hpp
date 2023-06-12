#pragma once
#include <stdexcept>
#include <iostream>
#include "Base.hpp"
#include "Task.hpp"

//"manager" is kind of class
//that well manages some sort of objects
//and that's it
//every "base" in abstract thinking
//schould have exacly ONE manager
class BaseManager
{
public:
    friend int main();
protected:
    std::vector<Habitat> habitats;
private:
    //for doing task graph
    std::vector<bool> taskTaken;
    std::vector<int> taskNeeds;
    std::vector<Habitat*> workingHabitats;

public:
    int HabitatsSize()
    {
        return habitats.size();
    }

    Habitat GetHabitat(int Id)
    {
        if (Id > habitats.size())
        {
            throw std::out_of_range("index " + std::to_string(Id) + "is out of range");
        }
        return habitats[Id];
    }

    void AddHabitat(const Habitat& newHabitat)
    {
        habitats.push_back(newHabitat);
    }

    //here stuff with whole task graph understanding

    double CalculateGlobalCost()
    {
        double globalCost = 0;
        //build cost of habs and channels
        for (int i = 0; i < habitats.size(); ++i)
        {
            globalCost += BaseData.HabitatBuildCost(habitats[i].GetType());
            for (int j = 0; j < habitats[i].comChannels.size(); ++j)
            {
                globalCost += BaseData.ChannelBuildCost(habitats[i].comChannels[j]);
            }
        }
        //cost of doing tasks
        //*
        for (int i = 0; i < habitats.size(); ++i)
        {
            for (int j = 0; j < habitats[i].takenTasks.size(); ++j)
            {
                globalCost += BaseData.HabitatTaskCost(habitats[i].GetType(), 0, true);
            }
        }
        //*/
        return globalCost;
    }

    //schould have alt version with debug couts
    double CalculateGlobalTime(bool debug)
    {
        //first create indicators
        taskTaken.clear();
        taskNeeds.clear(); //positive means unreachable
        //0 means active
        //-1 means done
        int size = taskGraph.size();
        for (int i = 0; i < size; ++i)
        {
            taskNeeds.push_back(0);
            taskTaken.push_back(false);
        }
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < taskGraph[i].children.size(); ++j)
            {
                taskNeeds[taskGraph[i].children[j]] += 1;
            }
        }

        //*
        //here choose tasks that can be done now:
        double globalTime = 0;
        std::vector<int> possibleTasks;
        do
        {
            possibleTasks.clear();
            for (int i = 0; i < size; ++i)
            {
                if (taskNeeds[i] == 0 && taskTaken[i] == false)
                {
                    possibleTasks.push_back(i);
                }
                
            }
            //debug
            std::cout << "possible tasks" << std::endl;
            for (int i = 0; i < possibleTasks.size(); ++i)
            {
                std::cout << possibleTasks[i] << "";
            }
            std::cout << std::endl;

            if (possibleTasks.size() == 1) //only one, so only one can be done
            {
                std::cout << "one task" << std::endl;
                int hab = FindHabitatForTask(possibleTasks[0]);
                
                if (!habitats[hab].isWorking)
                {
                    try
                    {
                        StartWorking(&(habitats[hab]), possibleTasks[0], debug);
                    }
                    catch (std::string message)
                    {
                        std::cout << message << std::endl;
                        return -1;
                    }
                }
                else
                {
                    std::cout << "all habitats taken" << std::endl;
                }
            }
            else if (possibleTasks.size() > 1)
            {
                //NO CHOOSING LONGEST TASK FOR NOW!!!!!
                std::vector<int> habs = FindHabitatForTask(possibleTasks);
                std::cout << "multi hab" << std::endl;

                bool tried = false;
                //for now not choosing longest route
                //if 2 or more tasks by same hab he just chooses first from left
                for (int i = 0; i < possibleTasks.size(); ++i)
                {
                    if (!habitats[habs[i]].isWorking)
                    {
                        try
                        {
                            StartWorking(&(habitats[habs[i]]), possibleTasks[i], debug);
                            tried = true;
                        }
                        catch (std::string message)
                        {
                            std::cout << message << std::endl;
                            return -1;
                        }
                    }
                }
                if (!tried)
                {
                    std::cout << "all habs taken" << std::endl;
                }

            }

            if (workingHabitats.size() > 0)
            {
                globalTime += PassGlobalTime(debug);
            }
            std::cout << "currently calculated time " << globalTime << std::endl;

        } while (possibleTasks.size() > 0); //no tasks, so we are done

        return globalTime;
    }

    //NO DEBUG
    //----------------------------------
    double CalculateGlobalTime()
    {
        //first create indicators
        taskTaken.clear();
        taskNeeds.clear(); //positive means unreachable
        //0 means active
        //-1 means done
        int size = taskGraph.size();
        for (int i = 0; i < size; ++i)
        {
            taskNeeds.push_back(0);
            taskTaken.push_back(false);
        }
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < taskGraph[i].children.size(); ++j)
            {
                taskNeeds[taskGraph[i].children[j]] += 1;
            }
        }
        //*
        //here choose tasks that can be done now:
        double globalTime = 0;
        std::vector<int> possibleTasks;
        do
        {
            possibleTasks.clear();
            for (int i = 0; i < size; ++i)
            {
                if (taskNeeds[i] == 0 && taskTaken[i] == false)
                {
                    possibleTasks.push_back(i);
                }
            }

            if (possibleTasks.size() == 1) //only one, so only one can be done
            {
                int hab = FindHabitatForTask(possibleTasks[0]);

                if (!habitats[hab].isWorking)
                {
                    try
                    {
                        StartWorking(&(habitats[hab]), possibleTasks[0]);
                    } catch (std::string message)
                    {
                        std::cout << message << std::endl;
                        return -1;
                    }
                }
            }
            else if (possibleTasks.size() > 1)
            {
                //NO CHOOSING LONGEST TASK FOR NOW!!!!!
                std::vector<int> habs = FindHabitatForTask(possibleTasks);

                bool tried = false;
                //for now not choosing longest route
                //if 2 or more tasks by same hab he just chooses first from left
                for (int i = 0; i < possibleTasks.size(); ++i)
                {
                    if (!habitats[habs[i]].isWorking)
                    {
                        try
                        {
                            StartWorking(&(habitats[habs[i]]), possibleTasks[i]);
                            tried = true;
                        } catch (std::string message)
                        {
                            std::cout << message << std::endl;
                            return -1;
                        }
                    }
                }

            }

            if (workingHabitats.size() > 0)
            {
                globalTime += PassGlobalTime();
            }

        } while (possibleTasks.size() > 0); //no tasks, so we are done

        return globalTime;
    }

private:
    void StartWorking(Habitat* hab, int possibleTask, bool debug)
    {
        std::cout << "current task ";
        std::cout << possibleTask << std::endl;
        //start working
        taskTaken[possibleTask] = true;
        hab->isWorking = true;
        hab->taskInWork = possibleTask;

        //first work is doing task, rest is doing communication
        hab->workTimeLeft.clear();
        hab->comInWork.clear();
        hab->workTimeLeft.push_back(BaseData.HabitatTaskTime(hab->GetType(), possibleTask, true));
        hab->comInWork.push_back(-1);
        for (int i = 0; i < taskGraph[possibleTask].children.size(); ++i)
        {
            try
            {
                hab->workTimeLeft.push_back(taskGraph[possibleTask].dataToTransfer[i] * GetComTime((*hab), habitats[FindHabitatForTask(possibleTask)]));
            }
            catch (std::string message)
            {
                throw message;
            }
            hab->comInWork.push_back(taskGraph[possibleTask].children[i]);
        }
        std::cout << "com in works ";
        for (int i = 0; i < hab->comInWork.size(); ++i)
        {
            std::cout << hab->comInWork[i] << " ";
        }
        std::cout << std::endl;

        /*
        for (int i = 0; i < hab->comInWork.size(); ++i)
        {
            std::cout << hab->workTimeLeft[i] << " ";
        }
        std::cout << std::endl;
        */

        workingHabitats.push_back(hab);
        //std::cout << hab->workTimeLeft[0] << std::endl;
    }

    double PassGlobalTime(bool debug)
    {
        //std::cout << workingHabitats.size() << std::endl;
        //find quickest habitat
        double minHabTime = workingHabitats[0]->workTimeLeft[0];
        Habitat* quickestHab = workingHabitats[0];
        int quickestHabId = 0;
        int quickestJob = 0;
        for (int i = 0; i < workingHabitats.size(); ++i)
        {
            if (workingHabitats[i]->comInWork[0] < 0) //still doing task
            {
                if (minHabTime > workingHabitats[i]->workTimeLeft[0])
                {
                    minHabTime = workingHabitats[i]->workTimeLeft[0];
                    quickestHabId = i;
                    quickestHab = workingHabitats[i];
                    //quickestJob = 0;
                }
            }
            else
            {
                for (int j = 1; j < workingHabitats[i]->workTimeLeft.size(); ++j)
                {
                    if (minHabTime > workingHabitats[i]->workTimeLeft[j])
                    {
                        minHabTime = workingHabitats[i]->workTimeLeft[j];
                        quickestHabId = i;
                        quickestHab = workingHabitats[i];
                        quickestJob = j;
                    }
                }
            }
        }
        //pass time
        for (int i = 1; i < workingHabitats.size(); ++i)
        {
            for (int j = 0; j < workingHabitats[i]->workTimeLeft.size(); ++j)
            {
                workingHabitats[i]->workTimeLeft[j] -= minHabTime;
            }
        }

        //only stop working if communication ends, ending task does not ends work
       
        //still doing work
        if (quickestHab->comInWork[0] < 0) //ending task directly
        {
            std::cout << "ending task " << quickestHab->taskInWork << " itself" << std::endl;
        }
        else //ending communication
        {
            std::cout << "ending com with ";
            std::cout << "task " << quickestHab->comInWork[quickestJob] << std::endl;
            taskNeeds[quickestHab->comInWork[quickestJob]] -= 1;
        }
        quickestHab->workTimeLeft.erase(quickestHab->workTimeLeft.begin() + quickestJob);
        quickestHab->comInWork.erase(quickestHab->comInWork.begin() + quickestJob);

        if (quickestHab->workTimeLeft.size() <= 0) //stop working
        {
            quickestHab->isWorking = false;
            quickestHab->taskInWork = -1;
            workingHabitats.erase(workingHabitats.begin() + quickestHabId);
        }

        return minHabTime;
    }

    //NO DEBUG
    //--------------------------
    void StartWorking(Habitat* hab, int possibleTask)
    {
        //start working
        taskTaken[possibleTask] = true;
        hab->isWorking = true;
        hab->taskInWork = possibleTask;
        //std::cout << BaseData.HabitatTaskTime(hab->GetType(), possibleTask, true) << std::endl;

        //first work is doing task, rest is doing communication
        hab->workTimeLeft.clear();
        hab->comInWork.clear();
        hab->workTimeLeft.push_back(BaseData.HabitatTaskTime(hab->GetType(), possibleTask, true));
        hab->comInWork.push_back(-1);
        for (int i = 0; i < taskGraph[possibleTask].children.size(); ++i)
        {
            try
            {
                hab->workTimeLeft.push_back(taskGraph[possibleTask].dataToTransfer[i] * GetComTime((*hab), habitats[FindHabitatForTask(possibleTask)]));
            } catch (std::string message)
            {
                throw message;
            }
            hab->comInWork.push_back(taskGraph[possibleTask].children[i]);
        }
        workingHabitats.push_back(hab);
    }

    double PassGlobalTime()
    {
        //std::cout << workingHabitats.size() << std::endl;
        //find quickest habitat
        double minHabTime = workingHabitats[0]->workTimeLeft[0];
        Habitat* quickestHab = workingHabitats[0];
        int quickestHabId = 0;
        int quickestJob = 0;
        for (int i = 0; i < workingHabitats.size(); ++i)
        {
            if (workingHabitats[i]->comInWork[0] < 0) //still doing task
            {
                if (minHabTime > workingHabitats[i]->workTimeLeft[0])
                {
                    minHabTime = workingHabitats[i]->workTimeLeft[0];
                    quickestHabId = i;
                    quickestHab = workingHabitats[i];
                    //quickestJob = 0;
                }
            }
            else
            {
                for (int j = 1; j < workingHabitats[i]->workTimeLeft.size(); ++j)
                {
                    if (minHabTime > workingHabitats[i]->workTimeLeft[j])
                    {
                        minHabTime = workingHabitats[i]->workTimeLeft[j];
                        quickestHabId = i;
                        quickestHab = workingHabitats[i];
                        quickestJob = j;
                    }
                }
            }
        }
        //pass time
        for (int i = 1; i < workingHabitats.size(); ++i)
        {
            for (int j = 0; j < workingHabitats[i]->workTimeLeft.size(); ++j)
            {
                workingHabitats[i]->workTimeLeft[j] -= minHabTime;
            }
        }

        //only stop working if communication ends, ending task does not ends work

        //still doing work
        if (quickestHab->comInWork[0] < 0) //ending task directly
        {

        }
        else //ending communication
        {
            taskNeeds[quickestHab->comInWork[quickestJob]] -= 1;
        }
        quickestHab->workTimeLeft.erase(quickestHab->workTimeLeft.begin() + quickestJob);
        quickestHab->comInWork.erase(quickestHab->comInWork.begin() + quickestJob);

        if (quickestHab->workTimeLeft.size() <= 0) //stop working
        {
            quickestHab->isWorking = false;
            quickestHab->taskInWork = -1;
            workingHabitats.erase(workingHabitats.begin() + quickestHabId);
        }

        return minHabTime;
    }

    //unimplemented for now
    double GetComTime(Habitat& hab1, Habitat& hab2)
    {
        //
        return 1;

        double res = BaseData.MaxChannelSpeed();
        if (hab1 == hab2)
        {
            return 0;
        }
        for (int i = 0; i < hab1.comChannels.size(); ++i)
        {
            for (int j = 0; j < hab2.comChannels.size(); ++j)
            {
                if (hab1.comChannels[i] == hab2.comChannels[j])
                {
                    if (res > BaseData.ChannelSpeed(hab1.comChannels[i]))
                    {
                        res = BaseData.ChannelSpeed(hab1.comChannels[i]);
                    }
                }
            }
        }
        if (res >= BaseData.MaxChannelSpeed())
        {
            throw "habitats cannot communicate!";
        }
        return res;

    }

    //NOTE
    //There is LTERALLY no way 2 habitats will commit
    //to do same task, so I don't need to check for that
    int FindHabitatForTask(int task)
    {
        for (int i = 0; i < habitats.size(); ++i)
        {
            for (int j = 0; j < habitats[i].takenTasks.size(); ++j)
            {
                if (habitats[i].takenTasks[j] == taskGraph[task].GetType())
                {
                    return i;
                }
            }
        }
    }

    std::vector<int> FindHabitatForTask(std::vector<int>& tasks)
    {
        std::vector<int> res;
        for (int i = 0; i < habitats.size(); ++i)
        {
            for (int j = 0; j < habitats[i].takenTasks.size(); ++j)
            {
                for (int k = 0; k < tasks.size(); ++k)
                {
                    if (habitats[i].takenTasks[j] == taskGraph[tasks[k]].GetType())
                    {
                        res.push_back(i);
                    }
                }
            }
        }
        return res;
    }

};
