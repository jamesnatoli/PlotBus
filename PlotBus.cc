// class to store plotting information and pass it to TryPlot.cc
#ifndef PLOT_BUS_CC
#define PLOT_BUS_CC

// Constructor takes era as parameter
PlotBus::PlotBus( std::string era, std::string channel, int year, std::string VFP="") {
  PlotBus::era = era;
  PlotBus::channel = channel;
  PlotBus::year = year;

  if (year == 2016) {
    if (VFP == "postVFP")
      PlotBus::postVFP = true;
    else if (VFP == "preVFP")
      PlotBus::preVFP = true;
    else {
      std::cout << "Not preVFP or postVFP!!!" << std::endl;
      throw;
    }
  } else if (VFP !=  "") {
    std::cout << "No " << VFP << " option for " << year << "!!!" << std::endl;
    throw;
  }
  
  // These are sort of defaults... can be overwritten
  PlotBus::dataTakingEras = {};
  files = {};
  bkgfiles = {};
  processes = {"QCD", "DY", "DY10", "ST", "TT", "ttV", "VV", "VVV", "W+Jets"};
  bkgsToPlot = {"QCD", "DY", "TT", "VV"};

  mergeSamples   = true;
  manualFiles    = false;
  samplesToMerge = {
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
  procsToStack = {};
  signalsToStack = {};
  bkgsParts = {{"DY10", "DY"}};
  prefix = "~/KState/Research/Wto3pi/ROOT/skims/";
  filepath = "plots_" + era + "/";
  currentRegion = "";
  
  // Aesthetics
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
  
  // Default Options
  logy             = false;
  logandlin        = false;
  saveHists        = false;
  saveCanvas       = false;
  plotData         = true;
  plotDataSR       = false;
  plotSignal       = true;
  stitchSignal     = false;
  stackSignal      = false;
  normalize        = false;
  stack            = true;
  fillHists        = true;
  drawLegend       = true;
  doQCD            = true;
  overflow         = false;
  qcdInfo          = false;
  doChi2           = false;
  DeepTauBinLabels = false;
  getBinSig        = false;
  autoRatioLimits  = false;
  doRatioDataMC    = false;
  doRatioMCData    = false;

  ratioLow  = -0.5;
  ratioHigh = 1.0;
  verbosity = 0;

  // ControlRegion = false;

  // Default Cuts
  chargereq = 1;
  
  deepTauVsEl  = 3;
  deepTauVsMu  = 15;
  deepTauVsJet = 31; // Signal Region

  Wpt = 40;
  MaxdR = 3.0;

  IsoTrack_iso = 0.1; // Signal Region

  // Impact Parameters
  Dxy = 1.0; // these are extremely loose
  Dz  = 1.0;

  bjetVeto = false;

  // Probably a better way to do this...?
  SRcut1_scale = "(PionTriplet_pion3_iso < 0.1)";
  SRcut2_shape = "(PionTriplet_LowestDeepTauVsJet >= 31)";
    
  SignalScale = 6;
  eventCuts   = "Trigger_ditau && !LeptonVeto";
  // TriggerMatching is broken in 2018D... not really necessary anyways
  // tripletCuts = "(abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && PionTriplet_TriggerMatched";
  // tripletCuts = "(abs(PionTriplet_pdgId) == 15*15*15) && !(PionTriplet_trailingIsTrack)";
  tripletCuts = "(abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack)";
  
  tripletCuts+= " && (min( min( PionTriplet_dR_12, PionTriplet_dR_13), PionTriplet_dR_23) > 0.3)";

  if (year == 2018) {
    stitchDY    = "(LHE_Njets==0?1.83962:1)*(LHE_Njets==1?0.628821:1)*(LHE_Njets==2?0.492408:1)*(LHE_Njets==3?0.233581:1)*(LHE_Njets==4?0.263824:1)*(LHE_Njets>4?1.83962:1)";
    stitchWJ    = "(LHE_Njets==0?2.1238030067e-04:1)*(LHE_Njets==1?9.4034644862e-05:1)*(LHE_Njets==2?7.8360783678e-05:1)*(LHE_Njets>2?8.1203167262e-05:1)";
    stitchSig = "";
    TTbar_NNLOweight = "Weight_TTbar_NNLO";
    dataTakingEras = {"A", "B", "C", "D"};
    Luminosity  = 59.8;
  } else if (year == 2017) {
    stitchDY = "(LHE_Njets==0?1.23734:1)*(LHE_Njets==1?0.414618:1)*(LHE_Njets==2?0.370996:1)*(LHE_Njets==3?0.215047:1)*(LHE_Njets==4?0.164546:1)*(LHE_Njets>4?1.23734:1)";
    stitchWJ = "(LHE_Njets==0?1.5334343878e-04:1)*(LHE_Njets==1?6.7497287730e-05:1)*(LHE_Njets==2?5.4048680964e-05:1)*(LHE_Njets>2?5.5666140133e-05:1)";
    stitchSig = "";
    TTbar_NNLOweight = "Weight_TTbar_NNLO";
    dataTakingEras = {"B", "C", "D", "E", "F"};
    Luminosity  = 41.5;
  } else if (year == 2016){
    if (postVFP) {
      std::cout << "No DY stitching weights for year: " << std::to_string( year) << std::endl;
      stitchDY  = "1";
      stitchWJ  = "(LHE_Njets==0?6.3492381179e-05:1)*(LHE_Njets==1?2.8788703517e-05:1)*(LHE_Njets==2?2.4297924110e-05:1)*(LHE_Njets>2?2.5215777910e-05:1)";
      stitchSig = "(LHE_Njets==0?0.0000807681027851917:1)*(LHE_Njets==1?0.0000266468927055796:1)*(LHE_Njets==2?0.0000221933057209814:1)*(LHE_Njets>2?0.00002287818499483:1)";
      TTbar_NNLOweight = "Weight_TTbar_NNLO";
      dataTakingEras = {"F", "G", "H"};
      Luminosity  = 16.8;
    } else if (preVFP) {
      std::cout << "No DY stitching weights for year: " << std::to_string( year) << std::endl;
      stitchDY = "1";
      stitchWJ = "(LHE_Njets==0?7.6176665591e-05:1)*(LHE_Njets==1?3.2866842007e-05:1)*(LHE_Njets==2?2.7493712509e-05:1)*(LHE_Njets>2?2.8571509261e-05:1)";
      stitchSig = "";
      TTbar_NNLOweight = "Weight_TTbar_NNLO";
      dataTakingEras = {"B", "C", "D", "E", "F"};
      Luminosity  = 19.5;
    }
  } else {
    stitchDY    = "(1)";
    stitchWJ    = "(1)";
    stitchSig   = "(1)";
    TTbar_NNLOweight = "1";
    std::cout << "ERROR!!! Not a valid year: " << std::to_string( year) << std::endl;
    std::cout << "Will use 2018 Luminosity (59.83) by default, unless set manually" << std::endl;
    Luminosity  = 59.8;
  }
  
  // Keep the various MC weights here
  // DxyDzWeight = "IPweight( abs(PionTriplet_pion1_dxy), abs(PionTriplet_pion1_dz), abs(PionTriplet_pion2_dxy), abs(PionTriplet_pion2_dz), abs(PionTriplet_pion3_dxy), abs(PionTriplet_pion3_dz))";
  DxyDzWeight = "(1)";
  // DxyDzWeight = "(PionTriplet_DxyDz_Weight)";
  stdMCweight = "(XSecMCweight * Generator_weight * PUweight * PionTriplet_TauSFweight * " + DxyDzWeight + ")";
  
  // We doubled the statistics for QCD MC (not being used anymore)
  qcdMCweight    = "(XSecMCweight * Generator_weight * PUweight * PionTriplet_TauSFweight * 0.5)";
  // LHE Weights don't need XSecMCweight (and by extension, GenWeight)?
  stitchMCweight = "(PUweight * PionTriplet_TauSFweight)";
  stitchMCweight = "(1)";

  MCweights   = {{"DY",     "(" + stitchDY + " * " + stitchMCweight + ")"},
		 {"W+Jets", "(" + stitchWJ + " * " + stitchMCweight + ")"},
		 {"DY10",   stdMCweight},
		 {"ST",     stdMCweight},
		 {"TT",     "(" + stdMCweight + "*" + TTbar_NNLOweight + ")"},
		 {"ttV",    stdMCweight},
		 {"VV",     stdMCweight},
		 {"VVV",    stdMCweight},
		 {"QCD MC", qcdMCweight},
  };
  weights = MCweights;
  
  // This actually does nothing...
  // then remove it? 
  title  = variable;
  xtitle = title;
} // END CONSTRUCTOR

std::string PlotBus::getDeepTauVsEl() {
  return ("(PionTriplet_LowestDeepTauVsEl >= "+std::to_string(deepTauVsEl)+")").c_str();
};
std::string PlotBus::getDeepTauVsMu() {
  return ("(PionTriplet_LowestDeepTauVsMu >= "+std::to_string(deepTauVsMu)+")").c_str();
};
std::string PlotBus::getDeepTauVsJet() {
  return ("(PionTriplet_LowestDeepTauVsJet >= "+std::to_string(deepTauVsJet)+")").c_str();
};
std::string PlotBus::getDeepTauString() {
  return (PlotBus::getDeepTauVsEl() + " && " +
	  PlotBus::getDeepTauVsMu() + " && " +
	  PlotBus::getDeepTauVsJet());
};

std::string PlotBus::getWptString() {
  return "(PionTriplet_pt > " + std::to_string(Wpt) + ")";
}

std::string PlotBus::getMaxdRString() {
  if (MaxdR == 0)
    return "(max( max( PionTriplet_dR_12, PionTriplet_dR_13), PionTriplet_dR_23) > -1)";
  else
    return "(max( max( PionTriplet_dR_12, PionTriplet_dR_13), PionTriplet_dR_23) < " + std::to_string(MaxdR) +")";
}

std::string PlotBus::getDxyString() {
  if (Dxy == 0)
    return ("(max(max(abs(PionTriplet_pion1_dxy), abs(PionTriplet_pion2_dxy)), abs(PionTriplet_pion3_dxy)) > -1)");
    // return ("(abs(PionTriplet_pion1_dxy) > -1) && (abs(PionTriplet_pion2_dxy) > -1) && (abs(PionTriplet_pion3_dxy) > -1)");
  else
    return ("(max(max(abs(PionTriplet_pion1_dxy), abs(PionTriplet_pion2_dxy)), abs(PionTriplet_pion3_dxy)) < " + std::to_string(Dxy) + ")");
    /*
      return ("(abs(PionTriplet_pion1_dxy) < " + std::to_string(Dxy) + ") && " +
      "(abs(PionTriplet_pion2_dxy) < " + std::to_string(Dxy) + ") && " +
      "(abs(PionTriplet_pion3_dxy) < " + std::to_string(Dxy) + ")");
    */
}

std::string PlotBus::getDzString() {
  if (Dz == 0)
    return ("(max(max(abs(PionTriplet_pion1_dz), abs(PionTriplet_pion2_dz)), abs(PionTriplet_pion3_dz)) > -1)");
  // return ("(abs(PionTriplet_pion1_dz) > -1) && (abs(PionTriplet_pion2_dz) > -1) && (abs(PionTriplet_pion3_dz) > -1)");
  else
    return ("(max(max(abs(PionTriplet_pion1_dz), abs(PionTriplet_pion2_dz)), abs(PionTriplet_pion3_dz)) < " + std::to_string(Dz) + ")");
  /*
    return ("(abs(PionTriplet_pion1_dz) < " + std::to_string(Dz) + ") && " +
    "(abs(PionTriplet_pion2_dz) < " + std::to_string(Dz) + ") && " +
    "(abs(PionTriplet_pion3_dz) < " + std::to_string(Dz) + ")");
  */
}

std::string PlotBus::getBjetVetoString() {
  float vetoVal = 0.5;
  if (bjetVeto)
    return "(Sum$( (Jet_btagDeepB[ CleanJet_jetIdx] > " + std::to_string(vetoVal) + ") && (CleanJet_pt > 20) && (abs(CleanJet_eta) < 2.5)) == 0)";
  else return "1";
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

std::string PlotBus::getSignalWeight() {
  if (stitchSignal)
    // return "(192900*1e-"+PlotBus::getSignalScale()+") * " + stitchSig + ") * (" + stitchMCweight;
    return "(1e"+PlotBus::getSignalScale()+") * " + stitchSig + ") * (" + stitchMCweight;
  else
    // return "( 1 / XSec) * (192900*1e-"+PlotBus::getSignalScale()+") * " + stdMCweight;
    return "(1)";

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
std::string PlotBus::getSelectionCut( std::string extras) {
  if (addCuts == "")
    return ("(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, " +
	    PlotBus::getChargeReqString() + " && " +
	    PlotBus::getTripletCuts() + " && " +
	    PlotBus::getWptString() + " && " +
	    PlotBus::getMaxdRString() + " && " + 
	    PlotBus::getDeepTauString() + " && " +
	    PlotBus::getIsoTrackIsoString() + " && " +
	    PlotBus::getDxyString() + " && " + 
	    PlotBus::getDzString() + " && " + 
	    extras + 
	    "))");
  else
    return ("(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, " +
	    PlotBus::getChargeReqString() + " && " +
	    PlotBus::getTripletCuts() + " && " +
	    PlotBus::getWptString() + " && " +
	    PlotBus::getMaxdRString() + " && " + 
	    PlotBus::getDeepTauString() + " && " +
	    PlotBus::getIsoTrackIsoString() + " && " +
	    PlotBus::getDxyString() + " && " + 
	    PlotBus::getDzString() + " && " + 
	    extras + " && " +
	    PlotBus::getAddCuts() + 
	    "))");
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
	  PlotBus::getDzString() + " && " +
	  PlotBus::getBjetVetoString());
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
	  PlotBus::getDzString() + " && " +
	  PlotBus::getBjetVetoString());
};

std::string PlotBus::getFullCutString() {
  if (addCuts == "")
    return PlotBus::getStdCutString();
  else
    return (PlotBus::getStdCutString() + " && " + PlotBus::getAddCuts());
};

// Overloaded for passing region information
std::string PlotBus::getFullCutString( std::string extras) {
  if (addCuts == "")
    return PlotBus::getStdCutString(extras);
  else
    return (PlotBus::getStdCutString(extras) + " && " + PlotBus::getAddCuts());
};

std::string PlotBus::getCutString( std::string process, std::string region="") {
  // Nominal Situation
  if (region == "") {
    if (manualCutString != "") {
      std::cout << ">>> USING MANUAL CUT STRING" << std::endl;
      if (std::find( signals.begin(), signals.end(), process) != signals.end())
	// if ( process == "signal")
	return ("(" + PlotBus::getSignalWeight() + ") * (" + manualCutString + ")");
      else if ( process == "data")
	return manualCutString;
      return ("(" + weights[process] + ") * (" + manualCutString + ")");
    } else {
      if (std::find( signals.begin(), signals.end(), process) != signals.end())
	return PlotBus::getCutStringSig();
      else if ( process == "data")
	return PlotBus::getFullCutString();
      return ("(" + weights[process] + ") * (" + PlotBus::getFullCutString() + ")");
    }
  } else { // Regions
    if (manualCutString != "") {
      std::cout << ">>> USING MANUAL CUT STRING" << std::endl;
      if (std::find( signals.begin(), signals.end(), process) != signals.end())
	// if ( process == "signal")
	return ("(" + PlotBus::getSignalWeight() + ") * (" + manualCutString + ")");
      else if ( process == "data")
	return ("(" + PlotBus::getSignalWeight() + ") * (" + manualCutString + ")");
	// return manualCutString;
      return ("(" + weights[process] + ") * (" + manualCutString + ")");
    } else {
      if (std::find( signals.begin(), signals.end(), process) != signals.end())
	return PlotBus::getRegionCutSignal( region);
      else if ( process == "data")
	return PlotBus::getRegionCutData( region);
      return PlotBus::getRegionCutMC( region, process);
    }
  }
}

std::string PlotBus::getCutStringSig() {
  return ("(" + PlotBus::getSignalWeight() + ") * (" + PlotBus::getFullCutString() + ")");
};

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
  if (chargereq == 1)
    return RegionTitles[currentRegion];
  else
    return ValRegionTitles[currentRegion];
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
  return ("(" + PlotBus::getSignalWeight() + ") * ( " +
	  PlotBus::getFullCutString(PlotBus::getRegionCut(region)) + " && " +
	  PlotBus::getRegionCut(region) + ")");
};

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
    ControlRegion = true;
    std::cout << ">> Using MUON CONTROL REGION" << std::endl;
    processes   =  {"DY", "DY10", "ST", "TT", "ttV", "VV", "VVV"};
    plotSignal  = false;
    tripletCuts = "(abs(PionTriplet_pdgId) == 13*13*15) && (PionTriplet_trailingIsTrack)";
    eventCuts   = "Trigger_ditau";
    deepTauVsMu = 0;
    
    title    += " Muon CR";
    filename += "_MuonCR";
    if (verbosity > 0) {
      std::cout << "\nIn the muon control region... " << std::endl
		<< "Proccesses : " << PlotBus::getProcesses() << std::endl
		<< "PlotSignal : false" << std::endl
		<< "TripeltCuts: " << tripletCuts << " (muon pgdID = 13)" << std::endl
		<< "EventCuts  : " << eventCuts << " (no lepton veto)" << std::endl
		<< "DeepTauVsMu: None" << std::endl;
    }
  } else
    std::cout << ">> Control region already set... BE CAREFUL" << std::endl;
};

