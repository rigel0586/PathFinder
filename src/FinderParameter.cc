#include "FinderParameter.h"
#include <iostream>

using namespace std;
using namespace pathfinder;

/*
constructors
*/
FinderParameter::FinderParameter():
    _isStraightLine(false),
    _isHelix(false),
    _findCurler(false),
    _useVertex(false),  /*Default: no vertex constaint*/
    _useConformalMapping(false),  /*Default: no conformal mapping*/
    _useIntersections(false), /*Default: full Hough space is used*/
    _maxXYDistance(0.),
    _maxSZDistance(0.),
    _maxXYDistanceFit(0.),
    _maxSZDistanceFit(0.),
    _minimumHitNumber(0),
    _numberXYThetaBins(0),
    _numberXYDzeroBins(0),
    _numberXYOmegaBins(0),
    _numberSZThetaBins(0),
    _numberSZDzeroBins(0),
    _maxDxy(0.),
    _maxDsz(0.),
    _allowedHitDistance(-1.),/*Default: hit distance is not used, set to -1.*/
    _searchNeighborhood(false),
    _saveRootFile(false)
{
}

FinderParameter::FinderParameter(bool isStraightLine, bool isHelix) :
    _isStraightLine(isStraightLine),
    _isHelix(isHelix),
    _findCurler(false),
    _useVertex(false) /*Default: no vertex constaint*/,
    _useConformalMapping(false) /*Default: no conformal mapping*/,
    _useIntersections(false), /*Default: full Hough space is used*/
    _maxXYDistance(0.),
    _maxSZDistance(0.),
    _maxXYDistanceFit(0.),
    _maxSZDistanceFit(0.),
    _minimumHitNumber(0),
    _numberXYThetaBins(0),
    _numberXYDzeroBins(0),
    _numberXYOmegaBins(0),
    _numberSZThetaBins(0),
    _numberSZDzeroBins(0),
    _maxDxy(0.),
    _maxDsz(0.),
    _allowedHitDistance(-1.),/*Default: hit distance is not used, set to -1.*/
    _searchNeighborhood(false),
    _saveRootFile(false)
{
}

void FinderParameter::print() const
{
    cout << "printing FinderParameters: " << endl;
    cout << "Track Type: ";
    if(_isStraightLine && !(_isHelix))
        cout << "Straight Line" << endl;
    else if(!(_isStraightLine) && _isHelix)
    {
        cout << "Helix" << endl;
        if(_findCurler)
            cout << "find curler" << endl;
    }
    else
        cout << "unknown" << endl;

    if(_useVertex)
    {
        cout << "Using Vertex Constraint" << endl;
        cout << "Chosen Vertex: " << _VertexPosition.first << " " << _VertexPosition.second << endl;
    }

    if(_useIntersections)
      {
	cout << "Only Intersections of functions are used for the Hough space"<<endl;
      }

    cout << "maxXYDistance: " << _maxXYDistance << endl;
    cout << "maxSZDistance: " << _maxSZDistance << endl;
    cout << "maxXYDistanceFit: " << _maxXYDistanceFit << endl;
    cout << "maxSZDistanceFit: " << _maxSZDistanceFit << endl;
    cout << "minimumHitNumber: " << _minimumHitNumber << endl;
    cout << "numberXYThetaBins: " << _numberXYThetaBins << endl;
    cout << "numberXYDzeroBins: " << _numberXYDzeroBins << endl;
    cout << "numberXYOmegaBins: " << _numberXYOmegaBins << endl;
    cout << "numberSZThetaBins: " << _numberSZThetaBins << endl;
    cout << "numberSZDzeroBins: " << _numberSZDzeroBins << endl;
    cout << "maxDxy: " << _maxDxy << endl;
    cout << "maxDsz: " << _maxDsz << endl;

    if(_searchNeighborhood)
    {
        cout << "search neighborhood of maxima in Hough space." << endl;
    }
    if(_saveRootFile)
    {
        cout << "Save Hough Space to Root Tree." << endl;
    }

    if(_useVertex)cout << "Use Vertex Constraint" << endl;

    if(_useConformalMapping)cout << "use conformal Mapping" << endl;
}
