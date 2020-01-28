#ifndef TRACKPARAMETERXY_H
#define TRACKPARAMETERXY_H

#include "TrackParameter.h"

namespace pathfinder
{
class TrackParameterXY : public TrackParameter
{

    public:
        /**
        Constructor. Parameters are phi, d0, omega. Uncertainties are set to 0.
        */
        TrackParameterXY(double, double, double);

        /**
           Constructor. Parameters are phi, d0, omega and their uncertainties phierr, d0err, omegaerr
         */
        TrackParameterXY(double, double, double, double, double, double);

        /**
           Constructor. Parameter is TrackParameterXY
        */
        TrackParameterXY(const TrackParameterXY &);

        ///Destructor.
        virtual ~TrackParameterXY()
        {
            ;
        };

        ///print track parameters and their uncertainties
        virtual void print() const;

        ///returns phi
        virtual double getPhi() const
        {
            return phi;
        };

        ///returns d0
        virtual double getDZero() const
        {
            return dzero;
        };

        ///returns omega
        virtual double getOmega() const
        {
            return omega;
        };

        ///retruns uncertainty of phi
        virtual double getPhiError() const
        {
            return phi_err;
        };

        ///returns uncertainty 0f d0
        virtual double getDZeroError() const
        {
            return dzero_err;
        };

        ///returns uncertainty of omega
        virtual double getOmegaError() const
        {
            return omega_err;
        };


        //get and set functions for slope and offset of straight line, only for debugging

        ///Set slope. For debugging only.
        virtual void setSlopeXY(double m)
        {
            slope = m;
        };
        ///Set slope uncertainty. For debugging only.
        virtual void setSlopeXYError(double mErr)
        {
            slope_err = mErr;
        };
        ///Set offset. For debugging only.
        virtual void setOffsetXY(double b)
        {
            offset = b;
        };
        ///Set offset uncertainty. For debugging only.
        virtual void setOffsetXYError(double bErr)
        {
            offset_err = bErr;
        };
        ///Returns slope. For debugging only.
        virtual double getSlopeXY() const
        {
            return slope;
        };
        ///Returns slope uncertainty. For debugging only.
        virtual double getSlopeXYError() const
        {
            return slope_err;
        };
        ///Returns offset. For debugging only.
        virtual double getOffsetXY() const
        {
            return offset;
        };
        ///Returns offset uncertainty. For debugging only.
        virtual double getOffsetXYError() const
        {
            return offset_err;
        };


    protected:
        ///default constructor, disabled.
        TrackParameterXY()
        {
            ;
        }; // no public default constructor
        double phi;///<track parameter phi
        double dzero;///<track parameter d0
        double omega;///<track parameter omega

        double phi_err;///<uncertainty of phi
        double dzero_err;///<uncertainty of d0
        double omega_err;///<uncertainty of omega

        //slope and offset of straight line, only needed for debugging
        double slope;///<slope. for debugging only.
        double offset;///<offset. for debugging only.
        double slope_err;///<uncertainty of slope. for debugging only.
        double offset_err;///<uncertainty of offset. for debugging only.

};//class TrackParameterXY
}
#endif //TRACKPARAMETER_H
