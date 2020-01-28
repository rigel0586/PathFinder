#ifndef XYLINEARFIT_H
#define XYLINEARFIT_H

#include "SimpleFit.h"
#include "basicHit.h"
//#include "TrackParameter.h"
//#include "FitFunctions.h"
#include <vector>

#include "TrackParameterXY.h"

namespace pathfinder
{

class XYLinearFit : public SimpleFit
{

    public:
        ///destructor
        virtual ~XYLinearFit()
        {
            ;
        };

        bool fit(std::vector<basicHit>, HoughMapMaximum*);///<straight line fit for xy projection

        bool fit(std::vector<candidateHit>, HoughMapMaximum*)///straight line fit for sz projection is implemented in SZFit
        {
            return false;
        };

        TrackParameterXY* getResult()///return fitted xy track parameters
        {
            return fittedXYTrackParameter;
        }

    private:
        //  TrackParameter fittedXYTrackParameter;
        TrackParameterXY* fittedXYTrackParameter;///<fitted xy track parameters

};//class XYLinearFit
}
#endif//XYLINEARFIT_H
