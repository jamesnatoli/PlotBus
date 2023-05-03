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
// #include "/Users/jamesnatoli/KSTATE/Research/Wto3pi/Plotting/TryPlot.cc"
#include "/Users/jamesnatoli/KSTATE/Research/Wto3pi/Plotting/TryPlot_obj.cc"


int main(int argc, char *argv[]) {
  // make this an object and pass it.

  PlotBus* plotbus = new PlotBus();

  plotbus->filename = "Tau_genPartFlav_DeepJetMed_charge1";
  plotbus->variable = "Tau_genPartFlav";
  plotbus->title    = plotbus->filename;
  
  plotbus->nbins    = 6;
  plotbus->lowbin   = -0.5;
  plotbus->highbin  = 5.5;
  plotbus->logy     = false;
  plotbus->chargereq = 1;
  // plotbus->addCuts = "(PionTriplet_pt>40) && (PionTriplet_LowestDeepTauVsJet >= 31)";
  plotbus->addCuts = "(PionTriplet_LowestDeepTauVsJet >= 31)";

  plotbus->bkgsToPlot = {"DY"};
  // plotbus->analyzeCuts = { 2.0, 2.5, 3.0};

  TryPlot_obj( plotbus);  
  
  // plotbus->variable = "((IsoTrack_pfRelIso03_all[PionTriplet_FSpions[2+3*(MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))]]) / (IsoTrack_pt[PionTriplet_FSpions[2+3*(MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))]]))";

}


