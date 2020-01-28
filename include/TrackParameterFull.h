#ifndef TRACKPARAMETERFULL_H
#define TRACKPARAMETERFULL_H

#include "TrackParameterXY.h"
#include "TrackParameterSZ.h"

namespace pathfinder
{
class TrackParameterFull : public TrackParameterXY, public TrackParameterSZ
{

    public:
        TrackParameterFull(const TrackParameterFull&);///<Constructor using TrackParameterFull
        TrackParameterFull(const double, const double, const double, const double, const double);///<Constructor using phi, d0, omega, tan lambda, z0
        TrackParameterFull(const double, const double, const double, const double, const double,
                           const double, const double, const double, const double, const double);///<Constructor using phi, d0, omega, tan lambda, z0 and the uncertainties of the parameters in the same order
        TrackParameterFull(const TrackParameterXY&, const TrackParameterSZ&);///<Constructor using TrackParameterXY and TrackParameterSZ

        ///Destructor.
        virtual ~TrackParameterFull()
        {
            ;
        };

        ///print track parameters
        virtual void print() const;
    private:
        ///default constructor, disabled
        TrackParameterFull()
        {
            ;
        }; // no public default constructor

};//class TrackParameterFull
}
#endif //TRACKPARAMETERFULL_H
