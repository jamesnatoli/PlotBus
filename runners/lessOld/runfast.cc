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
  PlotBus* plotbus;
  std::string era = "Wto3pi_2018_cont2";
  if (argc < 2) {
    std::cout << "GIVE ME A YEAR" << std::endl;
    return 0;
    plotbus = new PlotBus( 2018);
    plotbus->mainpath = "~/KState/Research/Wto3pi/ROOT/skims/" + era;
    // plotbus->mainpath = "/Volumes/WineCellar/KState/analysis/" + era;
    plotbus->era  = era;
  } else {
    std::cout << "Using year: " << argv[1] << std::endl;
    plotbus = new PlotBus( atoi(argv[1]));
    plotbus->mainpath = "~/KState/Research/Wto3pi/ROOT/skims/" + era;
    plotbus->mainpath = "/Volumes/WineCellar/KState/analysis/" + era;
    plotbus->era  = era;
  }
  
  plotbus->variable = "PionTriplet_MassInv";
  plotbus->verbosity = 0;

  // -1 is Flag for no charge req in cut (using it as region variable)
  plotbus->SignalScale = 6;
  plotbus->plotSignal = false;
  plotbus->plotData = false;
  // plotbus->chargereq = 1;
  // if (plotbus->chargereq == 1)
  //    plotbus->plotDataSR = false;
  // else
  //   plotbus->plotDataSR = true;
  plotbus->filepath += "/random/";

  plotbus->filename = "ST_Top_Compare";

  // plotbus->addCuts = "(PionTriplet_pt>40)";
  // plotbus->addCuts += " && (max( max( PionTriplet_dR_12, PionTriplet_dR_13), PionTriplet_dR_23) < 3.0)";
  // plotbus->addCuts = "(PionTriplet_pt>40) && (PionTriplet_dR_12 < 2.0)";
  // plotbus->addCuts += " && (PionTriplet_pion1_dz < "+dzcut+") && (PionTriplet_pion2_dz < "+dzcut+") && (PionTriplet_pion3_dz < "+dzcut+")";
  // plotbus->addCuts += " && (PionTriplet_pion1_dxy < "+dxycut+") && (PionTriplet_pion2_dxy < "+dxycut+") && (PionTriplet_pion3_dxy < "+dxycut+")";
  // plotbus->addCuts += " && (Sum$( (Jet_btagDeepB[ CleanJet_jetIdx] > "+bjetveto+") && (CleanJet_pt > 20) && (abs(CleanJet_eta) < 2.5)) == 0)";
    
  // plotbus->addCuts = "((PionTriplet_pt>40) && (PionTriplet_LowestDeepTauVsJet >= 31))"; // && (PionTriplet_pion3_iso < 0.5)";
  // plotbus->addCuts = "(PionTriplet_pion3_iso < 0.5)";
  // plotbus->addCuts = "(PionTriplet_pt>40) && (PionTriplet_pion3_iso < 2.0)";
  
  plotbus->nbins     = 80;
  plotbus->lowbin    = 0;
  plotbus->highbin   = 400;
  plotbus->saveHists = true;
  plotbus->bkgs = { "ST_Top",
		    "ST_TopUp",
		    "ST_TopDown",
  };
// plotbus->bkgs = { "ST_AntiTop",
// 		    "ST_AntiTopUp",
// 		    "ST_AntiTopDown"};
  SimplePlot( plotbus);
  
  // plotbus->variable = "((IsoTrack_pfRelIso03_all[PionTriplet_FSpions[2+3*(MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))]]) / (IsoTrack_pt[PionTriplet_FSpions[2+3*(MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))]]))";

}

