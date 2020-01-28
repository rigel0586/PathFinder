#include "HoughMapMaximumCandidateFinder.h"
#include <algorithm>

using namespace std;
using namespace pathfinder;

HoughMapMaximumCandidateFinder::HoughMapMaximumCandidateFinder(std::map<int, unsigned int> InputHoughMap, HoughSpaceBinning* trange, HoughSpaceBinning* drange, bool iscircle, bool searchneighborhood)
    : HoughMap(InputHoughMap), tRange(trange), dRange(drange), isCircle(iscircle), neighborhoodSearch(searchneighborhood)
{
    findMaxima();
}

void HoughMapMaximumCandidateFinder::findMaxima()
{
    /*
              1. Look through map to find maximum entry
              2. Find first key with maximum entry
              3. get a vector with all the keys which belong to a maximum entry
              5. Take all found maxima and determine maximum number of neighbor entries
              6. Write all maxima into a vector which have max number of neighbor entries
              7. If there is only one bin with max entries of neighbors, return this one
              8. Somehow select the right maximum (number of hits close to track???)
              9. return maximum
    */

    //1.
    vector<pair<int, unsigned int > > tempMaxVec;
    pair<int , unsigned int> tempMax;
    tempMax.first = (*max_element(HoughMap.begin(), HoughMap.end(), map_compare1)).first;
    tempMax.second = (*max_element(HoughMap.begin(), HoughMap.end(), map_compare1)).second;
    tempMaxVec.push_back(tempMax);

    //2.
    map<int, unsigned int>::iterator firstMaxIter;
    firstMaxIter = find_first_of(HoughMap.begin(),
                                 HoughMap.end(),
                                 tempMaxVec.begin(),
                                 tempMaxVec.end(),
                                 map_compare2
                                );

    //3.
    vector< map<int, unsigned int>::iterator> maxIterVec;
    maxIterVec.push_back(firstMaxIter);

    do
    {
        map<int, unsigned int>::iterator tempIter = find_first_of(++firstMaxIter,
                                                                  HoughMap.end(),
                                                                  tempMaxVec.begin(),
                                                                  tempMaxVec.end(),
                                                                  map_compare2
                                                                 );

        if(tempIter != HoughMap.end())
        {

            maxIterVec.push_back(tempIter);
            firstMaxIter = tempIter;
        }
        else break;
    }
    while(true);

    if(neighborhoodSearch)
    {
        unsigned int nEntriesNeighborBins = 0;

        for(unsigned int i = 0; i < maxIterVec.size(); i++)
        {
            HoughSpacePoint currentBin((*maxIterVec[i]).first, *tRange, *dRange);
            unsigned int currentNEntriesNeighborBins = searchNeighborhood(currentBin);


            if(currentNEntriesNeighborBins > nEntriesNeighborBins)
            {
                nEntriesNeighborBins = currentNEntriesNeighborBins;
            }
        }//for(unsigned int i = 0; i<maxIterVec.size(); i++)


        //6.
        for(unsigned int i = 0; i < maxIterVec.size(); i++)
        {
            HoughSpacePoint currentBin((*maxIterVec[i]).first, *tRange, *dRange);

            unsigned int currentNEntriesNeighborBins = searchNeighborhood(currentBin);

            if(currentNEntriesNeighborBins == nEntriesNeighborBins)
            {
                if(!isCircle)
                {
                    HoughMaximum2D tempMapMaximum(currentBin.getTheta(), currentBin.getD());
                    MaximumCandidates.push_back(tempMapMaximum);
                }
                else
                {
                    HoughMaximum2D tempMapMaximum(currentBin.getTheta(), 1. / currentBin.getD());
                    MaximumCandidates.push_back(tempMapMaximum);
                }
                //take into account that only half the HoughSpace was calculate
                if(!isCircle)
                {
                    HoughMaximum2D tempMapMaximum2(currentBin.getTheta() + M_PI , -currentBin.getD());
                    MaximumCandidates.push_back(tempMapMaximum2);
                }
                else
                {
                    HoughMaximum2D tempMapMaximum2(currentBin.getTheta() + M_PI , -1. / currentBin.getD());
                    MaximumCandidates.push_back(tempMapMaximum2);
                }
            }
        }
    }//if(neighborhoodSearch)
    else
    {
        // cout<<"Neighborhood of Maximum is not searched!"<<endl;
        for(unsigned int i = 0; i < maxIterVec.size(); i++)
        {
            HoughSpacePoint currentBin((*maxIterVec[i]).first, *tRange, *dRange);

            if(!isCircle)
            {
                HoughMaximum2D tempMapMaximum(currentBin.getTheta(), currentBin.getD());
                MaximumCandidates.push_back(tempMapMaximum);
            }
            else
            {
                HoughMaximum2D tempMapMaximum(currentBin.getTheta(), 1. / currentBin.getD());
                MaximumCandidates.push_back(tempMapMaximum);
            }

            //take into account that only half the HoughSpace was calculate
            if(!isCircle)
            {
                HoughMaximum2D tempMapMaximum2(currentBin.getTheta() + M_PI , -currentBin.getD());
                MaximumCandidates.push_back(tempMapMaximum2);
            }
            else
            {
                HoughMaximum2D tempMapMaximum2(currentBin.getTheta() + M_PI , -1. / currentBin.getD());
                MaximumCandidates.push_back(tempMapMaximum2);
            }
        }

    }

}

unsigned int HoughMapMaximumCandidateFinder::searchNeighborhood(HoughSpacePoint currentBin)
{
    /*
        1. determine the neighboring bins of current bin
        2. get the iterators for neighbors
        3. get entries of these bins and sum them up
    */

    int currentBinA, currentBinB;
    currentBinB = currentBin.getDBin();
    currentBinA = currentBin.getThetaBin();

    unsigned int sumEntries = 0;

    vector<map<int, unsigned int>::iterator> neighborIterVec;

    const int xBin[3] = {currentBinA - 1,
                         currentBinA,
                         currentBinA + 1
                        };
    const int yBin[3] = {currentBinB - 1,
                         currentBinB,
                         currentBinB + 1
                        };


    //2.
    for(unsigned int i = 0; i < 3; i++)
    {
        for(unsigned int j = 0; j < 3 ; j++)
        {
            if(!((i == 1) && (j == 1)))
            {
                HoughSpacePoint tmpPoint(xBin[i], yBin[j], *tRange, *dRange);
                int bin_index = (xBin[i] << 20) | (yBin[j] << 10);
                neighborIterVec.push_back(HoughMap.find(bin_index));
            }
        }
    }

    //3.
    for(unsigned int i = 0; i < neighborIterVec.size(); i++)
    {
        if(neighborIterVec[i] != HoughMap.end())
        {
            sumEntries += (*neighborIterVec[i]).second;
        }
        else sumEntries += 0;
    }


    return sumEntries;
}//unsigned int HoughMapMaximumCandidateFinder::searchNeighborhood(HoughSpacePoint currentBin)


