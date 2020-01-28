#include "TrackGenerator.h"

//#include "basicHit.h"

#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;
using namespace pathfinder;

//old constructor, do not use anymore
TrackGenerator::TrackGenerator(int _tt,
                               unsigned int _tpn,
                               unsigned int _nnoise,
                               unsigned int _ntracks,
                               unsigned int _nevents,
                               double _smearing,
                               double _seed)
    : track_type(_tt), tpn(_tpn), nnoise(_nnoise), ntracks(_ntracks), nevents(_nevents),
      smearing(_smearing), trackseed(_seed),
      controlTreeRand(NULL),
      noisePosTree(NULL),
      randomSmearingTree(NULL),
      file(NULL),
      d0rand(0.),
      phirand(0.),
      omegarand(0.),
      tanlrand(0.),
      z0rand(0.),
      eventrand(0),
      trackrand(0),
      inoise(0),
      ievent(0),
      noisex(0.),
      noisey(0.),
      noisez(0.),
      randgaus(0.)
{

    cout << "Warning! Old constructor, do not use anymore!" << endl;

    padsizey = 7.;

    phiLimits.first = M_PI / 2. - 0.5;
    phiLimits.first = M_PI / 2. + 0.5;
    d0Limits.first = 0.;
    d0Limits.second = 60.;
    tanlLimits.first = -2.;
    tanlLimits.second = 2.;
    z0Limits.first = 0.;
    z0Limits.second = 666.;

    if(track_type == 0)
    {
        omegaLimits.first = 0.;
        omegaLimits.second = 0.;
    }
    if(track_type == 1 || track_type == 2)
    {
        //todo: omega here is used as r!!!
        omegaLimits.first = 40.;
        omegaLimits.second = 1040;
    }
}//constructor


//new constructor
TrackGenerator::TrackGenerator(int _tt,
                               TGTrackParameterLimits _paramLimits,
                               TGEventType _evtType,
                               TGDetectorType _detType)
    : track_type(_tt) ,
      controlTreeRand(NULL),
      noisePosTree(NULL),
      randomSmearingTree(NULL),
      file(NULL),
      d0rand(0.),
      phirand(0.),
      omegarand(0.),
      tanlrand(0.),
      z0rand(0.),
      eventrand(0),
      trackrand(0),
      inoise(0),
      ievent(0),
      noisex(0.),
      noisey(0.),
      noisez(0.),
      randgaus(0.)
{
    tpn = _evtType.getNHits();
    nnoise = _evtType.getNNoise();
    ntracks = _evtType.getNTracks();
    nevents = _evtType.getNEvents();
    smearing = _evtType.getSmearing();

    phiLimits.first = _paramLimits.getMinPhi();
    phiLimits.second = _paramLimits.getMaxPhi();
    d0Limits.first = _paramLimits.getMinD0();
    d0Limits.second = _paramLimits.getMaxD0();
    omegaLimits.first = _paramLimits.getMinR();
    omegaLimits.second = _paramLimits.getMaxR();
    tanlLimits.first = _paramLimits.getMinTanL();
    tanlLimits.second = _paramLimits.getMaxTanL();
    z0Limits.first = _paramLimits.getMinZ0();
    z0Limits.second = _paramLimits.getMaxZ0();

    padplaneX.first = _detType.getPadPlaneXmin();
    padplaneX.second = _detType.getPadPlaneXmax();
    padplaneY.first = _detType.getPadPlaneYmin();
    padplaneY.second = _detType.getPadPlaneYmax();
    padplaneZ.first = _detType.getPadPlaneZmin();
    padplaneZ.second = _detType.getPadPlaneZmax();
    padsizey = _detType.getPadSizeY();

    file = new TFile("TrackGeneratorControlPlots.root", "recreate");

    controlTreeRand = new TTree("controlTreeRand", "controlTreeRand");
    noisePosTree = new TTree("noisePosTree", "noisePosTree");
    randomSmearingTree = new TTree("randomSmearingTree", "randomSmearingTree");

    controlTreeRand->Branch("RandomD0", &d0rand, "RandomD0/F");
    controlTreeRand->Branch("RandomPhi", &phirand, "RandomPhi/F");
    controlTreeRand->Branch("RandomOmega", &omegarand, "RandomOmega/F");
    controlTreeRand->Branch("RandomTanL", &tanlrand, "RandomTanL/F");
    controlTreeRand->Branch("RandomZ0", &z0rand, "RandomZ0/F");
    controlTreeRand->Branch("EventNumber", &eventrand, "EventNumber/I");
    controlTreeRand->Branch("TrackNumber", &trackrand, "TrackNumber/I");
    noisePosTree->Branch("inoise", &inoise, "inoise/I");
    noisePosTree->Branch("ievent", &ievent, "ievent/I");
    noisePosTree->Branch("noiseX", &noisex, "noiseX/F");
    noisePosTree->Branch("noiseY", &noisey, "noiseY/F");
    noisePosTree->Branch("noiseZ", &noisez, "noiseZ/F");
    randomSmearingTree->Branch("randomgaus", &randgaus, "randgaus/F");
}



