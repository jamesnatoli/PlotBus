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

// std::map<std::string, TH1*> PlotBus::SimplePlot() {
void PlotBus::SimplePlot() {
  if (variable == "") {
    std::cout << "ERROR! You must plot a variable!" << std::endl;
    throw;
  }
  TCanvas *c1 = new TCanvas("c1", "c1");
  // gErrorIgnoreLevel = kWarning;

  FillFiles();
  if (verbosity > 1) {
    for (auto& f : files) {
      std::cout << "--> " << f.first << std::endl;;
      for (auto s : f.second)
	std::cout << "\t" << s << std::endl;
    }
  }

  // Create Chains
  std::cout << ">>> Making chain" << std::endl;
  std::map<std::string, TChain> chain;
  SetDataChain();
  
  for(std::string proc : processes){
    if (proc != "QCD") {
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

  if (verbosity > 0)
    std::cout << getCutString( dataName, "A") << std::endl;
  
  int icount = 0;
  // #pragma omp parallel for
  for(std::string proc : processes){
    std::cout << ">>> " << std::setw(20) << std::left << proc << std::endl;
    if (proc != "QCD") {
      // #pragma omp parallel for
      for (std::string reg : {"A", "B", "C", "D"}) {
	if ((reg == "A") || doQCD) {
	  UnsetSignalRegionVars();
	  if (verbosity > 1) {
	    std::cout << ">> Drawing: " << (getDrawString( proc, reg, true)).c_str() << std::endl;
	    std::cout << ">> Cutting: " << (getCutString( proc, reg)).c_str() << std::endl;
	  }
	  // TODO: write a PlotBus::Draw() function
	  chain[proc].Draw( (getDrawString( proc, reg)).c_str(), (getCutString( proc, reg)).c_str());
	}
      }
    }
  }

  // TODO: add a protection here, before QCD
  // TODO: simplify this with a GetHist() function too...?
  std::cout << "\n>>> Getting histograms" << std::endl;
  // std::map<std::string, TH1*> hists;
  for (std::string proc : processes) {
    if (proc != "QCD") {
      if (verbosity > 1)
	std::cout << ">>> Getting: " << proc << std::endl;
      if ((proc != dataName) || plotDataSR) {
	hists[proc] = dynamic_cast<TH1*>(gDirectory->Get((proc+"A"+year).c_str()));
      }
    } else {
      // if I stored hists as a member of PlotBus I wouldn't need to return this
      hists[proc] = doQCDestimation(); 
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
    std::cout << "\n>>> Making canvas" << std::endl;
    makeRegionPlot( hists, this, "A");
  }
  
  // return hists;
  return;
}
