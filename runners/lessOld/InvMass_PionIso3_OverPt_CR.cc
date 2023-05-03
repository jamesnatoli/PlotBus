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

#include "/Users/jamesnatoli/KSTATE/Research/Wto3pi/Plotting/TryPlot.cc"

using namespace std;

int main(int argc, char *argv[]) {
  // make this an object and pass it...
  int year = 2018;
  int nbins = 40;
  double lowbin = 0;
  double highbin = 400;
  string variable = "PionTriplet_MassInv";

  vector<string> bkgs = {};
  vector<float> analyzeCuts = {};
  bool analyzeAbove = false;
  // vector<float> analyzeCuts = { 0.005, 0.010, 0.015};

  string filename = "SignalSelection_InvMass_regionB_Pion3Iso";
  // string moreCuts = "(PionTriplet_pt>40)&&((PionTriplet_pion3_iso / PionTriplet_pion3_pt)>=0.01)";

  string moreCuts = "(PionTriplet_pt>40)&&(((IsoTrack_pfRelIso03_all[PionTriplet_FSpions[2+3*(MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))]]) / (IsoTrack_pt[PionTriplet_FSpions[2+3*(MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))]])) >= 0.01)";
  
  bool logy = false;
  
  return TryPlot( filename, nbins, lowbin, highbin, variable,
		  analyzeCuts, analyzeAbove,
		  moreCuts, logy);
}


