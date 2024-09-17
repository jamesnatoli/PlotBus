// Function implementations for PlotBus
#ifndef PLOT_BUS_CC
#define PLOT_BUS_CC

#include <iostream>
#include <iomanip>

#include "PlotBus.h"

// Simpler Constructor
PlotBus::PlotBus( std::string year) {
  Init(); // LOOK HERE IF THERE ARE PROBLEMS
  if (!setupYear(year)) {
    std::cout << "ERROR: " << year << " is not a valid year!";
    throw;
  }
}

// Constructor takes era as parameter
PlotBus::PlotBus( std::string era, std::string channel, std::string year) {
  Init();
  PlotBus::era = era;
  PlotBus::channel = channel;
  PlotBus::year = year;
  PlotBus::filepath = "plots_" + era + "/";
}

void PlotBus::Init() { // Set ALL fields to default values
    // Default Options
  logy              = false;
  logz              = false;
  logandlin         = false;
  histErrors        = true;
  justDraw          = false;
  mergeSamples      = true;
  mergeSignals      = false;
  manualFiles       = false;
  saveHists         = false;
  saveCanvas        = false;
  plotData          = true;
  plotDataSR        = false;
  blindData         = false;
  plotSignal        = true;
  stitchSignal      = false;
  stackSignal       = false;
  stack             = true;
  keepStackOrder    = true;
  fillHists         = true;
  fillSignal        = false;
  usePalette        = false;
  drawLegend        = true;
  legendYield       = true;
  doQCD             = true;
  useAllQCD         = true;
  overflow          = true;
  ControlRegion     = false;
  qcdInfo           = false;
  doChi2            = false;
  DeepTauBinLabels  = false;
  manualBins        = false;
  twoDimensional    = false;
  getBinSig         = false;
  autoRatioLimits   = false;
  doRatioDataMC     = false;
  doRatioMCData     = false;
  doRatioDataSignal = false;
  doRatioSignalData = false;

  nbins     = 0;
  lowbin    = 0;
  highbin   = 0;
  ratioLow  = -0.5;
  ratioHigh = 1.0;
  bins        = {};
  bins2D      = {};
  blindRegion = {0, 150};

  verbosity  = 0;
  precision  = 2;
  Luminosity = -1;
  normalize  = "";
  year     = "";
  era      = "";
  channel  = "";
  filename = "";
  // filepath = "plots_" + era + "/";
  extfile  = "";
  prefix   = "~/KState/Research/Wto3pi/ROOT/skims/";
  variable = "";
  title    = "";
  xtitle   = variable;
  ytitle   = "Events";
  currentRegion  = "";
  canvasTags = {};
  RegionTitles = { 
		  {"A", "Signal Region (A)"},
		  {"B", "Shape Region (B)"},
		  {"C", "Ratio Numerator (C)"},
		  {"D", "Ratio Denominator (D)"}
  };
  
  ValRegionTitles = { 
		     {"A", "|Q|=3 Validation Region (A)"},
		     {"B", "|Q|=3 Shape Region (B)"},
		     {"C", "|Q|=3 Ratio Numerator (C)"},
		     {"D", "|Q|=3 Ratio Denominator (D)"}
  };

  datafiles      = {};
  dataTakingEras = {};
  signalfiles    = {};
  files          = {};
  bkgfiles       = {};

  hists = {}; // important container...

  // Default Cuts
  chargereq    = 1;
  deepTauVsEl  = 3;
  deepTauVsMu  = 15;
  deepTauVsJet = 15; // Signal Region
  Wpt          = 40;
  MaxdR        = 6.0;
  Dxy          = 1.0; 
  Dz           = 1.0;
  IsoTrack_iso = 0.1; // Signal Region
  bjetVeto = false;


  SignalScale = 6;
  addCuts = "";
  basicSelection = "(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack)) && Trigger_ditau && !LeptonVeto && (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack))";
  // with DM added
  // basicSelection = "(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (Tau_decayMode[Lepton_tauIdx[PionTriplet_FSpions1]] == 0) && (Tau_decayMode[Lepton_tauIdx[PionTriplet_FSpions2]] == 0)) && Trigger_ditau && !LeptonVeto && (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (Tau_decayMode[Lepton_tauIdx[PionTriplet_FSpions1]] == 0) && (Tau_decayMode[Lepton_tauIdx[PionTriplet_FSpions2]] == 0))";
  manualCutString = "";
  eventCuts    = "Trigger_ditau && METfilters && !LeptonVeto";
  // TriggerMatching is broken in 2018D... not really necessary anyways
  tripletCuts  = "(abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack)";  
  tripletCuts += " && (min( min( PionTriplet_dR_12_Track, PionTriplet_dR_13_Track), PionTriplet_dR_23_Track) > 0.3)";

  dataWeight     = "";
  stdMCweight    = "";
  DxyDzWeight    = "";
  qcdMCweight    = "";
  stitchMCweight = "";
  stitchDY       = "";
  stitchDY_LO    = "";
  stitchWJ       = "";
  stitchSig      = "";
  TTbar_NNLOweight = "";
  weights   = {};
  MCweights = {};

  // Probably a better way to do this...?
  SRcut1_scale = "(PionTriplet_pion3_iso < 0.1)";
  SRcut2_shape = "(PionTriplet_LowestDeepTauVsJet >= 15)";

  dataName = "Observed";
  bkgsToPlot = {"QCD", "DY", "TT", "VV"};
  processes  = {"QCD", "DY", "DY10", "ST", "TT", "ttV", "VV", "VVV", "W+Jets"};
  signals    = {};
  procsToStack   = {};
  signalsToStack = {};
  analyzeCuts    = {};

  colorIdx = 0;
  histFillStyle   = 1001;
  signalFillStyle = 0;
  drawingOptions  = "HIST SAME";
  bkgsParts = {{"DY10", "DY"}};
  samplesToMerge  = {
		     {"DY",
		      {"DY10"}
		     },
		     {"Top",
		      {"ST", "TT", "ttV"}
		     },
		     {"MultiBoson",
		      {"VV", "VVV"}
		     }
  };
  paletteColors = {};

  // Chains
  signalchain  = new TChain("Events");
  datachain    = new TChain("Events");
  for (auto proc : processes)
    processchain[proc] = new TChain("Events");

  if (mergeSignals) {
    samplesToMerge["WJetsTo3Pi"] =
      { "WJetsTo3Pi_0J",
	"WJetsTo3Pi_1J",
	"WJetsTo3Pi_2J",
	"WJetsTo3Pi_012J",
      };
  }
} // END INIT

