//c++
#include <iostream>
#include <vector>
#include <cmath>
//pathfinder
//#include "FinderParameter.h"
//#include "HoughTrafoTrackFinder.h"
#include "TrackGenerator.h"
#include "basicHit.h"
#include "TrackParameterFull.h"
#include "FinderParameter.h"
#include "HoughTrafoTrackFinder.h"
#include "TrackFinderTrack.h"

using namespace std;
using namespace pathfinder;

void printUsage(char **argv)
{
  cout<< "invoke like this:" << endl;
  cout<< argv[0] << " [steeringfilename_trackgeneration.txt] [steeringfilename_trackfinding.txt]"<<endl;
  cout<<"*******************"<<endl;
  cout<< "Example steeringfilename_trackgeneration.txt: "<<endl;
  cout<<"tracktype 2"<<endl;
  cout<<"nevents 10"<<endl;
  cout<<"ntracks 2"<<endl;
  cout<<"nhits 50"<<endl;
  cout<<"nnoise 3"<<endl;
  cout<<"smearing 0.1"<<endl;
  cout<<"phimin -3.141592653589793116"<<endl;
  cout<<"phimax 3.141592653589793116"<<endl;
  cout<<"d0min 0.0"<<endl;
  cout<<"d0max 1000.0"<<endl;
  cout<<"rmin -1000.0"<<endl;
  cout<<"rmax 1000.0"<<endl;
  cout<<"tanlmin -1.0"<<endl;
  cout<<"tanlmax 1.0"<<endl;
  cout<<"z0min 0.0"<<endl;
  cout<<"z0max 1000.0"<<endl;
  cout<<"padplanexmin -1000.0"<<endl;
  cout<<"padplanexmax 1000.0"<<endl;
  cout<<"padplaneymin -1400.0"<<endl;
  cout<<"padplaneymax 1400.0"<<endl;
  cout<<"padplanezmin -1000.0"<<endl;
  cout<<"padplanezmax 1000.0"<<endl;
  cout<<"padsizey 7.0"<<endl;
  cout<<"*******************"<<endl;
  cout<<"*******************"<<endl;
  cout<< "Example steeringfilename_trackfinding.txt: "<<endl;
  cout<<"tracktype 1"<<endl;
  cout<<"findcurler 0"<<endl;
  cout<<"usevertex 0"<<endl;
  cout<<"vertexX 0."<<endl;
  cout<<"vertexY 0."<<endl;
  cout<<"maxdistxy 10.0"<<endl;
  cout<<"maxdistsz 10.0"<<endl;
  cout<<"maxdistxyfit 5.0"<<endl;
  cout<<"maxdistszfit 5.0"<<endl;
  cout<<"minhitnumber 5"<<endl;
  cout<<"xythetabins 1000"<<endl;
  cout<<"xyd0bins 1000"<<endl;
  cout<<"xyomegabins 300"<<endl;
  cout<<"szthetabins 1000"<<endl;
  cout<<"szd0bins 1000"<<endl;
  cout<<"maxdxy 4000.0"<<endl;
  cout<<"maxdsz 4000.0"<<endl;
  cout<<"searchneighborhood 0"<<endl;
  cout<<"saverootfile 0"<<endl;
  cout <<"*******************"<<endl;
}


