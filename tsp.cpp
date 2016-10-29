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

double dist(Coord from, Coord to)
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

        std::cerr << "i: " << i << " j: " << j << " best index: " << best << std::endl;
        std::cerr << "places[best]: " << places[best].latitude << "," << places[best].longitude << std::endl;
        std::cerr << "old best: " << dist(places[tour[i]],places[best]) << std::endl;
        std::cerr << "new best: " << dist(places[tour[i]],places[j]) << std::endl;

        if(j==i){
          std::cerr << "j==i" << std::endl;
          //do nothing
        }

        /* base case, we have not used the node j so we add it as the best so far */
        else if(used[j]==false && best == -1){
          std::cerr << "used[j]==false && best==-1" << std::endl;
          best = j;
          used[best] = true;
          tour[i] = best;
          std::cerr << "best: " << best << " used[best] " << used[best] << " tour[i]" << tour[i] << std::endl;
        }

        /* if dist(i,j) < dist(i,best) then best = j */
        else if(dist(places[tour[i]],places[j]) < dist(places[tour[i]],places[best])) {
          std::cerr << "new best < old best" << std::endl;
          std::cerr << "old best: " << dist(places[tour[i]],places[best]) << std::endl;
          std::cerr << "new best: " << dist(places[tour[i]],places[j]) << std::endl;
          used[best] = false;
          best = j;
          used[best] = true;
          tour[i] = best;
        }


      }
  }

  for (int i = 0; i < len; i++){
    std::cout << tour[i] << std::endl;
  }

  return 0;

}
