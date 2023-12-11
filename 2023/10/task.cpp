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
std::vector<std::string> pipes{};
enum DIR {north, east, south, west};

struct Pos{
    int x;
    int y;
    bool operator==(const Pos rhs){
        return x == rhs.x && y == rhs.y;
    }
    DIR dir;
};



char getPipe(Pos pos){
    if(pos.x >= 0 && pos.x < pipes.size() && pos.y >= 0 && pos.y < pipes[0].size())
        return pipes[pos.x][pos.y];
    else{
        std::cout << "Error! x, y=" << pos.x << ", " << pos.y << std::endl;
        return '0';
    }
}


Pos getNext(Pos currPos){
    char c = getPipe(currPos);
    Pos nextPos{currPos};
    DIR dir = nextPos.dir;
    switch(c){
        case '|':
            if(dir == north){
                nextPos.x--;
                nextPos.dir = north;
            }
            
            else if(dir == south){
                nextPos.x++;
                nextPos.dir = south;
            }

            break;
        case '-':
            if(dir == west){
                nextPos.y--;
                nextPos.dir = west;
            }
            
            else if(dir == east){
                nextPos.y++;
                nextPos.dir = east;
            }
            break;
        case 'L':
            if(dir == west){

                nextPos.x--;
                nextPos.dir = north;
            }
            else if(dir == south){
                nextPos.y++;
                nextPos.dir = east;
            }
            break;
        case 'J':
            if(dir == east){
                nextPos.x--;
                nextPos.dir = north;
            }
            
            else if(dir == south){
                nextPos.y--;
                nextPos.dir = west;
            }
            break;
        case '7':
            if(dir == east){
                nextPos.x++;
                nextPos.dir = south;
            }
            
            else if(dir == north){
                nextPos.y--;
                nextPos.dir = west;
            }
            break;
        case 'F':           
            if(dir == north){
                nextPos.y++;
                nextPos.dir = east;
            }
            
            else if(dir == west){
                nextPos.x++;
                nextPos.dir = south;
            }
            break;
        case '.':
            std:: cout << "Error! you hit ground. " << currPos.x << " " << currPos.y << std::endl;
            return Pos{-1, -1};
            break;
        case 'S':
            break;

    }
    return nextPos;
}

DIR opposite(DIR dir){
    switch(dir){
        case south:
            return north;
        break;
        case north:
            return south;
        break;       
        case east:
            return west;
        break;
        case west:
            return east;
        break;
        
    }
    return north;
}

Pos findFirst(Pos sp){
    Pos testPos{};
    std::vector<Pos> testPoses{Pos{sp.x +1, sp.y}, Pos{sp.x-1, sp.y}, Pos{sp.x, sp.y+1}, Pos{sp.x, sp.y-1}};
    
    for(auto & testPos: testPoses ){
        for(int i = 0; i < 4; i++){
            DIR dir = static_cast<DIR>(i);
            testPos.dir = dir;
            auto nextPos = getNext(testPos);
            if(sp == nextPos){
                 testPos.dir = opposite(nextPos.dir);
                return testPos;
            } 
        }
    }
    return Pos{-1, -1};
    
}

// void task1(){
//     auto lines = readFile("input.txt");
//     pipes = lines;

//     //find S
//     int x= 0;
//     int y= std::string::npos;
//     for(; x < pipes.size(); x++){
//         y = pipes[x].find('S');
//         if(y != std::string::npos) break;
//     }
//     std::cout <<"startpos" << x << " " << y << " " << std::endl;
//     Pos startPos = Pos{x, y};
//     Pos pos = findFirst(startPos);
    
//     int i = 1;
//     while(pos != startPos){
//         pos = getNext(pos);
//         i++;
//     }
//     std::cout << "result: " << i << " " << i/2 << std::endl;
// }


std::vector<std::vector<int>> isInside{};
std::vector<Pos> loopCoord{};

bool isInBound(Pos pos, std::vector<std::vector<int>> v){
    return pos.x >= 0 && pos.x < v.size() && pos.y >= 0 && pos.y < v[0].size();
}
bool posInVec(Pos p, std::vector<Pos> v){
    for(auto& vp : v){
        if(vp == p)
            return true;
    }
    return false;
}


