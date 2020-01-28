#ifndef HOUGHTRAFOTRACKFINDER_H
#define HOUGHTRAFOTRACKFINDER_H

#include "basicHit.h"
#include "candidateHit.h"
#include "FinderParameter.h"
#include "TrackParameterXY.h"
#include "TrackParameterSZ.h"
#include "TrackParameterFull.h"
#include "HoughMap.h"
#include "HoughMapMaximum.h"
#include "SimpleFit.h"
#include "TrackFinderTrack.h"
#include <vector>

/** \mainpage  Pathfinder
 *
 *            A package for track finding using the Hough transformation.
 *
 */

namespace pathfinder
{
/**
   Does the track finding. A loop runs until no more tracks can be found. It does the following steps:
   - Search in xy (circle or straight line)
   - Simple fit in xy
   - calculate arc length s for each hit found on track in the xy projection
   - Search in sz (straight line)
   - Simple fit in sz
 */
class HoughTrafoTrackFinder
{

    public:

        ///Constructor.
        HoughTrafoTrackFinder();

        ///Destructor.
        ~HoughTrafoTrackFinder()
        {

            if(XYHoughMap != 0)
            {
                //      delete XYHoughMap;
            }
            if(SZHoughMap != 0)
            {
                //delete SZHoughMap;
            }
            if(XYFitter != 0)
            {
                //delete XYFitter;
            }
            if(SZFitter != 0)
            {
                //delete SZFitter;
            }
            if(XYHoughMaximum != 0)
            {
                delete XYHoughMaximum;
            }
            if(SZHoughMaximum != 0)
            {
                delete SZHoughMaximum;
            }
            if(XYTrackParameter != 0)
            {
                delete XYTrackParameter;
            }
            if(fittedXYTrackParameter != 0)
            {
                delete fittedXYTrackParameter;
            }
            if(SZTrackParameter != 0)
            {
                delete SZTrackParameter;
            }
            if(fittedSZTrackParameter != 0)
            {
                delete fittedSZTrackParameter;
            }
            if(finalTrackParameter != 0)
            {
                delete finalTrackParameter;
            }

        };

        /**
           Function finding tracks. It keeps searching (first in the xy projection, circle or straight line, then in the sz projection, straight lines) until no more tracks can be found.
         */
        bool find();

        /**
           Sets steering parameters.
         */
        void setFinderParameter(FinderParameter _finderParameter)
        {
            finderParameter = _finderParameter;
        }

        /**
           Returns steering parameters.
         */
        FinderParameter getFinderParameter()
        {
            return finderParameter;
        }

        /**
           Sets the Hits in which tracks are to be found.
         */
        void setInitialHits(std::vector<basicHit> initialHits)
        {
            allHits = initialHits;
            allHits_copy = initialHits;
        }

        /**
           Returns the Hits in which tracks are to be found.
         */
        std::vector<basicHit> getInitialHits()
        {
            return allHits;
        }

        /**
           Returns a vector with all found tracks.
         */
        std::vector<TrackFinderTrack> getTracks()
        {
            return finalTracks;
        }


    private:
        /**
           Does the search in the xy projection (straight line or circle), returns a pair containing the hits assigned to the track and the track parameters in the xy projection. Needs as parameters: vector of hits and steering parameters (FinderParameter).
         */
        std::pair<std::vector<basicHit>*, TrackParameterXY*> _doXYPlaneProjection(std::vector<basicHit>,
                                                                                  FinderParameter);
        /**
           Does the search in the sz projection (straight line), returns a pair containing the hits assigned to the track and the track parameters in the sz projection. Needs as parameters: vector of hits, steering parameters (FinderParameters) and track parameters in the xy projection.
         */
        std::pair<std::vector<candidateHit>*, TrackParameterSZ*> _doSZPlaneProjection(std::vector<candidateHit>,
                                                                                      FinderParameter, TrackParameterXY);

        /**
           Finds hits close to the track in xy. Parameters needed: Maximum of the Hough space, steering parameters and vector of hits and a bool which is true if the track was fitted (different distances might be allowed between hit and track if track was fitted or not).
         */
        std::vector<basicHit> findCloseXYHits(HoughMapMaximum*, FinderParameter, std::vector<basicHit>, bool);

        /**
           Finds hits close to the track in xy. Parameters needed: Track parameters in xy, steering parameters and vector of hits and a bool which is true if the track was fitted (different distances might be allowed between hit and track if track was fitted or not).
         */
        std::vector<basicHit> findCloseXYHits(TrackParameterXY, FinderParameter, std::vector<basicHit>, bool);

