#pragma once
#include <stdexcept>
#include <string>
#include <vector>

class Enum
{
public:
	friend class FileInterpreter; //again it is good practice, believe me
	//this way while reading the file we can change enums, but nowhere else

	unsigned int GetSize() const { return label.size(); }

	unsigned int GetId(const std::string& name)
	{
		unsigned int labelSize = label.size();
		for (unsigned int i = 0; i < labelSize; ++i)
		{
			if (CompareLabels(label[i], name))
			{
				return i;
			}
		}
		throw std::out_of_range("label " + name + " does not exists within current enum");
	}

private:
	// id is just by position within vector
	std::vector<std::string> label;

private:
	bool CompareLabels(std::string org, std::string other) const
	{
		unsigned int orgSize = org.size();
		if (orgSize != other.size())
		{
			return false;
		}
		for (unsigned int i = 0; i < orgSize; ++i)
		{
			if (org[i] != other[i])
			{
				return false;
			}
		}
		return true;
	}
};

// here defines global enums for usage within classes
Enum TaskFile;
Enum HabitatType;
Enum ChannelType;