void populateInside(Pos seed){
    if(posInVec(seed, loopCoord)) return;
    for(int i = -1; i <=1; i++){
        for(int j = -1; j <= 1; j++){
            int nx = seed.x+i;
            int ny = seed.y+j;
            auto p = Pos{nx, ny };
            if(!isInBound(p, isInside)) continue;
            if(isInside[p.x][p.y] == 1) continue;
            if(!posInVec(p, loopCoord)){
                isInside[p.x][p.y] = 1;
                populateInside(p);
            }
                
        }
    }
}

void task2(){
    auto lines = readFile("input.txt");
    // init insidemap
    for (auto & l : lines){
        isInside.push_back(std::vector<int>(l.size(), 0));
    }

        pipes = lines;

    //find S
    int x= 0;
    int y= std::string::npos;
    for(; x < pipes.size(); x++){
        y = pipes[x].find('S');
        if(y != std::string::npos) break;
    }
    std::cout <<"startpos" << x << " " << y << std::endl;
    Pos startPos = Pos{x, y};
    Pos pos = findFirst(startPos);   
    loopCoord.push_back(pos);

    //Get loop
    int i = 1;
    while(pos != startPos){
        pos = getNext(pos);
        loopCoord.push_back(pos);
        i++;
    }

    std::vector<Pos> searchSeeds{};
    // Assume counter clockwise rotation on loop, add all points next to loop-coord to seed list to find all inside points
    
    for(auto p : loopCoord){
        char c = getPipe(pos);
        Pos np;
        switch(p.dir){
            case north:
                np = Pos{p.x, p.y-1};
            break;
            case south:
                np = Pos{p.x, p.y+1};
            break;
            case east:
                np = Pos{p.x-1, p.y};
            break;
            case west:
                np = Pos{p.x+1, p.y};
            break;
            default:
                np = Pos{-1,-1};
        }
        searchSeeds.push_back(np);
        switch(c){
            case 'F':
                if(p.dir == east){
                    searchSeeds.push_back(Pos{p.x - 1, p.y});
                    searchSeeds.push_back(Pos{p.x - 1, p.y -1});
                    searchSeeds.push_back(Pos{p.x, p.y -1});
                }

            break;
            case 'J':
            if(p.dir == west){
                searchSeeds.push_back(Pos{p.x , p.y + 1});
                searchSeeds.push_back(Pos{p.x + 1, p.y + 1});
                searchSeeds.push_back(Pos{p.x + 1, p.y});
            }
            break;
            case 'L':
                if(p.dir = north){
                    searchSeeds.push_back(Pos{p.x + 1, p.y});
                    searchSeeds.push_back(Pos{p.x + 1, p.y - 1});
                    searchSeeds.push_back(Pos{p.x , p.y - 1});
                }

                
            break;
            case '7':
                if(p.dir = south){
                    searchSeeds.push_back(Pos{p.x, p.y + 1});
                    searchSeeds.push_back(Pos{p.x - 1, p.y + 1});
                    searchSeeds.push_back(Pos{p.x - 1 , p.y });
                }
                
            break;
            
        }
    }

    // find all inside points expanding from the seed list
    for(auto & s: searchSeeds){
        populateInside(s);
    }

    int sum = 0;

    for(auto & i: isInside){
        for(auto & j: i){
            std::cout << j << " ";
            if(j == 1)
                sum++;
        }
        std::cout << std::endl;
    }


    //print grid to file
    std::ofstream file;
    file.open ("grid.txt");
    std::vector<std::string> toPrint{};
    for(auto & lin : isInside){
        std::stringstream result;
        std::copy(lin.begin(), lin.end(), std::ostream_iterator<int>(result, ""));
        std::string r = result.str();
        std::replace(r.begin(), r.end(), '1', 'X');
        toPrint.push_back(r + "\n");
    }
    for(auto & p : loopCoord){
        toPrint[p.x][p.y] = getPipe(p);
    }
    for(auto & l : toPrint){
        file << l;
    }
    file.close();
    std:: cout << "SUM: " << sum << std::endl;
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