#include <iostream>
#include "../readFile.cpp"
#include <string>
#include <algorithm>
#include <map>
#include <vector>


int parseGameLine(std::string line, std::map<std::string, int>& maxCubes){
    auto nums = "0123456789";
    auto i1 = line.find_first_of(nums);
    auto i2 = line.find_first_not_of(nums, i1);
    int game = std::stoi(line.substr(i1, i2));

    size_t i = i2;
    while(i != std::string::npos){
        i1 = line.find_first_of(nums, i);
        i2 = line.find_first_not_of(nums, i1);
        if(i1 == std::string::npos || i2 == std::string::npos)
            break;
        int num = std::stoi(line.substr(i1, i2));

        i1 = line.find_first_of(",;", i2);
        std::string color = "";
        if(i1 == std::string::npos)
            color = line.substr(i2);
        else
            color = line.substr(i2, i1 - i2);
        std::erase(color, ' ');
        if(maxCubes[color] < num)
            maxCubes[color] = num;
        if(maxCubes.size() > 3)
            std::cout << "Error Error, over 3" << std::endl;
        i = i1;
    }
    return game;
}

bool verifyGame(std::map<std::string, int> verify, std::map<std::string, int> c){
    return verify["blue"] >= c["blue"] && verify["red"] >= c["red"] && verify["green"] >= c["green"];
}
int power(std::map<std::string, int> c){
    return c["blue"]*c["red"]*c["green"];
}

int main(){
    auto lines = readFile("input.txt");
    int sum = 0;
    int sumpower = 0;
    std::map<std::string, int> verify = {{"blue", 14}, {"red", 12},{"green", 13}};

    for(auto & l : lines){
        std::map<std::string, int> maxCubes = {{"blue", 0}, {"red", 0},{"green", 0}};

        int game = parseGameLine(l, maxCubes);
        if(verifyGame(verify, maxCubes))
            sum += game;
        sumpower += power(maxCubes);
    }
    std::cout << "sum: " << sum << std::endl;
    std::cout << "sumpower: " << sumpower << std::endl;

}