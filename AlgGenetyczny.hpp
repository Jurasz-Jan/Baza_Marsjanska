#pragma once
#include <stdexcept>
#include <iostream>
#include "Base.hpp"
#include <random>
#include "Tree.hpp"
#include "WeightedGraph.hpp" 
#include <string>

//"manager" is kind of class
//that well manages some sort of objects
//and that's it
//every "base" in abstract thinking
//schould have exacly ONE manager

//graph
WeightedGraph<std::string, int> taskGraph;
taskGraph.addEdge("Task A", "Task B", 2);
taskGraph.addEdge("Task B", "Task C", 1);





class Individual : public Tree<int>
{
public:
    int fitness;

    Individual() : Tree(), fitness(0) {}
    ~Individual() = default;

    Individual(const Individual& other) : Tree(other), fitness(other.fitness) {}
    Individual& operator=(const Individual& other)
    {
        if (this != &other)
        {
            Tree::operator=(other);
            fitness = other.fitness;
        }
        return *this;
    }
};

 void createExampleHabitats()
    {
        for (int i = 0; i < 10; ++i)
        {
            Habitat* habitat = new Habitat(std::to_string(i));
            
            habitats.push_back(habitat);
        }
    }




std::random_device rd;
std::mt19937 gen(rd());


int NUM_HABITATS=10;
const int POPULATION_SIZE = 50;
const int MAX_GENERATIONS = 100;
const double MUTATION_RATE = 0.1;
const double CROSSOVER_RATE = 0.8;
const int MAX_CHROMOSOME_SIZE = 10; 



class BaseManager
{ 

    std::vector<Individual> population;

class Individual : public Tree<int>
{
public:
    int fitness;

    Individual() : Tree(), fitness(0) {}
    ~Individual() = default;

    Individual(const Individual& other) : Tree(other), fitness(other.fitness) {}
    Individual& operator=(const Individual& other)
    {
        if (this != &other)
        {
            Tree::operator=(other);
            fitness = other.fitness;
        }
        return *this;
    }
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



std::vector<Individual> initializePopulation(int size_of_population)
{
    std::vector<Individual> population;

    // Generowanie populacji
    for (int i = 0; i < size_of_population; ++i)
    {
        std::vector<std::pair<int, int>> connections;
        std::vector<int> availablePoints;

        // Inicjalizacja dostępnych punktów
        for (int j = 1; j <= 10; ++j)
        {
            availablePoints.push_back(j);
        }

        // Generowanie losowych połączeń dla chromosomu
        while (availablePoints.size() > 1)
        {
            std::uniform_int_distribution<int> dist(0, availablePoints.size() - 1);
            int indexA = dist(gen);
            int pointA = availablePoints[indexA];
            availablePoints.erase(availablePoints.begin() + indexA);

            int indexB = dist(gen);
            int pointB = availablePoints[indexB];
            availablePoints.erase(availablePoints.begin() + indexB);

            connections.emplace_back(pointA, pointB);
        }

        // Dodanie ostatniego punktu z dostępnych jako korzenia drzewa
        int lastPoint = availablePoints[0];
        connections.emplace_back(0, lastPoint);

        // Sprawdzenie, czy drzewo zostało poprawnie zbudowane
        std::vector<int> connectedPoints(availablePoints.begin(), availablePoints.end());
        connectedPoints.push_back(lastPoint);

        if (connectedPoints.size() == 10)
        {
            
            population.emplace_back(connections);
        }
        else
        {
            // Jeżeli drzewo nie jest poprawne, powtarzamy generowanie populacji
            i--;
        }
    }

    return population;
}






    
    void mutate(Individual &individual)
    {
        
    }

    




    */
    
    void calculateFitness(Individual &individual)
    {
       
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





