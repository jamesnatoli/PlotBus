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
  
  plotbus->filename = "Jet_btagDeepB";
  plotbus->variable = "Jet_btagDeepB[CleanJet_jetIdx]";
  plotbus->title    = "bjet Score";

  // Probably just hard code this now?
  plotbus->addCuts = "(PionTriplet_pt>40)";

  // Ok, try a B-jet veto?
  std::string bjetveto = "0.5";
  // plotbus->bjetVeto = true;
  plotbus->addCuts += " && (CleanJet_pt > 20) && (abs(CleanJet_eta) < 2.5)";
  // plotbus->addCuts += " && (Sum$( (Jet_btagDeepB[ CleanJet_jetIdx] > "+bjetveto+") && (CleanJet_pt > 20) && (abs(CleanJet_eta) < 2.5)) == 0)";
  
  plotbus->Dxy = 0.01;
  plotbus->Dz  = 0.01;
    
  plotbus->nbins      = 25;
  plotbus->lowbin     = -2;
  plotbus->highbin    = 2;
  plotbus->chargereq  = 1;
  plotbus->SignalScale = 6;
  
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


