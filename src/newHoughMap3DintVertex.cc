#include "newHoughMap3DintVertex.h"
#include "RootFileWriter.h"
#include "ThetaToPhiConverter.h"
#include "DistanceHitTrackCalculator.h"
#include "HoughMapMaximumCandidateFinder.h"
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;
using namespace pathfinder;

newHoughMap3DintVertex::newHoughMap3DintVertex(vector<basicHit> initialHits, FinderParameter FinderParameter)
{
    Map_Maximum3D = 0;
    Map_Maximum3D1 = 0;
    Map_Maximum3D2 = 0;
    Map_Maximum3D2 = 0;
    Map_Maximum3D3 = 0;
    Map_Maximum3D4 = 0;

    Parameter = FinderParameter;
    initialBasicHits = initialHits;

    trangexy = new HoughSpaceBinning(FinderParameter.getNumberXYThetaBins(), -M_PI, 0.);
    newHoughMap3DintVertex::calculateDRangeXY();

    trackfound = newHoughMap3DintVertex::fill();
}

bool newHoughMap3DintVertex::fill()
{
    //if xy projection
    /*
      1. calculate bins for theta
      2. fill HoughMap for all Hits
      3. rounding of the calculated d0 to create a binning in this direction
    */

    //1.
    vector<double> a1Vec;
    for(float a1 = trangexy->getLow(); a1 <= trangexy->getHigh(); a1 += trangexy->getBinWidth())
    {
        a1Vec.push_back(a1);
    }

    //code with vertex constraint
    for(unsigned int iHit = 0; iHit < initialBasicHits.size() - 1; iHit++)
    {
        //hit position
        double pos1[2];
        pos1[0] = initialBasicHits[iHit].getX();
        pos1[1] = initialBasicHits[iHit].getY();

        //vertex position
        double pos2[2];
        pos2[0] = (Parameter.getVertex()).first;
        pos2[1] = (Parameter.getVertex()).second;

        for(vector<double>::iterator itera = a1Vec.begin(); itera < a1Vec.end(); itera++)
        {
            double tmpD = 0.5 * (pos1[1] * pos1[1] - pos2[1] * pos2[1] + pos1[0] * pos1[0] - pos2[0] * pos2[0]) /
                          ((pos1[1] - pos2[1]) * sin(*itera) + (pos1[0] - pos2[0]) * cos(*itera));
            tmpD = 1. / tmpD;
            HoughSpacePoint* tmpPoint = new HoughSpacePoint((*itera), tmpD, *trangexy, *drangexy);

            if(tmpD > drangexy->getLow() && tmpD < drangexy->getHigh())
            {
                ++HoughMapInt1[tmpPoint->getIndex()];
            }//if(tempPair.second < 2000. && tempPair.second > -2000.)
            delete tmpPoint;
        }//for(vector<double>::iterator itera = a1Vec.begin(); itera<a1Vec.end(); itera++)
    }//for(unsigned int iHit = 0; iHit< initialBasicHits.size(); iHit++)

    //if map has no entries, no track can be found
    if(HoughMapInt1.size() == 0)
    {
        return false;
    }

    findMaximum2D();

    //find most likely radius for circle
    double radius1 = findRadius(MapMaximumPair.first);
    double radius2 = findRadius(MapMaximumPair.second);


    if(((MapMaximumPair.first)->getSecond() < 0. && radius1 < 0.) || ((MapMaximumPair.first)->getSecond() > 0. && radius1 > 0.))
    {
        if(abs((MapMaximumPair.first)->getSecond()) > abs(radius1))
        {
            //cout<<"Theta: "<<(MapMaximumPair.first)->getFirst()<<" D: "<<(MapMaximumPair.first)->getSecond()<<" R: "<<radius1<<" d0: "<<(MapMaximumPair.first)->getSecond() - radius1<<endl;
            Map_Maximum3D1 = new HoughMaximum3D((MapMaximumPair.first)->getFirst(),
                                                (MapMaximumPair.first)->getSecond() - radius1,
                                                1. / radius1);
        }
        else
        {
            //cout<<"Theta: "<<(MapMaximumPair.first)->getFirst()<<" D: "<<(MapMaximumPair.first)->getSecond()<<" R: "<<radius1<<" d0: "<<-((MapMaximumPair.first)->getSecond() - radius1)<<endl;
            Map_Maximum3D1 = new HoughMaximum3D((MapMaximumPair.first)->getFirst(),
                                                -((MapMaximumPair.first)->getSecond() - radius1),
                                                1. / radius1);
        }
    }
    else
    {
        if(abs((MapMaximumPair.first)->getSecond()) > abs(radius1))
        {
            //cout<<"Theta: "<<(MapMaximumPair.first)->getFirst()<<" D: "<<(MapMaximumPair.first)->getSecond()<<" R: "<<radius1<<" d0: "<<(MapMaximumPair.first)->getSecond() + radius1<<endl;
            Map_Maximum3D1 = new HoughMaximum3D((MapMaximumPair.first)->getFirst(),
                                                (MapMaximumPair.first)->getSecond() + radius1,
                                                1. / radius1);
        }
        else
        {
            //cout<<"Theta: "<<(MapMaximumPair.first)->getFirst()<<" D: "<<(MapMaximumPair.first)->getSecond()<<" R: "<<radius1<<" d0: "<<-((MapMaximumPair.first)->getSecond() + radius1)<<endl;
            Map_Maximum3D1 = new HoughMaximum3D((MapMaximumPair.first)->getFirst(),
                                                -((MapMaximumPair.first)->getSecond() + radius1),
                                                1. / radius1);
        }
    }



    if(((MapMaximumPair.second)->getSecond() < 0. && radius2 < 0.) || ((MapMaximumPair.second)->getSecond() > 0. && radius2 > 0.))
    {
        if(abs((MapMaximumPair.second)->getSecond()) > abs(radius2))
        {
            //cout<<"Theta: "<<(MapMaximumPair.second)->getFirst()<<" D: "<<(MapMaximumPair.second)->getSecond()<<" R: "<<radius2<<" d0: "<<(MapMaximumPair.second)->getSecond() - radius2<<endl;
            Map_Maximum3D2 = new HoughMaximum3D((MapMaximumPair.second)->getFirst(),
                                                (MapMaximumPair.second)->getSecond() - radius2,
                                                1. / radius2);
        }
        else
        {
            //cout<<"Theta: "<<(MapMaximumPair.second)->getFirst()<<" D: "<<(MapMaximumPair.second)->getSecond()<<" R: "<<radius2<<" d0: "<<-((MapMaximumPair.second)->getSecond() - radius2)<<endl;
            Map_Maximum3D2 = new HoughMaximum3D((MapMaximumPair.second)->getFirst(),
                                                -((MapMaximumPair.second)->getSecond() - radius2),
                                                1. / radius2);
        }
    }
    else
    {
        if(abs((MapMaximumPair.second)->getSecond()) > abs(radius2))
        {
            //cout<<"Theta: "<<(MapMaximumPair.second)->getFirst()<<" D: "<<(MapMaximumPair.second)->getSecond()<<" R: "<<radius2<<" d0: "<<(MapMaximumPair.second)->getSecond() + radius2<<endl;
            Map_Maximum3D2 = new HoughMaximum3D((MapMaximumPair.second)->getFirst(),
                                                (MapMaximumPair.second)->getSecond() + radius2,
                                                1. / radius2);
        }
        else
        {
            //cout<<"Theta: "<<(MapMaximumPair.second)->getFirst()<<" D: "<<(MapMaximumPair.second)->getSecond()<<" R: "<<radius2<<" d0: "<<-((MapMaximumPair.second)->getSecond() + radius2)<<endl;
            Map_Maximum3D2 = new HoughMaximum3D((MapMaximumPair.second)->getFirst(),
                                                -((MapMaximumPair.second)->getSecond() + radius2),
                                                1. / radius2);
        }
    }


    radius1 = -radius1;
    radius2 = -radius2;


    if(((MapMaximumPair.first)->getSecond() < 0. && radius1 < 0.) || ((MapMaximumPair.first)->getSecond() > 0. && radius1 > 0.))
    {
        if(abs((MapMaximumPair.first)->getSecond()) > abs(radius1))
        {
            //cout<<"Theta: "<<(MapMaximumPair.first)->getFirst()<<"D: "<<(MapMaximumPair.first)->getSecond()<<" R: "<<radius1<<" d0: "<<(MapMaximumPair.first)->getSecond() - radius1<<endl;
            Map_Maximum3D3 = new HoughMaximum3D((MapMaximumPair.first)->getFirst(),
                                                (MapMaximumPair.first)->getSecond() - radius1,
                                                1. / radius1);
        }
        else
        {
            //cout<<"Theta: "<<(MapMaximumPair.first)->getFirst()<<"D: "<<(MapMaximumPair.first)->getSecond()<<" R: "<<radius1<<" d0: "<<-((MapMaximumPair.first)->getSecond() - radius1)<<endl;
            Map_Maximum3D3 = new HoughMaximum3D((MapMaximumPair.first)->getFirst(),
                                                -((MapMaximumPair.first)->getSecond() - radius1),
                                                1. / radius1);
        }
    }
    else
    {
        if(abs((MapMaximumPair.first)->getSecond()) > abs(radius1))
        {
            //cout<<"Theta: "<<(MapMaximumPair.first)->getFirst()<<"D: "<<(MapMaximumPair.first)->getSecond()<<" R: "<<radius1<<" d0: "<<(MapMaximumPair.first)->getSecond() + radius1<<endl;
            Map_Maximum3D3 = new HoughMaximum3D((MapMaximumPair.first)->getFirst(),
                                                (MapMaximumPair.first)->getSecond() + radius1,
                                                1. / radius1);
        }
        else
        {
            //cout<<"Theta: "<<(MapMaximumPair.first)->getFirst()<<"D: "<<(MapMaximumPair.first)->getSecond()<<" R: "<<radius1<<" d0: "<<-((MapMaximumPair.first)->getSecond() + radius1)<<endl;
            Map_Maximum3D3 = new HoughMaximum3D((MapMaximumPair.first)->getFirst(),
                                                -((MapMaximumPair.first)->getSecond() + radius1),
                                                1. / radius1);
        }
    }


    if(((MapMaximumPair.second)->getSecond() < 0. && radius2 < 0.) || ((MapMaximumPair.second)->getSecond() > 0. && radius2 > 0.))
    {
        if(abs((MapMaximumPair.second)->getSecond()) > abs(radius2))
        {
            //cout<<"Theta: "<<(MapMaximumPair.second)->getFirst()<<"D: "<<(MapMaximumPair.second)->getSecond()<<" R: "<<radius2<<" d0: "<<(MapMaximumPair.second)->getSecond() - radius2<<endl;
            Map_Maximum3D4 = new HoughMaximum3D((MapMaximumPair.second)->getFirst(),
                                                (MapMaximumPair.second)->getSecond() - radius2,
                                                1. / radius2);
        }
        else
        {
            //cout<<"Theta: "<<(MapMaximumPair.second)->getFirst()<<"D: "<<(MapMaximumPair.second)->getSecond()<<" R: "<<radius2<<" d0: "<<-((MapMaximumPair.second)->getSecond() - radius2)<<endl;
            Map_Maximum3D4 = new HoughMaximum3D((MapMaximumPair.second)->getFirst(),
                                                -((MapMaximumPair.second)->getSecond() - radius2),
                                                1. / radius2);
        }
    }
    else
    {
        if(abs((MapMaximumPair.second)->getSecond()) > abs(radius2))
        {
            //cout<<"Theta: "<<(MapMaximumPair.second)->getFirst()<<"D: "<<(MapMaximumPair.second)->getSecond()<<" R: "<<radius2<<" d0: "<<(MapMaximumPair.second)->getSecond() + radius2<<endl;
            Map_Maximum3D4 = new HoughMaximum3D((MapMaximumPair.second)->getFirst(),
                                                (MapMaximumPair.second)->getSecond() + radius2,
                                                1. / radius2);
        }
        else
        {
            //cout<<"Theta: "<<(MapMaximumPair.second)->getFirst()<<"D: "<<(MapMaximumPair.second)->getSecond()<<" R: "<<radius2<<" d0: "<<-((MapMaximumPair.second)->getSecond() + radius2)<<endl;
            Map_Maximum3D4 = new HoughMaximum3D((MapMaximumPair.second)->getFirst(),
                                                -((MapMaximumPair.second)->getSecond() + radius2),
                                                1. / radius2);
        }
    }


    //cout<<"calculating distance 1"<<endl;
    int distance1 = MeanDistanceCalculator(Map_Maximum3D1);
    //cout<<"calculating distance 2"<<endl;
    int distance2 = MeanDistanceCalculator(Map_Maximum3D2);
    //cout<<"calculating distance 3"<<endl;
    int distance3 = MeanDistanceCalculator(Map_Maximum3D3);
    //cout<<"calculating distance 4"<<endl;
    int distance4 = MeanDistanceCalculator(Map_Maximum3D4);

    //    cout<<"distance1: "<<distance1<<" distance2: "<<distance2<<" distance3: "<<distance3<<" distnance4: "<<distance4<<endl;

    int nHitsOnBestTrack = 0;

    if(distance1 >= distance2 && distance1 >= distance3 && distance1 >= distance4)
    {
        nHitsOnBestTrack = distance1;
        Map_Maximum3D = Map_Maximum3D1;
    }
    else if(distance2 >= distance1 && distance2 >= distance3 && distance2 >= distance4)
    {
        nHitsOnBestTrack = distance2;
        Map_Maximum3D = Map_Maximum3D2;
    }
    else if(distance3 >= distance1 && distance3 >= distance2 && distance3 >= distance4)
    {
        nHitsOnBestTrack = distance3;
        Map_Maximum3D = Map_Maximum3D3;
    }
    else if(distance4 >= distance1 && distance4 >= distance2 && distance4 >= distance3)
    {
        nHitsOnBestTrack = distance4;
        Map_Maximum3D = Map_Maximum3D4;
    }

    if(Parameter.getSaveRootFile() == true)
    {
        //      cout<<"RootFileWriter not implemented for this kind of Hough map"<<endl;
        RootFileWriter Writer1;
        bool FileDoesNotExists1;
        FileDoesNotExists1 = Writer1.writeRootFile(&HoughMapInt1,
                                                   &HoughMapRadius_copy, "XYCircularHoughMapVertex_test1.root");
        if(!FileDoesNotExists1)
        {
            Writer1.writeRootFile(&HoughMapInt1, &HoughMapRadius_copy, "XYCircularHoughMapVertex_test2.root");
        }
    }

    // cout<<"Number of hits on track: "<<nHitsOnBestTrack<<endl;

    if((unsigned int)nHitsOnBestTrack >= (unsigned int)Parameter.getMinimumHitNumber())
    {
        return true;
    }
    else
    {
        HoughMapInt1.clear();
        HoughMapRadius.clear();
    }


    //cout<<"No track found in xyProjection"<<endl;

    if(Map_Maximum3D1 != NULL)
        delete Map_Maximum3D1;
    if(Map_Maximum3D2 != NULL)
        delete Map_Maximum3D2;
    if(Map_Maximum3D3 != NULL)
        delete Map_Maximum3D3;
    if(Map_Maximum3D4 != NULL)
        delete Map_Maximum3D4;

    return false;

}//bool 2DHoughMap::fill


