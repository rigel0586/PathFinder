#ifndef TGEVENTTYPE_H
#define TGEVENTTYPE_H

namespace pathfinder
{
/**
   This class is needed by the track generator. It contains information about how the events should look like:
   - number of hits on track
   - number of tracks per event
   - number of noise hits
   - amount of smearing (amount by which hits are shifted off the track)
   - number of events
 */
class TGEventType
{
    public:

        /**
        Constructor. The parameters are: number of hits on track, number of tracks in event, number of noise hits in event, amount of smearing, number of events
             */
        TGEventType(unsigned int _nhits, unsigned int _ntracks, unsigned int _nnoise, double _smearing , unsigned int _nevents):
            nhits(_nhits), ntracks(_ntracks), nnoise(_nnoise), smearing(_smearing), nevents(_nevents)
        {
            ;
        };

        /**
        Destructor.
             */
        ~TGEventType()
        {
            ;
        };

        ///returns number of hits on track.
        unsigned int getNHits()
        {
            return nhits;
        };

        ///returns number of track per event.
        unsigned int getNTracks()
        {
            return ntracks;
        };

        ///returns number of noise hits per event.
        unsigned int getNNoise()
        {
            return nnoise;
        };

        ///returns number of events.
        unsigned int getNEvents()
        {
            return nevents;
        };

        ///returns amount of smearint
        double getSmearing()
        {
            return smearing;
        };

    private:
        ///default constructor, disabled.
        TGEventType()
        {
            ;
        };

        unsigned int nhits;///<number of hits on track
        unsigned int ntracks;///<number of tracks per event
        unsigned int nnoise;///<number of noinse hits per event
        double smearing;///<amount of smearing
        unsigned int nevents;///<number of events
};
}
#endif //TGEVENTTYPE_H