bool PlotBus::setupYear( std::string year) { // called by constructor
  std::cout << "Setting up YEAR: " << year << std::endl;
  if ((year == "2016_preVFP") || (year == "2016_postVFP") || (year == "2017") || (year == "2018")) {
    PlotBus::year = year;
    PlotBus::era = "Wto3pi_" + year + "_fromstep1";
    
    // Wow, this is annoying
    std::string tag = "_ABCD_FS";
    if ((year == "2016_preVFP") || (year == "2016_postVFP"))
      PlotBus::channel = (year.find("postVFP") != std::string::npos) ? "Wto3pi_2016postVFP" + tag : "Wto3pi_2016preVFP" + tag;
    else
      PlotBus::channel = "Wto3pi_" + year + tag; 
    filepath = "plots_" + era + "/";
    return true;
  } else {
    return false;
  }
}

bool PlotBus::setupYear( std::string era, std::string channel, std::string year) {
  std::cout << "Setting up ERA, CHANNEL, AND YEAR: " << era << ", " << channel << ", " << year << std::endl;
  PlotBus::era = era;
  PlotBus::channel = channel;
  PlotBus::year = year;
   
  filepath = "plots_" + era + "/";
  return true;
}

bool PlotBus::isSignal( std::string objname) {
  return (std::find( signals.begin(), signals.end(), objname) != signals.end());
}

bool PlotBus::isData( std::string objname) {
  return (objname == dataName);
}

bool PlotBus::isSignal( TObject* obj) {
  // return (std::find( signals.begin(), signals.end(), obj->GetName()) != signals.end());
  for (auto ele : signals) {
    if (std::string(obj->GetName()).find( ele) != std::string::npos)
      return true;
  }
  return false;    
}

bool PlotBus::isData( TObject* obj) {
  return (std::string(obj->GetName()).find( dataName) != std::string::npos);
}

