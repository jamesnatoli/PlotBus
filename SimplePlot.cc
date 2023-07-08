// #include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TH1.h"
#include "THStack.h"
#include "TLegend.h"
#include "TF1.h"
#include "TError.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <assert.h> 
#include <iomanip>

#include "Analyzers.h"
#include "PlotUtils.h"
#include "PlotBus.cc"
#include "doQCDestimation.cc"

using namespace std;
int SimplePlot( PlotBus* pb) {
  // Options
  int year        = pb->year;
  int numbins     = pb->nbins;
  double lowbin   = pb->lowbin;
  double highbin  = pb->highbin;
  string variable = pb->variable;
  string filename = pb->filename;
  bool logy       = pb->logy;
  TCanvas *c1 = new TCanvas("c1", "c1");
  pb->xtitle = variable;
  // gErrorIgnoreLevel = kWarning;

  // should I do this in the constructor?
  pb->FillFiles();
  pb->MergeFiles();
  map<string, vector<string>> files = pb->files;

  std::cout << ">>> Making chain" << std::endl;
  bool doQCD = false;
  map<string, TChain> chain;
  for(string proc : pb->processes){
    if (proc != "QCD") {
      chain[proc].SetName("Events");
      for(string file : pb->files[proc]){
	chain[proc].Add((file).c_str());
      }
    } else {
      doQCD = true;
    }
  }
  
  pb->datachain.SetName("Events");
  for (string file : pb->datafiles)
    (pb->datachain).Add((file).c_str());
  
  string binning = "("+to_string(numbins)+","+to_string(lowbin)+","+to_string(highbin)+")";
  std::cout << ">>> Plotting variable: " << variable
	    << "\n" << std::endl;

  // pb->UnsetSignalRegionVars();
  int icount = 0;
  for(string proc : pb->processes){
    icount++;
    std::cout << ">>> "
	      << setw(20) << left
	      << proc+":" << icount << " / " << pb->processes.size()
	      << std::endl;

    if (proc != "QCD") {
      for (std::string reg : {"A", "B", "C", "D"}) {
	if ((reg == "A") || doQCD) {
	  pb->UnsetSignalRegionVars();
	  if (pb->verbosity > 0)
	    std::cout << (pb->getCutString( proc, reg)).c_str() << std::endl;
	  chain[proc].Draw((variable + ">>proc" + proc + reg + binning).c_str(), (pb->getCutString( proc, reg)).c_str());
	}
      }
    }
  }
  
  std::cout << "\n>>> Getting histograms" << std::endl;
  std::map<std::string, TH1F*> hists;
  for (string proc : pb->processes) {
    if (proc != "QCD") {
      if (pb->verbosity > 1)
	std::cout << ">>> Getting: " << proc << std::endl;
      if (proc != "data" || pb->plotDataSR)
	hists[proc] = (TH1F*)gDirectory->Get(("proc"+proc+"A").c_str());
    }
    else
      hists[proc] = doQCDestimation( pb, binning);
  }

  pb->MergeSamples( &hists);
  std::cout << ">>> Making canvas" << std::endl;
  makeRegionPlot( hists, pb, "A");
  
  return 0;
}


