#include "TrackFinderTrack.h"
#include <iostream>
using namespace std;
using namespace pathfinder;

TrackFinderTrack::TrackFinderTrack(const TrackParameterFull& tp, const std::vector<basicHit>& accHits)
    : hitsOnTrack(accHits)
{
    trackParameter = new TrackParameterFull(tp);
}



TrackFinderTrack::TrackFinderTrack(const TrackParameterFull& tp, const std::vector<basicHit>& accHits, const std::vector<basicHit>& rejHits)
    : hitsOnTrack(accHits), rejectedHits(rejHits)
{
    trackParameter = new TrackParameterFull(tp);
}



TrackFinderTrack::~TrackFinderTrack()
{
//    if(trackParameter)
//      delete trackParameter;
}


void TrackFinderTrack::print()
{
    cout << "[TrackFinderTrack]::start printing track parameters:" << endl;
    trackParameter->print();
    cout << "[TrackFinderTrack]::end printing track parameters; start printing hits on track:" << endl;
    for(vector<basicHit>::iterator hit = hitsOnTrack.begin(); hit < hitsOnTrack.end(); hit++)
        hit->print();
    cout << "[TrackFinderTrack]::end printing hits on track; start printing rejected:" << endl;
    for(vector<basicHit>::iterator hit = rejectedHits.begin(); hit < rejectedHits.end(); hit++)
        hit->print();
    cout << "[TrackFinderTrack]::end printing rejected hits." << endl;
}
