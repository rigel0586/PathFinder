#ifndef HOUGHSPACEPOINT_H
#define HOUGHSPACEPOINT_H

#include "HoughSpaceBinning.h"
#include <iostream>

namespace pathfinder
{
/**
   A class doing the conversion between (theta,d) and index needed for the maps containing the Hough space.
*/
class HoughSpacePoint
{
    public:
        /**
           Constructor. Parameters are theta, d, binning in theta and binning in d. Does the conversion to bin numbers and index.
         */
        HoughSpacePoint(double _theta, double _d,
                        HoughSpaceBinning _thetaBinning,
                        HoughSpaceBinning _dBinning);

        /**
           Constructor. Parameters are the theta bin number, the d bin number, binning in theta and binning in d. Does the conversion to values and index.
         */
        HoughSpacePoint(int _thetabin, int _dbin,
                        HoughSpaceBinning _thetaBinning,
                        HoughSpaceBinning _dBinning);

        /**
           Constructor. Parameters are the Hough space index, the d bin number, binning in theta and binning in d. Does the conversion to values and bin numbers.
         */
        HoughSpacePoint(int _index,
                        HoughSpaceBinning _thetaBinning,
                        HoughSpaceBinning _dBinning);

        ///Destructor.
        ~HoughSpacePoint()
        {
            ;
        };

        ///Returns theta.
        double getTheta()
        {
            return theta;
        };

        ///Returns d.
        double getD()
        {
            return d;
        };

        ///Returns theta bin number.
        int getThetaBin()
        {
            return thetaBin;
        };

        ///Returns d bin number
        int getDBin()
        {
            return dBin;
        };

        ///returns Hough space index
        int getIndex()
        {
            return index;
        };

        ///Prints the Hough space point (theta and d value, theta and d bin number, Hough space index).
        void Print();

    private:
        ///Default constructor, disabled.
        HoughSpacePoint();

        double theta;///<theta value of Hough space point.
        double d;///<d value of Hough space point.
        int thetaBin;///<theta bin number of Hough space point.
        int dBin;///<d bin number of Hough space point.
        int index;///<Hough space index of Hough space point.
};
}

#endif //HOUGHSPACEPOINT_H
