#pragma once
#include <stdexcept>
#include <iostream>
#include "Base.hpp"

//"manager" is kind of class
//that well manages some sort of objects
//and that's it
//every "base" in abstract thinking
//schould have exacly ONE manager
class BaseManager
{
	//HabitatDatabase* database;

	std::vector<Habitat> habitats;
	//std::vector<Channel> channels; //The individual is a combination of channels- a vector of channels. Like this one on the left.
	std::vector<std::vector<Channel>> population;



public:
	Habitat GetHabitat(int Id)
	{
		if (Id > habitats.size())
		{
			throw std::out_of_range("index " + std::to_string(Id) + "is out of range");
		}
		return habitats[Id];
	}

	Channel GetChannel(int Id)
	{
		if (Id >= channels.size())
		{
			throw std::out_of_range("index " + std::to_string(Id) + "is out of range");
		}
		return channels[Id];
	}

	void AddHabitat(Habitat newHabitat)
	{
		habitats.push_back(newHabitat);
	}

	void AddChannel(Channel newChannel)
	{
		channels.push_back(newChannel);
	}


	void AddIndividual(std::vector<std::vector<Channel>> newIndividual)
	{
		population.push_back(newIndividual);

	}


	

	//Time and cost calculation (else algorithm quality check)
	//-------------------------------------------------------
	
	//returns time required to made such task
	//throws exception if cannot made such task




	
void InitializePopulation(int populationSize,int par1=1,int par2=1)
{
    // Clear the existing population
    channels.clear();

    // Generate random individuals
    for (int i = 0; i < populationSize; i++)
    {
        std::vector<Channel> newIndividual;

        // Generate random channels
        for (int j = 0; j < habitats.size(); j++)
        {
            Channel newChannel;

            // Generate random connections for the channel
            // ...

            newIndividual.push_back(newChannel);
        }

        channels.push_back(newIndividual);
    }
}

    
    void Mutate(Channel& individual, double mutationRate);

    
    Channel Crossover(const Channel& parent1, const Channel& parent2);

    
    std::vector<Channel> Selection(int numParents);

    // Evolves the population for a certain number of generations
    void Evolve(int numGenerations, int populationSize, double mutationRate);





private:
	double TryDoTask(int taskType)
	{

	}
};