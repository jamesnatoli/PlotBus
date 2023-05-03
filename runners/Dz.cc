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
  
  plotbus->filename = "Pion1_Dz";
  plotbus->variable = "abs(PionTriplet_pion1_dz)";
  plotbus->title    = "Pion1 Dz";

  plotbus->addCuts = "(PionTriplet_pt>40)";
  // plotbus->Dxy = 0.01;
  // plotbus->Dz  = 0.005;
    
  plotbus->nbins      = 60;
  plotbus->lowbin     = 0;
  plotbus->highbin    = 0.06;
  plotbus->chargereq  = 1;
  plotbus->SignalScale = 6;
  
  plotbus->logy       = true;
  plotbus->saveHists  = false;
  plotbus->plotSignal = true;
  plotbus->plotData   = false;
  plotbus->stack      = true;
  
  plotbus->verbosity = 0;
  SimplePlot( plotbus);    
}


