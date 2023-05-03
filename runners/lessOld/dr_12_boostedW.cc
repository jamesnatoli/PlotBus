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
  // make this an object and pass it.

  PlotBus* plotbus = new PlotBus();

  plotbus->filename = "dR_12_boostedW";
  plotbus->variable = "PionTriplet_dR_12";
  plotbus->nbins    = 90;
  plotbus->lowbin   = 0;
  plotbus->highbin  = 4.5;
  plotbus->logy     = false;
  plotbus->addCuts = "(PionTriplet_pt>40)";

  // plotbus->bkgs = {};
  plotbus->analyzeCuts = { 2.0, 2.5, 3.0};

  TryPlot_obj( plotbus);  
  
  // plotbus->variable = "((IsoTrack_pfRelIso03_all[PionTriplet_FSpions[2+3*(MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))]]) / (IsoTrack_pt[PionTriplet_FSpions[2+3*(MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))]]))";

}


