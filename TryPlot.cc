#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TH1.h"
#include "THStack.h"
#include "TLegend.h"
#include "TF1.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <assert.h> 
#include <iomanip>

#include "Analyzers.h"
#include "PlotUtils.h"
#include "PlotBus.cc"

using namespace std;
int TryPlot( PlotBus* pb) {
  // Options

  /*
  string eventcuts = "(HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg) * (Sum$(abs(Lepton_pdgId)==15) == Length$(Lepton_pdgId))";
  string tripletcuts = "(abs(PionTriplet_charge) == 1) * (abs(PionTriplet_pdgId) == 15*15*15) * (PionTriplet_trailingIsTrack) * (PionTriplet_LowestDeepTauVsEl >= 3) * (PionTriplet_LowestDeepTauVsMu >= 15)";
  string selectioncut = "(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, "+tripletcuts+"))";
  
  string moreCuts = "(PionTriplet_pt>40)";
  string addcuts = moreCuts;
  string MCweights = "XSecMCweight * PUweight"; //  * Generator_weight
  string Sigweights = "(XSecMCweight / XSec) * (192900*1e-3) * PUweight";
  
  // string chargereq = "(abs(PionTriplet_charge) == "+pb->GetChargeReq()+")";
  string eventcuts = "(HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg) && (Sum$(abs(Lepton_pdgId)==15) == Length$(Lepton_pdgId))";
  // string deepTau   = "(PionTriplet_LowestDeepTauVsEl >= 0) && (PionTriplet_LowestDeepTauVsMu >= 15)";
  // string tripletcuts = pb->getChargeReqString() + " && " + "(abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack)" + pb->getDeepTauString();
  // string tripletcuts = chargereq+"&&"+"(abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack)";
  // string tripletcuts = "(abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)";
  string tripletcuts = "(abs(PionTriplet_charge) == 3) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)";
  string selectioncut = "(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, "+tripletcuts+"))";
  string Sigweights = "(XSecMCweight / XSec) * (192900*1e-3) * PUweight";
  
  string standardCuts = pb->getStdCutString();
  string addcuts = pb->getAddCuts();
  */

  int year        = pb->year;
  int numbins     = pb->nbins;
  double lowbin   = pb->lowbin;
  double highbin  = pb->highbin;
  string variable = pb->variable;
  string filename = pb->filename;
  bool logy       = pb->logy;
  pb->xtitle = variable;

  std::cout << "Main Path: " << pb->mainpath << std::endl;

  vector<string> signalfiles = pb->signalfiles;
  vector<string> datafiles = pb->datafiles;
  map<string, vector<string>> bkgfiles = pb->bkgfiles;
  
  vector<string> bkgs     = pb->bkgs;
  vector<string> bkgsPlot = pb->bkgsToPlot;

  map<string, string> bkgsParts{{"DY10", "DY"}}; // {"Part of bkg...", "...belonging to this main bkg"}
  for (auto const& bkgpart : bkgsParts){
    // Now DY10 is in bkgs
    bkgs.push_back(bkgpart.first);
  }
  map<string, string> additionalWeights;

  // Get file names
  pb->FillFiles( pb->year, 2);

  cout << "Making chain" << endl;
  TChain datachain("Events");
  TChain signalchain("Events");
  for(string sigfile : pb->signalfiles){
    signalchain.Add((sigfile).c_str());
  }
  pb->SetSignalChain( signalchain.Clone());
  
  for(string datafile : pb->datafiles){
    datachain.Add((datafile).c_str());
  }
  pb->SetDataChain( datachain.Clone());
  
  map<string, TChain> bkgchain;
  for(string bkg : bkgs){
    bkgchain[bkg].SetName("Events");
    for(string bkgfile : pb->bkgfiles[bkg]){
      bkgchain[bkg].Add((bkgfile).c_str());
    }
  }
  // pb->bkgchain = bkgchain;

  string binning = "("+to_string(numbins)+","+to_string(lowbin)+","+to_string(highbin)+")";
  cout << "Plotting variable: " << variable
       << "\n" << endl;
  
  cout << "Standard Cuts: " << endl;
  cout << pb->getStdCutString() << "\n" << std::endl;
  // cout << selectioncut+"&&"+eventcuts+"&&"+tripletcuts << "\n" << endl;

  cout << "Additional Cuts: " << endl;
  cout << pb->getAddCuts() << "\n" << std::endl;
  // cout << addcuts << "\n" << endl;

  cout << "Signal Cut String: " << endl;
  cout << pb->getCutStringSig() << std::endl;
  // cout << "("+Sigweights+")*"+selectioncut+"&&"+eventcuts+"&&"+tripletcuts+"&&"+addcuts << endl;
  // cout << selectioncut+"&&"+eventcuts+"&&"+tripletcuts+"&&"+addcuts << "\n" << endl;

  // cout << "\nMC Cut String: " << endl;
  // cout << pb->getCutStringMC() << std::endl;

  signalchain.Draw((variable+">>signal"+binning).c_str(),
		   pb->getCutStringSig().c_str());
  //("("+Sigweights+")*("+selectioncut+"&&"+eventcuts+"&&"+tripletcuts+"&&"+addcuts + ")").c_str());

  if (pb->plotData) {
    datachain.Draw((variable+">>data"+binning).c_str(),
		   pb->getFullCutString().c_str());
    // (selectioncut+"&&"+eventcuts+"&&"+tripletcuts+"&&"+addcuts).c_str());
  }
    
  int icount = 0;
  string addWeight;
  for(string bkg : bkgs){
    icount++;
    cout << setw(8) << left
	 << bkg+":" << icount << " / " << bkgs.size() << endl;

    // Stitching weights for WJets and DY
    // can probably hide this away
    // if (additionalWeights.find(bkg) != additionalWeights.end()){
    //   addWeight = "("+additionalWeights[bkg]+") * ";
    // } else{
    //   addWeight = "";
    // }
    // 
    // Normal drawing
    int num = bkgchain[bkg].Draw((variable+">>bkg"+bkg+binning).c_str(),
				 // (addWeight+"("+MCweights+")*("+selectioncut+"&&"+eventcuts+"&&"+tripletcuts+"&&"+addcuts+")").c_str());
				 (pb->getCutStringMC( bkg)).c_str());
    if (bkg == "TT") {
      std::cout << "TT Cut String: \n" << pb->getCutStringMC( bkg) << std::endl;
      std::cout << "NEntries: " << num << std::endl;
    }
  }
  
  cout << "\nGetting histograms" << endl;
  TH1F* signalhist;
  TH1F* datahist;
  map<string, TH1F*> bkghists;

  signalhist = (TH1F*)gDirectory->Get("signal");
  
  datahist = (TH1F*)gDirectory->Get("data");
  for (string bkg : bkgs)
    bkghists[bkg] = (TH1F*)gDirectory->Get(("bkg"+bkg).c_str());
  
  // Don't forget to add in the DY10 to DY
  for (auto const& bkgpart : bkgsParts){
    bkghists[bkgpart.second]->Add(bkghists[bkgpart.first], 1);
  }
  
  cout << "Making canvas" << endl;
  makePlot( signalhist, datahist, bkghists, bkgs, pb);
  
  // Analyze Cuts
  for (float cut : pb->analyzeCuts)
    analyze( signalhist, cut);

  return 0;
}


