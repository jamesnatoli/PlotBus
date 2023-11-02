#include "TCanvas.h"
#include "TChain.h"
#include "TH1F.h"

#include <iostream>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <omp.h>

#include "PlotBus.h"
#include "SimplePlot.h"
#include "PlotUtils.h"

int SimplePlot( PlotBus* pb) {
  // Options
  int numbins     = pb->nbins;
  double lowbin   = pb->lowbin;
  double highbin  = pb->highbin;
  std::string variable = pb->variable;
  TCanvas *c1 = new TCanvas("c1", "c1");
  // gErrorIgnoreLevel = kWarning;

  pb->FillFiles();
  std::map<std::string, std::vector<std::string>> files = pb->files;
  if (pb->verbosity > 1) {
    for (auto& f : files) {
      std::cout << "--> " << f.first << std::endl;;
      for (auto s : f.second)
	std::cout << "\t" << s << std::endl;
    }
  }

  std::cout << ">>> Making chain" << std::endl;
  bool doQCD = false;
  std::map<std::string, TChain> chain;

  // Create Chains
  for(std::string proc : pb->processes){
    if (proc != "QCD") {
      chain[proc].SetName("Events");
      for(std::string file : pb->files[proc]){
	chain[proc].Add((file).c_str());
      }
    } else {
      doQCD = true;
    }
  }

  // Used for QCD!!!
  pb->datachain.SetName("Events");
  for (std::string file : pb->datafiles)
    (pb->datachain).Add((file).c_str());
  
  // std::string binning = "("+std::to_string(numbins)+","+std::to_string(lowbin)+","+std::to_string(highbin)+")";
  std::string binning = pb->getBinning();
  std::cout << ">>> Plotting variable: " << variable
	    << "\n" << std::endl;

  if (pb->verbosity > 0)
    std::cout << pb->getCutString( pb->dataName, "A") << std::endl;
  
  // pb->UnsetSignalRegionVars();
  int icount = 0;
  #pragma omp parallel for
  for(std::string proc : pb->processes){
    std::cout << ">>> " << std::setw(20) << std::left << proc << std::endl;
    if (proc != "QCD") {
      #pragma omp parallel for
      for (std::string reg : {"A", "B", "C", "D"}) {
	if ((reg == "A") || doQCD) {
	  pb->UnsetSignalRegionVars();
	  if (pb->verbosity > 1) {
	    std::cout << (pb->getCutString( proc, reg)).c_str() << std::endl;
	    std::cout << ">> Drawing: " << (pb->getDrawString( proc, reg)).c_str() << std::endl;
	  }
	  // TODO: write a PlotBus::Draw() function
	  chain[proc].Draw( (pb->getDrawString( proc, reg)).c_str(), (pb->getCutString( proc, reg)).c_str());
	  // std::cout << "Total Entries for " << proc << ": " << chain[proc].GetEntries() << std::endl;;
	}
      }
    }
  }

  // TODO: add a protection here, before QCD
  
  std::cout << "\n>>> Getting histograms" << std::endl;
  std::map<std::string, TH1F*> hists;
  for (std::string proc : pb->processes) {
    if (proc != "QCD") {
      if (pb->verbosity > 1)
	std::cout << ">>> Getting: " << proc << std::endl;
      if ((proc != pb->dataName) || pb->plotDataSR) {
	// this is where the name is set
	// if ((TH1F*)gDirectory->Get(("proc"+proc+"A").c_str())) {
	hists[proc] = (TH1F*)gDirectory->Get(("proc"+proc+"A").c_str());
	// } else {
	// std::cout << "!!!ERROR!!! Sample not available: " << proc << std::endl;
	// }
      }
    } else {
      hists[proc] = doQCDestimation( pb, binning);
    }
  }

  // Sanity Check
  for (auto& proc : hists) {
    if (!proc.second) {
      std::cout << "!!! ERROR !!! Failed to draw " << proc.first << ", exiting" << std::endl;
      return 1;
    }
  }
  
  pb->MergeSamples( &hists);
  std::cout << "\n>>> Making canvas" << std::endl;
  makeRegionPlot( hists, pb, "A");
  
  return 0;
}


