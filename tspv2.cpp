/*
1.   V = {1, ..., n-1}          // Vertices except for 0.
2.   U = {0}                    // Vertex 0.
3.   while V not empty
4.      u = most recently added vertex to U
5.      Find vertex v in V closest to u
6.      Add v to U and remove v from V.
7.   endwhile
8.   Output vertices in the order they were added to U
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <ctime>

using namespace std;

class Coord {
  public:
    int name;
    double latitude;
    double longitude;

};



double dist(Coord from, Coord to)
{
  return std::sqrt(std::pow(std::abs(from.latitude-to.latitude),2.0) + std::pow(std::abs(from.longitude-to.longitude),2.0));
}
//
// double dist(Edge a)
// {
//   return std::sqrt(std::pow(std::abs(a.from.latitude-a.to.latitude),2.0) + std::pow(std::abs(a.from.longitude-a.to.longitude),2.0));
// }

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

bool isSwapBetter(Coord p1, Coord p2, Coord p3, Coord p4){
  int currentDist= dist(p1, p2) + dist(p3, p4);
  int newDist = dist(p1, p3) + dist(p2, p4);
  if(newDist < currentDist) {
   return true;
 } else {
    return false;
  }
}


// double calculateTotalDistance(std::vector<Edge> path){
//   double ret = 0;
//   for(int i = 0; i < path.size(); i++){
//     ret = ret + path[i].cost;
//   }
//   return ret;
// }
//
// std::vector<Edge> swap2(std::vector<Edge> original, int i, int j){
//   std::vector<Edge> ret = original;
//   ret[i].to = original[j].from;
//   ret[j].from = original[i].to;
//   ret[i].cost = dist(ret[i]);
//   ret[j].cost = dist(ret[j]);
//
//   return ret;
// }

std::vector<Coord> twoSwap(int i, int k, std::vector<Coord>& route)
{
    //Take path[1] - path[i-1] and add them in order to the new route
    std::vector<Coord> newtour(route);

    //Take path[i] - path[k] and add them in reverse order for the new route
    int dec = 0;
    for(int j = i; j <= k; ++j){
        newtour[j] = route[k-dec];
    dec++;
    }
    //Take path[k+1] to end and add them in order to new_route
    return newtour;
/*
1.   V = {1, ..., n-1}          // Vertices except for 0.
2.   U = {0}                    // Vertex 0.
3.   while V not empty
4.      u = most recently added vertex to U
5.      Find vertex v in V closest to u
6.      Add v to U and remove v from V.
7.   endwhile
8.   Output vertices in the order they were added to U
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <ctime>
#include <stdlib.h>     /* srand, rand */

using namespace std;

class Coord {
public:
    int name;
    double x;
    double y;
    bool visited;
    // Coord* next;
    // Coord* prev;


};



double dist(Coord from, Coord to)
{
  return sqrt(pow(abs(from.x-to.x),2.0) + pow(abs(from.y-to.y),2.0));
}


int randomFreeCity(vector<Coord> U){
    int size = U.size();
    int i = rand() % size;
    while(U[i].visited){
        i++;
        i = i % size;
        //i = i % U.size();
    }
    return i;
}

//V:- aVailable
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

int findClosestVertex2(int node, vector<Coord>& U){
    double bestDist = std::numeric_limits<double>::max();
    int bestIndex = -1;
    for(int j=0; j < U.size(); j++){
        double jDist = dist(U[node], U[j]);
        if(!U[j].visited && (bestIndex==-1 || jDist < bestDist)){
            bestIndex = j;
            bestDist = jDist;
        }
    }
    return bestIndex;
}

//Checks if edge node - j is cheaper than going "around it"
//i.e. node - j+1- j :
double costOfInsertion(Coord node1, Coord node2, Coord node3){
    return dist(node1, node3) + dist(node3, node2) - dist(node1, node2);
}


