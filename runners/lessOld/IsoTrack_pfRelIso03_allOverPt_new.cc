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
#include "/Users/jamesnatoli/KSTATE/Research/Wto3pi/Plotting/TryPlot_obj.cc"

using namespace std;

int main(int argc, char *argv[]) {
  // make this an object and pass it...
  int year = 2018;
  string filename = "IsoTrack_pfRelIso03_allOverPt_new";
  int nbins = 250;
  double lowbin = 0;
  double highbin = 0.25;
  // string variable = "IsoTrack_pfRelIso03_all / IsoTrack_pt";
  string variable = "((IsoTrack_pfRelIso03_all[PionTriplet_FSpions[2+3*(MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))]]) / (IsoTrack_pt[PionTriplet_FSpions[2+3*(MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))]]))";

  vector<string> bkgs = {};
  vector<float> analyzeCuts = { 0.005, 0.010, 0.015};
  bool analyzeAbove = true;

  string moreCuts = "(PionTriplet_pt>40)";
  bool logy = true;

  PlotBus plotbus = new PlotBus();
  TryPlot_obj( plotbus);
  
  return TryPlot( filename, nbins, lowbin, highbin, variable,
		  analyzeCuts, analyzeAbove,
		  moreCuts, logy);
}


