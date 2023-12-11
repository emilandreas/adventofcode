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
struct Galaxy {
    size_t x;
    size_t y;
    size_t id;
};

bool isEmptyCol(size_t y, std::vector<std::string> v){
    int count = 0;
    for(auto&l : v){
        if(l[y] == '#') return false;
    }
    return true;
}
bool isEmptyRow(size_t x, std::vector<std::string> v){
    return !v[x].contains('#');
}

int64_t countEmptyRows(size_t x, size_t y, std::vector<std::string> v){
    size_t start = std::min(x, y)+1;
    size_t end = std::max(x,y);
    int count = 0;
    for(int i = start; i < end; i++){
        if(isEmptyRow(i, v)) count++;
    }
    return count;
}
int64_t countEmptyCols(size_t x, size_t y, std::vector<std::string> v){
    size_t start = std::min(x, y)+1;
    size_t end = std::max(x,y);
    int count = 0;
    for(int i = start; i < end; i++){
        if(isEmptyCol(i, v)) count++;
    }
    return count;
}

int64_t getDist(Galaxy a, Galaxy b, std::vector<std::string> v){
    auto emptyRows = countEmptyRows(a.x, b.x, v);
    auto emptyCols = countEmptyCols(a.y, b.y, v);
    return abs((int)a.x-(int)b.x) + abs((int)a.y-(int)b.y) + (1000000-1)*(emptyRows + emptyCols);
}



std::vector<Galaxy> galaxies{};

void expand(std::vector<std::string> &v){
    for(size_t i = 0; i < v.size(); i++){
        for(int n = 0; n < 1000000; n++){
                        if(isEmptyRow(i, v)){
                v.insert(v.begin() + (int)i, v[i]);
                i++;
            }
        }


    }
    for(size_t j = 0; j < v[0].size(); j++){
        if(isEmptyCol(j, v)){
            for(int n = 0; n < 1000000; n++){

                for (auto & s: v){
                    s.insert(s.begin() + j, '.');
                }
                j++;
            }
        }
    }
}

// void task1(){
//     auto space = readFile("input.txt");
//     size_t x = 0;
//     size_t ngalaxy = 0;
//     // expand(space);

//     for(auto &l: space){
//         size_t y= 0;
//         for(auto &c: l){
//             if(c == '#')
//                 galaxies.push_back(Galaxy{x, y, ngalaxy++});
//             y++;
//         }
//         x++;
//     }


//     int64_t dist = 0;
//     for (int i = 0; i < galaxies.size() - 1; i++){
//         Galaxy a = galaxies[i];
//         for(int j = i+1; j < galaxies.size(); j++){
//             Galaxy b = galaxies[j];
//             dist += getDist(a,b, space);
//         }
//     }
//     std::cout << "Dist " << dist << std::endl;
// }


void task2(){
    auto space = readFile("input.txt");
    size_t x = 0;
    size_t ngalaxy = 0;
    // expand(space);

    for(auto &l: space){
        size_t y= 0;
        for(auto &c: l){
            if(c == '#')
                galaxies.push_back(Galaxy{x, y, ngalaxy++});
            y++;
        }
        x++;
    }


    size_t dist = 0;
    for (int i = 0; i < galaxies.size() - 1; i++){
        std::cout << "Galaxy: " << i << std::endl;
        Galaxy a = galaxies[i];
        for(int j = i+1; j < galaxies.size(); j++){
            Galaxy b = galaxies[j];
            dist += getDist(a,b, space);
        }
    }
    std::cout << "Dist " << dist << std::endl;
    
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