const char* PlotBus::getxtitle() {
  if (xtitle == "")
    return variable.c_str();
  else
    return xtitle.c_str();
}

std::string PlotBus::getDeepTauVsEl(bool invert) {
  if (invert)
    return ("!(PionTriplet_LowestDeepTauVsEl >= "+std::to_string(deepTauVsEl)+")").c_str();
  else
    return ("(PionTriplet_LowestDeepTauVsEl >= "+std::to_string(deepTauVsEl)+")").c_str();
  
};
std::string PlotBus::getDeepTauVsMu(bool invert) {
  if (invert)
    return ("!(PionTriplet_LowestDeepTauVsMu >= "+std::to_string(deepTauVsMu)+")").c_str();
  else
    return ("(PionTriplet_LowestDeepTauVsMu >= "+std::to_string(deepTauVsMu)+")").c_str();
};
std::string PlotBus::getDeepTauVsJet(bool invert) {
  if (invert)
    return ("!(PionTriplet_LowestDeepTauVsJet >= "+std::to_string(deepTauVsJet)+")").c_str();
  else
    return ("(PionTriplet_LowestDeepTauVsJet >= "+std::to_string(deepTauVsJet)+")").c_str();
};
std::string PlotBus::getDeepTauString() {
  return (PlotBus::getDeepTauVsEl() + " && " +
	  PlotBus::getDeepTauVsMu() + " && " +
	  PlotBus::getDeepTauVsJet());
};

std::string PlotBus::getWptString(bool invert) {
  if (invert)
    return "!(PionTriplet_pt_Full > " + std::to_string(Wpt) + ")";
  else
    return "(PionTriplet_pt_Full > " + std::to_string(Wpt) + ")";
}

std::string PlotBus::getMaxdRString(bool invert) {
  if (MaxdR == 0) {
    return "(max( max( PionTriplet_dR_12_Track, PionTriplet_dR_13_Track), PionTriplet_dR_23_Track) > -1)";
  } else {
    if (invert)
      return "!(max( max( PionTriplet_dR_12_Track, PionTriplet_dR_13_Track), PionTriplet_dR_23_Track) < " + std::to_string(MaxdR) +")";
    else
      return "(max( max( PionTriplet_dR_12_Track, PionTriplet_dR_13_Track), PionTriplet_dR_23_Track) < " + std::to_string(MaxdR) +")";
  }
}

std::string PlotBus::getDxyString(bool invert) {
  if (Dxy == 0) {
    return ("(max(max(abs(PionTriplet_pion1_dxy), abs(PionTriplet_pion2_dxy)), abs(PionTriplet_pion3_dxy)) > -1)");
  } else {
    if (invert)
      return ("!(max(max(abs(PionTriplet_pion1_dxy), abs(PionTriplet_pion2_dxy)), abs(PionTriplet_pion3_dxy)) < " + std::to_string(Dxy) + ")");
    else 
      return ("(max(max(abs(PionTriplet_pion1_dxy), abs(PionTriplet_pion2_dxy)), abs(PionTriplet_pion3_dxy)) < " + std::to_string(Dxy) + ")");
  }
}

std::string PlotBus::getDzString(bool invert) {
  if (Dz == 0) {
    return ("(max(max(abs(PionTriplet_pion1_dz), abs(PionTriplet_pion2_dz)), abs(PionTriplet_pion3_dz)) > -1)");
  } else {
    if (invert)
      return ("!(max(max(abs(PionTriplet_pion1_dz), abs(PionTriplet_pion2_dz)), abs(PionTriplet_pion3_dz)) < " + std::to_string(Dz) + ")");
    else
      return ("(max(max(abs(PionTriplet_pion1_dz), abs(PionTriplet_pion2_dz)), abs(PionTriplet_pion3_dz)) < " + std::to_string(Dz) + ")");
  }
  
}

// *** No Longer Used ***
std::string PlotBus::getBjetVetoString() {
  float vetoVal = 0.5;
  if (bjetVeto)
    return "(Sum$( (Jet_btagDeepB[ CleanJet_jetIdx] > " + std::to_string(vetoVal) + ") && (CleanJet_pt > 20) && (abs(CleanJet_eta) < 2.5)) == 0)";
  else return " (1) ";
}