int newHoughMap3DintVertex::MeanDistanceCalculator(HoughMaximum3D* currentMapMax)
{
    double meandistance = 1000000000.;

    double trackDZero = currentMapMax->getSecond();
    ThetaToPhiConverter* angleConverter = new ThetaToPhiConverter(currentMapMax);
    double trackPhi = angleConverter->getPhi();
    delete angleConverter;
    double trackOmega = currentMapMax->getThird();
    double mean = 0.;
    int nhitsCloseToTrack = 0;

    for(unsigned int iHit = 0; iHit < initialBasicHits.size(); iHit++)
    {
        double distance = 0.;

        //double currentHitPositionX = (initialBasicHits.at(iHit)).getX();
        //double currentHitPositionY = (initialBasicHits.at(iHit)).getY();

        DistanceHitTrackCalculator* distanceCalculator = new DistanceHitTrackCalculator(&initialBasicHits.at(iHit), trackPhi, trackDZero, trackOmega);
        distance = distanceCalculator->getDistance();


        if(distance < Parameter.getMaxXYDistance())
        {
            nhitsCloseToTrack++;
        }

        mean += distance / initialBasicHits.size();

        delete distanceCalculator;

    }


    if(mean < meandistance)
    {
        meandistance = mean;
    }

    return  nhitsCloseToTrack;
}

