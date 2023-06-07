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
    for (std::string proc : processes)
      hists[proc] = = (TH1F*)gDirectory->Get(("proc"+proc+reg).c_str());
    
    QCDhists[reg]  = (TH1F*)datahists[reg]->Clone(("QCD_"+reg).c_str());
    QCDhists[reg]->Sumw2();
    
    // Substract out processes (not qcd or signal)
    for(string proc : processes){
      if ((proc != "signal") && (proc != "QCD") && (proc != "data")) {
	if (pb->verbosity > 1)
	  std::cout << "Subtracting: " << proc << std::endl;
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

  if (pb->verbosity > -1)
    std::cout << ">>> Getting obtained QCD background" << std::endl;

  // Don't forget about the last bin
  for (int ibin = 0; ibin <= QCDhists["B"]->GetNbinsX()+1; ++ibin)
    QCDhists["A"]->SetBinContent( ibin, QCDhists["B"]->GetBinContent(ibin) * histRatio->GetBinContent(ibin));
  
  return QCDhists["A"];
}

#endif
