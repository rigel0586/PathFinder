#ifndef HOUGHMAP_H
#define HOUGHMAP_H

#include "HoughMapMaximum.h"
#include "FinderParameter.h"
#include "basicHit.h"
#include "candidateHit.h"
#include <vector>
#include <map>


namespace pathfinder
{
class HoughMap
{

    public:
        ///destructor
        virtual ~HoughMap()
        {
            ;
        };

        ///clear Hough map
        virtual void clear() = 0;

        ///find maximum
        virtual HoughMapMaximum* findMaximum() = 0;

        ///print Hough map
        virtual void print() const = 0;

        ///returns true if track was found
        virtual bool getTrackFound() = 0;

    protected:

    private:
        ///calculate Hough space
        virtual bool fill() = 0;

};//class HoughMap
}
#endif //HOUGHMAP_H