//main
int main(int argc, char **argv)
{

  if (argc != 3)
    {
      printUsage(argv);
      return 1;
    }


  char str [80];
  float f;
  FILE * pFile;

  //define some variables for track generation
  unsigned int track_type_tg = 0;
  unsigned int nevents = 0;
  unsigned int ntracks = 0;
  unsigned int nnoise = 0;
  double smearing = 0.;
  unsigned int tpn = 0;
  double phimin = 0., phimax = 0.;
  double d0min = 0., d0max = 0.;
  double rmin = 0., rmax = 0.;
  double tanlmin = 0., tanlmax = 0.;
  double z0min = 0., z0max = 0.;
  double padplanexmin = 0., padplanexmax = 0.;
  double padplaneymin = 0., padplaneymax = 0.;
  double padplanezmin = 0., padplanezmax = 0.;
  double padsizey = 0.;

  //open steering file for track generation
  pFile = fopen (argv[1],"r");

  //read file for track generation
  cout<<"reading file "<<argv[1]<<endl;
  while(!feof(pFile))
  {
    fscanf (pFile, "%s", str);
    fscanf (pFile, "%f", &f);
    cout<<"Read track generation steering file: "<<str<<" "<<f<<endl;
    string var(str);
    if(var == "tracktype") {track_type_tg = (unsigned int)f;}
    if(var == "nevents") {nevents = (unsigned int)f;}
    if(var == "ntracks") {ntracks = (unsigned int)f;}
    if(var == "nnoise") {nnoise = (unsigned int)f;}
    if(var == "smearing") {smearing = (unsigned int)f;}
    if(var == "nhits") {tpn = (unsigned int)f;}
    if(var == "phimin") {phimin = (double)f;}
    if(var == "phimax") {phimax = (double)f;}
    if(var == "d0min") {d0min = (double)f;}
    if(var == "d0max") {d0max = (double)f;}
    if(var == "rmin") {rmin = (double)f;}
    if(var == "rmax") {rmax = (double)f;}
    if(var == "tanlmin") {tanlmin = (double)f;}
    if(var == "tanlmax") {tanlmax = (double)f;}
    if(var == "z0min") {z0min = (double)f;}
    if(var == "z0max") {z0max = (double)f;}
    if(var == "padplanexmin") {padplanexmin = (double)f;}
    if(var == "padplanexmax") {padplanexmax = (double)f;}
    if(var == "padplaneymin") {padplaneymin = (double)f;}
    if(var == "padplaneymax") {padplaneymax = (double)f;}
    if(var == "padplanezmin") {padplanezmin = (double)f;}
    if(var == "padplanezmax") {padplanezmax = (double)f;}
    if(var == "padsizey") {padsizey = (double)f;}
  }

  cout<<"following is read from track generatin steering file: "<<endl;
  cout<<"tracktype: "<<track_type_tg<<endl;
  cout<<"nevents: "<<nevents<<endl;
  cout<<"ntracks: "<<ntracks<<endl;
  cout<<"nhits: "<<tpn<<endl;
  cout<<"nnoise: "<<nnoise<<endl;
  cout<<"smearing: "<<smearing<<endl;
  cout<<"phi range: "<<phimin<<" "<<phimax<<endl;
  cout<<"d0 range: "<<d0min<<" "<<d0max<<endl;
  cout<<"omega range: "<<rmin<<" "<<rmax<<endl;
  cout<<"tanl range: "<<tanlmin<<" "<<tanlmax<<endl;
  cout<<"z0 range: "<<z0min<<" "<<z0max<<endl;
  cout<<"pad plane size x: "<<padplanexmin<<" "<<padplanexmax<<endl;  
  cout<<"pad plane size y: "<<padplaneymin<<" "<<padplaneymax<<endl;  
  cout<<"pad plane size z: "<<padplanezmin<<" "<<padplanezmax<<endl;  
  cout<<"pad size y: "<<padsizey<<endl;

  //close file for track generation
  fclose (pFile);



  //define some variables for track finding
  unsigned int track_type_tf = 0;
  unsigned int find_curler = 0;
  unsigned int use_vertex = 0;
  double vertexX = 0.;
  double vertexY = 0.;
  double maxdistxy = 0.;
  double maxdistsz = 0.;
  double maxdistxyfit = 0.;
  double maxdistszfit = 0.;
  unsigned int minhitnumber = 0;
  unsigned int xythetabins = 0;
  unsigned int xyd0bins = 0;
  unsigned int xyomegabins = 0;
  unsigned int szthetabins = 0;
  unsigned int szd0bins = 0;
  double maxdxy = 0.;
  double maxdsz = 0.;
  unsigned int searchneighborhood = 0;
  unsigned int saverootfile = 0;


  //open steering file for track finding
  pFile = fopen (argv[2],"r");

  //read file for track finding
  cout<<"reading file "<<argv[1]<<endl;
  while(!feof(pFile))
    {
      fscanf (pFile, "%s", str);
      fscanf (pFile, "%f", &f);
      cout<<"Read config file: "<<str<<" "<<f<<endl;
      string var(str);
      if(var == "tracktype") {track_type_tf = (unsigned int)f;}
      if(var == "findcurler") {find_curler = (unsigned int)f;}
      if(var == "usevertex") {use_vertex = (unsigned int)f;}
      if(var == "vertexX") {vertexX = (double)f;}
      if(var == "vertexY") {vertexY = (double)f;}
      if(var == "maxdistxy") {maxdistxy = (double)f;}
      if(var == "maxdistsz") {maxdistsz = (double)f;}
      if(var == "maxdistxyfit") {maxdistxyfit = (double)f;}
      if(var == "maxdistszfit") {maxdistszfit = (double)f;}
      if(var == "minhitnumber") {minhitnumber = (unsigned int)f;}
      if(var == "xythetabins") {xythetabins = (unsigned int)f;}
      if(var == "xyd0bins") {xyd0bins = (unsigned int)f;}
      if(var == "xyomegabins") {xyomegabins = (unsigned int)f;}
      if(var == "szthetabins") {szthetabins = (unsigned int)f;}
      if(var == "szd0bins") {szd0bins = (unsigned int)f;}
      if(var == "maxdxy") {maxdxy = (double)f;}
      if(var == "maxdsz") {maxdsz = (double)f;}
      if(var == "searchneighborhood") {searchneighborhood = (unsigned int)f;}
      if(var == "saverootfile") {saverootfile = (unsigned int)f;}
    }

  cout<<"following is read from track generatin steering file: "<<endl;
  cout<<"tracktype: "<<track_type_tf<<endl;
  cout<<"findcurler: "<<find_curler<<endl;
  if(use_vertex == 1)cout<<"vertex: "<<vertexX<<" "<<vertexY<<endl;
  cout<<"maxdistxy: "<<maxdistxy<<endl;
  cout<<"maxdistsz: "<<maxdistsz<<endl;
  cout<<"maxdistxyfit: "<<maxdistxyfit<<endl;
  cout<<"maxdistszfit: "<<maxdistszfit<<endl;
  cout<<"minhitnumber: "<<minhitnumber<<endl;
  cout<<"xythetabins: "<<xythetabins<<endl;
  cout<<"xyd0bins: "<<xyd0bins<<endl;
  cout<<"xyomegabins: "<<xyomegabins<<endl;
  cout<<"szthetabins: "<<szthetabins<<endl;
  cout<<"szd0bins: "<<szd0bins<<endl;
  cout<<"maxdxy: "<<maxdxy<<endl;
  cout<<"maxdsz: "<<maxdsz<<endl;
  cout<<"searchneighborhood: "<<searchneighborhood<<endl;
  cout<<"saverootfile: "<<saverootfile<<endl;

  //close file for track finding
  fclose (pFile);


  //create object TrackParameterLimits
  //This givse the ranges of the track parameters which will be crated randomly 
  TGTrackParameterLimits TrackParameterLimits(phimin,
					      phimax,
					      d0min,
					      d0max,
					      rmin,
					      rmax,
					      tanlmin,
					      tanlmax,
					      z0min,
					      z0max);
  
  //create object EventType
  //this defines how the event should look like
  TGEventType EventType(tpn,//total point number 
			ntracks, //number of tracks per event
			nnoise, //number of noise hits per event
			smearing, // amount of searing
			nevents);//number of events
  
  //create object DetectorType
  //defines how the readout plane looks like
  //only available for pad readout!
  TGDetectorType DetectorType(padplanexmin,padplanexmax,padplaneymin, padplaneymax, padplanezmin, padplanezmax, padsizey); 
  
  //create object TrackGenerator
  TrackGenerator newTrackGen(track_type_tg, TrackParameterLimits, EventType, DetectorType);



  //create finder parameter
  FinderParameter* newFinderParameter = 0;
  if(track_type_tf == 0)//straight line
    {
      newFinderParameter= new FinderParameter(true, false); //straight line
      newFinderParameter -> setFindCurler(false);
    }
  if(track_type_tf == 1 && find_curler == 0)//helix segment
    {
      newFinderParameter= new FinderParameter(false, true); //straight line
      newFinderParameter -> setFindCurler(false);
    }
  if(track_type_tf == 1 && find_curler == 1)//curler
    {
      newFinderParameter= new FinderParameter(false, true); //straight line
      newFinderParameter -> setFindCurler(true);
    }
  //  if(use_vertex == 0) newFinderParameter -> setUseVertex(false);
  //  if(use_vertex == 1) newFinderParameter -> setUseVertex(true);
  if(use_vertex == 1) 
    {  
      std::pair<double, double> vertex(vertexX, vertexY);
      newFinderParameter -> setVertex(vertex);
    }
  newFinderParameter -> setMaxXYDistance(maxdistxy);
  newFinderParameter -> setMaxSZDistance(maxdistsz);
  newFinderParameter -> setMaxXYDistanceFit(maxdistxyfit);
  newFinderParameter -> setMaxSZDistanceFit(maxdistszfit);
  newFinderParameter -> setMinimumHitNumber(minhitnumber);
  newFinderParameter -> setNumberXYThetaBins(xythetabins);
  newFinderParameter -> setNumberXYDzeroBins(xyd0bins);
  newFinderParameter -> setNumberXYOmegaBins(xyomegabins);
  newFinderParameter -> setNumberSZThetaBins(szthetabins);
  newFinderParameter -> setNumberSZDzeroBins(szd0bins);
  newFinderParameter -> setMaxDxy(maxdxy);
  newFinderParameter -> setMaxDsz(maxdsz);
  if(searchneighborhood == 0)
    {
      newFinderParameter -> setSearchNeighborhood(false);
    }
  else
    {
      newFinderParameter -> setSearchNeighborhood(true);
    }
  if(saverootfile == 0)
    {
      newFinderParameter -> setSaveRootFile(false);
    }
  else
    {
      newFinderParameter -> setSaveRootFile(true);
    }


  //  TFile ftest("MuonEfficiencies.root","recreate");


  //loop over number of events that should be created
  for(unsigned int event = 0; event < nevents; event++)
    {

    /***************************************

                Track Generation

     ***************************************/

      //generate tracks
      cout<<"Starting Track Generation ..."<<endl;
      newTrackGen.generateTracks(event);

      //get the generated tracks, all hits in the event and the noise hits
      vector<TrackFinderTrack*> simtracks = newTrackGen.getGeneratorTracks();
      vector<basicHit> allhits = newTrackGen.getHits();
      vector<basicHit> noisehits = newTrackGen.getNoiseHits();

      //print out the generated tracks
      for(unsigned int i = 0; i<simtracks.size(); i++)
	 {
	     TrackParameterFull currentTrackParameters = simtracks[i]->getTrackParameter();
	     vector<basicHit> currentTrackHits = simtracks[i]->getHitsOnTrack();
	     double d0 = currentTrackParameters.getDZero();
	     double phi = currentTrackParameters.getPhi();
	     double omega = currentTrackParameters.getOmega();
	     double tanl = currentTrackParameters.getTanLambda();
	     double z0 = currentTrackParameters.getZZero();

	     cout<<"Track Parameter (generated): "<<i<<"/"<<simtracks.size()<<endl;
	     cout<<"d0: "<<d0<<" phi: "<<phi<<" omega: "<<omega<<" tanl: "<<tanl<<" z0: "<<z0<<endl;

	     cout<<"Hits on Track: "<<currentTrackHits.size()<<endl;
	     for(unsigned int j =0; j<currentTrackHits.size(); j++)
	       {
		 double pos[3];
		 pos[0] = currentTrackHits[j].getX();
		 pos[1] = currentTrackHits[j].getY();
		 pos[2] = currentTrackHits[j].getZ();
		 // cout<<"hit "<<j<<": "<<pos[0]<<" "<<pos[1]<<" "<<pos[2]<<endl;
	       }//for(unsigned int j =0; j<currentTrackHits.size(); j++)
	 }//for(unsigned int i = 0; i<simtracks.size(); i++)

      //print out noise hits
      cout<<"Noise Hits: "<<endl;
      for(unsigned int j =0; j<noisehits.size(); j++)
	{
	  double pos[3];
	  pos[0] = noisehits[j].getX();
	  pos[1] = noisehits[j].getY();
	  pos[2] = noisehits[j].getZ();
	}

      cout<<"Track Generation is done."<<endl;


      /***************************************

                Track Finding

      ***************************************/

      //creating an object HoughTrafoTrackFinder
      clock_t start = clock();
      cout<<"Starting Track Finding ..."<<endl;
      HoughTrafoTrackFinder newTrackFinder;

      //setting steering parameter
      newTrackFinder.setFinderParameter(*newFinderParameter);

      //set the vector of basic hits in which tracks should be found
      //here: use all hits deliverd by the track generator
      newTrackFinder.setInitialHits(allhits);

      //do the actual track finding
      bool tracks_found = newTrackFinder.find();

      if(tracks_found)
	{
	  //get the tracks which were found
	  vector<TrackFinderTrack> foundTracks = newTrackFinder.getTracks();

	  for(unsigned int i = 0; i<foundTracks.size();i++)
	    {
	      TrackParameterFull recoTrackParam = foundTracks[i].getTrackParameter();
	      //get track parameters
	      double d0 = recoTrackParam.getDZero();
	      double phi = recoTrackParam.getPhi();
	      double omega = recoTrackParam.getOmega();
	      double z0 = recoTrackParam.getZZero();
	      double tanl = recoTrackParam.getTanLambda();

	      cout<<"Track Parameter (reconstructed): "<<i<<"/"<<foundTracks.size()<<endl;
	     cout<<"d0: "<<d0<<" phi: "<<phi<<" omega: "<<omega<<" tanl: "<<tanl<<" z0: "<<z0<<endl;

	     //get hits on track
	     vector<basicHit> hitsOnTrack = foundTracks[i].getHitsOnTrack();
	     cout<<"Number of hits on track: "<<hitsOnTrack.size()<<endl;
	     
	     for(unsigned int j =0; j<hitsOnTrack.size(); j++)
	       {
		 double pos[3];
		 pos[0] = hitsOnTrack[j].getX();
		 pos[1] = hitsOnTrack[j].getY();
		 pos[2] = hitsOnTrack[j].getZ();
		 //cout<<"hit "<<j<<": "<<pos[0]<<" "<<pos[1]<<" "<<pos[2]<<endl;
	       }//for(unsigned int j =0; j<currentTrackHits.size(); j++)

	    }//for(int i = 0; i<foundTracks.size();i++)
	}
      else
	{
	  cout<<"Not tracks were found."<<endl;
	}

      cout<<"Track Finding is done."<<endl;
      cout <<"Needed time: "<< ((clock() - start) / (double)CLOCKS_PER_SEC) << " sec" << endl;
    }//for(unsigned int event = 0; event < nevents<< event++)
  delete newFinderParameter;
  return 0;
}//int main(int argc, char **argv)
