#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> readFile(const std::string &filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<std::string> lines;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
    return lines;
}