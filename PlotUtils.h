// Useful plotting things hidden away

#ifndef PLOT_UTILS_H
#define PLOT_UTILS_H

#include "TList.h"
#include "TColor.h"

#include "Analyzers.h"
#include "PlotBus.cc"

void makeRatioPlot( TH1F* histRatio, PlotBus* pb) {
  TCanvas *can = new TCanvas("Normalization ratio", "Normalization ratio", 600, 600);
  can->SetLeftMargin(0.14); // 0.1 -> 0.14
  can->SetRightMargin(0.06); // 0.1 -> 0.06
  can->SetTickx();
  can->SetTicky();
  can->cd();

  // gStyle->SetOptFit( 1111);
  histRatio->SetStats(true);
  histRatio->SetMarkerColor(1);
  histRatio->GetXaxis()->SetTitle("Inv. W boson mass [GeV]");
  // histRatio->GetXaxis()->SetRangeUser( lowfitbin, highfitbin);
  histRatio->GetYaxis()->SetTitle("Region C over D");
  histRatio->GetYaxis()->SetRangeUser( -0.5, 1);
  // histRatio->GetYaxis()->SetRangeUser( 0.0, 0.5);
  histRatio->SetTitle("Normalization ratio");
  histRatio->Draw("E1");
  
  can->SaveAs((pb->filepath + "/QCD_normailzation_" + pb->filename + "_" + pb->getyear()  + ".png").c_str());
};

// Figure out which element is the tallest and draw it, such that the scaling is correct
void drawTallest( TList* thingsToDraw, PlotBus* pb) {
  // TODO: deal with logy issue...
  TObject* tallest;
  float maxheight = -1;
  for (const auto&& obj : *thingsToDraw) {
    if (obj->IsA() == TClass::GetClass("TH1F")) {
      if ( ((TH1F*)obj)->GetMaximum() > maxheight) {
	maxheight = ((TH1F*)obj)->GetMaximum();
	tallest = thingsToDraw->FindObject( obj);
      }
    } else if (obj->IsA() == TClass::GetClass("THStack")) {
      if ( ((THStack*)obj)->GetMaximum() > maxheight) {
	maxheight = ((THStack*)obj)->GetMaximum();
	tallest = thingsToDraw->FindObject( obj);
      }
    }
  }

  if ( std::string(tallest->GetName()).find("data") != std::string::npos ) { 
    tallest->Draw("E1");
  }
  else
    tallest->Draw("HIST");
  
  if (tallest->IsA() == TClass::GetClass("TH1F")) {
    ((TH1F*)tallest)->SetTitle( pb->gettitle());
    ((TH1F*)tallest)->GetXaxis()->SetTitle( pb->getxtitle());
    ((TH1F*)tallest)->GetYaxis()->SetTitle("Events");
  } else if (tallest->IsA() == TClass::GetClass("THStack")) {
    ((THStack*)tallest)->SetTitle( pb->gettitle());
    ((THStack*)tallest)->GetXaxis()->SetTitle( pb->getxtitle());
    ((THStack*)tallest)->GetYaxis()->SetTitle("Events");
  }
}

