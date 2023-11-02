// These functions are messy so store them here
#ifndef FILL_FILES
#define FILL_FILES

#include <iostream>

#include "PlotBus.h"

void PlotBus::FillFiles( ) {
  SetWeights();
  if (manualFiles) {
    std::cout << "*** Using Manual Files *** " << std::endl;
    for (const auto &sig : signalfiles) {
      for (int i = 0; i < sig.second.size(); ++i)
	std::cout << sig.second[i] << std::endl;
    }
    for (const auto &bkg : bkgfiles) {
      for (int i = 0; i < bkg.second.size(); ++i)
	std::cout << bkg.second[i] << std::endl;
    }
    for (int i = 0; i < datafiles.size(); ++i)
      std::cout << datafiles[i] << std::endl;
    return;
  }
  
  std::cout << ">>> Prefix:  " << prefix << std::endl;
  std::cout << ">>> Era:     " << era << std::endl;
  std::cout << ">>> Channel: " << channel << std::endl;

  for (std::string dtera : PlotBus::dataTakingEras) {
    if (verbosity > 0)
      std::cout << "Adding Data Taking Era: " << dtera << std::endl;
    datafiles.push_back( prefix + era + "/Data/Tau_Run" + year + dtera + "_"  + channel + ".root");
  }
  
  // NLO PRIVATE PRODUCTION
  // BE CAREFUL WITH THE NUMBER OF PARTS, THIS WILL CHANGE FOR FULL SAMPLES
  signalfiles["WJetsTo3Pi_0J"].push_back( prefix + era + "/Wto3pi/SignalW0JetsTo3Pi_" + channel + ".root");
  signalfiles["WJetsTo3Pi_1J"].push_back( prefix + era + "/Wto3pi/SignalW1JetsTo3Pi_" + channel + ".root");
  signalfiles["WJetsTo3Pi_2J"].push_back( prefix + era + "/Wto3pi/SignalW2JetsTo3Pi_" + channel + ".root");
  signalfiles["WJetsTo3Pi_Incl"].push_back( prefix + era + "/Wto3pi/SignalWJetsTo3Pi_" + channel + ".root");
  
  // LEADING ORDER
  signalfiles["Wto3pi_LO"].push_back( prefix + era + "/Wto3pi/SignalWto3pi_" + channel + ".root");
  
  bkgfiles["DY"].push_back( prefix + era + "/DY/DYJetsToLL_M-50_" + channel + ".root");
  bkgfiles["DY"].push_back( prefix + era + "/DY/DY1JetsToLL_M-50_" + channel + ".root");
  bkgfiles["DY"].push_back( prefix + era + "/DY/DY2JetsToLL_M-50_" + channel + ".root");
  bkgfiles["DY"].push_back( prefix + era + "/DY/DY3JetsToLL_M-50_" + channel + ".root");
  bkgfiles["DY"].push_back( prefix + era + "/DY/DY4JetsToLL_M-50_" + channel + ".root");
  bkgfiles["DY10"].push_back( prefix + era + "/DY/DYJetsToLL_M-10to50_" + channel + ".root");
    
  bkgfiles["ST"].push_back( prefix + era + "/ST/ST_t-channel_antitop_" + channel + ".root");
  bkgfiles["ST"].push_back( prefix + era + "/ST/ST_t-channel_top_" + channel + ".root");
  bkgfiles["ST"].push_back( prefix + era + "/ST/ST_tW_antitop_" + channel + ".root");
  bkgfiles["ST"].push_back( prefix + era + "/ST/ST_tW_top_" + channel + ".root");
  bkgfiles["ST"].push_back( prefix + era + "/ST/ST_s-channel_leptonDecays_" + channel + ".root");
  bkgfiles["ST"].push_back( prefix + era + "/ST/ST_s-channel_hadronicDecays_" + channel + ".root");
    
  bkgfiles["TT"].push_back( prefix + era + "/TT/TTTo2L2Nu_" + channel + ".root");
  bkgfiles["TT"].push_back( prefix + era + "/TT/TTToHadronic_" + channel + ".root");
  bkgfiles["TT"].push_back( prefix + era + "/TT/TTToSemiLeptonic_" + channel + ".root");
    
  bkgfiles["ttV"].push_back( prefix + era + "/TTV/TTW_" + channel + ".root");
  bkgfiles["ttV"].push_back( prefix + era + "/TTV/TTZ_" + channel + ".root");

  // Don't need inclusive for Diboson :)
  // bkgfiles["VV"].push_back( prefix + era + "/VV/WW_" + channel + ".root");
  bkgfiles["VV"].push_back( prefix + era + "/VV/WWTo1L1Nu2Q_" + channel + ".root");
  bkgfiles["VV"].push_back( prefix + era + "/VV/WWTo2L2Nu_" + channel + ".root");
  bkgfiles["VV"].push_back( prefix + era + "/VV/WWTo4Q_" + channel + ".root");
    
  // bkgfiles["VV"].push_back( prefix + era + "/VV/WZ_" + channel + ".root");
  bkgfiles["VV"].push_back( prefix + era + "/VV/WZTo1L1Nu2Q_" + channel + ".root");
  bkgfiles["VV"].push_back( prefix + era + "/VV/WZTo1L3Nu_" + channel + ".root");
  bkgfiles["VV"].push_back( prefix + era + "/VV/WZTo2L2Q_" + channel + ".root");
  bkgfiles["VV"].push_back( prefix + era + "/VV/WZTo3L1Nu_" + channel + ".root");

  // bkgfiles["VV"].push_back( prefix + era + "/VV/ZZ_" + channel + ".root");
  bkgfiles["VV"].push_back( prefix + era + "/VV/ZZTo2L2Nu_" + channel + ".root");
  bkgfiles["VV"].push_back( prefix + era + "/VV/ZZTo2L2Q_" + channel + ".root");
  bkgfiles["VV"].push_back( prefix + era + "/VV/ZZTo2Nu2Q_" + channel + ".root");
  bkgfiles["VV"].push_back( prefix + era + "/VV/ZZTo4L_" + channel + ".root");
  bkgfiles["VV"].push_back( prefix + era + "/VV/ZZTo4Q_" + channel + ".root");
    
  bkgfiles["VVV"].push_back( prefix + era + "/VVV/WWW_" + channel + ".root");
  bkgfiles["VVV"].push_back( prefix + era + "/VVV/WWZ_" + channel + ".root");
  bkgfiles["VVV"].push_back( prefix + era + "/VVV/WZZ_" + channel + ".root");
  bkgfiles["VVV"].push_back( prefix + era + "/VVV/ZZZ_" + channel + ".root");

  bkgfiles["W+Jets"].push_back( prefix + era + "/W+Jets/WJetsToLNu_" + channel + ".root");
  bkgfiles["W+Jets"].push_back( prefix + era + "/W+Jets/W0JetsToLNu_" + channel + ".root");
  bkgfiles["W+Jets"].push_back( prefix + era + "/W+Jets/W1JetsToLNu_" + channel + ".root");
  bkgfiles["W+Jets"].push_back( prefix + era + "/W+Jets/W2JetsToLNu_" + channel + ".root");
    
  if (year == "other") {
    // Single Top
    bkgfiles["ST_Top"].push_back( prefix + era + "/ST/ST_t-channel_top_" + channel + ".root");
    bkgfiles["ST_TopUp"].push_back( prefix + era + "/ST/ST_t-channel_top_" + channel + "_TuneUp.root");
    bkgfiles["ST_TopDown"].push_back( prefix + era + "/ST/ST_t-channel_top_" + channel + "_TuneDown.root");
    
    bkgfiles["ST_AntiTop"].push_back( prefix + era + "/ST/ST_t-channel_antitop_" + channel + ".root");
    bkgfiles["ST_AntiTopUp"].push_back( prefix + era + "/ST/ST_t-channel_antitop_" + channel + "_TuneUp.root");
    bkgfiles["ST_AntiTopDown"].push_back( prefix + era + "/ST/ST_t-channel_antitop_" + channel + "_TuneDown.root");

    // TTBar
    bkgfiles["TTTo2L2Nu"].push_back( prefix + era + "/TT/TTTo2L2Nu_" + channel + ".root");
    bkgfiles["TTTo2L2Nu_Up"].push_back( prefix + era + "/TT/TTTo2L2Nu_" + channel + "_TuneUp.root");
    bkgfiles["TTTo2L2Nu_Down"].push_back( prefix + era + "/TT/TTTo2L2Nu_" + channel + "_TuneDown.root");
    
    bkgfiles["TTToSemiLeptonic"].push_back( prefix + era + "/TT/TTToSemiLeptonic_" + channel + ".root");
    bkgfiles["TTToSemiLeptonic_Up"].push_back( prefix + era + "/TT/TTToSemiLeptonic_" + channel + "_TuneUp.root");
    bkgfiles["TTToSemiLeptonic_Down"].push_back( prefix + era + "/TT/TTToSemiLeptonic_" + channel + "_TuneDown.root");

    bkgfiles["TTToHadronic"].push_back( prefix + era + "/TT/TTToHadronic_" + channel + ".root");
    bkgfiles["TTToHadronic_Up"].push_back( prefix + era + "/TT/TTToHadronic_" + channel + "_TuneUp.root");
    bkgfiles["TTToHadronic_Down"].push_back( prefix + era + "/TT/TTToHadronic_" + channel + "_TuneDown.root");
  }

  MergeFiles();
}

