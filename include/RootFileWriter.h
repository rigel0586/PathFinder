#ifndef ROOTFILEWRITER_H
#define ROOTFILEWRITER_H

#include "TrackFinderTrack.h"
#include <map>
#include <iostream>

//Root
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>


namespace pathfinder
{
class RootFileWriter
{

    public:
        ///constructor
        RootFileWriter();
        ///destructor
        ~RootFileWriter()
        {
            if(RadiusTree != 0)
            {
                //std::cout<<"Delete RadiusTree "<<RadiusTree<<std::endl;
                //RadiusTree->Print();
                //RadiusTree->Delete("all");
            }
            /*
            if(randD0 !=0)delete randD0;
            if(randPhi !=0)delete randPhi;
            if(randOmega !=0)delete randOmega;
            if(randTanL !=0)delete randTanL;
            if(randZ0 !=0)delete randZ0;
            if(simD0 !=0)delete simD0;
            if(simPhi !=0)delete simPhi;
            if(simOmega !=0)delete simOmega;
            if(simTanL !=0)delete simTanL;
            if(simZ0 !=0)delete simZ0;
            */
            if(HoughTree != 0)
            {
                //std::cout<<"Delete HoughTree "<<HoughTree<<std::endl;
                //HoughTree->Show(10);
                //HoughTree->Print();
                //HoughTree->Delete("all");
            }
        };

        /**
           Writes Hough space to root tree. For straight lines only (xy and sz). It needs the Hough space as a map and the file name to write it to.
         */
        bool writeRootFile(std::map<int, unsigned int>*, std::string filename);

        /**
           Writes Hough space to root tree. For circles only. It needs the Hough space for the circle center, the Hough space for the radius and a file name.
         */
        bool writeRootFile(std::map<int, unsigned int>*, std::map<int, unsigned int>*, std::string filename);

        /**
           \todo Function is not implemented. Is it needed at all?
         */
        bool writeRootFile(std::vector<TrackParameterFull*>, std::string filename);

        /**
           \todo What's the point of this function? Is it needed? Instead of a map a vector of vectors is used for the Hough space.
         */
        bool writeRootFile(std::vector<std::vector<unsigned int>* >, std::string filename);

    private:

        /**
           Function creating branches in root trees. For the HoughTree it creates thetabin, dzerobin, omegabin, nentries, for the RadiusTree it creates radiusbin, nradius.
           \todo For the Hough space a branch for Omega is created, but this is not used anymore because the search for circles is split into circle center and radius. So I guess this is not needed anymore?
         */
        void setTreeBranches();

        /**
           Fills Hough space for straight lines to root tree.
         */
        void fillRootTree(std::map<int, unsigned int>*);

        /**
           Fills Hough spaces for circles to root tree.
         */
        void fillRootTree(std::map<int, unsigned int>*, std::map<int, unsigned int>*);

        /**
           \todo Not implemented. Is it needed at all?
         */
        void fillRootTree(std::vector<TrackFinderTrack*>);

        /**
           \todo Is this function needed?
         */
        void fillRootTree(std::vector<std::vector<unsigned int>* >);

        /**
           \todo Not implemented. What was this function supposed to do anyway?
         */
        void fillRootHistos(std::vector<TrackFinderTrack*>);

        /**
           Converter needed to convert the keys of the Hough maps to theta bin and d0 bin.
         */
        std::pair<int, int> IntToBinConverter2D(int);
        //  void fillRootHisto(double, TH1*);

        //root tree to save hough map
        TTree *HoughTree;///<Root tree for Hough space (straight lines and center of circle)
        TTree *RadiusTree;///<Root tree for radius
        //  TTree *TrackParameter;

        //histograms for track parameter
        /*
        TH1* randD0;
        TH1* randPhi;
        TH1* randOmega;
        TH1* randTanL;
        TH1* randZ0;
        TH1* simD0;
        TH1* simPhi;
        TH1* simOmega;
        TH1* simTanL;
        TH1* simZ0;
        */

        double theta;///<\todo not used. Why?
        double dzero;///<\todo not used. Why?
        double omega;///<\todo not used. Why?
        int binindex;///<Bin index, key of Hough spaces
        int bintheta;///<Bin number in theta direction
        int bindzero;///<Bin number in d0 direction
        int binomega;///<Bin number in omega direction \todo Is this really used?
        int binradius;///<Bin number in radius direction
        int nentries;///<Number of entries per bin for 2D Hough spaces (straight line, center of circle)
        int nradius;///<Number of entries per bin for 1D Hough spaces (radius)


};//class RootFileWriter
}
#endif //ROOTFILEWRITER_H