TrackGenerator::~TrackGenerator()
{
    controlTreeRand->Write();
    noisePosTree->Write();
    randomSmearingTree->Write();

    file->Close();

    for(std::vector<TrackFinderTrack*>::iterator iter = generatorTracks.begin(), endIter = generatorTracks.end(); iter < endIter; ++iter)
        delete *iter;
    // delete everything you create with "new" -> couldn't find another use of this . CR, 24.01.2012

    for(std::vector<TrackParameterFull*>::iterator iter = generatorTrackParameters.begin(); iter != generatorTrackParameters.end(); ++iter)
        delete *iter;

    //delete controlTreeRand;
    //delete noisePosTree;
    //delete file;
}


bool TrackGenerator::generateTracks(unsigned int e)
{
    generatorTracks.clear();
    generatorTrackParameters.clear();
    hitsInEvent.clear();
    noiseHits.clear();

    gROOT->SetStyle("Plain");
    gStyle->SetPalette(1);
    gStyle->SetOptStat(110011);
    gROOT->ForceStyle();

    //  for(unsigned int e = 0; e<nevents; e++)
    //{
    cout << "creating event " << e << " of " << nevents << endl;
    unsigned int n = 0;
    //cout<<"generatorTracks.size() = "<<generatorTracks.size()<<" ntracks "<<ntracks<<endl;
    while(generatorTracks.size() < ntracks)
    {
        TrackParameterFull* generatorTrackParameter;
        //cout<<"crating track "<<n<<" of "<<ntracks<<endl;
        bool hitsInTPC = true;
        trackseed = (double)e;
        double seed = trackseed * trackseed * trackseed / (double)nevents + (double)n * (double)n * (double)n / (double)ntracks;

        if(track_type == 0) //straight line
        {
            generatorTrackParameter = new TrackParameterFull(uniform(phiLimits.first,
                                                                     phiLimits.second,
                                                                     seed * n + seed * trackseed
                                                                    ),
                                                             uniform(d0Limits.first,
                                                                     d0Limits.second,
                                                                     seed + trackseed + n
                                                                    ),
                                                             0.,
                                                             uniform(tanlLimits.first,
                                                                     tanlLimits.second,
                                                                     seed + trackseed * trackseed + n * n
                                                                    ) ,
                                                             uniform(z0Limits.first,
                                                                     z0Limits.second,
                                                                     seed + trackseed * trackseed * trackseed / (double)nevents / (double)nevents / (double)nevents - (trackseed * trackseed + 15.) + n * n * n + 30.
                                                                    )
                                                            );


            d0rand = (float)(generatorTrackParameter->getDZero());
            phirand = (float)(generatorTrackParameter->getPhi());
            omegarand = (float)(generatorTrackParameter->getOmega());
            tanlrand = (float)(generatorTrackParameter->getTanLambda());
            z0rand = (float)(generatorTrackParameter->getZZero());
            eventrand = (int)e;
            trackrand = (int)n;
            controlTreeRand->Fill();
        }
        if(track_type == 1 || track_type == 2) //helix segment || curler
        {
            //cout<<"Track type helix"<<endl;
            generatorTrackParameter = new TrackParameterFull(uniform(phiLimits.first,
                                                                     phiLimits.second,
                                                                     seed * n + seed * trackseed),
                                                             uniform(d0Limits.first,
                                                                     d0Limits.second,
                                                                     seed + trackseed + n),
                                                             1. / (uniform(omegaLimits.first,
                                                                           omegaLimits.second,
                                                                           seed + trackseed * trackseed * trackseed + 5. + n * n)),
                                                             uniform(tanlLimits.first,
                                                                     tanlLimits.second,
                                                                     seed + trackseed * trackseed + n * n),
                                                             uniform(z0Limits.first,
                                                                     z0Limits.second,
                                                                     seed + trackseed * trackseed * trackseed / (double)nevents / (double)nevents / (double)nevents - (trackseed * trackseed + 15.) + n * n * n + 30.)
                                                            );

            d0rand = (float)(generatorTrackParameter->getDZero());
            phirand = (float)(generatorTrackParameter->getPhi());
            omegarand = (float)(generatorTrackParameter->getOmega());
            tanlrand = (float)(generatorTrackParameter->getTanLambda());
            z0rand = (float)(generatorTrackParameter->getZZero());
            eventrand = (int)e;
            trackrand = (int)n;

            //cout<<"Filling root tree"<<endl;
            controlTreeRand->Fill();
        }


        vector<double> valuesY, valuesX, valuesZ;
        //calculate hit positions for track
        valuesY = computeY();
        valuesX = computeX(valuesY, generatorTrackParameter);

        if(track_type == 2) //curler
        {
            valuesY = correctY(valuesY, generatorTrackParameter);
        }
        //cout<<"compute z ...";
        if(valuesX.size() != valuesY.size())
        {
            cout << "Vectors do not have the same sizes: " << valuesX.size() << " " << valuesY.size() << endl;
            break;
        }
        valuesZ = computeZ(valuesX, valuesY, generatorTrackParameter);

        vector<basicHit> tempBasicHitVec;

        for(unsigned int step = 0; step < valuesY.size(); ++step)
        {
            double position[3] = {valuesX.at(step), valuesY.at(step), valuesZ.at(step)};

            basicHit tempBasicHit(position[0], position[1], position[2]);
            hitsInEvent.push_back(tempBasicHit);//all hits in event
            tempBasicHitVec.push_back(tempBasicHit);//only hits in current track
            if(position[0] < padplaneX.first || position[0] > padplaneX.second ||
                    position[1] < (padplaneY.first - padsizey / 2.) || position[1] > (padplaneY.second + padsizey / 2.) ||
                    position[2] < padplaneZ.first || position[2] > padplaneZ.second ||
                    position[0] != position[0] || position[2] != position[2]) //position is not a number
            {
                hitsInTPC = false;
            }

        }

        //for curler hits can lie outside TPC, at least for now
        //TODO: remove this for straight lines later
        if(track_type == 2 || track_type == 0 || track_type == 1)
        {
            hitsInTPC = true;
        }

        if(hitsInTPC == true)
        {
            //save track
            generatorTrackParameters.push_back(generatorTrackParameter);
            generatorTracks.push_back(new TrackFinderTrack(*generatorTrackParameter, tempBasicHitVec));
            cout << "Track was added!" << endl;
        }
        else
        {
            cout << "Track was NOT added!" << endl;
        }

        n++;

    }

    //add noise
    for(unsigned int i = 0; i < nnoise; i++)
    {
        double randomSeed = (3826 * (double)i * ((double)e + 1) + (double)i * 5 * (double)i * ((double)e + 1)) / (double)nnoise;
        double randomRow = floor(uniform(-1.*(double)tpn, (double)tpn, randomSeed));

        cout << "yrange: " << -1.*(double)tpn << " " << (double)tpn << endl;
        cout << "seed: " << randomSeed << endl;
        cout << "Random Row for Noise hits: " << randomRow << endl;

        double x = uniform(padplaneX.first, padplaneX.second, 0.213465 * ((double)i + 1) * (((double)e + 1) * ((double)e + 5.0) + 36493));
        double y;
        if(padplaneY.second < 0.)
        {
            y = ((-1.) * padsizey * (randomRow + 1.) + padsizey / 2.);
        }
        else
        {
            y = (padsizey * (randomRow + 1.) - padsizey / 2.);
        }


        double z = uniform(padplaneZ.first, padplaneZ.second, ((double)i * (double)i * ((double)e + 1) * ((double)e + 1) + ((double)e + 1)) / (double)nnoise);

        noisex = x;
        noisey = y;
        noisez = z;
        inoise = i;
        ievent = e;
        noisePosTree->Fill();

        basicHit tempHit(x, y, z);
        hitsInEvent.push_back(tempHit);
        noiseHits.push_back(tempHit);
    }//while

    return true;
}//genertateTrack

