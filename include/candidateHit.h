#ifndef CANDIDATEHIT_H
#define CANDIDATEHIT_H

#include "basicHit.h"

namespace pathfinder
{
/**
   the extension of the basic hit for track finding

   in the first stage of hough trafo track finding the hits are projected into x and y
   for the second stage of hough trafo the arclength of a hit w.r.t. a reference hit is needed

   this class describes a basicHit, extended by the arclength s in the xy plane
 */

class candidateHit : public basicHit
{
    public:
        candidateHit(basicHit); ///< construct from basicHit
        candidateHit(basicHit, double); ///<construct from basicHit and set arclength s

        ///returns arclength s
        double getS() const
        {
            return pathLength;
        };

        ///sets the arc length s
        void setS(double s)
        {
            pathLength = s;
        };

        virtual void print() const;

    private:
        double pathLength;///< arclength s

};
}
#endif //CANDIDATEHIT_H 
