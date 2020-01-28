#include "SZFit.h"
#include "ThetaToPhiConverter.h"

using namespace std;
using namespace pathfinder;

bool SZFit::fit(vector<candidateHit> inputHits, HoughMapMaximum* Parameter)
{
    ThetaToPhiConverter* angleConverter = new ThetaToPhiConverter(Parameter);
    double startParams[2];
    startParams[0] = angleConverter->getPhi();
    startParams[1] = Parameter->getSecond();
    delete angleConverter;

    //  cout << "Start Parameters for fit: " << startParams[0] << " " << startParams[1] << endl;
    double slope = tan(startParams[0]);
    // cout << "Slope of straight line sz: " << slope << endl;

    double mean_x = 0.;
    double mean_y = 0.;
    double mean_x2 = 0.;
    double mean_xy = 0.;
    double mean_y2 = 0.;

    for(unsigned int iHit = 0 ; iHit < inputHits.size(); iHit++)
    {
        double pos[2];
        pos[0] = inputHits[iHit].getS();
        pos[1] = inputHits[iHit].getZ();

        mean_x += pos[0];
        mean_y += pos[1];
        mean_x2 += pos[0] * pos[0];
        mean_xy += pos[0] * pos[1];
        mean_y2 += pos[1] * pos[1];

    }

    double tanl_fit;
    double z0_fit;

    double tanlErr_fit;
    double z0Err_fit;

    double m = ((double)inputHits.size() * mean_xy - mean_x * mean_y) /
               ((double)inputHits.size() * mean_x2 - mean_x * mean_x);
    double mprime = ((double)inputHits.size() * mean_xy - mean_x * mean_y) /
                    ((double)inputHits.size() * mean_y2 - mean_y * mean_y);
    mprime = mprime * (-1.); //Note: mprime needs to be multiplied with -1 to get correct result, strange I thought I had carefully thought about the signs. And furthermore it is only true for sz...
    double b = (mean_x2 * mean_y - mean_x * mean_xy) / ((double)inputHits.size() * mean_x2 - mean_x * mean_x);
    double bprime = (mean_y2 * mean_x - mean_y * mean_xy) / ((double)inputHits.size() * mean_y2 - mean_y * mean_y);


    //if slope is smaller than 1, minimize the y-distance of the hits to the track
    if(slope >= -1. && slope <= 1.)
    {
        tanl_fit = m;
        z0_fit = b;
    }
    //if slope is larger than 1, minimize the x-distance of the hits to the track
    else
    {
        tanl_fit = -1. / mprime;
        z0_fit = bprime / mprime;
    }


    double mean_ybmx2 = 0.;
    double mean_ybmx2prime = 0.;
    for(unsigned int iHit = 0 ; iHit < inputHits.size(); iHit++)
    {
        double pos[2];
        pos[0] = inputHits[iHit].getS();
        pos[1] = inputHits[iHit].getZ();

        mean_ybmx2 += (pos[1] - b - m * pos[0]) * (pos[1] - b - m * pos[0]);
        mean_ybmx2prime += (pos[0] - bprime - mprime * pos[1]) * (pos[0] - bprime - mprime * pos[1]);
    }

    double mErr = sqrt(((double)inputHits.size() / ((double)inputHits.size() - 2.) * mean_ybmx2) /
                       ((double)inputHits.size() * mean_x2 - mean_x * mean_x));
    double mprimeErr = sqrt(((double)inputHits.size() / ((double)inputHits.size() - 2.) * mean_ybmx2prime) /
                            ((double)inputHits.size() * mean_y2 - mean_y * mean_y));
    double bErr = sqrt((mean_x2 * mean_ybmx2 / ((double)inputHits.size() - 2.)) / ((double)inputHits.size() * mean_x2 - mean_x * mean_x));
    double bprimeErr = sqrt((mean_y2 * mean_ybmx2prime / ((double)inputHits.size() - 2.)) / ((double)inputHits.size() * mean_y2 - mean_y * mean_y));

    if(slope >= -1. && slope <= 1.)
    {
        tanlErr_fit = mErr;
        z0Err_fit = bErr;
    }
    else
    {
        //Note: no garantee that this is correct...
        tanlErr_fit = mprimeErr / mprime / mprime;
        z0Err_fit = sqrt((bprime * mprimeErr / mprime / mprime) + (bprimeErr / mprime) * (bprimeErr / mprime));
    }


    // cout << "tanl_fit: " << tanl_fit <<" +- "<<tanlErr_fit<< " z0_fit: " << z0_fit <<" +- "<<z0Err_fit<< endl;

    fittedSZTrackParameter = new TrackParameterSZ(tanl_fit, z0_fit, tanlErr_fit, z0Err_fit);

    return(true);

}//bool SZFit::fit(vector<basicHit> inputHits)