        /**
           Finds hits close to the track in sz. Parameters needed: Maximum of the Hough space, track parameters in xy (it is only used if curles should be found), steering parameters and vector of hits and a bool which is true if the track was fitted (different distances might be allowed between hit and track if track was fitted or not).
         */
        std::vector<candidateHit> findCloseSZHits(HoughMapMaximum*, TrackParameterXY , FinderParameter, std::vector<candidateHit>, bool);

        /**
           Finds hits close to the track in sz. Parameters needed: Track parameters in sz, track parameters in xy (it is only used if curles should be found), steering parameters and vector of hits and a bool which is true if the track was fitted (different distances might be allowed between hit and track if track was fitted or not).
         */
        std::vector<candidateHit> findCloseSZHits(TrackParameterSZ, TrackParameterXY , FinderParameter, std::vector<candidateHit>, bool);

        /**
           Creates a vector containing the hits not assigned to the track. \todo Is this really needed twice?
         */
        std::vector<basicHit> findHitsNotOnTrack(std::vector<basicHit>, std::vector<basicHit>);

        /**
           Creates a vector containing the hits not assigned to the track. \todo: Is this really needed twice?
         */
        std::vector<basicHit> findHitsNotOnTrack(std::vector<candidateHit>, std::vector<candidateHit>);

        /**
        Sorts the hits by z position (it is only used if curles should be found).
        */
        std::vector<candidateHit> sortByZ(std::vector<candidateHit>);

        ///Needed to sort hits by z positions.
        static bool sortZ(candidateHit i1, candidateHit i2)
        {
            //std::cout<<"HoughTrafoTrackFinder::sortZ: i1 = "<<i1.getZ()<<" i2 = "<<i2.getZ()<<std::endl;
            return i1.getZ() < i2.getZ();
        };


        FinderParameter finderParameter;///<Steering parameters.

        //HoughSpaceRanges
        //std::pair<double, double> thetaRange;
        //std::pair<double, double> dzeroRange;
        //std::pair<double, double> omegaRange;//TODO: is this one really needed here?

        //HoughMaps
        HoughMap* XYHoughMap;///<xy Hough space (straight line or circle).
        HoughMap* SZHoughMap;///<sz Hough space (straight line).

        SimpleFit* XYFitter;///<Fitter for xy projection (straight line or circle).
        SimpleFit* SZFitter;///<Fitter for sz (straight line).

        //HoughMapMaxima
        HoughMapMaximum* XYHoughMaximum;///<Maximum in xy Hough space
        HoughMapMaximum* SZHoughMaximum;///<Maximum in sz Hough space

        //TrackParameter
        TrackParameterXY* XYTrackParameter;///<xy track parameters of current track before fit.
        TrackParameterXY* fittedXYTrackParameter;///<xy track parameters of current track after fit.
        TrackParameterSZ* SZTrackParameter;///<sz track parameters of current track before fit.
        TrackParameterSZ* fittedSZTrackParameter;///<sz track parameters of current track after fit.

        std::pair<std::vector<basicHit>*, TrackParameterXY*> xyTrack;///<Track found in the xy projection (hits on track and xy track parameters).
        std::pair<std::vector<candidateHit>*, TrackParameterSZ*> szTrack;///<Track found in the sz projection (hits on track and sz track parameters).

        std::vector<basicHit> allHits;///<Vector of hits on which track finding is to be done.
        std::vector<basicHit> allHits_copy;///<Vector of hits on which track finding is to be done. Hits are removed from this vector when they are assigned to a track.
        std::vector<basicHit> hitsOnFittedTrackXY;///<Vector containing hits assigned to the track in xy after the xy fit.
        std::vector<basicHit> noiseHits;///<Vector containing hits not having been assigned to a track.
        std::vector<candidateHit> hitsOnFittedTrackSZ;///<Vector containing hits assigned to the track in sz after the sz fit.
        std::vector<candidateHit> xyHitsAndS;///<Vector containing hits assigned to the track in xy after the xy fit + the arclength s for each hit.

        TrackParameterFull* finalTrackParameter;///<Final track parameters (xy and sz combined).
        std::vector<basicHit> finalHitsOnTrack;///<Hits on final track.
        std::vector<basicHit> finalHitsNotOnTrack;///<Hits not assigned to the track (the search is continued on these hits).

        std::vector<TrackFinderTrack> finalTracks;///<Vector containing all found tracks which are returned.

};//class HoughTrafoTrackFinder
}
#endif // HOUGHTRAFOTRACKFINDER_H

