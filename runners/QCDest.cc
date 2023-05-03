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
#include "/Users/jamesnatoli/KSTATE/Research/Wto3pi/Plotting/QCDestimation.cc"

int main(int argc, char *argv[]) {
  PlotBus* plotbus;
  std::string era = "Wto3pi_2018_cont2";
  if (argc < 2) {
    std::cout << "No year provided... defaulting to 2018" << std::endl;
    plotbus = new PlotBus( 2018);
    plotbus->mainpath = "~/KState/Research/Wto3pi/ROOT/skims/" + era;
    // plotbus->mainpath = "/Volumes/WineCellar/KState/analysis/" + era;
    plotbus->era  = era;
  } else {
    std::cout << "Using year: " << argv[1] << std::endl;
    plotbus = new PlotBus( atoi(argv[1]));
    plotbus->mainpath = "~/KState/Research/Wto3pi/ROOT/skims/" + era;
    plotbus->era  = era;
  }
  
  // This can go in the object, it's not going to change for QCDest
  plotbus->variable = "PionTriplet_MassInv";
  plotbus->verbosity = 1;

  // -1 is Flag for no charge req in cut (using it as region variable)
  plotbus->SignalScale = 6;
  plotbus->chargereq = 1;
  if (plotbus->chargereq == 1)
     plotbus->plotDataSR = false;
  else
    plotbus->plotDataSR = true;
  plotbus->filepath += "QCDPlots/";

  bool deepTauShape = false;
  if (deepTauShape) {
    plotbus->filename = "DeepTauMedium_Pion3Iso_charge" + to_string(plotbus->chargereq);
    plotbus->SRcut1_scale = "(PionTriplet_LowestDeepTauVsJet >= 31)";
    plotbus->SRcut2_shape = "(PionTriplet_pion3_iso < 0.1)";
  } else { // Pion Iso Shape
    plotbus->filename = "Pion3Iso_DeepTauMedium_charge" + to_string(plotbus->chargereq);
    plotbus->SRcut1_scale = "(PionTriplet_pion3_iso < 0.1)";
    plotbus->SRcut2_shape = "(PionTriplet_LowestDeepTauVsJet >= 31)";
  }

  plotbus->Dxy = 0.025;
  plotbus->Dz  = 0.05;
  std::string bjetveto = "0.5";

  plotbus->addCuts = "(PionTriplet_pt>40)";
  // plotbus->addCuts += " && (max( max( PionTriplet_dR_12, PionTriplet_dR_13), PionTriplet_dR_23) < 3.0)";
  // plotbus->addCuts = "(PionTriplet_pt>40) && (PionTriplet_dR_12 < 2.0)";
  // plotbus->addCuts += " && (PionTriplet_pion1_dz < "+dzcut+") && (PionTriplet_pion2_dz < "+dzcut+") && (PionTriplet_pion3_dz < "+dzcut+")";
  // plotbus->addCuts += " && (PionTriplet_pion1_dxy < "+dxycut+") && (PionTriplet_pion2_dxy < "+dxycut+") && (PionTriplet_pion3_dxy < "+dxycut+")";
  // plotbus->addCuts += " && (Sum$( (Jet_btagDeepB[ CleanJet_jetIdx] > "+bjetveto+") && (CleanJet_pt > 20) && (abs(CleanJet_eta) < 2.5)) == 0)";
    
  // plotbus->addCuts = "((PionTriplet_pt>40) && (PionTriplet_LowestDeepTauVsJet >= 31))"; // && (PionTriplet_pion3_iso < 0.5)";
  // plotbus->addCuts = "(PionTriplet_pion3_iso < 0.5)";
  // plotbus->addCuts = "(PionTriplet_pt>40) && (PionTriplet_pion3_iso < 2.0)";

  plotbus->UnsetSignalRegionVars();
  
  plotbus->nbins     = 20;
  plotbus->lowbin    = 0;
  plotbus->highbin   = 400;
  double bins[26] = { 00.0, 10.0, 20.0, 30.0, 40.0, 
		      50.0, 60.0, 70.0, 80.0, 90.0,
		      100.0, 110.0, 120.0, 130.0, 140.0,
		      150.0, 160.0, 170.0, 180.0, 190.0,
		      200.0, 210.0, 220.0, 230.0, 240.0,
		      250.0};
  plotbus->bins = bins;

  plotbus->saveHists = true;
  plotbus->plotSignal = true;

  // plotbus->bkgsToPlot = {"TT", "DY", "ST", "QCD MC"};
  plotbus->bkgsToPlot = {"TT", "DY", "ST"};
  // plotbus->analyzeCuts = { 2.0, 2.5, 3.0};

  QCDestimation( plotbus);
  
  // plotbus->variable = "((IsoTrack_pfRelIso03_all[PionTriplet_FSpions[2+3*(MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))]]) / (IsoTrack_pt[PionTriplet_FSpions[2+3*(MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))]]))";

}

