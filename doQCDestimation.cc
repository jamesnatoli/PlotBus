// Hide this here

#ifndef DOQCDESTIMATION_H
#define DOQCDESTIMATION_H
TH1F* doQCDestimation( PlotBus* pb, std::string binning) {
  std::cout << ">>> Getting: QCD (est)" << std::endl;
  // Need to do this so we can set the values for the region seperately
  pb->UnsetSignalRegionVars();
  
  vector<string> processes     = pb->processes;
  
  // std::cout << ">>> Getting histograms" << std::endl;
  map<string, TH1F*> signalhists;
  map<string, TH1F*> datahists;
  map<string, TH1F*> QCDhists;
  map<string, TH1F*> prochists;
  for (string reg : {"A", "B", "C", "D"}){
    if (pb->verbosity > 0)
      std::cout << ">>> Region: " << reg << std::endl;
    if (!(TH1F*)gDirectory->Get(("data"+reg).c_str())) {
      (pb->datachain).Draw(( pb->variable + ">>procdata" + reg + binning).c_str(), (pb->getCutString( "data", reg)).c_str());
      datahists[reg]   = (TH1F*)gDirectory->Get(("procdata"+reg).c_str());
    }
    for (std::string proc : processes) {
      prochists[proc+"_"+reg] = (TH1F*)gDirectory->Get(("proc"+proc+reg).c_str());
    }
    QCDhists[reg]  = (TH1F*)datahists[reg]->Clone(("QCD_"+reg).c_str());
    QCDhists[reg]->Sumw2();
    
    // Substract out processes (not qcd or signal)
    for(string proc : processes){
      if ((proc != "signal") && (proc != "QCD") && (proc != "data")) {
	if (pb->verbosity > 0)
	  std::cout << "Subbing: " << proc << std::endl;
	QCDhists[reg]->Add(prochists[proc+"_"+reg], -1);
      }
    }
  } // for (string reg : abcd)
    
  // Data Sanity Check
  double dataEntries  = datahists["D"]->GetEntries();
  double dataIntegral = datahists["D"]->Integral(0, (pb->nbins)+1);
  if (dataEntries != dataIntegral) {
    std::cout << "Data Entries not matching integral!!!" << std::endl;
    std::cout << "Data Events in D  : " << datahists["D"]->GetEntries() << std::endl;
    std::cout << "Data Integral in D: " << datahists["D"]->Integral(0, 21) << std::endl;
  }

  if (pb->verbosity > 0)
    std::cout << ">>> Getting extrapolation" << std::endl;
  TH1F* histRatio = (TH1F*)QCDhists["C"]->Clone("Extrapolation ratio");
  histRatio->Divide(QCDhists["D"]);
  
  // Account for bins with zero entries (?)
  for (int b = 0; b < histRatio->GetNbinsX(); ++b) {
    if (pb->verbosity > 1)
      std::cout << "content: " << histRatio->GetBinContent(b) 
		<< ", error  : " << histRatio->GetBinError(b)
		<< std::endl;
    
    if ((histRatio->GetBinContent(b) < 0.0001) || (histRatio->GetBinError(b) < 0.0001))
      histRatio->SetBinError( b, 1);
  }
  if (pb->verbosity > 0)
    histRatio->SaveAs("histRatio.C");

  // ******************
  // *** ESTIMATION ***
  // ******************

  if (pb->verbosity > 0)
    std::cout << ">>> Getting obtained QCD background" << std::endl;
  prochists["QCD"] = (TH1F*)QCDhists["B"]->Clone("QCD");
  
  for (int ibin = 0; ibin < prochists["QCD"]->GetNbinsX(); ++ibin)
    prochists["QCD"]->SetBinContent( ibin, prochists["QCD"]->GetBinContent(ibin) * histRatio->GetBinContent(ibin));
  
  return prochists["QCD"];
}

#endif
