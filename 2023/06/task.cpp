#include <iostream>
#include <sstream>
#include "../readFile.cpp"
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <chrono>


void task1(){
    auto lines =readFile("input.txt");
    // auto lines =readFile("inputTest.txt");

    std::stringstream ss{lines[0]};
    int dur1, dur2, dur3, dur4;
    int rec1, rec2, rec3, rec4;
    std::string s;
    ss >> s;
    ss >> dur1 >> dur2 >> dur3 >> dur4;
    ss.clear();
    ss.str(lines[1]);
    ss >> s;
    ss >> rec1 >> rec2 >>rec3 >> rec4;

    std::vector<int> dur{dur1, dur2, dur3, dur4};
    std::vector<int> rec{rec1, rec2,rec3, rec4};
    int64_t sum = 1;
    for(int r = 0; r < dur.size(); r++){
        int numFaster = 0;
        for(int i = 0; i <= dur[r]; i++){
            int dist = (dur[r] - i)*i;
            if(dist > rec[r])
                numFaster++;
        }
        sum *= numFaster;

    }
    std::cout << "sum: " << sum << std::endl;

}


void task2(){
        auto lines =readFile("input.txt");
    // auto lines =readFile("inputTest.txt");

    std::stringstream ss{lines[0]};
    std::string dur1, dur2, dur3, dur4;
    std::string rec1, rec2, rec3, rec4;
    std::string s;
    ss >> s;
    ss >> dur1 >> dur2 >> dur3 >> dur4;
    ss.clear();
    ss.str(lines[1]);
    ss >> s;
    ss >> rec1 >> rec2 >>rec3 >> rec4;

    std::string durStr = dur1+dur2+dur3+dur4;
    std::string recStr = rec1+rec2+rec3+rec4;

    int64_t dur = stoll(durStr);
    int64_t rec = stoll(recStr);



    int64_t numFaster = 0;
    for(int i = 0; i <= dur; i++){
        int64_t dist = (dur - i)*i;
        if(dist > rec)
            numFaster++;
    }



    std::cout << "numFaster: " << numFaster << std::endl;

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