#include <iostream>
#include <sstream>
#include "../readFile.cpp"
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <set>

void task1(){
    int sum = 0;
    auto lines = readFile("input.txt");
    std::string s;
    for (auto & l : lines){
        std::stringstream ss{l};
        ss >> s; //Card
        ss >> s; //[Number]:
        std::set<int> winners{};
        std::set<int> mine{};

        while(ss >> s){
            if(s.contains('|')) break;
            winners.insert(stoi(s));
        }
        int p = 0;
        while(ss >> s){
            if(winners.contains(stoi(s))){
                p++;
            }
        }
        if(p > 0){
            sum += pow(2, p-1);
        }
    }

    std::cout << sum << std::endl;
}

void task2(){
    auto lines = readFile("input.txt");
    // auto lines = readFile("inputTest.txt");
    std::string s;
    std::vector<int> multi(1000, 1);
    int index = 0;
    for (auto & l : lines){
        std::stringstream ss{l};
        ss >> s; //Card
        ss >> s; //[Number]:
        std::set<int> winners{};
        std::set<int> mine{};

        while(ss >> s){
            if(s.contains('|')) break;
            winners.insert(stoi(s));
        }
        int p = 0;
        while(ss >> s){
            if(winners.contains(stoi(s))){
                p++;
            }
        }
        int numCopies = multi[index];
        for(int i = 1; i <= p; i++){
            multi[index + i] += numCopies;
        }
        index++;
    }
    int numCards = 0;
    for (int i = 0; i < lines.size(); i++){
        numCards += multi[i];
    }
    std::cout << numCards << std::endl;

}

int main(){
    task2();
}