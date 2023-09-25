// Header file for Plotbus
#ifndef PLOTBUS_H
#define PLOTBUS_H

// Root Includes
#include "TChain.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"

// C++ Includes
#include <regex>

// Personal Includes

class PlotBus {
public:
  // Constructor
  PlotBus();
  PlotBus( std::string, std::string , int, std::string);
  
  bool logy;
  bool logandlin;
  bool mergeSamples;
  bool manualFiles;
  bool saveHists;
  bool saveCanvas;
  bool plotData;
  bool plotDataSR;
  bool plotSignal;
  bool stitchSignal;
  bool stackSignal;
  bool normalize;
  bool stack;
  bool fillHists;
  bool drawLegend;
  bool doQCD;
  bool overflow;
  bool ControlRegion;
  bool qcdInfo;
  bool doChi2;
  bool DeepTauBinLabels;
  bool getBinSig;
  bool autoRatioLimits;
  bool doRatioDataMC;
  bool doRatioMCData;
  
  int nbins;
  double lowbin, highbin;
  double* bins;
  double ratioLow;
  double ratioHigh;
  
  int verbosity;
  int year;
  bool preVFP;
  bool postVFP;
  Double_t Luminosity;
  std::string era;
  std::string channel;
  std::string filename;
  std::string filepath;
  std::string prefix;
  std::string variable;
  std::string title;
  std::string xtitle;
  std::string addCuts;
  std::string currentRegion;
  std::map<std::string, std::string> RegionTitles;
  std::map<std::string, std::string> ValRegionTitles;

  std::map<std::string, std::vector<std::string>> signalfiles;
  // std::vector<std::string> signalfiles;
  std::vector<std::string> datafiles;
  std::vector<std::string> dataTakingEras;
  std::map<std::string, std::vector<std::string>> files;
  std::map<std::string, std::vector<std::string>> bkgfiles;
    
  int chargereq;
  int deepTauVsEl;
  int deepTauVsMu;
  int deepTauVsJet;
  int Wpt;
  float MaxdR;
  float Dxy;
  float Dz;
  float IsoTrack_iso;
  bool bjetVeto;
  
  int SignalScale;
  std::string manualCutString;
  std::string eventCuts;
  std::string tripletCuts;
  std::string Sigweight;
  std::string stdMCweight;
  std::string DxyDzWeight;
  std::string qcdMCweight;
  std::string stitchMCweight;
  std::string stitchDY;
  std::string stitchWJ;
  std::string stitchSig;
  std::string TTbar_NNLOweight;
  // This allows you to set your own weights, if you want
  std::map< std::string, std::string> weights;
  std::map< std::string, std::string> MCweights;

  std::string SRcut1_scale;
  std::string SRcut2_shape;
  
  std::vector<std::string> bkgsToPlot     = {};
  std::vector<std::string> processes      = {};
  std::vector<std::string> signals        = {};
  std::vector<std::string> procsToStack   = {};
  std::vector<std::string> signalsToStack = {};
  std::vector<float>  analyzeCuts    = {};

  // Samples to Merge
  std::map< std::string, std::string> bkgsParts = {};
  std::map< std::string, std::vector<std::string>> samplesToMerge = {};
  static std::map< std::string, int> colors;
  static std::map< std::string, int> signalcolors;

  // Chains
  TChain* signalchain;
  TChain datachain;
  TChain* processchain;
  // std::map< std::string, TChain> bkgchain;

  // Member Functions
  // Getters
  const char* getvariable()    { return variable.c_str(); };
  const char* getfilename()    { return filename.c_str(); };
  const char* getfilepath()    { return filepath.c_str(); };
  const char* gettitle()       { return title.c_str(); };
  const char* getxtitle()      { return xtitle.c_str(); };
  const char* getAddCuts()     { return addCuts.c_str(); };
  std::string getyear()        { return std::to_string(year); };
  std::string getEventCuts()   { return eventCuts.c_str(); };
  std::string getTripletCuts() { return tripletCuts.c_str(); };
  std::string getSignalScale() { return std::to_string( SignalScale); };

  std::string getDeepTauVsEl();
  std::string getDeepTauVsMu();
  std::string getDeepTauVsJet();
  std::string getDeepTauString();
  std::string getWptString();
  std::string getMaxdRString();
  std::string getDxyString();
  std::string getDzString();
  std::string getBjetVetoString();
  std::string getIsoTrackIsoString();
  std::string getChargeReq() { return std::to_string(chargereq); };
  std::string getChargeReqString();
  std::string getSignalWeight();
  std::string getProcesses();
  std::string getSignals();

  std::string getSelectionCut();
  std::string getStdCutString();
  std::string getFullCutString();

  // Overloaded methods for passing region information
  std::string getSelectionCut(std::string);
  std::string getStdCutString(std::string);
  std::string getFullCutString(std::string);
  
  std::string getCutStringSig();
  std::string getCutString( std::string, std::string);

  std::string getRegionCut( std::string);

  // scale is TrackIso, Shape is DeepTau
  std::string getRegionCutsA()  { return "("  + SRcut1_scale + ") && ("  + SRcut2_shape + ")"; };
  std::string getRegionCutsB()  { return "!(" + SRcut1_scale + ") && ("  + SRcut2_shape + ")"; };
  std::string getRegionCutsC()  { return "("  + SRcut1_scale + ") && !(" + SRcut2_shape + ")"; };
  std::string getRegionCutsD()  { return "!(" + SRcut1_scale + ") && !(" + SRcut2_shape + ")"; };
  std::string getRegionString() { return ("_Reg" + currentRegion).c_str(); };
  std::string getRegionTitle();
  // std::string getRegionTitle()  { return  RegionTitles[currentRegion]; };
  
  std::string getRegionCutData( std::string region);
  std::string getRegionCutSignal( std::string region);
  std::string getRegionCutMC( std::string region, std::string bkg);

  // Setters
  void NoSignalRegion();
  void UnsetSignalRegionVars();
  void MuonControlRegion();
  void QCDControlRegion();
  void SetSignalChain( TObject* chain);
  // void SetDataChain( TChain* chain);
  void UseFullSamples( std::string);

  void MergeFiles();
  void FillFiles();
  int MergeSamples( std::map<std::string, TH1F*> *phists);
  // std::map<std::string, TH1F*> MergeSamples( std::map<std::string, TH1F*> phists);
  void UseNormWeight( std::string inWeight);
};

#include "PlotBus.cc"
#endif
