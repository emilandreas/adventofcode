#include <iostream>
#include <sstream>
#include "../readFile.cpp"
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <chrono>

struct mapping{
    int64_t source;
    int64_t dest;
    int64_t range;
};

std::vector<std::vector<mapping>> AllMappings{};

bool isInMapping(mapping &m, int64_t from){
    if(from >= m.source && from < m.source + m.range){
        return true;
    }
    return false;
}

int64_t mapToNext(std::vector<mapping>& mappings, int64_t from){
    for (auto & m: mappings){
        if(isInMapping(m, from))
            return m.dest + from - m.source;
    }
    return from;
}
bool isInMappingReverse(mapping &m, int64_t from){
    if(from >= m.dest && from < m.dest + m.range){
        return true;
    }
    return false;
}
int64_t mapToNextReverse(std::vector<mapping>& mappings, int64_t from){
    for (auto & m: mappings){
        if(isInMappingReverse(m, from))
            return m.source + from - m.dest;
    }
    return from;
}


void task1(){
    auto lines = readFile("input.txt");
    std::vector<int64_t> seeds{};
    std::stringstream ss{lines[0]};
    std::string s;

    ss >> s;
    while(ss >> s){
        seeds.push_back(stoll(s));
    }
    auto maps = std::vector<std::string>(lines.begin() + 2, lines.end());

    int64_t mapIndex = -1;
    for(auto & l :maps){
        if (l.contains("map:")){
            mapIndex++;
            AllMappings.push_back(std::vector<mapping>{});
            continue;
        }
        if(l.empty())continue;
        std::string dest, source, range;
        std::stringstream ss1{l};
        ss1 >> dest;
        ss1 >> source;
        ss1 >> range;
        mapping map{stoll(source), stoll(dest), stoll(range)};
        AllMappings[mapIndex].push_back(map);
        // AllMappings.push_back()

    }
    int64_t lowestDest = 9999999999999;
    for(auto & sds: seeds){
        int64_t dest = sds;
        for(auto & map : AllMappings){
            dest = mapToNext(map, dest);
        }
        if (dest < lowestDest){
            lowestDest = dest;
        }
    }
    std::cout << lowestDest << std::endl;


}

bool isInSeeds(std::vector<int64_t> seeds, int64_t dest){
    for(int i = 0; i < seeds.size(); i += 2){
        if(dest > seeds[i] && dest < seeds[i]+seeds[i+1]) 
            return true;
    }
    return false;
}

void task2(){
   auto lines = readFile("input.txt");
    std::vector<int64_t> seeds{};
    std::stringstream ss{lines[0]};
    std::string s;

    ss >> s;
    while(ss >> s){
        seeds.push_back(stoll(s));
    }
    auto maps = std::vector<std::string>(lines.begin() + 2, lines.end());

    int64_t mapIndex = -1;
    for(auto & l :maps){
        if (l.contains("map:")){
            mapIndex++;
            AllMappings.push_back(std::vector<mapping>{});
            continue;
        }
        if(l.empty())continue;
        std::string dest, source, range;
        std::stringstream ss1{l};
        ss1 >> dest;
        ss1 >> source;
        ss1 >> range;
        mapping map{ stoll(source), stoll(dest), stoll(range)};
        AllMappings[mapIndex].push_back(map);
        // AllMappings.push_back()

    }
    reverse(AllMappings.begin(), AllMappings.end());
    int64_t i = 0;
    while(true){
        int64_t dest = i;
        for(auto & map : AllMappings){
            dest = mapToNextReverse(map, dest);
        }
        if(isInSeeds(seeds,dest)){
            std::cout << "lowest: " << i << std::endl;
            return;
        }
        i++;
    }
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