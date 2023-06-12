#include <iostream>
#include "FileLoader.hpp"
#include "BaseManager.hpp"
#include "Task.hpp"
#include "Randomizer.hpp"
#include "Genetic.hpp"

//collection of static workings on a task file
//is in main due to it being actually part of main
//but compilation process requires static functions
class FileInterpreter
{
public:
	friend int main(); //only main can access this class
private:
	static void PrintFile(std::vector<std::string>* data)
	{
		for (int i = 0; i < data->size(); ++i)
		{
			std::cout << (*data)[i] << " ";
		}
		std::cout << std::endl;
	}

	static void ConstructTaskGraph(std::vector<std::string>* data)
	{
		//now only cout for testing
		//taskGraph.taskList.push_back(TreeNode<Task>(((*data)[0])));
		try
		{
			TaskType.GetId((*data)[0]);
		}
		catch (const std::out_of_range& message)
		{
			//add only if new type encountered
			TaskType.label.push_back((*data)[0]);
		}
		//Task aaa((*data)[0], taskGraph.size());
		taskGraph.taskList.push_back(Task((*data)[0], taskGraph.size()));
		unsigned int last = taskGraph.size() - 1;
		for (int i = 1; i < data->size(); i += 2)
		{
			taskGraph[last].children.push_back(std::stoi((*data)[i]));
			taskGraph[last].dataToTransfer.push_back(std::stod((*data)[i + 1]));
		}
	}

	static void LoadHabitatTypes(std::vector<std::string>* data)
	{
		HabitatType.label.push_back((*data)[0]);
		BaseData.habitatBuildCost.push_back(std::stod((*data)[1]));
		//possible task types by habitat
		unsigned int last = BaseData.habitatBuildCost.size() - 1;
		BaseData.habitatTasks.push_back(std::vector<int>());
		for (int i = 2; i < data->size(); ++i)
		{
			BaseData.habitatTasks[last].push_back(TaskType.GetId((*data)[i]));
		}
	}

	static void LoadHabitatTasksTime(std::vector<std::string>* data)
	{
		for (int i = BaseData.habitatTaskTimes.size(); i < data->size(); ++i)
		{
			BaseData.habitatTaskTimes.push_back(std::vector<double>());
		}
		for (int i = 0; i < data->size(); ++i)
		{
			/*
			bool allowed = true;
			for (int j = 0; j < BaseData.habitatTasks[i].size(); ++j)
			{
				if (BaseData.habitatTasks[i][j] == taskGraph[i].GetType())
				{
					BaseData.habitatTaskTimes[i].push_back(0);
					allowed = false;
					break;
				}
			}
			if (allowed)
			{
				BaseData.habitatTaskTimes[i].push_back(std::stod((*data)[i]));
			}
			*/
			BaseData.habitatTaskTimes[i].push_back(std::stod((*data)[i]));
		}
	}

	static void LoadHabitatTasksCost(std::vector<std::string>* data)
	{
		for (int i = BaseData.habitatTaskCosts.size(); i < data->size(); ++i)
		{
			BaseData.habitatTaskCosts.push_back(std::vector<double>());
		}
		for (int i = 0; i < data->size(); ++i)
		{
			BaseData.habitatTaskCosts[i].push_back(std::stod((*data)[i]));
		}
	}

	static void LoadChannels(std::vector<std::string>* data)
	{
		ChannelType.label.push_back((*data)[0]);
		BaseData.channelBuildCost.push_back(std::stod((*data)[1]));
		BaseData.channelComCost.push_back(std::stod((*data)[2]));
		BaseData.channelSpeed.push_back(std::stod((*data)[2]));
	}
};



