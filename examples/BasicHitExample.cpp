/*
This example shows how objects of type basicHit are created
 */

//c++
#include <iostream>
//pathfinder
#include "basicHit.h"

using namespace std;
using namespace pathfinder;

int main(int argc, char **argv)
{

  //a hit has a positon in 3D space
  double x = 4.5;
  double y = 1.2;
  double z = 67.9;
  
  cout<<"Position of the Hit is: "<<x<<" "<<y<<" "<<z<<" "<<endl;

  //to construct the object, x- y- and z-positions are needed
  cout<<"Hit is being printed: "<<endl;
  basicHit myFirstBasicHit(x, y, z);
  
  //one can print the basicHit
  myFirstBasicHit.print();

  return(0);
}//int main(int argc, char **argv)
