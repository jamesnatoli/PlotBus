#ifndef DOQCDESTIMATION_H
#define DOQCDESTIMATION_H

#include <iostream>
#include <iomanip>

#include "PlotBus.h"
#include "PlotUtils.h"

void PlotBus::doQCDestimation() {
// TH1* PlotBus::doQCDestimation() {
  std::cout << ">>> Multijet (est)" << std::endl;
  // Need to do this so we can set the values for the region seperately
  UnsetSignalRegionVars();
  
  // std::cout << ">>> Getting histograms" << std::endl;
  std::map<std::string, TH1*> datahists = {};
  std::map<std::string, TH1*> QCDhists = {};
  std::map<std::string, std::map<std::string, TH1*>> prochists = {}; // in case we merge and don't want to plot everything

  std::map<std::string, TChain> allchain;
  if (useAllQCD) {
    files = {}; // CLEAR FILES
    std::cout << ">>> Using All Eras to estimate Multijet" << std::endl;
    for (std::string yr : {"2016_preVFP", "2016_postVFP", "2017", "2018"}) {
      if (yr == year) {
	// std::cout << "Skipping already added year: " << year << std::endl;
	continue;
      }
      FillFiles(yr); // NB: THIS MIGHT BE A PROBLEM
    }
    // manually merge
    for (auto proc : processes) {
      files[proc].insert( files[proc].end(), bkgfiles[proc].begin(), bkgfiles[proc].end());
    }
    files[dataName].insert( files[dataName].end(), datafiles.begin(), datafiles.end());
    SetDataChain(); // reset datachain and add the new files

    // create new process chain and add the new files
    for(std::string proc : processes){
      if (proc != "Multijet") {
	allchain[proc].SetName("Events");
	for(std::string file : files[proc]){
	  allchain[proc].Add((file).c_str());
	}
      } else {
	doQCD = true;
      }
    }
  }

  // *** Try to save some memory here by only saving the histograms that we need...
  #pragma omp parallel for
  for (std::string reg : {"B", "C", "D", "A"}) {
    currentRegion = reg;
    if (verbosity > 1) {
      std::cout << "\n>>> *** REGION: " << reg << " ***" << std::endl;
      std::cout << getCutString( dataName, reg) << std::endl;
    }

    // (re)draw data... use 'MJ' to prevent overwrite of existing histogram
    datachain->Draw( (getDrawString( dataName, reg + "_MJ_")).c_str(), (getCutString( dataName, reg)).c_str());
    datahists[reg] = (TH1*)gDirectory->Get(( dataName + reg + "_MJ_" + year).c_str());
    QCDhists[reg]  = (TH1*)datahists[reg]->Clone(("Multijet"+ reg + year).c_str());
    QCDhists[reg]->Sumw2();
    
    if (verbosity > 1)
      std::cout << ">>> Multijet Yield BEFORE subtraction (" << reg << "): " << QCDhists[reg]->GetSumOfWeights() << std::endl;
    #pragma omp parallel for 
    for (std::string proc : processes) {
      if (!(isSignal( proc)) && !(isData(proc)) && (proc != "Multijet")) {
	if ((TH1*)gDirectory->Get((proc + reg + year).c_str())) {
	  if (useAllQCD) {
	    allchain[proc].Draw( (getDrawString( proc, reg + "_ALLERAS_")).c_str(), (getCutString( proc, reg)).c_str());
	    // subtract out processes (not signal or data)
	    if (verbosity > 1)
	      std::cout << ">>> Subtracting: " << proc << " (" << ((TH1*)gDirectory->Get((proc + reg + "_ALLERAS_" + year).c_str()))->GetSumOfWeights() << ")" << std::endl;
	    QCDhists[reg]->Add( (TH1*)gDirectory->Get((proc + reg + "_ALLERAS_" + year).c_str()), -1);
	  } else {
	    prochists[reg][proc] = (TH1*)gDirectory->Get((proc + reg + year).c_str());
	    // subtract out processes (not signal or data)
	    if (!(isSignal( proc)) && !(isData(proc))) {
	      if (verbosity > 1)
		std::cout << ">>> Subtracting: " << proc << std::endl;
	      QCDhists[reg]->Add( prochists[reg][proc], -1);
	    }
	  }
	} else {
	  std::cout << ">>> Didn't find " << proc << "!" << std::endl;
	  // remove it ??
	}
      }
    }
    
    prochists[reg]["Multijet"] = QCDhists[reg];
    
    // I hope this isn't necessary bc it's not working :(
    // MergeSamples( &prochists[reg]);
    if (verbosity > 2)
      getYieldsAndEntries( prochists[reg]);
    if (reg != "A" && qcdInfo) {
      std::cout << ">>> Making region " << reg << " plot" << std::endl;
      prochists[reg][dataName] = datahists[reg];
      makeRegionPlot( prochists[reg], this, reg);
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
      if (verbosity > 0)
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

  if (useAllQCD) {
    std::cout << ">>> QCD Yield (before scale): " << QCDhists["A"]->Integral() << std::endl;
    std::cout << ">>> Scaling Factor: " << (Luminosity / 137.1) << std::endl;
    QCDhists["A"]->Scale( Luminosity / 137.1);
    std::cout << ">>> QCD Yield (after scale): " << QCDhists["A"]->Integral() << std::endl;
  }

  if (doChi2) {
    TH1* prediction = (TH1*)QCDhists["A"]->Clone();
    for (auto&& ele : prochists["A"]) {
      if (!(isSignal(ele.first)) && !(isData(ele.first)) && (ele.first != "Multijet")) { // because it's a Clone of QCD
	if (verbosity > 1) {
	  std::cout << "adding to prediction: " << ele.first << "(" << ele.second->GetSumOfWeights() << ")" << std::endl;
	}
	prediction->Add(ele.second);
      }
    }
    CalcChi2( datahists["A"], prediction);
  }

  hists["Multijet"] = QCDhists["A"];
  // return QCDhists["A"];
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
