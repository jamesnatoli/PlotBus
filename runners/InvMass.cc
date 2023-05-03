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
#include "/Users/jamesnatoli/KSTATE/Research/Wto3pi/Plotting/SimplePlot.cc"

int main(int argc, char *argv[]) {

  std::string era = "Wto3pi_2018_cont2";
  PlotBus* plotbus = new PlotBus( 2018);
  plotbus->mainpath = "~/KState/Research/Wto3pi/ROOT/skims/" + era;
  plotbus->era  = era;

  plotbus->filepath += "Tuning";
  plotbus->filename = "InvMass_StartingPoint";
  plotbus->variable = "PionTriplet_MassInv";
  plotbus->title    = "Inv Mass";

  // Probably just hard code this now?
  plotbus->addCuts = " (1) ";
  plotbus->addCuts += " && (PionTriplet_pt > 40)";
  // plotbus->addCuts += " && (max(max(PionTriplet_dR_12, PionTriplet_dR_13), PionTriplet_dR_23) < 2.4)";

  // Ok, try a B-jet veto?
  std::string bjetveto = "0.5";
  // plotbus->deepTauVsEl = 15;
  // plotbus->bjetVeto = true;
  // plotbus->addCuts += " && (Sum$( (Jet_btagDeepB[ CleanJet_jetIdx] > "+bjetveto+") && (CleanJet_pt > 20) && (abs(CleanJet_eta) < 2.5)) == 0)";
  // plotbus->addCuts += " && (PionTriplet_dphi_12 < 2.4)";
  // plotbus->addCuts += " && (PionTriplet_dphi_23 < 2.4)";
  
  plotbus->Dxy = 100.0;
  plotbus->Dz  = 100.0;

  /*
  plotbus->processes  = {"ST_Top", "ST_TopUp", "ST_TopDown"};
  // plotbus->processes  = {"ST_AntiTop", "ST_AntiTopUp", "ST_AntiTopDown"};
  plotbus->weights = { {"ST_Top",     plotbus->MCweights["ST"]},
		       {"ST_TopUp",   plotbus->MCweights["ST"]},
		       {"ST_TopDown", plotbus->MCweights["ST"]},
		       {"ST_AntiTop",     plotbus->MCweights["ST"]},
		       {"ST_AntiTopUp",   plotbus->MCweights["ST"]},
		       {"ST_AntiTopDown", plotbus->MCweights["ST"]}
  };
  */

  // plotbus->manualCutString = "( (PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 0) && (PionTriplet_LowestDeepTauVsMu >= 0) && (PionTriplet_LowestDeepTauVsJet >= 0) && (PionTriplet_pion3_iso >= 0) )) && Trigger_ditau && !LeptonVeto && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (abs(PionTriplet_charge) == 1) && (PionTriplet_LowestDeepTauVsEl >= 0) && (PionTriplet_LowestDeepTauVsMu >= 0) && (PionTriplet_LowestDeepTauVsJet >= 0) && (PionTriplet_pion3_iso >= 0))";
  
  plotbus->nbins      = 35;
  plotbus->lowbin     = 0;
  plotbus->highbin    = 350;
  plotbus->chargereq  = 1;
  plotbus->SignalScale = 6;
  
  plotbus->logy       = false;
  plotbus->saveHists  = true;
  plotbus->plotSignal = true;
  plotbus->plotData   = false;
  plotbus->stack      = true;
  plotbus->overflow   = false;
  plotbus->fillHists  = true;
    
  plotbus->verbosity = 0;

  // Now Run
  SimplePlot( plotbus);    
}


