#ifndef HOUGHSPACEBINNING_H
#define HOUGHSPACEBINNING_H

#include <iostream>

namespace pathfinder
{
class HoughSpaceBinning
{
    public:
        /**
           Constructor. Parameters are the number of bins, the lower limit and the higher limit.
         */
        HoughSpaceBinning(int _bins, double _low, double _high);

        /**
           Constructor. Parameters are the number of bins and the range (pair containing lower and higher limit).
         */
        HoughSpaceBinning(int _bins, std::pair<double, double> _range);

        /**
           Returns the number of bins.
         */
        int getNBins()
        {
            return bins;
        }

        /**
           Returns range (pair containing lower and higher limit).
         */
        std::pair<double, double> getRangeLimits()
        {
            return rangelimits;
        }

        /**
           Returns lower limit.
         */
        double getLow()
        {
            return rangelimits.first;
        }

        /**
           Returns higher limit.
         */
        double getHigh()
        {
            return rangelimits.second;
        }

        /**
           Returns bin width.
         */
        double getBinWidth()
        {
            return binwidth;
        }

        /**
           Returns range width.
         */
        double getRangeWidth()
        {
            return rangewidth;
        }

        ///Destructor.
        ~HoughSpaceBinning()
        {
            ;
        };

        ///Prints Hough space binning information.
        void Print();

    private:
        ///Default Constructor, disabled.
        HoughSpaceBinning()
        {
            ;
        };

        int bins;///<Number of bins.

        std::pair<double, double> rangelimits; ///<Range (lower limit, upper limit).

        double rangewidth;///<Range width.

        double binwidth;///<Bin width.
};
}

#endif //HOUGHSPACEBINNING_H
