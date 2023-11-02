#include <iostream>
#include <fstream>
#include <math.h>

#include <iomanip>
#include <chrono>

using namespace std;
#include "/Users/jamesnatoli/KSTATE/Research/Wto3pi/PlotBus/PlotBus.h"
#include "/Users/jamesnatoli/KSTATE/Research/Wto3pi/PlotBus/PlotTrain.h"
#include "/Users/jamesnatoli/KSTATE/Research/Wto3pi/PlotBus/SimplePlot.h"
#include "/Users/jamesnatoli/KSTATE/Research/Wto3pi/PlotBus/macros/InvMass.C"

int main(int argc, char *argv[]) {

  PlotTrain* plotbus = new PlotTrain({"2017", "2018"});
  // PlotBus* plotbus = new PlotBus("2017");
  // plotbus->UseFullSamples();
  
  // plotbus->filepath += "SignalRegion";
  plotbus->filename = "InvMass_LooseVsJet_DM0_No2PiMass";
  plotbus->AddCanvasTag("Full #tau_{h} info");
  plotbus->AddCanvasTag("#tau_{1,2} DM0");
  // plotbus->AddCanvasTag("#tau_{1} OR #tau_{2} DM0");
  plotbus->chargereq = 1;
  plotbus->SignalScale = 6;
  plotbus->variable = "InvMass( Lepton_pt[PionTriplet_FSpions1], Lepton_eta[PionTriplet_FSpions1], Lepton_phi[PionTriplet_FSpions1], Lepton_pt[PionTriplet_FSpions2], Lepton_eta[PionTriplet_FSpions2], Lepton_phi[PionTriplet_FSpions2], PionTrack_pt[PionTriplet_FSpions3], PionTrack_eta[PionTriplet_FSpions3], PionTrack_phi[PionTriplet_FSpions3])";
  // plotbus->variable = "Tau_leadTkPtOverTauPt[ Lepton_tauIdx[ PionTriplet_FSpions2]]";
  // plotbus->variable = "TMath::Log2(Tau_idDeepTau2017v2p1VSjet[Lepton_tauIdx[PionTriplet_FSpions2]]+1)";
  // plotbus->variable = "max( max(abs(PionTriplet_dR_13), abs(PionTriplet_dR_23)), abs(PionTriplet_dR_12))";
  plotbus->xtitle  = "m_{W} [GeV]";
  // plotbus->xtitle = "Trk_{3} pfRelIso03 * p_{T}";
  // plotbus->xtitle = "Trk_{1} p_{T} / #tau_{1} p_{T}";
  
  // Binning
  plotbus->nbins    = 30;
  plotbus->lowbin   = 0;
  plotbus->highbin  = 300;
  // plotbus->SetBins( {0, 45, 60, 75, 85, 100, 115, 130, 145, 160, 175, 190, 205, 220, 235, 250, 400});
  plotbus->SetBins( {0, 60, 75, 85, 100, 130, 160, 190, 220, 250, 300, 400});
  
  // plotbus->setDeepTauBinning();

  // Low Purity
  // plotbus->AddCuts( "(Tau_decayMode[Lepton_tauIdx[PionTriplet_FSpions1]] == 0) || (Tau_decayMode[Lepton_tauIdx[PionTriplet_FSpions2]] == 0)");
  // High Purity
  plotbus->AddCuts( "Tau_decayMode[Lepton_tauIdx[PionTriplet_FSpions1]] == 0");
  plotbus->AddCuts( "Tau_decayMode[Lepton_tauIdx[PionTriplet_FSpions2]] == 0");
  // plotbus->AddCuts( "PionTriplet_MassInv_12 < 80");
  // plotbus->AddCuts( "(PionTriplet_pion1_pt > 35) && (PionTriplet_pion2_pt > 35)");

  // plotbus->UseBasicSelection();
  // plotbus->manualCutString = "(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 13*13*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_pt > 40) && (max( max(abs(PionTriplet_pion1_dxy), abs(PionTriplet_pion2_dxy)), abs(PionTriplet_pion3_dxy)) < 0.01) && (max( max(abs(PionTriplet_pion1_dz), abs(PionTriplet_pion2_dz)), abs(PionTriplet_pion3_dz)) < 0.01)) && Trigger_ditau && LeptonVeto && (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 13*13*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_pt > 40) && (max( max(abs(PionTriplet_pion1_dxy), abs(PionTriplet_pion2_dxy)), abs(PionTriplet_pion3_dxy)) < 0.01) && (max( max(abs(PionTriplet_pion1_dz), abs(PionTriplet_pion2_dz)), abs(PionTriplet_pion3_dz)) < 0.01))";

  // Signal Region
  plotbus->Dxy = 0.005;
  plotbus->Dz  = 0.01;
  plotbus->Wpt = 40;
  plotbus->MaxdR = 0.0;

  // Options
  plotbus->logy         = false;
  plotbus->getBinSig    = false;
  plotbus->saveHists    = false;
  plotbus->saveCanvas   = false;
  plotbus->stack        = true;
  plotbus->fillHists    = true;
  plotbus->overflow     = true;
  plotbus->qcdInfo      = false;
  plotbus->doChi2       = false;
  plotbus->mergeSamples = true;
  plotbus->mergeSignals = true;

  plotbus->plotData     = false;
  plotbus->plotDataSR   = false;
  plotbus->plotSignal   = true;
  plotbus->stitchSignal = false;
  plotbus->verbosity    = 0;
  plotbus->normalize = false;

  // Do Control Regions here, because they will overwrite some settings
  // plotbus->QCDControlRegion();
  
  // load any macros first
  // W3pi_weightadder();
  InvMass();

  plotbus->processes = {"DY", "DY10", "ST", "TT", "ttV", "VV", "VVV", "QCD"};
  plotbus->procsToStack = {"DY", "MultiBoson", "Top", "QCD"};
  // need to add the merged one here...
  // plotbus->signals = {"WJetsTo3Pi_0J", "WJetsTo3Pi_1J", "WJetsTo3Pi_2J", "WJetsTo3Pi_012J", "WJetsTo3Pi", "Wto3pi2017"};
  plotbus->signals = {"WJetsTo3Pi_Incl"};

  // Now Run
  auto start = std::chrono::high_resolution_clock::now();
  plotbus->SimplePlot();
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
  std::cout << ">>> Finished in " << duration.count() << " seconds" << std::endl;
}


