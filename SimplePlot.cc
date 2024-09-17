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
#include "PlotUtils.h"

void PlotBus::SimplePlot() {
  if (variable == "") {
    std::cout << "ERROR! You must plot a variable!" << std::endl;
    throw;
  }
  TCanvas *c1 = new TCanvas( ("c1_" + year).c_str(), "c1");
  // gErrorIgnoreLevel = kWarning;

  FillFiles();
  MergeFiles();
  
  if (verbosity > 1) {
    for (auto& f : files) {
      if (std::find( processes.begin(), processes.end(), f.first) != processes.end()) {
	std::cout << "--> " << f.first << std::endl;;
	for (auto s : f.second)
	  std::cout << "\t" << s << std::endl;
      }
    }
  }

  // Create Chains
  // std::cout << "here" << std::endl;
  // SetProcessChain();
  // std::cout << "here!!!" << std::endl;
  
  SetDataChain();
  
  std::map<std::string, TChain> chain;
  for(std::string proc : processes){
    if (proc != "Multijet") {
      chain[proc].SetName("Events");
      for(std::string file : files[proc]){
  	chain[proc].Add((file).c_str());
      }
    } else {
      doQCD = true;
    }
  }
  
  std::cout << ">>> Plotting variable: " << variable
	    << "\n" << std::endl;

  if (verbosity >= 0)
    std::cout << getCutString( dataName, "A") << std::endl;

  std::cout << "\naddCuts: " << addCuts << std::endl;
  
  int icount = 0;
  for (std::string proc : processes){
    if (proc != "Multijet") {
      std::cout << ">>> " << std::setw(20) << std::left << proc << std::endl;
      for (std::string reg : {"A", "B", "C", "D"}) {
	if ((reg == "A") || doQCD) {
	  UnsetSignalRegionVars();
	  if (verbosity > 0) {
	    std::cout << ">> Drawing: " << (getDrawString( proc, reg, true)).c_str() << std::endl;
	    std::cout << ">> Cutting: " << (getCutString( proc, reg)).c_str() << std::endl;
	  }
	  chain[proc].Draw( (getDrawString( proc, reg)).c_str(), (getCutString( proc, reg)).c_str());
	  // DrawProcess( proc, reg);
	}
      }
    }
  }

  // TODO: add a protection here, before QCD
  // TODO: simplify this with a GetHist() function too...?
  // std::map<std::string, TH1*> hists;
  for (std::string proc : processes) {
    if (proc != "Multijet") {
      if (verbosity > 1)
	std::cout << ">>> Getting: " << proc << std::endl;
      if ((proc != dataName) || plotDataSR) {
	hists[proc] = dynamic_cast<TH1*>(gDirectory->Get((proc+"A"+year).c_str()));
      }
    } else {
      doQCDestimation();
    }
  }

  // Sanity Check
  for (auto& proc : hists) {
    if (!proc.second) {
      std::cout << "!!! ERROR !!! Failed to draw " << proc.first << ", exiting" << std::endl;
      throw;
    }
  }

  MergeSamples( &hists);
  if (!justDraw) {
    std::cout << "\n>>> Making Canvas" << std::endl;
    makeRegionPlot( hists, this, "A");
  }
  
  return;
}
