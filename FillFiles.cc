// These functions are messy so store them here
#ifndef FILL_FILES
#define FILL_FILES

#include "PlotBus.cc"

void PlotBus::FillFiles( ) {
  std::cout << ">>> Prefix:  " << prefix << std::endl;
  std::cout << ">>> Era:     " << era << std::endl;
  std::cout << ">>> Channel: " << channel << std::endl;
  
  if (year == 2018) {
    std::cout << "here" << std::endl;
    signalfiles.push_back( prefix + era +"/Wto3pi/SignalWto3pi_" + channel + ".root");
    datafiles.push_back( prefix + era + "/Data/Tau_Run2018A_" + channel + ".root");
    datafiles.push_back( prefix + era + "/Data/Tau_Run2018B_" + channel + ".root");
    datafiles.push_back( prefix + era + "/Data/Tau_Run2018C_" + channel + ".root");
    datafiles.push_back( prefix + era + "/Data/Tau_Run2018D_" + channel + ".root");
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
    // bkgfiles["ST"].push_back( prefix + era + "/ST/ST_t-channel_top_TuneUp_" + channel + ".root");
    // bkgfiles["ST"].push_back( prefix + era + "/ST/ST_t-channel_top_TuneDown_" + channel + ".root");
    // bkgfiles["ST"].push_back( prefix + era + "/ST/ST_t-channel_antitop_TuneUp_" + channel + ".root");
    // bkgfiles["ST"].push_back( prefix + era + "/ST/ST_t-channel_antitop_TuneDown_" + channel + ".root");
    bkgfiles["ST"].push_back( prefix + era + "/ST/ST_s-channel_leptonDecays_" + channel + ".root");
    bkgfiles["ST"].push_back( prefix + era + "/ST/ST_s-channel_hadronicDecays_" + channel + ".root");
    
    bkgfiles["TT"].push_back( prefix + era + "/TT/TTTo2L2Nu_" + channel + ".root");
    bkgfiles["TT"].push_back( prefix + era + "/TT/TTToHadronic_" + channel + ".root");
    bkgfiles["TT"].push_back( prefix + era + "/TT/TTToSemiLeptonic_" + channel + ".root");
    // bkgfiles["TT"].push_back( prefix + era + "/TT/TTToSemiLeptonic_TuneUp_" + channel + ".root");
    // bkgfiles["TT"].push_back( prefix + era + "/TT/TTToSemiLeptonic_TuneDown_" + channel + ".root");
    // bkgfiles["TT"].push_back( prefix + era + "/TT/TTTo2L2Nu_TuneUp_" + channel + ".root");
    // bkgfiles["TT"].push_back( prefix + era + "/TT/TTTo2L2Nu_TuneDown_" + channel + ".root");
    
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

    // bkgfiles["W+Jets"].push_back("~/KSTATE/Research/Wto3pi/ROOT/FullW+JetsSamples/WJetsToLNu_Wto3pi_postfix2_2018.root");
    // bkgfiles["W+Jets"].push_back("~/KSTATE/Research/Wto3pi/ROOT/FullW+JetsSamples/W0JetsToLNu_Wto3pi_postfix2_2018.root");
    // bkgfiles["W+Jets"].push_back("~/KSTATE/Research/Wto3pi/ROOT/FullW+JetsSamples/W1JetsToLNu_Wto3pi_postfix2_2018.root");
    // bkgfiles["W+Jets"].push_back("~/KSTATE/Research/Wto3pi/ROOT/FullW+JetsSamples/W2JetsToLNu_Wto3pi_postfix2_2018.root");
    bkgfiles["W+Jets"].push_back( prefix + era + "/W+Jets/WJetsToLNu_" + channel + ".root");
    bkgfiles["W+Jets"].push_back( prefix + era + "/W+Jets/W0JetsToLNu_" + channel + ".root");
    bkgfiles["W+Jets"].push_back( prefix + era + "/W+Jets/W1JetsToLNu_" + channel + ".root");
    bkgfiles["W+Jets"].push_back( prefix + era + "/W+Jets/W2JetsToLNu_" + channel + ".root");
    
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_HT50to100_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_HT100to200_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_HT200to300_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_HT300to500_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_HT500to700_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_HT700to1000_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_HT1000to1500_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_HT1500to2000_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_HT2000toInf_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt15to30_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt30to50_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt50to80_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt80to120_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt120to170_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt170to300_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt300to470_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt470to600_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt600to800_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt800to1000_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt1000to1400_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt1400to1800_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt1800to2400_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt2400to3200_" + channel + ".root");
    // bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt3200toInf_" + channel + ".root");

  } else if (year == 2017) {
    signalfiles.push_back( prefix + era + "/Wto3pi/SignalWto3pi_Wto3pi_almostfull_v2_2017.root");
    datafiles.push_back( prefix + era + "/Data/Tau_Run2017B_Wto3pi_almostfull_v2_2017.root");
    datafiles.push_back( prefix + era + "/Data/Tau_Run2017C_Wto3pi_almostfull_v2_2017.root");
    datafiles.push_back( prefix + era + "/Data/Tau_Run2017D_Wto3pi_almostfull_v2_2017.root");
    datafiles.push_back( prefix + era + "/Data/Tau_Run2017E_Wto3pi_almostfull_v2_2017.root");
    datafiles.push_back( prefix + era + "/Data/Tau_Run2017F_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["DY"].push_back( prefix + era + "/DY/DYJetsToLL_M-50_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["DY"].push_back( prefix + era + "/DY/DY1JetsToLL_M-50_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["DY"].push_back( prefix + era + "/DY/DY2JetsToLL_M-50_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["DY"].push_back( prefix + era + "/DY/DY3JetsToLL_M-50_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["DY"].push_back( prefix + era + "/DY/DY4JetsToLL_M-50_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["DY10"].push_back( prefix + era + "/DY/DYJetsToLL_M-10to50_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["ST"].push_back( prefix + era + "/ST/ST_t-channel_antitop_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["ST"].push_back( prefix + era + "/ST/ST_t-channel_top_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["ST"].push_back( prefix + era + "/ST/ST_tW_antitop_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["ST"].push_back( prefix + era + "/ST/ST_tW_top_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["TT"].push_back( prefix + era + "/TT/TTTo2L2Nu_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["TT"].push_back( prefix + era + "/TT/TTToHadronic_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["TT"].push_back( prefix + era + "/TT/TTToSemiLeptonic_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["ttV"].push_back( prefix + era + "/TTV/TTW_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["ttV"].push_back( prefix + era + "/TTV/TTZ_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["VV"].push_back( prefix + era + "/VV/WW_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["VV"].push_back( prefix + era + "/VV/WZ_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["VV"].push_back( prefix + era + "/VV/ZZ_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["VVV"].push_back( prefix + era + "/VVV/WWW_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["VVV"].push_back( prefix + era + "/VVV/WWZ_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["VVV"].push_back( prefix + era + "/VVV/WZZ_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["VVV"].push_back( prefix + era + "/VVV/ZZZ_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["W+Jets"].push_back( prefix + era + "/W+Jets/WJetsToLNu_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["W+Jets"].push_back( prefix + era + "/W+Jets/W0JetsToLNu_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["W+Jets"].push_back( prefix + era + "/W+Jets/W1JetsToLNu_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["W+Jets"].push_back( prefix + era + "/W+Jets/W2JetsToLNu_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_HT50to100_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_HT100to200_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_HT200to300_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_HT300to500_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_HT500to700_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_HT700to1000_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_HT1000to1500_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_HT1500to2000_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_HT2000toInf_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt15to30_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt30to50_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt50to80_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt80to120_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt120to170_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt170to300_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt300to470_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt470to600_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt600to800_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt800to1000_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt1000to1400_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt1400to1800_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt1800to2400_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt2400to3200_Wto3pi_almostfull_v2_2017.root");
    bkgfiles["QCD MC"].push_back( prefix + era + "/QCD/QCD_Pt3200toInf_Wto3pi_almostfull_v2_2017.root");
  } else if (year == 9999) {
    channel = "Wto3pi_2018";

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
}

#endif

// std::cout << "YOU ARE DOING SOMETHING DUMB" << std::endl;
//     signalfiles.push_back( prefix + era + "Wto3pi/SignalWto3pi_Wto3pi_almostfull_2018.root");
//     datafiles.push_back( prefix + era + "Data/Tau_Run2018A_Wto3pi_almostfull_2018.root");
//     datafiles.push_back( prefix + era + "Data/Tau_Run2018B_Wto3pi_almostfull_2018.root");
//     datafiles.push_back( prefix + era + "Data/Tau_Run2018C_Wto3pi_almostfull_2018.root");
//     datafiles.push_back( prefix + era + "Data/Tau_Run2018D_Wto3pi_almostfull_2018.root");
//     bkgfiles["DY"].push_back( prefix + era + "DY/DYJetsToLL_M-50_Wto3pi_almostfull_2018.root");
//     bkgfiles["DY"].push_back( prefix + era + "DY/DY1JetsToLL_M-50_Wto3pi_almostfull_2018.root");
//     bkgfiles["DY"].push_back( prefix + era + "DY/DY2JetsToLL_M-50_Wto3pi_almostfull_2018.root");
//     bkgfiles["DY"].push_back( prefix + era + "DY/DY3JetsToLL_M-50_Wto3pi_almostfull_2018.root");
//     bkgfiles["DY"].push_back( prefix + era + "DY/DY4JetsToLL_M-50_Wto3pi_almostfull_2018.root");
//     bkgfiles["DY10"].push_back( prefix + era + "DY/DYJetsToLL_M-10to50_Wto3pi_almostfull_2018.root");
//     bkgfiles["ST"].push_back( prefix + era + "ST/ST_t-channel_antitop_Wto3pi_almostfull_2018.root");
//     bkgfiles["ST"].push_back( prefix + era + "ST/ST_t-channel_top_Wto3pi_almostfull_2018.root");
//     bkgfiles["ST"].push_back( prefix + era + "ST/ST_tW_antitop_Wto3pi_almostfull_2018.root");
//     bkgfiles["ST"].push_back( prefix + era + "ST/ST_tW_top_Wto3pi_almostfull_2018.root");
//     bkgfiles["TT"].push_back( prefix + era + "TT/TTTo2L2Nu_Wto3pi_almostfull_2018.root");
//     bkgfiles["TT"].push_back( prefix + era + "TT/TTToHadronic_Wto3pi_almostfull_2018.root");
//     bkgfiles["TT"].push_back( prefix + era + "TT/TTToSemiLeptonic_Wto3pi_almostfull_2018.root");
//     bkgfiles["ttV"].push_back( prefix + era + "TTV/ttWJets_Wto3pi_almostfull_2018.root");
//     bkgfiles["ttV"].push_back( prefix + era + "TTV/ttZJets_Wto3pi_almostfull_2018.root");
//     bkgfiles["VV"].push_back( prefix + era + "VV/WW_Wto3pi_almostfull_2018.root");
//     bkgfiles["VV"].push_back( prefix + era + "VV/WZ_Wto3pi_almostfull_2018.root");
//     bkgfiles["VV"].push_back( prefix + era + "VV/ZZ_Wto3pi_almostfull_2018.root");
//     bkgfiles["VVV"].push_back( prefix + era + "VVV/WWW_Wto3pi_almostfull_2018.root");
//     bkgfiles["VVV"].push_back( prefix + era + "VVV/WWZ_Wto3pi_almostfull_2018.root");
//     bkgfiles["VVV"].push_back( prefix + era + "VVV/WZZ_Wto3pi_almostfull_2018.root");
//     bkgfiles["VVV"].push_back( prefix + era + "VVV/ZZZ_Wto3pi_almostfull_2018.root");
//     bkgfiles["W+Jets"].push_back( prefix + era + "W+Jets/WJetsToLNu_Wto3pi_almostfull_2018.root");
//     bkgfiles["W+Jets"].push_back( prefix + era + "W+Jets/W1JetsToLNu_Wto3pi_almostfull_2018.root");
//     bkgfiles["W+Jets"].push_back( prefix + era + "W+Jets/W2JetsToLNu_Wto3pi_almostfull_2018.root");
//     bkgfiles["W+Jets"].push_back( prefix + era + "W+Jets/W3JetsToLNu_Wto3pi_almostfull_2018.root");
//     bkgfiles["W+Jets"].push_back( prefix + era + "W+Jets/W4JetsToLNu_Wto3pi_almostfull_2018.root");
//     bkgfiles["QCD"].push_back( prefix + era + "QCD/QCD_HT50to100_Wto3pi_almostfull_2018.root");
//     bkgfiles["QCD"].push_back( prefix + era + "QCD/QCD_HT100to200_Wto3pi_almostfull_2018.root");
//     bkgfiles["QCD"].push_back( prefix + era + "QCD/QCD_HT200to300_Wto3pi_almostfull_2018.root");
//     bkgfiles["QCD"].push_back( prefix + era + "QCD/QCD_HT300to500_Wto3pi_almostfull_2018.root");
//     bkgfiles["QCD"].push_back( prefix + era + "QCD/QCD_HT500to700_Wto3pi_almostfull_2018.root");
//     bkgfiles["QCD"].push_back( prefix + era + "QCD/QCD_HT700to1000_Wto3pi_almostfull_2018.root");
//     bkgfiles["QCD"].push_back( prefix + era + "QCD/QCD_HT1000to1500_Wto3pi_almostfull_2018.root");
//     bkgfiles["QCD"].push_back( prefix + era + "QCD/QCD_HT1500to2000_Wto3pi_almostfull_2018.root");
//     bkgfiles["QCD"].push_back( prefix + era + "QCD/QCD_HT2000toInf_Wto3pi_almostfull_2018.root");

// Stitching Weights
// additionalWeights["DY"] = "(LHE_Njets==0?1.83563:1)*(LHE_Njets==1?0.640449:1)*(LHE_Njets==2?0.491338:1)*(LHE_Njets==3?0.233073:1)*(LHE_Njets==4?0.263251:1)*(LHE_Njets>4?1.83563:1)";
// additionalWeights["W+Jets"] = "(LHE_Njets==0?3.0896:1)*(LHE_Njets==1?1.70867:1)*(LHE_Njets==2?1.78251:1)*(LHE_Njets==3?1.35992:1)*(LHE_Njets==4?0.000406113:1)*(LHE_Njets>4?3.0896:1)";  