std::string PlotBus::getIsoTrackIsoString() {
  if (IsoTrack_iso == 0)
    return ("(PionTriplet_pion3_iso >= 0)");
  else
    return ("(PionTriplet_pion3_iso < " + std::to_string(IsoTrack_iso) + ")").c_str();
}

std::string PlotBus::getChargeReqString() {
  // In case we want to use charge as a region variable
  if (chargereq == -1)
    return ("(abs(PionTriplet_charge) > " + PlotBus::getChargeReq() + ")").c_str();
  else
    return ("(abs(PionTriplet_charge) == " + PlotBus::getChargeReq() + ")").c_str();
};

std::string PlotBus::getSignalWeight( std::string proc="") {
  // return "(192900*1e-"+PlotBus::getSignalScale()+") * " + stitchSig + ") * (" + stitchMCweight;
  if (stitchSignal) {
    if ( proc.find("LO") != std::string::npos)
      return "(1e-"+PlotBus::getSignalScale()+") * " + weights[proc];
    else 
      return "(1e-"+PlotBus::getSignalScale()+") * " + stitchSig + ") * (" + stitchMCweight;
  } else {
    if (proc=="") {
      std::cout << "!!!ERROR!!! You must provide a provide a signal process!" << std::endl;
      return "(1)";
    } else {
      return "(1e-"+PlotBus::getSignalScale()+") * " + weights[proc];
    }
  }
};

std::string PlotBus::getProcesses() {
  std::string output = "{ ";
  for (int i = 0; i < processes.size(); ++i) {
    if (i != processes.size() - 1)
      output += processes[i] + ", ";
    else
      output += processes[i] + "}";
  }
  return output;
};

std::string PlotBus::getSignals() {
  std::string output = "{ ";
  for (int i = 0; i < signals.size(); ++i) {
    if (i != signals.size() - 1)
      output += signals[i] + ", ";
    else
      output += signals[i] + "}";
  }
  return output;
};

std::string PlotBus::getSelectionCut() {
  return ("(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, " +
	  PlotBus::getChargeReqString() + " && " +
	  PlotBus::getTripletCuts() + " && " +
	  PlotBus::getWptString() + " && " +
	  PlotBus::getMaxdRString() + " && " + 
	  PlotBus::getDeepTauString() + " && " +
	  PlotBus::getIsoTrackIsoString() + " && " +
	  PlotBus::getDxyString() + " && " +
	  PlotBus::getDzString() + 
	  "))");
};

// Overloaded for passing region information
// I feel like there's got to be a better way to do this...
std::string PlotBus::getSelectionCut( std::string extras) {
  return ("(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, " +
	  PlotBus::getChargeReqString() + " && " +
	  PlotBus::getTripletCuts() + " && " +
	  PlotBus::getWptString() + " && " +
	  PlotBus::getMaxdRString() + " && " + 
	  PlotBus::getDeepTauString() + " && " +
	  PlotBus::getIsoTrackIsoString() + " && " +
	  PlotBus::getDxyString() + " && " + 
	  PlotBus::getDzString() + " && " + 
	  extras + PlotBus::getAddCuts() + "))");
};

std::string PlotBus::getStdCutString() {
  return (PlotBus::getSelectionCut() + " && " + 
	  PlotBus::getEventCuts() + " && " +
	  PlotBus::getChargeReqString() + " && " +
	  PlotBus::getTripletCuts() + " && " +
	  PlotBus::getWptString() + " && " +
	  PlotBus::getMaxdRString() + " && " + 
	  PlotBus::getDeepTauString() + " && " +
	  PlotBus::getIsoTrackIsoString() + " && " +
	  PlotBus::getDxyString() + " && " + 
	  PlotBus::getDzString());
};

// Overloaded for passing region information
std::string PlotBus::getStdCutString( std::string extras) {
  return (PlotBus::getSelectionCut( extras) + " && " + 
	  PlotBus::getEventCuts() + " && " +
	  PlotBus::getChargeReqString() + " && " +
	  PlotBus::getTripletCuts() + " && " +
	  PlotBus::getWptString() + " && " +
	  PlotBus::getMaxdRString() + " && " + 
	  PlotBus::getDeepTauString() + " && " +
	  PlotBus::getIsoTrackIsoString() + " && " +
	  PlotBus::getDxyString() + " && " + 
	  PlotBus::getDzString());
};