vector<double> TrackGenerator::computeX(vector<double> valuesY, TrackParameterFull* generatorTrackParameter)
{
    vector<double> xvals;
    vector<double> newyvals;

    //loop over hits

    unsigned int nYValues = valuesY.size();

    for(unsigned int steps = 0; steps < nYValues; ++ steps)
    {
        double x;
        if(track_type == 0 /*straight line*/)
        {
            x = (cos(generatorTrackParameter->getPhi()) * valuesY.at(steps) - generatorTrackParameter->getDZero()) / sin(generatorTrackParameter->getPhi());

            //apply smearing
            double seed = steps * steps * steps * (randgaus + 1.253) / tpn ;
            randgaus = gaus(-1., 1., seed);
            randomSmearingTree->Fill();
            x = x + smearing * randgaus;

            xvals.push_back(x);
        }
        if(track_type == 1)
        {
            double tempx1, tempx2;
            double xm, ym;
            double R = 1. / generatorTrackParameter->getOmega();//correct in gnuplot
            xm = (R - generatorTrackParameter->getDZero()) * sin(generatorTrackParameter->getPhi());
            ym = -(R - generatorTrackParameter->getDZero()) * cos(generatorTrackParameter->getPhi());
            tempx1 = xm + sqrt(R * R - (valuesY.at(steps) - ym) * (valuesY.at(steps) - ym));
            tempx2 = xm - sqrt(R * R - (valuesY.at(steps) - ym) * (valuesY.at(steps) - ym));

            if(abs(tempx1) < abs(tempx2))
            {
                double seed = steps * steps * steps / tpn * (double)track_type;
                randgaus = gaus(-1., 1., seed);
                randomSmearingTree->Fill();
                x = tempx1 + smearing * randgaus;
                xvals.push_back(x);
            }
            else
            {
                double seed = steps * steps * steps / tpn * (double)track_type;
                randgaus = gaus(-1., 1., seed);
                randomSmearingTree->Fill();
                x = tempx2 + smearing * randgaus;
                xvals.push_back(x);
            }
        }
        if(track_type == 2) //curler
        {
            double tempx1, tempx2;
            double xm, ym;
            double R = 1. / generatorTrackParameter->getOmega();
            xm = (R - generatorTrackParameter->getDZero()) * sin(generatorTrackParameter->getPhi());
            ym = -(R - generatorTrackParameter->getDZero()) * cos(generatorTrackParameter->getPhi());
            //cout << "center of circle: " << xm << " " << ym << endl;
            tempx1 = xm + sqrt(R * R - (valuesY.at(steps) - ym) * (valuesY.at(steps) - ym));
            tempx2 = xm - sqrt(R * R - (valuesY.at(steps) - ym) * (valuesY.at(steps) - ym));

            if(tempx1 == tempx1 && tempx2 == tempx2) //if tempx1 and tempx2 != nan
            {
                double seed = steps * steps * steps / tpn * (double)track_type;
                randgaus = gaus(-1., 1., seed);
                randomSmearingTree->Fill();
                tempx1 = tempx1 + smearing * randgaus;
                randgaus = gaus(-1., 1., seed * seed);
                randomSmearingTree->Fill();
                tempx2 = tempx2 + smearing * randgaus;
                xvals.push_back(tempx1);
                xvals.push_back(tempx2);
            }

        }
    }


    return xvals;

}//vector<double> computeX()

