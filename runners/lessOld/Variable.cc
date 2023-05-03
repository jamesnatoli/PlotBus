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
  plotbus->year = 2017;

  plotbus->chargereq   = 1;
  plotbus->SignalScale = 5;
  plotbus->filename  = "InvMass_test";
  plotbus->nbins     = 25;
  plotbus->lowbin    = 0;
  plotbus->highbin   = 400;
  plotbus->variable  = "PionTriplet_MassInv";
  plotbus->title     = plotbus->filename;

  // plotbus->addCuts = "(PionTriplet_dR_12 < 2.5) && (PionTriplet_pt<40)";
  plotbus->addCuts = "(PionTriplet_pt>40)";
  std::string dzcut  = "0.01";
  std::string dxycut = "0.0025";
  // L: 0.1208, M: 0.4168, T:0.7665
  std::string bjetveto = "0.1208";

  // (max( max( PionTriplet_dR_12, PionTriplet_dR_13), PionTriplet_dR_23) < 3.0)
  // plotbus->addCuts += " && (PionTriplet_dR_12 > PionTriplet_dR_13) && (PionTriplet_dR_12 > PionTriplet_dR_23)";
  // plotbus->addCuts += " && (PionTriplet_pion1_dz < "+dzcut+") && (PionTriplet_pion2_dz < "+dzcut+") && (PionTriplet_pion3_dz < "+dzcut+")";
  // plotbus->addCuts += " && (PionTriplet_pion1_dxy < "+dxycut+") && (PionTriplet_pion2_dxy < "+dxycut+") && (PionTriplet_pion3_dxy < "+dxycut+")";
  // plotbus->addCuts += " && (Sum$( (Jet_btagDeepB[ CleanJet_jetIdx] > "+bjetveto+") && (CleanJet_pt > 20) && (abs(CleanJet_eta) < 2.5)) == 0)";
  
  plotbus->logy      = true;
  plotbus->saveHists = false;
  plotbus->AddSigMCtoPlots = true;
  plotbus->plotData = false;
  
  // plotbus->UnsetSignalRegionVars();

  plotbus->bkgsToPlot = {"TT", "DY", "QCD MC"};
  // plotbus->analyzeCuts = { 2.0, 2.5, 3.0};

  TryPlot( plotbus);  
  
  // plotbus->variable = "((IsoTrack_pfRelIso03_all[PionTriplet_FSpions[2+3*(MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))]]) / (IsoTrack_pt[PionTriplet_FSpions[2+3*(MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))]]))";

}