std::string PlotBus::getFullCutString() {
  return (PlotBus::getStdCutString() + PlotBus::getAddCuts());
};

// Overloaded for passing region information
std::string PlotBus::getFullCutString( std::string extras) {
  return (PlotBus::getStdCutString(extras) + PlotBus::getAddCuts());
};

std::string PlotBus::getCutString( std::string process, std::string region="") {
  // Nominal Situation
  if (region == "") {
    if (manualCutString != "") {
      std::cout << ">>> USING MANUAL CUT STRING" << std::endl;
      if (std::find( signals.begin(), signals.end(), process) != signals.end())
	return ("(" + PlotBus::getSignalWeight( process) + ") * (" + manualCutString + ")");
      else if ( process == dataName)
	return manualCutString;
      return ("(" + weights[process] + ") * (" + manualCutString + ")");
    } else { // Normal Cut String
      if (std::find( signals.begin(), signals.end(), process) != signals.end())
	return PlotBus::getCutStringSig( process);
      else if ( process == dataName)
	return PlotBus::getFullCutString();
      return ("(" + weights[process] + ") * (" + PlotBus::getFullCutString() + ")");
    }
  } else { // Regions
    if (manualCutString != "") {
      std::cout << ">>> USING MANUAL CUT STRING" << std::endl;
      if (std::find( signals.begin(), signals.end(), process) != signals.end())
	return ("(" + PlotBus::getSignalWeight(process) + ") * (" + manualCutString + ")");
      else if ( process == dataName) {
	std::cout << "PLOTTING DATA: " << dataWeight << std::endl;
	return ("(" + dataWeight + ") * (" + manualCutString + ")");
      }
      // return manualCutString;
      return ("(" + weights[process] + ") * (" + manualCutString + ")");
    } else { // Normal Cut String
      if (std::find( signals.begin(), signals.end(), process) != signals.end()) 
	return "(" + PlotBus::getSignalWeight( process) + ") * " + PlotBus::getRegionCutSignal( region);
      else if ( process == dataName)
	return ("(" + dataWeight + ") * (" + PlotBus::getRegionCutData( region) + ")");
      return PlotBus::getRegionCutMC( region, process);
    }
  }
}

std::string PlotBus::getCutStringSig( std::string process) {
  return ("(" + PlotBus::getSignalWeight( process) + ") * (" + PlotBus::getFullCutString() + ")");
};

// TODO: Make this work for different named regions?? wow
std::string PlotBus::getRegionCut( std::string region) {
  if (region == "A")
    return getRegionCutsA();
  else if (region == "B")
    return getRegionCutsB();
  else if (region == "C")
    return getRegionCutsC();
  else if (region == "D")
    return getRegionCutsD();
  else {
    std::cout << "*** ERROR ***" << std::endl;
    std::cout << "Not a valid region: " << region << std::endl;
    return "";
  }
}

std::string PlotBus::getRegionTitle() {
  return RegionTitles[currentRegion];
}

std::string PlotBus::getRegionCutData( std::string region) {
  return (PlotBus::getFullCutString(PlotBus::getRegionCut(region)) + " && " + 
	  PlotBus::getRegionCut( region));
};

std::string PlotBus::getRegionCutMC( std::string region, std::string bkg) {
  return ("(" + weights[bkg] + ") * ( " +
	  PlotBus::getFullCutString(PlotBus::getRegionCut(region)) + " && " +
	  PlotBus::getRegionCut(region) + ")");
};

std::string PlotBus::getRegionCutSignal( std::string region) {
  return ("( " + PlotBus::getFullCutString(PlotBus::getRegionCut(region)) + " && " +
	  PlotBus::getRegionCut(region) + ")");
};

std::string PlotBus::getBinning() {
  if (!twoDimensional)
    return "("+std::to_string(nbins)+","+std::to_string(lowbin)+","+std::to_string(highbin)+")";
  else {
    std::string temp = "(";
    for (auto i : bins2D)
      temp += std::to_string(i) + ",";
    temp.pop_back(); // remove the final comma... low tech
    temp += ")";
    // return "("+std::to_string(2dbins[0])+","+std::to_string(lowbinx)+","+std::to_string(highbinx)+std::to_string(nbinsy)+","+std::to_string(lowbiny)+","+std::to_string(highbiny)+")";
    return temp;
  }
}

