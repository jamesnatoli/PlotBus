// Store analyzers here...
#ifndef ANALYZER_H
#define ANALYZER_H

#include <iostream>

#include "Colors.h"
#include "PlotBus.cc"

// Do some cut analysis
void analyze( TH1F *sighist, float cut) {
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

void printYields( std::map<std::string, std::vector<std::string>> yields, std::string text=""){
  // make this prettier?
  text = (text!="") ? (": " + text) : "";
  std::cout << "    *** Yields Table" << text << " ***" << std::endl;
  std::cout << std::setw(15) << std::left
	    << "Process" << ", "
	    << std::setw(10) << std::right
	    << "Yield" << ", "
	    << std::setw(7) << std::right
	    << "Entries" 
	    << std::endl;
  std::cout << "------------------------------------" << std::endl;
  for (auto const& yld : yields) {
    std::cout << std::setw(15) << std::left
	      << yld.first << ", "
	      << std::setw(10) << std::right
	      << yld.second[0] << ", "
	      << std::setw(7) << std::right
	      << yld.second[1]
	      << std::endl;
  }
}

void CalculateYields( std::map<std::string, TH1F*> hists, std::map<std::string, std::vector<std::string>>* yields,
		      TLegend* legend, PlotBus* pb) {
  stringstream integ;
  // Loop over only the backgrounds that we want to plot
  for (auto const& hist : hists) {
    if (pb->overflow) {
      integ << fixed << setprecision(2) << hist.second->Integral( 0, hist.second->GetNbinsX()+1);
      std::vector<std::string> vec{ integ.str(), to_string( (int)hist.second->GetEntries() +
							    (int)hist.second->GetBinContent( hist.second->GetNbinsX()+1))};
      (*yields)[hist.first] = vec;
    } else {
      integ << fixed << setprecision(2) << hist.second->GetSumOfWeights();
      std::vector<std::string> vec{ integ.str(), to_string( (int)hist.second->GetEntries())};
      (*yields)[hist.first] = vec;
    }

    // Now add to legend
    if (hist.first == "signal")
      legend->AddEntry( hist.second, ("W->3#pi, B=10^-"+pb->getSignalScale()+" ("+integ.str()+")").c_str(),"l");
    else if (hist.first == "data") {
      legend->AddEntry( hist.second, (hist.first + " ("+integ.str()+")").c_str(),"lep");
    }
    else
      legend->AddEntry( hist.second, (hist.first + " ("+integ.str()+")").c_str(),"f");

    // Reset the stringstream
    integ.str( std::string());
  }
}

void getYieldsAndEntries( map<string, TH1F*> hists, TLegend* legend,
			  PlotBus* pb) {
  std::map<std::string, std::vector<std::string>> yields = {};

  if (pb->verbosity > 0) std::cout << ">>> Getting Yields and Entries..." << std::endl;
  CalculateYields( hists, &yields, legend, pb);
  if (pb->verbosity >= 0)
    printYields( yields, pb->currentRegion);
}

/*
void getYieldsAndEntries( TH1F* datahist, TH1F* signalhist, map<string, TH1F*> bkghists, TLegend* legend,
			  PlotBus* pb, std::string region) {
  stringstream integ;
  std::map<std::string, std::vector<std::string>> yields = {};
  
  // Add everything together to loop over...
  std::map<string, TH1F*> hists = {};
  for (auto const &bkg : bkghists) {
    std::string proc = bkg.first.substr( 0, bkg.first.find("_"));
    std::string procRegion = bkg.first.substr( bkg.first.find("_")+1);
    if ((procRegion == region) || (proc.find("QCD") != std::string::npos)) {
      hists[proc] = bkg.second;
      hists[proc]->SetFillColor( colors[proc]);
      hists[proc]->SetStats( false);
    }
  }

  hists["Signal"] = signalhist;
  if (datahist)
    hists["Data"] = datahist;

  CalculateYields( hists, &yields, legend, pb);
  if (pb->verbosity > 0)
    printYields( yields, "Region " + region);
}
*/

#endif