// Simple function that just plots the hists that you give it
// the std::map hists should look like { "process", histogram pointer}
void makePlot( std::map<std::string, TH1F*> hists, PlotBus* pb) {
  std::map<std::string, std::vector<std::string>> yields;
  TCanvas *can = new TCanvas( (pb->getfilename()+pb->getRegionString()).c_str(), pb->getfilename(), 600, 600);
  TList *thingsToDraw = new TList();
  can->SetLeftMargin(0.14); // 0.1 -> 0.14
  can->SetRightMargin(0.06); // 0.1 -> 0.06
  can->cd();
  can->SetLogy( pb->logy);
  TLegend *legend = new TLegend(0.6,0.7,0.94,0.9);
  THStack *stack = new THStack("MC","MC");

  getYieldsAndEntries( hists, legend, pb);
  
  // Backgrounds
  for (auto const &hist : hists){
    if (pb->fillHists)
      hist.second->SetFillColor( getColors(hist.first));
    else
      hist.second->SetFillColor(0);
    
    hist.second->SetStats(false);
    if (pb->normalize)
      hist.second->Scale( 1 / hist.second->GetEntries());

    // Stack and *draw* only the bkgs we want
    // Treat signal and data special
    if (pb->stack) {
      if ( std::find( pb->procsToStack.begin(), pb->procsToStack.end(), hist.first) != pb->procsToStack.end()) {
	hist.second->SetLineColor( kBlack);
	if (pb->verbosity > 0)
	  std::cout << ">>> Stacking: " << hist.first << std::endl;
	stack->Add( hist.second);
      } else if ((pb->plotData) && (hist.first == "data")) {
	thingsToDraw->Add( hist.second);      
      } else if ((pb->plotSignal) && (hist.first == "signal")) {
	thingsToDraw->Add( hist.second);
      }
    } else {
      hist.second->SetLineColor( getColors(hist.first));
      if (pb->verbosity > 0)
	std::cout << ">>> Plotting: " << hist.first << std::endl;
      thingsToDraw->Add( hist.second);
    }
  } // for (auto hist& : ...

  if (pb->stack)
    thingsToDraw->Add( stack);
  
  // Draw the tallest, now we can do whatever order we want
  drawTallest( thingsToDraw, pb);
  
  if (pb->stack) {
    stack->Draw("HIST SAME");
  } else {
    for (auto const &hist : hists) 
      hist.second->Draw("HIST SAME");
  }

  // Signal
  if (pb->plotSignal) {
    std::cout << ">>> Plotting Signal..." << std::endl;
    hists["signal"]->SetLineColor(kBlue);
    hists["signal"]->SetLineWidth(2);
    hists["signal"]->SetLineStyle(kDashed);
    hists["signal"]->SetMarkerStyle(0);
    hists["signal"]->SetFillStyle(0);
    hists["signal"]->SetStats(false);
    hists["signal"]->Draw("HIST SAME");
  }

  // Data (not in SR (unless I say so))
  // Put this last so error bars are visible
  if (pb->currentRegion != "A" || pb->plotDataSR) {
    std::cout << ">>> Plotting Data..." << std::endl;
    hists["data"]->SetMarkerStyle(8);
    hists["data"]->SetMarkerSize(0.8);
    hists["data"]->SetStats(false);
    hists["data"]->Draw("E1SAME");
  }
  
  legend->Draw();

  if (pb->logy) 
    can->SaveAs(( pb->filepath + "/QuickPlot_"+pb->filename+pb->getRegionString()+"_"+pb->getyear()+"_logy.png").c_str());
  else
    can->SaveAs(( pb->filepath + "/QuickPlot_"+pb->filename+pb->getRegionString()+"_"+pb->getyear()+".png").c_str());

  if (pb->saveHists) {
    std::cout << ">>> Saving histograms as .C files in histMacros/" << std::endl;
    for (auto const &hist : hists) {
      (hist.second)->SaveAs( TString( "histMacros/" + pb->filename + "_" + hist.first  + ".C"));
    }
  }
}

// Is this smart?
void makeRegionPlot( std::map<std::string, TH1F*> hists, PlotBus* pb, std::string region) {
  pb->currentRegion = region;
  if (pb->qcdInfo)
    pb->title = pb->RegionTitles[region];
  makePlot( hists, pb);
}

