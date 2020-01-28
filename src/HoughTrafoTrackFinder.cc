#include "HoughTrafoTrackFinder.h"
#include "HoughMap2Dint.h"
#include "HoughMap2DintIntersectionMethod.h"
#include "newHoughMap3Dint.h"
#include "newHoughMap3DintVertex.h"
#include "HoughMap2DCircleint.h"
#include "HoughMaximum2D.h"
#include "HoughMaximum3D.h"
#include "candidateHitCombination.h"
#include "XYLinearFit.h"
#include "XYCircularFit.h"
#include "SZFit.h"
#include "ThetaToPhiConverter.h"
#include "DistanceHitTrackCalculator.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;
using namespace pathfinder;

HoughTrafoTrackFinder::HoughTrafoTrackFinder()
    : XYHoughMap(NULL), SZHoughMap(NULL),
      XYFitter(NULL), SZFitter(NULL), XYHoughMaximum(NULL), SZHoughMaximum(NULL),
      XYTrackParameter(NULL), fittedXYTrackParameter(NULL), SZTrackParameter(NULL), fittedSZTrackParameter(NULL), finalTrackParameter(NULL)
{
}



bool HoughTrafoTrackFinder::find()
{
    // guard against empty hit collections
    if(allHits.size() == 0)
        return false;
    /*
      1.   check number of hits
      2.   do xy plane projection
      3.   check number of hits
      4.   calculate arclength s
      5.   do sz plane projection
      6.   check number of hits
      7.   prepare output
      7.1. write hits found on track after sz plane search to finalHitsOnTrack
      7.2. write TrackParameter for xy plane and sz plane to finalTrackParameter
      8. cleaning up everything after each iteration
    */


    //1.
    while(allHits_copy.size() >= finderParameter.getMinimumHitNumber())
    {
        //check if all x, all y or all z are inf or nan, if so break
        bool x_nan = true;
        bool y_nan = true;
        bool z_nan = true;
        for(unsigned int i = 0; i < allHits_copy.size(); i++)
        {
            if(allHits_copy[i].getX() == numeric_limits<double>::infinity() ||
                    allHits_copy[i].getX() == -numeric_limits<double>::infinity() ||
                    allHits_copy[i].getX() != allHits_copy[i].getX())
            {
                cout << "x1 " << allHits_copy[i].getX() << endl;
                //nan of inf
            }
            else
            {
                //          cout<<"x2 "<<allHits_copy[i].getX()<<endl;
                x_nan = false;
            }
            if(allHits_copy[i].getY() == numeric_limits<double>::infinity() ||
                    allHits_copy[i].getY() == -numeric_limits<double>::infinity() ||
                    allHits_copy[i].getY() != allHits_copy[i].getY())
            {
                cout << "y1 " << allHits_copy[i].getY() << endl;
                //nan of inf
            }
            else
            {
                // cout<<"y2 "<<allHits_copy[i].getY()<<endl;
                y_nan = false;
            }
            if(allHits_copy[i].getZ() == numeric_limits<double>::infinity() ||
                    allHits_copy[i].getZ() == -numeric_limits<double>::infinity() ||
                    allHits_copy[i].getZ() != allHits_copy[i].getZ())
            {
                cout << "z1 " << allHits_copy[i].getZ() << endl;
                //nan or inf
            }
            else
            {
                //cout<<"z2 "<<allHits_copy[i].getZ()<<endl;
                z_nan = false;
            }
        }
        if(x_nan || y_nan || z_nan)
        {
            if(x_nan)cout << "all x are inf or nan: break!" << endl;
            if(y_nan)cout << "all y are inf or nan: break!" << endl;
            if(z_nan)cout << "all z are inf or nan: break!" << endl;
            break;
        }

        //1.
        /*
        //TODO: What is this doing here? Will not be executed because here
        //allHits_copy.size() >= finderParameter.getMinimumHitNumber()
        if(allHits_copy.size() < finderParameter.getMinimumHitNumber())
        {
        //in this case all hits are not on track
        finalHitsNotOnTrack.clear();
        finalHitsNotOnTrack = allHits_copy;
        cout<<"No track found: Not enough Hits to create a track."<<endl;
        return false;
        }
        */

        //2.
        xyTrack = _doXYPlaneProjection(allHits_copy, finderParameter);

        if(xyTrack.first == 0 && xyTrack.second == 0)
        {
            //cout<<"all hits are noise hits"<<endl;

            noiseHits.insert(noiseHits.end(),
                             allHits_copy.begin(),
                             allHits_copy.end()
                            );
            allHits_copy.clear();
            //only for now XYHoughMap->clear();

            break;
        }

        //cout<<"Number of hits on track after xy search: "<<(xyTrack.first)->size()<<endl;

        //3.
        if((xyTrack.first)->size() < finderParameter.getMinimumHitNumber())
        {



            allHits_copy.clear();
            allHits_copy = finalHitsNotOnTrack;

            xyHitsAndS.clear();
            finalHitsOnTrack.clear();
            finalHitsNotOnTrack.clear();

            //only for now XYHoughMap->clear();
            //SZHoughMap->clear();//Why does this cause seg fault??

            noiseHits.insert(noiseHits.end(),
                             (xyTrack.first)->begin(),
                             (xyTrack.first)->end()
                            );

            // cout << "No track found: Not enough Hits associated to track in xy plane." << endl;
            //cout<<"Added "<<(xyTrack.first)->size()<<" hits to noise hit vector."<<endl;

            if((xyTrack.first)->size() > 0)
            {
                //TODO: Which version is the correct one now??? Well, continue seems to do the right thing...
                continue;//else the whole search is stoppt although there are many remaining hits.
                //break;  //else endless loop if no hits were found in xy. Then search is done for the same set of its again and again
            }
            else
            {
                //  cout<<"No hits were found in xy. Break."<<endl;
                break;
            }
        }

        //cout << "******************" << endl;


        //4.
        candidateHitCombination candidateHitCombination(*xyTrack.first,
                                                        *xyTrack.second, finderParameter);

        xyHitsAndS = candidateHitCombination.getCombination(*xyTrack.second);

        //cout << "******************" << endl;


        //5.
        szTrack = _doSZPlaneProjection(xyHitsAndS, finderParameter, *xyTrack.second);

        if(szTrack.first == 0 && szTrack.second == 0)
        {
            //cout<<"all hits are noise hits"<<endl;

            noiseHits.insert(noiseHits.end(),
                             allHits_copy.begin(),
                             allHits_copy.end()
                            );
            allHits_copy.clear();
            //only for now XYHoughMap->clear();

            break;
        }


        //cout<<"Number of hits on track after sz search: "<<(szTrack.first)->size()<<endl;
        //6.
        if((szTrack.first)->size() < finderParameter.getMinimumHitNumber())
        {

            allHits_copy.clear();
            allHits_copy = finalHitsNotOnTrack;

            xyHitsAndS.clear();
            finalHitsOnTrack.clear();
            finalHitsNotOnTrack.clear();

            //only for now XYHoughMap->clear();
            //only for now SZHoughMap->clear();

            noiseHits.insert(noiseHits.end(),
                             (szTrack.first)->begin(),
                             (szTrack.first)->end()
                            );
            //cout << "No track found: Not enough Hits associated to track in sz plane." << endl;
            //cout<<"Added "<<(szTrack.first)->size()<<" hits to noise hit vector."<<endl;

            if((szTrack.first)->size() > 0)
            {
                //TODO: Which version is the correct one now??? Well, continue seems to do the right thing...
                continue;//else the whole search is stoppt although there are many remaining hits.
                //break;  //else endless loop if no hits were found in xy. Then search is done for the same set of its again and again
            }
            else
            {
                //cout<<"No hits were found in sz. Break."<<endl;
                break;
            }


        }

        //7.
        //7.1.
        for(unsigned int i = 0; i < (szTrack.first)->size(); i++)
        {
            finalHitsOnTrack.push_back((szTrack.first)->at(i));
        }

        std::vector<basicHit> finalHitsNotOnTrackAndNoise = finalHitsNotOnTrack;
        finalHitsNotOnTrackAndNoise.insert(finalHitsNotOnTrackAndNoise.end(),
                                           noiseHits.begin(),
                                           noiseHits.end()
                                          );

        //7.2.
        finalTrackParameter = new TrackParameterFull(*xyTrack.second, *szTrack.second);


        TrackFinderTrack tempFinalTrack(*finalTrackParameter, finalHitsOnTrack, finalHitsNotOnTrackAndNoise);
        finalTracks.push_back(tempFinalTrack);


        //8.
        allHits_copy.clear();
        allHits_copy = finalHitsNotOnTrack;


        xyHitsAndS.clear();
        finalHitsOnTrack.clear();
        finalHitsNotOnTrack.clear();

        hitsOnFittedTrackXY.clear();
        hitsOnFittedTrackSZ.clear();


    }//while


    if(finalTracks.size() != 0)
    {
        TrackFinderTrack lastTrack = finalTracks.back();

        std::vector<basicHit> hitsNotOnLastTrack = lastTrack.getRejectedHits();

        TrackFinderTrack lastTrack2(lastTrack.getTrackParameter(), lastTrack.getHitsOnTrack(), hitsNotOnLastTrack);
        finalTracks.pop_back();
        finalTracks.push_back(lastTrack2);


    }

    return (finalTracks.size() > 0);
}


