#pragma once

#include <iostream>

class Task
{
public:
	Task(uint32_t _id, const std::string &_name = "TASK") : id(_id), name(_name) {}
	~Task() = default;

	Task(Task &&) = default;

	Task(const Task &) = default;

	Task &operator=(Task &&) = default;

	Task &operator=(const Task &) = default;

	uint32_t getID() const { return id; }
	const std::string &getName() const { return name; }

private:
	uint32_t id;
	std::string name;
};