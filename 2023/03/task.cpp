#include <iostream>
#include "../readFile.cpp"
#include <string>
#include <algorithm>
#include <map>
#include <vector>
std::map<char, int> GLOB{};

std::map<char, int> ALL{};

bool isPosValid(std::vector<std::string> v, size_t y, size_t x){
    int y_temp{(int)y}, x_temp{(int)x};
    for(int yt = -1; yt <= 1; yt++){
        if((y_temp = y+yt) <0 || y_temp >= v.size())
            continue;
        for(int xt = -1; xt <= 1; xt++){
            if((x_temp = x+xt) <0 || x_temp >= v[yt].size())
                continue;
            if(not isdigit(v[y_temp][x_temp]) && v[y_temp][x_temp] != '.' && v[y_temp][x_temp] != '\0'){
                GLOB[v[y_temp][x_temp]] = 1;
                return true;
            }

        }
    }
    return false;
}

bool isNumValid(std::vector<std::string> v, int y, int x, int length){
    for(int numIndex = 0; numIndex < length; numIndex++){
        if(isPosValid(v, y, x+numIndex)) return true;
    }
    return false;
}

std::string NUMS = "0123456789";
int main(){
    int sum = 0;
    auto lines = readFile("input.txt");
    auto res = isPosValid(lines, 0, 2);

    for(int lineIndex = 0; lineIndex < lines.size(); lineIndex++){
        size_t i = 0;
        while(i != std::string::npos){
            std::string l = lines[lineIndex];
            auto start = l.find_first_of(NUMS, i);
            auto end = l.find_first_not_of(NUMS, start);
            if(start == std::string::npos) break;
            if(end == std::string::npos) 
                end = l.size();
            int num = std::stoi(l.substr(start,end-start));
            bool numValid = isNumValid(lines, lineIndex, start, end - start);
            if(numValid)
                sum += num;
            i = end;
        }

    }

}