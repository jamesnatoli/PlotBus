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
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>

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
  bool setupYear(std::string, std::string, std::string);
  
  bool logy;
  bool logz;
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
  bool blindData;
  bool plotSignal;
  bool stitchSignal;
  bool stackSignal;
  bool stack;
  bool keepStackOrder;
  bool fillHists;
  bool fillSignal;
  bool usePalette;
  bool drawLegend;
  bool legendYield;
  bool doQCD;
  bool useAllQCD;
  bool overflow;
  bool ControlRegion;
  bool qcdInfo;
  bool doChi2;
  bool DeepTauBinLabels;
  bool manualBins;
  bool twoDimensional;
  bool getBinSig;
  bool autoRatioLimits;
  bool doRatioDataMC;
  bool doRatioMCData;
  bool doRatioDataSignal;
  bool doRatioSignalData;

  // Binning
  int nbins;
  double lowbin, highbin;
  double ratioLow;
  double ratioHigh;
  std::vector<double> bins;
  std::vector<double> bins2D;
  std::vector<double> blindRegion;

  // Plot aesthetics
  int verbosity;
  int precision;
  Double_t Luminosity;
  std::string normalize;
  std::string year;
  std::string era;
  std::string channel;
  std::string filename;
  std::string filepath;
  std::string extfile;
  std::string prefix;
  std::string variable;
  std::string title;
  std::string xtitle;
  std::string ytitle;
  std::string currentRegion;
  std::vector<std::string> canvasTags;
  std::map<std::string, std::string> RegionTitles;
  std::map<std::string, std::string> ValRegionTitles;

  // Files
  std::vector<std::string> datafiles;
  std::vector<std::string> dataTakingEras;
  std::map<std::string, std::vector<std::string>> signalfiles;
  std::map<std::string, std::vector<std::string>> files;
  std::map<std::string, std::vector<std::string>> bkgfiles;

  // Important Container
  std::map<std::string, TH1*> hists;

  // Cuts
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
  std::string addCuts;
  std::string basicSelection;
  std::string manualCutString;
  std::string eventCuts;
  std::string tripletCuts;
  std::string dataWeight;
  std::string stdMCweight;
  std::string DxyDzWeight;
  std::string TauSFweight;
  std::string qcdMCweight;
  std::string stitchMCweight;
  std::string stitchDY;
  std::string stitchDY_LO;
  std::string stitchWJ;
  std::string stitchSig;
  std::string TTbar_NNLOweight;
  // This allows you to set your own weights, if you want
  std::map< std::string, std::string> weights;
  std::map< std::string, std::string> MCweights;

  std::string SRcut1_scale;
  std::string SRcut2_shape;

  std::string dataName;
  std::vector<std::string> bkgsToPlot;
  std::vector<std::string> processes;
  std::vector<std::string> signals;
  std::vector<std::string> procsToStack;
  std::vector<std::string> signalsToStack;
  std::vector<float> analyzeCuts;

  // Samples to Merge
  int colorIdx;
  int histFillStyle;
  int signalFillStyle;
  std::string drawingOptions;
  std::map< std::string, std::string> bkgsParts;
  std::map< std::string, std::vector<std::string>> samplesToMerge;
  static std::map< std::string, int> colors; // defined in Colors.cc
  std::map< std::string, int> paletteColors;

  // Chains
  TChain* signalchain;
  TChain* datachain; // need to be carefull with inheriting pointers
  std::map<std::string, TChain*> processchain;
  // std::map< std::string, TChain> bkgchain;

  // Member Functions

  // Getters
  bool isData(std::string);
  bool isSignal(std::string);
  bool isData(TObject*);
  bool isSignal(TObject*);
  const char* getxtitle();
  const char* getvariable()       { return variable.c_str(); };
  const char* getfilename()       { return filename.c_str(); };
  const char* gettitle()          { return title.c_str(); };
  const char* getytitle()         { return ytitle.c_str(); };
  const char* getDrawingOpts()    { return drawingOptions.c_str(); };
  std::string getfilepath()       { return (filepath + extfile); };
  std::string getAddCuts()        { return (addCuts == "") ? (addCuts) : (" && " + addCuts); };
  std::string getEventCuts()      { return eventCuts.c_str(); };
  std::string getTripletCuts()    { return tripletCuts.c_str(); };
  std::string getSignalScale()    { return std::to_string( SignalScale); };
  std::string getLumi(int prec=1) {
    if (Luminosity > 100)
      prec = 0;
    return (std::stringstream() << std::fixed << std::setprecision(prec) << Luminosity).str();
  };

  virtual std::string getTopLabel() { return ("UL"+getyear()+", "+getLumi(1)+" fb^{-1} (13 TeV)"); };
  virtual std::string getyear() { return year; };

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
  void QCDControlRegion(bool=true);
  void Blind( std::vector<double>);
  // void SetSignalChain( TObject* chain);
  void SetProcessChain();
  void SetDataChain();
  void UseFullSamples( std::string s="");
  void setPalette( int);
  // 3744 is a nice hash pattern
  void setHistFillStyle(int=1001); 
  void setSignalFillStyle(int=1001);
  void setDeepTauBinning();

  // Important Draw() Functions
  void DrawProcess(std::string, std::string);
  void DrawData(std::string);
  
  void MergeFiles();
  void PrintYields(); // overloaded to just print field hists
  void PrintYields( std::map<std::string, std::vector<std::string>>, int, std::string="");
  void CalculateYields( std::map<std::string, TH1*>, std::map<std::string, std::vector<std::string>>*);
  void getYieldsAndEntries( std::map<std::string, TH1*>, TLegend* = 0);
  int MergeSamples( std::map<std::string, TH1*>*);
  void UseNormWeight( std::string);
  void UseBasicSelection() { manualCutString = basicSelection; };

  // ******************************
  // *** Defined in other files ***
  // ******************************
  
  // Getters in Colors.cc
  int getColors( std::string);
  int getHistFillStyle()     { return histFillStyle; };
  int getSignalFillStyle()   { return signalFillStyle; };
  const char* getSignalFill();
  const char* getHistFill();
  
  // FillFiles.cc
  void SetWeights();
  void FillFiles(std::string);
  void FillFiles();
  void FillSignalStitch();
  void FillDYStitch(std::string);
  void FillGenFiles2016();

  // Big Boys in their own files
  void SimplePlot(); // SimplePlot.cc
  void doQCDestimation(); // doQCDestimation.cc
  float CalcChi2(TH1*, TH1*); // doQCDestimation.cc
};

#endif
