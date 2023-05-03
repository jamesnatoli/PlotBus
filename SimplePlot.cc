#include "TROOT.h"
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

  pb->FillFiles( pb->year);
  pb->MergeFiles();
  map<string, vector<string>> files = pb->files;
  map<string, string> bkgsParts{{"DY10", "DY"}}; 

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

  pb->UnsetSignalRegionVars();
  int icount = 0;
  for(string proc : pb->processes){
    icount++;
    std::cout << ">>> "
	      << setw(20) << left
	      << proc+":" << icount << " / " << pb->processes.size()
	      << std::endl;

    if (proc != "QCD") {
      for (std::string reg : {"A", "B", "C", "D"}) {
	if (pb->manualCutString == "") {
	  if (pb->verbosity > 0)
	    std::cout << (pb->getCutString( proc, reg)).c_str() << std::endl;
	  chain[proc].Draw((variable + ">>proc" + proc + reg + binning).c_str(), (pb->getCutString( proc, reg)).c_str());
	} else {
	  std::cout << ">> Using manual cut string:" << std::endl;
	  std::cout << pb->manualCutString << std::endl;
	  chain[proc].Draw((variable + ">>proc" + proc + reg + binning).c_str(), pb->manualCutString.c_str());
	}
      }
    }
  }
  
  std::cout << "\n>>> Getting histograms" << std::endl;
  map<string, TH1F*> hists;
  if (doQCD)
    hists["QCD"] = doQCDestimation( pb, binning);
  for (string proc : pb->processes) {
    if (proc != "QCD") {
      if (pb->verbosity > 0 )
	std::cout << ">>> Getting: " << proc << std::endl;
      hists[proc] = (TH1F*)gDirectory->Get(("proc"+proc+"A").c_str());
    }
  }

  // Add DY10 to DY and then get rid of it (can do this for other bkgs too
  // if ( std::find( pb->procsToStack.begin(), pb->procsToStack.end(), hist.first) != pb->procsToStack.end()) 
  
  for (auto const& bkgpart : bkgsParts) {
    if ( (std::find( pb->processes.begin(), pb->processes.end(), bkgpart.first)  != pb->processes.end()) &&
	 (std::find( pb->processes.begin(), pb->processes.end(), bkgpart.second) != pb->processes.end())) {
      if (pb->verbosity > 0)
	std::cout << ">>> Adding " << bkgpart.first << " to " << bkgpart.second << std::endl;
      hists[bkgpart.second]->Add( hists[bkgpart.first], 1);
      if (pb->verbosity > 0)
	std::cout << ">>> Erasing: " << bkgpart.first << std::endl;      
      hists.erase( bkgpart.first);
    }
  }

  std::cout << ">>> Making canvas" << std::endl;
  makePlot( hists, pb);
  
  return 0;
}