pair<vector<basicHit>*, TrackParameterXY*> HoughTrafoTrackFinder::_doXYPlaneProjection(vector<basicHit> initialHits,
        FinderParameter XYFinderParameter)
{
    //std::cout<<"Do xy plane projection: test 1"<<std::endl;

    /*
      0. choose 2D Hough Map or 3D Hough Map
      1. fill HoughMap
      2. find Maximum in HoughMap
      3. find closest hits
      4. do simple fit
      5. find closest hits
      6. find hits not on track
      7. return vector<basiHit> and Trackparameters
     */

    // XYFinderParameter.print();

    //0. & 1. (filling of Hough Map is done in constructor)
    if(XYFinderParameter.getIsStraightLine() == true)
    {
        //std::cout<<"straight line "<<std::endl;
      if(XYFinderParameter.getUseIntersections() == false)
	{
	  XYHoughMap = new HoughMap2Dint(initialHits, XYFinderParameter);
	}
      else
	{
	  XYHoughMap = new HoughMap2DintIntersectionMethod(initialHits, XYFinderParameter);
	}
    }


    if(XYFinderParameter.getIsHelix() == true)
    {
        //std::cout<<"helix "<<std::endl;
        if(XYFinderParameter.getUseVertex() == false && XYFinderParameter.getUseConformalMapping() == false)
        {
            //                    std::cout<<"helix no vertex "<<std::endl;
            XYHoughMap = new newHoughMap3Dint(initialHits, XYFinderParameter);
        }
        if(XYFinderParameter.getUseVertex() == true && XYFinderParameter.getUseConformalMapping() == false)
        {
            //std::cout<<"helix vertex"<<std::endl;
            XYHoughMap = new newHoughMap3DintVertex(initialHits, XYFinderParameter);
            //XYHoughMap = new HoughMap2DCircleint(initialHits, XYFinderParameter);
        }
        if(XYFinderParameter.getUseVertex() == false && XYFinderParameter.getUseConformalMapping() == true)
        {
            //std::cout<<"no vertex, conformal mapping"<<std::endl;
            XYHoughMap = new HoughMap2DCircleint(initialHits, XYFinderParameter);
        }
        if(XYFinderParameter.getUseVertex() == true && XYFinderParameter.getUseConformalMapping() == true)
        {
            //std::cout<<"vertex, conformal mapping: No valid option!"<<std::endl;
        }

    }

    // std::cout<<"Do xy plane projection: test 2"<<std::endl;


    //XYHoughMap->print();


    //2.
    if(XYHoughMap->getTrackFound())
    {
        //cout<<"Found Track is true"<<endl;
        XYHoughMaximum = XYHoughMap->findMaximum();
    }
    else//all hits in initial hit vector were noise hits
    {
        //cout<<"Found Track is false"<<endl;
        pair<vector<basicHit>*, TrackParameterXY*> nullpair;
        nullpair.first = 0;
        nullpair.second = 0;
        return nullpair;
    }

    ThetaToPhiConverter* angleConverter = new ThetaToPhiConverter(XYHoughMaximum);
    double trackPhi = angleConverter->getPhi();
    delete angleConverter;
    XYTrackParameter = new TrackParameterXY(trackPhi, XYHoughMaximum->getSecond(), XYHoughMaximum->getThird());

    //3. && 4.
    if(XYFinderParameter.getIsStraightLine() == true)
    {
        XYFitter = new XYLinearFit();
    }
    if(XYFinderParameter.getIsHelix() == true)
    {
        XYFitter = new XYCircularFit();
    }

    unsigned int closeXYHits = findCloseXYHits(XYHoughMaximum, XYFinderParameter, initialHits, false).size();
    //cout << "Test: number of hits in xy before fit: " << closeXYHits << endl;

    bool fitSuccessful = false;
    if((XYFinderParameter.getIsStraightLine() == true && closeXYHits >= 2)
            ||
            (XYFinderParameter.getIsHelix() == true && closeXYHits >= 3))
    {
        fitSuccessful = XYFitter->fit(findCloseXYHits(XYHoughMaximum, XYFinderParameter, initialHits, false),
                                      XYHoughMaximum);
    }
    else
    {
        fitSuccessful = false;
    }

    if(fitSuccessful)
    {
        fittedXYTrackParameter = dynamic_cast<TrackParameterXY*>(XYFitter->getResult());
    }
    else
    {
        //cout << "xy Fit Failed!" << endl;
        fittedXYTrackParameter = new TrackParameterXY(*XYTrackParameter);
    }

    //cout << "find close xy hits: " << endl;
    //5.
    hitsOnFittedTrackXY = findCloseXYHits(*fittedXYTrackParameter, XYFinderParameter, initialHits, true);

    //cout << "find xy hits: not on track " << (findHitsNotOnTrack(initialHits, hitsOnFittedTrackXY)).size() << endl;

    //6.
    vector<basicHit> tempHitsNotOnTrack = findHitsNotOnTrack(initialHits, hitsOnFittedTrackXY);
    finalHitsNotOnTrack.insert(finalHitsNotOnTrack.end(),
                               tempHitsNotOnTrack.begin(),
                               tempHitsNotOnTrack.end()
                              );

    //cout << "done" << endl;

    //7.
    pair<vector<basicHit>*, TrackParameterXY*> tempPair;
    tempPair.first = &hitsOnFittedTrackXY;
    tempPair.second = fittedXYTrackParameter;

    delete XYHoughMap;

    delete XYFitter;

    /*
    for(unsigned int i = 0; i<hitsOnFittedTrackXY.size(); i++)
      {
    hitsOnFittedTrackXY[i].print();
      }
    */
    return tempPair;

}//pair<vector<basicHit>, TrackParameter*> HoughTrafoTrackFinder::_doXYPlaneProjection