std::string PlotBus::getDrawString( std::string proc, std::string reg, bool printerMode) {
  if (manualBins) { // requires the "+" sign
    TH1F* temp;
    if (!printerMode) {
      temp = new TH1F( (proc + reg + year).c_str(), proc.c_str(), bins.size()-1, &bins[0]);
      temp->Draw();
    }
    // if ( isSignal( proc))
    //   return ("PionTriplet_MassInv_Full>>" + proc + reg + year);
    // else
    return (variable + ">>+" + proc + reg + year);
  } else {
    // if ( isSignal( proc))
    //   return ("PionTriplet_MassInv_Full>>" + proc + reg + year + PlotBus::getBinning());
    // else
    return (variable + ">>" + proc + reg + year + PlotBus::getBinning());
  }
}

// Setters
void PlotBus::SetBins( std::vector<double> b) {
  manualBins = true;
  bins = b;
}

void PlotBus::AddCuts( std::string cut) {
  if (addCuts == "")
    addCuts += "(1) * (" + cut + ")";
  else
    addCuts += " * (" + cut + ")";
}

void PlotBus::NoSignalRegion() {
  SRcut1_scale = "(1)";
  SRcut2_shape = "(1)";
}

void PlotBus::UnsetSignalRegionVars() {
  deepTauVsJet = 1;
  IsoTrack_iso = 0;
};

void PlotBus::MuonControlRegion() {
  if (!ControlRegion) {
    std::cout << ">> Using MUON CONTROL REGION" << std::endl;
    this->UseFullSamples();

    doRatioDataMC = true;
    ControlRegion = true;
    plotData      = true;
    plotDataSR    = true;
    plotSignal    = false;
    verbosity     = 0;
    
    processes   =  {"DY", "DY10", "ST", "TT", "ttV", "VV", "VVV"};
    
    tripletCuts = "(abs(PionTriplet_pdgId) == 13*13*15) && (PionTriplet_trailingIsTrack)";
    eventCuts   = "Trigger_ditau";
    // eventCuts   = " (1) ";
    deepTauVsMu = 0;
    IsoTrack_iso = 1.0;
    
    RegionTitles = { {"A", "Muon CR"}};
    filename += "_MuonCR";
    if (verbosity > 0) {
      std::cout << "\nIn the muon control region... " << std::endl
		<< "Proccesses : " << PlotBus::getProcesses() << std::endl
		<< "PlotSignal : false" << std::endl
		<< "TripletCuts: " << tripletCuts << " (muon pgdID = 13)" << std::endl
		<< "EventCuts  : " << eventCuts << " (no lepton veto)" << std::endl
		<< "DeepTauVsMu: None" << std::endl;
    }
  } else
    std::cout << ">> Control region already set... BE CAREFUL" << std::endl;
};

void PlotBus::QCDControlRegion(bool cr) {
  if (!ControlRegion) {
    if (cr) {
      std::cout << ">> Using QCD CONTROL REGION" << std::endl;
      // processes   =  {"QCD", "DY", "DY10", "ST", "TT", "ttV", "VV", "VVV"};
      ControlRegion = true;
      doRatioDataMC = true;
      qcdInfo       = true;
      doChi2        = false;
      plotData      = true;
      plotDataSR    = true;
      plotSignal    = false;
      chargereq = 3;
      Wpt = 0;
      // Dxy = 0.1;
      // Dz = 1.0;
      // AddCuts( "PionTriplet_pt_Full < 40");
      
      // RegionTitles = ValRegionTitles;
      filename += "_qcdCR";
      if (verbosity >= 0) {
	std::cout << "\nIn the QCD control region... " << std::endl
	  //	  << "Proccesses  : " << PlotBus::getProcesses() << std::endl
		  << "PlotSignal  : false" << std::endl
		  << "Charge (|Q|): 3" << std::endl
		  << "No WpT requirement" << std::endl;
      }
    }
  } else {
    std::cout << ">> Control region already set... BE CAREFUL" << std::endl;
  }
};

void PlotBus::Blind( std::vector<double> br) {
  blindData  = true;
  plotData   = true;
  plotDataSR = true;
  blindRegion = br;
};

// void PlotBus::SetSignalChain( TObject* chain) {
//   signalchain = (TChain*)chain;
// };

