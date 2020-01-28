#ifndef TRACKGENERATOR_H
#define TRACKGENERATOR_H

#include "TrackFinderTrack.h"
#include "TrackParameterFull.h"
#include "basicHit.h"

#include "TGTrackParameterLimits.h"
#include "TGEventType.h"
#include "TGDetectorType.h"

#include "TFile.h"
#include <TH1.h>
#include <TH2.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTree.h>

namespace pathfinder
{

/**
   Class to create random tracks.
   \todo The random numbers for the smearing need to be reworked.
 */
class TrackGenerator
{
    public:

        /**
        Old constructor, don't use it.
         The first parameter is the track type (0: straight line, 1: helix segment, 2: curler).
         The second parameter is the number of hits per track.
         The third parameter is the number of noise hits per event.
         The fourth is the number of tracks per event.
         The fifth the number of events to be generated (Note: This is only used for the random seed, the loop over events has to be provided in an external program!).
         The sixth parameter is the amount of smearing.
         The seventh parameter is a seed number for the random number generator
             */
        TrackGenerator(int,
                       unsigned int,
                       unsigned int,
                       unsigned int,
                       unsigned int,
                       double,
                       double);

        /**
           Constructor.
           The first parameter is the track type (0: straight line, 1: helix segment, 2: curler).
           The second parameter contains the parameter ranges in which tracks are created.
           The third parameter contains information about the events: number of tracks per event, number of noise hits per event,... (Note: The number of events is only used for the random seed, the loop over events has to be provided in an external program!).
           The fourth parameter contains information about the detector layout
         */
        TrackGenerator(int, TGTrackParameterLimits, TGEventType, TGDetectorType);

        ///Destructor.
        ~TrackGenerator();

        ///generates random track parameters, fills them into control histograms and creates hits along the track.
        bool generateTracks(unsigned int);

        ///returns all hits created in the event
        std::vector<basicHit>  getHits()
        {
            return hitsInEvent;
        };

        ///returns noise hits created in the event
        std::vector<basicHit> getNoiseHits()
        {
            return noiseHits;
        };

        ///returns the tracks generated in the event
        std::vector<TrackFinderTrack*>  getGeneratorTracks()
        {
            return generatorTracks;
        };

        ///returns the track parameters of the generated tracks
        std::vector<TrackParameterFull*>  getTrackParameters()
        {
            return generatorTrackParameters;
        };

    private:
        int track_type;///<Track shape: 0 = straight line; 1 = helix segment; 2 = curler
        std::vector<TrackFinderTrack*> generatorTracks;///<vector containing generated tracks
        std::vector<TrackParameterFull*> generatorTrackParameters;///<vector containing parameters of generated tracks
        //std::vector<std::vector<TrackFinderTrack*> > generatorTracksVec;
        //std::vector<std::vector<TrackParameterFull*> > generatorTrackParametersVec;

        unsigned int tpn;///<total point number per track
        unsigned int nnoise;///<total number of noise in event
        unsigned int ntracks;///<total number of tracks in event
        unsigned int nevents;///<currently not used
        double smearing;///<amount of smearing by which hits are shifted off the track
        double trackseed;///<seed for random number generator

        //detector layout
        std::pair<double, double> padplaneX;///<bordes of pad plane in x
        std::pair<double, double> padplaneY;///<borders of pad plane in y
        std::pair<double, double> padplaneZ;///<size of sensitive volume in z
        double padsizey;///<size of pads in y direction, is used to calculate y positions of hits


        std::pair<double, double> phiLimits;///<track parameter range in phi
        std::pair<double, double> d0Limits;///<track parameter range in d0
        std::pair<double, double> omegaLimits;///<track parameter range in omega
        //            std::pair<double, double> rLimits;///<track parameter range in r
        std::pair<double, double> tanlLimits;///<track parameter range in tan lambda
        std::pair<double, double> z0Limits;///<track parameter range in z0

        /**
           Compute x values of hits using the track parameters and the y positions of the hits (the parameter needed for this funtion is a vector containing the y positions).
         */
        std::vector<double> computeX(std::vector<double>, TrackParameterFull*);

        /**
           Only needed for curler. In case for curler there are two possible x values for one y value. This is taken care of in this function.
         */
        std::vector<double> correctY(std::vector<double>, TrackParameterFull*);

        /**
           Compute y values of hits according to pad plane
         */
        std::vector<double> computeY();

        /**
           Compute z values of hits using track parameters and the x and y positions of hits. The positions must be given to the function as two vectors, the first one for x, the second one fot y).
         */
        std::vector<double> computeZ(std::vector<double>, std::vector<double>, TrackParameterFull*);

        std::vector<basicHit> hitsInEvent;///<vector contaning all hits in the event
        std::vector<basicHit> noiseHits;///<vector containing all noise hits in the event
        //std::vector<std::vector<basicHit> > hitsInEventVec;
        //std::vector<std::vector<basicHit> > noiseHitsVec;

        //double uniformSmearing(double);
        //double uniform1(double, double);
        //double uniform2(double, double);
        //double uniformOmega(double, double);

        /**
           Function creating uniform random numbers. The first two parameters specify the range, the third is a seed.
         */
        double uniform(double, double, double);

        /**
           Function creating gaussian random numbers. The third parameter is a seed.
           \todo the first two parameters are not used, so why are they there?
         */
        double gaus(double, double, double);

        TTree* controlTreeRand;///<root tree containing random numbers
        TTree* noisePosTree;///<root tree containg noise hit positions
        TTree* randomSmearingTree;///<root tree containig random amount of smearing

        TFile* file;///<file to write control plots and root tree to

        float d0rand;///<random d0
        float phirand;///<random phi
        float omegarand;///<random omega
        float tanlrand;///<random tan lambda
        float z0rand;///<random z0
        int eventrand;///<event number
        int eventsim;///<event number
        int trackrand;///<track number
        int tracksim;///<track number
        int inoise;///<noise hit number
        int ievent;///<event number
        float noisex;///<noise hit position x
        float noisey;///<noise hit position y
        float noisez;///<noise hit position z
        float randgaus;///<random number of smearing
};
}
#endif //TRACKGENERATOR_H
