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
  // make this an object and pass it.

  std::string era = "Wto3pi_2018_cont2";
  PlotBus* plotbus = new PlotBus( 2018);
  plotbus->mainpath = "~/KState/Research/Wto3pi/ROOT/skims/" + era;
  plotbus->era  = era;
  
  plotbus->filename = "MaxDeltaR_noWpT";
  plotbus->variable = "max(max(PionTriplet_dR_12, PionTriplet_dR_13), PionTriplet_dR_23)";
  plotbus->title    = "Max(#Delta_{R})";

  // Probably just hard code this now?
  // plotbus->addCuts = "(max(max(PionTriplet_dR_12, PionTriplet_dR_13), PionTriplet_dR_23) < 3.0)";
  plotbus->addCuts = "(PionTriplet_pt>0)";
  // plotbus->addCuts += "(PionTriplet_dphi_12 < 2.4)";
  // plotbus->addCuts += " && (PionTriplet_dphi_23 < 2.4)";

  // Ok, try a B-jet veto?
  std::string bjetveto = "0.5";
  // plotbus->bjetVeto = true;
  // plotbus->addCuts += " && (Sum$( (Jet_btagDeepB[ CleanJet_jetIdx] > "+bjetveto+") && (CleanJet_pt > 20) && (abs(CleanJet_eta) < 2.5)) == 0)";
  
  plotbus->Dxy = 0.025;
  plotbus->Dz  = 0.05;
    
  plotbus->nbins      = 30;
  plotbus->lowbin     = 0;
  plotbus->highbin    = 6;
  plotbus->chargereq  = 1;
  plotbus->SignalScale = 5;
  
  plotbus->logy       = false;
  plotbus->saveHists  = false;
  plotbus->plotSignal = true;
  plotbus->plotData   = false;
  plotbus->stack      = true;
  plotbus->overflow   = true;
  
  plotbus->verbosity = 0;

  // Now Run
  SimplePlot( plotbus);    
}