pair<vector<candidateHit>*, TrackParameterSZ*> HoughTrafoTrackFinder::_doSZPlaneProjection(vector<candidateHit> xyHits,
        FinderParameter SZFinderParameter,
        TrackParameterXY tpXY)
{
    /*
      1. fill 2D HoughMap
      2. find Maximum in HoughMap
      3. find closest hits
      4. do simple fit
      5. find closest hits
      6. find hits not on track
      7. return vector<candidateHit> and Trackparameters
    */

    //1. (filling of HoughMap is done in constructor)
    SZHoughMap = new HoughMap2Dint(xyHits, SZFinderParameter);
  //  SZHoughMap = new HoughMap2DintIntersectionMethod(xyHits, SZFinderParameter,100);
    //    HoughMap2DintIntersectionMethod* SZHoughMapTest = new HoughMap2DintIntersectionMethod(xyHits, SZFinderParameter);
    //SZHoughMap = new AdaptiveHoughMap2D(xyHits, SZFinderParameter);
    //SZHoughMap = new AdaptiveHoughMap2D_new(xyHits, SZFinderParameter);

    //2.
    if(SZHoughMap->getTrackFound())
    {
        //cout<<"Found Track is true"<<endl;
        SZHoughMaximum = SZHoughMap->findMaximum();
    }
    else//all hits in initial hit vector were noise hits
    {
        //cout<<"Found Track is false"<<endl;
        pair<vector<candidateHit>*, TrackParameterSZ*> nullpair;
        nullpair.first = 0;
        nullpair.second = 0;
        return nullpair;
    }

    // SZHoughMaximum->print();


    double Max1 = 0., Max2 = 0.;
    Max1 = SZHoughMaximum->getFirst();
    Max2 = SZHoughMaximum->getSecond();
    //cout << "HoughMap Maximum sz: " << Max1 << " " << Max2 << endl;


    //cout<<"Number of hits on fitted sz track (expected to be 0 at this point): "<<hitsOnFittedTrackSZ.size()<<endl;
    if(fabs(Max1) < 0.0000000001)
    {
        //TODO
        cout << "Warning! Theta in sz projection is 0. This is not allowed -> leads to a TanLambda = inf! Just return empty hit vector" << endl;
        pair<vector<candidateHit>*, TrackParameterSZ*> tempPair;
        tempPair.first = &hitsOnFittedTrackSZ;
        tempPair.second = fittedSZTrackParameter;

        return tempPair;
    }

    //HoughMap is using angle theta, not phi!
    //SZTrackParameter = new TrackParameterSZ(1./tan(Max1), (Max2 / sin(Max1)));
    //    SZTrackParameter = new TrackParameterSZ(1./tan(Max1), (Max2 / sin(Max1)));
    SZTrackParameter = new TrackParameterSZ(-1. / tan(Max1), (Max2 / sin(Max1)));
    //SZTrackParameter = new TrackParameterSZ(tan(Max1), (Max2 / cos(Max1)));


    // cout<<"print track parameter: "<<endl;
    //SZTrackParameter->print();
    //  SZTrackParameter.setOmega(0.);

    //3. && 4.
    SZFitter = new SZFit();

    vector<candidateHit> tempSZHit = findCloseSZHits(SZHoughMaximum, tpXY , SZFinderParameter, xyHits, false);

    //    cout << "test: number of hits in sz before fit: " << tempSZHit.size() << endl;

    //cout<<"hits close to track: "<<endl;

    bool fitSuccessful = false;
    if(tempSZHit.size() >= 2)
    {
        fitSuccessful = SZFitter->fit(tempSZHit,
                                      SZHoughMaximum);
    }
    else
    {
        fitSuccessful = false;
    }

    if(fitSuccessful)
    {
        fittedSZTrackParameter = dynamic_cast<TrackParameterSZ*>(SZFitter->getResult());
    }
    else
    {
        //  cout << "sz Fit Failed!" << endl;

        //      fittedSZTrackParameter = SZTrackParameter;
        fittedSZTrackParameter = new TrackParameterSZ(*SZTrackParameter);
    }

    //cout << "SZTrackParameter: " << endl;
    //SZTrackParameter->print();
    //cout << "FittedSZTrackParameter: " << endl;
    //fittedSZTrackParameter->print();

    //5.
    hitsOnFittedTrackSZ = findCloseSZHits(*fittedSZTrackParameter, tpXY , SZFinderParameter, xyHits, true);

    //cout << "test: number of hits in sz after fit: " << hitsOnFittedTrackSZ.size() << endl;


    //6.
    vector<basicHit> tempHitsNotOnTrack = findHitsNotOnTrack(xyHits, hitsOnFittedTrackSZ);
    finalHitsNotOnTrack.insert(finalHitsNotOnTrack.end(),
                               tempHitsNotOnTrack.begin(),
                               tempHitsNotOnTrack.end()
                              );

    //7.
    pair<vector<candidateHit>*, TrackParameterSZ*> tempPair;
    tempPair.first = &hitsOnFittedTrackSZ;
    tempPair.second = fittedSZTrackParameter;

    delete SZHoughMap;
    delete SZFitter;

    return tempPair;


}//HoughTrafoTrackFinder::_doSZProjection

