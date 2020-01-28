#ifndef HOUGHMAP2DCIRCLEINT_H
#define HOUGHMAP2DCIRCLEINT_H

#include "HoughMap.h"
#include "HoughMaximum3D.h"
#include "HoughSpacePoint.h"
#include "FinderParameter.h"
#include "basicHit.h"
#include "HoughSpaceBinning.h"
#include <vector>
#include <map>
#include <cmath>
#include <cstdlib>

namespace pathfinder
{
/**
   Class to calculate the Hough space for circles (using conformal mapping, circles in the xy plane are mapped to straight lines in the uv plane).
 */
class HoughMap2DCircleint : public HoughMap
{

    public:
        /**
           Constructor. Parameters are a vector of basic hits in which circles are to be found and FinderParameters which contain information on Hough space binning etc.
        */
        HoughMap2DCircleint(std::vector<basicHit>, FinderParameter);

        /**
           Constructor. \todo Is this constructor needed?
        */
        HoughMap2DCircleint(std::vector<candidateHit>, FinderParameter);

        ///Destructor.
        virtual  ~HoughMap2DCircleint()
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
        HoughMap2DCircleint()
        {
            ;
        };//no public default constructor


        /**
           Calculates the maximum range for D (distance of closest approach) in the Hough space. If it is larger than the value given as steering parameter, the value in the steering parameters is taken, else the new one is used.
        */
        void calculateDRangeXY();

        /**
          Function to calculate the Hough space.
        */
        bool fill();

        bool trackfound;///<True if a track was found.
        std::map<int, unsigned int> HoughMapInt;///<Map for the Hough space.

        std::vector<basicHit> initialBasicHits;///<Vector of basic hits in which circles are to be found.

        HoughSpaceBinning* drangexy;///<Range of the Hough space (D).
        HoughSpaceBinning* trangexy;///<Range of the Hough space (theta).

        FinderParameter Parameter;///<Steering parameters for search.

        HoughMaximum2D* Map_Maximum;///<Maximum in Hough Map which is returned.

};//class 2DHoughMapint

}//end namespace

#endif //HOUGHMAP2DCIRCLEINT_H
