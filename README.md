# Project1-AvAlg
Project 1 for the advanced algorithms course

Input
Your program should take as input a single TSP instance. It will be run several times, once for every test case. The time limit is per test case.

The first line of standard input contains an integer 1≤N≤10001≤N≤1000, the number of points. The following NN lines each contain a pair of real numbers x,yx,y giving the coordinates of the NN points. All numbers in the input have absolute value bounded by 106106.

The distance between two points is computed as the Euclidean distance between the two points, rounded to the nearest integer.

Output
Standard output should consist of NN lines, the ii’th of which should contain the (0-based) index of the ii’th point visited.

Score
Let OptOpt be the length of an optimal tour, ValVal be the length of the tour found by your solution, and NaiveNaive be the length of the tour found by the algorithm below. Define x=(Val−Opt)/(Naive−Opt)x=(Val−Opt)/(Naive−Opt). (In the special case that Naive=OptNaive=Opt, define x=0x=0 if Val=OptVal=Opt, and x=∞x=∞ if Val>OptVal>Opt.)

The score on a test case is 0.02x0.02x. Thus, if your tour is optimal, you will get 11 point on this test case. If your score is halfway between NaiveNaive and OptOpt, you get roughly 0.140.14 points. The total score of your submission is the sum of your score over all test cases. There will be a total of 5050 test cases. Thus, an implementation of the algorithm below should give a score of at least 11 (it will get 0.020.02 points on most test cases, and 1.01.0 points on some easy cases where it manages to find an optimal solution).

The algorithm giving the value NaiveNaive is as follows:


GreedyTour
   tour[0] = 0
   used[0] = true
   for i = 1 to n-1
      best = -1
      for j = 0 to n-1
         if not used[j] and (best = -1 or dist(tour[i-1],j) < dist(tour[i-1],best))
            best = j
      tour[i] = best
      used[best] = true
   return tour


The sample output gives the tour found by GreedyTour on the sample input. The length of the tour is 323. See sample output in seperate files.
