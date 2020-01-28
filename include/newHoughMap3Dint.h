#ifndef NEWHOUGHMAP3DINT_H
#define NewHOUGHMAP3DINT_H

#include "HoughMap.h"
#include "HoughMaximum2D.h"
#include "HoughMaximum3D.h"
#include "HoughSpacePoint.h"
#include "FinderParameter.h"
#include "basicHit.h"
#include "HoughSpaceBinning.h"
#include <vector>
#include <map>
#include <cmath>

namespace pathfinder
{

/**
   Class to calculate the Hough space for circles (center of circle and radius separately).
*/
class newHoughMap3Dint : public HoughMap
{

    public:
        /**
           Constructor. Parameters are a vector of basic hits in which circles are to be found and FinderParameters which contain information on Hough space binning etc.
        */
        newHoughMap3Dint(std::vector<basicHit>, FinderParameter);

        /**
           Constructor. \todo Is this constructor needed?
        */
        newHoughMap3Dint(std::vector<candidateHit>, FinderParameter);

        ///Destructor.
        virtual  ~newHoughMap3Dint()
        {
            /*
                 if(Map_Maximum3D !=0)
            {
              delete Map_Maximum3D;
            }
                 if(Map_Maximum3D1 !=0)
            {
              delete Map_Maximum3D1;
            }
                 if(Map_Maximum3D2 !=0)
            {
              delete Map_Maximum3D2;
            }
                 if(Map_Maximum3D3 !=0)
            {
              delete Map_Maximum3D3;
            }
                 if(Map_Maximum3D4 !=0)
            {
              delete Map_Maximum3D4;
            }
                 */
            delete MapMaximumPair.first;
            delete MapMaximumPair.second;

            delete drangexy;
            delete trangexy;
        };

        ///Deletes all entries from map containing the Hough space.
        void clear()
        {
            HoughMapInt1.clear();
        };

        /**
          Function returning maximum of Hough space
        */
        HoughMaximum3D* findMaximum();

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
        newHoughMap3Dint()
        {
            ;
        };

        /**
           Calculates the mean distance between hits and track described bu the parameters given as parameter. This is needed to get the correct set of parameters describing the track.
        */
        int MeanDistanceCalculator(HoughMaximum3D*);

        /**
           Finds the Maximum of the Hough space (for the center of the circle).
        */
        void findMaximum2D();

        /**
           Finds the radius of the circle with the center given as parameter.
        */
        double findRadius(HoughMaximum2D*);

        /**
           Calculates the maximum range for 1/D (distance of the center of the circle to the origin of the coordinate system) in the Hough space. If it is larger than the value given as steering parameter, the value in the steering parameters is taken, else the new one is used.
           \todo Now 1/D is used in the Hough transformation. Maybe the name of the function is now misleading...
        */
        void calculateDRangeXY();

        /**
          Function to calculate the Hough space.
        */
        bool fill();

        /**
          Needed to do the search the maximum of the radius Hough space.
        */
        static bool map_compare1(std::pair<int, unsigned int> i1,
                                 std::pair<int , unsigned int> i2)
        {
            return i1.second < i2.second;
        };

        std::map<int, unsigned int> HoughMapInt1;///<Map for the Hough space (center of circle).
        std::map<int, unsigned int> HoughMapRadius;///<Map for the Hough space (radius).
        std::map<int, unsigned int> HoughMapRadius_copy;///<Map for the Hough space (radius). \todo Check why this is here? Is it needed?

        std::vector<basicHit> initialBasicHits;///<Vector of basic hits in which circles are to be found.

        HoughSpaceBinning* drangexy;///<Range of the Hough space (1/D).
        HoughSpaceBinning* trangexy;///<Range of the Hough space (theta).

        FinderParameter Parameter;///<Steering parameters for search.

        std::pair<HoughMaximum2D*, HoughMaximum2D*> MapMaximumPair;///<In the Hough space for the center of the circle two possible Maxima can be found.
        HoughMaximum3D* Map_Maximum3D;///<Maximum in Hough Map which is returned
        HoughMaximum3D* Map_Maximum3D1;///<There are four different combinations of track parameters that can be found, the correct one is chosen and copied to Map_Maximum3D.
        HoughMaximum3D* Map_Maximum3D2;///<There are four different combinations of track parameters that can be found, the correct one is chosen and copied to Map_Maximum3D.
        HoughMaximum3D* Map_Maximum3D3;///<There are four different combinations of track parameters that can be found, the correct one is chosen and copied to Map_Maximum3D.
        HoughMaximum3D* Map_Maximum3D4;///<There are four different combinations of track parameters that can be found, the correct one is chosen and copied to Map_Maximum3D.

        bool trackfound;///<True if a track was found.
};//class 2DHoughMapint
}
#endif //NEWHOUGHMAP3DINT_H
