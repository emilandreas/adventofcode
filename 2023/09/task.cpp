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


std::vector<int> getDiff(std::vector<int> in){
    std::vector<int> diff;
    for(int i = 0; i < in.size() -1; i++){
        diff.push_back(in[i+1]-in[i]);
    }
    return diff;
}

bool isZeros(std::vector<int> in){
    for (auto & i : in){
        if(i != 0)
            return false;
    }
    return true;
}

void task1(){
    auto lines = readFile("input.txt");
    std::vector<int> input{};
    int sum = 0;
    for(auto & l : lines){
        std::vector<int> input{};
        std::stringstream ss{l};
        int s;
        while(ss >> s){
            input.push_back(s);
        }
        std::vector<std::vector<int>> seqs{};
        seqs.push_back(input);
        while(true){
            auto diffVec = getDiff(seqs.back());
            if(isZeros(diffVec))
                break;
            seqs.push_back(diffVec);
        }

        //extrapolate
        int tempSum = 0;
        int diff = 0;
        for(auto & v : seqs | std::views::reverse){
            int ext = v.back() + diff;
            v.push_back(ext);
            diff = ext;
            tempSum += ext;
        }
        sum += seqs[0].back();
    }


    std::cout << "sum: " << sum << std::endl;    
}



void task2(){
    auto lines = readFile("input.txt");
    std::vector<int> input{};
    int sum = 0;
    for(auto & l : lines){
        std::vector<int> input{};
        std::stringstream ss{l};
        int s;
        while(ss >> s){
            input.push_back(s);

        }
        std::vector<std::vector<int>> seqs{};
        std::reverse(input.begin(), input.end());
        seqs.push_back(input);
        while(true){
            auto diffVec = getDiff(seqs.back());
            if(isZeros(diffVec))
                break;
            seqs.push_back(diffVec);
        }

        //extrapolate
        int diff = 0;
        for(auto & v : seqs | std::views::reverse){
            int ext = v.back() + diff;
            v.push_back(ext);
            diff = ext;
        }
        sum += seqs[0].back();
    }


    std::cout << "sum: " << sum << std::endl; 
}

int main(){
    
    try {
        auto start = std::chrono::high_resolution_clock::now();
        task2();
        auto stop = std::chrono::high_resolution_clock::now();
        std::cout << "Time used [ms]: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start) << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}