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

using namespace std;
#include "/Users/jamesnatoli/KSTATE/Research/Wto3pi/Plotting/TryPlot.cc"

int main(int argc, char *argv[]) {
  // make this an object and pass it.

  PlotBus* plotbus = new PlotBus();

  plotbus->filename = "Pion3IsoOverPt";
  plotbus->variable = "(PionTriplet_pion3_iso / PionTriplet_pion3_pt)";
  // plotbus->title    = plotbus->filename;

  // plotbus->addCuts = "(PionTriplet_charge == 3) && ((PionTriplet_LowestDeepTauVsJet >= 7) && ((PionTriplet_pion3_iso / PionTriplet_pion3_pt) < 0.02))";
  // plotbus->addCuts = "(PionTriplet_dR_12 < 2.5) && (PionTriplet_pt<40)";
  // plotbus->addCuts = "(PionTriplet_pt>40) && (PionTriplet_LowestDeepTauVsJet >= 31)";
  // plotbus->addCuts = "(PionTriplet_LowestDeepTauVsJet >= 31)";

  plotbus->title   = plotbus->addCuts;
  
  plotbus->nbins     = 200;
  plotbus->lowbin    = 0;
  plotbus->highbin   = 0.02;
  plotbus->logy      = true;
  plotbus->chargereq = 1;

  plotbus->deepTauVsEl  = 3;
  // plotbus->deepTauVsMu  = 3;
  plotbus->deepTauVsJet = 7;

  plotbus->saveHists = false;

  // plotbus->bkgsToPlot = plotbus->bkgs;
  // plotbus->analyzeCuts = { 2.0, 2.5, 3.0};

  TryPlot( plotbus);  
  
  // plotbus->variable = "((IsoTrack_pfRelIso03_all[PionTriplet_FSpions[2+3*(MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))]]) / (IsoTrack_pt[PionTriplet_FSpions[2+3*(MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))]]))";

}


