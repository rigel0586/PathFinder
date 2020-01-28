#ifndef TGTRACKPARMETERLIMITS_H
#define TGTRACKPARMETERLIMITS_H

namespace pathfinder
{
/**
   This class is needed by the track generator. It contains the parameter ranges in which tracks are created.
 */
class TGTrackParameterLimits
{
        /*
          class containing upper and lower limits of track parameters to be simulated
        */
    public:
        /**
        Constructor. Parameters are: minimum phi, maximum phi, minimum d0, maximum d0, minimum r, maximum r, minimum tan lambda, maximum tan lambda, minimum z0, maximum z0
             */
        TGTrackParameterLimits(double _minphi,
                               double _maxphi,
                               double _mind0,
                               double _maxd0,
                               double _minr,
                               double _maxr,
                               double _mintanl,
                               double _maxtanl,
                               double _minz0,
                               double _maxz0)
            : minphi(_minphi), maxphi(_maxphi), mind0(_mind0), maxd0(_maxd0), minr(_minr), maxr(_maxr),
              mintanl(_mintanl), maxtanl(_maxtanl), minz0(_minz0), maxz0(_maxz0)
        {
            ;
        };

        /**
        Destructor.
             */
        ~TGTrackParameterLimits()
        {
            ;
        };

        ///returns minimum phi
        double getMinPhi()
        {
            return minphi;
        };

        ///returns maximum phi
        double getMaxPhi()
        {
            return maxphi;
        };

        ///returns minimum d0
        double getMinD0()
        {
            return mind0;
        };

        ///returns maximum d0
        double getMaxD0()
        {
            return maxd0;
        };

        ///returns minimum r
        double getMinR()
        {
            return minr;
        };

        ///returns maximum r
        double getMaxR()
        {
            return maxr;
        };

        ///returns minimum tan lambda
        double getMinTanL()
        {
            return mintanl;
        };

        ///returns maximum tan lambda
        double getMaxTanL()
        {
            return maxtanl;
        };

        ///returns minimum z0
        double getMinZ0()
        {
            return minz0;
        };

        ///returns maximum z0
        double getMaxZ0()
        {
            return maxz0;
        };

    private:
        ///default constructor, disabled.
        TGTrackParameterLimits()
        {
            ;
        };

        double minphi;///<minimum phi
        double maxphi;///<maximum phi
        double mind0;///<minimum d0
        double maxd0;///<maximum d0
        double minr;///<minimum r
        double maxr;///<maximum r
        double mintanl;///<minimum tan lambda
        double maxtanl;///<maximum tan lambda
        double minz0;///<minimum z0
        double maxz0;///<maximum z0
};
}
#endif//TGTRACKPARMETERLIMITS_H
