// Store analyzers here...
#ifndef ANALYZER_H
#define ANALYZER_H

#include <iostream>
#include <iomanip>

#include "Analyzers.h"

// Do some cut analysis (not really used)
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

// Get Signal signifigance for each bin (also not really used)
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

#endif
