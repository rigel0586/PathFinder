#include "XYLinearFit.h"
#include "ThetaToPhiConverter.h"

using namespace std;
using namespace pathfinder;

bool XYLinearFit::fit(vector<basicHit> inputHits, HoughMapMaximum* Parameter)
{
    ThetaToPhiConverter* angleConverter = new ThetaToPhiConverter(Parameter);
    double startParams[2];
    startParams[0] = angleConverter->getPhi();
    startParams[1] = Parameter->getSecond();
    delete angleConverter;

    // cout << "Start Parameters for fit: " << startParams[0] << " " << startParams[1] << endl;
    double slope = tan(startParams[0]);

    double mean_x = 0.;
    double mean_y = 0.;
    double mean_x2 = 0.;
    double mean_xy = 0.;
    double mean_y2 = 0.;

    for(unsigned int iHit = 0 ; iHit < inputHits.size(); iHit++)
    {
        double pos[2];
        pos[0] = inputHits[iHit].getX();
        pos[1] = inputHits[iHit].getY();

        mean_x += pos[0];
        mean_y += pos[1];
        mean_x2 += pos[0] * pos[0];
        mean_xy += pos[0] * pos[1];
        mean_y2 += pos[1] * pos[1];
    }

    double phi_fit;
    double d0_fit;
    double omega_fit = 0.;

    double phiErr_fit;
    double d0Err_fit;
    double omegaErr_fit = 0.;

    double m = ((double)inputHits.size() * mean_xy - mean_x * mean_y) /
               ((double)inputHits.size() * mean_x2 - mean_x * mean_x);
    double mprime = ((double)inputHits.size() * mean_xy - mean_x * mean_y) /
                    ((double)inputHits.size() * mean_y2 - mean_y * mean_y);
    double b = (mean_x2 * mean_y - mean_x * mean_xy) / ((double)inputHits.size() * mean_x2 - mean_x * mean_x);
    double bprime = (mean_y2 * mean_x - mean_y * mean_xy) / ((double)inputHits.size() * mean_y2 - mean_y * mean_y);

    //if slope is smaller than 1, minimize the y-distance of the hits to the track
    if(slope >= -1. && slope <= 1.)
    {

        phi_fit = atan2(m, 1);
        d0_fit = cos(phi_fit) * b;
    }
    //if slope is larger than 1, minimize the x-distance of the hits to the track
    else
    {
        //Note: no garantee that this is correct yet
        phi_fit = atan2(-mprime, 1);
        phi_fit = phi_fit - M_PI / 2.;

        d0_fit = -1 * sin(phi_fit) * bprime;
    }

    double mean_ybmx2 = 0.;
    double mean_ybmx2prime = 0.;
    for(unsigned int iHit = 0 ; iHit < inputHits.size(); iHit++)
    {
        double pos[2];
        pos[0] = inputHits[iHit].getX();
        pos[1] = inputHits[iHit].getY();

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
        phiErr_fit = mErr / (1 + m * m);
        d0Err_fit = sqrt((sin(phi_fit) * b * phiErr_fit) * (sin(phi_fit) * b * phiErr_fit) + (cos(phi_fit) * bErr) * (cos(phi_fit) * bErr));
    }
    else
    {
        //Note: no garantee that this is correct...
        phiErr_fit = mprimeErr / (1 + mprime * mprime);
        d0Err_fit = sqrt((cos(phi_fit) * bprime * phiErr_fit) * (cos(phi_fit) * bprime * phiErr_fit) + (sin(phi_fit) * bprimeErr) * (sin(phi_fit) * bprimeErr));
    }

    // cout << "phi_fit: " << phi_fit << " d0_fit: " << d0_fit << endl;

    //cout << "Karimaeki Fit Phi: " << phi_fit <<" +- "<<phiErr_fit<< endl;
    //cout << "Karimaeki Fit D0: " << d0_fit <<" +- "<<d0Err_fit<< endl;


    fittedXYTrackParameter = new TrackParameterXY(phi_fit, d0_fit, omega_fit, phiErr_fit, d0Err_fit, omegaErr_fit);
    fittedXYTrackParameter->setSlopeXY(m);
    fittedXYTrackParameter->setSlopeXYError(mErr);
    fittedXYTrackParameter->setOffsetXY(b);
    fittedXYTrackParameter->setOffsetXYError(bErr);

    return(true);

}//bool XYLinearFit::fit(vector<basicHit> inputHits)

