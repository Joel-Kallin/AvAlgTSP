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
};



double dist(Coord from, Coord to)
{
  return sqrt(pow(abs(from.x-to.x),2.0) + pow(abs(from.y-to.y),2.0));
}

double routeDist(std::vector<Coord>& places, std::vector<int>& route, int len)
{
  double sum = 0.0;
  for(int i = 0; i < len-1; i++){
    sum += sqrt(pow(abs(places[route[i]].x-places[route[i+1]].x),2.0) + pow(abs(places[route[i]].y-places[route[i+1]].y),2.0));
  }
  return sum;
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
double insertionCost(Coord node1, Coord node2, Coord node3){
  return dist(node1, node3) + dist(node3, node2) - dist(node1, node2);
}



int minimumNodeInsertion(int node, vector<int> route, vector<Coord> U){
  int nodePathPossition;
  unsigned int size(route.size());
  double bestCost = std::numeric_limits<double>::max();
  double currentCost;
  for(unsigned int j = 0; j < size-1; j++){
    //Checks if a current direct edge j - j+1 is cheaper than going "around it"
    //i.e. j - node - j+1 :
    currentCost = insertionCost(U[route[j]], U[route[j+1]], U[node]);
    if(currentCost < bestCost){
      bestCost = currentCost;
      nodePathPossition = j+1;
    }
  }
  return nodePathPossition;
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

std::vector<int> twoSwap(int i, int k, std::vector<int>& route)
{
  //Take path[1] - path[i-1] and add them in order to the new route
  std::vector<int> newtour(route);

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
  int node1 = randomFreeCity(U);
  route.push_back(node1);

  //Marks the coordinate as being used
  U[node1].visited = true;


  int node;
  node = findClosestVertex2(node1, U);
  route.push_back(node);
  //U[node1].visited = true;
  //Initial path complete
  int nodeIndex;

  for(int i = 1; i < len; i++){
    // TODO: Selection Random free city
    node = randomFreeCity(U);

    // TODO:
    nodeIndex = minimumNodeInsertion(node, route, U);
    //TODO: IMPORTANT: CHECK IF YOU CAN REPLACE WITH route[j] = node; NOPE
    route.insert(route.begin() + nodeIndex, node);

    U[node].visited = true;
  }

  return route;
}

int main()
{
  std::clock_t c_start = std::clock();
  //initiate the randomizer
  srand(time(NULL));
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
    //Initate 2-opt:
    int improve = 0;
    // double best = routeDist(U, route, len);
    while(improve < 20) {
      start:
      if((std::clock() - c_start) / (double)CLOCKS_PER_SEC  >= (double)1.990) goto finished;
      //int best = routeDist(places, tour, len);
      for(int i = 1; i < len; i++){
        for(int j = i+1; j < len-1; j++){
          if((std::clock() - c_start) / (double)CLOCKS_PER_SEC > (double)1.980) goto finished;
          // std::vector<int> newroute(twoSwap(i, j, route));
          // double newDist = routeDist(U, newroute, len);
          // if(newDist < best){
          //   route = newroute;
          //   best = newDist;
          //   improve= 0;
          // }
          if(isSwapBetter(U[route[i-1]], U[route[i]], U[route[j]], U[route[j+1]])) {
              route = twoSwap(i, j, route);
              improve = 0;
              // goto start;
          }
        }
      }
      improve++;
    }

    finished:
    for (int i = 0; i < route.size(); i++){
      std::cout << route[i] << std::endl;
    }
  } else{
    std::cout << U[0].name << std::endl;
  }

return 0;
}
