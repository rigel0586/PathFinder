//c++
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <map>
#include <ctime>

//root
#include "TH1F.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"

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
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetFrameFillColor(kWhite);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFillColor(kWhite);
  gStyle->SetLegendBorderSize(1);

  unsigned int nevents = 1;  
  unsigned int ntracks = 200;
  double minPT = 10.;
  double maxPT = 50.;
  double minRadius = floor(1./calculateOmegaFromTransverseMomentum(minPT));
  double maxRadius = ceil(1./calculateOmegaFromTransverseMomentum(maxPT));
  
  cout<<"Range of radius: "<<minRadius<<" "<<maxRadius<<endl;

  TGraph* computingTimeGraph1 = new TGraph(ntracks);
  computingTimeGraph1->SetNameTitle("ComputingTimeOld","Computing Time Old");
  computingTimeGraph1->GetXaxis()->SetTitle("Number of Tracks");
  computingTimeGraph1->GetYaxis()->SetTitle("Computing Time in s");
  computingTimeGraph1->SetMarkerColor(kRed);
  computingTimeGraph1->SetLineColor(kRed);
  computingTimeGraph1->SetFillColor(kWhite);
  computingTimeGraph1->SetMarkerStyle(21);
  TGraph* computingTimeGraph2 = new TGraph(ntracks);
  computingTimeGraph2->SetNameTitle("ComputingTimeIntersection","Computing Time Intersection Method");
  computingTimeGraph2->GetXaxis()->SetTitle("Number of Tracks");
  computingTimeGraph2->GetYaxis()->SetTitle("Computing Time in s");
  computingTimeGraph2->SetMarkerColor(kBlue);
  computingTimeGraph2->SetLineColor(kBlue);
  computingTimeGraph2->SetFillColor(kWhite);
  computingTimeGraph2->SetMarkerStyle(22);
  TGraph* computingTimeGraph3 = new TGraph(ntracks);
  computingTimeGraph3->SetNameTitle("ComputingTimeIntersectionDistanceCut","Computing Time Intersection Method with Distance Cut");
  computingTimeGraph3->GetXaxis()->SetTitle("Number of Tracks");
  computingTimeGraph3->GetYaxis()->SetTitle("Computing Time in s");
  computingTimeGraph3->SetMarkerColor(kGreen+2);
  computingTimeGraph3->SetLineColor(kGreen+2);
  computingTimeGraph3->SetFillColor(kWhite);
  computingTimeGraph3->SetMarkerStyle(20);

  //loop over number of tracks
  for(unsigned int tracks = 1; tracks<=ntracks; tracks++)
    {
      cout<<"Number of tracks: "<<tracks<<endl;  
      //objects needed for track generation
      TGTrackParameterLimits* TrackParameterRanges = new TGTrackParameterLimits(-M_PI,
										M_PI,
										-300.,
										300.,
										minRadius,
										maxRadius,
										-10.,
										10.,
										-1000.,
										1000.);
  
      TGEventType* EventType = new TGEventType(100,
					       tracks,
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
      slFinderParameter -> setUseIntersections(false);
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
      slFinderParameter -> setSaveRootFile(false);

      FinderParameter* slFinderParameter2 = new FinderParameter(true, false);
      slFinderParameter2 -> setFindCurler(false);
      slFinderParameter2 -> setUseIntersections(true);
      slFinderParameter2 -> setMaxXYDistance(20.);
      slFinderParameter2 -> setMaxSZDistance(20.);
      slFinderParameter2 -> setMaxXYDistanceFit(10.);
      slFinderParameter2 -> setMaxSZDistanceFit(10.);
      slFinderParameter2 -> setMinimumHitNumber(5);
      slFinderParameter2 -> setNumberXYThetaBins(1000);
      slFinderParameter2 -> setNumberXYDzeroBins(1000);
      slFinderParameter2 -> setNumberXYOmegaBins(1000);
      slFinderParameter2 -> setNumberSZThetaBins(1000);
      slFinderParameter2 -> setNumberSZDzeroBins(1000);
      slFinderParameter2 -> setMaxDxy(5000);
      slFinderParameter2 -> setMaxDsz(5000);
      slFinderParameter2 -> setAllowedHitDistance(-1.);
      slFinderParameter2 -> setSearchNeighborhood(false);
      slFinderParameter2 -> setSaveRootFile(false);
      
      FinderParameter* slFinderParameter3 = new FinderParameter(true, false);
      slFinderParameter3 -> setFindCurler(false);
      slFinderParameter3 -> setUseIntersections(true);
      slFinderParameter3 -> setMaxXYDistance(20.);
      slFinderParameter3 -> setMaxSZDistance(20.);
      slFinderParameter3 -> setMaxXYDistanceFit(10.);
      slFinderParameter3 -> setMaxSZDistanceFit(10.);
      slFinderParameter3 -> setMinimumHitNumber(5);
      slFinderParameter3 -> setNumberXYThetaBins(1000);
      slFinderParameter3 -> setNumberXYDzeroBins(1000);
      slFinderParameter3 -> setNumberXYOmegaBins(1000);
      slFinderParameter3 -> setNumberSZThetaBins(1000);
      slFinderParameter3 -> setNumberSZDzeroBins(1000);
      slFinderParameter3 -> setMaxDxy(5000);
      slFinderParameter3 -> setMaxDsz(5000);
      slFinderParameter3 -> setAllowedHitDistance(100.);
      slFinderParameter3 -> setSearchNeighborhood(false);
      slFinderParameter3 -> setSaveRootFile(false);
      
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

	  std::clock_t start1 = std::clock();	  
	  HoughMap2Dint HoughSpace1(hitsForTrackFinding, *slFinderParameter);
	  computingTimeGraph1->SetPoint(tracks-1, tracks, ((std::clock() - start1) / (double)CLOCKS_PER_SEC));
	  //std::cout<<"clock1: "<< ((std::clock() - start1) / (double)CLOCKS_PER_SEC) <<" sec"<<std::endl;

	  std::clock_t start2 = std::clock();
	  HoughMap2DintIntersectionMethod HoughSpace2(hitsForTrackFinding, *slFinderParameter2);
	  computingTimeGraph2->SetPoint(tracks-1, tracks, ((std::clock() - start2) / (double)CLOCKS_PER_SEC));

	  std::clock_t start3 = std::clock();
	  HoughMap2DintIntersectionMethod HoughSpace3(hitsForTrackFinding, *slFinderParameter3);
	  computingTimeGraph3->SetPoint(tracks-1, tracks, ((std::clock() - start3) / (double)CLOCKS_PER_SEC));

	  //std::cout<<"clock2: "<< ((std::clock() - start2) / (double)CLOCKS_PER_SEC) <<" sec"<<std::endl;
	}//loop over events
      
      
      //clean up at the end
      delete TrackParameterRanges;
      delete EventType;
      delete DetType;
      delete TrackGen;
      delete slFinderParameter;

    }//for(unsigned int t = 1; t<=100; t++)

  TFile outputFile("ComputingTimeGraph.root", "recreate");
  TCanvas* computingTimeCanvas = new TCanvas("computingTimeCanvas","computingTimeCanvas",1);
  computingTimeCanvas->cd();
  computingTimeGraph1->GetXaxis()->SetTitle("Number of Tracks");
  computingTimeGraph1->GetYaxis()->SetTitle("Computing Time in s");
  computingTimeGraph1->GetYaxis()->SetTitleOffset(1.1);
  computingTimeGraph1->Draw("ap");
  computingTimeGraph2->Draw("p");
  computingTimeGraph3->Draw("p");
  TLegend* leg = computingTimeCanvas->BuildLegend(0.15,0.65,0.7,0.86);
  leg->SetFillColor(kWhite);
  computingTimeCanvas->Update();
  computingTimeCanvas->Write();
  computingTimeGraph1->Write();
  computingTimeGraph2->Write();
  outputFile.Close();

  delete computingTimeCanvas;
  delete leg;

  delete computingTimeGraph1;
  delete computingTimeGraph2;

  return 0;
}
