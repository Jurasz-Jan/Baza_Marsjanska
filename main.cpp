#include <iostream>
#include "FileLoader.hpp"
#include "AlgGenetyczny.hpp"
#include "Tree.hpp"


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
	}

	static void LoadHabitatTypes(std::vector<std::string>* data)
	{
		HabitatType.label.push_back((*data)[0]);
		 (*data)[1];
		 BaseData.habitatBuildCost.push_back(std::stod((*data)[1]));
	}

	static void LoadHabitatTasksTime(std::vector<std::string>* data)
	{
		BaseData.habitatTaskTimes.push_back(std::vector<double>());
		int last = BaseData.habitatTaskTimes.size() - 1;
		for (int i = 0; i < data->size(); ++i)
		{
			BaseData.habitatTaskTimes[last].push_back(std::stod((*data)[i]));
		}
	}

	static void LoadHabitatTasksCost(std::vector<std::string>* data)
	{
		BaseData.habitatTaskCosts.push_back(std::vector<double>());
		int last = BaseData.habitatTaskCosts.size() - 1;
		for (int i = 0; i < data->size(); ++i)
		{
			BaseData.habitatTaskCosts[last].push_back(std::stod((*data)[i]));
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
	BaseManager mainBase;
	//here setup for database and enums

	//LOAD FILE
	//------------------------------------------
	typedef void(*fileFunction)(std::vector<std::string>*);
	fileFunction fileFunctions[6] = { FileInterpreter::PrintFile, FileInterpreter::ConstructTaskGraph, FileInterpreter::LoadHabitatTypes, FileInterpreter::LoadHabitatTasksTime, FileInterpreter::LoadHabitatTasksCost, FileInterpreter::LoadChannels};
	
	std::cout << "give name of file with settings: ";
	std::string name;
	std::cin >> name;
	TaskFileLoader fileLoader;
	fileLoader.ReadFile(name, fileFunctions, 6);

	//here check if data is good:
	for (int i = 0; i < BaseData.channelBuildCost.size(); ++i)
	{
		std::cout << BaseData.channelBuildCost[i] << std::endl;
	}

	//------------------------------------------
	
	//base building aka start of program

	//add habitats to base


	//MAIN LOOP
	//-------------------------------------------
	/*
	while (true)
	{
		//here goes genetic algorithm

		//-----------------------------------
		//quality check
	}
	*/
}