int main()
{
	//START
	//------------------------------------------
	GeneticAlgorithm mainBase;
	//here setup for database and enums

	//LOAD FILE
	//------------------------------------------
	typedef void(*fileFunction)(std::vector<std::string>*);
	fileFunction fileFunctions[6] = { FileInterpreter::PrintFile, FileInterpreter::ConstructTaskGraph, FileInterpreter::LoadHabitatTypes, FileInterpreter::LoadHabitatTasksTime, FileInterpreter::LoadHabitatTasksCost, FileInterpreter::LoadChannels};
	
	std::cout << "give name of file with settings: ";
	std::string name;
	std::cin >> name;
	TaskFileLoader fileLoader;
	//fileLoader.ReadFile(name, fileFunctions, 6);

	//FOR TESTING!!!!!!!!!
	fileLoader.ReadFile("SingleTest.txt", fileFunctions, 6);
	//fileLoader.ReadFile("MultiHabTest.txt", fileFunctions, 6);

	//here check if data is good:
	/*
	for (int i = 0; i < BaseData.channelBuildCost.size(); ++i)
	{
		std::cout << BaseData.channelBuildCost[i] << std::endl;
	}
	*/

	std::cout << "data check (time): " << std::endl;
	for (int i = 0; i < BaseData.habitatTaskTimes.size(); ++i)
	{
		for (int j = 0; j < BaseData.habitatTaskTimes[i].size(); ++j)
		{
			std::cout << BaseData.habitatTaskTimes[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "data check (cost): " << std::endl;
	for (int i = 0; i < BaseData.habitatTaskCosts.size(); ++i)
	{
		for (int j = 0; j < BaseData.habitatTaskCosts[i].size(); ++j)
		{
			std::cout << BaseData.habitatTaskCosts[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "taskGraph check: " << std::endl;
	for (int i = 0; i < taskGraph.size(); ++i)
	{
		std::cout << i << ": ";
		for (int j = 0; j < taskGraph[i].children.size(); ++j)
		{
			std::cout << taskGraph[i].children[j] << " ";
		}
		std::cout << std::endl;
	}

	//defines for later use
	//---------------------------------------------
	//define max channelSpeed
	double maxSpeed = 0;
	for (int i = 0; i < BaseData.channelSpeed.size(); ++i)
	{
		if (BaseData.channelSpeed[i] > maxSpeed)
		{
			maxSpeed = BaseData.channelSpeed[i];
		}
	}
	BaseData.maxChannelSpeed = maxSpeed;
	//PreperationsForHabitatAdding
	//-------------------------------------------------
	if (HabitatType.GetSize() <= 0)
	{
		std::cout << "error! base needs at least one habitat to work!" << std::endl;
		return 1;
	}
	//general purpose
	std::vector<int> startHabType;
	int cheapestHab = 0;
	double minHabCost = BaseData.habitatBuildCost[0];
	for (int i = 0; i < BaseData.habitatTasks.size(); ++i)
	{
		//no specyfic tasks, so it is general purpose
		if (BaseData.habitatTasks[i].size() <= 0)
		{
			startHabType.push_back(i);
			if (minHabCost < BaseData.habitatBuildCost[i])
			{
				minHabCost = BaseData.habitatBuildCost[i];
				cheapestHab = i;
			}
		}
	}
	if (startHabType.size() <= 0)
	{
		std::cout << "error! base needs at least one habitat of general purpose" << std::endl;
		return 1;
	}
	//min time and cost
	double minTaskTime = 0;
	double minTaskBoth = 0;
	int minTaskTimeHab = 0;
	int minTaskBothHab = 0;
	for (int j = 0; j < BaseData.habitatTaskTimes[0].size(); ++j)
	{
		minTaskTime += BaseData.habitatTaskTimes[0][j];
		minTaskBoth += BaseData.habitatTaskCosts[0][j];
	}
	minTaskBoth = minTaskBoth * minTaskTime;
	for (int i = 0; i < BaseData.habitatTaskTimes.size(); ++i)
	{
		double curTaskTime = 0;
		double curTaskCost = 0;
		for (int j = 0; j < BaseData.habitatTaskTimes[i].size(); ++j)
		{
			curTaskTime += BaseData.habitatTaskTimes[i][j];
			curTaskCost += BaseData.habitatTaskCosts[i][j];
		}
		if (minTaskTime > curTaskTime)
		{
			minTaskTime = curTaskTime;
			minTaskTimeHab = i;
		}
		if (minTaskBoth > curTaskCost * curTaskTime)
		{
			minTaskBoth = curTaskCost * curTaskTime;
			minTaskBothHab = i;
		}
	}

	//BASE CONSTRUCTION
	//------------------------------------------
	//for future: schould choose by random
	//first habitat
	mainBase.AddHabitat(Habitat(startHabType[0]));
	for (int i = 0; i < taskGraph.taskList.size(); ++i)
	{
		mainBase.habitats[0].takenTasks.push_back(i);
	}
	 
	//rest habs
	std::cout << "give number of habitats" << std::endl;
	int habNum = 1;
	std::cin >> habNum;
	//LEGEND:
	//chapest general 0.1
	//quickest 0.1 (how?, it depends by tasks)
	//least time and cost of possible tasks 0.4 (is by possible, not taken)
	//same as last time 0.2
	//least added 0.2
	std::vector<int> addingAmount;
	int lastChoosenHab = 0; //schould be starting
	addingAmount.resize(BaseData.habitatBuildCost.size(), 0);
	for (int i = 1; i < habNum; ++i)
	{
		int rand = RandomGenerator.RandomIntRange(1, 10);
		std::cout << "random int: " << rand << std::endl;
		
		int choosenHab = 0;
		if (rand <= 1)
		{
			choosenHab = cheapestHab;
		}
		else if (rand <= 2)
		{
			choosenHab = minTaskTimeHab;
		}
		else if (rand <= 6)
		{
			choosenHab = minTaskBothHab;
		}
		else if (rand <= 8)
		{
			choosenHab = lastChoosenHab;
		}
		else
		{
			int leastHab = 0;
			int minChoice = addingAmount[0];
			for (int i = 0; i < addingAmount.size(); ++i)
			{
				if (minChoice > addingAmount[i])
				{
					minChoice = addingAmount[i];
					leastHab = i;
				}
			}
			choosenHab = leastHab;
		}
		std::cout << "added hab of type" << choosenHab << std::endl;
		//here add habitat
		mainBase.AddHabitat(Habitat(choosenHab));
		mainBase.habitats[mainBase.habitats.size() - 1].taskPercentage = RandomGenerator.RandomDoublePercent();
		addingAmount[choosenHab] += 1;
		lastChoosenHab = choosenHab;
	}

	//std::cout << "check end" << std::endl;
	//return 0;

	//test check if doing task graph works:
	//double tasksTime = mainBase.CalculateGlobalTime();
	//std::cout << "base time completion: " << tasksTime << std::endl;
	//std::cout << "base total cost: " << mainBase.CalculateGlobalCost() << std::endl;


	//MAIN LOOP
	//-------------------------------------------
	std::cout << "gen" << std::endl;
	mainBase.RedistributeTasks();
	for (int i = 0;i < mainBase.habitats.size(); ++i)
	{
		std::cout << "percent " << mainBase.habitats[i].taskPercentage << " ";
		for (int j = 0; j < mainBase.habitats[i].takenTasks.size(); ++j)
		{
			std::cout << mainBase.habitats[i].takenTasks[j] << " ";
		}
	}
	std::cout << std::endl;
	return 0;
	while (true)
	{
		//here goes genetic algorithm

		//-----------------------------------
		//quality check
		mainBase.Crossover();
		mainBase.MutateHabitat();
		mainBase.MutateParents();
		//*
		for (int i = 0; mainBase.habitats.size(); ++i)
		{
			std::cout << mainBase.habitats[i].taskPercentage << std::endl;
		}
		//*/
	}
}
