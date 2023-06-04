#pragma once
#include <stdexcept>
#include <iostream>
#include "Base.hpp"
#include <random>


//"manager" is kind of class
//that well manages some sort of objects
//and that's it
//every "base" in abstract thinking
//schould have exacly ONE manager





// RNG 
std::random_device rd;
std::mt19937 gen(rd());


const int POPULATION_SIZE = 50;
const int MAX_GENERATIONS = 100;
const double MUTATION_RATE = 0.1;
const double CROSSOVER_RATE = 0.8;
const int MAX_CHROMOSOME_SIZE = 10; //also 



class BaseManager
{ 
	//HabitatDatabase* database;

	std::vector<Habitat> habitats;
	
	std::vector<std::pair<int, int>> chromosome;
    std::vector<Channel> channels;

	
	
class Individual
{
public:
    std::vector<int> chromosome;
    double fitness;

    Individual(std::vector<int> chromosome) : chromosome(chromosome), fitness(0.0) {}
};
	

std::vector<Individual> population;

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
		if (Id >= habitats.size())
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

/*
	void AddIndividual(std::vector<std::vector<Channel>> newIndividual)
	{
		population.push_back(newIndividual);

	}

*/
//LETS SUPPOSE TERE EXISTS #DEFINE NUM_HABITATS
int NUM_HABITATS=10;

std::vector<Individual> initializePopulation(int size_of_population)
{
    std::vector<Individual> population;

    // Generowanie populacji
    for (int i = 0; i < size_of_population; ++i)
    {
        std::vector<std::pair<int, int>> connections;
        std::vector<std::pair<int, int>> existingConnections;

        // Generowanie losowych połączeń dla chromosomu
        while (connections.size() < MAX_CHROMOSOME_SIZE)
        {
            std::uniform_int_distribution<int> dist(1, NUM_HABITATS); // Numery habitacji od 1 do NUM_HABITATS

            int habitatA = dist(gen);
            int habitatB = dist(gen);

            
            bool isValidConnection = true;

            
            if (habitatA == habitatB)
            {
                isValidConnection = false;
            }

            
            if (std::find(existingConnections.begin(), existingConnections.end(), std::make_pair(habitatA, habitatB)) != existingConnections.end() ||
                std::find(existingConnections.begin(), existingConnections.end(), std::make_pair(habitatB, habitatA)) != existingConnections.end())
            {
                isValidConnection = false;
            }

            
            if (std::find(existingConnections.begin(), existingConnections.end(), std::make_pair(habitatB, habitatA)) != existingConnections.end())
            {
                isValidConnection = false;
            }

            
            if (isValidConnection)
            {
                connections.emplace_back(habitatA, habitatB);
                existingConnections.push_back(std::make_pair(habitatA, habitatB));
            }
        }

        population.emplace_back(connections);
    }

    return population;
}




    
    void mutate(Individual &individual)
    {
        for (int i = 0; i < individual.chromosome.size(); ++i)
        {
            if (std::generate_canonical<double, 10>(gen) < MUTATION_RATE)
            {
                
            }
        }
    }

    
    Individual crossover(const Individual &parent1, const Individual &parent2)
{
    std::vector<int> offspringChromosome;

   
    
    std::uniform_int_distribution<int> dist(0, parent1.chromosome.size() - 1);
    int crossoverPoint = dist(gen);

   
    for (int i = 0; i < parent1.chromosome.size(); ++i)
    {
        if (i < crossoverPoint)
        {
            offspringChromosome.push_back(parent1.chromosome[i]);
        }
        else
        {
            offspringChromosome.push_back(parent2.chromosome[i]);
        }
    }

    return Individual(offspringChromosome);
}



    
    
    void calculateFitness(Individual &individual)
    {
       //function calculating time of doing the task
	//Time and cost calculation (else algorithm quality check)
	//returns time required to made such task
	//throws exception if cannot made such task	    
	       	    
    }


	
     void evaluatePopulation(std::vector<Individual> &population)
    {
        for (auto &individual : population)
        {
            calculateFitness(individual);
        }
    }
	
	
std::pair<Individual, Individual> selectParents(std::vector<Individual>& population)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    int tournamentSize = 5;

    // Select participants for the first tournament
    std::vector<Individual> participants;
    for (int i = 0; i < tournamentSize; ++i)
    {
        std::uniform_int_distribution<int> dist(0, population.size() - 1);
        int index = dist(gen);
        participants.push_back(population[index]);
    }

    // Find the individual with the highest fitness in the tournament
    Individual parent1 = *std::max_element(participants.begin(), participants.end(),
        [](const Individual& ind1, const Individual& ind2)
        {
            return ind1.fitness < ind2.fitness;
        });

    // Remove the selected parent from the population
    auto parent1It = std::find(population.begin(), population.end(), parent1);
    population.erase(parent1It);

    // Select participants for the second tournament from the updated population
    participants.clear();
    for (int i = 0; i < tournamentSize; ++i)
    {
        std::uniform_int_distribution<int> dist(0, population.size() - 1);
        int index = dist(gen);
        participants.push_back(population[index]);
    }

    // Find the individual with the highest fitness in the second tournament
    Individual parent2 = *std::max_element(participants.begin(), participants.end(),
        [](const Individual& ind1, const Individual& ind2)
        {
            return ind1.fitness < ind2.fitness;
        });

    // Remove the selected parent from the population
    auto parent2It = std::find(population.begin(), population.end(), parent2);
    population.erase(parent2It);

    return std::make_pair(parent1, parent2);
}
	
   std::vector<Individual> generateNewPopulation(const std::vector<Individual> &population)
    {
        std::vector<Individual> newPopulation;
        // Elitism-keeping best individual 
	   
        while (newPopulation.size() < POPULATION_SIZE)
        {

            std::pair<Individual, Individual> parents = selectParents(population);
            Individual offspring = crossover(parents.first, parents.second);
            mutate(offspring);

            newPopulation.push_back(offspring);
        }

        return newPopulation;
    }

	
	Individual runGeneticAlgorithm()
{
    BaseManager baseManager;

    std::vector<Individual> population = initializePopulation();
    evaluatePopulation(population);
    int generation = 0;
    while (generation < MAX_GENERATIONS)
    {
        std::vector<Individual> newPopulation = generateNewPopulation(population);
        evaluatePopulation(newPopulation);
        // Replacing the population
        population = newPopulation;

        ++generation;
    }

    // Selecting fittest one
    Individual bestIndividual = population[0];
    for (const auto &individual : population)
    {
        if (individual.fitness > bestIndividual.fitness)
        {
            bestIndividual = individual;
        }
    }
    
    return bestIndividual;
}


private:
	double TryDoTask(int taskType)
	{

	}
}





