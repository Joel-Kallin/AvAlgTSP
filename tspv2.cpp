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

class Edge {
  public:
    Coord from;
    Coord to;
    double cost;
};

double dist(Coord from, Coord to)
{
  return std::sqrt(std::pow(std::abs(from.latitude-to.latitude),2.0) + std::pow(std::abs(from.longitude-to.longitude),2.0));
}

double dist(Edge a)
{
  return std::sqrt(std::pow(std::abs(a.from.latitude-a.to.latitude),2.0) + std::pow(std::abs(a.from.longitude-a.to.longitude),2.0));
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

std::vector<Edge> swap2(std::vector<Edge> original, int i, int j){
  std::vector<Edge> ret = original;
  ret[i].to = original[j].from;
  ret[j].from = original[i].to;
  ret[i].cost = dist(ret[i]);
  ret[j].cost = dist(ret[j]);

  return ret;
}

std::vector<Coord> findEligibleNodes();

int main(){

  std::clock_t start = std::clock();
  int len = 0;
  std::cin >> len;

  std::vector<Coord> V(len-1); //Tror vector gör new åt oss, annars ligger den på stacken

  std::vector<Coord> U(1);

  std::vector<Edge> route(0);

  std::cin >> U[0].latitude;
  std::cin >> U[0].longitude;
  U[0].name = 0;

  for(int i = 0; i < len-1; i++){
      std::cin >> V[i].latitude;
      std::cin >> V[i].longitude;
      V[i].name = i+1;
  }
/*
  for (int i = 0; i < len-1; i++) {
      std::cerr << V[i].latitude << " " << V[i].longitude << " " << V[i].name << std::endl;
  }
*/
  int counter = 0;

  while(V.size()!=0){
    /*
    std::cerr << "size: " << V.size() << std::endl;
    */
    Coord u = U.back();
    /*
    std::cerr << "examining: " << u.name << std::endl;
    */
    int index = findClosestVertex(u, V);
    /*
    std::cerr << "closest: " << V[index].name << std::endl;
    std::cerr << "U.size before: " << U.size() << std::endl;
    */
    U.push_back(V[index]);
    Edge e;
    e.from = U[counter];
    e .to = U[counter+1];
    e.cost = dist(e.from, e.to);
    route.push_back(e);
    counter++;
    /*
    std::cerr << "adding node " << U.back().name << std::endl;
    std::cerr << "U.size after: " << U.size() << std::endl;
    std::cerr << "V.size before: " << V.size() << std::endl;
    */
    V.erase(V.begin()+index);
    /*
    std::cerr << "V.size after: " << V.size() << std::endl;
    */
  }

  //2-opt

    //swap all nodes

  for(int i = 0; i < route.size()-1; i++){
    for(int j = 0; j < route.size(); j++){
      if(std::clock()-start / (double)CLOCKS_PER_SEC >= (double)1.800) {goto finished;}
      if(calculateTotalDistance(swap2(route, i, j))<calculateTotalDistance(route)) {
        route = swap2(route, i, j);
      }
    }
  }

  finished:

  /* Print path vector to console */

  for (int i = 0; i < route.size(); i++){
    std::cout << route[i].from.name << "->" << route[i].to.name << std::endl;
    //if(i==route.size()-1) {std::cout << route[route.size()-1].to.name << std::endl;}
  }


/*
  for (int i = 0; i < len; i++){
    std::cout << U[i].name << std::endl;
  }
  */



  return 0;
}
