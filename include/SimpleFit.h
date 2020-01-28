#ifndef SIMPLEFIT_H
#define SIMPLEFIT_H

#include "basicHit.h"
#include "candidateHit.h"
//#include "TrackParameter.h"
#include "HoughMaximum2D.h"
#include "HoughMaximum3D.h"
#include <vector>
#include <cmath>
#include <iostream>

#include "TrackParameter.h"

namespace pathfinder
{
class SimpleFit
{

    public:
        ///virtual destructor
        virtual ~SimpleFit()
        {
            ;
        }

        ///fittin xy (either straight line or circle)
        virtual bool fit(std::vector<basicHit>, HoughMapMaximum*) = 0;
        //  virtual bool fit(std::vector<basicHit>, HoughMapMaximum*) = 0;//xy projection
        ///fit in sz (straight line)
        virtual bool fit(std::vector<candidateHit>, HoughMapMaximum*) = 0;//sz projection

        ///return fitted track parameters
        virtual TrackParameter* getResult() = 0;

        // virtual void printFitResult() const;


};//class SimpleFit
}
#endif//SIMPLEFIT_H
