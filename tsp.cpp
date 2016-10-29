//Implement everything here

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class Coord {
  public:
    double latitude;
    double longitude;

};

int dist(Coord from, Coord to)
{
  return std::sqrt(std::pow(std::abs(from.latitude-to.latitude),2.0) + std::pow(std::abs(from.longitude-to.longitude),2.0));
}

int main()
{
  int len = 0;
  std::cin >> len;

  std::cerr << "Number of places is " << len << std::endl;

  std::vector<Coord> places(len); //Tror vector gör new åt oss, annars ligger den på stacken

  std::vector<bool> used(len);

  std::vector<int> tour(len);
  //Coord* places = new Coord[len]; //malloced, need to be deleted to avoid mem leaks

  for(int i = 0; i < len; i++){
      std::cin >> places[i].latitude;
      std::cin >> places[i].longitude;
  }

  for (int i = 0; i < len; i++) {
      std::cerr << places[i].latitude << " " << places[i].longitude << std::endl;
  }


  //std::cerr << "Testing the distance function " << dist(places[1], places[4]) << std::endl;

  for (int i = 0; i < len; i++) {
      int best = -1;
      for (int j = 0; j < len; j++) {

        /* if places[j] is not used and best is not
        initilized or distance between i-1 and j < i-1 and best */
        if(used[j]==false && (best == -1 || dist(places[tour[i-1]],places[j]) < dist(places[tour[i-1]],places[best]))) {
          best = j;
        }
        //std::cerr << i << " " << j << " " << std::endl;
        tour[i] = best;
        if(best!=-1){
          used[best] = true;
        }
      }
  }

  for (int i = 0; i < len; i++){
    std::cout << tour[i] << std::endl;
  }

  return 0;

}
