// Hide this here

#ifndef DOQCDESTIMATION_H
#define DOQCDESTIMATION_H

#include "PlotUtils.h"

TH1F* doQCDestimation( PlotBus* pb, std::string binning) {
  std::cout << ">>> Getting: QCD (est)" << std::endl;
  // Need to do this so we can set the values for the region seperately
  pb->UnsetSignalRegionVars();
  
  std::vector<string> processes     = pb->processes;
  
  // std::cout << ">>> Getting histograms" << std::endl;
  std::map<std::string, TH1F*> datahists;
  std::map<std::string, TH1F*> QCDhists;
  std::map<std::string, TH1F*> hists; // this will have everythig we want to plot...
  
  // *** Try to save some memory here by only saving the histograms that we need...
  for (string reg : {"B", "C", "D", "A"}){
    hists = {}; // reset for every region
    pb->currentRegion = reg;
    if (pb->verbosity > 1)
      std::cout << "\n>>> *** REGION: " << reg << " ***" << std::endl;
    if (!(TH1F*)gDirectory->Get(("procdata"+reg).c_str())) { // data is *usually* not drawn (SR)
      (pb->datachain).Draw(( pb->variable + ">>procdata" + reg + binning).c_str(), (pb->getCutString( "data", reg)).c_str());
      datahists[reg]   = (TH1F*)gDirectory->Get(("procdata"+reg).c_str());
      hists["data"] = datahists[reg];
    } else {
      datahists[reg] = (TH1F*)gDirectory->Get(("procdata"+reg).c_str());
      hists["data"] = datahists[reg];
    }

    QCDhists[reg]  = (TH1F*)datahists[reg]->Clone(("QCD_"+reg).c_str());
    QCDhists[reg]->Sumw2();
    
    for (std::string proc : processes) {
      if (proc != "QCD") {
	hists[proc] = (TH1F*)gDirectory->Get(("proc"+proc+reg).c_str());
	// subtract out processes (not signal or data)
	if ((proc != "signal") && (proc != "data"))
	  QCDhists[reg]->Add(hists[proc], -1);
      }
    }
    
    hists["QCD"] = QCDhists[reg];
    pb->MergeSamples( &hists);
    if (reg != "A" && pb->qcdInfo)
      makeRegionPlot( hists, pb, reg);
  } // for (string reg : abcd)
    
  // Data Sanity Check
  double dataEntries  = datahists["D"]->GetEntries();
  double dataIntegral = datahists["D"]->Integral(0, (pb->nbins)+1);
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

    // do a chi2 comparison between data and prediction (with mc or without?)
  if ( true ) {
    std::cout << ">>> Calculating Chi2... " << std::endl;
    double chi2 = 0;
    for (int ibin = 0; ibin <= QCDhists["A"]->GetNbinsX()+1; ++ibin) {
      double expected = QCDhists["A"]->GetBinContent( ibin);
      for (std::string proc : processes) {
	if (proc != "data") {
	  expected += hists[proc]->GetBinContent( ibin);
	}
      }
      std::cout << "Expected: " << expected << std::endl;
      std::cout << "Observed: " << hists["data"]->GetBinContent(ibin) << std::endl;
      if (expected != 0) {
	chi2 += pow((hists["data"]->GetBinContent(ibin) - expected), 2) / expected;
      }
    }
    std::cout << "Chi Squared: " << chi2 << std::endl;
  } // if (pb->doChi2)
  
  return QCDhists["A"];
}

#endif