vector<double> TrackGenerator::correctY(vector<double> valuesY, TrackParameterFull* generatorTrackParameter)//for curler only
{
    vector<double> xvals;
    vector<double> newyvals;

    //loop over hits

    unsigned int nYValues = valuesY.size();

    for(unsigned int steps = 0; steps < nYValues; ++ steps)
    {
        double tempx1, tempx2;
        double xm, ym;
        double R = 1. / generatorTrackParameter->getOmega();
        xm = (R - generatorTrackParameter->getDZero()) * sin(generatorTrackParameter->getPhi());
        ym = -(R - generatorTrackParameter->getDZero()) * cos(generatorTrackParameter->getPhi());
        tempx1 = xm + sqrt(R * R - (valuesY.at(steps) - ym) * (valuesY.at(steps) - ym));
        tempx2 = xm - sqrt(R * R - (valuesY.at(steps) - ym) * (valuesY.at(steps) - ym));

        if(tempx1 == tempx1 && tempx2 == tempx2) //if tempx1 and tempx2 != nan
        {
            xvals.push_back(tempx1);
            xvals.push_back(tempx2);
            newyvals.push_back(valuesY.at(steps));
            newyvals.push_back(valuesY.at(steps));
        }

    }


    return newyvals;

}

vector<double> TrackGenerator::computeY()
{
    vector<double> yvals;

    for(unsigned int steps = 0; steps < tpn; ++steps)
    {
        double y;

        if(track_type == 2 || track_type == 0 || track_type == 1)
        {
            if(padplaneY.first < 0.)
            {
                y = ((-1.) * padsizey * ((double)steps + 1.) + padsizey / 2.);
                yvals.push_back(y);
            }
            if(padplaneY.second > 0.)
            {
                y = (padsizey * ((double)steps + 1.) - padsizey / 2.);
                yvals.push_back(y);
            }
        }
        else
        {
            if(padplaneY.first < 0.)
            {
                y = ((-1.) * padsizey * ((double)steps + 1.) + padsizey / 2.);
            }
            else
            {
                y = (padsizey * ((double)steps + 1.) - padsizey / 2.);
            }
            yvals.push_back(y);
        }

    }

    return yvals;

}//vector<double> computeY()


