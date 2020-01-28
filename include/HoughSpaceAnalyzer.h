#ifndef HOUGHSPACEANALYZER_H
#define HOUGHSPACEANALYZER_H

//pathfinder
#include "HoughSpaceBinning.h"
#include "HoughMaximum2D.h"

//C++
#include <map>
#include <list>

//root
#include "TH1I.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"

namespace pathfinder
{
/**
\todo Currently only used in HoughMap2DintIntersectionMethod. Add this to other Hough Maps as well?
*/
class HoughSpaceAnalyzer
{
    public:

        ///constructor
        HoughSpaceAnalyzer(std::map<int, unsigned int>, HoughSpaceBinning, HoughSpaceBinning);

        ///destructor
        ~HoughSpaceAnalyzer()
        {
            HoughSpace.clear();
            delete HoughSpaceHistogram;
            delete HoughSpaceXHistogram;
            delete HoughSpaceYHistogram;
            delete HoughSpaceKeyValueGraph;
            delete HoughSpaceValueHistogram;
            //delete HoughSpaceIntersectionGraph1;
            //delete HoughSpaceIntersectionGraph2;

            RootObjectList.clear();
        };

        /**
           function to analyze the Hough space
           it provides a loop over the Hough Map
           histograms keys of the map (bin indices)
           histograms values of the map (number of entries per bin
        */
        void Analyze();

        ///function to write root file
        void WriteRootFile(const char*);

        ///function to write pdf file
        void WritePdfFile(const char*);

    private:
        ///function which sets root style
        void SetRootStyle();

        ///function initializes root objects
        void InitializeRootObjects();

        ///function which finds maxima, calls FindMaxima1(), FindMaxima2(), ...
        void FindMaxima();

        ///function finding maxima with standard pathfinder method
        void FindMaxima1();

        ///function finding maxima with method coming with root, if that is possible for 2D histograms
        void FindMaxima2();

        ///create root object list
        void CreateRootObjectList();

        ///container holding the Hough space
        std::map<int, unsigned int> HoughSpace;

        ///Binning of Hough space in x (theta)
        HoughSpaceBinning xBinning;

        ///Binning of Hough space in y (d0)
        HoughSpaceBinning yBinning;

        ///Vector containing maximum candidates in current Hough space
        std::vector<HoughMaximum2D> HoughSpaceMaxima;

        ///2D Histogram containing Hough space
        TH2F* HoughSpaceHistogram;

        ///Histogram containing x axis of the Hough space
        TH1F* HoughSpaceXHistogram;

        ///Histogram containing y axis of the Hough space
        TH1F* HoughSpaceYHistogram;

        ///Graph for map keys
        TGraph* HoughSpaceKeyValueGraph;

        ///Histogram for map values
        TH1I* HoughSpaceValueHistogram;

        ///graph holding the found maxima (with standard pathfinder method)
        TGraph* HoughSpaceIntersectionGraph1;

        ///graph holding the found maxima (with root method)
        TGraph* HoughSpaceIntersectionGraph2;

        ///list of all root objects and their draw options
        std::list< std::pair<TObject*, const char*> > RootObjectList;

};//class
}//end namespace

#endif//HOUGHSPACEANALYZER_H
