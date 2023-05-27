

void mutacja(std::vector<Rozwiazanie>& populacja, double prawdopodobienstwoMutacji) {
   
    
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
		std::cerr << "Error: Wrong number of habitats. Don't blame me, this just doesn't make sense mathematically." << std::endl;
		std:cerr << " (N-1)! must be greater than or equal to A*Z, where A is inputted from keyboard, and Z is number of tasks"<<std:endl;
        return 1; // Return a non-zero value to indicate an error
	}
	
	
}