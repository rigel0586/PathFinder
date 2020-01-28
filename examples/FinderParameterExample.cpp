/*
This example shows how an object of type FinderParameter is crated.
This class contains all steering parameters needed
*/

//c++
#include <iostream>
#include <cstdlib>
//pathfinder
#include "FinderParameter.h"

using namespace std;
using namespace pathfinder;

int main(int argc, char **argv)
{

  if(argc != 2)
    {
      cout<<"invoke like this: "<<endl;
      cout<<argv[0]<<" "<<"[track_type]"<<endl;
      cout<<"track_type = 0: Straight Line"<<endl;
      cout<<"track_type = 1: Helixsegment"<<endl;
      cout<<"track_type = 2: Curler"<<endl;

      return(1);
    }

  /*
  First one needs to define what kind of tracks one wants to find: straight line or helix.
  Depending on the track_type different Parameters need to be set
  */

  //create FinderParameter
  FinderParameter* myFinderParameter = 0;
    if(atoi(argv[1]) == 0)//straightline
      {
	//constructor FinderParameter(bool isStraightLine, bool isHelix)
	myFinderParameter = new FinderParameter(true, false);
	myFinderParameter->setFindCurler(false);
      }
    if(atoi(argv[1]) == 1)//straightline
      {
	myFinderParameter = new FinderParameter(false, true);
	myFinderParameter->setFindCurler(false);
      }
    if(atoi(argv[1]) == 2)//straightline
      {
	myFinderParameter = new FinderParameter(false, true);
	myFinderParameter->setFindCurler(true);
      }

    //use vertex constraint?
    //myFinderParameter -> setUseVertex(false);
    std::pair<double, double> vertex(3.4, 5.6);
    myFinderParameter -> setVertex(vertex);

    //set maximum allowed distance of hit to track
    myFinderParameter -> setMaxXYDistance(5.);
    myFinderParameter -> setMaxSZDistance(5.);

    //set maximum allowed distance of hit to track after fit
    myFinderParameter -> setMaxXYDistanceFit(5.);
    myFinderParameter -> setMaxSZDistanceFit(5.);

    //set minimum number of hits needed to build a track
    myFinderParameter -> setMinimumHitNumber(5);

    //set number of bins for hough space
    myFinderParameter -> setNumberXYThetaBins(200);
    myFinderParameter -> setNumberXYDzeroBins(200);
    myFinderParameter -> setNumberXYOmegaBins(200);
    myFinderParameter -> setNumberSZThetaBins(200);
    myFinderParameter -> setNumberSZDzeroBins(200);

    //circle: set maximum possible distance of center of circle to origin to still see a circle
    //straight line: set maximum distance of closest approach so that track can be detected
    myFinderParameter -> setMaxDxy(4000.);
    myFinderParameter -> setMaxDsz(4000.);

    //option to not only look for the maximum number of entries in hough space but also at the neighboring area
    myFinderParameter -> setSearchNeighborhood(false);

    //option to write hough space to a root tree
    //!!!FOR DEBUGGING ONLY!!!
    myFinderParameter -> setSaveRootFile(false);

    //FinderParameter can be printed
    myFinderParameter -> print();

    return(0);
}//int main(int argc, char **argv)
