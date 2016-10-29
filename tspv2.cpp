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

int main(){

  int len = 0;
  std::cin >> len;

  std::vector<Coord> V(len-1); //Tror vector gör new åt oss, annars ligger den på stacken

  std::vector<Coord> U(len);

  std::vector<bool> used(len);

  std::vector<int> tour(len);

  std::cin >> U[0].latitude;
  std::cin >> U[0].longitude;
  U[0].name = 0;

  for(int i = 0; i < len-1; i++){
      std::cin >> V[i].latitude;
      std::cin >> V[i].longitude;
      V[i].name = i+1;
  }

  while(V.size()!=0){
    Coord u = U.back();
    int index = findClosestVertex(u, V);
    U.push_back(V[index]);
    V.erase(V.begin()+index);
  }

  for (int i = 0; i < len; i++){
    std::cout << U[i].name << std::endl;
  }


  return 0;
}
