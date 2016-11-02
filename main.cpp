//
//  main.cpp
//  TSP
//
//  Created by Joel Kallin Kilman on 2016-11-01.
//  Copyright © 2016 Joel Kallin Kilman. All rights reserved.
//

#include <iostream>
#include "Graph.h"
#include <string>
#include <vector>
#include <limits>
#include <ctime>
#include <algorithm>
#include <queue>

using namespace std;

int main(int argc, const char * argv[]) {

    std::clock_t start = std::clock();
    int len = 0;
    std::cin >> len;
    
    std::vector<Coord> V(len-1);
    std::vector<Coord> U(1);
    
    
    std::cin >> U[0].x;
    std::cin >> U[0].y;
    U[0].name = 0;
    
    for(int i = 0; i < len-1; i++){
        std::cin >> V[i].x;
        std::cin >> V[i].y;
        V[i].name = i+1;
    }
    
    int counter = 0;
    
    while(V.size()!=0){
        
        Coord u = U.back();
        
        if(counter>0){
            u.prev = &U[counter-1];
        }
        
        int index = findClosestVertex(u, V);
        
        U.push_back(V[index]);
        
        u.next = &U[counter];
        
        counter++;
        
        V.erase(V.begin()+index);
        
    }
    
    //2-opt
    
    std::vector<bool> inQue(0);
    
    std::vector<Coord> remaining(0);
    
    std::queue<Coord> swappable;
    
    for(int i = 0; i < U.size(); i++){
        swappable.push(U[i]);
        inQue.push_back(true);
        remaining.push_back(U[i]);
    }
    
    while(swappable.size()>0){
        
        Coord current = swappable.front();
        swappable.pop();
        
        removeCoord(current, remaining);
        inQue[current.name] = false;
        
        for(int i = 0; i < remaining.size(); i++){
            if(isSwapBetter(current, *current.next, *remaining[i].prev, remaining[i])){
                U = twoSwap(current.name, remaining[i].prev->name, len, U);
            }
        }
    }
    
     
    
    /* Print path vector to console */
    
    for (int i = 0; i < U.size(); i++){
        std::cout << U[i].name << std::endl;
    }
    
    
    
    
    return 0;
}
