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
  
  plotbus->filename = "PuppiMET_pt";
  plotbus->variable = "PuppiMET_pt";
  plotbus->title    = "Puppi MET p_{T}";

  plotbus->addCuts = "(PionTriplet_pt>40)";
  plotbus->Dxy = 0.01;
  plotbus->Dz  = 0.01;
    
  plotbus->nbins      = 24;
  plotbus->lowbin     = 0;
  plotbus->highbin    = 360;
  plotbus->chargereq  = 1;
  plotbus->SignalScale = 6;
  
  plotbus->logy       = false;
  plotbus->saveHists  = false;
  plotbus->plotSignal = true;
  plotbus->plotData   = false;
  plotbus->stack      = true;
  
  plotbus->verbosity = 0;
  SimplePlot( plotbus);    
}


