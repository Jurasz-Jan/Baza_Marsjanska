#pragma once
#include <fstream>
#include <vector>
#include "Enums.hpp"

//works on callbacks, actual reading process defined in main,
//this works only as a wrapper for dealing with specyfic file format
class TaskFileLoader
{

public:
    //takes function pointer, where each subsequent function
    //reads a new section of the file
    void ReadFile(std::string name, void(**function)(std::vector<std::string>*), int fNums)
    {
        std::ifstream infile(name);

        if (infile.is_open())
        {
            unsigned int section = 0;
            int lineNum = 0;
            int readPoint = 0;
            std::string line;
            std::string reader;
            while (std::getline(infile, line))
            {
                if (changeSection(line)) //make this co-work with enums!
                {
                    ++section;
                    lineNum = 0;
                    continue;
                }
                readPoint = 0;
                reader = "";
                std::vector<std::string> parts;
                for (int j = 0; readPoint < line.size(); ++j)
                {
                    reader = nextStringToCharacter(line, ' ', readPoint);
                    readPoint += reader.size() + 1;
                    parts.push_back(reader);
                }
                //here call function that does something with data:
                if (section < fNums)
                {
                    function[section](&parts);
                }
                //general debugging function
                function[0](&parts);
            }
        }
        else
        {
            throw "file " + name + " unable to read";
        }
    }

private:
    std::string nextStringToCharacter(std::string org, char comp, int startPoint)
    {
        unsigned int i = startPoint;
        std::string res = "";
        if (i < org.size() && org[i] == comp)
        {
            ++i;
        }
        while (i < org.size() && org[i] != comp)
        {
            res.push_back(org[i]);
            ++i;
        }
        return res;
    }

    bool changeSection(std::string line)
    {
        if (line.size() > 0 && line[0] == '@')
        {
            return true;
        }
        return false;
    }
};
