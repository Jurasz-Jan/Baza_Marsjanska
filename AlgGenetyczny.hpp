#pragma once
#include <stdexcept>
#include <iostream>
#include "Base.hpp"

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



class BaseManager
{
	//HabitatDatabase* database;

	std::vector<Habitat> habitats;
	std::vector<Individual> population;
	
	
	
	
class Individual
{
public:
    std::vector<int> chromosome;
    double fitness;

    Individual(std::vector<int> chromosome) : chromosome(chromosome), fitness(0.0) {}
};
	



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

/*
	void AddIndividual(std::vector<std::vector<Channel>> newIndividual)
	{
		population.push_back(newIndividual);

	}

*/

 std::vector<Individual> initializePopulation()
    {
        std::vector<Individual> population;
        for (int i = 0; i < POPULATION_SIZE; ++i)
        {
            std::vector<int> chromosome;
            //chromosome is a combination of numbers. How can it work?
            population.emplace_back(chromosome);
        }
        return population;
    }

    
    void mutate(Individual &individual)
    {
        for (int i = 0; i < individual.chromosome.size(); ++i)
        {
            if (std::generate_canonical<double, 10>(gen) < MUTATION_RATE)
            {
                // Perform mutation operation on the chromosome
                // Add code here to modify the chromosome based on your mutation strategy
            }
        }
    }

    
    Individual crossover(const Individual &parent1, const Individual &parent2)
    {
        std::vector<int> offspringChromosome;
        //add crossover
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
	
	
   std::pair<Individual, Individual> selectParents(const std::vector<Individual> &population)
    {
        std::uniform_int_distribution<> dis(0, POPULATION_SIZE - 1);
        Individual parent1 = population[dis(gen)];
        Individual parent2 = population[dis(gen)];
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

            newPopulation.emplace_back(offspring);
        }

        return newPopulation;
    }

	
	
	void runGeneticAlgorithm()
    {

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

        
    }
};


private:
	double TryDoTask(int taskType)
	{

	}
};
