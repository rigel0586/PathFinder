#ifndef TRACKPARAMETER_H
#define TRACKPARAMETER_H

namespace pathfinder
{
class TrackParameter
{

    public:
        ///destructor
        virtual ~TrackParameter()
        {
            ;
        };

        ///print track parameters
        virtual void print() const = 0;

};//class TrackParameter
}
#endif //TRACKPARAMETER_H
