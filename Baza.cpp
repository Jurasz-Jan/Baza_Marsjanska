//plik "główny"-ofc, to tylko propozycja struktury. ~Janek
//proponuję jakieś ramy struktur w komentarzu,ale to tylko propozycja.


/*

class/struct Habitat
{
    int HabitatID

}


//Each Habitat should have its ID

struct ChannelConnection {
    int fromHabitatId;
    int toHabitatId;
    Int cost;
   
};




*/


/* What is an individual?
An individual is a specific connection of communication channels between specific base modules, habitats.
An individual has one important component: std::vector<ChannelConnection> channelConnections, which essentially represents the individual 
The rest of an individual is only some not important functions to help to operate on him.
We are able to calculate, based on that, the execution time of tasks by the individual.
*/