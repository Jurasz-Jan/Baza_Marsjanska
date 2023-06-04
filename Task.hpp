#pragma once

#include <iostream>

class Task
{
public:
	Task(unsigned int _id, const std::string &_name = "TASK") : id(_id), name(_name) {}
	~Task() = default;

	Task(Task &&) = default;

	Task(const Task &) = default;

	Task &operator=(Task &&) = default;

	Task &operator=(const Task &) = default;

private:
	unsigned int id;
	std::string name;
};