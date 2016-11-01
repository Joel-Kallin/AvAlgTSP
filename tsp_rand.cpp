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
#include <random>

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

  std::vector<Coord> X(len);

  std::vector<Coord> U(0);

/*
  std::cin >> U[0].latitude;
  std::cin >> U[0].longitude;
  U[0].name = 0;
  */

  for(int i = 0; i < len; i++){
      std::cin >> X[i].latitude;
      std::cin >> X[i].longitude;
      X[i].name = i;
  }
/*
  for (int i = 0; i < len-1; i++) {
      std::cerr << X[i].latitude << " " << X[i].longitude << " " << X[i].name << std::endl;
  }*/
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0,len);

  int v1 = distribution(generator);
  std::cerr << "rand is: " << v1 <<" len is: "<< len << std::endl;
  //std::cerr << "shuffling" << std::endl;

  //std::random_shuffle(X.begin(),X.end());
/*
  for (int i = 0; i < len-1; i++) {
      std::cerr << X[i].latitude << " " << X[i].longitude << " " << X[i].name << std::endl;
  }*/

  U.push_back(X[v1]);
  std::cerr << "pushing back: " << U[0].name << std::endl;

  X.erase(X.begin()+v1);
  //std::cerr << "erased" << std::endl;


/*
  for (int i = 0; i < len-1; i++) {
      std::cerr << V[i].latitude << " " << V[i].longitude << " " << V[i].name << std::endl;
  }
*/

  while(X.size()!=0){
    /*
    std::cerr << "size: " << V.size() << std::endl;
    */
    Coord u = U.back();
    /*
    std::cerr << "examining: " << u.name << std::endl;
    */
    int index = findClosestVertex(u, X);
    /*
    std::cerr << "closest: " << V[index].name << std::endl;
    std::cerr << "U.size before: " << U.size() << std::endl;
    */
    U.push_back(X[index]);
    /*
    std::cerr << "adding node " << U.back().name << std::endl;
    std::cerr << "U.size after: " << U.size() << std::endl;
    std::cerr << "V.size before: " << V.size() << std::endl;
    */
    X.erase(X.begin()+index);
    /*
    std::cerr << "V.size after: " << V.size() << std::endl;
    */
  }

  /* Print path vector to console */
  for (int i = 0; i < len; i++){
    std::cout << U[i].name << std::endl;
  }


  return 0;
}
