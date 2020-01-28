#include "RootFileWriter.h"
#include <iostream>

using namespace std;
using namespace pathfinder;


RootFileWriter::RootFileWriter() :
    theta(0.),
    dzero(0.),
    omega(0.),
    binindex(0),
    bintheta(0),
    bindzero(0),
    binomega(0),
    binradius(0),
    nentries(0),
    nradius(0)
{
    HoughTree = 0;
    RadiusTree = 0;
}


void RootFileWriter::setTreeBranches()
{
    HoughTree = new TTree("HoughTree", "HoughTree");
    HoughTree->Branch("thetabin", &bintheta, "bintheta/I");
    //  HoughTree->GetBranch("thetabin")->SetAutoDelete(kTRUE);
    HoughTree->Branch("dzerobin", &bindzero, "bindzero/I");
    //HoughTree->GetBranch("dzerobin")->SetAutoDelete(kTRUE);
    HoughTree->Branch("omegabin", &binomega, "binomega/I");
    //HoughTree->GetBranch("omegabin")->SetAutoDelete(kTRUE);
    HoughTree->Branch("nentries", &nentries, "nentries/I");
    //HoughTree->GetBranch("nentries")->SetAutoDelete(kTRUE);

    RadiusTree = new TTree("RadiusTree", "RadiusTree");
    RadiusTree->Branch("radiusbin", &binradius, "binradius/I");
    RadiusTree->Branch("nradius", &nradius, "nradius/I");
}

void RootFileWriter::fillRootTree(map<int, unsigned int>* HoughMap)
{
    map<int, unsigned int>::iterator mapIter;
    for(mapIter = HoughMap->begin(); mapIter != HoughMap->end(); ++mapIter)
    {
        binindex = (*mapIter).first;
        pair<int, int> binpair = IntToBinConverter2D(binindex);
        bintheta = binpair.first;
        bindzero = binpair.second;
        binomega = 0;
        //      theta=((*mapIter).first).first;
        //  dzero=((*mapIter).first).second;
        //  omega = 0.;
        nentries = (*mapIter).second;
        HoughTree->Fill();
    }
}


void RootFileWriter::fillRootTree(map<int, unsigned int>* HoughMap, map<int, unsigned int>* RadiusMap)
{
    map<int, unsigned int>::iterator mapIter;
    for(mapIter = HoughMap->begin(); mapIter != HoughMap->end(); ++mapIter)
    {
        binindex = (*mapIter).first;
        pair<int, int> binpair = IntToBinConverter2D(binindex);
        bintheta = binpair.first;
        bindzero = binpair.second;
        binomega = 0;
        //      theta=((*mapIter).first).first;
        //  dzero=((*mapIter).first).second;
        //  omega = 0.;
        nentries = (*mapIter).second;
        HoughTree->Fill();
    }

    map<int, unsigned int>::iterator mapIter2;
    for(mapIter2 = RadiusMap->begin(); mapIter2 != RadiusMap->end(); ++mapIter2)
    {
        binindex = (*mapIter2).first;
        binradius = binindex;
        nradius = (*mapIter2).second;
        RadiusTree->Fill();
    }

}

void RootFileWriter::fillRootTree(std::vector<std::vector<unsigned int>* > theVectorOfVectors)
{
    //loop over vector of vectors
    for(vector<vector<unsigned int>*>::const_iterator thetaIterator = theVectorOfVectors.begin(),
            thetaStart = theVectorOfVectors.begin(),
            thetaEnd = theVectorOfVectors.end();
            thetaIterator < thetaEnd; ++thetaIterator)
    {
        unsigned int thetaBin = thetaIterator - thetaStart;
        vector<unsigned int>* theCurrentThetaVector = *thetaIterator;
        unsigned int _numberOfBins = theCurrentThetaVector->size();
        for(unsigned int valueBin = 0; valueBin < _numberOfBins; ++valueBin)
        {

            bintheta = thetaBin;//for root tree theta
            bindzero = valueBin;//for root tree d
            unsigned int currentNumber = (*theCurrentThetaVector)[valueBin];
            binomega = 0;//for root tree omega
            nentries = currentNumber;//for root tree number of entries in current bin
            HoughTree->Fill();
        }
    }
}

void RootFileWriter::fillRootHistos(std::vector<TrackFinderTrack*>)
{

}

bool RootFileWriter::writeRootFile(map<int, unsigned int>* HoughMap, string filename)
{
    TFile *file = new TFile(filename.c_str(), "create");

    bool fileDoesNotExist = file->IsOpen();

    if(file->IsOpen()) //if file does not exist yet
    {
        setTreeBranches();
        fillRootTree(HoughMap);


        /*
        CREATE:   create a new file and open it for writing,
        if the file already exists the file is
        not opened.
        */
        cout << "HoughTree Test" << endl;
        RadiusTree->Print();
        HoughTree->Print();


        int radiuswrite = RadiusTree->Write();
        cout << "rw: " << radiuswrite << endl;
        int houghwrite = HoughTree->Write();
        cout << "hw: " << houghwrite << endl;


        cout << "HoughTree Test2" << endl;
        HoughTree->Print();
        RadiusTree->Print();

        file->Close();

    }
    else
    {
        cout << "File already exists. It is not written again." << endl;
    }

    return fileDoesNotExist;
}


bool RootFileWriter::writeRootFile(map<int, unsigned int>* HoughMap, map<int, unsigned int>* RadiusMap,
                                   string filename)
{
    TFile *file = new TFile(filename.c_str(), "create");

    bool fileDoesNotExist = file->IsOpen();

    if(file->IsOpen()) //if file does not exist yet
    {

        setTreeBranches();
        fillRootTree(HoughMap, RadiusMap);


        //  CREATE:   create a new file and open it for writing,
        //          if the file already exists the file is
        //        not opened.

        HoughTree->Write();
        RadiusTree->Write();
        file->Close();

        //    delete file;
    }
    else
    {
        cout << "File already exists. It is not written again." << endl;
    }

    return fileDoesNotExist;
}

bool RootFileWriter::writeRootFile(std::vector<std::vector<unsigned int>* > HoughMap, string filename)
{
    TFile *file = new TFile(filename.c_str(), "create");
    bool fileDoesNotExist = file->IsOpen();

    if(file->IsOpen()) //if file does not exist yet
    {
        setTreeBranches();
        fillRootTree(HoughMap);


        //  CREATE:   create a new file and open it for writing,
        //          if the file already exists the file is
        //        not opened.

        HoughTree->Write();
        RadiusTree->Write();
        file->Close();

        //    delete file;
    }
    else
    {
        cout << "File already exists. It is not written again." << endl;
    }
    return fileDoesNotExist;
}


pair<int, int> RootFileWriter::IntToBinConverter2D(int bin_index)
{
    pair<int, int> binPair;
    int a;
    int b;

    b = (bin_index >> 10) & 1023;
    a = (bin_index >> 20);


    binPair.first = a;
    binPair.second = b;
    /*
    if(_useXY)
      {
        binPair.first = -M_PI + a*2*M_PI/Parameter.getNumberXYThetaBins();
        binPair.second = Parameter.getMinXYDzero() + b*(Parameter.getMaxXYDzero()-Parameter.getMinXYDzero())/
          (double)Parameter.getNumberXYDzeroBins();
      }
    else
      {
        binPair.first = -M_PI + a*2*M_PI/Parameter.getNumberSZThetaBins();
        binPair.second = Parameter.getMinSZDzero() + b*(Parameter.getMaxSZDzero()-Parameter.getMinSZDzero())/
          (double)Parameter.getNumberSZDzeroBins();
      }
    */
    return binPair;
}