void PlotBus::SetProcessChain( ) {
  for (std::string proc : processes){
    if (proc != "QCD") {
      processchain[proc]->Reset(); // clear this, in case it was already set
      std::cout << proc << std::endl;
      // processchain[proc]->SetName("Events");
      for(std::string file : files[proc]){
	processchain[proc]->Add((file).c_str());
      }
    } else {
      doQCD = true;
    }
    std::cout << "here?" << std::endl;
  }
  std::cout << "returning..." << std::endl;
};

void PlotBus::SetDataChain( ) {
  datachain->Reset(); // clear this, in case it was already set
  for (std::string file : datafiles)
    datachain->Add((file).c_str());
};

void PlotBus::UseFullSamples( std::string s) {
  if (s != "")
    prefix = s;
  else
    prefix = "/Volumes/WineCellar/KState/analysis/";
}

void PlotBus::setPalette( int p=kBird) {
  usePalette = true;
  gStyle->SetPalette(p);
  drawingOptions += " PFC";
  return;
}

// 3744 is nice
void PlotBus::setHistFillStyle( int fs) {
  if (fs > 0)
    fillHists = true;
  histFillStyle = fs;
}

void PlotBus::setSignalFillStyle( int fs) {
  if (fs > 0)
    fillSignal = true;
  signalFillStyle = fs;
}

void PlotBus::setDeepTauBinning() {
  DeepTauBinLabels = true;
  if (variable.find( "Mu") != std::string::npos) {
    nbins = 12;
    lowbin = -0.5;
    highbin = 5.5;
  } else {
    nbins = 22;
    lowbin = -0.5;
    highbin = 10.5;
  }
}

void PlotBus::DrawProcess( std::string process, std::string region) {                                                                                                     
  processchain[process]->Draw( (getDrawString( process, region)).c_str(), (getCutString( process, region)).c_str());                                                           
}

void PlotBus::DrawData( std::string region) {
  datachain->Draw( getDrawString( dataName, region).c_str(), getCutString( dataName, region).c_str());
} 

void PlotBus::MergeFiles() {
  files.insert( bkgfiles.begin(), bkgfiles.end());
  if (plotSignal) {
    files.insert( signalfiles.begin(), signalfiles.end());
    for (auto& ele : signalfiles)
      if ( std::find( signals.begin(), signals.end(), ele.first) != signals.end())
	processes.push_back(ele.first);
  }
  if (plotData) {
    files[dataName] = datafiles;
    // Name data how we want
    processes.push_back( dataName);
  }
}

void PlotBus::PrintYields() {
  getYieldsAndEntries( hists);
}

void PlotBus::PrintYields( std::map<std::string, std::vector<std::string>> yields, int prec, std::string text) {
  // TODO: get maximum length for process, yields, and entries :/
  int offsets[3] = { 20, 10, 7};
  text = (text!="") ? (": " + text) : "";
  std::cout << "    *** Yields Table" << text << " ***" << std::endl;
  std::cout << std::setw(offsets[0]) << std::left
	    << "Process" << ", "
	    << std::setw(offsets[1] + prec) << std::right
	    << "Yield" << ", "
	    << std::setw(offsets[2]) << std::right
	    << "Entries" 
	    << std::endl;
  std::cout << "--------------------------------------------" << std::endl;
  for (auto const& yld : yields) {
    std::cout << std::setw(offsets[0]) << std::left
	      << yld.first << ", "
	      << std::setw(offsets[1] + prec) << std::right
	      << yld.second[0] << ", "
	      << std::setw(offsets[2]) << std::right
	      << yld.second[1]
	      << std::endl;
  }
}

void PlotBus::CalculateYields( std::map<std::string, TH1*> hists, std::map<std::string, std::vector<std::string>>* yields) {
  std::stringstream integ;
  // Loop over only the backgrounds that we want to plot
  // NB: The Fitter seems to take *yields* from overflow, but nentries from only bins, so match that
  // NNB: nentries is CONSTANT (and an integral)
  for (auto const& hist : hists) {
    if (overflow) 
      integ << std::fixed << std::setprecision( precision) << hist.second->Integral( 0, hist.second->GetNbinsX()+1);
    else {
      integ << std::fixed << std::setprecision( precision) << hist.second->Integral( 0, hist.second->GetNbinsX());
    }
    
    std::vector<std::string> vec{ integ.str(), std::to_string( (int)hist.second->GetEntries())};
    (*yields)[hist.first] = vec;
    
    // Reset the stringstream
    integ.str( std::string());
  }
}

