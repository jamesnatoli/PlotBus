#ifndef DOQCDESTIMATION_H
#define DOQCDESTIMATION_H

#include <iostream>
#include <iomanip>

#include "PlotBus.h"
#include "PlotUtils.h"

TH1* PlotBus::doQCDestimation() {
  std::cout << ">>> Getting: QCD (est)" << std::endl;
  // Need to do this so we can set the values for the region seperately
  UnsetSignalRegionVars();
  
  // std::cout << ">>> Getting histograms" << std::endl;
  std::map<std::string, TH1*> datahists;
  std::map<std::string, TH1*> QCDhists;
  std::map<std::string, std::map<std::string, TH1*>> prochists; // in case we merge and don't want to plot everything

  // *** Try to save some memory here by only saving the histograms that we need...
  #pragma omp parallel for
  for (std::string reg : {"B", "C", "D", "A"}){
    currentRegion = reg;
    if (verbosity > 1) {
      std::cout << "\n>>> *** REGION: " << reg << " ***" << std::endl;
      std::cout << getCutString( dataName, reg) << std::endl;
    }
    if (!(TH1*)gDirectory->Get((dataName + reg + year).c_str())) { // data is *usually* not drawn (SR)
      datachain->Draw( (getDrawString( dataName, reg)).c_str(), (getCutString( dataName, reg)).c_str());
      datahists[reg]   = (TH1*)gDirectory->Get(( dataName + reg + year).c_str());
      // add protection here...
    } else {
      datahists[reg] = (TH1*)gDirectory->Get(( dataName + reg + year).c_str());
    }
    QCDhists[reg]  = (TH1*)datahists[reg]->Clone(("QCD_"+reg).c_str());
    QCDhists[reg]->Sumw2();
    
    #pragma omp parallel for 
    for (std::string proc : processes) {
      if (proc != "QCD") {
	if ((TH1*)gDirectory->Get((proc + reg + year).c_str())) {
	  prochists[reg][proc] = (TH1*)gDirectory->Get((proc + reg + year).c_str());
	  // subtract out processes (not signal or data)
	  if (!(isSignal( proc)) && !(isData(proc))) {
	    if (verbosity > 1)
	      std::cout << ">>> Subtracting: " << proc << std::endl;
	    QCDhists[reg]->Add( prochists[reg][proc], -1);
	  }
	} else {
	  std::cout << ">>> Didn't find " << proc << "!" << std::endl;
	  // remove it ??
	}
      }
    }

    prochists[reg]["QCD"] = QCDhists[reg];
    MergeSamples( &prochists[reg]);
    if (reg != "A" && qcdInfo) {
      std::cout << ">> Making region " << reg << " plot" << std::endl;
      makeRegionPlot( hists, this, reg);
    }
  } // for (string reg : abcd)
  
  // Data Sanity Check
  double dataEntries  = datahists["D"]->GetEntries();
  double dataIntegral = datahists["D"]->Integral(0, datahists["D"]->GetNbinsX()+1);
  if (dataEntries != dataIntegral) {
    std::cout << "Data Entries not matching integral!!!" << std::endl;
    std::cout << "Data Events in D  : " << datahists["D"]->GetEntries() << std::endl;
    std::cout << "Data Integral in D: " << datahists["D"]->Integral(0, datahists["D"]->GetNbinsX()+1) << std::endl;
  }

  if (verbosity > 1)
    std::cout << ">>> Getting extrapolation" << std::endl;
  TH1* histRatio = (TH1*)QCDhists["C"]->Clone("Normalization ratio");
  histRatio->Divide(QCDhists["D"]);
  
  // Account for bins with zero entries (?)
  for (int b = 0; b < histRatio->GetNbinsX(); ++b) {
    if ((histRatio->GetBinContent(b) < 0.0001) || (histRatio->GetBinError(b) < 0.0001)) {
      if (verbosity >= 0)
	std::cout << "Bin " << b << " content: " << histRatio->GetBinContent(b) 
		  << ", error  : " << histRatio->GetBinError(b)
		  << std::endl;
      histRatio->SetBinError( b, 1);
      histRatio->SetBinContent( b, 0);
    }
  }

  // Some output stuff...
  if (verbosity > 1) histRatio->SaveAs("histRatio.C");
  if (qcdInfo) makeRatioPlot( histRatio, this);

  // ******************
  // *** ESTIMATION ***
  // ******************

  if (verbosity > 1)
    std::cout << ">>> Getting obtained QCD background" << std::endl;

  // Don't forget about the last bin
  for (int ibin = 0; ibin <= QCDhists["B"]->GetNbinsX()+1; ++ibin)
    QCDhists["A"]->SetBinContent( ibin, QCDhists["B"]->GetBinContent(ibin) * histRatio->GetBinContent(ibin));

  TH1* prediction = (TH1*)QCDhists["A"]->Clone();
  for (auto&& ele : prochists["A"]) {
    if (!(isSignal(ele.first)) && !(isData(ele.first)) && (ele.first != "QCD")) { // because it's a Clone of QCD
      if (verbosity > 1) {
	std::cout << "adding to prediction: " << ele.first << "(" << ele.second->GetSumOfWeights() << ")" << std::endl;
      }
      prediction->Add(ele.second);
    }
  }
  if (doChi2) CalcChi2( datahists["A"], prediction);
  
  return QCDhists["A"];
}

// Do a chi2 comparison between data and prediction (with mc or without?)
float PlotBus::CalcChi2( TH1* data, TH1* prediction) {
    std::cout << "\n>>> Calculating Chi2... " << std::endl;
    double chi2 = 0;
    int nonzerobins = 0;
    for (int ibin = 0; ibin <= data->GetNbinsX()+1; ++ibin) {
      if (data->GetBinContent(ibin) > 0) {
	++nonzerobins;
	chi2 += pow((prediction->GetBinContent(ibin) - data->GetBinContent(ibin)), 2) / data->GetBinContent(ibin);
	if (verbosity > 1) {
	  std::cout << "** Bin " << ibin << " ** " << std::endl;
	  std::cout << "Observed:  " << data->GetBinContent(ibin) << std::endl;
	  std::cout << "Predicted: " << prediction->GetBinContent(ibin) << "\n" << std::endl;
	  std::cout << "Bin " << ibin << " Chi2: " << chi2 << std::endl;
	}
      }
    }
    
    std::cout << "\n   *** Chi2 Calculation ***" << std::endl;
    std::cout << "\tChi Squared:  " << chi2 << std::endl;
    std::cout << "\tChi2 / nbins: " << (chi2 / nonzerobins) << std::endl;
    AddCanvasTag( "#chi^{2} / dof = " +
		  (std::stringstream() << std::fixed << std::setprecision(2) << chi2).str() +
		  " / " + std::to_string(nonzerobins));
    
  return chi2;
}

#endif
