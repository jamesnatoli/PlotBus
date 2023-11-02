// Header file for Plotbus
#ifndef PLOTBUS_H
#define PLOTBUS_H

// Root Includes
#include "TChain.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"
#include "TStyle.h"

// C++ Includes
#include <regex>
#include <string>

// Personal Includes

class PlotBus {
public:
  // Constructors
  PlotBus() { // default
    Init();
  };
  PlotBus( std::string);
  PlotBus( std::string, std::string , std::string);
  // PlotBus( std::vector<std::string>);
  void Init(); // actually does most of the work
  bool setupYear(std::string);
  
  bool logy;
  bool logandlin;
  bool histErrors;
  bool justDraw;
  bool mergeSamples;
  bool mergeSignals;
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
  bool fillSignal;
  bool usePalette;
  bool drawLegend;
  bool legendYield;
  bool doQCD;
  bool overflow;
  bool ControlRegion;
  bool qcdInfo;
  bool doChi2;
  bool DeepTauBinLabels;
  bool manualBins;
  bool getBinSig;
  bool autoRatioLimits;
  bool doRatioDataMC;
  bool doRatioMCData;
  bool doRatioDataSignal;
  bool doRatioSignalData;
  
  int nbins;
  double lowbin, highbin;
  std::vector<double> bins;
  double ratioLow;
  double ratioHigh;
  
  int verbosity;
  bool preVFP;
  bool postVFP;
  Double_t Luminosity;
  std::string year;
  std::string era;
  std::string channel;
  std::string filename;
  std::string filepath;
  std::string prefix;
  std::string variable;
  std::string title;
  std::string xtitle;
  std::string ytitle;
  std::string addCuts;
  std::string currentRegion;
  std::string basicSelection;
  std::vector<std::string> canvasTags;
  std::map<std::string, std::string> RegionTitles;
  std::map<std::string, std::string> ValRegionTitles;

  std::vector<std::string> datafiles;
  std::vector<std::string> dataTakingEras;
  std::map<std::string, std::vector<std::string>> signalfiles;
  std::map<std::string, std::vector<std::string>> files;
  std::map<std::string, std::vector<std::string>> bkgfiles;

  std::map<std::string, TH1*> hists; // important container...
    
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
  std::string dataWeight;
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

  std::string dataName;
  std::vector<std::string> bkgsToPlot     = {};
  std::vector<std::string> processes      = {};
  std::vector<std::string> signals        = {};
  std::vector<std::string> procsToStack   = {};
  std::vector<std::string> signalsToStack = {};
  std::vector<float>  analyzeCuts    = {};

  // Samples to Merge
  int colorIdx;
  int histFillStyle;
  int signalFillStyle;
  std::string drawingOptions;
  std::map< std::string, std::string> bkgsParts = {};
  std::map< std::string, std::vector<std::string>> samplesToMerge = {};
  static std::map< std::string, int> colors; // defined in Colors.cc
  std::map< std::string, int> paletteColors = {};

  // Chains
  TChain* signalchain;
  TChain* datachain;
  TChain* processchain;
  // std::map< std::string, TChain> bkgchain;

  // Member Functions
  // Getters in Colors.cc
  int getColors( std::string);
  int getHistFillStyle()     { return histFillStyle; };
  int getSignalFillStyle()   { return signalFillStyle; };
  const char* getSignalFill();
  const char* getHistFill();

  // Getters
  bool isData(std::string);
  bool isSignal(std::string);
  bool isData(TObject*);
  bool isSignal(TObject*);
  const char* getxtitle();
  const char* getvariable()    { return variable.c_str(); };
  const char* getfilename()    { return filename.c_str(); };
  const char* getfilepath()    { return filepath.c_str(); };
  const char* gettitle()       { return title.c_str(); };
  const char* getytitle()      { return ytitle.c_str(); };
  const char* getDrawingOpts() { return drawingOptions.c_str(); };
  const char* getAddCuts()     { return ( "&& " + addCuts).c_str(); };
  virtual const char* getTopLabel()    { return ("UL"+getyear()+", "+getLumi().substr(0, 4)+" fb^{-1} (13 TeV)").c_str(); };
  std::string getLumi()        { return std::to_string(Luminosity); };
  virtual std::string getyear()        { return year; };
  std::string getEventCuts()   { return eventCuts.c_str(); };
  std::string getTripletCuts() { return tripletCuts.c_str(); };
  std::string getSignalScale() { return std::to_string( SignalScale); };

  std::string getDeepTauVsEl(  bool=false); // for inverting
  std::string getDeepTauVsMu(  bool=false);
  std::string getDeepTauVsJet( bool=false);
  std::string getDeepTauString();
  std::string getWptString(    bool=false);
  std::string getMaxdRString(  bool=false);
  std::string getDxyString(    bool=false);
  std::string getDzString(     bool=false);
  std::string getBjetVetoString();
  std::string getIsoTrackIsoString();
  std::string getChargeReq() { return std::to_string(chargereq); };
  std::string getChargeReqString();
  std::string getSignalWeight(std::string);
  std::string getProcesses();
  std::string getSignals();
  
  std::string getSelectionCut();
  std::string getStdCutString();
  std::string getFullCutString();

  // Overloaded methods for passing region information
  std::string getSelectionCut(std::string);
  std::string getStdCutString(std::string);
  std::string getFullCutString(std::string);
  
  std::string getCutStringSig( std::string);
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

  std::string getDrawString( std::string, std::string, bool=false);
  std::string getBinning();

  // Setters
  void SetBins( std::vector<double>);
  void AddCuts( std::string);
  void AddCanvasTag( std::string ct) { canvasTags.push_back(ct); };
  void NoSignalRegion();
  void UnsetSignalRegionVars();
  void MuonControlRegion();
  void QCDControlRegion();
  // void SetSignalChain( TObject* chain);
  void SetDataChain();
  void UseFullSamples( std::string s="");
  void setPalette( int);
  // 3744 is a nice hash pattern
  void setHistFillStyle(int); 
  void setSignalFillStyle(int);
  void setDeepTauBinning();

  void SetWeights();
  void MergeFiles();
  void FillFiles();
  void FillGenFiles2016();
  int MergeSamples( std::map<std::string, TH1*>*);
  // std::map<std::string, TH1F*> MergeSamples( std::map<std::string, TH1F*> phists);
  void UseNormWeight( std::string);
  void UseBasicSelection() { manualCutString = basicSelection; };

  // Big Boys in their own files
  // std::map<std::string, TH1*> SimplePlot();
  void SimplePlot();
  TH1* doQCDestimation();
  float CalcChi2(TH1*, TH1*);
};

#endif
