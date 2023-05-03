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
  string filename = "IsoTrack_pfRelIso03_chgOverPt";
  int nbins = 50;
  double lowbin = 0;
  double highbin = 0.1;
  string variable = "IsoTrack_pfRelIso03_chg";

  string moreCuts = "(PionTriplet_pt>40)";
  bool logy = true;
  
  return TryPlot( filename, nbins, lowbin, highbin, variable, moreCuts, logy);
}


