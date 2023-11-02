// Store analyzers here...
#ifndef ANALYZER_H
#define ANALYZER_H

#include <iostream>
#include <iomanip>

#include "Analyzers.h"

// Do some cut analysis
void analyze( TH1* sighist, float cut) {
  std::cout << "\nAnalyzing Cuts..." << std::endl;
  float cutregionAbove = 0.0, cutregionBelow = 0.0;
  float normal = sighist->Integral( 0, sighist->GetNbinsX()+1);

  cutregionAbove = sighist->Integral( sighist->FindBin(cut), sighist->GetNbinsX()+1);
  cutregionBelow = sighist->Integral( 0, sighist->FindBin(cut));

  std::cout << "Full Region: " << normal << "\n" << std::endl;
  std::cout << "Cut  Region > " << cut << ": " << cutregionAbove << std::endl;
  std::cout << "Sig Eff of >" << cut << " cut: " << cutregionAbove / normal << std::endl;
  
  std::cout << "\nCut  Region < "<< cut << ": " << cutregionBelow << std::endl;
  std::cout << "Sig Eff of <" << cut << " cut: " << cutregionBelow / normal << std::endl;
}

// Get Signal signifigance for each bin
void signalSignifigance( TH1* sighist, THStack* others, PlotBus* pb) {
  std::cout << "Calculating bin significance... " << std::endl;
  if ((!sighist) || (!others)) {
    std::cout << "You've made a HUGE mistake... " << std::endl;
    return;
  }

  TH1F* binSig = new TH1F( (pb->filename+"_binSig").c_str(), "binSig", sighist->GetNbinsX(), -0.5, sighist->GetNbinsX() - 0.5);
  std::vector<float> binSigs;
  float sig = 0, denom = 0;
  for (int i = 0; i < sighist->GetNbinsX(); ++i) {
    float totalOthers = 0;
    for (const auto&& ele : *(others->GetHists()))
      totalOthers += ((TH1D*)ele)->GetBinContent(i);
    denom = (sighist->GetBinContent(i) + totalOthers);
    
    if (denom <= 0)
      sig = 0;
    else
      sig = sighist->GetBinContent(i) / denom;
    
    binSigs.push_back( sig);
    binSig->SetBinContent( i, sig);
    std::cout << "Bin " << i << " Sig: " << sig << std::endl;
  }
  TCanvas* c1 = new TCanvas();
  binSig->Draw("e");
  binSig->SaveAs( (pb->filename + "_binSig.C").c_str());
  c1->SaveAs( (pb->filename + "_binSig.png").c_str());
}

void printYields( std::map<std::string, std::vector<std::string>> yields, int prec, std::string text) {
  // TODO: get maximum length for process, yields, and entries :/
  int offsets[3] = { 20, 10, 7};
  text = (text!="") ? (": " + text) : "";
  std::cout << "    *** Yields Table" << text << " ***" << std::endl;
  std::cout << std::setw(offsets[0]) << std::left
	    << "Process" << ", "
	    << std::setw(offsets[1] + prec) << std::right
	    << "Yield" << ", "
	    << std::setw(offsets[2]) << std::right
	    << "Entries" 
	    << std::endl;
  std::cout << "--------------------------------------------" << std::endl;
  for (auto const& yld : yields) {
    std::cout << std::setw(offsets[0]) << std::left
	      << yld.first << ", "
	      << std::setw(offsets[1] + prec) << std::right
	      << yld.second[0] << ", "
	      << std::setw(offsets[2]) << std::right
	      << yld.second[1]
	      << std::endl;
  }
}

void CalculateYields( std::map<std::string, TH1*> hists, std::map<std::string, std::vector<std::string>>* yields,
		      TLegend* legend, PlotBus* pb, int prec) {
  std::stringstream integ;
  // Loop over only the backgrounds that we want to plot
  for (auto const& hist : hists) {
    if (pb->overflow) {
      integ << std::fixed << std::setprecision( prec) << hist.second->Integral( 0, hist.second->GetNbinsX()+1);
      std::vector<std::string> vec{ integ.str(), std::to_string( (int)hist.second->GetEntries() +
							    (int)hist.second->GetBinContent( hist.second->GetNbinsX()+1))};
      (*yields)[hist.first] = vec;
    } else {
      integ << std::fixed << std::setprecision( prec) << hist.second->GetSumOfWeights();
      std::vector<std::string> vec{ integ.str(), std::to_string( (int)hist.second->GetEntries())};
      (*yields)[hist.first] = vec;
    }

    std::string legendTitle = hist.first;
    if (pb->legendYield)
      legendTitle += " ("+integ.str()+")";

    // Now add to legend
    // TODO: fix this special signal functionality...
    // "W->3#pi, B=10^-"+pb->getSignalScale()
    if (std::find( pb->signals.begin(), pb->signals.end(), hist.first) != pb->signals.end()) {
      legend->AddEntry( hist.second, (legendTitle).c_str(), pb->getSignalFill());
      // legend->AddEntry( hist.second, (legendTitle).c_str(), "f");
    } else if (hist.first == pb->dataName) {
      legend->AddEntry( hist.second, (legendTitle).c_str(),"lep");
    } else {
      legend->AddEntry( hist.second, (legendTitle).c_str(), pb->getHistFill());
    }
    
    // Reset the stringstream
    integ.str( std::string());
  }
}

void getYieldsAndEntries( std::map<std::string, TH1*> hists, TLegend* legend,
			  PlotBus* pb) {
  std::map<std::string, std::vector<std::string>> yields = {};

  if (pb->verbosity > 1) std::cout << ">>> Getting Yields and Entries..." << std::endl;
  int precision = 3;
  CalculateYields( hists, &yields, legend, pb, precision);
  if (pb->verbosity >= 0)
    printYields( yields, precision, pb->currentRegion);
}

#endif