/*
void makePlot(TH1F* signalhist, TH1F* datahist, std::map<std::string, TH1F*> bkghists, std::vector<std::string> bkgs, PlotBus* pb) {
  std::map<std::string, std::vector<std::string>> yields;
  TCanvas *can = new TCanvas( pb->getfilename(), pb->getfilename(), 600, 600);
  TList *thingsToDraw = new TList();
  can->SetLeftMargin(0.14); // 0.1 -> 0.14
  can->SetRightMargin(0.06); // 0.1 -> 0.06
  can->cd();
  can->SetLogy( pb->logy);
  THStack *stack = new THStack("MC","MC");
  TLegend *legend = new TLegend(0.6,0.7,0.94,0.9);

  // Signal
  std::stringstream integSignal;
  // integSignal << std::fixed << std::setprecision(2) << signalhist->Integral(0, signalhist->GetNbinsX()+1);
  integSignal << std::fixed << std::setprecision(2) << signalhist->GetSumOfWeights();
  std::vector<std::string> vec{ integSignal.str(), to_string( (int)signalhist->GetEntries())};
  yields["Signal"] = vec;
  legend->AddEntry( signalhist,("W->3#pi, B=10^-"+pb->getSignalScale()+" ("+integSignal.str()+")").c_str(),"l");
  signalhist->SetLineColor(kBlue);
  signalhist->SetLineWidth(2);
  signalhist->SetMarkerStyle(0);
  signalhist->SetFillStyle(0);
  signalhist->SetStats(false);
  
  // Data
  if (datahist) {
    std::stringstream integData;
    integData << std::fixed << std::setprecision(2) << datahist->Integral(0, datahist->GetNbinsX()+1);
    std::vector<std::string> vec{ integData.str(), to_string( (int)datahist->GetEntries())};
    yields["Data"] = vec;
    legend->AddEntry( datahist,("Data ("+integData.str()+")").c_str(),"lep");
    datahist->SetMarkerStyle(8);
    datahist->SetMarkerSize(0.8);
    datahist->SetStats(false);
  }

  // Backgrounds
  for(std::string bkg : bkgs){
    // bkghists[bkg]->SetFillColor(colors[bkg]);
    // bkghists[bkg]->SetStats(false);
    std::stringstream integ;
    integ << std::fixed << std::setprecision(2) << bkghists[bkg]->Integral(0, bkghists[bkg]->GetNbinsX()+1);
    std::vector<std::string> vec{ integ.str(), to_string( (int)bkghists[bkg]->GetEntries())};
    yields[bkg] = vec;
    // Only display the ones we want...
    if (std::find( pb->bkgsToPlot.begin(), pb->bkgsToPlot.end(), bkg) != pb->bkgsToPlot.end()) {
      stack->Add(bkghists[bkg]);
      legend->AddEntry( bkghists[bkg],(bkg+" ("+integ.str()+")").c_str(),"f");
    }
  }

  printYields( yields);

  thingsToDraw->Add( stack);
  if (pb->plotData)
    thingsToDraw->Add( datahist);
  if (pb->plotSignal)
    thingsToDraw->Add( signalhist);

  // Draw the tallest, then we can do whatever order we want
  drawTallest( thingsToDraw, pb);
  stack->Draw("HIST SAME");
  if (pb->plotSignal)
    signalhist->Draw("HIST SAME");
  if (pb->plotData)
    datahist->Draw("E1 SAME");
  
  legend->Draw();
  if (pb->logy) 
    can->SaveAs(TString(pb->filepath + pb->filename+"_"+pb->getyear()+"_logy.png"));
  else
    can->SaveAs(TString(pb->filepath + pb->filename+"_"+pb->getyear()+".png"));

  if (pb->saveHists) {
    std::cout << "Saving histograms as .C files..." << std::endl;
    signalhist->SaveAs( TString( "histMacros/"+pb->filename+"_signalhist.C"));
    if (pb->plotData)
      datahist->SaveAs( TString( "histMacros/"+pb->filename+"_datahist.C"));
    stack->SaveAs( TString( "histMacros/"+pb->filename+"_stack_mine.C"));
  }
}

// I don't really need this... I can do this using my big one I think
void makeRegionPlot( string region, TH1F* datahist, TH1F* signalhist, map<string, TH1F*> bkghists, vector<string> bkgs, PlotBus* pb){
  std::map<std::string, std::vector<std::string>> yields;
  TList *thingsToDraw = new TList();
  TCanvas *can = new TCanvas(("Region "+region).c_str(), ("Region "+region).c_str(), 600, 600);
  can->SetLeftMargin(0.14); // 0.1 -> 0.14
  can->SetRightMargin(0.06); // 0.1 -> 0.06
  can->cd();
  THStack *stack = new THStack("MC","MC");
  THStack *stack_est = (THStack*)stack->Clone("EST");
  THStack *stack_estBins = (THStack*)stack->Clone("EST Bins");
  
  TLegend *legend = new TLegend(0.6,0.7,0.94,0.9);
  pb->title = pb->RegionTitles[region];
  if (pb->chargereq == 3) {
    if (region == "A")
      pb->title = "|Q|=3 Fully Isolated Region";
    else
      pb->title += "|Q|=3";
  }

  if (pb->plotDataSR)
    getYieldsAndEntries( datahist, signalhist, bkghists, legend, pb, region);
  else
    getYieldsAndEntries( NULL, signalhist, bkghists, legend, pb, region);
  
  // Backgrounds
  for (string bkg : bkgs){
    // Only plot the ones we want
    if (std::find( pb->bkgsToPlot.begin(), pb->bkgsToPlot.end(), bkg) != pb->bkgsToPlot.end()) {
      bkghists[bkg+"_"+region]->SetFillColor(colors[bkg]);
      bkghists[bkg+"_"+region]->SetStats(false);
      stack->Add(bkghists[bkg+"_"+region]);
      if (bkg != "QCD MC") {
	stack_est->Add( (TH1F*)bkghists[bkg+"_"+region]);
	stack_estBins->Add( (TH1F*)bkghists[bkg+"_"+region]);
      } // if (bkg != ...
    } // if (std::find ...
  } // for (string bkg : ...
  
  // Make our TList of things to plot...
  thingsToDraw->Add( signalhist);
  thingsToDraw->Add( stack);
  if (region == "A") { // Take care of QCD
    bkghists["QCD Est Bins"]->SetLineColor( colors["QCD Est Bins"]);
    bkghists["QCD Est Bins"]->SetLineWidth(2);
    bkghists["QCD Est Bins"]->SetFillColor( 0);
    bkghists["QCD Est Bins"]->SetStats(false);

    bkghists["QCD Estimation"]->SetLineColor( colors["QCD Estimation"]);
    bkghists["QCD Estimation"]->SetLineWidth(2);
    bkghists["QCD Estimation"]->SetFillColor( 0);
    bkghists["QCD Estimation"]->SetStats(false);
    stack_est->Add( bkghists["QCD Estimation"]);
    stack_estBins->Add( bkghists["QCD Est Bins"]);
    
    thingsToDraw->Add( stack_est);
    thingsToDraw->Add( stack_estBins);

    if (pb->plotDataSR)
      thingsToDraw->Add( datahist);
  } else {
    thingsToDraw->Add( datahist);
  }
  
  // Draw the tallest, now we can do whatever order we want
  drawTallest( thingsToDraw, pb);
  stack->Draw("HIST SAME");

  // Data (not in SR (unless I say so))
  if (((region != "A") || pb->plotDataSR) && pb->plotData) { 
    datahist->SetMarkerStyle(8);
    datahist->SetMarkerSize(0.8);
    datahist->SetStats(false);
    datahist->Draw("E1SAME");
  }

  // QCD Estimate (only A)
  if (region == "A") { 
    stack_est->Draw("HIST SAME");
    stack_estBins->Draw("HIST SAME");
  }

  // Signal
  if (pb->plotSignal) {
    signalhist->SetLineColor(kBlue);
    signalhist->SetLineWidth(2);
    signalhist->SetLineStyle(kDashed);
    signalhist->SetMarkerStyle(0);
    signalhist->SetFillStyle(0);
    signalhist->SetStats(false);
    signalhist->Draw("HIST SAME");
  }
  
  legend->Draw();
  can->SaveAs(( pb->filepath + "/QCD_region_"+region+"_"+pb->filename+"_"+pb->getyear()+".png").c_str());
}
*/
#endif
