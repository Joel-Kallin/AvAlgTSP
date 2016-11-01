//Implement everything here

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>


using namespace std;
class Coord {
  public:
    double latitude;
    double longitude;

};

int dist(Coord from, Coord to)
{
  return std::sqrt(std::pow(std::abs(from.latitude-to.latitude),2.0) + std::pow(std::abs(from.longitude-to.longitude),2.0));
}

int routeDist(std::vector<Coord>& places, std::vector<int>& tour, int len)
{
	int sum = 0;
	for(int i = 0; i < len-1; i++){
		sum += sqrt(pow(abs(places[tour[i]].latitude-places[tour[i+1]].latitude),2.0) + pow(sabs(places[tour[i]].longitude-places[tour[i+1]].longitude),2.0));
	}
	return sum;
}

std::vector<int> twoSwap(int i, int k, int len, std::vector<int>& tour)
{
	//Take path[1] - path[i-1] and add them in order to the new route
	std::vector<int> newtour(tour);

	//Take path[i] - path[k] and add them in reverse order for the new route
	int dec = 0;
	for(int j = i; j <= k; ++j){
		newtour[j] = tour[k-dec];
		dec++;
	}
	//Take path[k+1] to end and add them in order to new_route
	return newtour;

}


int main()
{
  std::clock_t c_start = std::clock();
  int len = 0;
  std::cin >> len;

  //std::cerr << "Number of places is " << len << std::endl;

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
          tour[i] = best;
        }
        //std::cerr << i << " " << j << " " << std::endl;

      }
      //if(best != -1){
      used[best] = true;
      //}
  }
  //2-opt
  int improve = 0;
  while(improve < 20) {
	start:
	if((std::clock() - c_start) / (double)CLOCKS_PER_SEC  >= (double)1.990) goto answer;
	int best = routeDist(places, tour, len);
	for(int i = 0; i < len-1; i++){
		for(int k = i+1; k < len; k++){
		if((std::clock() - c_start) / (double)CLOCKS_PER_SEC >= (double)1.970) goto answer;
		std::vector<int> newtour(twoSwap(i, k, len, tour));
		int newBest = routeDist(places, newtour, len);
		if(newBest < best){
			improve= 0;
			tour = newtour;
			best = newBest;
			goto start;
			}
		}
	}
	improve++;
  }

  answer:
  for (int i = 0; i < len; i++){
    std::cout << tour[i] << std::endl;
  }

  //print out cost
  //std::cout << "Cost of route is: " << routeDist(places, tour, len) << std::endl;

  return 0;

}
