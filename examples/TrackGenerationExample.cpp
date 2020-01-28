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

using namespace std;
using namespace pathfinder;

void printUsage(char **argv)
{
  cout << "invoke like this:" << endl;
  cout << argv[0] << " [configfilename.txt]"<<endl;
  cout << "Example configuration file: "<<endl;
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
}


//main
int main(int argc, char **argv)
{

  if (argc != 2)
    {
      printUsage(argv);
      return 1;
    }


  char str [80];
  float f;
  FILE * pFile;

  //define some variables
  unsigned int track_type = 0;
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

  //open steering file
  pFile = fopen (argv[1],"r");

  //read file
  cout<<"reading file "<<argv[1]<<endl;
  while(!feof(pFile))
  {
    fscanf (pFile, "%s", str);
    fscanf (pFile, "%f", &f);
    cout<<"Read config file: "<<str<<" "<<f<<endl;
    string var(str);
    if(var == "tracktype") {track_type = (unsigned int)f;}
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

  cout<<"following is read from file: "<<endl;
  cout<<"tracktype: "<<track_type<<endl;
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

  //close file
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
  TrackGenerator newTrackGen(track_type, TrackParameterLimits, EventType, DetectorType);

  //loop over number of events that should be created
  for(unsigned int event = 0; event < nevents; event++)
    {
      //generate tracks
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

	     cout<<"Track Parameter: "<<endl;
	     cout<<"d0: "<<d0<<endl;
	     cout<<"phi: "<<phi<<endl;
	     cout<<"omega: "<<omega<<endl;
	     cout<<"tanl: "<<tanl<<endl;
	     cout<<"z0: "<<z0<<endl;

	     cout<<"Hits on Track: "<<endl;
	     for(unsigned int j =0; j<currentTrackHits.size(); j++)
	       {
		 double pos[3];
		 pos[0] = currentTrackHits[j].getX();
		 pos[1] = currentTrackHits[j].getY();
		 pos[2] = currentTrackHits[j].getZ();
		 cout<<"hit "<<j<<": "<<pos[0]<<" "<<pos[1]<<" "<<pos[2]<<endl;
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
    


    }//for(unsigned int event = 0; event < nevents<< event++)

  return 0;
}//int main(int argc, char **argv)
