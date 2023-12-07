#include <iostream>
#include <sstream>
#include "../readFile.cpp"
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <chrono>
struct HAND {
    std::string cards;
    int bid;
    int score;
};
std::vector<HAND> hands{};


bool cmp(std::pair<char, int>& a,
         std::pair<char, int>& b)
{
    return a.second > b.second;
}
std::vector<char> names{'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};

bool cmp2(HAND a, HAND b){
    if(a.score == b.score){
        for(int i = 0; i < 5; i++){
            char cardA = a.cards[i];
            char cardB = b.cards[i];
            if(std::find(names.begin(), names.end(), cardA) == std::find(names.begin(), names.end(), cardB))
                continue;
            return std::find(names.begin(), names.end(), cardA) > std::find(names.begin(), names.end(), cardB);
        }
    }
    return a.score < b.score;
}
int scoreHand(std::string cards){
    std::map<char, int> cardCount{};
    for(int i = 0; i < cards.size(); i++){
        if(!cardCount.contains(cards[i])){
            cardCount[cards[i]] = 0;
        }
        cardCount[cards[i]]++;
    }
    std::vector<std::pair<char, int>> sortedMap{};
    for(auto& [key, value] : cardCount){
        sortedMap.push_back(std::pair<char, int>(key, value));
    }
    std::sort(sortedMap.begin(), sortedMap.end(), cmp);
    int score = 0;

    auto c = sortedMap[0];
    auto c2 = sortedMap[1];
    if(c.second == 5){
        score = 6;
    }
    else if(c.second == 4){
        score = 5;
    }
    else if(c.second == 3 && c2.second == 2){
        score = 4;
    }
    else if(c.second == 3){
        score = 3;
    }
    else if(c.second == 2 && c2.second == 2){
        score = 2;
    }
    else if(c.second == 2){
        score = 1;
    }
    else {
        score = 0;
    }
    return score;
}



int getMaxJokerScore(std::string cards){
    if(cards.contains('J')){
        int maxScore = 0;
        for(auto & c: names){
            std::string s = cards;
            std::replace(s.begin(), s.end(), 'J', c);
            int score = scoreHand(s);
            if(score > maxScore) maxScore = score;
        }
        return maxScore;

    }else
    return scoreHand(cards);
}

void task1(){
    auto lines =readFile("input.txt");
    for(auto & l : lines){
        std::stringstream ss{l};
        std::string cards;
        int bid;
        ss >> cards;
        ss >> bid;
         
        hands.push_back(HAND{cards, bid, scoreHand(cards)});
    }
    std::sort(hands.begin(), hands.end(), cmp2);
    int64_t sum = 0;
    for(int i = 0; i < hands.size(); i++ ){
        sum += hands[i].bid*(i+1);
    }
    std::cout << "Sum: " << sum << std::endl;
}


void task2(){
    auto lines =readFile("input.txt");
    for(auto & l : lines){
        std::stringstream ss{l};
        std::string cards;
        int bid;
        ss >> cards;
        ss >> bid;
         
        hands.push_back(HAND{cards, bid, getMaxJokerScore(cards)});
    }
    std::sort(hands.begin(), hands.end(), cmp2);
    int64_t sum = 0;
    for(int i = 0; i < hands.size(); i++ ){
        sum += hands[i].bid*(i+1);
    }
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