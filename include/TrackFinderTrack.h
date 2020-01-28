#ifndef TRACKFINDERTRACK_H
#define TRACKFINDERTRACK_H

#include <vector>
#include "basicHit.h"
#include "TrackParameterFull.h"

namespace pathfinder
{
class TrackFinderTrack
{
    public:
        /**
        Constructor. First parameter is the full set of track parameters, the second parameter is the vector of hits belonging to the track.
             */
        TrackFinderTrack(const TrackParameterFull&, const std::vector<basicHit>&);

        /**
           Constructor. First parameter is the full set of track parameters, the second parameter is the vector of hits belonging to the track, the third parameter is a vector containing rejected hits.
         */
        TrackFinderTrack(const TrackParameterFull&, const std::vector<basicHit>&, const std::vector<basicHit>&);

        ///Destructor.
        ~TrackFinderTrack();

        /**
           Returns track parameters.
         */
        const TrackParameterFull& getTrackParameter()
        {
            return *trackParameter;
        }

        /**
           Returns a vector containing the hits on the track.
         */
        const std::vector<basicHit>& getHitsOnTrack()
        {
            return hitsOnTrack;
        }

        /**
           Returns a vector containing rejected hits.
         */
        const std::vector<basicHit>& getRejectedHits()
        {
            return rejectedHits;
        }

        ///Prints track parameters, hits on track and rejected hits
        void print();

    private:
        TrackFinderTrack();///< no public default constructor -> immutable!
        TrackParameterFull* trackParameter;///<track parameters
        std::vector<basicHit> hitsOnTrack;///<vector containing hits on track
        std::vector<basicHit> rejectedHits;///<vector containing rejected hits
};
}
#endif // TRACKFINDERTRACK_H
