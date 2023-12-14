#include <iostream>
#include <sstream>
#include "../readFile.cpp"
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <chrono>

#include <numeric>
#include <ranges>
#include <execution>

bool isReflect(std::string s, int i){
    int back = i - 1;
    int front = i;
    while(back>= 0  && front < s.size()){
        if(s[back] != s[front])
            return false;
        back--;
        front++;
    }
    return true;
}
bool isReflect(std::vector<std::string> v, int i){
 
    int back = i - 1;
    int front = i;
    while(back>= 0  && front < v.size()){
        if(v[back][i] != v[front][i])
            return false;
    }
    return true;
}

std::vector<std::vector<std::string>> patterns{};
int findReflectHorizontal(std::vector<std::string> pattern){
    for(int i = 1; i < pattern.front().size(); i++){
        for (int j = 0; j < pattern.size(); j++){
            std::string row = pattern[j];
            if(!isReflect(row, i)){
                break;
            }
            else
                if(j == pattern.size()-1){
                    return i;
                }
        }
    }

    return -1;
}
int64_t findReflectVertical(std::vector<std::string> pattern){
    for(int x = 1; x < pattern.size(); x++){
        for (int y = 0; y < pattern.front().size(); y++){
            if(!isReflect(pattern, ))
        }
    }
}
void task1(){
    auto lines = readFile("inputTest.txt");
    std::vector<std::string> pattern{};
    for(int i = 0; i < lines.size(); i++){
        auto l = lines[i];
        std::stringstream ss{l};
        std::string s;
        ss >> s;
        if(s.empty() || i + 1 == lines.size()){
            patterns.push_back(pattern);
            pattern.clear();
        }
        else
            pattern.push_back(s);
    }
}

void task2(){

}

int main(){
    
    try {
        auto start = std::chrono::high_resolution_clock::now();
        task1();
        auto stop = std::chrono::high_resolution_clock::now();
        std::cout << "Time used [ms]: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start) << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}