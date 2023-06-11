#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Enums.hpp"

struct ChannelConnection
{
	// Channel channel;
	int fromHabitatId;
	int toHabitatId;
};

struct Channel
{
public:
	Channel(std::vector<ChannelConnection> connections, int id) : connections(std::move(connections))
	{
		type = id;
		if (id >= HabitatType.GetSize())
		{
			type = 0;
			std::cout << "id: " << id << " is outside of enum's range" << std::endl;
		}
	}

	Channel(std::vector<ChannelConnection> connections, std::string name) : connections(std::move(connections))
	{
		try
		{
			type = ChannelType.GetId(name);
		} catch (const std::out_of_range& message)
		{
			type = 0;
			std::cout << message.what() << std::endl;
		}
	}

	// is neccesarry?
	void AddConnection(ChannelConnection newConnection) { connections.push_back(newConnection); }

	void ReplaceConnections(std::vector<ChannelConnection> newConnections) { connections = newConnections; }

	// for mutation
	void ChangeConnection(ChannelConnection newConnection, int id)
	{
		if (id >= connections.size())
		{
			throw std::out_of_range("index " + std::to_string(id) + "is out of range");
		}
	}

	unsigned int GetType()
	{
		return type;
	}

	friend bool operator==(Channel& ch1, Channel& ch2)
	{
		if (ch1.GetType() == ch2.GetType())
		{
			return true;
		}
		return false;
	}

private:
	unsigned int type;
	std::vector<ChannelConnection> connections;
};

class Habitat
{
public:
	bool tasksRedistributed = false;
	///---------------------------
	double taskPercentage;
	std::vector<int> takenTasks; //by task id
	std::vector<int> comChannels;
	//--------------------------------

	bool isWorking = false;
	int taskInWork = -1; //-1 means no task currently done
	std::vector<int> comInWork = std::vector<int>(); //-1 means no com
	std::vector<double> workTimeLeft = std::vector<double>();

	Habitat(std::string name) : taskPercentage(1), takenTasks(std::vector<int>()), comChannels(std::vector<int>())
	{
		try
		{
			type = HabitatType.GetId(name);
		}
		catch (const std::out_of_range& message)
		{
			type = 0;
			std::cout << message.what() << std::endl;
		}
	}

	Habitat(int id)
	{
		taskPercentage = 1;
		type = id;
		if (id >= HabitatType.GetSize())
		{
			type = 0;
			std::cout << "id: " << id << " is outside of enum's range" << std::endl;
		}
	}

	int GetType()
	{
		return type;
	}

	bool operator==(Habitat& hab2)
	{
		if (type == hab2.GetType())
		{
			return true;
		}
		return false;
	}

private:
	int type;
};

//"database" is kind of class that
// contains all informations about
// other kinds of object, that such object itself
// does not needs that info at every time
// oh, it is also ALWAYS a singleton
class HabitatDatabase
{
public:
	friend int main();  // YEAH, I KNOW WHAT I AM DOING --ADAM
	friend class FileInterpreter;

private:
	// per habitat type
	std::vector<double> habitatBuildCost;
	std::vector<std::vector<int>> habitatTasks;  // by tasks type
	// for task per habitat
	std::vector<std::vector<double>> habitatTaskTimes;
	std::vector<std::vector<double>> habitatTaskCosts;

	// per channel
	std::vector<double> channelBuildCost;
	std::vector<double> channelSpeed;
	std::vector<double> channelComCost;

	// per task (defaults):
	//these aren't needed here
	std::vector<double> taskTime;
	std::vector<double> taskCost;

	//defined max channelSpeed so can be used in taskGraph
	double maxChannelSpeed;

public:
	// a whole lot of getters:
	double HabitatBuildCost(int type) { return habitatBuildCost[type]; }
	// channel
	double ChannelBuildCost(int type) { return channelBuildCost[type]; }
	double ChannelSpeed(int type) { return channelSpeed[type]; }
	double ChannelComCost(int type) { return channelComCost[type]; }
	
	double MaxChannelSpeed() { return maxChannelSpeed; }
	// task
	double TaskTime(int type) { return taskTime[type]; }
	double TaskCost(int type) { return taskCost[type]; }

	// utility:
	int MapTaskType(int habType, int taskType)
	{
		for (int i = 0; i < habitatTasks.size(); ++i)
		{
			if (taskType == habitatTasks[habType][i])
			{
				return i;
			}
		}
		return -1;  // does not exists
	}

	// habitat + task
	// taskid is not a type of task, it is already mapped place within vector
	// bool is here only so that overloading compiles
	double HabitatTaskTime(int habType, int taskId, bool byId)
	{
		return habitatTaskTimes[habType][taskId];
	}

	double HabitatTaskTime(int habType, int taskType)
	{
		return HabitatTaskTime(habType, MapTaskType(habType, taskType), true);
	}

	double HabitatTaskCost(int habType, int taskId, bool byId)
	{
		return habitatTaskCosts[habType][taskId];
	}

	double HabitatTaskCost(int habType, int taskType)
	{
		return HabitatTaskCost(habType, MapTaskType(habType, taskType), true);
	}

public:
	// game framework:
	void AddHabitatConfig() {}
};

// like I said, singleton, also global
HabitatDatabase BaseData;