void PlotBus::getYieldsAndEntries( std::map<std::string, TH1*> hists, TLegend* legend) {
  if (verbosity > 1)
    std::cout << ">>> Getting Yields and Entries..." << std::endl;
  std::map<std::string, std::vector<std::string>> yields = {};

  CalculateYields( hists, &yields);
  if (legend) {
    std::stringstream integ;
    for (auto const& hist : hists) {
      std::string legendTitle = hist.first;
      if (legendYield)
	legendTitle += " ("+yields[hist.first][0]+")";
      
      // Now add to legend
      // TODO: fix this special signal functionality...
      // "W->3#pi, B=10^-"+pb->getSignalScale()
      if ( isSignal( hist.first))
	legend->AddEntry( hist.second, (legendTitle).c_str(), getSignalFill());
      else if (hist.first == dataName)
	legend->AddEntry( hist.second, (legendTitle).c_str(),"lep");
      else 
	legend->AddEntry( hist.second, (legendTitle).c_str(), getHistFill());

      // Reset the stringstream
      integ.str( std::string());
    } // for (auto const& hist : hists)
  } // if (legend)
  
  if (verbosity >= 0)
    PrintYields( yields, precision, currentRegion);
}

// Merge samples, but smartly :)
int PlotBus::MergeSamples( std::map<std::string, TH1*> *phists) {
  if (!mergeSamples) {
    return 1;
  }
  // dereference this once here...
  std::map<std::string, TH1*> &hists = *phists;

  // Do Things
  for (auto const& merger : samplesToMerge) {
    // Merge samples to create a *NEW* process
    if (std::find( processes.begin(), processes.end(), merger.first) == processes.end()) {
      if (verbosity > 1)
	std::cout << ">>> Creating new process: " << merger.first << std::endl;
      // processes.push_back( merger.first);
      if (std::find( processes.begin(), processes.end(), merger.second[0]) != processes.end()) {
	hists[merger.first] = (TH1F*)hists[merger.second[0]]->Clone((merger.first + currentRegion + year).c_str());
	hists[merger.first]->Reset();
      } else {
	std::cout << ">>> !!!MERGE ERROR: Sample " << merger.second[0] << " did not exist... could not merge" << std::endl;
      }
    }

    // Now we've ensured that there is something to add to 
    for (auto const& sample : merger.second) {
      if (std::find( processes.begin(), processes.end(), sample) != processes.end()) {
	if (verbosity > 1) {
	  std::cout << ">>> Adding " << sample << " to " << merger.first << std::endl;
	  std::cout << ">>> Erasing: " << sample << std::endl;
	}
	if (hists[sample]) {
	  hists[merger.first]->Add( hists[sample], 1);
	  hists.erase( sample);
	} else {
	  std::cout << ">>> MergeSamples: Couldn't add " << sample << " to " << merger.first << std::endl;
	}
	// processes.erase( std::find( processes.begin(), processes.end(), sample));
      } else {
	std::cout << ">>> !!!MERGE ERROR: Sample " << merger.second[0] << " did not exist... could not merge" << std::endl;
      }
    } // end sample loop
  } // end merger loop
  return 0;
}

// Option to use the normalized weight for crosscheck with Plotter
void PlotBus::UseNormWeight(std::string inWeight="") {
  if (inWeight == "")
    inWeight = "(XSec * " + getLumi(2) + " * 1000 * (1/SumOfWeights) * Generator_weight * PUweight * PionTriplet_TauSFweight_Loose)";

  stdMCweight = inWeight;
  
  MCweights   = {{"DY",     "(" + stitchDY + " * " + stitchMCweight + ")"},
		 {"W+Jets", "(" + stitchWJ + " * " + stitchMCweight + ")"},
		 {"DY10",   inWeight},
		 {"ST",     inWeight},
		 {"TT",     inWeight},
		 {"ttV",    inWeight},
		 {"VV",     inWeight},
		 {"VVV",    inWeight},
		 {"QCD MC", inWeight},
  };
  weights = MCweights;
}

#endif