// Full Generated Signals (unprocessed)
void PlotBus::FillGenFiles2016() {

  // plot this as data...
  datafiles.push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_012J-RunIISummer20UL16NanoAODv9_part1.root");
  datafiles.push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_012J-RunIISummer20UL16NanoAODv9_part2.root");
  datafiles.push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_012J-RunIISummer20UL16NanoAODv9_part3.root");
  datafiles.push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_012J-RunIISummer20UL16NanoAODv9_part4.root");
  // 0 Jet
  signalfiles["WJetsTo3Pi_0J"].push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_0J-RunIISummer20UL16NanoAODv9_part1.root");
  signalfiles["WJetsTo3Pi_0J"].push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_0J-RunIISummer20UL16NanoAODv9_part2.root");
  // 1 Jet
  signalfiles["WJetsTo3Pi_1J"].push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_1J-RunIISummer20UL16NanoAODv9_part1.root");
  signalfiles["WJetsTo3Pi_1J"].push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_1J-RunIISummer20UL16NanoAODv9_part2.root");
  signalfiles["WJetsTo3Pi_1J"].push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_1J-RunIISummer20UL16NanoAODv9_part3.root");
  // 2 Jet
  signalfiles["WJetsTo3Pi_2J"].push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_2J-RunIISummer20UL16NanoAODv9_part1.root");
  signalfiles["WJetsTo3Pi_2J"].push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_2J-RunIISummer20UL16NanoAODv9_part2.root");
  signalfiles["WJetsTo3Pi_2J"].push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_2J-RunIISummer20UL16NanoAODv9_part3.root");
  signalfiles["WJetsTo3Pi_2J"].push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_2J-RunIISummer20UL16NanoAODv9_part4.root");
  signalfiles["WJetsTo3Pi_2J"].push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_2J-RunIISummer20UL16NanoAODv9_part5.root");
  signalfiles["WJetsTo3Pi_2J"].push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_2J-RunIISummer20UL16NanoAODv9_part6.root");
  signalfiles["WJetsTo3Pi_2J"].push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_2J-RunIISummer20UL16NanoAODv9_part7.root");
  // Inclusive
  signalfiles["WJetsTo3Pi_012J"].push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_012J-RunIISummer20UL16NanoAODv9_part1.root");
  signalfiles["WJetsTo3Pi_012J"].push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_012J-RunIISummer20UL16NanoAODv9_part2.root");
  signalfiles["WJetsTo3Pi_012J"].push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_012J-RunIISummer20UL16NanoAODv9_part3.root");
  signalfiles["WJetsTo3Pi_012J"].push_back( "/Volumes/WineCellar/KState/GenHadded/HIG-WJetsTo3Pi_012J-RunIISummer20UL16NanoAODv9_part4.root");
}

#endif