vector<double> TrackGenerator::computeZ(vector<double> valuesX, vector<double> valuesY, TrackParameterFull* generatorTrackParameter)
{

    /*
      Attention!!!!
      Ambiguity in z0:
      For curler there might be several possible z0s, for each turn one because there is a pca in each turn.
    */

    vector<double> zvals;
    pair<double, double> refPos;


    refPos.first = -generatorTrackParameter->getDZero() * sin(generatorTrackParameter->getPhi());
    refPos.second = generatorTrackParameter->getDZero() * cos(generatorTrackParameter->getPhi());


    for(unsigned int steps = 0; steps < valuesX.size(); ++steps)
    {

        double z;
        double s;
        double phi = 0.;
        if(track_type == 0)
        {

            s = sqrt((valuesX.at(steps) - refPos.first) * (valuesX.at(steps) - refPos.first) +
                     (valuesY.at(steps) - refPos.second) * (valuesY.at(steps) - refPos.second));

            if(refPos.second < valuesY.at(steps))
            {
                s = s * (-1.);
            }

            z = generatorTrackParameter->getTanLambda() * s + generatorTrackParameter->getZZero();

            //apply smearing
            double seed = steps * steps * 10000 / tpn / (double)track_type / (double)track_type;
            randgaus = gaus(-1., 1., seed);
            randomSmearingTree->Fill();
            z = z + smearing * randgaus;
        }
        if(track_type == 1  || track_type == 2) //helix segment or curler
        {
            double r = 1. / generatorTrackParameter->getOmega();

            double xm, ym;
            xm = (r - generatorTrackParameter->getDZero()) * sin(generatorTrackParameter->getPhi());
            ym = -(r - generatorTrackParameter->getDZero()) * cos(generatorTrackParameter->getPhi());


            s = r * (
                    atan2(refPos.second - ym , refPos.first - xm)
                    -
                    atan2(valuesY.at(steps) - ym , valuesX.at(steps) - xm)
                );

            if(phi != phi)
            {
                cout << "valuesX.at(steps) " << valuesX.at(steps) << endl;
                cout << "valuesY.at(steps) " << valuesY.at(steps) << endl;
                cout << "d0 " << generatorTrackParameter->getDZero() << endl;
                cout << "phi0 " << generatorTrackParameter->getPhi() << endl;
                cout << "r " << r << endl;
                cout << "- 2*d0*sin(phi0) " << -generatorTrackParameter->getDZero()*sin(generatorTrackParameter->getPhi()) << endl;
                cout << "-(r+d0)*sin(phi0) " << -(r + generatorTrackParameter->getDZero())*sin(generatorTrackParameter->getPhi()) << endl;
                cout << "sum " << (valuesX.at(steps) - generatorTrackParameter->getDZero()*sin(generatorTrackParameter->getPhi()) - r * sin(generatorTrackParameter->getPhi())) << endl;
                cout << "-sum/r: " << -1. / r *(valuesX.at(steps) + generatorTrackParameter->getDZero()*sin(generatorTrackParameter->getPhi()) - r * sin(generatorTrackParameter->getPhi())) << endl;
                cout << "phi " << phi << endl;
                cout << "s " << s << endl;
            }

            z = generatorTrackParameter->getTanLambda() * s + generatorTrackParameter->getZZero();

            //apply smearing
            double seed = steps * steps * 10000 / tpn / (double)track_type / (double)track_type;
            randgaus = gaus(-1., 1., seed);
            randomSmearingTree->Fill();
            z = z + smearing * randgaus;
        }
        zvals.push_back(z);

        //cout<<" "<<valuesX.at(steps)<<" "<<valuesY.at(steps)<<" "<<zvals.at(steps)<<" "<<s<<" "<<phi<<endl;

    }

    return zvals;

}//vector<double> computeZ()


double TrackGenerator::uniform(double a, double b, double seed)
{
    srand48((long int)seed);
    double rand = a + (b - a) * drand48();

    return rand;
}

double TrackGenerator::gaus(double a, double b, double seed)
{
    double rand1 = uniform(0, 1, seed);
    double rand2 = uniform(0, 1, seed * seed + 384.32489 * sqrt(seed));

    double x = sqrt(-2.*log(rand1)) * cos(2 * M_PI * log(rand2));

    double z = x;

    return z;
}
