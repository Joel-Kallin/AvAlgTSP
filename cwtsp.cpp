/*
1.   Identify a hub vertex h
2.   VH = V - {h}
3.   for each i,j != h
4.      compute savings(i,j)
5.   endfor
6.   sortlist = Sort vertex pairs in decreasing order of savings
7.   while |VH| > 2
8.      try vertex pair (i,j) in sortlist order
9.      if (i,j) shortcut does not create a cycle
           and degree(v) ≤ 2 for all v
10.          add (i,j) segment to partial tour
11.          if degree(i) = 2
12.             VH =  VH - {i}
13.          endif
14.          if degree(j) = 2
15.             VH =  VH - {j}
16.          endif
17.     endif
18.  endwhile
19.  Stitch together remaining two vertices and hub into final tour
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
    std::vector<int> neighbours;
};

class Edge {
  public:
    int from;
    int to;
    int savings;
};

/*
  function to sort
*/
bool order (Edge i,Edge j) { return (i.savings>j.savings); }

/*
  Calculate the distance from node 'from' to node 'to'
*/
double dist(Coord from, Coord to)
{
  return std::sqrt(std::pow(std::abs(from.latitude-to.latitude),2.0) + std::pow(std::abs(from.longitude-to.longitude),2.0));
}

/*
  Calculate the degree of vertex i in graph V
*/
int degree(std::vector<Coord> V, int i){
  return V[i].neighbours.size();
}

/*
  Calculate the maximum degree for a graph V
*/
int maxDegree(std::vector<Coord> V) {
  int max = std::numeric_limits<int>::max();
  for (int i = 0; i < V.size(); i++){
    if(max>degree(V, i)){
      max = degree(V, i);
    }
  }
  return max;
}

/*
  Given a vertex u, find it's closes neighbour
*/
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

/*
  Check if there is already an Edge i -> j or j -> i
*/
bool noEdge(int i, int j, std::vector<Edge> edges){
  for(int k = 0; k < edges.size(); k++){
    if((edges[k].from==i&&edges[k].to==j)||(edges[k].from==j&&edges[k].to==i)){
      return true;
    }
  }
  return false;
}

/*
  Calculate the distance from a node source to all it's neighbours
*/
int sumDist(std::vector<Coord> V, int source){
  int sum = 0;
  for(int i = 0; i < V.size(); i++){
    if(i != source){
      sum += 2*dist(V[source], V[i]);
    }
  }
  return sum;
}

/*
  Find the 'hub' of a graph by calculating which vertex has the
  lowest sum distance to all it's neighbours
*/
int findHub(std::vector<Coord> V){
  int min = std::numeric_limits<int>::max();
  int ret = -1;
  for(int i = 0; i < V.size(); i++){
    if (sumDist(V, i) < min){
      min = sumDist(V, i);
      ret = i;
    }
  }
  return ret;
}

/*
  Calculate the savings of taking the shortcut from first to second
  as dist(hub, first) + dist(hub, second) - dist(first, second)
*/
double computeSavings(Coord first, Coord second, Coord hub){
  return dist(first, hub)+dist(second, hub)-dist(first, second);
}

/*
  We initialize the neighbours by adding every node i != h as a neighbour
  to h, and h as neihgbour to every other node i.
*/
void initializeNeighbours(std::vector<Coord> &V, int h){
  for(int i = 0; i < V.size(); i++){
    if(i!=h){
      V[i].neighbours.push_back(h);
    } else {
      V[h].neighbours.push_back(i);
    }
  }
}

/*
  find an int n in a vector V of ints,
  returns -1 if n is not found in V
*/
int find(std::vector<int> V, int n){
  for (int i = 0; i < V.size(); i++){
    if (V[i] == n) return i;
  }
  return -1;
}

/*
  Remove a node n from a graph V
*/
void removeNode(std::vector<Coord> &V, int n){
  //for every neighbour of n
  for (int i = 0; i < V[n].neighbours.size(); i++){
    //remove n as neighbour of i
    int index = find(V[i].neighbours, n);
    if(index == -1){
      std::cerr << "Could not find: " << n << std::endl << std::endl;
    } else {
      V[i].neighbours.erase(V[i].neighbours.begin()+index);
    }
  }
  std::cerr << "Erasing: " << (V.begin()+n)->name << std::endl << std::endl;
  V.erase(V.begin()+n);
}

