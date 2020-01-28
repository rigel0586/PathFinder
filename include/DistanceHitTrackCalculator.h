#ifndef DISTANCEHITTRACKCALCULATOR_H
#define DISTANCEHITTRACKCALCULATOR_H

#include "basicHit.h"
#include "candidateHit.h"
#include "TrackParameterXY.h"
#include "TrackParameterSZ.h"
#include "HoughMaximum2D.h"
#include "HoughMaximum3D.h"

namespace pathfinder
{
/**
   class calculating the shortest distance between hit and track either in the xy plane or in the sz plane

   For Circle: \f$ d = \min \left( \pm \sqrt{ (x_{hit} - x_{center})^2 + (y_{hit} - y_{center})^2 } - \frac{1}{|\Omega|} \right)\f$

   with: \f$ x_{center} = \left( \frac{1}{\Omega} - d_0 \right) \sin(\phi_0) \f$ and \f$ y_{center} = - \left( \frac{1}{\Omega} - d_0 \right) \cos(\phi_0) \f$

   For Straight Line: \f$ d = | x_{hit} \sin(\phi_0) - y_{hit} \cos(\phi_0) + d_0|\f$
 */
class DistanceHitTrackCalculator
{
    public:
//constructors
        DistanceHitTrackCalculator(basicHit* _hit, TrackParameterXY* _trackparameter);///<\brief Constructor to calculate distance between hit and track in xy. \details Depending on the size of the curvature either for straight line or circle.
        DistanceHitTrackCalculator(basicHit* _hit, HoughMaximum2D* _trackparameter);///<constructor to calculate distance between hit and track in xy for straight lines
        DistanceHitTrackCalculator(basicHit* _hit, HoughMaximum3D* _trackparameter);///<\brief Constructor to calculate distance between hit and track in xy. \details Depending on the size of the curvature either for straight line or circle.
        DistanceHitTrackCalculator(basicHit* _hit, double _phi, double _d0);///<constructor to calculate distance between hit and track in xy for straight lines
        DistanceHitTrackCalculator(basicHit* _hit, double _phi, double _d0, double _omega);///<constructor to calculate distance between hit and track in xy, depending on the size of the curvature either for straight line or circle
        DistanceHitTrackCalculator(candidateHit* _hit, TrackParameterSZ* _trackparameter);///<constructor to calculate distance between hit and track in sz (straight lines only)
        DistanceHitTrackCalculator(candidateHit* _hit, HoughMaximum2D* _trackparameter);///<constructor to calculate distance between hit and track in sz (straight lines only)
        DistanceHitTrackCalculator(candidateHit* _hit, double _phi, double _d0);///<constructor to calculate distance between hit and track in sz (straight lines only)

        ///default destructor
        ~DistanceHitTrackCalculator()
        {
            ;
        };

        /**
           returns distance between hit and track
         */
        double getDistance()
        {
            return distance;
        };

    private:
///disable default constructor
        DistanceHitTrackCalculator();

///function to calculate the center of a circle
        void CalculateCircleCenter();

///function which calculates the distance between hit and track for straight lines in xy
        void CalculateDistanceStraightLineXY();

///function which calculates the distance between hit and track for circles in xy
        void CalculateDistanceCircleXY();

///function which calculates the distance between hit and track for straight lines in sz
        void CalculateDistanceStraightLineSZ();

        double distance;///<distance between hit and track

        double hitX;///<x position of hit
        double hitY;///<y position of hit
        double hitZ;///<z position of hit
        double hitS;///<s of hit

        double phi;///<track parameter phi
        double d0;///<track parameter d0
        double omega;///<track parameter Omega
        double tanl;///< track parameter tan lambda
        double z0;///<track parameter z0

        double centerX;///<x position of circle center
        double centerY;///<y position of circle center
};
}//end namespace

#endif //DISTANCEHITTRACKCALCULATOR