vector<basicHit> HoughTrafoTrackFinder::findCloseXYHits(HoughMapMaximum* Maximum,
                                                        FinderParameter XYFinderParameter,
                                                        vector<basicHit> initialHits,
                                                        bool fitted)
{
    //cout<<"HoughTrafoTrackFinder::findCloseXYHits is here!"<<endl;
    //calculate correct phi angle
    ThetaToPhiConverter* angleConverter = new ThetaToPhiConverter(Maximum);
    double trackPhi = angleConverter->getPhi();
    delete angleConverter;
    TrackParameterXY temp_TrackParameter((trackPhi), Maximum->getSecond() , Maximum->getThird());

    return findCloseXYHits(temp_TrackParameter, XYFinderParameter, initialHits, fitted);
}//HoughTrafoTrackFinder::findCloseXYHits

vector<basicHit> HoughTrafoTrackFinder::findCloseXYHits(TrackParameterXY tpXY,
                                                        FinderParameter XYFinderParameter,
                                                        vector<basicHit> initialHits,
                                                        bool fitted)
{

    /*
      1. Loop over all Hits
      2. Calculate distance of Hit to Track
      3. Write Hits close to track to new vector of basicHits
      4. Return vector
     */

    vector<basicHit> hitsOnTrackXY;

    //1.
    for(unsigned int i = 0; i < initialHits.size(); i++)
    {
        double currentHitPositionX = initialHits[i].getX();
        double currentHitPositionY = initialHits[i].getY();

        double cmpos[2];
        double r2 = currentHitPositionX * currentHitPositionX + currentHitPositionY * currentHitPositionY;
        cmpos[0] = currentHitPositionX / r2;
        cmpos[1] = -1 * currentHitPositionY / r2;

        //cout<<cmpos[0]<<" "<<cmpos[1]<<endl;

        double trackPhi = tpXY.getPhi();
        double trackDZero = tpXY.getDZero();
        //            double trackOmega = tpXY.getOmega();

        //2.
        DistanceHitTrackCalculator* distanceCalculator = 0;
        double distance = 1000.;
        if(!(XYFinderParameter.getUseConformalMapping() == true && fitted == false))
        {
            distanceCalculator = new DistanceHitTrackCalculator(&initialHits.at(i), &tpXY);
            distance = distanceCalculator->getDistance();
        }
        else
        {
            //conformal mapping does not yet work properly...
            distance = fabs(
                           cmpos[0] * sin(trackPhi) -
                           cmpos[1] * cos(trackPhi) +
                           trackDZero);
        }


        //3.
        if(fitted == false)
        {
            //cout<<"xyProjection before : Hit is closer than "<<XYFinderParameter.getMaxXYDistance()<<"? "<<distance<<endl;
            if(distance < XYFinderParameter.getMaxXYDistance())
            {

                hitsOnTrackXY.push_back(initialHits[i]);
            }
        }
        else
        {
            //cout<<"xyProjection before : Hit is closer than "<<XYFinderParameter.getMaxXYDistanceFit()<<"? "<<distance<<endl;
            if(distance < XYFinderParameter.getMaxXYDistanceFit())
            {

                hitsOnTrackXY.push_back(initialHits[i]);
            }
        }
        delete distanceCalculator;
    }//for(unsigned int i =0; i<initialHit.size(); i++)


    //4.
    return hitsOnTrackXY;

}//vector<basicHit> findCloseXYHits()