int main(){

  int len = 0;

  std::cin >> len;

  std::vector<Coord> V(len);

  std::vector<bool> visited(0);

  std::vector<int> tour(0);

  for(int i = 0; i < len; i++){
      std::cin >> V[i].latitude;
      std::cin >> V[i].longitude;
      V[i].name = i;
      visited.push_back(false);
  }

  std::cerr << "Nodes in problem: " << len << std::endl << std::endl;

  for (int i = 0; i < len; i++) {
      std::cerr << "lat: " << V[i].latitude << " long: " << V[i].longitude << " name: " << V[i].name << std::endl << std::endl;
  }

  //Identify a hub vertex h
  int hubVertex = findHub(V);
  std::cerr << "hub: " << hubVertex << std::endl << std::endl;

  initializeNeighbours(V, hubVertex);

  //VH = V - {h}
  std::vector<Coord> VH(0);

  for (int i = 0; i < len; i++){
    if(V[i].name!=hubVertex){
        VH.push_back(V[i]);
    }
  }

  std::cerr << "VH: " << hubVertex << std::endl << std::endl;
  for (int i = 0; i < VH.size(); i++) {
    std::cerr << "lat: " << VH[i].latitude << " long: " << VH[i].longitude << " name: " << VH[i].name << std::endl << std::endl;
  }

  //for each i,j != h
  std::vector<Edge> savings(0);

  for (int i = 0; i < VH.size(); i++){
    for (int j = 0; j < VH.size(); j++){
        //compute savings(i,j)
        if(i!=j){
          Edge e;
          e.from = i;
          e.to = j;
          e.savings = computeSavings(V[i],V[j],V[hubVertex]);
          savings.push_back(e);
        }
    }
  }

  //sortlist = Sort vertex pairs in decreasing order of savings
  std::sort (savings.begin(), savings.end(), order);

  std::cerr << "Savings: "<< std::endl << std::endl;
  for (int i = 0; i < savings.size(); i++) {
    std::cerr << "from: " << savings[i].from << " to: " << savings[i].to << " saving: " << savings[i].savings << std::endl << std::endl;
  }

  int i;
  int j;
  int counter;
  //while |VH| > 2
  while(VH.size()>2){
    std::cerr << "VH.size()= "<< VH.size() << std::endl << std::endl;
    std::cerr << "counter: "<< counter << std::endl << std::endl;
    //try vertex pair (i,j) in sortlist order
    i = savings[counter].from;
    j = savings[counter].to;
    std::cerr << "examining "<< i << "->" << j << std::endl << std::endl;
    std::cerr << "visited[i]: "<< visited[i] << std::endl << std::endl;
    std::cerr << "visited[j]: "<< visited[j] << std::endl << std::endl;
    std::cerr << "maxDegree(VH): "<< maxDegree(VH) << std::endl << std::endl;
    //if (i,j) shortcut does not create a cycle and degree(v) ≤ 2 for all v
    if(!(visited[i]==true&&visited[j]==true)&&maxDegree(VH)<=2){
      std::cerr << "if.. " << std::endl << std::endl;

      //add (i,j) segment to partial tour
      tour.push_back(i);
      tour.push_back(j);
      visited[i] = true;
      visited[j] = true;
      VH[i].neighbours.push_back(j);
      VH[j].neighbours.push_back(i);
      //if degree(i) = 2
      if(degree(VH,i)>=2){
        std::cerr << "degree(VH,i)= "<< degree(VH,i) << std::endl << std::endl;
        //VH =  VH - {i}
        std::cerr << "VH.size() " << VH.size() << std::endl << std::endl;
        std::cerr << "removing" << std::endl << std::endl;
        removeNode(VH, i);
        std::cerr << "VH.size() " << VH.size() << std::endl << std::endl;
      }
      //if degree(j) = 2
      if(degree(VH,j)>=2){
        //VH =  VH - {j}
        std::cerr << "degree(VH,j)= "<< degree(VH,j) << std::endl << std::endl;
        std::cerr << "VH.size() " << VH.size() << std::endl << std::endl;
        std::cerr << "removing" << std::endl << std::endl;
        removeNode(VH, j);
        std::cerr << "VH.size() " << VH.size() << std::endl << std::endl;
      }
    }
    std::cerr << "counter: " << counter+1 << std::endl << std::endl;
    counter++;
  }
  //Stitch together remaining two vertices and hub into final tour

  /* Print path vector to console */
  for (int i = 0; i < len; i++){
    std::cout << tour[i]<< std::endl;
  }


  return 0;
}
