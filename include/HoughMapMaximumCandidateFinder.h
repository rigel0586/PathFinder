#ifndef HOUGHMAPMAXIMUMCANDIDATEFINDER_H
#define HOUGHMAPMAXIMUMCANDIDATEFINDER_H

#include "HoughSpaceBinning.h"
#include "HoughSpacePoint.h"
#include "HoughMaximum2D.h"
#include <map>
#include <vector>
#include <cmath>
#include <cstdlib>

namespace pathfinder
{
/**
   Class finding the maximum in the Hough maps.
 */
class HoughMapMaximumCandidateFinder
{

    public:
        /**
           Constructor. Parameters are the Hough space, the binning of the Hough space in theta and d and a bool defining if the neighborhood of a maximum candidate should be taken into account.
         */
        HoughMapMaximumCandidateFinder(std::map<int, unsigned int> InputHoughMap, HoughSpaceBinning* trange, HoughSpaceBinning* drange, bool iscircle, bool searchneighborhood);

        ///Destructor.
        ~HoughMapMaximumCandidateFinder()
        {
            HoughMap.clear();
            MaximumCandidates.clear();
        };

        /**
           Returns the found maximum candidates.
         */
        std::vector<HoughMaximum2D> getMaximumCandidates()
        {
            return MaximumCandidates;
        };

    private:
        ///Default constructor, disabled.
        HoughMapMaximumCandidateFinder()
        {
            ;
        };

        /**
           Finds maxima in Hough map.
         */
        void findMaxima();

        /**
           Function counts how many entries there are in the neighboring bins of the bin given to it as parameter.
         */
        unsigned int searchNeighborhood(HoughSpacePoint currentBin);

        /**
                  Needed to do the search the maximum of the Hough space.
        */
        static bool map_compare1(std::pair<int, unsigned int> i1,
                                 std::pair<int , unsigned int> i2)
        {
            return i1.second < i2.second;
        };

        /**
                  Needed to do the search the maximum of the Hough space.
        */
        static bool map_compare2(std::pair<int , unsigned int> i1,
                                 std::pair<int, unsigned int> i2)
        {
            //return i1.second==i2.second;
            //if entries are the same within statistical uncertainty
            //return abs((long int)i1.second - (long int)i2.second) <= (i1.second)/2;//using this more maxima can be found.
            return abs((long int)i1.second - (long int)i2.second) <= sqrt(i1.second);
        };

        std::map<int, unsigned int> HoughMap;///<Map containing Hough space in which maxima are searched.

        HoughSpaceBinning* tRange;///<Hough space binning theta.
        HoughSpaceBinning* dRange;///<Hough space binning d.

        bool isCircle;///<True if a circle needs to be found. This needs to be known because for straight lines d is used for the Hough space, for circles 1/d is used.
        bool neighborhoodSearch;///<Defines if the neighborhood of a maximum candidate should be taken into account.

        std::vector<HoughMaximum2D> MaximumCandidates;///<Vector holding all maximum candidates found in the Hough space.

}; //class HoughMapMaximumCandidateFinder
}//end namespace

#endif //HOUGHMAPMAXIMUMCANDIDATEFINDER_H
