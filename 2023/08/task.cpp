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

int traverse(std::string start, std::string search, std::string LR, std::map<std::string, std::pair<std::string, std::string>> graph){
    int i = 0;
    std::string curr = start;
    while(true){

        char lr = LR[i%LR.size()];

        if(lr == 'L')
            curr = graph[curr].first;
        else 
            curr = graph[curr].second;
        i++;
        if(curr == search){
            return i;
        }
    }

}

int64_t gcd(int64_t a, int64_t b)
{
    for (;;)
    {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}

int64_t lcm(int64_t a, int64_t b)
{
    int64_t temp = gcd(a, b);

    return temp ? (a / temp * b) : 0;
}

int traverse2(std::string LR, std::map<std::string, std::pair<std::string, std::string>> graph){
    int64_t i = 0;
    std::vector<std::string> curr{};

    for(auto & [nodes, _]: graph){
        if(nodes[2] == 'A'){
            curr.push_back(nodes);
        }
    }       
    std::vector<int64_t> cyc(curr.size());

    int cyCount = 0; 
    while(true){
        char lr = LR[i%LR.size()]; 
        int check = 0;
        for(auto & c: curr){       
            if(lr == 'L')
                c = graph[c].first;
            else 
                c = graph[c].second;
            if(c[2] == 'Z'){
                check++;
            }
        }
        
        i++;
        // if(check == curr.size())
        //     return i;
        if(i%1000000 == 0)
            std::cout << i << " ... " << check << "/" << curr.size() << std::endl;
        for(int j = 0; j < curr.size(); j++){
            if(curr[j][2] == 'Z' && cyc[j] == 0){
                cyc[j] = i;
                std::cout << "cyCount: " << cyCount << " " << i << std::endl;
            }
        }
        int cyCheck = 0;
        for (auto &c: cyc){
            if(c != 0)
                cyCheck++;
        }
        if(cyCheck == cyc.size()){
            break;
        }
    }
    std::cout << "cycheck: " << cyc[0] << std::endl; 

    int64_t result = std::accumulate(cyc.begin(), cyc.end(), (int64_t)1, lcm);

    std::cout << result << '\n';
    return result;
}



// void task1(){
//     auto lines = readFile("inputTest.txt");
//     std::string instructions = lines[0];
//     std::map<std::string, std::pair<std::string, std::string>> graph{};
//     for (int i = 2; i < lines.size(); i++){
//         auto l = lines[i];
//         std::stringstream ss{l};
//         std::string source, eq, left, right;
//         ss >> source >> eq >> left >> right;
//         std::erase(left, '(');
//         std::erase(left, ',');
//         std::erase(right, ')');

//         graph[source] = std::pair<std::string, std::string>(left,right);
//     }
//     int ans = traverse("AAA", "ZZZ", instructions, graph);
//     std::cout << ans << std::endl;
// }



void task2(){
    auto lines = readFile("input.txt");
    std::string instructions = lines[0];
    std::map<std::string, std::pair<std::string, std::string>> graph{};
    for (int i = 2; i < lines.size(); i++){
        auto l = lines[i];
        std::stringstream ss{l};
        std::string source, eq, left, right;
        ss >> source >> eq >> left >> right;
        std::erase(left, '(');
        std::erase(left, ',');
        std::erase(right, ')');
        graph[source] = std::pair<std::string, std::string>(left,right);
    }
    int ans = traverse2(instructions, graph);
    std::cout << ans << std::endl;
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