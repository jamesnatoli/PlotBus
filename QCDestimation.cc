#ifndef QCD_ESTIMATION
#define QCD_ESTIMATION

#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TH1.h"
#include "THStack.h"
#include "TLegend.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TStyle.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <assert.h> 
#include <iomanip>

#include "Analyzers.h"
#include "PlotUtils.h"
#include "PlotBus.cc"

using namespace std;

int QCDestimation( PlotBus* pb) {

  // Options
  /*
  string eventcuts = "(HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg) && (Sum$(abs(Lepton_pdgId)==15) == Length$(Lepton_pdgId))";
  string tripletcuts = "(abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)";
  string selectioncut = "(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, "+tripletcuts+"))";
  string MCweights = "XSecMCweight * PUweight"; //  * Generator_weight

  string SRcut1 = "(PionTriplet_LowestDeepTauVsJet >= 31)"; // Medium WP
  string SRcut2 = "(PionTriplet_pt>40)"; */

  int numbins     = pb->nbins;
  double lowbin   = pb->lowbin;
  double highbin  = pb->highbin;
  string variable = pb->variable;
  string filename = pb->filename;
  bool logy       = pb->logy;
  pb->xtitle = "Inv. W boson mass [GeV]";

  // Need to do this so we can set the values for the region seperately
  pb->UnsetSignalRegionVars();

  vector<string> signalfiles;
  vector<string> datafiles;
  map<string, vector<string>> bkgfiles;
  
  vector<string> bkgs     = pb->bkgs;
  vector<string> bkgsPlot = pb->bkgsToPlot;

  // We do this because DY10 needs a different weight than the rest of DY (no stitching)
  map<string, string> bkgsParts{{"DY10", "DY"}}; // {"Part of bkg...", "...belonging to this main bkg"}
  for (auto const& bkgpart : bkgsParts){
    // Now DY10 is in bkgs, and it points to bkgsParts?
    bkgs.push_back(bkgpart.first);
  }
  map<string, string> additionalWeights;

  // Get file names
  pb->FillFiles( pb->year);

  cout << "Making chain" << endl;
  TChain datachain("Events");
  TChain signalchain("Events");
  for(string sigfile : pb->signalfiles){
    signalchain.Add((sigfile).c_str());
  }
  // pb->SetSignalChain( signalchain.Clone());
  
  for(string datafile : pb->datafiles){
    datachain.Add((datafile).c_str());
  }
  // pb->SetDataChain( datachain.Clone());
  
  map<string, TChain> bkgchain;
  for(string bkg : bkgs){
    bkgchain[bkg].SetName("Events");
    for(string bkgfile : pb->bkgfiles[bkg]){
      bkgchain[bkg].Add((bkgfile).c_str());
    }
  }
  // pb->bkgchain = bkgchain;

  string binning = "("+to_string(numbins)+","+to_string(lowbin)+","+to_string(highbin)+")";
  cout << "Plotting variable: " << variable
       << "\n" << endl;
  
  cout << "Standard Cuts: " << endl;
  cout << pb->getStdCutString() << "\n" << std::endl;
  // cout << selectioncut+"&&"+eventcuts+"&&"+tripletcuts << "\n" << endl;

  cout << "Additional Cuts: " << endl;
  cout << pb->getAddCuts() << "\n" << std::endl;
  // cout << addcuts << "\n" << endl;

  if (pb->verbosity > 0) 
    cout << "Signal Cut String: " << endl
	 << pb->getCutStringSig() << std::endl;
  // cout << "("+Sigweights+")*"+selectioncut+"&&"+eventcuts+"&&"+tripletcuts+"&&"+addcuts << endl;
  // cout << selectioncut+"&&"+eventcuts+"&&"+tripletcuts+"&&"+addcuts << "\n" << endl;
  
  // Print the Regions
  if (pb->verbosity > -1) {
    cout << "\nRegion A (Signal):" << endl;
    cout << "("+pb->SRcut1_scale+")  &&  ("+pb->SRcut2_shape+")" << endl;
    cout << "Region B (Shape):" << endl;
    cout << "!("+pb->SRcut1_scale+") &&  ("+pb->SRcut2_shape+")" << endl;
    cout << "Region C (Norm Numerator):" << endl;
    cout << "("+pb->SRcut1_scale+")  && !("+pb->SRcut2_shape+")" << endl;
    cout << "Region D (Norm Denominator):" << endl;
    cout << "!("+pb->SRcut1_scale+") && !("+pb->SRcut2_shape+")" << endl;
  }
  
  cout << "\nApplying cuts\n" << endl;
  // _A: Signal region, this is what we want
  // _B: Invert iso cut (SRcut1_scale): This is where we get the SHAPE from. For the NORMALIZATION, we add ratio of integrals "_C"/"_D".
  // _C: Invert Wpt (SRcut2_shape)
  // _D: Invert Wpt AND iso cut
  vector<string> abcd{"A", "B", "C", "D"};
  vector<string> bcd{"B", "C", "D"};
  
  string addWeight;

  for (string reg : abcd) {
    if (pb->verbosity > 0)
      std::cout << "Region Cut Data: " << reg << std::endl
		<< pb->getRegionCutData(reg) << std::endl;
    
    signalchain.Draw(("PionTriplet_MassInv>>signal"+reg+binning).c_str(), (pb->getRegionCutSignal(reg)).c_str());
    datachain.Draw(("PionTriplet_MassInv>>data"+reg+binning).c_str(), (pb->getRegionCutData(reg)).c_str());
  }

  int icount = 0;
  for (string bkg : bkgs){
    ++icount;
    cout << setw(8) << left << bkg+":" << icount << " / " << bkgs.size() << endl;

    if (pb->verbosity > 1)
      std::cout << "*** " + bkg + " ***"
		<< pb->getRegionCutMC( "A", bkg) << std::endl;
    for (string reg : abcd) {
      bkgchain[bkg].Draw(("PionTriplet_MassInv>>bkg"+bkg+reg+binning).c_str(), (pb->getRegionCutMC(reg, bkg)).c_str());
    } // end for (string reg : abcd)
  } // end for (string bkg : bkgs)
  
  cout << "Getting histograms" << endl;
  map<string, TH1F*> signalhists;
  map<string, TH1F*> datahists;
  map<string, TH1F*> QCDhists;
  map<string, TH1F*> bkghists;
  for (string region : abcd){
    signalhists[region] = (TH1F*)gDirectory->Get(("signal"+region).c_str());
    datahists[region]   = (TH1F*)gDirectory->Get(("data"+region).c_str());
    for (string bkg : bkgs)
      bkghists[bkg+"_"+region] = (TH1F*)gDirectory->Get(("bkg"+bkg+region).c_str());

    QCDhists[region]  = (TH1F*)datahists[region]->Clone(("QCD Est_"+region).c_str());
    QCDhists[region]->Sumw2();
    // Substract out bkgs (not qcd or signal)
    for(string bkg : bkgs){ 
      if ((bkg != "QCD MC") && (bkg != "W3pi"))
	QCDhists[region]->Add(bkghists[bkg+"_"+region], -1);
    }
    
    // Add DY10 to DY and then get rid of it
    for (auto const& bkgpart : bkgsParts) {
      if (pb->verbosity > 0)
	std::cout << "Adding DY10 to DY in region " << region << std::endl;
      bkghists[bkgpart.second+"_"+region]->Add(bkghists[bkgpart.first+"_"+region], 1);
      bkghists.erase( bkgpart.first+"_"+region);
    }
  } // for (string region : abcd)

  // Can remove DY10 now that it's been added in all regions
  // bkgs.pop_back(); // requires DY10 to be last added
  for (auto const& bkgpart : bkgsParts)
    bkgs.erase( std::find(bkgs.begin(), bkgs.end(), bkgpart.first));

  double dataEntries  = datahists["D"]->GetEntries();
  double dataIntegral = datahists["D"]->Integral(0, numbins+1);
  if (dataEntries != dataIntegral) {
    std::cout << "Data Entries not matching integral!!!" << std::endl;
    std::cout << "Data Events in D  : " << datahists["D"]->GetEntries() << std::endl;
    std::cout << "Data Integral in D: " << datahists["D"]->Integral(0, 21) << std::endl;
  }
  
  cout << "Making canvas" << endl;
  for(string region : bcd){
    makeRegionPlot( region, datahists[region], signalhists[region], bkghists, bkgs, pb);
  }
  
  cout << "Getting extrapolation" << endl;
  TH1F* histRatio = (TH1F*)QCDhists["C"]->Clone("Extrapolation ratio");
  histRatio->Divide(QCDhists["D"]);

  // **********************
  // *** FITTING THINGS ***
  // **********************
  
  // int lowfitbin = lowbin, highfitbin = highbin;
  int lowfitbin = 40, highfitbin = 260;
  auto funcfit = new TF1("funcfit","([0] + [1]*x)", lowfitbin, highfitbin);
  Double_t chi2 = 0;
  // opt "R" uses the range of the TF1
  // opt "V" is verbose
  // opt "S" returns the fit result
  if (pb->verbosity > 1)
    chi2 = (histRatio->Fit(funcfit, "RSV"))->Chi2();
  else if (pb->verbosity > 0)
    chi2 = (histRatio->Fit(funcfit, "RS"))->Chi2();
  else 
    chi2 = (histRatio->Fit(funcfit, "QRS"))->Chi2();
  
  TCanvas *can = new TCanvas("Extrapolation ratio", "Extrapolation ratio", 600, 600);
  cout << "\n" << "Extrapolation function:" << endl;
  cout << funcfit->GetParameter(0) << " (+/- " << funcfit->GetParError(0) << ") + m_{W} * "
       << funcfit->GetParameter(1) << " (+/- " << funcfit->GetParError(1) << ")"
       << "\n" << endl;
  cout << "Chi2: " << chi2 << std::endl;
  can->SetLeftMargin(0.14); // 0.1 -> 0.14
  can->SetRightMargin(0.06); // 0.1 -> 0.06
  can->SetTickx();
  can->SetTicky();
  can->cd();

  // Plot and draw some other functions
  const char* p0 = to_string(funcfit->GetParameter(0)).c_str();
  const char* p1 = to_string(funcfit->GetParameter(1)).c_str();

  const char* p0Up = to_string(funcfit->GetParameter(0) + funcfit->GetParError(0)).c_str();
  const char* p0Do = to_string(funcfit->GetParameter(0) - funcfit->GetParError(0)).c_str();
  const char* p1Up = to_string(funcfit->GetParameter(1) + funcfit->GetParError(1)).c_str();
  const char* p1Do = to_string(funcfit->GetParameter(1) - funcfit->GetParError(1)).c_str();

  // No Slope
  auto funcfitZero   = new TF1( "funcfitZ",    p0, lowfitbin, highfitbin);
  auto funcfitZeroUp = new TF1( "funcfitZUp",  p0Up, lowfitbin, highfitbin);
  auto funcfitZeroDo = new TF1( "funcfitZDo",  p0Do, lowfitbin, highfitbin);

  // Slope opposite of y-int
  auto funcfitUp     = new TF1( "funcfitUp",   p0Up + TString(" + x*") + p1Do, lowfitbin, highfitbin);
  auto funcfitDo     = new TF1( "funcfitDo",   p0Do + TString(" + x*") + p1Up, lowfitbin, highfitbin);

  // Slope same as y-int
  auto funcfitUpUp   = new TF1( "funcfitUpUp", p0Up + TString(" + x*") + p1Up, lowfitbin, highfitbin);
  auto funcfitDoDo   = new TF1( "funcfitDoDo", p0Do + TString(" + x*") + p1Do, lowfitbin, highfitbin);
  
  // Account for bins with zero entries (?)
  histRatio->SaveAs("histRatio.C");
  for (int b = 0; b < histRatio->GetNbinsX(); ++b) {
    if (pb->verbosity > 1)
      std::cout << "content: " << histRatio->GetBinContent(b) 
		<< ", error  : " << histRatio->GetBinError(b)
		<< std::endl;
    
    if ((histRatio->GetBinContent(b) < 0.0001) || (histRatio->GetBinError(b) < 0.0001))
      histRatio->SetBinError( b, 1);
  }
  
  gStyle->SetOptFit( 1111);
  histRatio->SetStats(true);
  histRatio->SetMarkerColor(1);
  histRatio->GetXaxis()->SetTitle("Inv. W boson mass [GeV]");
  // histRatio->GetXaxis()->SetRangeUser( lowfitbin, highfitbin);
  histRatio->GetYaxis()->SetTitle("Region C over D");
  histRatio->GetYaxis()->SetRangeUser( -0.5, 1);
  histRatio->GetYaxis()->SetRangeUser( 0.0, 0.5);
  histRatio->SetTitle("Extrapolation ratio");
  histRatio->Draw("E1");
  funcfit->SetLineColor(2);
  funcfit->Draw("SAME");

  // New functions to plot
  funcfitZero->SetLineColor(kOrange);
  funcfitZeroUp->SetLineColor(kGreen);
  funcfitZeroDo->SetLineColor(kBlue);
  
  funcfitUp->SetLineColor(kGreen);
  funcfitDo->SetLineColor(kBlue);
  
  funcfitUpUp->SetLineColor(kGreen);
  funcfitDoDo->SetLineColor(kBlue);

  TLegend *legend = new TLegend(0.14,0.75,0.34,0.9);
  legend->AddEntry(histRatio, "Ratio", "lep");
  legend->AddEntry(funcfit, "Fit", "l");

  // funcfitZero->Draw("SAME");
  // funcfitZeroUp->Draw("SAME");
  // funcfitZeroDo->Draw("SAME");
  // legend->AddEntry(funcfitZero, "Zero Slope", "l");
  // legend->AddEntry(funcfitZeroUp, "Zero Slope Up", "l");
  // legend->AddEntry(funcfitZeroDo, "Zero Slope Down", "l");
  
  // funcfitUp->Draw("SAME");
  // funcfitDo->Draw("SAME");
  // legend->AddEntry(funcfitUp, "Y-int Up, Slope Down", "l");
  // legend->AddEntry(funcfitDo, "Y-int Down, Slope Up", "l");
  
  // funcfitUpUp->Draw("SAME");
  // funcfitDoDo->Draw("SAME");
  // legend->AddEntry(funcfitUp, "Y-int Up, Slope Up", "l");
  // legend->AddEntry(funcfitDo, "Y-int Down, Slope Down", "l");
  
  legend->Draw();
  can->SaveAs((pb->filepath + "/QCD_extrap_" + pb->filename + "_" + pb->getyear()  + ".png").c_str());
  // can->SaveAs((pb->filepath + "/QCD_extrapZeroSlope_" + pb->filename + "_" + pb->getyear()  + ".png").c_str());
  // can->SaveAs((pb->filepath + "/QCD_extrapOppYintSlope_" + pb->filename + "_" + pb->getyear()  + ".png").c_str());
  // can->SaveAs((pb->filepath + "/QCD_extrapSameYintSlope_" + pb->filename + "_" + pb->getyear()  + ".png").c_str());
  delete can;
  delete legend;

  // Check A / B ratio in bad charge region
  if (pb->chargereq == 3) {
    QCDhists["A"]->SaveAs("ShapVal_A.C");
    QCDhists["B"]->SaveAs("ShapVal_B.C");
    TH1F* histRatio_val = (TH1F*)QCDhists["A"]->Clone("Shape Validation");
    histRatio_val->Divide(QCDhists["B"]);
    histRatio_val->SaveAs("ShapVal_Ratio.C");
    auto funcfit_val = new TF1("funcfit_val","([0] + [1]*x)", 40, 260);

    Double_t chi2_val = 0;
    if (pb->verbosity > 1)
      chi2_val = (histRatio_val->Fit( funcfit_val, "RSV"))->Chi2();
    else if (pb->verbosity > 0)
      chi2_val = (histRatio_val->Fit( funcfit_val, "RS"))->Chi2();
    else 
      chi2_val = (histRatio_val->Fit( funcfit_val, "QRS"))->Chi2();
    
    TCanvas *canval = new TCanvas("Shape Validation", "Shape Validation", 600, 600);
    cout << "\n" << "Extrapolation function:" << endl;
    cout << funcfit_val->GetParameter(0) << " (+/- " << funcfit_val->GetParError(0) << ") + m_{W} * "
	 << funcfit_val->GetParameter(1) << " (+/- " << funcfit_val->GetParError(1) << ")"
	 << "\n" << endl;
    std::cout << "Chi2: " << chi2_val << std::endl;
    canval->SetLeftMargin(0.14); // 0.1 -> 0.14
    canval->SetRightMargin(0.06); // 0.1 -> 0.06
    canval->SetTickx();
    canval->SetTicky();
    canval->cd();

    // Account for bins with zero entries (?)
    // for (int b = 0; b < histRatio_val->GetNbinsX(); ++b)
    //   if (histRatio_val->GetBinContent(b) == 0)
    // 	histRatio_val->SetBinError( b, 1);

    gStyle->SetOptFit( 1111);
    histRatio_val->SetStats(true);
    histRatio_val->SetMarkerColor(1);
    histRatio_val->GetXaxis()->SetTitle("Inv. W boson mass [GeV]");
    histRatio_val->GetXaxis()->SetRangeUser( lowfitbin, highfitbin);
    histRatio_val->GetYaxis()->SetTitle("Region A' over B'");
    histRatio_val->GetYaxis()->SetRangeUser( -1, 2);
    histRatio_val->SetTitle("Shape Validation");
    histRatio_val->Draw("E1");
    funcfit_val->SetLineColor(3);
    funcfit_val->Draw("SAME");
    TLegend *legendval = new TLegend(0.14,0.75,0.34,0.9);
    legendval->AddEntry( histRatio_val, "Ratio", "lep");
    legendval->AddEntry( funcfit_val, "Fit", "l");
    legendval->Draw();
    canval->SaveAs((pb->filepath + "/QCD_shapeVal_" + pb->filename + ".png").c_str());
    delete canval;
    delete legendval;
  }

  // ******************
  // *** ESTIMATION ***
  // ******************
  
  cout << "Getting obtained QCD background" << endl;
  string extrapWeight = to_string(funcfit->GetParameter(0))+" + (PionTriplet_MassInv * "+to_string(funcfit->GetParameter(1))+")";
  // ("("+extrapWeight+")*("+selectioncut+"&&"+eventcuts+"&&"+tripletcuts+"&& !("+pb->SRcut1_scale+") && ("+pb->SRcut2_shape+"))").c_str());
  
  // Same as Region B cuts, but with extrapolation weight
  datachain.Draw(("PionTriplet_MassInv>>QCDFinalEstimation"+binning).c_str(), ( "(" + extrapWeight + ")* ("+ pb->getRegionCutData("B") + ")").c_str());
  bkghists["QCD Estimation"] = (TH1F*)gDirectory->Get("QCDFinalEstimation");
  bkghists["QCD Est Bins"] = (TH1F*)QCDhists["B"]->Clone("Bin Est");
  
  for (int ibin = 0; ibin < bkghists["QCD Est Bins"]->GetNbinsX(); ++ibin)
    bkghists["QCD Est Bins"]->SetBinContent( ibin, bkghists["QCD Est Bins"]->GetBinContent(ibin) * histRatio->GetBinContent(ibin));

  // Don't need to subtract from "QCD Est Bin", QCDhists["B"] already had them subbed out
  // Subtract our other backgrounds...
  for (string bkg : bkgs){
    if (bkg == "QCD MC") {
      std::cout << "skipping QCD" << std::endl;
      continue;
    }
    bkgchain[bkg].Draw(("PionTriplet_MassInv>>bkg"+bkg+"Extrap"+binning).c_str(), ( "(" + extrapWeight + ")* ("+ pb->getRegionCutMC("B", bkg) + ")").c_str());
    bkghists["QCD Estimation"]->Add( (TH1F*)gDirectory->Get(("bkg"+bkg+"Extrap").c_str()), -1);
    // std::cout << "Subtracting: " << bkg << " ( " << ((TH1F*)gDirectory->Get(("bkg"+bkg+"Extrap").c_str()))->Integral(0, numbins+1) << " )" << std::endl;
  }
  bkgs.push_back("QCD Estimation");
  bkgs.push_back("QCD Est Bins");

  // Now we can plot our Signal Region
  makeRegionPlot("A", datahists["A"], signalhists["A"], bkghists, bkgs, pb);

  // manually calculate chi2
  if (pb->chargereq == 3) {
    std::cout << "\n\nCalculating Chi2 between observed and expected" << std::endl;
    // this hist will be our full background estimation
    TH1F* fullBkgEst = (TH1F*)bkghists["QCD Estimation"]->Clone("yieldCompare");
    for ( std::string bkg : bkgs)
      if (bkg != "QCD Estimation")
	fullBkgEst->Add( bkghists[bkg+"_A"]);
    
    // Loop over bins and calculate chi2
    float chi2  = 0;
    float nbins = 0;
    for (int b = 0; b < fullBkgEst->GetNbinsX(); ++b) {
      if ( datahists["A"]->GetBinContent(b) != 0) {
	++nbins;
	chi2 += ((fullBkgEst->GetBinContent(b) - datahists["A"]->GetBinContent(b)) *
		 (fullBkgEst->GetBinContent(b) - datahists["A"]->GetBinContent(b))) / datahists["A"]->GetBinContent(b);
      }
    }
    std::cout << "Bin by Bin Chi2: " << setprecision(4) << chi2 << std::endl;
  }
  return 0;
}

#endif
