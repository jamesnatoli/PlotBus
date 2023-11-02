#ifndef DOQCDESTIMATION_H
#define DOQCDESTIMATION_H

#include <iostream>
// #include <omp.h>

#include "SimplePlot.h"
#include "PlotUtils.h"

TH1F* doQCDestimation( PlotBus* pb, std::string binning) {
  std::cout << ">>> Getting: QCD (est)" << std::endl;
  // Need to do this so we can set the values for the region seperately
  pb->UnsetSignalRegionVars();
  
  std::vector<std::string> processes = pb->processes;
  
  // std::cout << ">>> Getting histograms" << std::endl;
  std::map<std::string, TH1F*> datahists;
  std::map<std::string, TH1F*> QCDhists;
  std::map<std::string, TH1F*> hists; // this will have everythig we want to plot...
  std::map<std::string, TH1F*> prochists; // in case we merge and don't want to plot everything

  // *** Try to save some memory here by only saving the histograms that we need...
  #pragma omp parallel for
  for (std::string reg : {"B", "C", "D", "A"}){
    hists = {}; // reset for every region
    pb->currentRegion = reg;
    if (pb->verbosity > 1) {
      std::cout << "\n>>> *** REGION: " << reg << " ***" << std::endl;
      std::cout << pb->getCutString( pb->dataName, reg) << std::endl;
    }
    if (!(TH1F*)gDirectory->Get(("procObserved"+reg).c_str())) { // data is *usually* not drawn (SR)
      (pb->datachain).Draw( (pb->getDrawString( pb->dataName, reg)).c_str(), (pb->getCutString( pb->dataName, reg)).c_str());
      // (pb->datachain).Draw(( pb->variable + ">>procObserved" + reg + binning).c_str(), (pb->getCutString( pb->dataName, reg)).c_str());
      datahists[reg]   = (TH1F*)gDirectory->Get(("procObserved"+reg).c_str());
      // add protection here...
      hists[pb->dataName] = datahists[reg];
    } else {
      datahists[reg] = (TH1F*)gDirectory->Get(("procObserved"+reg).c_str());
      hists[pb->dataName] = datahists[reg];
    }

    QCDhists[reg]  = (TH1F*)datahists[reg]->Clone(("QCD_"+reg).c_str());
    QCDhists[reg]->Sumw2();
    
    #pragma omp parallel for 
    for (std::string proc : processes) {
      if (proc != "QCD") {
	if ((TH1F*)gDirectory->Get(("proc"+proc+reg).c_str())) {
	  hists[proc] = (TH1F*)gDirectory->Get(("proc"+proc+reg).c_str());
	  // subtract out processes (not signal or data)
	  if (!(pb->isSignal( proc)) && !(pb->isData(proc))) {
	    if (pb->verbosity > 1)
	      std::cout << ">>> Subtracting: " << proc << std::endl;
	    QCDhists[reg]->Add(hists[proc], -1);
	  }
	} else {
	  std::cout << ">>> Didn't find " << proc << "!" << std::endl;
	  // remove it ??
	}
      }
    }

    hists["QCD"] = QCDhists[reg];

    prochists = hists;
    pb->MergeSamples( &hists);
    // for (auto& h : hists)
    //   std::cout << h.first << ": " << h.second << std::endl;
    if (reg != "A" && pb->qcdInfo) {
      std::cout << "making region plot " << reg << std::endl;
      makeRegionPlot( hists, pb, reg);
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

  if (pb->verbosity > 1)
    std::cout << ">>> Getting extrapolation" << std::endl;
  TH1F* histRatio = (TH1F*)QCDhists["C"]->Clone("Normalization ratio");
  histRatio->Divide(QCDhists["D"]);
  
  // Account for bins with zero entries (?)
  for (int b = 0; b < histRatio->GetNbinsX(); ++b) {
    if ((histRatio->GetBinContent(b) < 0.0001) || (histRatio->GetBinError(b) < 0.0001)) {
      if (pb->verbosity >= 0)
	std::cout << "Bin " << b << " content: " << histRatio->GetBinContent(b) 
		  << ", error  : " << histRatio->GetBinError(b)
		  << std::endl;
      histRatio->SetBinError( b, 1);
      histRatio->SetBinContent( b, 0);
    }
  }

  // Some output stuff...
  if (pb->verbosity > 1) histRatio->SaveAs("histRatio.C");
  if (pb->qcdInfo) makeRatioPlot( histRatio, pb);

  // ******************
  // *** ESTIMATION ***
  // ******************

  if (pb->verbosity > 1)
    std::cout << ">>> Getting obtained QCD background" << std::endl;

  // Don't forget about the last bin
  for (int ibin = 0; ibin <= QCDhists["B"]->GetNbinsX()+1; ++ibin)
    QCDhists["A"]->SetBinContent( ibin, QCDhists["B"]->GetBinContent(ibin) * histRatio->GetBinContent(ibin));

  // TODO: Make this a function which returns the chi2 and draws it on the plot
  // TString xIntString = TString::Format("Intercept =  %.3f", xpos);
  // TLatex TextXint = TLatex();
  // TextXint.SetTextFont(42);
  // TextXint.SetNDC();
  // TextXint.SetTextSize(0.04);
  // TextXint.DrawLatex( 0.62, 0.4, xIntString);
  // do a chi2 comparison between data and prediction (with mc or without?)
  if ( pb->doChi2 ) {
    std::cout << "\n>>> Calculating Chi2... " << std::endl;
    double chi2 = 0;
    for (int ibin = 0; ibin <= QCDhists["A"]->GetNbinsX()+1; ++ibin) {
      double expected = 0;
      if (pb->plotSignal) // prevent errors
	expected = prochists["signal"]->GetBinContent( ibin);
      
      for (std::string proc : processes) {
	if (proc != pb->dataName) {
	  // std::cout << "proc: " << proc << std::endl;
	  expected += prochists[proc]->GetBinContent( ibin);
	}
      }
      if (pb->verbosity > 0) {
	std::cout << "Expected: " << expected << std::endl;
	std::cout << "Observed: " << prochists[pb->dataName]->GetBinContent(ibin) << std::endl;
      }
      if (expected != 0) {
	chi2 += pow((prochists[pb->dataName]->GetBinContent(ibin) - expected), 2) / expected;
      }
    }
    std::cout << "Chi Squared:  " << chi2 << std::endl;
    std::cout << "Chi2 / nbins: " << chi2 / QCDhists["A"]->GetNbinsX() << std::endl;
  } // if (pb->doChi2)
  
  return QCDhists["A"];
}

#endif
