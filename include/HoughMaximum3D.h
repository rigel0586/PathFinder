#ifndef HOUGHMAXIMUM3D_H
#define HOUGHMAXIMUM3D_H

#include "HoughMaximum2D.h"

namespace pathfinder
{
/**
   Hough Maximum for circles.
 */
class HoughMaximum3D : public HoughMaximum2D
{

    public:
        /**
        Constructor. Parameters are theta, d, omega
             */
        HoughMaximum3D(double, double, double);

        ///Destructor.
        virtual ~HoughMaximum3D()
        {
            ;
        };

        ///Print Hough Maximum 3D.
        void print() const;

        ///returns third component (omega).
        double getThird()
        {
            return (_third);
        };

    private:
        double _third;///<omega

        ///Default constructor, disabled.
        HoughMaximum3D()
        {
            ;
        };//no public default constructor

};//class HoughMaximum3D
}
#endif //HOUGHMAXIMUM3D_H
