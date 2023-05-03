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

using namespace std;

int main(int argc, char *argv[]) {
  // make this an object and pass it...
  int year = 2018;
  string filename = "SignalSelection_InvMass_regionA_DeepTau";
  int nbins = 40;
  double lowbin = 0;
  double highbin = 400;
  string variable = "PionTriplet_MassInv";

  vector<string> bkgs = {};
  vector<float> analyzeCuts = {};
  bool analyzeAbove = false;
  // vector<float> analyzeCuts = { 0.005, 0.010, 0.015};

  string moreCuts = "(PionTriplet_pt>40)&&(PionTriplet_LowestDeepTauVsJet>=31)";
  bool logy = false;
  
  return TryPlot( filename, nbins, lowbin, highbin, variable,
		  analyzeCuts, analyzeAbove,
		  moreCuts, logy);
}


