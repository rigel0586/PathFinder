#ifndef XYCIRCULARFIT_H
#define XYCIRCULARFIT_H

#include "SimpleFit.h"
#include "basicHit.h"
//#include "TrackParameter.h"
//#include "FitFunctions.h"
#include <vector>

#include "TrackParameterXY.h"
namespace pathfinder
{
/**
   Class implementing a circle fit.

   Discription of the method in: V. Karimaeki, "Effective circle fitting for particle trajectories", Nucl. Instr. Meth. A 305, pages 187-191.
 */
class XYCircularFit : public SimpleFit
{

    public:
        ///destructor
        virtual ~XYCircularFit()
        {
            ;
        };

        bool fit(std::vector<basicHit>, HoughMapMaximum*);///<circular fit in xy projection
        bool fit(std::vector<candidateHit>, HoughMapMaximum*)///not implemented, no circle fit needed in sz projection
        {
            return false;
        };

        ///return fitted xy track parameter
        TrackParameterXY* getResult()
        {
            return fittedXYTrackParameter;
        }


    private:
        TrackParameterXY* fittedXYTrackParameter;///<fitted xy track parameters

};//class XYCircularFit
}
#endif//XYCIRCULARFIT_H
