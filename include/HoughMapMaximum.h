#ifndef HOUGHMAPMAXIMUM_H
#define HOUGHMAPMAXIMUM_H

namespace pathfinder
{
class HoughMapMaximum
{

    public:
        ///Destructor.
        virtual ~HoughMapMaximum()
        {
            ;
        };

        ///Returns theta.
        virtual double getFirst() = 0;

        ///Returns d.
        virtual double getSecond() = 0;

        ///Returns omega.
        virtual double getThird() = 0;

        ///Prints Hough Map Maximum.
        virtual void print() const = 0;

};//class HoughMapMaximum
}
#endif //HOUGHMAPMAXIMUM_H