vector<candidateHit> HoughTrafoTrackFinder::findCloseSZHits(HoughMapMaximum* Maximum, TrackParameterXY tpXY,
                                                            FinderParameter SZFinderParameter,
                                                            vector<candidateHit> initialHits,
                                                            bool fitted)
{


    //TrackParameterSZ temp_TrackParameter(( 1./tan(Maximum->getFirst()) ) , (Maximum->getSecond() / sin(Maximum->getFirst())));      //Abuse both values here : phi for d0 in sz!
    TrackParameterSZ temp_TrackParameter((-1. / tan(Maximum->getFirst())) , (Maximum->getSecond() / sin(Maximum->getFirst())));      //Abuse both values here : phi for d0 in sz!
    //    TrackParameterSZ temp_TrackParameter(( tan(Maximum->getFirst()) ) , (Maximum->getSecond() / cos(Maximum->getFirst())));      //Abuse both values here : phi for d0 in sz!
    return findCloseSZHits(temp_TrackParameter, tpXY , SZFinderParameter, initialHits, fitted);

}//HoughTrafoTrackFinder::findCloseXYHits


vector<candidateHit> HoughTrafoTrackFinder::findCloseSZHits(TrackParameterSZ tpSZ, TrackParameterXY tpXY,
                                                            FinderParameter SZFinderParameter,
                                                            vector<candidateHit> xyHits,
                                                            bool fitted)
{

    /*
      1. Loop over all Hits
      2. Calculate distance of Hit to Track
      3. Write Hits close to track to new vector of basicHits
      4. Return vector
    */

    //  vector<candidateHit> tempSortedCandidates = sortByZ(xyHits);

    vector<candidateHit> hitsOnTrackSZ;


    //1.
    for(unsigned int i = 0; i < xyHits.size(); i++)
    {

        //2.
        double distance = 1000.;
        DistanceHitTrackCalculator* distanceCalculator = new DistanceHitTrackCalculator(&xyHits.at(i), &tpSZ);
        distance = distanceCalculator->getDistance();
        delete distanceCalculator;

        //      cout<<xyHits[i].getX()<<" "<<xyHits[i].getY()<<" "<<currentHitPositionZ<<" s: "<<currentHitPositionS<<" distance: "<<distance<<endl;
        //3.
        if(!fitted)
        {
            if(distance < SZFinderParameter.getMaxSZDistance())
            {
                hitsOnTrackSZ.push_back(xyHits[i]);
            }
        }
        else
        {
            if(distance < SZFinderParameter.getMaxSZDistanceFit())
            {
                hitsOnTrackSZ.push_back(xyHits[i]);
            }
        }
    }//for (unsigned int i = 0; i < xyHits.size(); i++)


    if(hitsOnTrackSZ.size() == 0)
    {
        return hitsOnTrackSZ;
    }


    if(SZFinderParameter.getFindCurler())
    {
        //if search for curler is to be done...
        bool moreLoopsAvailable = true;
        int loopcount_p = 0;
        int loopcount_m = 0;
        unsigned int nHigherHits = 0;
        unsigned int nLowerHits = 0;
        while(moreLoopsAvailable)
        {
            loopcount_p++;
            loopcount_m--;
            //get hit with largest z in hitsOnTrackSZ
            //get hit with smallest z in hitsOnTrackSZ
            vector<candidateHit> sortedHitsOnTrackSZ = sortByZ(hitsOnTrackSZ);//BUG HERE: These hits are already found to be on the track!!!!!!

            candidateHit lowestZHit = sortedHitsOnTrackSZ.front();
            candidateHit highestZHit = sortedHitsOnTrackSZ.back();

            //write new vectors with hits larger and smaller than
            vector<candidateHit> higherZHits;
            vector<candidateHit> lowerZHits;
            for(vector<candidateHit>::const_iterator aHit = xyHits.begin();
                    aHit < xyHits.end(); ++aHit)
            {
                candidateHit tempCandidateHit(*aHit);
                double s = (*aHit).getS();
                if(sortZ(highestZHit, *aHit))
                {

                    //Note: Which slope the curve has in zs plane obviously depends on the sign of omega!!! Or maybe not? additional checks needed...
                    if(tpSZ.getTanLambda() >= 0)//depending on slope in sz one has to add or subtract circumference
                    {
                        tempCandidateHit.setS(s + 2 * M_PI * (double)loopcount_p / abs(tpXY.getOmega()));
                    }
                    else
                    {
                        tempCandidateHit.setS(s - 2 * M_PI * (double)loopcount_p / abs(tpXY.getOmega()));
                    }
                    higherZHits.push_back(tempCandidateHit);

                }

                if(sortZ(*aHit, lowestZHit))
                {
                    if(tpSZ.getTanLambda() >= 0)
                    {
                        tempCandidateHit.setS(s - 2 * M_PI * (double)loopcount_p / abs(tpXY.getOmega()));
                    }
                    else
                    {
                        tempCandidateHit.setS(s + 2 * M_PI * (double)loopcount_p / abs(tpXY.getOmega()));
                    }
                    lowerZHits.push_back(tempCandidateHit);
                }


            }//for (vector<candidateHit>::const_iterator aHit = xyHits.begin();

            //if either no hits are left which have higher z than the highest found one
            //or                         which have lower z than the lowest found one
            //or the number of hits left with higher z than the highest found one
            //or                         with lower z than the lowest found one does not change anymore (this means only noise hits are left)
            //break!
            if((lowerZHits.size() == 0 && higherZHits.size() == 0) ||
                    (nHigherHits == higherZHits.size() && nLowerHits == lowerZHits.size()))
            {
                //      cout<<"no more loops, break here"<<endl;
                moreLoopsAvailable = false;
                break;
            }
            else
            {
                //  cout<<"test 1"<<endl;
                nHigherHits = higherZHits.size();
                nLowerHits = lowerZHits.size();
            }

            // cout<<"number of hits with lower z (2): "<<lowerZHits.size()<<endl;
            for(unsigned int i = 0; i < lowerZHits.size(); i++)
            {
                //cout<<"lower hit "<<i<<endl;
                double currentHitPositionS = lowerZHits[i].getS();
                double currentHitPositionZ = lowerZHits[i].getZ();

                double trackTanLambda = tpSZ.getTanLambda();
                double trackZZero = tpSZ.getZZero();

                //2.
                double distance = 1000.;

                distance = fabs(
                               currentHitPositionZ * cos(atan2(trackTanLambda, 1)) -
                               currentHitPositionS * sin(atan2(trackTanLambda, 1)) -
                               trackZZero * cos(atan2(trackTanLambda, 1))
                           );

                //3.
                if(!fitted)
                {
                    if(distance < SZFinderParameter.getMaxSZDistance())
                    {
                        hitsOnTrackSZ.push_back(lowerZHits[i]);
                    }
                }
                else
                {
                    if(distance < SZFinderParameter.getMaxSZDistanceFit())
                    {
                        hitsOnTrackSZ.push_back(lowerZHits[i]);
                    }
                }
            }//for (unsigned int i = 0; i < lowerZHits.size(); i++)


            for(unsigned int i = 0; i < higherZHits.size(); i++)
            {

                double currentHitPositionS = higherZHits[i].getS();
                double currentHitPositionZ = higherZHits[i].getZ();

                double trackTanLambda = tpSZ.getTanLambda();
                double trackZZero = tpSZ.getZZero();

                //2.
                double distance = 1000.;

                distance = fabs(
                               currentHitPositionZ * cos(atan2(trackTanLambda, 1)) -
                               currentHitPositionS * sin(atan2(trackTanLambda, 1)) -
                               trackZZero * cos(atan2(trackTanLambda, 2))
                           );

                //cout<<"distance: "<<distance<<" minimal distance: "<<SZFinderParameter.getMaxSZDistance()<<endl;
                //3.
                if(!fitted)
                {
                    if(distance < SZFinderParameter.getMaxSZDistance())
                    {
                        //cout<<"additional hit found"<<endl;
                        hitsOnTrackSZ.push_back(higherZHits[i]);
                    }
                }
                else
                {
                    if(distance < SZFinderParameter.getMaxSZDistanceFit())
                    {
                        //cout<<"additional hit found"<<endl;
                        hitsOnTrackSZ.push_back(higherZHits[i]);
                    }
                }
            }//for (unsigned int i = 0; i < higherZHits.size(); i++)

            lowerZHits.clear();
            higherZHits.clear();
        }//while(moreLoopsAvailable)
        //end if curlers should be found
    }//if(findCurler)


    //4.
    return hitsOnTrackSZ;


}///vector<basicHit> findCloseSZHits()


