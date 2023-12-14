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

int isReflect(std::string s, int i){
    int back = i - 1;
    int front = i;
    int count = 0;
    while(back>= 0  && front < s.size()){
        if(s[back] != s[front]){
            count++;   
        }
        back--;
        front++;
    }
    return count;
}

int isReflect(std::vector<std::string> v, int i, int j){
 
    int back = i - 1;
    int front = i;
    int count = 0;
    while(back>= 0  && front < v.size()){
        char a = v[back][j];
        char b = v[front][j];
        if(a != b)
            count++;
        back--;
        front++;
    }
    return count;
}

std::vector<std::vector<std::string>> patterns{};
int findReflectHorizontal(std::vector<std::string> pattern){
    for(int i = 1; i < pattern.front().size(); i++){
        int count = 0;
        for (int j = 0; j < pattern.size(); j++){
            std::string row = pattern[j];
            count += isReflect(row, i);
            if(count > 1 ){
                break;
            }
            else
                if(j == pattern.size()-1){
                    if(count == 1)
                        return i;
                }
        }
    }
    return -1;
}
int64_t findReflectVertical(std::vector<std::string> pattern){
    for(int x = 1; x < pattern.size(); x++){
        int count = 0;
        for (int y = 0; y < pattern.front().size(); y++){
            count += isReflect(pattern, x, y);
            if(count > 1){
                break;
            }
            else
                if(y == pattern[x].size() -1){
                    if(count == 1)
                        return x;
                }
        }
    }
    return -1;
}
void task1(){
    auto lines = readFile("input.txt");
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
    int sum = 0;
    for (auto & pattern: patterns){
        int tempSum1 = findReflectHorizontal(pattern);
        if(tempSum1 != -1){
            sum += tempSum1;
        }
        int tempSum2 = findReflectVertical(pattern);
        if(tempSum2 != -1){
            sum += tempSum2*100;
        }
    }
    std::cout << "Sum: " << sum << std::endl;
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