void PlotBus::QCDControlRegion() {
  if (!ControlRegion) {
    ControlRegion = true;
    std::cout << ">> Using QCD CONTROL REGION" << std::endl;
    processes   =  {"QCD", "DY", "DY10", "ST", "TT", "ttV", "VV", "VVV"};
    plotData    = true;
    plotDataSR  = true;
    plotSignal  = true;
    // tripletCuts = "(abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack)";
    // deepTauVsJet = 31;
    chargereq = 3;
    
    title    += " QCD CR";
    filename += "_qcdCR";
    if (verbosity >= 0) {
      std::cout << "\nIn the QCD control region... " << std::endl
		<< "Proccesses  : " << PlotBus::getProcesses() << std::endl
		<< "PlotSignal  : false" << std::endl
	// 		<< "DeepTauVsJet: None" << std::endl
		<< "Charge (|Q|): 3" << std::endl;
    }
  } else
    std::cout << ">> Control region already set... BE CAREFUL" << std::endl;
};

void PlotBus::SetSignalChain( TObject* chain) {
  signalchain = (TChain*)chain;
};

// void PlotBus::SetDataChain( TChain* chain) {
//   datachain = chain;
// };

void PlotBus::UseFullSamples( std::string s="") {
  if (s != "")
    prefix = s;
  else
    prefix = "/Volumes/WineCellar/KState/analysis/";
    
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
    files["data"] = datafiles;
    processes.push_back("data");
  }
}