vector<basicHit> HoughTrafoTrackFinder::findHitsNotOnTrack(vector<basicHit> allHits,
                                                           vector<basicHit> trackHits)
{
    /*
      1. loop over all hits
      2. find current hit in trackHits
      3. if current hit was not in trackHits, add it to HitsNotOnTrack
      4. return HitsNotOnTrack
    */

    vector<basicHit> HitsNotOnTrack;

    vector<basicHit>::iterator it;

    //1.
    for(it = allHits.begin(); it < allHits.end(); it++)
    {
        vector<basicHit>::iterator it2;

        //2.
        it2 = std::find(trackHits.begin(), trackHits.end(), *it);

        //3.
        if(it2 == trackHits.end())
        {
            HitsNotOnTrack.push_back(*it);
            //finalHitsNotOnTrack.push_back(*it);
        }
    }

    //4.
    return HitsNotOnTrack;

}//HoughTrafoTrackFinder::findHitsNotOnTrack


vector<basicHit> HoughTrafoTrackFinder::findHitsNotOnTrack(vector<candidateHit> allHits,
                                                           vector<candidateHit> trackHits)
{

    //1. loop over all hits
    //2. find current hit in trackHits
    //3. if current hit was not in track hits, add it to HitsNotOnTrack
    // 4. return HitsNotOnTrack


    vector<basicHit> HitsNotOnTrack;

    vector<candidateHit>::iterator it;

    //1.
    for(it = allHits.begin(); it < allHits.end(); it++)
    {
        vector<candidateHit>::iterator it2;

        //2.
        it2 = std::find(trackHits.begin(), trackHits.end(), *it);

        //3.
        if(it2 == trackHits.end())
        {
            HitsNotOnTrack.push_back(*it);
            //finalHitsNotOnTrack.push_back(*it);
        }
    }

    //4.
    return HitsNotOnTrack;

}//HoughTrafoTrackFinder::findHitsNotOnTrack


vector<candidateHit> HoughTrafoTrackFinder::sortByZ(vector<candidateHit> unsortedHits)
{
    vector<candidateHit> sortedHits = unsortedHits;

    sort(sortedHits.begin(), sortedHits.end(), sortZ);

    return sortedHits;
}//vector<candidateHit> HoughTrafoTrackFinder::sortByZ(vector<candidateHit> unsortedHits)
