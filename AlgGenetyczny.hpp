

void mutate(std::vector<Individual>& population, double probability) {
   
    
}



double getRandomDouble(double min, double max) {
    return min + static_cast<double>(rand()) / RAND_MAX * (max - min);
}



class Individual {
private:
    std::vector<ChannelConnection> channelConnections; // Essentially the genotype

public:
    // constructor
    Individual(std::vector<ChannelConnection> connections) : channelConnections(std::move(connections)) {}

    // adding channel connections
    void addChannelConnection(ChannelConnection connection) {
        channelConnections.push_back(connection);
    }

    // method for returning channel connections
    std::vector<ChannelConnection> getChannelConnections() const {
        return channelConnections;
    }
	
	
	//method to rate each individual
	void fitness_value(
	//returns time of finding the task
	);
	
};


unsigned int factorial(unsigned int n) {
    unsigned int result = 1;
    for (unsigned int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}



std::vector<ChannelConnection> generateRandomConnections(int numberOfConnections,int n) {
    std::vector<ChannelConnection> connections;

    // generate random connections
    for (int i = 0; i < numberOfConnections; ++i) {
        int sourceHabitatId = /*generate randomly from 0 to n */;
        int destinationHabitatId = /* cannot be sourceHabitatID */;
        double cost = /* generate random cost */;
        double bandwidth = /* Generate random bandwidth */;

        ChannelConnection connection(sourceHabitatId, destinationHabitatId, cost, bandwidth);
        connections.push_back(connection);
    }

    return connections;
}




std::vector<Individual> createInitialPopulation(int populationSize, int numberOfConnections) {
    std::vector<Individual> population;

    // generate random individuals
    for (int i = 0; i < populationSize; ++i) {
        std::vector<ChannelConnection> connections = generateRandomConnections(numberOfConnections);
        Individual individual(connections);
        population.push_back(individual);
    }

    return population;
}



// n- number of habitats, 
// z-number of resources
// a-inputted parameter
//initial population size= anz
//anz<= n!/2

class BaseManager(int n, int z)    
{
	std::vector<Habitat> habitats;
	
	
	
	
	
	
	
	if (a*n*z > (factorial(n))/2) 
	{
		//std::cerr << "Error: Wrong number of habitats. Don't blame me, this just doesn't make sense mathematically." << std::endl;
		//std:cerr << " (N-1)! must be greater than or equal to A*Z, where A is inputted from keyboard, and Z is number of tasks"<<std:endl;
        //return 1; // Return a non-zero value to indicate an error
		print("We need more habitats");
		//Population must be of size ANB. I suggest we should keep building until it will be possible to create ANB unique combinations
				
		
	}
	
	
	
	
	
	
	
	
	
	
	
}