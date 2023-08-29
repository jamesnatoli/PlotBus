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
#include <chrono>

using namespace std;
#include "/Users/jamesnatoli/KSTATE/Research/Wto3pi/PlotBus/SimplePlot.cc"
#include "/Users/jamesnatoli/KSTATE/Research/Wto3pi/PlotBus/W3pi_weightadder.C"

int main(int argc, char *argv[]) {

  std::string era = "Wto3pi_2018_cont2";
  std::string channel = "Wto3pi_postfix2_2018";
  PlotBus* plotbus = new PlotBus( era, channel, 2018);
  // plotbus->UseFullSamples();

  // plotbus->filepath += "Nominal";
  plotbus->filename = "InvMass_test";
  plotbus->variable = "PionTriplet_MassInv";
  plotbus->xtitle   = "Inv Mass [GeV]";
  plotbus->title    = "Inv Mass";

  // Probably just hard code this now?
  // plotbus->addCuts = " (1) ";
  // plotbus->addCuts += " && (max(max(PionTriplet_dR_12, PionTriplet_dR_13), PionTriplet_dR_23) < 3.0)";

  // plotbus->deepTauVsEl = 15;

  // plotbus->manualCutString = "( (PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 0) && (PionTriplet_LowestDeepTauVsMu >= 0) && (PionTriplet_LowestDeepTauVsJet >= 0) && (PionTriplet_pion3_iso >= 0) )) && Trigger_ditau && !LeptonVeto && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (abs(PionTriplet_charge) == 1) && (PionTriplet_LowestDeepTauVsEl >= 0) && (PionTriplet_LowestDeepTauVsMu >= 0) && (PionTriplet_LowestDeepTauVsJet >= 0) && (PionTriplet_pion3_iso >= 0))";

  // Nominal
  plotbus->Dxy = 0.045;
  plotbus->Dz  = 0.2;
  // plotbus->Wpt = 0;
  
  // Low Purity
  // plotbus->Dxy = 0.01;
  // plotbus->Dz  = 0.05;
  plotbus->Wpt = 0;
  plotbus->MaxdR = 0;
  
  // High Purity
  // plotbus->Dxy = 0.005;
  // plotbus->Dz  = 0.01;
  // plotbus->Wpt = 75;
  // plotbus->addCuts  = "(max( max( PionTriplet_dR_12, PionTriplet_dR_13), PionTriplet_dR_23) < 3.0)";

  plotbus->nbins     = 40;
  plotbus->lowbin    = 0;
  plotbus->highbin   = 400;

  plotbus->getBinSig    = false;
  plotbus->saveHists    = false;
  plotbus->saveCanvas   = false;
  plotbus->plotSignal   = true;
  plotbus->stack        = true;
  plotbus->overflow     = false;
  plotbus->fillHists    = true;
  plotbus->qcdInfo      = true;
  plotbus->mergeSamples = true;
  std::string DxyDzWeight = "IPweight( abs(PionTriplet_pion1_dxy), abs(PionTriplet_pion1_dz), abs(PionTriplet_pion2_dxy), abs(PionTriplet_pion2_dz), abs(PionTriplet_pion3_dxy), abs(PionTriplet_pion3_dz))";
  plotbus->UseNormWeight( "(XSec * " + to_string(plotbus->Luminosity) + " * 1000 * (1/SumOfWeights) * Generator_weight * PUweight * PionTriplet_TauSFweight * " + DxyDzWeight + ")");

  W3pi_weightadder();

  plotbus->verbosity   = 0;
  plotbus->SignalScale = 6;

  // plotbus->procsToStack = plotbus->processes;
  plotbus->procsToStack = {"QCD", "MultiBoson", "DY", "Top"};

  // Now Run
  auto start = std::chrono::high_resolution_clock::now();
  SimplePlot( plotbus);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
  std::cout << ">>> Finished in " << duration.count() << " seconds" << std::endl;
}


