#include <iostream>
#include "../readFile.cpp"
#include <string>
#include <algorithm>

int getLineNum(std::string line)
{
    std::size_t i1 = line.find_first_of("0123456789");
    std::size_t i2 = line.find_last_of("0123456789");
    std::string result{""};
    if (i1 != std::string::npos)
        result += line[i1];
    if (i2 != std::string::npos)
        result += line[i2];
    std::cout << result << std::endl;
    return std::stoi(result);
}

std::vector<std::string> nums = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int getLineNumWString(std::string line)
{
    std::size_t i1{0}, i2{0}, s1{0}, s2{0};
    i1 = line.find_first_of("0123456789");
    i2 = line.find_last_of("0123456789");
    if (i2 == std::string::npos)
        i2 = 0;
    s1 = 9999;
    s2 = std::string::npos;
    std::string string1{""};
    std::string string2{""};

    for (auto &n : nums)
    {
        std::size_t i = 0;

        while (i != std::string::npos){
            i = line.find(n, i);
            if (i != std::string::npos)
            {
                if(s2 == std::string::npos)
                    s2 = 0;
                if (i < s1)
                {
                    string1 = n;
                    s1 = i;
                }
                if (i > s2)
                {
                    string2 = n;
                    s2 = i;
                }
                i += 1;
            }
        }
    
    }
    std::string result{""};
    if(i1 < s1){
        result += line[i1]; 
    }
    else {
        auto a = std::find(nums.begin(), nums.end(), string1);
        auto b = std::find(nums.begin(), nums.end(), string1) - nums.begin();
    
        result += std::to_string(std::find(nums.begin(), nums.end(), string1) - nums.begin() + 1);
    }
    
    if(s2 == std::string::npos || i2 > s2){
        result += line[i2];
    }
    else{
        result += std::to_string(std::find(nums.begin(), nums.end(), string2) - nums.begin() + 1);
    }
    std::cout << result << std::endl;
    return std::stoi(result);    
}


int main()
{
    auto vec = readFile("./input1.txt");
    int sum = 0;
    for (auto &line : vec)
    {
        sum += getLineNumWString(line);
    }
    std::cout << "Sum: " << sum << std::endl;
}
