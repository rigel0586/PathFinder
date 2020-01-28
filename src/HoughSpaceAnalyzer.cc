#include "HoughSpaceAnalyzer.h"
#include "HoughSpacePoint.h"
#include "HoughMapMaximumCandidateFinder.h"

//root
#include "TFile.h"
#include "TPDF.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TEllipse.h"

using namespace std;
using namespace pathfinder;

HoughSpaceAnalyzer::HoughSpaceAnalyzer(map<int, unsigned int> _houghMap,
                                       HoughSpaceBinning _xBinning,
                                       HoughSpaceBinning _yBinning)
    : HoughSpace(_houghMap),
      xBinning(_xBinning),
      yBinning(_yBinning)
{
    SetRootStyle();
    InitializeRootObjects();
}

void HoughSpaceAnalyzer::Analyze()
{
    map<int, unsigned int>::iterator mapIter = HoughSpace.begin();

    for(; mapIter != HoughSpace.end(); mapIter++)
    {
        int currentKey = (*mapIter).first;
        int currentValue = (*mapIter).second;

        HoughSpacePoint* currentHoughSpacePoint = new HoughSpacePoint(currentKey, xBinning, yBinning);

        for(int i = 0; i < currentValue; i++)
        {
            HoughSpaceHistogram->Fill(currentHoughSpacePoint->getTheta(), currentHoughSpacePoint->getD());
            HoughSpaceXHistogram->Fill(currentHoughSpacePoint->getTheta());
            HoughSpaceYHistogram->Fill(currentHoughSpacePoint->getD());
        }

        HoughSpaceKeyValueGraph->SetPoint(HoughSpaceKeyValueGraph->GetN(),
                                          currentKey,
                                          currentValue);

        HoughSpaceValueHistogram->Fill(currentValue);

        delete currentHoughSpacePoint;
    }
}

void HoughSpaceAnalyzer::WriteRootFile(const char* _fileName)
{
    TFile outputFile(_fileName, "recreate");

    list<pair<TObject*, const char*> >::iterator objectIter = RootObjectList.begin();
    for(; objectIter != RootObjectList.end(); objectIter++)
    {
        (*objectIter).first->Write();
    }

    outputFile.Close();
}

void HoughSpaceAnalyzer::WritePdfFile(const char* _fileName)
{
    TPDF* pdfFile = new TPDF(_fileName, 111);
    string outputOpen = pdfFile->GetName();
    outputOpen += "[";

    TCanvas* defaultCanvas = new TCanvas("defaultCanvas", "defaultCanvas", 1200, 800);
    defaultCanvas->Print(outputOpen.c_str());

    list<pair<TObject*, const char*> >::iterator objectIter = RootObjectList.begin();
    for(; objectIter != RootObjectList.end(); objectIter++)
    {
        TCanvas* defaultCanvas2 = new TCanvas(Form("%sCanvas", (*objectIter).first->GetName()),
                                              Form("%sCanvas", (*objectIter).first->GetName()), 1200, 800);
        defaultCanvas2->cd();
        (*objectIter).first->Draw((*objectIter).second);

        if(objectIter == RootObjectList.begin())
        {
            HoughSpaceIntersectionGraph1->SetMarkerStyle(24);
            HoughSpaceIntersectionGraph1->SetMarkerSize(5);
            HoughSpaceIntersectionGraph1->Draw("p");
        }

        defaultCanvas2->Update();
        defaultCanvas2->Print(pdfFile->GetName());
        delete defaultCanvas2;
    }

    string outputClose = pdfFile->GetName();
    outputClose += "]";
    defaultCanvas->Print(outputClose.c_str());

    delete pdfFile;
    delete defaultCanvas;

}

void HoughSpaceAnalyzer::SetRootStyle()
{
    gStyle->SetPalette(1);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetCanvasColor(kWhite);
    gStyle->SetFrameFillColor(kWhite);
    gStyle->SetFrameBorderMode(0);
    gStyle->SetFillColor(kWhite);
    gStyle->SetLegendBorderSize(1);
}

void HoughSpaceAnalyzer::InitializeRootObjects()
{
    HoughSpaceHistogram = new TH2F("HoughSpace", "Hough Space; #theta in rad; d (arbitrary unit); Number of Entries",
                                   xBinning.getNBins() + 2,
                                   xBinning.getLow() - xBinning.getBinWidth(),
                                   xBinning.getHigh() + xBinning.getBinWidth(),
                                   yBinning.getNBins() + 2,
                                   yBinning.getLow() - yBinning.getBinWidth(),
                                   yBinning.getHigh() + yBinning.getBinWidth()
                                  );

    HoughSpaceIntersectionGraph1 = new TGraph();

    HoughSpaceXHistogram = new TH1F("HoughSpaceX", "Hough Space #theta; #theta in rad; Number of Entries",
                                    xBinning.getNBins() + 2,
                                    xBinning.getLow() - xBinning.getBinWidth(),
                                    xBinning.getHigh() + xBinning.getBinWidth()
                                   );

    HoughSpaceYHistogram = new TH1F("HoughSpaceY", "Hough Space d; d (arbitrary unit); Number of Entries",
                                    yBinning.getNBins() + 2,
                                    yBinning.getLow() - yBinning.getBinWidth(),
                                    yBinning.getHigh() + yBinning.getBinWidth()
                                   );

    HoughSpaceKeyValueGraph = new TGraph(HoughSpace.size());
    HoughSpaceKeyValueGraph->SetNameTitle("HoughSpaceKeyValueGraph", "Hough Space Keys and Values; Key; Value");
    HoughSpaceKeyValueGraph->SetMarkerStyle(7);

    HoughSpaceValueHistogram = new TH1I("HoughSpaceValues", "Hough Space Values; Hough Space Value; Number of Entries",
                                        1000,
                                        0, 200);

    FindMaxima();

    CreateRootObjectList();

}

void HoughSpaceAnalyzer::FindMaxima()
{
    FindMaxima1();
}

void HoughSpaceAnalyzer::FindMaxima1()
{
    HoughMapMaximumCandidateFinder HoughSpaceMaximumFinder(HoughSpace, &xBinning, &yBinning, false, false);
    HoughSpaceMaxima = HoughSpaceMaximumFinder.getMaximumCandidates();

    int counter = 0;
    for(unsigned int i = 0; i < HoughSpaceMaxima.size(); i++)
    {
        if(HoughSpaceMaxima.at(i).getFirst() >= xBinning.getLow() && HoughSpaceMaxima.at(i).getFirst() <= xBinning.getHigh())
        {
            HoughSpaceMaxima.at(i).print();
            HoughSpaceIntersectionGraph1->SetPoint(counter, HoughSpaceMaxima.at(i).getFirst(), HoughSpaceMaxima.at(i).getSecond());
            counter++;
        }
    }
}

void HoughSpaceAnalyzer::CreateRootObjectList()
{
    RootObjectList.push_back(make_pair(HoughSpaceHistogram, "colz"));
    RootObjectList.push_back(make_pair(HoughSpaceIntersectionGraph1, "a*"));
    RootObjectList.push_back(make_pair(HoughSpaceXHistogram, ""));
    RootObjectList.push_back(make_pair(HoughSpaceYHistogram, ""));
    RootObjectList.push_back(make_pair(HoughSpaceKeyValueGraph, "ap"));
    RootObjectList.push_back(make_pair(HoughSpaceValueHistogram, ""));
}
