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
std::vector<int64_t> split(const std::string &str, char sep)
{
    std::vector<int64_t> tokens;
 
    int64_t i;
    std::stringstream ss(str);
    while (ss >> i) {
        tokens.push_back(i);
        if (ss.peek() == sep) {
            ss.ignore();
        }
    }
 
    return tokens;
}
std::vector<std::string> splitStr (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

bool fits(std::string input, std::string fasit){
    for(int64_t i = 0; i < input.size(); i++){
        if(!(fasit[i] == '?' or input[i] == fasit[i]))
            return false;
    }
    return true;
}


std::map<int64_t, int64_t> MEMO{};

int64_t hashArgs(std::string str, std::vector<int64_t> vec){
    std::string vecStr{};
    for(auto v:vec){
        vecStr += std::to_string(v) + ',';
    }
    auto res = str+vecStr;
    return std::hash<std::string>{}(res);
}

int64_t countPermuts2(std::string fullCond, std::vector<int64_t> groups){
    int64_t count = 0;
    int64_t minSizeRemaining = std::transform_reduce(groups.begin() + 1, groups.end(), 0, std::plus{}, [](int64_t val){return val+1;});
    int64_t endI = fullCond.size() - minSizeRemaining;
    int64_t range = groups.front();
    if(groups.size() == 1){
        for(int64_t i = 0; i < endI - range + 1; i++){
            std::string tempCond; 
            tempCond = std::string(i, '.') + std::string(range, '#');
            tempCond.append(fullCond.size() - tempCond.size(), '.');
            if(!fits(tempCond, fullCond)) continue;    
            count += 1; 
            
        }
    }
    else{
        for(int64_t i = 0; i < endI - range + 1; i++){
            std::string tempCond; 
            std::string padding = "";
            
            tempCond = std::string(i - 0, '.') + std::string(range, '#');
            tempCond += '.';
            int64_t nextStartI = i + range + 1;
            if(!fits(tempCond, fullCond)) continue;
            std::string restCond = fullCond.substr(nextStartI);
            auto subGroups = std::vector<int64_t>(groups.begin()+1, groups.end());
            auto hash = hashArgs(restCond, subGroups);
            if(MEMO.contains(hash))
                count += MEMO[hash];
            else{
                int64_t res = countPermuts2(restCond, subGroups);
                MEMO[hash] = res;
                count += res;
            }

        }
    }

    return count;
}

int64_t countPermuts(int64_t startI, std::string fullCond, std::vector<int64_t> groups, int64_t groupIndex, std::string buildCond){
    int64_t count = 0;
    int64_t minSizeRemaining = std::transform_reduce(groups.begin() + groupIndex + 1, groups.end(), 0, std::plus{}, [](int64_t val){return val+1;});
    int64_t endI = fullCond.size() - minSizeRemaining;
    int64_t range = groups[groupIndex];
    if(groupIndex == groups.size()-1){
        for(int64_t i = startI; i < endI - range + 1; i++){
            std::string tempCond; 
            tempCond = buildCond + std::string(i - startI, '.') + std::string(range, '#');
            tempCond.append(fullCond.size() - tempCond.size(), '.');
            if(!fits(tempCond, fullCond)) continue;    
            count += 1; 
            
        }
    }
    else{
        for(int64_t i = startI; i < endI - range + 1; i++){
            std::string tempCond; 
            std::string padding = "";
            
            tempCond = buildCond + std::string(i - startI, '.') + std::string(range, '#');
            tempCond += '.';
            int64_t nextStartI = i + range + 1;
            if(!fits(buildCond, fullCond)) continue;
            count += countPermuts(nextStartI, fullCond, groups, groupIndex + 1, tempCond);
        }
    }

    return count;
}

    // void task1(){
    //     auto lines = readFile("inputTest.txt");
    //     int64_t sum = 0;
    //     for(auto &l : lines){
    //         std::stringstream ss {l};
    //         std::string conditions, groupsString;
    //         ss >> conditions >> groupsString;
    //         auto groups = split(groupsString, ',');

    //         int64_t temp = countPermuts(conditions, groups);
    //         std::cout << std::endl;
    //         std::cout << "Temp: " << temp << std::endl;
    //         std::cout << std::endl;
    //         sum += temp;
    //     }

    //     std::cout << "Sum: " << sum << std::endl;
    // }
bool onlyHashes(std::string s){
    for(auto c :s){
        if(c != '#')return false;
    }
    return true;
}
int64_t countSubstrings(std::string s, std::string target){


   int occurrences = 0;
   std::string::size_type pos = 0;
   while ((pos = s.find(target, pos )) != std::string::npos) {
          ++ occurrences;
          pos += target.length();
   }
   return occurrences;
}

void prune(std::string & cond, std::vector<int64_t> & groups){
    
    for(int i = 1; i < cond.size(); i++){
        char c = cond[i];
        if(c == '.' && c  == cond[i-1]){
            cond.erase(i, 1);
            i--;
        }
    }
    auto vec = splitStr(cond, '.');

    if(vec.front() == "")
        vec.erase(vec.begin());
    bool keepgoing = true;
    while(keepgoing){
        keepgoing = false;
        if(vec.back().size() == groups.back() && onlyHashes(vec.back())){
            vec.pop_back();
            groups.pop_back();
            keepgoing = true;
        }
        if(vec.front().size() == groups.front() && onlyHashes(vec.back())){
            vec.erase(vec.begin());
            groups.erase(groups.begin());
            keepgoing = true;
        }
    }
    std::string str{};
    int i = 0;
    for(auto & v : vec){
        if(v != ""){
            str += v;
            if (i != vec.size()-1) 
                str += '.';
        }

        i++;
    }
    for(auto & n:groups){
        std::cout << n << " ";
    }


    cond = str;
}

void task2(){
    auto lines = readFile("inputTest.txt");
    int64_t sum = 0;
    int64_t index = 0;

    sum = std::transform_reduce(std::execution::seq, lines.begin(), lines.end(), (int64_t)0, std::plus{}, [&](auto &l){
        std::stringstream ss {l};
        std::string conditions, groupsString;
        ss >> conditions >> groupsString;
        auto groups = split(groupsString, ',');

        std::string newCond = "";
        std::vector<int64_t> newGroups{};
        for (int64_t i = 0; i < 5; i++){
            if(i == 4){
                newCond += conditions;
            }   
            else newCond += conditions + '?';
            newGroups.append_range(groups);
        }
        std::cout << "newCond: " << newCond << std::endl;

        prune(newCond, newGroups);
        int64_t temp = countPermuts2(newCond, newGroups);

        // int64_t temp = countPermuts(0, newCond, newGroups, 0, "");
        std::cout << std::endl;
        std::cout << index +1<< "/" << lines.size()  << std::endl;
        std::cout << "Temp: " << temp << std::endl;
        std::cout << std::endl;
        index++;
        return temp;
    });

    std::cout << "Sum: " << sum << std::endl;
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