/*
 * Implementaion of the circle fit as described in V.Karimaeki - "effective circle fitting for particle trajectories"
 */
#include "XYCircularFit.h"
#include "TMatrixD.h"

using namespace std;
using namespace pathfinder;

bool XYCircularFit::fit(vector<basicHit> inputHits, HoughMapMaximum* Parameter)
{

    vector<double> XPos;
    vector<double> YPos;

    //cout << "Start Parameters for fit: " << startParams[0] << " " << startParams[1] << " " << startParams[2] << endl;

    double mean_x = 0.;
    double mean_y = 0.;
    double mean_x2 = 0.;
    double mean_xy = 0.;
    double mean_y2 = 0.;
    double mean_xr2 = 0.;
    double mean_yr2 = 0.;
    double mean_r2 = 0.;
    double mean_r4 = 0.;
    double Sx = 0.;
    double Sy = 0.;
    double Sxy = 0.;
    double Sxx = 0.;
    double Syy = 0.;
    double Sxr2 = 0;
    double Syr2 = 0.;
    double Sr2 = 0.;
    double Sr4 = 0.;
    double Sw = 0.;
    for(unsigned int iHit = 0 ; iHit < inputHits.size(); iHit++)
    {
        double pos[2];
        pos[0] = inputHits[iHit].getX();
        pos[1] = inputHits[iHit].getY();

        double r2 = pos[0] * pos[0] + pos[1] * pos[1];

        Sx += pos[0];
        Sy += pos[1];
        Sxx += pos[0] * pos[0];
        Sxy += pos[0] * pos[1];
        Syy += pos[1] * pos[1];
        Sxr2 += pos[0] * r2;
        Syr2 += pos[1] * r2;
        Sr2 += r2;
        Sr4  += r2 * r2;

        Sw += 1.;

        XPos.push_back(pos[0]);
        YPos.push_back(pos[1]);
    }

    mean_x = Sx / (double)inputHits.size();
    mean_y = Sy / (double)inputHits.size();
    mean_x2 = Sxx / (double)inputHits.size();
    mean_xy = Sxy / (double)inputHits.size();
    mean_y2 = Syy / (double)inputHits.size();
    mean_xr2 = Sxr2 / (double)inputHits.size();
    mean_yr2 = Syr2 / (double)inputHits.size();
    mean_r2 = Sr2 / (double)inputHits.size();
    mean_r4 = Sr4 / (double)inputHits.size();

    double Cxx = mean_x2 - mean_x * mean_x;
    double Cxy = mean_xy - mean_x * mean_y;
    double Cyy = mean_y2 - mean_y * mean_y;
    double Cxr2 = mean_xr2 - mean_x * mean_r2;
    double Cyr2 = mean_yr2 - mean_y * mean_r2;
    double Cr2r2 = mean_r4 - mean_r2 * mean_r2;

    double q1 = Cr2r2 * Cxy - Cxr2 * Cyr2;
    double q2 = Cr2r2 * (Cxx - Cyy) - Cxr2 * Cxr2 + Cyr2 * Cyr2;

    double phi_fit = 0.5 * atan2(2 * q1, q2);

    double kappa = (sin(phi_fit) * Cxr2 - cos(phi_fit) * Cyr2) / Cr2r2;

    double delta = -kappa * mean_r2 + sin(phi_fit) * mean_x - cos(phi_fit) * mean_y;

    double omega_fit = 2 * kappa / sqrt(1 - 4 * delta * kappa);

    double d0_fit = 2 * delta / (1 + sqrt(1 - 4 * delta * kappa));

    //calculation of errors
    double u = 1 + omega_fit * d0_fit;
    double Sa = sin(phi_fit) * Sx - cos(phi_fit) * Sy;
    double Sb = cos(phi_fit) * Sx + sin(phi_fit) * Sy;
    double Sg = (sin(phi_fit) * sin(phi_fit) - cos(phi_fit) * cos(phi_fit)) * Sxy + sin(phi_fit) * cos(phi_fit) * (Sxx - Syy);
    double Sd = sin(phi_fit) * Sxr2 - cos(phi_fit) * Syr2;
    double Saa = sin(phi_fit) * sin(phi_fit) * Sxx - 2 * sin(phi_fit) * cos(phi_fit) * Sxy + cos(phi_fit) * cos(phi_fit) * Syy;

    TMatrixD V_inv(3, 3);

    V_inv(0, 0) = 0.25 * Sr4 - d0_fit * (Sd - d0_fit * (Saa = 0.5 * Sr2 - d0_fit * (Sa - 0.25 * d0_fit * Sw)));
    V_inv(0, 1) = -u * (0.5 * (cos(phi_fit) * Sxr2 + sin(phi_fit) * Syr2) - d0_fit * (Sg - 0.5 * d0_fit * Sb));
    V_inv(0, 2) = omega_fit * (-0.5 * Sd + d0_fit * Saa) + 0.5 * u * Sr2 - 0.5 * d0_fit * ((2 * u + omega_fit * d0_fit) * Sa - u * d0_fit * Sw);
    V_inv(1, 0) = -u * (0.5 * (cos(phi_fit) * Sxr2 + sin(phi_fit) * Syr2) - d0_fit * (Sg - 0.5 * d0_fit * Sb));
    V_inv(1, 1) = u * u * (cos(phi_fit) * cos(phi_fit) * Sxx + sin(2 * phi_fit) * Sxy + sin(phi_fit) * sin(phi_fit) * Syy);
    V_inv(1, 2) = u * (omega_fit * Sg - u * Sb);
    V_inv(2, 0) = omega_fit * (-0.5 * Sd + d0_fit * Saa) + 0.5 * u * Sr2 - 0.5 * d0_fit * ((2 * u + omega_fit * d0_fit) * Sa - u * d0_fit * Sw);
    V_inv(2, 1) = u * (omega_fit * Sg - u * Sb);
    V_inv(2, 2) = omega_fit * (omega_fit * Saa - 2 * u * Sa) + u * u * Sw;

    TMatrixD V = V_inv.InvertFast();//Attention: This line changes V_inv!!!

    double phiErr_fit = sqrt(abs(V(1, 1)));
    double d0Err_fit = sqrt(abs(V(2, 2)));
    double omegaErr_fit = sqrt(abs(V(0, 0)));
    /*
    cout << "Karimaeki Fit Phi: " << phi_fit <<" +- "<<phiErr_fit<< endl;
    cout << "Karimaeki Fit D0: " << d0_fit <<" +- "<<d0Err_fit<< endl;
    cout << "Karimaeki Fit Omega: " << omega_fit <<" +- "<<omegaErr_fit<< endl;
    */
    //fittedXYTrackParameter = new TrackParameterXY(phi, d0, omega);
    fittedXYTrackParameter = new TrackParameterXY(phi_fit, -d0_fit, omega_fit, phiErr_fit, d0Err_fit, omegaErr_fit);

    //    return (fitResult.IsValid());
    return(true);
}//bool XYLinearFit::fit(vector<basicHit> inputHits)