// Merge samples, but smartly :)
int PlotBus::MergeSamples( std::map<std::string, TH1F*> *phists) {
  if (!mergeSamples)
    return 1;
  // dereference this once here...
  std::map<std::string, TH1F*> &hists = *phists;

  // Do Things
  for (auto const& merger : samplesToMerge) {
    // Merge samples to create a *NEW* process
    if (std::find( processes.begin(), processes.end(), merger.first) == processes.end()) {
      if (verbosity > 0)
	std::cout << ">>> Creating new process: " << merger.first << std::endl;
      // processes.push_back( merger.first);
      if (std::find( processes.begin(), processes.end(), merger.second[0]) != processes.end()) {
	hists[merger.first] = (TH1F*)hists[merger.second[0]]->Clone();
	hists[merger.first]->Reset();
      } else {
	std::cout << ">>> !!!MERGE ERROR: Sample " << merger.second[0] << " did not exist... could not merge" << std::endl;
      }
    }

    // Now we've ensured that there is something to add to 
    for (auto const& sample : merger.second) {
      if (std::find( processes.begin(), processes.end(), sample) != processes.end()) {
	if (verbosity > 0) {
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
    inWeight = "(XSec * " + std::to_string(Luminosity) + " * 1000 * (1/SumOfWeights) * Generator_weight * PUweight * PionTriplet_TauSFweight)";

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
 
// for the extra methods
#include "FillFiles.cc"

#endif
