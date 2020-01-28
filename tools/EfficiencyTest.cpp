//c++
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <map>

//root
#include "TH1F.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"

//pathfinder
#include "TrackGenerator.h"
#include "FinderParameter.h"
#include "HoughTrafoTrackFinder.h"

using namespace std;
using namespace pathfinder;

struct GraphPoint
{
  GraphPoint(double _x, double _xlow, double _xhigh, double _y, double _ylow, double _yhigh):
    x(_x), xlow(_xlow), xhigh(_xhigh), y(_y), ylow(_ylow), yhigh(_yhigh)
  {};
  double x;
  double xlow;
  double xhigh;
  double y;
  double ylow;
  double yhigh;
};

map<int,GraphPoint> nomGraphValuesSLEfficiency()
{
  map<int,GraphPoint> graphPoints;
  int pointcounter = 0;
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.25,1.25,1.25,0,0,0.0615421)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(3.75,1.25,1.25,0.0465116,0.0299954,0.0581073)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(6.25,1.25,1.25,0.5,0.0878963,0.0878963)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(8.75,1.25,1.25,0.755102,0.0769642,0.0649799)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(11.25,1.25,1.25,0.904762,0.0689575,0.0450368)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(13.75,1.25,1.25,0.921569,0.0577131,0.0371735)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(16.25,1.25,1.25,0.978723,0.0472556,0.0176116)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(18.75,1.25,1.25,1,0.0450058,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(21.25,1.25,1.25,1,0.054289,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(23.75,1.25,1.25,1,0.0384335,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(26.25,1.25,1.25,1,0.0485649,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(28.75,1.25,1.25,1,0.054289,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(31.25,1.25,1.25,1,0.0450058,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(33.75,1.25,1.25,0.999561,0.000579527,0.000283883)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(36.25,1.25,1.25,1,0.0473176,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(38.75,1.25,1.25,1,0.0450058,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(41.25,1.25,1.25,1,0.0615421,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(43.75,1.25,1.25,1,0.0392523,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(46.25,1.25,1.25,1,0.054289,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(48.75,1.25,1.25,1,0.0769639,0)));
  
  return graphPoints;
}

map<int,GraphPoint> nomGraphValuesHEfficiency()
{
  map<int,GraphPoint> graphPoints;
  int pointcounter = 0;
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.25,1.25,1.25,0.842105,0.0824322,0.0608143)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(3.75,1.25,1.25,0.985075,0.0335018,0.012353)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(6.25,1.25,1.25,1,0.028371,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(8.75,1.25,1.25,0.987179,0.028878,0.0106105)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(11.25,1.25,1.25,0.985507,0.0325541,0.0119949)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(13.75,1.25,1.25,0.988095,0.0268561,0.00985247)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(16.25,1.25,1.25,1,0.0233387,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(18.75,1.25,1.25,1,0.028371,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(21.25,1.25,1.25,1,0.0292727,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(23.75,1.25,1.25,1,0.0236382,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(26.25,1.25,1.25,1,0.030738,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(28.75,1.25,1.25,1,0.036894,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(31.25,1.25,1.25,0.985294,0.0330212,0.0121713)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(33.75,1.25,1.25,0.998954,0.000707125,0.000451762)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(36.25,1.25,1.25,1,0.0279407,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(38.75,1.25,1.25,0.986111,0.031229,0.011495)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(41.25,1.25,1.25,0.982759,0.0385516,0.0142705)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(43.75,1.25,1.25,1,0.0252589,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(46.25,1.25,1.25,1,0.037648,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(48.75,1.25,1.25,0.978261,0.0482456,0.0179947)));

  return graphPoints;
}

map<int,GraphPoint> nomGraphValuesHVEfficiency()
{
  map<int,GraphPoint> graphPoints;
  int pointcounter = 0;
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.25,1.25,1.25,0.842105,0.0824322,0.0608143)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(3.75,1.25,1.25,0.985075,0.0335018,0.012353)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(6.25,1.25,1.25,1,0.028371,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(8.75,1.25,1.25,0.987179,0.028878,0.0106105)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(11.25,1.25,1.25,0.985507,0.0325541,0.0119949)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(13.75,1.25,1.25,0.988095,0.0268561,0.00985247)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(16.25,1.25,1.25,1,0.0233387,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(18.75,1.25,1.25,1,0.028371,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(21.25,1.25,1.25,1,0.0292727,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(23.75,1.25,1.25,1,0.0236382,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(26.25,1.25,1.25,1,0.030738,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(28.75,1.25,1.25,1,0.036894,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(31.25,1.25,1.25,0.985294,0.0330212,0.0121713)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(33.75,1.25,1.25,0.998954,0.000707125,0.000451762)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(36.25,1.25,1.25,1,0.0279407,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(38.75,1.25,1.25,0.986111,0.031229,0.011495)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(41.25,1.25,1.25,0.982759,0.0385516,0.0142705)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(43.75,1.25,1.25,1,0.0252589,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(46.25,1.25,1.25,1,0.037648,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(48.75,1.25,1.25,0.956522,0.0545151,0.0280427)));

  return graphPoints;
}

map<int,GraphPoint> nomGraphValuesSLD0Efficiency()
{
  map<int,GraphPoint> graphPoints;
  int pointcounter = 0;
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-294,6,6,1,0.0188105,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-282,6,6,1,0.0167571,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-270,6,6,1,0.0192027,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-258,6,6,1,0.0178967,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-246,6,6,1,0.0180723,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-234,6,6,1,0.0178967,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-222,6,6,1,0.0224841,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-210,6,6,1,0.0190046,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-198,6,6,1,0.0164577,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-186,6,6,1,0.016606,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-174,6,6,1,0.0192027,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-162,6,6,1,0.0178967,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-150,6,6,1,0.0214375,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-138,6,6,1,0.0188105,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-126,6,6,1,0.0180723,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-114,6,6,1,0.0192027,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-102,6,6,1,0.0167571,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-90,6,6,1,0.019405,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-78,6,6,1,0.0167571,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-66,6,6,1,0.0186204,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-54,6,6,0.989796,0.0230846,0.00844472)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-42,6,6,1,0.019405,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-30,6,6,1,0.0178967,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-18,6,6,1,0.0224841,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-6,6,6,1,0.0156203,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(6,6,6,1,0.0214375,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(18,6,6,1,0.0216899,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(30,6,6,1,0.0172272,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(42,6,6,1,0.016606,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(54,6,6,1,0.0170676,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(66,6,6,1,0.0200383,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(78,6,6,1,0.0214375,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(90,6,6,1,0.0202587,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(102,6,6,1,0.0188105,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(114,6,6,1,0.0188105,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(126,6,6,1,0.0182514,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(138,6,6,1,0.0188105,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(150,6,6,1,0.0167571,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(162,6,6,1,0.0200383,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(174,6,6,1,0.0186204,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(186,6,6,1,0.0230467,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(198,6,6,1,0.0182514,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(210,6,6,1,0.016606,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(222,6,6,0.989796,0.0230846,0.00844472)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(234,6,6,1,0.0200383,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(246,6,6,1,0.0164577,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(258,6,6,1,0.018434,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(270,6,6,1,0.0142876,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(282,6,6,1,0.0180723,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(294,6,6,1,0.015489,0)));

  return graphPoints;
}

map<int,GraphPoint> nomGraphValuesHD0Efficiency()
{
  map<int,GraphPoint> graphPoints;
  int pointcounter = 0;
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-294,6,6,1,0.014985,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-282,6,6,1,0.0139627,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-270,6,6,1,0.0161688,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-258,6,6,1,0.0151079,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-246,6,6,1,0.0163119,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-234,6,6,1,0.014864,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-222,6,6,0.990826,0.0207904,0.00759236)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-210,6,6,1,0.0157539,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-198,6,6,1,0.0139627,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-186,6,6,1,0.0145127,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-174,6,6,1,0.0158898,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-162,6,6,1,0.0147451,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-150,6,6,1,0.0177245,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-138,6,6,1,0.0156203,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-126,6,6,1,0.0153598,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-114,6,6,1,0.0161688,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-102,6,6,0.977099,0.0217869,0.0124429)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-90,6,6,1,0.0161688,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-78,6,6,1,0.0137542,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-66,6,6,1,0.014864,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-54,6,6,0.991379,0.0195537,0.00713413)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-42,6,6,1,0.0163119,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-30,6,6,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-18,6,6,0.990909,0.0206042,0.00752333)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-6,6,6,0.992537,0.0169596,0.00617569)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(6,6,6,1,0.0180723,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(18,6,6,0.990654,0.021173,0.0077343)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(30,6,6,1,0.0142876,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(42,6,6,1,0.0139627,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(54,6,6,0.992063,0.0180223,0.00656785)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(66,6,6,1,0.0163119,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(78,6,6,1,0.0170676,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(90,6,6,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(102,6,6,1,0.0161688,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(114,6,6,0.991597,0.0190676,0.00695425)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(126,6,6,0.991525,0.019227,0.00701319)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(138,6,6,1,0.0147451,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(150,6,6,1,0.0139627,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(162,6,6,0.991525,0.019227,0.00701319)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(174,6,6,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(186,6,6,1,0.0178967,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(198,6,6,1,0.014985,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(210,6,6,1,0.0136522,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(222,6,6,0.991597,0.0190676,0.00695425)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(234,6,6,0.99115,0.0200652,0.00732356)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(246,6,6,0.984496,0.0200936,0.0100113)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(258,6,6,1,0.0163119,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(270,6,6,0.993548,0.0146864,0.00533888)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(282,6,6,0.983193,0.0217489,0.010852)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(294,6,6,1,0.0131644,0)));

  return graphPoints;
}

map<int,GraphPoint> nomGraphValuesHVD0Efficiency()
{
  map<int,GraphPoint> graphPoints;
  int pointcounter = 0;
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-294,6,6,1,0.014985,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-282,6,6,1,0.0139627,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-270,6,6,1,0.0161688,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-258,6,6,0.991736,0.0187568,0.00683929)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-246,6,6,1,0.0163119,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-234,6,6,1,0.014864,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-222,6,6,0.990826,0.0207904,0.00759236)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-210,6,6,1,0.0157539,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-198,6,6,1,0.0139627,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-186,6,6,1,0.0145127,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-174,6,6,1,0.0158898,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-162,6,6,1,0.0147451,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-150,6,6,1,0.0177245,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-138,6,6,1,0.0156203,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-126,6,6,1,0.0153598,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-114,6,6,1,0.0161688,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-102,6,6,0.977099,0.0217869,0.0124429)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-90,6,6,1,0.0161688,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-78,6,6,1,0.0137542,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-66,6,6,1,0.014864,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-54,6,6,0.991379,0.0195537,0.00713413)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-42,6,6,1,0.0163119,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-30,6,6,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-18,6,6,0.990909,0.0206042,0.00752333)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-6,6,6,0.992537,0.0169596,0.00617569)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(6,6,6,1,0.0180723,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(18,6,6,0.990654,0.021173,0.0077343)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(30,6,6,1,0.0142876,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(42,6,6,1,0.0139627,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(54,6,6,0.992063,0.0180223,0.00656785)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(66,6,6,1,0.0163119,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(78,6,6,1,0.0170676,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(90,6,6,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(102,6,6,1,0.0161688,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(114,6,6,0.991597,0.0190676,0.00695425)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(126,6,6,0.991525,0.019227,0.00701319)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(138,6,6,1,0.0147451,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(150,6,6,1,0.0139627,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(162,6,6,0.991525,0.019227,0.00701319)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(174,6,6,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(186,6,6,1,0.0178967,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(198,6,6,1,0.014985,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(210,6,6,1,0.0136522,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(222,6,6,0.991597,0.0190676,0.00695425)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(234,6,6,0.99115,0.0200652,0.00732356)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(246,6,6,0.984496,0.0200936,0.0100113)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(258,6,6,1,0.0163119,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(270,6,6,0.993548,0.0146864,0.00533888)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(282,6,6,0.983193,0.0217489,0.010852)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(294,6,6,1,0.0131644,0)));

  return graphPoints;
}


map<int,GraphPoint> nomGraphValuesSLPhi0Efficiency()
{
  map<int,GraphPoint> graphPoints;
  int pointcounter = 0;
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-3.136,0.064,0.064,0,0,0.108745)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-3.008,0.064,0.064,0,0,0.0576885)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.88,0.064,0.064,0.0909091,0.0585162,0.107601)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.752,0.064,0.064,0.5,0.114707,0.114707)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.624,0.064,0.064,1,0.080318,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.496,0.064,0.064,1,0.0636685,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.368,0.064,0.064,1,0.054289,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.24,0.064,0.064,1,0.0498797,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.112,0.064,0.064,1,0.0527351,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.984,0.064,0.064,1,0.0923963,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.856,0.064,0.064,1,0.0659471,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.728,0.064,0.064,1,0.0659471,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.6,0.064,0.064,1,0.0659471,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.472,0.064,0.064,1,0.0659471,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.344,0.064,0.064,1,0.0839775,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.216,0.064,0.064,1,0.0559371,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.088,0.064,0.064,1,0.0769639,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.96,0.064,0.064,1,0.0450058,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.832,0.064,0.064,1,0.080318,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.704,0.064,0.064,1,0.0879861,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.576,0.064,0.064,1,0.080318,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.448,0.064,0.064,0.9,0.0878452,0.0539436)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.32,0.064,0.064,0.0606061,0.0390617,0.0744424)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.192,0.064,0.064,0,0,0.059553)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.064,0.064,0.064,0,0,0.0450058)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.064,0.064,0.064,0,0,0.0636685)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.192,0.064,0.064,0,0,0.0710311)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.32,0.064,0.064,0.2,0.0763539,0.100361)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.448,0.064,0.064,0.875,0.106886,0.0672642)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.576,0.064,0.064,1,0.0559371,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.704,0.064,0.064,1,0.054289,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.832,0.064,0.064,1,0.0683948,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.96,0.064,0.064,1,0.0576885,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.088,0.064,0.064,1,0.00044569,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.216,0.064,0.064,1,0.0683948,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.344,0.064,0.064,1,0.0636685,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.472,0.064,0.064,1,0.080318,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.6,0.064,0.064,0.928571,0.0865904,0.0460158)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.728,0.064,0.064,1,0.0839775,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.856,0.064,0.064,1,0.0738787,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.984,0.064,0.064,1,0.0683948,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.112,0.064,0.064,1,0.0576885,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.24,0.064,0.064,1,0.0636685,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.368,0.064,0.064,1,0.0559371,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.496,0.064,0.064,1,0.059553,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.624,0.064,0.064,0.961538,0.0829999,0.0318462)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.752,0.064,0.064,0.695652,0.125034,0.10478)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.88,0.064,0.064,0,0,0.0498797)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(3.008,0.064,0.064,0,0,0.0683948)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(3.136,0.064,0.064,0,0,0.080318)));


  return graphPoints;
}

map<int,GraphPoint> nomGraphValuesHPhi0Efficiency()
{
  map<int,GraphPoint> graphPoints;
  int pointcounter = 0;
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-3.136,0.064,0.064,1,0.0923963,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-3.008,0.064,0.064,1,0.0450058,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.88,0.064,0.064,1,0.054289,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.752,0.064,0.064,1,0.0473176,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.624,0.064,0.064,0.969697,0.0662957,0.0250873)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.496,0.064,0.064,1,0.0392523,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.368,0.064,0.064,1,0.0439326,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.24,0.064,0.064,1,0.0384335,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.112,0.064,0.064,1,0.0429093,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.984,0.064,0.064,1,0.0659471,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.856,0.064,0.064,1,0.0527351,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.728,0.064,0.064,1,0.0485649,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.6,0.064,0.064,1,0.0473176,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.472,0.064,0.064,1,0.0498797,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.344,0.064,0.064,1,0.0485649,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.216,0.064,0.064,1,0.034803,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.088,0.064,0.064,1,0.0498797,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.96,0.064,0.064,1,0.0329363,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.832,0.064,0.064,1,0.0527351,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.704,0.064,0.064,1,0.0559371,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.576,0.064,0.064,1,0.0498797,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.448,0.064,0.064,0.970588,0.0644419,0.0243491)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.32,0.064,0.064,1,0.0392523,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.192,0.064,0.064,1,0.0461328,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.064,0.064,0.064,0.961538,0.0485142,0.0248122)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.064,0.064,0.064,0.945946,0.0669215,0.0348485)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.192,0.064,0.064,1,0.054289,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.32,0.064,0.064,1,0.0409995,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.448,0.064,0.064,1,0.0615421,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.576,0.064,0.064,1,0.0485649,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.704,0.064,0.064,1,0.0392523,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.832,0.064,0.064,0.972222,0.0610285,0.0229957)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.96,0.064,0.064,1,0.0485649,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.088,0.064,0.064,1,0.000443437,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.216,0.064,0.064,1,0.0473176,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.344,0.064,0.064,0.976744,0.0514812,0.0192506)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.472,0.064,0.064,0.896552,0.0905401,0.055785)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.6,0.064,0.064,0.914286,0.0764452,0.0463011)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.728,0.064,0.064,1,0.0636685,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.856,0.064,0.064,1,0.054289,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.984,0.064,0.064,1,0.0498797,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.112,0.064,0.064,1,0.0498797,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.24,0.064,0.064,1,0.0512677,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.368,0.064,0.064,1,0.0439326,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.496,0.064,0.064,1,0.0439326,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.624,0.064,0.064,1,0.0527351,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.752,0.064,0.064,1,0.0473176,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.88,0.064,0.064,1,0.0392523,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(3.008,0.064,0.064,1,0.0429093,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(3.136,0.064,0.064,0.827586,0.0998735,0.072402)));

  return graphPoints;
}

map<int,GraphPoint> nomGraphValuesHVPhi0Efficiency()
{
  map<int,GraphPoint> graphPoints;
  int pointcounter = 0;
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-3.136,0.064,0.064,1,0.0923963,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-3.008,0.064,0.064,1,0.0450058,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.88,0.064,0.064,1,0.054289,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.752,0.064,0.064,1,0.0473176,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.624,0.064,0.064,0.969697,0.0662957,0.0250873)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.496,0.064,0.064,1,0.0392523,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.368,0.064,0.064,1,0.0439326,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.24,0.064,0.064,1,0.0384335,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.112,0.064,0.064,1,0.0429093,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.984,0.064,0.064,1,0.0659471,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.856,0.064,0.064,1,0.0527351,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.728,0.064,0.064,1,0.0485649,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.6,0.064,0.064,1,0.0473176,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.472,0.064,0.064,1,0.0498797,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.344,0.064,0.064,1,0.0485649,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.216,0.064,0.064,1,0.034803,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.088,0.064,0.064,1,0.0498797,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.96,0.064,0.064,1,0.0329363,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.832,0.064,0.064,1,0.0527351,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.704,0.064,0.064,1,0.0559371,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.576,0.064,0.064,1,0.0498797,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.448,0.064,0.064,0.970588,0.0644419,0.0243491)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.32,0.064,0.064,1,0.0392523,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.192,0.064,0.064,1,0.0461328,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.064,0.064,0.064,0.961538,0.0485142,0.0248122)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.064,0.064,0.064,0.918919,0.0726664,0.0438177)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.192,0.064,0.064,1,0.054289,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.32,0.064,0.064,1,0.0409995,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.448,0.064,0.064,1,0.0615421,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.576,0.064,0.064,1,0.0485649,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.704,0.064,0.064,1,0.0392523,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.832,0.064,0.064,0.972222,0.0610285,0.0229957)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.96,0.064,0.064,1,0.0485649,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.088,0.064,0.064,1,0.000443437,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.216,0.064,0.064,1,0.0473176,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.344,0.064,0.064,0.976744,0.0514812,0.0192506)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.472,0.064,0.064,0.896552,0.0905401,0.055785)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.6,0.064,0.064,0.914286,0.0764452,0.0463011)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.728,0.064,0.064,1,0.0636685,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.856,0.064,0.064,1,0.054289,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.984,0.064,0.064,1,0.0498797,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.112,0.064,0.064,1,0.0498797,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.24,0.064,0.064,1,0.0512677,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.368,0.064,0.064,1,0.0439326,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.496,0.064,0.064,1,0.0439326,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.624,0.064,0.064,1,0.0527351,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.752,0.064,0.064,1,0.0473176,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.88,0.064,0.064,1,0.0392523,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(3.008,0.064,0.064,1,0.0429093,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(3.136,0.064,0.064,0.827586,0.0998735,0.072402)));

  return graphPoints;
}


map<int,GraphPoint> nomGraphValuesSLZ0Efficiency()
{
  map<int,GraphPoint> graphPoints;
  int pointcounter = 0;
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-980,20,20,1,0.0267246,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-940,20,20,1,0.0151079,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-900,20,20,1,0.0202587,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-860,20,20,1,0.0169109,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-820,20,20,1,0.018434,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-780,20,20,0.988372,0.0262436,0.0096233)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-740,20,20,1,0.0178967,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-700,20,20,1,0.0196116,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-660,20,20,1,0.0167571,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-620,20,20,1,0.0178967,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-580,20,20,1,0.0207143,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-540,20,20,0.988095,0.0268561,0.00985247)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-500,20,20,1,0.0170676,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-460,20,20,1,0.0190046,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-420,20,20,1,0.0163119,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-380,20,20,1,0.0192027,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-340,20,20,1,0.0182514,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-300,20,20,1,0.0233387,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-260,20,20,1,0.0186204,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-220,20,20,1,0.0180723,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-180,20,20,1,0.0157539,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-140,20,20,1,0.0214375,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-100,20,20,1,0.0202587,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-60,20,20,1,0.0192027,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-20,20,20,1,0.0180723,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(20,20,20,1,0.0180723,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(60,20,20,1,0.0188105,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(100,20,20,1,0.0211909,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(140,20,20,1,0.0161688,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(180,20,20,1,0.019405,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(220,20,20,1,0.0263425,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(260,20,20,1,0.0239455,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(300,20,20,1,0.0224841,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(340,20,20,1,0.0180723,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(380,20,20,1,0.0160281,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(420,20,20,1,0.0161688,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(460,20,20,1,0.0180723,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(500,20,20,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(540,20,20,1,0.0182514,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(580,20,20,1,0.014628,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(620,20,20,1,0.0186204,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(660,20,20,1,0.0175556,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(700,20,20,1,0.0142876,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(740,20,20,1,0.0169109,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(780,20,20,1,0.0169109,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(820,20,20,1,0.0172272,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(860,20,20,1,0.0170676,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(900,20,20,1,0.0172272,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(940,20,20,1,0.018434,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(980,20,20,1,0.0211909,0)));

  return graphPoints;
}

map<int,GraphPoint> nomGraphValuesHZ0Efficiency()
{
  map<int,GraphPoint> graphPoints;
  int pointcounter = 0;
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-980,20,20,1,0.0209499,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-940,20,20,0.992481,0.0170855,0.00622213)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-900,20,20,1,0.0172272,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-860,20,20,0.992908,0.0161275,0.00586905)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-820,20,20,1,0.0156203,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-780,20,20,0.990741,0.0209799,0.00766267)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-740,20,20,1,0.0152328,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-700,20,20,0.99115,0.0200652,0.00732356)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-660,20,20,1,0.0140693,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-620,20,20,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-580,20,20,1,0.0173899,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-540,20,20,0.990099,0.0224101,0.00819384)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-500,20,20,0.992,0.0181645,0.0066204)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-460,20,20,0.990909,0.0206042,0.00752333)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-420,20,20,0.992126,0.0178822,0.00651613)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-380,20,20,0.991379,0.0195537,0.00713413)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-340,20,20,1,0.014864,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-300,20,20,1,0.0173899,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-260,20,20,1,0.0157539,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-220,20,20,1,0.0153598,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-180,20,20,0.992537,0.0169596,0.00617569)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-140,20,20,1,0.0175556,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-100,20,20,1,0.0158898,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-60,20,20,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-20,20,20,0.984,0.0207246,0.0103314)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(20,20,20,1,0.0158898,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(60,20,20,0.991667,0.0189109,0.00689629)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(100,20,20,1,0.0175556,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(140,20,20,1,0.0138576,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(180,20,20,1,0.014864,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(220,20,20,1,0.0188105,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(260,20,20,0.989011,0.0248279,0.00909444)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(300,20,20,1,0.0196116,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(340,20,20,0.983333,0.0215712,0.0107616)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(380,20,20,1,0.0140693,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(420,20,20,1,0.0133553,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(460,20,20,0.992,0.0181645,0.0066204)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(500,20,20,1,0.0127985,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(540,20,20,1,0.0151079,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(580,20,20,1,0.0122049,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(620,20,20,1,0.0153598,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(660,20,20,0.992308,0.0174748,0.00636573)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(700,20,20,1,0.0122863,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(740,20,20,1,0.0135518,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(780,20,20,1,0.014628,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(820,20,20,1,0.0139627,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(860,20,20,1,0.0143993,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(900,20,20,1,0.0134528,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(940,20,20,1,0.0145127,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(980,20,20,0.990476,0.0215699,0.00788164)));

  return graphPoints;
}

map<int,GraphPoint> nomGraphValuesHVZ0Efficiency()
{
  map<int,GraphPoint> graphPoints;
  int pointcounter = 0;
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-980,20,20,1,0.0209499,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-940,20,20,0.992481,0.0170855,0.00622213)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-900,20,20,1,0.0172272,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-860,20,20,0.992908,0.0161275,0.00586905)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-820,20,20,1,0.0156203,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-780,20,20,0.990741,0.0209799,0.00766267)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-740,20,20,1,0.0152328,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-700,20,20,0.99115,0.0200652,0.00732356)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-660,20,20,1,0.0140693,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-620,20,20,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-580,20,20,1,0.0173899,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-540,20,20,0.990099,0.0224101,0.00819384)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-500,20,20,0.992,0.0181645,0.0066204)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-460,20,20,0.990909,0.0206042,0.00752333)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-420,20,20,0.992126,0.0178822,0.00651613)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-380,20,20,0.991379,0.0195537,0.00713413)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-340,20,20,1,0.014864,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-300,20,20,1,0.0173899,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-260,20,20,1,0.0157539,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-220,20,20,1,0.0153598,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-180,20,20,0.992537,0.0169596,0.00617569)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-140,20,20,1,0.0175556,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-100,20,20,1,0.0158898,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-60,20,20,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-20,20,20,0.984,0.0207246,0.0103314)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(20,20,20,1,0.0158898,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(60,20,20,0.991667,0.0189109,0.00689629)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(100,20,20,1,0.0175556,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(140,20,20,1,0.0138576,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(180,20,20,1,0.014864,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(220,20,20,1,0.0188105,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(260,20,20,0.989011,0.0248279,0.00909444)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(300,20,20,1,0.0196116,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(340,20,20,0.983333,0.0215712,0.0107616)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(380,20,20,1,0.0140693,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(420,20,20,1,0.0133553,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(460,20,20,0.992,0.0181645,0.0066204)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(500,20,20,1,0.0127985,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(540,20,20,1,0.0151079,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(580,20,20,1,0.0122049,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(620,20,20,1,0.0153598,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(660,20,20,0.992308,0.0174748,0.00636573)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(700,20,20,1,0.0122863,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(740,20,20,1,0.0135518,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(780,20,20,1,0.014628,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(820,20,20,0.992366,0.0173431,0.00631713)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(860,20,20,1,0.0143993,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(900,20,20,1,0.0134528,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(940,20,20,1,0.0145127,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(980,20,20,0.990476,0.0215699,0.00788164)));

  return graphPoints;
}


map<int,GraphPoint> nomGraphValuesSLTanLEfficiency()
{
  map<int,GraphPoint> graphPoints;
  int pointcounter = 0;
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-9.8,0.2,0.2,1,0.0170676,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-9.4,0.2,0.2,1,0.0211909,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-9,0.2,0.2,1,0.018434,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-8.6,0.2,0.2,1,0.0209499,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-8.2,0.2,0.2,1,0.0214375,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-7.8,0.2,0.2,1,0.0160281,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-7.4,0.2,0.2,1,0.0178967,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-7,0.2,0.2,1,0.0242609,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-6.6,0.2,0.2,1,0.0186204,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-6.2,0.2,0.2,1,0.0169109,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-5.8,0.2,0.2,1,0.0188105,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-5.4,0.2,0.2,0.986301,0.030811,0.0113375)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-5,0.2,0.2,1,0.014985,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-4.6,0.2,0.2,1,0.0200383,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-4.2,0.2,0.2,1,0.0200383,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-3.8,0.2,0.2,1,0.0180723,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-3.4,0.2,0.2,1,0.018434,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-3,0.2,0.2,1,0.018434,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.6,0.2,0.2,1,0.0188105,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.2,0.2,0.2,1,0.0216899,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.8,0.2,0.2,1,0.0202587,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.4,0.2,0.2,1,0.0173899,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1,0.2,0.2,1,0.0188105,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.6,0.2,0.2,1,0.0172272,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.2,0.2,0.2,1,0.0173899,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.2,0.2,0.2,1,0.0156203,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.6,0.2,0.2,1,0.0196116,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1,0.2,0.2,1,0.0170676,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.4,0.2,0.2,1,0.0214375,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.8,0.2,0.2,0.988636,0.0256584,0.00940454)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.2,0.2,0.2,1,0.0192027,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.6,0.2,0.2,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(3,0.2,0.2,1,0.0196116,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(3.4,0.2,0.2,1,0.0190046,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(3.8,0.2,0.2,1,0.0188105,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(4.2,0.2,0.2,1,0.0178967,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(4.6,0.2,0.2,1,0.0190046,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(5,0.2,0.2,1,0.0167571,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(5.4,0.2,0.2,1,0.0196116,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(5.8,0.2,0.2,1,0.0167571,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(6.2,0.2,0.2,1,0.0186204,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(6.6,0.2,0.2,1,0.0170676,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(7,0.2,0.2,1,0.0200383,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(7.4,0.2,0.2,1,0.019405,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(7.8,0.2,0.2,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(8.2,0.2,0.2,1,0.0157539,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(8.6,0.2,0.2,1,0.0163119,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(9,0.2,0.2,1,0.0182514,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(9.4,0.2,0.2,1,0.0196116,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(9.8,0.2,0.2,1,0.015489,0)));

  return graphPoints;
}

map<int,GraphPoint> nomGraphValuesHTanLEfficiency()
{
  map<int,GraphPoint> graphPoints;
  int pointcounter = 0;
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-9.8,0.2,0.2,1,0.014628,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-9.4,0.2,0.2,1,0.0167571,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-9,0.2,0.2,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-8.6,0.2,0.2,1,0.0169109,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-8.2,0.2,0.2,0.982906,0.0221132,0.0110373)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-7.8,0.2,0.2,1,0.0138576,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-7.4,0.2,0.2,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-7,0.2,0.2,1,0.0175556,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-6.6,0.2,0.2,0.991597,0.0190676,0.00695425)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-6.2,0.2,0.2,1,0.0142876,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-5.8,0.2,0.2,1,0.0161688,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-5.4,0.2,0.2,0.988764,0.0253755,0.00929885)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-5,0.2,0.2,1,0.0132591,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-4.6,0.2,0.2,1,0.0158898,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-4.2,0.2,0.2,0.991525,0.019227,0.00701319)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-3.8,0.2,0.2,1,0.0152328,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-3.4,0.2,0.2,1,0.0151079,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-3,0.2,0.2,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.6,0.2,0.2,1,0.0157539,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.2,0.2,0.2,1,0.0190046,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.8,0.2,0.2,1,0.0164577,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.4,0.2,0.2,1,0.0139627,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1,0.2,0.2,1,0.0157539,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.6,0.2,0.2,0.992063,0.0180223,0.00656785)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.2,0.2,0.2,0.992248,0.0176085,0.00641509)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.2,0.2,0.2,1,0.013071,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.6,0.2,0.2,1,0.0153598,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1,0.2,0.2,1,0.0145127,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.4,0.2,0.2,1,0.0170676,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.8,0.2,0.2,0.97479,0.0239283,0.0136948)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.2,0.2,0.2,1,0.0156203,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.6,0.2,0.2,1,0.0131644,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(3,0.2,0.2,1,0.0161688,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(3.4,0.2,0.2,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(3.8,0.2,0.2,0.991803,0.0186051,0.00678322)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(4.2,0.2,0.2,1,0.0147451,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(4.6,0.2,0.2,1,0.0161688,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(5,0.2,0.2,1,0.014628,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(5.4,0.2,0.2,1,0.0164577,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(5.8,0.2,0.2,1,0.0141776,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(6.2,0.2,0.2,0.991803,0.0186051,0.00678322)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(6.6,0.2,0.2,0.992248,0.0176085,0.00641509)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(7,0.2,0.2,1,0.0161688,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(7.4,0.2,0.2,1,0.0169109,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(7.8,0.2,0.2,1,0.0134528,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(8.2,0.2,0.2,1,0.0134528,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(8.6,0.2,0.2,0.992701,0.0165927,0.00604043)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(9,0.2,0.2,0.973684,0.02495,0.014294)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(9.4,0.2,0.2,0.982456,0.0226832,0.0113276)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(9.8,0.2,0.2,1,0.0136522,0)));


  return graphPoints;
}

map<int,GraphPoint> nomGraphValuesHVTanLEfficiency()
{
  map<int,GraphPoint> graphPoints;
  int pointcounter = 0;
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-9.8,0.2,0.2,1,0.014628,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-9.4,0.2,0.2,1,0.0167571,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-9,0.2,0.2,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-8.6,0.2,0.2,1,0.0169109,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-8.2,0.2,0.2,0.982906,0.0221132,0.0110373)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-7.8,0.2,0.2,1,0.0138576,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-7.4,0.2,0.2,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-7,0.2,0.2,1,0.0175556,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-6.6,0.2,0.2,0.991597,0.0190676,0.00695425)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-6.2,0.2,0.2,1,0.0142876,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-5.8,0.2,0.2,1,0.0161688,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-5.4,0.2,0.2,0.988764,0.0253755,0.00929885)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-5,0.2,0.2,1,0.0132591,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-4.6,0.2,0.2,1,0.0158898,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-4.2,0.2,0.2,0.991525,0.019227,0.00701319)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-3.8,0.2,0.2,1,0.0152328,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-3.4,0.2,0.2,1,0.0151079,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-3,0.2,0.2,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.6,0.2,0.2,1,0.0157539,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-2.2,0.2,0.2,1,0.0190046,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.8,0.2,0.2,1,0.0164577,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1.4,0.2,0.2,1,0.0139627,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-1,0.2,0.2,1,0.0157539,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.6,0.2,0.2,0.992063,0.0180223,0.00656785)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(-0.2,0.2,0.2,0.992248,0.0176085,0.00641509)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.2,0.2,0.2,1,0.013071,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(0.6,0.2,0.2,1,0.0153598,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1,0.2,0.2,1,0.0145127,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.4,0.2,0.2,1,0.0170676,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(1.8,0.2,0.2,0.97479,0.0239283,0.0136948)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.2,0.2,0.2,1,0.0156203,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(2.6,0.2,0.2,1,0.0131644,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(3,0.2,0.2,1,0.0161688,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(3.4,0.2,0.2,1,0.015489,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(3.8,0.2,0.2,0.991803,0.0186051,0.00678322)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(4.2,0.2,0.2,1,0.0147451,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(4.6,0.2,0.2,1,0.0161688,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(5,0.2,0.2,1,0.014628,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(5.4,0.2,0.2,1,0.0164577,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(5.8,0.2,0.2,1,0.0141776,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(6.2,0.2,0.2,0.991803,0.0186051,0.00678322)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(6.6,0.2,0.2,0.992248,0.0176085,0.00641509)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(7,0.2,0.2,1,0.0161688,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(7.4,0.2,0.2,1,0.0169109,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(7.8,0.2,0.2,1,0.0134528,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(8.2,0.2,0.2,1,0.0134528,0)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(8.6,0.2,0.2,0.985401,0.0189403,0.00942701)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(9,0.2,0.2,0.973684,0.02495,0.014294)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(9.4,0.2,0.2,0.982456,0.0226832,0.0113276)));
  graphPoints.insert(make_pair(pointcounter++, GraphPoint(9.8,0.2,0.2,1,0.0136522,0)));

  return graphPoints;
}

double calculateTansverseMomentumFromOmega(double omega)
{

  double B = 3.5/*kg/A/s^2*/;
  double q = -1.60176565e-19/*A*s*/;
  double fpt = q*B/omega;
  fpt = fpt/(5.343e-19);//convert to GeV
  fpt = abs(fpt);//make sure all moment have the same sign

  return fpt/1000.;//Unanswered Question: why is the result wrong by a factor of 1000? It did work fine for the muons...
}

double calculateOmegaFromTransverseMomentum(double pt)
{
  double B = 3.5/*kg/A/s^2*/;
  double q = -1.60176565e-19/*A*s*/;
  double o = abs(q*B/pt/1000./5.343e-19);

  return o;
}

//function which prints simulated tracks
void printSimTracks(vector<TrackFinderTrack*> simtracks)
{
  
  //check that simulation worked
  for(unsigned int t = 0; t<simtracks.size(); t++)
    {
      simtracks[t]->getTrackParameter().print();
      vector<basicHit> currentTrackHits = simtracks[t]->getHitsOnTrack();
      for(unsigned int h =0; h<currentTrackHits.size(); h++)
	{
	  cout<<"Hit Number "<<h<<endl;
	  currentTrackHits[h].print();
	  double pos[3];
	  pos[0] = currentTrackHits[h].getX();
	  pos[1] = currentTrackHits[h].getY();
	  pos[2] = currentTrackHits[h].getZ();
	}
    }
}

//function which prints simulated tracks
void printSimTracks(vector<TrackFinderTrack> simtracks)
{

  //check that simulation worked
  for(unsigned int t = 0; t<simtracks.size(); t++)
    {
      simtracks[t].getTrackParameter().print();
      vector<basicHit> currentTrackHits = simtracks[t].getHitsOnTrack();
      for(unsigned int h =0; h<currentTrackHits.size(); h++)
	{
	  cout<<"Hit Number "<<h<<endl;
	  currentTrackHits[h].print();
	  double pos[3];
	  pos[0] = currentTrackHits[h].getX();
	  pos[1] = currentTrackHits[h].getY();
	  pos[2] = currentTrackHits[h].getZ();
	}
    }
}

TGraphAsymmErrors* createEfficiencyGraph(TH1* total, TH1* pass, Color_t c, Style_t m, const char* name, const char* title)
{
  TGraphAsymmErrors* graph = new TGraphAsymmErrors();
  //graph->GetYaxis()->SetRangeUser(0., 1.1);
  graph->SetNameTitle(name, title);
  graph->Divide(pass, total);
  graph->SetMarkerStyle(m);
  graph->SetMarkerColor(c);
  graph->SetLineColor(c);
  graph->SetFillColor(kWhite);
  return graph;
}

TGraphAsymmErrors* createNominalEfficiencyGraph(map<int,GraphPoint> graphValues, Color_t c, Style_t m, const char* name, const char* title)
{
  TGraphAsymmErrors* graph = new TGraphAsymmErrors();
  //  graph->GetYaxis()->SetRangeUser(0., 1.1);
  graph->SetNameTitle(name, title);
  graph->SetMarkerStyle(m);
  graph->SetMarkerColor(c);
  graph->SetLineColor(c);
  graph->SetFillColor(kWhite);

  //set points
  map<int,GraphPoint>::iterator iter = graphValues.begin();
  for(; iter != graphValues.end(); iter++)
    {
      graph->SetPoint((*iter).first, ((*iter).second).x , ((*iter).second).y);
      graph->SetPointError((*iter).first, ((*iter).second).xlow, ((*iter).second).xhigh, ((*iter).second).ylow, ((*iter).second).yhigh);
    }

  return graph;
}

TCanvas* createEfficiencyCanvas(TGraphAsymmErrors* grsl, TGraphAsymmErrors* grslnom, TGraphAsymmErrors* grh, TGraphAsymmErrors* grhnom, TGraphAsymmErrors* grhv, TGraphAsymmErrors* grhvnom, const char* name, const char* title)
{
  grsl->GetYaxis()->SetRangeUser(0., 1.1);
  grslnom->GetYaxis()->SetRangeUser(0., 1.1);
  grh->GetYaxis()->SetRangeUser(0., 1.1);
  grhnom->GetYaxis()->SetRangeUser(0., 1.1);
  grhv->GetYaxis()->SetRangeUser(0., 1.1);
  grhvnom->GetYaxis()->SetRangeUser(0., 1.1);

  TCanvas* canvas = new TCanvas(name,title,1);
  canvas->Divide(2,2);
  canvas->SetFillColor(kWhite);
  canvas->SetBorderMode(0);
  
  canvas->cd(1)->SetGridx();
  canvas->cd(1)->SetGridy();
  canvas->cd(1)->SetFillColor(kWhite);
  canvas->cd(1);
  grslnom->Draw("alp");
  grsl->Draw("p");
  
  canvas->cd(2)->SetGridx();
  canvas->cd(2)->SetGridy();
  canvas->cd(2)->SetFillColor(kWhite);
  canvas->cd(2);
  grhnom->Draw("alp");
  grh->Draw("p");
  
  canvas->cd(3)->SetGridx();
  canvas->cd(3)->SetGridy();
  canvas->cd(3)->SetFillColor(kWhite);
  canvas->cd(3);
  grhvnom->Draw("alp");
  grhv->Draw("p");
  
  canvas->Update();

  return canvas;
}

bool CompareTracks(TrackFinderTrack* simTrack, TrackFinderTrack* recoTrack)
{
  vector<basicHit> simHits = simTrack->getHitsOnTrack();
  vector<basicHit> recoHits = recoTrack->getHitsOnTrack();
  
  int correctHitCounter = 0;
  
  cout<<"Number of Hits on Track: "<<simHits.size()<<" "<<recoHits.size()<<endl;
  
  for(unsigned int s = 0; s<simHits.size(); s++)
    {
      double sPos[3];
      sPos[0] = simHits.at(s).getX();
      sPos[1] = simHits.at(s).getY();
      sPos[2] = simHits.at(s).getZ();
      
      for(unsigned int r = 0; r<recoHits.size(); r++)
	{
	  double rPos[3];
	  rPos[0] = recoHits.at(r).getX();
	  rPos[1] = recoHits.at(r).getY();
	  rPos[2] = recoHits.at(r).getZ();
	  
	  if(fabs(sPos[0]-rPos[0]) < 1e-10 &&
	     fabs(sPos[1]-rPos[1]) < 1e-10 &&
	     fabs(sPos[2]-rPos[2]) < 1e-10)
	    {
	      correctHitCounter++;
	    }
	  
	}
    }
  
  if( fabs((double)(simHits.size() - correctHitCounter)) < (double)(simHits.size()*25/100) )
    {
      return true;
    }
  else
    {
      return false;
    }
}

//main
int main(int argc, char**argv)
{
  if (argc != 3)
    {
      cout<<"Usage: EfficiencyTest <trackType> <nEvents>"<<endl;
      cout<<"trackType can be: sl, h, hv, all"<<endl;
      cout<<"sl: straight line"<<endl;
      cout<<"h: helix"<<endl;
      cout<<"hv: helix with vertex constraint"<<endl;
      cout<<"all: all track types"<<endl;
      return 1;
    }

  string trackType = argv[1];
  unsigned int nevents = atoi(argv[2]);
  
  double minPT = 1.;
  double maxPT = 50.;
  double minRadius = floor(1./calculateOmegaFromTransverseMomentum(minPT));
  double maxRadius = ceil(1./calculateOmegaFromTransverseMomentum(maxPT));
  
  cout<<"Range of radius: "<<minRadius<<" "<<maxRadius<<endl;
  
  //objects needed for track generation
  TGTrackParameterLimits* TrackParameterRanges = new TGTrackParameterLimits(-M_PI,
									    M_PI,
									    -300.,
									    300.,
									    minRadius,
									    maxRadius,
									    -10.,
									    10.,
									    -1000.,
									    1000.);
  
  TGEventType* EventType = new TGEventType(100,
					   1,
					   0,
					   0.001,
					   nevents);
  
  TGDetectorType* DetType = new TGDetectorType(-1000.,
					       1000.,
					       -500.,
					       500.,
					       -1000.,
					       1000.,
					       5.);
  
  //create Track Generator for curler
  TrackGenerator* TrackGen = new TrackGenerator(2 , *TrackParameterRanges, *EventType, *DetType); 
  

  //objects needed for track finding: one for straight lines, one for helices without vertex constraint, one for helices with vertex constraint
  FinderParameter* slFinderParameter = new FinderParameter(true, false);
  slFinderParameter -> setFindCurler(false);
  slFinderParameter -> setUseIntersections(false);
  slFinderParameter -> setMaxXYDistance(20.);
  slFinderParameter -> setMaxSZDistance(20.);
  slFinderParameter -> setMaxXYDistanceFit(10.);
  slFinderParameter -> setMaxSZDistanceFit(10.);
  slFinderParameter -> setMinimumHitNumber(5);
  slFinderParameter -> setNumberXYThetaBins(1000);
  slFinderParameter -> setNumberXYDzeroBins(1000);
  slFinderParameter -> setNumberXYOmegaBins(1000);
  slFinderParameter -> setNumberSZThetaBins(1000);
  slFinderParameter -> setNumberSZDzeroBins(1000);
  slFinderParameter -> setMaxDxy(5000);
  slFinderParameter -> setMaxDsz(5000);
  slFinderParameter -> setAllowedHitDistance(-1.);
  slFinderParameter -> setSearchNeighborhood(false);
  slFinderParameter -> setSaveRootFile(false);


  FinderParameter* hFinderParameter = new FinderParameter(false, true);
  hFinderParameter -> setFindCurler(true);
  hFinderParameter -> setUseIntersections(false);
  hFinderParameter -> setMaxXYDistance(20.);
  hFinderParameter -> setMaxSZDistance(20.);
  hFinderParameter -> setMaxXYDistanceFit(10.);
  hFinderParameter -> setMaxSZDistanceFit(10.);
  hFinderParameter -> setMinimumHitNumber(5);
  hFinderParameter -> setNumberXYThetaBins(1000);
  hFinderParameter -> setNumberXYDzeroBins(1000);
  hFinderParameter -> setNumberXYOmegaBins(1000);
  hFinderParameter -> setNumberSZThetaBins(1000);
  hFinderParameter -> setNumberSZDzeroBins(1000);
  hFinderParameter -> setMaxDxy(0.1);
  hFinderParameter -> setMaxDsz(5000);
  hFinderParameter -> setAllowedHitDistance(-1.);
  hFinderParameter -> setSearchNeighborhood(false);
  hFinderParameter -> setSaveRootFile(false);

  FinderParameter* hvFinderParameter = new FinderParameter(false, true);
  hvFinderParameter -> setFindCurler(true);
  hvFinderParameter -> setUseIntersections(false);
  hvFinderParameter -> setMaxXYDistance(20.);
  hvFinderParameter -> setMaxSZDistance(20.);
  hvFinderParameter -> setMaxXYDistanceFit(10.);
  hvFinderParameter -> setMaxSZDistanceFit(10.);
  hvFinderParameter -> setMinimumHitNumber(5);
  hvFinderParameter -> setNumberXYThetaBins(1000);
  hvFinderParameter -> setNumberXYDzeroBins(1000);
  hvFinderParameter -> setNumberXYOmegaBins(1000);
  hvFinderParameter -> setNumberSZThetaBins(1000);
  hvFinderParameter -> setNumberSZDzeroBins(1000);
  hvFinderParameter -> setMaxDxy(0.1);
  hvFinderParameter -> setMaxDsz(5000);
  hvFinderParameter -> setAllowedHitDistance(-1.);
  hvFinderParameter -> setSearchNeighborhood(false);
  hvFinderParameter -> setSaveRootFile(false);


  //define histograms for efficiency plots
  TH1F* simRadius = new TH1F("simRadius", "simRadius; p_{T} in GeV; Number of Events", 20, 0., maxPT);
  TH1F* simRadiusWithCuts = new TH1F("simRadiusWithCuts", "simRadiusWithCuts; p_{T} in GeV; Number of Events", 20, 0., maxPT);
  TH1F* slRecoRadius = new TH1F("slRecoRadius", "slRecoRadius; p_{T} in GeV; Number of Events", 20, 0., maxPT);
  TH1F* hRecoRadius = new TH1F("hRecoRadius", "hRecoRadius; p_{T} in GeV; Number of Events", 20, 0., maxPT);
  TH1F* hvRecoRadius = new TH1F("hvRecoRadius", "hvRecoRadius; p_{T} in GeV; Number of Events", 20, 0., maxPT);

  //and for parameter scans
  TH1F* simPhi0 = new TH1F("simPhi0","simPhi0; #phi_{0} in rad; Number of Entries", 50, -3.2, 3.2);
  TH1F* simPhi0WithCuts = new TH1F("simPhi0WithCuts","simPhi0WithCuts; #phi_{0} in rad; Number of Entries", 50, -3.2, 3.2);
  TH1F* slFoundPhi0 = new TH1F("slFoundPhi0","slFoundPhi0; #phi_{0} in rad; Number of Entries", 50, -3.2, 3.2);
  TH1F* hFoundPhi0 = new TH1F("hFoundPhi0","hFoundPhi0; #phi_{0} in rad; Number of Entries", 50, -3.2, 3.2);
  TH1F* hvFoundPhi0 = new TH1F("hvFoundPhi0","hvFoundPhi0; #phi_{0} in rad; Number of Entries", 50, -3.2, 3.2);
  TH1F* simD0 = new TH1F("simD0","simD0; d_{0} in mm; Number of Entries", 50, -300., 300.);
  TH1F* simD0WithCuts = new TH1F("simD0WithCuts","simD0WithCuts; d_{0} in mm; Number of Entries", 50, -300., 300.);
  TH1F* slFoundD0 = new TH1F("slFoundD0","slFoundD0; d_{0} in mm; Number of Entries", 50, -300., 300.);
  TH1F* hFoundD0 = new TH1F("hFoundD0","hFoundD0; d_{0} in mm; Number of Entries", 50, -300., 300.);
  TH1F* hvFoundD0 = new TH1F("hvFoundD0","hvFoundD0; d_{0} in mm; Number of Entries", 50, -300., 300.);
  TH1F* simTanL = new TH1F("simTanL","simTanL; tan #lambda; Number of Entries", 50, -10., 10.);
  TH1F* simTanLWithCuts = new TH1F("simTanLWithCuts","simTanLWithCuts; tan #lambda; Number of Entries", 50, -10., 10.);
  TH1F* slFoundTanL = new TH1F("slFoundTanL","slFoundTanL; tan #lambda; Number of Entries", 50, -10., 10.);
  TH1F* hFoundTanL = new TH1F("hFoundTanL","hFoundTanL; tan #lambda; Number of Entries", 50, -10., 10.);
  TH1F* hvFoundTanL = new TH1F("hvFoundTanL","hvFoundTanL; tan #lambda; Number of Entries", 50, -10., 10.);
  TH1F* simZ0 = new TH1F("simZ0","simZ0; z_{0} in mm; Number of Entries", 50, -1000., 1000.);
  TH1F* simZ0WithCuts = new TH1F("simZ0WithCuts","simZ0WithCuts; z_{0} in mm; Number of Entries", 50, -1000., 1000.);
  TH1F* slFoundZ0 = new TH1F("slFoundZ0","slFoundZ0; z_{0} in mm; Number of Entries", 50, -1000., 1000.);
  TH1F* hFoundZ0 = new TH1F("hFoundZ0","hFoundZ0; z_{0} in mm; Number of Entries", 50, -1000., 1000.);
  TH1F* hvFoundZ0 = new TH1F("hvFoundZ0","hvFoundZ0; z_{0} in mm; Number of Entries", 50, -1000., 1000.);


  //loop over events to be created
  for(unsigned int e = 0; e<nevents; e++)
    {
      //generate an event
      TrackGen->generateTracks(e);
      
      //get the simulated tracks and hits
      vector<TrackFinderTrack*> simtracks = TrackGen->getGeneratorTracks();
      vector<basicHit> allhits = TrackGen->getHits();

      //check that simulation worked
      //	printSimTracks(simtracks);
      
      //do some cleaning up of the hits
      //if the radius is large tha the size of the pad plane in y remove one half of the circle (to be closer to ILD track)
      //1.) create a vector containing all hits thatshould be removed before track finding.
      vector<basicHit> hitsForTrackFinding;
      vector<TrackFinderTrack> simTracksHitsRemoved;
      double yDetRange = DetType->getPadPlaneYmax() - DetType->getPadPlaneYmin();
      for(unsigned int t = 0; t<simtracks.size(); t++)
	{
	  //fill histograms with simulated radius
	  TrackParameterFull simTrackParam = simtracks[t]->getTrackParameter();
	  double omega = simTrackParam.getOmega();
	  double phi0 = simTrackParam.getPhi();
	  double d0 = simTrackParam.getDZero();
	  double z0 = simTrackParam.getZZero();
	  double tanl = simTrackParam.getTanLambda();
	  double pt = calculateTansverseMomentumFromOmega(omega);
	  float radius = 1/omega;
	  simRadius->Fill(pt);
	  simPhi0->Fill(phi0);
	  simD0->Fill(d0);
	  simTanL->Fill(tanl);
	  simZ0->Fill(z0);
	  if( 0.5 < fabs(phi0) && fabs(phi0) <2.5 )
	    {
	      simRadiusWithCuts->Fill(pt);
	      if(pt >= 19.)
		{
		  simD0WithCuts->Fill(d0);
		  simTanLWithCuts->Fill(tanl);
		  simZ0WithCuts->Fill(z0);
		}
	    }
	  if(pt >= 19.)
	    {
	      simPhi0WithCuts->Fill(phi0);
	    }
	  
	  
	  if(radius > yDetRange)
	    {
	      //get hits on sim track to check which should be kept
	      vector<basicHit> simHits = simtracks.at(t)->getHitsOnTrack();
	      map<double,int> yPosInvestigated;
	      vector<basicHit> hitsForTrackFindingOnCurrentTrack;
	      for(unsigned int s = 0; s<simHits.size(); s++)
		{
		  double currentHitY = simHits.at(s).getY();
		  //find all hit with current y hit position
		  basicHit* hitToBeAdded = new basicHit(1e40,1e40,1e40);
		  if(yPosInvestigated.find(currentHitY) == yPosInvestigated.end())
		    {
		      //cout<<"Hits with y = "<<currentHitY<<endl;
		      
		      for(unsigned int s1 = s; s1< simHits.size(); s1++)
			{
			  if( fabs(simHits.at(s1).getY() - currentHitY) < 1e-10)
			    {
			      //simHits.at(s1).print();
			      if(fabs(simHits.at(s1).getX())<fabs(hitToBeAdded->getX()))
				{
				  hitToBeAdded = new basicHit(simHits.at(s1));
				}
			    }
			  yPosInvestigated.insert(make_pair(currentHitY,1));			}
		    
		      
		      //hitToBeAdded->print();
		      hitsForTrackFinding.push_back(*hitToBeAdded);
		      hitsForTrackFindingOnCurrentTrack.push_back(*hitToBeAdded);
		      delete hitToBeAdded;	
		    }
		    
		}//for(unsigned int s = 0; s<simHits.size(); s++)
	      //create a new TrackFinderTrack
	      TrackFinderTrack tmpTrack(simTrackParam , hitsForTrackFindingOnCurrentTrack);
	      simTracksHitsRemoved.push_back(tmpTrack);
	      
	    }//if(radius > yDetRange)
	  else
	    {
	      simTracksHitsRemoved.push_back(*simtracks.at(t));
	    }
	}//for(unsigned int t = 0; t<simtracks.size(); t++)
      
      
      //now start reconstruction
      
      //straight lines
      if(trackType == "sl" || trackType == "all")
	{
	  HoughTrafoTrackFinder* slTrackFinder = new HoughTrafoTrackFinder();
	  slTrackFinder->setFinderParameter(*slFinderParameter); 
	  slTrackFinder->setInitialHits(hitsForTrackFinding);
	  bool slfound = slTrackFinder->find();
      
	  if(slfound)
	    {
	      //get reco tracks
	      vector<TrackFinderTrack> foundTracks = slTrackFinder->getTracks();
	      cout<<"SL: Number of found tracks: "<<foundTracks.size()<<"/"<<simTracksHitsRemoved.size()<<endl;
	      //compare sim tracks with reco tracks
	      for(unsigned int s = 0; s<simTracksHitsRemoved.size(); s++)
		{
		  TrackFinderTrack simTrack = simTracksHitsRemoved.at(s);
		  TrackParameterFull simTrackParam = simTrack.getTrackParameter();
		  
		  double omega = simTrackParam.getOmega();
		  double phi0 = simTrackParam.getPhi();
		  double d0 = simTrackParam.getDZero();
		  double z0 = simTrackParam.getZZero();
		  double tanl = simTrackParam.getTanLambda();
		  //		float radius = 1/omega;
		  double pt = calculateTansverseMomentumFromOmega(omega);
		  cout<<"Radius and pt: "<<1/omega<<" "<<pt<<endl;
		  
		  for(unsigned int r = 0; r<foundTracks.size(); r++)
		    {
		      TrackFinderTrack recoTrack = foundTracks[r];
		      bool trackcorrect = CompareTracks(&simTrack, &recoTrack);
		      
		      if(trackcorrect)
			{
			  if( 0.5 < fabs(phi0) && fabs(phi0) <2.5 )
			    {
			      slRecoRadius->Fill(pt);
			      if(pt >= 19.)
				{
				  slFoundD0->Fill(d0);
				  slFoundTanL->Fill(tanl);
				  slFoundZ0->Fill(z0);
				}
			    }
			  if(pt >= 19.)
			    {
			      slFoundPhi0->Fill(phi0);
			    }
			  break;
			}
		    }//for(unsigned int r = 0; r<foundTracks.size(); r++)    
		}//for(unsigned int s = 0; s<simTracksHitsRemoved.size(); s++)
	    }//if(slfound)
	  cout<<"Straight line is done"<<endl;
	  delete slTrackFinder;	
	}//if(trackType == "sl")


      //circles without vertex constraint
      if(trackType == "h" || trackType == "all")
	{
	  HoughTrafoTrackFinder* hTrackFinder = new HoughTrafoTrackFinder();
	  hTrackFinder->setFinderParameter(*hFinderParameter); 
	  hTrackFinder->setInitialHits(hitsForTrackFinding);
	  bool hfound = hTrackFinder->find();
	  
	  if(hfound)
	    {
	      //get reco tracks
	      vector<TrackFinderTrack> foundTracks = hTrackFinder->getTracks();
	      cout<<"H: Number of found tracks: "<<foundTracks.size()<<"/"<<simTracksHitsRemoved.size()<<endl;
	      //compare sim tracks with reco tracks
	      for(unsigned int s = 0; s<simTracksHitsRemoved.size(); s++)
		{
		  TrackFinderTrack simTrack = simTracksHitsRemoved.at(s);
		  TrackParameterFull simTrackParam = simTrack.getTrackParameter();
		  
		  double omega = simTrackParam.getOmega();
		  double phi0 = simTrackParam.getPhi();
		  double d0 = simTrackParam.getDZero();
		  double z0 = simTrackParam.getZZero();
		  double tanl = simTrackParam.getTanLambda();
		  
		  double pt = calculateTansverseMomentumFromOmega(omega);
		  //		float radius = 1/omega;
	      
		  for(unsigned int r = 0; r<foundTracks.size(); r++)
		    {
		      TrackFinderTrack recoTrack = foundTracks[r];
		      
		      bool trackcorrect = CompareTracks(&simTrack, &recoTrack);
		  
		      if(trackcorrect)
			{
			  hRecoRadius->Fill(pt);
			  hFoundPhi0->Fill(phi0);
			  hFoundD0->Fill(d0);
			  hFoundTanL->Fill(tanl);
			  hFoundZ0->Fill(z0);
			  break;
			}
		    }//for(unsigned int r = 0; r<foundTracks.size(); r++)    
		}//for(unsigned int s = 0; s<simTracksHitsRemoved.size(); s++)
	    }//if(hfound)
	  cout<<"helix is done"<<endl;
	  delete hTrackFinder;
	}//if(trackType == "h")



      //Something is wrong in pathfinder, maybe try most up to date version, comment it out for now.
      if(trackType == "hv" || trackType == "all")
	{
	  //circle with vertex constraint
	  HoughTrafoTrackFinder* hvTrackFinder = new HoughTrafoTrackFinder();
	  
	  //use one of the hits as vertex and remove that hit from the hit vector
	  pair<double, double> vertex( (allhits.at(allhits.size()-1)).getX(), 
				       (allhits.at(allhits.size()-1)).getY());
	  hvFinderParameter -> setVertex(vertex);
	  allhits.pop_back();
	  
	  hvTrackFinder->setFinderParameter(*hvFinderParameter); 
	  hvTrackFinder->setInitialHits(hitsForTrackFinding);
	  bool hvfound = hvTrackFinder->find();
	  
	  if(hvfound)
	    {
	      //get reco tracks
	      vector<TrackFinderTrack> foundTracks = hvTrackFinder->getTracks();
	      cout<<"HV: Number of found tracks: "<<foundTracks.size()<<"/"<<simTracksHitsRemoved.size()<<endl;

	      //compare sim tracks with reco tracks
	      for(unsigned int s = 0; s<simTracksHitsRemoved.size(); s++)
		{
		  TrackFinderTrack simTrack = simTracksHitsRemoved.at(s);
		  TrackParameterFull simTrackParam = simTrack.getTrackParameter();
	      
		  double omega = simTrackParam.getOmega();
		  double phi0 = simTrackParam.getPhi();
		  double d0 = simTrackParam.getDZero();
		  double z0 = simTrackParam.getZZero();
		  double tanl = simTrackParam.getTanLambda();
	      
		  double pt = calculateTansverseMomentumFromOmega(omega);
		  //		float radius = 1/omega;
		  
		  for(unsigned int r = 0; r<foundTracks.size(); r++)
		    {
		      TrackFinderTrack recoTrack = foundTracks[r];
		  
		      bool trackcorrect = CompareTracks(&simTrack, &recoTrack);
		  
		      if(trackcorrect)
			{
			  hvRecoRadius->Fill(pt);
			  hvFoundPhi0->Fill(phi0);
			  hvFoundD0->Fill(d0);
			  hvFoundTanL->Fill(tanl);
			  hvFoundZ0->Fill(z0);
			  break;
			}
		    }//for(unsigned int r = 0; r<foundTracks.size(); r++)    
		}//for(unsigned int s = 0; s<simTracksHitsRemoved.size(); s++)
	    }//if(hvfound)
	  cout<<"helix with vertex is done"<<endl;
	  delete hvTrackFinder;	  
	}//if(trackType == "hv")
      
      //clean up after each event
      simtracks.clear();
      simTracksHitsRemoved.clear();
      allhits.clear();
      
    }//for(unsigned int e = 0; e<nevents; e++)
  
  cout<<"Simulation and Reconstruction is complete"<<endl;
  
    
  cout<<"test 1"<<endl;

  //write output to root file
  TFile* outputFile = new TFile("PathfinderEfficiencyTestResults.root","RECREATE");

  cout<<"test 2"<<endl;  
  //efficiency from lates reconstruction
  TGraphAsymmErrors* slEfficiency = createEfficiencyGraph(simRadiusWithCuts, slRecoRadius, kRed+1, 20, "slEfficiency", "Straight Line with cut on #phi_{0}; p_{T} in GeV; Efficiecny");
  cout<<"test 3"<<endl;
  TGraphAsymmErrors* hEfficiency = createEfficiencyGraph(simRadius, hRecoRadius, kBlue+1, 21, "hEfficiency","Helix; p_{T} in GeV; Efficiency");
  cout<<"test 4"<<endl;
  TGraphAsymmErrors* hvEfficiency = createEfficiencyGraph(simRadius, hvRecoRadius, kGreen+1, 22, "hvEfficiency","Helix with Vertex; p_{T} in GeV; Efficiency");
  cout<<"test 5"<<endl;
  //parameter scan
  TGraphAsymmErrors* slPhi0Efficiency = createEfficiencyGraph(simPhi0WithCuts, slFoundPhi0, kRed+1, 20, "slPhi0Efficiency","Straight Line with cut p_{T}; #phi_{0} in rad; Efficiency");
  cout<<"test 6"<<endl;
  TGraphAsymmErrors* slD0Efficiency = createEfficiencyGraph(simD0WithCuts, slFoundD0, kRed+1, 20, "slD0Efficiency","Straight Line with cut on p_{T} and #phi_{0}; d_{0} in mm; Efficiency");
  TGraphAsymmErrors* slTanLEfficiency = createEfficiencyGraph(simTanLWithCuts, slFoundTanL, kRed+1, 20, "slTanLEfficiency","Straight Line with cut on p_{T} and #phi_{0}; tan #lambda; Efficiency");
  TGraphAsymmErrors* slZ0Efficiency = createEfficiencyGraph(simZ0WithCuts, slFoundZ0, kRed+1, 20, "slZ0Efficiency","Straight Line with cut on p_{T} and #phi_{0}; z_{0} in mm; Efficiency");
  
  TGraphAsymmErrors* hPhi0Efficiency = createEfficiencyGraph(simPhi0, hFoundPhi0, kBlue+1, 21, "hPhi0Efficiency","Helix; #phi_{0} in rad; Efficiency");
  TGraphAsymmErrors* hD0Efficiency = createEfficiencyGraph(simD0, hFoundD0, kBlue+1, 21, "hD0Efficiency","Helix; d_{0} in mm; Efficiency");
  TGraphAsymmErrors* hTanLEfficiency = createEfficiencyGraph(simTanL, hFoundTanL, kBlue+1, 21, "hTanLEfficiency","Helix; tan #lambda; Efficiency");
  TGraphAsymmErrors* hZ0Efficiency = createEfficiencyGraph(simZ0, hFoundZ0, kBlue+1, 21, "hZ0Efficiency","Helix; z_{0} in mm; Efficiency");
    
  TGraphAsymmErrors* hvPhi0Efficiency = createEfficiencyGraph(simPhi0, hvFoundPhi0, kGreen+1, 22, "hvPhi0Efficiency","Helix with Vertex; #phi_{0} in rad; Efficiency");
  TGraphAsymmErrors* hvD0Efficiency = createEfficiencyGraph(simD0, hvFoundD0, kGreen+1, 22, "hvD0Efficiency","Helix with Vertex; d_{0} in mm; Efficiency");
  TGraphAsymmErrors* hvTanLEfficiency = createEfficiencyGraph(simTanL, hvFoundTanL, kGreen+1, 22, "hvTanLEfficiency","Helix with Vertex; tan #lambda; Efficiency");
  TGraphAsymmErrors* hvZ0Efficiency = createEfficiencyGraph(simZ0, hvFoundZ0, kGreen+1, 22, "hvZ0Efficiency","Helix with Vertex; z_{0} in mm; Efficiency");


  //nominal Efficiencies
  TGraphAsymmErrors* nomSLEfficiency = createNominalEfficiencyGraph(nomGraphValuesSLEfficiency(), kRed-10, 20,"nomSLEfficiency","Straight Line (nominal); p_{T} in GeV; Efficiency");
  TGraphAsymmErrors* nomHEfficiency = createNominalEfficiencyGraph(nomGraphValuesHEfficiency(), kBlue-10, 21,"nomHEfficiency","Helix (nominal); p_{T} in GeV; Efficiency");
  TGraphAsymmErrors* nomHVEfficiency = createNominalEfficiencyGraph(nomGraphValuesHVEfficiency(), kGreen-10, 22,"nomSLEfficiency","Helix with Vertex (nominal); p_{T} in GeV; Efficiency");

  TGraphAsymmErrors* nomSLD0Efficiency = createNominalEfficiencyGraph(nomGraphValuesSLD0Efficiency(), kRed-10, 20,"nomSLEfficiency","Straight Line (nominal); d_{0} in mm; Efficiency");
  TGraphAsymmErrors* nomHD0Efficiency = createNominalEfficiencyGraph(nomGraphValuesHD0Efficiency(), kBlue-10, 21,"nomHEfficiency","Helix (nominal); d_{0} in mm; Efficiency");
  TGraphAsymmErrors* nomHVD0Efficiency = createNominalEfficiencyGraph(nomGraphValuesHVD0Efficiency(), kGreen-10, 22,"nomSLEfficiency","Helix with Vertex (nominal); d_{0} in mm; Efficiency");

  TGraphAsymmErrors* nomSLPhi0Efficiency = createNominalEfficiencyGraph(nomGraphValuesSLPhi0Efficiency(), kRed-10, 20,"nomSLEfficiency","Straight Line (nominal); #phi_{0} in rad; Efficiency");
  TGraphAsymmErrors* nomHPhi0Efficiency = createNominalEfficiencyGraph(nomGraphValuesHPhi0Efficiency(), kBlue-10, 21,"nomHEfficiency","Helix (nominal); #phi_{0} in rad; Efficiency");
  TGraphAsymmErrors* nomHVPhi0Efficiency = createNominalEfficiencyGraph(nomGraphValuesHVPhi0Efficiency(), kGreen-10, 22,"nomSLEfficiency","Helix with Vertex (nominal); #phi_{0} in rad; Efficiency");

  TGraphAsymmErrors* nomSLZ0Efficiency = createNominalEfficiencyGraph(nomGraphValuesSLZ0Efficiency(), kRed-10, 20,"nomSLEfficiency","Straight Line (nominal); z_{0} in mm; Efficiency");
  TGraphAsymmErrors* nomHZ0Efficiency = createNominalEfficiencyGraph(nomGraphValuesHZ0Efficiency(), kBlue-10, 21,"nomHEfficiency","Helix (nominal); z_{0} in mm; Efficiency");
  TGraphAsymmErrors* nomHVZ0Efficiency = createNominalEfficiencyGraph(nomGraphValuesHVZ0Efficiency(), kGreen-10, 22,"nomSLEfficiency","Helix with Vertex (nominal); z_{0} in mm; Efficiency");

  TGraphAsymmErrors* nomSLTanLEfficiency = createNominalEfficiencyGraph(nomGraphValuesSLTanLEfficiency(), kRed-10, 20,"nomSLEfficiency","Straight Line (nominal); tan #lambda; Efficiency");
  TGraphAsymmErrors* nomHTanLEfficiency = createNominalEfficiencyGraph(nomGraphValuesHTanLEfficiency(), kBlue-10, 21,"nomHEfficiency","Helix (nominal); tan #lambda; Efficiency");
  TGraphAsymmErrors* nomHVTanLEfficiency = createNominalEfficiencyGraph(nomGraphValuesHVTanLEfficiency(), kGreen-10, 22,"nomSLEfficiency","Helix with Vertex (nominal); tan #lambda; Efficiency");
  
  TCanvas* ptEfficiencyCanvas = createEfficiencyCanvas(slEfficiency, nomSLEfficiency, hEfficiency, nomHEfficiency, hvEfficiency, nomHVEfficiency, "ptEfficiencyCanvas", "ptEfficiencyCanvas");
  ptEfficiencyCanvas->Write();
  TCanvas* phi0EfficiencyCanvas = createEfficiencyCanvas(slPhi0Efficiency, nomSLPhi0Efficiency, hPhi0Efficiency, nomHPhi0Efficiency, hvPhi0Efficiency, nomHVPhi0Efficiency, "phi0EfficiencyCanvas", "phi0EfficiencyCanvas");
  phi0EfficiencyCanvas->Write();
  TCanvas* d0EfficiencyCanvas = createEfficiencyCanvas(slD0Efficiency, nomSLD0Efficiency, hD0Efficiency, nomHD0Efficiency, hvD0Efficiency, nomHVD0Efficiency, "d0EfficiencyCanvas", "d0EfficiencyCanvas");
  d0EfficiencyCanvas->Write();
  TCanvas* z0EfficiencyCanvas = createEfficiencyCanvas(slZ0Efficiency, nomSLZ0Efficiency, hZ0Efficiency, nomHZ0Efficiency, hvZ0Efficiency, nomHVZ0Efficiency, "z0EfficiencyCanvas", "z0EfficiencyCanvas");
  z0EfficiencyCanvas->Write();
  TCanvas* tanlEfficiencyCanvas = createEfficiencyCanvas(slTanLEfficiency, nomSLTanLEfficiency, hTanLEfficiency, nomHTanLEfficiency, hvTanLEfficiency, nomHVTanLEfficiency, "tanlEfficiencyCanvas", "tanlEfficiencyCanvas");
  tanlEfficiencyCanvas->Write();
  
  
  outputFile->Write();
  outputFile->Close();
   

  //clean up at the end
  delete TrackParameterRanges;
  delete EventType;
  delete DetType;
  delete TrackGen;
  delete slFinderParameter;
  delete hFinderParameter;
  delete hvFinderParameter;

  return 0;
}