double newHoughMap3DintVertex::findRadius(HoughMaximum2D* currentMapMax)
{
    //calculate center of circle
    double d = currentMapMax->getSecond();
    double theta = currentMapMax->getFirst();

    double xm = d * cos(theta);
    double ym = d * sin(theta);

    //cout<<"center of circle: "<<xm<<" "<<ym<<endl;

    vector<double> calculatedRadii;

    double minr = 0.;
    double maxr = 0.;
    double meanR = 0.;
    for(unsigned int iHit = 0; iHit < initialBasicHits.size(); iHit++)
    {

        double pos[2];
        pos[0] = initialBasicHits[iHit].getX();
        pos[1] = initialBasicHits[iHit].getY();
        double r = sqrt((pos[0] - xm) * (pos[0] - xm) + (pos[1] - ym) * (pos[1] - ym));
        meanR += r / initialBasicHits.size();
        if(iHit == 0)
        {
            minr = r;
            maxr = r;
        }
        else
        {
            if(minr > r)
            {
                minr = r;
            }
            if(maxr < r)
            {
                maxr = r;
            }
        }
        //cout<<"calculated R: "<<r<<endl;
        calculatedRadii.push_back(r);
    }


    //fill 1D Hough Map
    //cout<<"Number of calulated radii: "<<calculatedRadii.size()<<endl;
    for(unsigned int i = 0; i < calculatedRadii.size(); i++)
    {
        double currentR = calculatedRadii.at(i);
        int a = (int)floor(Parameter.getNumberXYOmegaBins() / (maxr - minr) * (currentR - minr));
        //cout<<"currentR: "<<currentR<<" map key: "<<a<<endl;
        HoughMapRadius[a]++;
    }

    //find maximum in 1D Hough Map
    pair<int , unsigned int> tempMax;
    tempMax.first = (*max_element(HoughMapRadius.begin(), HoughMapRadius.end(), map_compare1)).first;
    tempMax.second = (*max_element(HoughMapRadius.begin(), HoughMapRadius.end(), map_compare1)).second;

    //cout<<"most likely radius: "<<tempMax.first<<" "<<tempMax.second<<endl;

    double bestR = minr + (double)tempMax.first * (maxr - minr) / Parameter.getNumberXYOmegaBins();

    //cout<<"Best Radius: "<<bestR<<endl;

    if(HoughMapRadius_copy.empty())
    {
        HoughMapRadius_copy = HoughMapRadius;
    }

    HoughMapRadius.clear();
    return bestR;
}//double newHoughMap3DintVertex::findRadius()


