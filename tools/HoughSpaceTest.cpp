//c++
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <map>

//root
#include "TH1F.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"

//pathfinder
#include "TrackGenerator.h"
#include "FinderParameter.h"
#include "HoughMap2Dint.h"
#include "HoughMap2DintIntersectionMethod.h"

using namespace std;
using namespace pathfinder;


double calculateTansverseMomentumFromOmega(double omega)
{
  double B = 3.5/*kg/A/s^2*/;
  double q = -1.60176565e-19/*A*s*/;
  double fpt = q*B/omega;
  fpt = fpt/(5.343e-19);//convert to GeV
  fpt = abs(fpt);//make sure all moment have the same sign

  return fpt/1000.;//Unanswered Question: why is the result wrong by a factor of 1000? It did work fine for the muons...
}

double calculateOmegaFromTransverseMomentum(double pt)
{
  double B = 3.5/*kg/A/s^2*/;
  double q = -1.60176565e-19/*A*s*/;
  double o = abs(q*B/pt/1000./5.343e-19);

  return o;
}


//main
int main(int argc, char**argv)
{
  unsigned int nevents = 1;  
  double minPT = 40.;
  double maxPT = 50.;
  double minRadius = floor(1./calculateOmegaFromTransverseMomentum(minPT));
  double maxRadius = ceil(1./calculateOmegaFromTransverseMomentum(maxPT));
  
  cout<<"Range of radius: "<<minRadius<<" "<<maxRadius<<endl;
  
  //objects needed for track generation
  TGTrackParameterLimits* TrackParameterRanges = new TGTrackParameterLimits(-2.,
									    -1.,
									    -300.,
									    300.,
									    minRadius,
									    maxRadius,
									    -10.,
									    10.,
									    -1000.,
									    1000.);
  
  TGEventType* EventType = new TGEventType(100,
					   10,
					   0,
					   0.001,
					   197);
  
  TGDetectorType* DetType = new TGDetectorType(-1000.,
					       1000.,
					       -500.,
					       500.,
					       -1000.,
					       1000.,
					       5.);
  
  //create Track Generator for curler
  TrackGenerator* TrackGen = new TrackGenerator(2 , *TrackParameterRanges, *EventType, *DetType); 

//finder parameter
  FinderParameter* slFinderParameter = new FinderParameter(true, false);
  slFinderParameter -> setFindCurler(false);
  slFinderParameter -> setUseIntersections(true);
  slFinderParameter -> setMaxXYDistance(20.);
  slFinderParameter -> setMaxSZDistance(20.);
  slFinderParameter -> setMaxXYDistanceFit(10.);
  slFinderParameter -> setMaxSZDistanceFit(10.);
  slFinderParameter -> setMinimumHitNumber(5);
  slFinderParameter -> setNumberXYThetaBins(1000);
  slFinderParameter -> setNumberXYDzeroBins(1000);
  slFinderParameter -> setNumberXYOmegaBins(1000);
  slFinderParameter -> setNumberSZThetaBins(1000);
  slFinderParameter -> setNumberSZDzeroBins(1000);
  slFinderParameter -> setMaxDxy(5000);
  slFinderParameter -> setMaxDsz(5000);
  slFinderParameter -> setAllowedHitDistance(-1.);
  slFinderParameter -> setSearchNeighborhood(false);
  slFinderParameter -> setSaveRootFile(true);
  

  //loop over events to be created
  for(unsigned int e = 0; e<nevents; e++)
    {
      //generate an event
      TrackGen->generateTracks(e);
      
      //get the simulated tracks and hits
      vector<TrackFinderTrack*> simtracks = TrackGen->getGeneratorTracks();
      vector<basicHit> allhits = TrackGen->getHits();


      //check that simulation worked
      //	printSimTracks(simtracks);
      
      //do some cleaning up of the hits
      //if the radius is large tha the size of the pad plane in y remove one half of the circle (to be closer to ILD track)
      //1.) create a vector containing all hits thatshould be removed before track finding.
      vector<basicHit> hitsForTrackFinding;
      vector<TrackFinderTrack> simTracksHitsRemoved;
      double yDetRange = DetType->getPadPlaneYmax() - DetType->getPadPlaneYmin();
      for(unsigned int t = 0; t<simtracks.size(); t++)
	{
	  //fill histograms with simulated radius
	  TrackParameterFull simTrackParam = simtracks[t]->getTrackParameter();
	  double omega = simTrackParam.getOmega();
	  float radius = 1/omega;
	  
	  if(radius > yDetRange)
	    {
	      //get hits on sim track to check which should be kept
	      vector<basicHit> simHits = simtracks.at(t)->getHitsOnTrack();
	      map<double,int> yPosInvestigated;
	      vector<basicHit> hitsForTrackFindingOnCurrentTrack;
	      for(unsigned int s = 0; s<simHits.size(); s++)
		{
		  double currentHitY = simHits.at(s).getY();
		  //find all hit with current y hit position
		  basicHit* hitToBeAdded = new basicHit(1e40,1e40,1e40);
		  if(yPosInvestigated.find(currentHitY) == yPosInvestigated.end())
		    {
		      //cout<<"Hits with y = "<<currentHitY<<endl;
		      
		      for(unsigned int s1 = s; s1< simHits.size(); s1++)
			{
			  if( fabs(simHits.at(s1).getY() - currentHitY) < 1e-10)
			    {
			      //simHits.at(s1).print();
			      if(fabs(simHits.at(s1).getX())<fabs(hitToBeAdded->getX()))
				{
				  hitToBeAdded = new basicHit(simHits.at(s1));
				}
			    }
			  yPosInvestigated.insert(make_pair(currentHitY,1));			}
		    
		      
		      //hitToBeAdded->print();
		      hitsForTrackFinding.push_back(*hitToBeAdded);
		      hitsForTrackFindingOnCurrentTrack.push_back(*hitToBeAdded);
		      delete hitToBeAdded;	
		    }
		    
		}//for(unsigned int s = 0; s<simHits.size(); s++)
	      //create a new TrackFinderTrack
	      TrackFinderTrack tmpTrack(simTrackParam , hitsForTrackFindingOnCurrentTrack);
	      simTracksHitsRemoved.push_back(tmpTrack);
	      
	    }//if(radius > yDetRange)
	  else
	    {
	      simTracksHitsRemoved.push_back(*simtracks.at(t));
	    }
	}//for(unsigned int t = 0; t<simtracks.size(); t++)

      HoughMap2DintIntersectionMethod HoughSpace(hitsForTrackFinding, *slFinderParameter);
      //HoughMap2Dint HoughSpace(hitsForTrackFinding, *slFinderParameter);
      
    }//loop over events
  
  //clean up at the end
  delete TrackParameterRanges;
  delete EventType;
  delete DetType;
  delete TrackGen;
  delete slFinderParameter;
  
  return 0;
}
