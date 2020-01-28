/*
  Root script to make beautiful plots out of the output from the RootFileWriter
  Filenames might need to be changed!!!
  Usage: root -x Produce2DHistoFromTree.C
*/

void Make2DHistosFromRootFileWriterRootTree()
{
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  gROOT->ForceStyle();

  //xy plane hough space

  //filename for xy projection
  TFile *f1 = new TFile("XYHoughMap.root");

  
  TTree *t1a = (TTree*)f1->Get("HoughTree");
  Int_t dzero1, theta1, nentries1a;
  t1a->SetBranchAddress("dzerobin",&dzero1);
  t1a->SetBranchAddress("thetabin",&theta1);
  t1a->SetBranchAddress("nentries",&nentries1a);
  TH2I *hdzerothetaxy = new TH2I("hdzerothetaxy","xy Hough Space; #theta bin; D bin",1000,0,1000,1000,0,1000);
  Int_t nentries1 = (Int_t)t1a->GetEntries();
  for (Int_t i=0; i<nentries1; i++) {
    cout<<i<<" "<<nentries1<<endl;
    t1a->GetEntry(i);
    for(int j = 0; j<nentries1a; j++)
      {
	hdzerothetaxy->Fill(theta1,dzero1);
      }
  }
  TCanvas* c1 = new TCanvas("xyHoughMap","xyHoughMap",1);
  c1->cd();
  hdzerothetaxy->Draw("colz");
  // hdzerothetaxy->Draw("");

  

  //r
  TTree *t1b = (TTree*)f1->Get("RadiusTree");
  Int_t radius1, nentries1b;
  t1b->SetBranchAddress("radiusbin",&radius1);
  t1b->SetBranchAddress("nradius",&nentries1b);
  TH1I *hradiusxy = new TH1I("hradiusxy","xy Hough Space; radius bins; number of entries", 300, 0, 300);
  Int_t nentries11 = (Int_t)t1b->GetEntries();
  for (Int_t i=0; i<nentries11; i++) {
    cout<<i<<" "<<nentries11<<endl;
    t1b->GetEntry(i);
    for(int j = 0; j<nentries1b; j++)
      {
        hradiusxy->Fill(radius1);
      }
  }
  TCanvas* c1b = new TCanvas("xyHoughMap 2","xyHoughMap 2",1);
  c1b->cd();
  hradiusxy->Draw("");


  //sz plane hough space

  //file name for sz projection
  TFile *f2 = new TFile("SZHoughMap.root");

  TTree *t2 = (TTree*)f2->Get("HoughTree");
  Int_t dzero2, theta2, nentries2a;
  t2->SetBranchAddress("dzerobin",&dzero2);
  t2->SetBranchAddress("thetabin",&theta2);
  t2->SetBranchAddress("nentries",&nentries2a);
  TH2I *hdzerothetasz = new TH2I("hdzerothetasz","sz Hough Space; #theta bin; d_{0} bin",1000,0,1000,1000,0,1000);
  Int_t nentries2 = (Int_t)t2->GetEntries();
  for (Int_t i=0; i<nentries2; i++) {
    cout<<i<<" "<<nentries2<<endl;
    t2->GetEntry(i);
    for(int j = 0; j<nentries2a; j++)
      {
	hdzerothetasz->Fill(theta2,dzero2);
      }
  }
  TCanvas* c2 = new TCanvas("szHoughMap","szHoughMap",1);
  c2->cd();
    hdzerothetasz->Draw("colz");
    //  hdzerothetasz->Draw("");
}
