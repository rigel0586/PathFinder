#ifndef CANDIDATEHITCOMBINATION_H
#define CANDIDATEHITCOMBINATION_H

#include "basicHit.h"
#include "TrackParameterXY.h"
#include "FinderParameter.h"
#include "candidateHit.h"
#include <vector>

namespace pathfinder
{
/**
   class calculating the arc length s for hits having been assigned to a track in the xy plane

   takes a vector of basicHits

   returns a vector of candidateHits
 */
class candidateHitCombination
{
    public:

        candidateHitCombination(std::vector<basicHit>, TrackParameterXY, FinderParameter);///<constructor, needs a vector of basic hits having been assigned to a track in xy, the track parameters in xy and FinderParameter
        ~candidateHitCombination();///<destructor

        std::vector<candidateHit> getCombination(TrackParameterXY);///<returns vector of candidate Hits which contain the input basicHits and the corresponfing values for s

        void print();///<print function


    private:
        std::vector<basicHit> _basicHits;///<vector of basicHits

        basicHit* _pca;///<point of closest approach, is calculated from xy track parameters

        bool _isHelix;///<true if track type is a helix

        /**
           calculate the arc length s for a hit in the xy plane, s is counted from the point of closest approach (pca)

           for straight lines: \f$ s = \sqrt{ (x_{hit} - x_{pca})^2 + (y_{hit} - y_{pca})^2 }\f$

           for helices: \f$ s = \frac{1}{|\Omega|} \left( \arctan \left( \frac{y_{pca} - y_{center}}{x_{pca} - x_{center}} \right) - \arctan \left( \frac{y_{hit} - y_{center}}{x_{hit} - x_{center}} \right) \right)\f$
        */
        double calculateS(basicHit, basicHit, TrackParameterXY);

        /**
           sort hits by z position
         */
        std::vector<candidateHit> sortByZ(std::vector<candidateHit>);

        ///comparison to sort hit vector by z
        static bool sortZ(candidateHit i1,
                          candidateHit i2)
        {
            return i1.getZ() < i2.getZ();
        };

};
}
#endif // CANDIDATEHITCOMBINATION_H 
