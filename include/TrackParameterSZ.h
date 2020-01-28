#ifndef TRACKPARAMETERSZ_H
#define TRACKPARAMETERSZ_H

#include "TrackParameter.h"

namespace pathfinder
{
class TrackParameterSZ : public TrackParameter
{

    public:
        /**
        Constructor. Parameters are tan lambda and z0. Uncertainties are set to 0.
             */
        TrackParameterSZ(double, double);

        /**
        Constructor. Parameters are tan lambda, z0 and their uncertainties tanlerr and z0err
             */
        TrackParameterSZ(double, double, double, double);

        /**
           Constructor. Parameter is TrackParameterSZ
         */
        TrackParameterSZ(const TrackParameterSZ &);

        /**
           Destructor.
         */
        virtual ~TrackParameterSZ()
        {
            ;
        };

        ///print track parameters and their uncertainties
        virtual void print() const;

        ///returns tan lambda
        virtual double getTanLambda() const
        {
            return tanlambda;
        };

        ///returns z0
        virtual double getZZero() const
        {
            return zzero;
        };

        ///returns uncertainty of tan lambda
        virtual double getTanLambdaError() const
        {
            return tanlambda_err;
        };

        ///returns uncertainty of z0
        virtual double getZZeroError() const
        {
            return zzero_err;
        };


    protected:
        ///default constructor, disabled.
        TrackParameterSZ()
        {
            ;
        }; // no public default constructor

        double tanlambda;///<track parameter tan lambda
        double zzero;///<track parameter z0
        double tanlambda_err;///<uncertainty of tan lambda
        double zzero_err;///<uncertainty of z0

};//class TrackParameterSZ
}
#endif //TRACKPARAMETERSZ_H