HoughMaximum3D* newHoughMap3DintVertex::findMaximum()
{
    return Map_Maximum3D;
}//HoughMaximum3D* newHoughMap3DintVertex::findMaximum()

//pair<HoughMaximum2D*, HoughMaximum2D*>
void newHoughMap3DintVertex::findMaximum2D()
{
    //using new class HoughMapMaximumCandidateFinder to find maxima in Hough map
    HoughMapMaximumCandidateFinder* maxCandidateFinder = new HoughMapMaximumCandidateFinder(HoughMapInt1, trangexy, drangexy, true, Parameter.getSearchNeighborhood());
    vector<HoughMaximum2D> MapMaximumVec = maxCandidateFinder->getMaximumCandidates();
    delete maxCandidateFinder;

    MapMaximumPair.first = new HoughMaximum2D(MapMaximumVec.at(0));
    MapMaximumPair.second = new HoughMaximum2D(MapMaximumVec.at(1));

    //delete all other entries in vector
    if(MapMaximumVec.size() > 2)
    {
        MapMaximumVec.erase(MapMaximumVec.begin() + 2, MapMaximumVec.end());
    }

}//2DHoughMaximum 2DHoughMap::findMaximum

void newHoughMap3DintVertex::calculateDRangeXY()
{
    double maxD = Parameter.getMaxDxy() + Parameter.getMaxDxy() / 4.;
    double minD = (-1.) * Parameter.getMaxDxy() - Parameter.getMaxDxy() / 4.;

    std::pair<double, double> dzeroRange;
    dzeroRange.first = 100000000.;
    dzeroRange.second = -100000000.;

    vector<double> thetaVec;
    for(float t1 = trangexy->getLow(); t1 <= trangexy->getHigh(); t1 += trangexy->getBinWidth())
    {
        thetaVec.push_back(t1);
    }

    for(unsigned int iHit = 0; iHit < initialBasicHits.size() - 1; iHit++)
    {
        //      cout<<"loop 1 over hit "<<iHit<<endl;
        double pos1[2];
        pos1[0] = initialBasicHits[iHit].getX();
        pos1[1] = initialBasicHits[iHit].getY();

        double pos2[2];
        pos2[0] = (Parameter.getVertex()).first;
        pos2[1] = (Parameter.getVertex()).second;

        for(vector<double>::iterator itert = thetaVec.begin(); itert < thetaVec.end(); itert++)
        {
            pair<double, double> temppair;
            temppair.first = *itert;
            temppair.second = 0.5 * (pos1[1] * pos1[1] - pos2[1] * pos2[1] + pos1[0] * pos1[0] - pos2[0] * pos2[0]) /
                              ((pos1[1] - pos2[1]) * sin(*itert) + (pos1[0] - pos2[0]) * cos(*itert));
            temppair.second = 1. / temppair.second;

            if(temppair.second < maxD && temppair.second > minD)
            {
                if(temppair.second > dzeroRange.second /*&& temppair.second < dzeroRange.first*/)
                {
                    dzeroRange.second = temppair.second;
                }
                if(temppair.second < dzeroRange.first /*&& temppair.second > dzeroRange.first*/)
                {
                    dzeroRange.first = temppair.second;
                }
            }
        }//for(vector<double>::iterator itert = thetaVec.begin(); itert < thetaVec.end(); itert++)

    }//for(unsigned int iHit = 0; iHit < initialBasicHits.size() - 1; iHit++)

    drangexy = new HoughSpaceBinning(Parameter.getNumberXYDzeroBins(), dzeroRange);

}//void newHoughMap3DintVertex::calculateDRangeXY()

void newHoughMap3DintVertex::print() const
{
    map<int, unsigned int>::const_iterator mapIter;

    cout << "Circle Center:" << endl;
    cout << "Key:      Value:" << endl;
    for(mapIter = HoughMapInt1.begin(); mapIter != HoughMapInt1.end(); mapIter++)
    {
        cout << (*mapIter).first << " " << (*mapIter).second << endl;
    }

    cout << "Radius:" << endl;
    for(mapIter = HoughMapRadius.begin(); mapIter != HoughMapRadius.end(); mapIter++)
    {
        cout << (*mapIter).first << " " << (*mapIter).second << endl;
    }
}//void 2DHoughMap::print()
