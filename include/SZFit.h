#ifndef SZFIT_H
#define SZFIT_H

#include "SimpleFit.h"
#include "candidateHit.h"
//#include "TrackParameter.h"
//#include "FitFunctions.h"
#include <vector>

#include "TrackParameterSZ.h"

namespace pathfinder
{
class SZFit : public SimpleFit
{

    public:
        ///destructor
        virtual ~SZFit()
        {
            ;
        };

        bool fit(std::vector<basicHit>, HoughMapMaximum*)///fit for xy projection is implemented in XYLinearFit and XYCircularFit
        {
            return false;
        };
        bool fit(std::vector<candidateHit>, HoughMapMaximum*);///<straight line fit for sz projection

        TrackParameterSZ* getResult()///returns fitted sz track parameters
        {
            return fittedSZTrackParameter;
        }

    private:
        TrackParameterSZ* fittedSZTrackParameter;///<fitted sz track parameters

};//class SZFit
}
#endif//SZFIT_H
