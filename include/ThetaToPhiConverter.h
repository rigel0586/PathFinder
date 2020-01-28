#ifndef THETATOPHICONVERTER_H
#define THETATOPHICONVERTER_H

#include "HoughMapMaximum.h"
//#include "HoughMaximum2D.h"
//#include "HoughMaximum3D.h"

namespace pathfinder
{
/**
   class converting theta (parameter used in the Hough transformation) to phi (lcio track parameter)
 */
class ThetaToPhiConverter
{
    public:
        ThetaToPhiConverter(double _theta, double _d0);///<Constructor using theta and d0
        ThetaToPhiConverter(HoughMapMaximum* _intersection);///<Constructor using HoughMapMaximum, which is in principle theta and d0
        //    ThetaToPhiConverter(HoughMaximum2D* _intersection);
        //ThetaToPhiConverter(HoughMaximum3D* _intersection);

        ///Destructor.
        ~ThetaToPhiConverter()
        {
            ;
        };

        ///Returns the value for phi.
        double getPhi()
        {
            return phi;
        };

    private:
        ///default constructor, disabled
        ThetaToPhiConverter();

        void CalculatePhi();///<function calculating phi from d0 and theta

        double theta;///<theta
        double d0;///<d0
        double phi;///<phi
};

}//end namespace

#endif // THETATOPHICONVERTER_H
