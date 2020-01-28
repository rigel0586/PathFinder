#ifndef HOUGHMAXIMUM2D_H
#define HOUGHMAXIMUM2D_H

#include "HoughMapMaximum.h"

namespace pathfinder
{
/**
   Hough Maximum for straight lines.
*/
class HoughMaximum2D : public HoughMapMaximum
{

    public:
        /**
        Constructor. Parameters are theta and d.
             */
        HoughMaximum2D(double, double);

        /**
           Destructor.
         */
        virtual ~HoughMaximum2D()
        {
            ;
        };

        ///Prints Hough Maximum 2D.
        virtual void print() const;

        ///Returns first component (theta).
        double getFirst()
        {
            return (_first);
        };

        ///Returns second component (d)
        double getSecond()
        {
            return (_second);
        };

        ///Returns 0.
        double getThird()
        {
            return (0.);
        };


    protected:
        double _first;///<theta
        double _second;///<d

        ///Default constructor, disabled.
        HoughMaximum2D()
        {
            ;
        };//no public default constructor

    private:

};//class 2DHoughMaximum
}
#endif //2DHOUGHMAXIMUM_H
