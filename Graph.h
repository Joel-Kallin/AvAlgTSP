//
//  Graph.h
//  TSP
//
//  Created by Joel Kallin Kilman on 2016-11-01.
//  Copyright © 2016 Joel Kallin Kilman. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

class Coord {
public:
    int name;
    double x;
    double y;
    
};

class Edge {
public:
    Coord from;
    Coord to;
    double cost;
};

bool intersection(Edge a, Edge b) {
    
    float x1 = a.from.x, x2 = a.to.x, x3 = b.from.x, x4 = b.to.x;
    float y1 = a.from.y, y2 = a.to.y, y3 = b.from.y, y4 = b.to.y;
    
    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0) return false;
    
    
    return true;
}

double dist(Coord from, Coord to)
{
    return std::sqrt(std::pow(std::abs(from.x-to.x),2.0) + std::pow(std::abs(from.y-to.y),2.0));
}

double dist(Edge a)
{
    return std::sqrt(std::pow(std::abs(a.from.x-a.to.x),2.0) + std::pow(std::abs(a.from.y-a.to.y),2.0));
}

double dist(Coord first, Coord second, Coord third, Coord fourth){
    return dist(first, second)+dist(third, fourth);
}

int findClosestVertex(Coord u, std::vector<Coord> V){
    
    int bestDist = std::numeric_limits<int>::max();
    int bestIndex = -1;
    
    for(int i = 0; i < V.size(); i++){
        
        if(dist(u, V[i])<bestDist){
            bestDist = dist(u, V[i]);
            bestIndex = i;
        }
    }
    
    return bestIndex;
}

double calculateTotalDistance(std::vector<Edge> path){
    double ret = 0;
    for(int i = 0; i < path.size(); i++){
        ret = ret + path[i].cost;
    }
    return ret;
}

void swap2(std::vector<Edge> &edges, int i , int j){
    
    Edge a = edges[i];
    Edge b = edges[j];
    
    edges[i].to = edges[j].from;
    
}

void removeCoord(Coord remove, std::vector<Coord>& list){
    for(int i = 0; i < list.size(); i++){
        if(list[i].name==remove.name){
            list.erase(list.begin()+i);
            return;
        }
    }
}



#endif /* Graph_h */