// new_city doesnt belong to tour
// return the position in which new_city will be inserted in tour that will minimize the insertion cost for the tour
// Specifically we are looking for teh next node that will give us the lowest cost.
int find_minimum_triangular_distance_edge(int node, vector<int> route, vector<Coord> U){
    int nodePathPossition;
    unsigned int number_visited_cities(route.size());
    double bestCost = 99999;
    double currentCost;
    for(unsigned int j = 0; j < number_visited_cities-1; j++){
            //Checks if a current direct edge j - j+1 is cheaper than going "around it"
            //i.e. j - node - j+1 :
            currentCost = insertion_cost(U[route[j]], U[route[j+1]], U[node]);
            if(currentCost < bestCost){
                bestCost = currentCost;
                nodePathPossition = j+1;
            }
    }
    return nodePathPossition;
}



// double calculateTotalDistance(std::vector<Edge> path){
//   double ret = 0;
//   for(int i = 0; i < path.size(); i++){
//     ret = ret + path[i].cost;
//   }
//   return ret;
// }
//
// std::vector<Edge> swap2(std::vector<Edge> original, int i, int j){insertion_cost
//   std::vector<Edge> ret = original;
//   ret[i].to = original[j].from;
//   ret[j].from = original[i].to;
//   ret[i].cost = dist(ret[i]);
//   ret[j].cost = dist(ret[j]);
//
//   return ret;
// }

std::vector<Coord> twoSwap(int i, int k, std::vector<Coord>& route)
{
    //Take path[1] - path[i-1] and add them in order to the new route
    std::vector<Coord> newtour(route);

    //Take path[i] - path[k] and add them in reverse order for the new route
    int dec = 0;
    for(int j = i; j <= k; ++j){
        newtour[j] = route[k-dec];
    dec++;
    }
    //Take path[k+1] to end and add them in order to new_route
    return newtour;

}

vector<int> nnInsertion(vector<Coord>& U, int len){

    vector<int> route;


    //Currently the path is empty, intialise by picking a random node to build a route to base upon
    int node1 = rand() % len;
    route.push_back(node1);

    //Marks the coordinate as being used
    U[node1].visited = true;


    int node;
    node =  findClosestVertex2(node1, U);
    route.push_back(node);
    //U[node1].visited = true;
    //Initial path complete
    int nodeIndex;
    //Creates V for available nodes:
    // std::vector<Coord> V(U);
    // if(node1 < node) {
    //   V.erase(node);
    //   V.erase(node1);
    // }
    // else{
    //   V.erase(node1);
    //   V.erase(node);
    // }
    //Note that we alreaddy have used two nodes already; therefore i starts at 2

    for(int i = 1; i < len; i++){
      // TODO: Selection Random free city
      node = randomFreeCity(U);

      // TODO:
      nodeIndex = find_minimum_triangular_distance_edge(node, route, U);
      //TODO: IMPORTANT: CHECK IF YOU CAN REPLACE WITH route[j] = node; NOPE
      route.insert(route.begin() + nodeIndex, node);

      U[node].visited = true;
    }

    return route;
}

int main(){

  std::clock_t start = std::clock();
  int len = 0;
  std::cin >> len;

  //std::vector<Coord> V(len-1); //Tror vector gör new åt oss, annars ligger den på stacken

  std::vector<Coord> U(len);

  for(int i = 0; i < len; i++){
    std::cin >> U[i].x;
    std::cin >> U[i].y;
    U[i].name = i;
    U[i].visited = false;

  }

  //Begin Nearest Neighboor Insertion:
  if(len > 1){
  vector<int> route = nnInsertion(U, len);
  for (int i = 0; i < route.size(); i++){
    std::cout << route[i] << std::endl;
  }
} else{
  std::cout << U[0].name << std::endl;
}


//   //3-opt
//
//   //2-opt






//
//     //swap all nodes
// loopstart:
//   for(int i = 0; i < len-1; i++){
//     for(int j = i+1; j < len-1; j++){
//       if((std::clock()-start) / (double)CLOCKS_PER_SEC > (double)1.970) {goto finished;}
//       if(isSwapBetter(U[i], U[i+1], U[j], U[j+1])) {
//         U = twoSwap(i, j, U);
//         goto loopstart;
//       }
//     }
//   }
//
//   finished:

  /* Print path vector to console */
/*
  for (int i = 0; i < route.size(); i++){
    std::cout << route[i].from.name << "->" << route[i].to.name << std::endl;
    //if(i==route.size()-1) {std::cout << route[route.size()-1].to.name << std::endl;}
  }
*/






  return 0;
}

}
