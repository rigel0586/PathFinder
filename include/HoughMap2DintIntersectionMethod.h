#ifndef HOUGHMAP2DINTINTERSECTIONMETHOD_H
#define HOUGHMAP2DINT_H

#include "HoughMap.h"
#include "HoughMaximum2D.h"
#include "HoughSpacePoint.h"
#include "FinderParameter.h"
#include "basicHit.h"
#include "candidateHit.h"
#include "HoughSpaceBinning.h"
#include <vector>
#include <map>
#include <cmath>
#include <cstdlib>

namespace pathfinder
{
/**
   Class to calculate the Hough space for straight lines. It is using a local Hough transformation, meaning that the intersection of two functions is calculated analytically and only those points are filled into the Hough spaces (keeps them smaller).
   \todo This method is still to be investigated in more detail.
 */
class HoughMap2DintIntersectionMethod : public HoughMap
{

    public:
        /**
        Constructor. Parameters are a vector of basic hits in which straight lines are to be found and FinderParameters which contain information on Hough space binning etc. This constructor is used for the xy projection.
             */
        HoughMap2DintIntersectionMethod(std::vector<basicHit>, FinderParameter);

        /**
           Constructor. Parameters are a vector of candidate hits (arc length s war calculated) in which straight lines are to be found and FinderParameters which contain information on Hough space binning etc. This constructor is used for the sz projection.
         */
        HoughMap2DintIntersectionMethod(std::vector<candidateHit>, FinderParameter);

        ///Destructor.
        virtual  ~HoughMap2DintIntersectionMethod()
        {
            //    if(Map_Maximum != 0) { delete Map_Maximum;}
        };

        ///Deletes all entries from map containing the Hough space.
        void clear()
        {
            HoughMapInt.clear();
        };

        /**
          Function finding the maximum in Hough space and returning it.
        */
        HoughMaximum2D* findMaximum();

        /**
           Returns true if a track was found
        */
        bool getTrackFound()
        {
            return trackfound;
        }

        /**
           Prints out Hough space.
        */
        virtual void print() const;


    private:
        ///Default constructor, disabled.
        HoughMap2DintIntersectionMethod()
        {
            ;
        };//no public default constructor

        /**
           Calculates the maximum range for D (distance of closest approach) in the Hough space (xy). If it is larger than the value given as steering parameter, the value in the steering parameters is taken, else the new one is used.
        */
        void calculateDRangeXY();

        /**
           Calculates the maximum range for D (distance of closest approach) in the Hough space (sz). If it is larger than the value given as steering parameter, the value in the steering parameters is taken, else the new one is used.
        */
        void calculateDRangeSZ();

        /**
           Function to calculate the Hough space.
        */
        bool fill();

        bool trackfound;///<True if a track was found.
        std::map<int, unsigned int> HoughMapInt;///<Map for the Hough space.
        bool _useXY;///<true if search is done in the xy projection.

        std::vector<basicHit> initialBasicHits;///<Vector of basic hits in which straight lines are to be found (xy).
        std::vector<candidateHit> initialCandidateHits;///<Vector of candidate hits in which straight lines are to be found (sz).

        HoughSpaceBinning* drangexy;///<Range of the xy Hough space (D).
        HoughSpaceBinning* trangexy;///<Range of the xy Hough space (theta).

        HoughSpaceBinning* drangesz;///<Range of the sz Hough space (D).
        HoughSpaceBinning* trangesz;///<Range of the sz Hough space (theta).


        FinderParameter Parameter;///<Steering parameters for search.

        HoughMaximum2D* Map_Maximum;///<Maximum in Hough Map which is returned.

};//class 2DHoughMapintIntersectionMethod
}
#endif //HOUGHMAP2DINTINTERSECTIONMETHOD_H
