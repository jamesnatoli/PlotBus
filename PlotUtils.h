// Useful plotting things hidden away

#ifndef PLOT_UTILS_H
#define PLOT_UTILS_H

#include "TList.h"
#include "TColor.h"

#include "Analyzers.h"
#include "PlotBus.cc"
// Think about making a Plot class...

void manualbinlabels( TH1F* hist) {
  hist->GetXaxis()->SetTitle("");
  hist->GetXaxis()->SetBinLabel( 4,  "VVVLoose");
  hist->GetXaxis()->SetBinLabel( 6,  "VVLoose");
  hist->GetXaxis()->SetBinLabel( 8,  "VLoose");
  hist->GetXaxis()->SetBinLabel( 10,  "Loose");
  hist->GetXaxis()->SetBinLabel( 12, "Medium");
  hist->GetXaxis()->SetBinLabel( 14, "Tight");
  hist->GetXaxis()->SetBinLabel( 16, "VTight");
  hist->GetXaxis()->SetBinLabel( 18, "VVTight");

}

// Helper function to make a ratio just like TRatioPlot and draw it at the bottom
void makeMyRatio( PlotBus* pb, THStack* st, TH1* dh, TCanvas* canMain) {
  TCanvas *canRatio = new TCanvas("c", "Ratio", 800, 800);
  TH1* histRatio = (TH1*)dh->Clone();
  TList *stackHists = st->GetHists();
  
  if (stackHists->GetSize() == 0) {
    std::cout << ">> ERROR: Stack does not have histograms" << std::endl;
    return; // returns NULL object
  }
  TH1* tmpHist = (TH1*)stackHists->At(0)->Clone();
  tmpHist->Reset();
  
  for (int i=0;i<stackHists->GetSize();++i) {
    tmpHist->Add((TH1*)stackHists->At(i));
  }
  if (pb->doRatioDataMC) { 
    histRatio->Divide( tmpHist);
  } else { // standard
    histRatio = (TH1*)tmpHist->Clone();
    histRatio->Divide( dh);
  }
    
  // Now make a new pad below
  TPad *top = new TPad("top", "top", 0, 0.25, 1, 1.0);
  top->SetBottomMargin(0.1);
  top->Draw();
  top->cd();
  // Draw the main canvas on top pad
  canMain->DrawClonePad();
  // go back to Ratio Canvas before defining bottom
  canRatio->cd();

  // Now the Ratio on bottom
  TPad *bottom = new TPad("bottom", "bottom", 0, 0.0, 1, 0.30);
  bottom->SetTopMargin(0.1);
  bottom->SetBottomMargin(0.3);
  bottom->SetLeftMargin( canMain->GetLeftMargin());
  bottom->SetRightMargin( canMain->GetRightMargin());
  bottom->Draw();
  // bottom becomes the current pad
  bottom->cd();
  histRatio->SetMarkerStyle(8);
  // Use option "HIST" to override the associated errors
  // https://root-forum.cern.ch/t/draw-option-c-in-histogram-is-not-responding/30820/3
  histRatio->Draw("HIST P");

  // Beautify the Ratio a bit
  histRatio->SetTitle("");
  
  // Y axis ratio plot settings
  histRatio->GetYaxis()->SetTitle("Obs. / Exp.");
  // histRatio->GetYaxis()->SetNdivisions(505);
  histRatio->GetYaxis()->SetTitleSize(20);
  histRatio->GetYaxis()->SetTitleFont(43);
  histRatio->GetYaxis()->SetTitleOffset(1.55);
  histRatio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  histRatio->GetYaxis()->SetLabelSize(15);
  histRatio->GetYaxis()->SetRangeUser( 0.5, 2.0);
 
  // X axis ratio plot settings
  histRatio->GetXaxis()->SetTitle(pb->getxtitle());
  histRatio->GetXaxis()->SetTitleSize(25);
  histRatio->GetXaxis()->SetTitleFont(43);
  histRatio->GetXaxis()->SetTitleOffset(4);
  histRatio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  histRatio->GetXaxis()->SetLabelSize(15);

  // And finally, a line at x = 1
  // NB: the x and y coords are for the axis
  TLine* unity = new TLine( 0.0, 1.0, 0.045, 1.0);
  unity->SetLineStyle( kDashed);
  unity->Draw("same");
  
  if (pb->logy) 
    canRatio->SaveAs(( pb->filepath + "/QuickPlot_"+pb->filename+pb->getRegionString()+"_"+pb->getyear()+"_Ratio_logy.png").c_str());
  else
    canRatio->SaveAs(( pb->filepath + "/QuickPlot_"+pb->filename+pb->getRegionString()+"_"+pb->getyear()+"_Ratio.png").c_str());
  
  // change back to main Canvas before leaving
  canRatio->SaveAs("temp.C");
  canMain->cd(); 
}

void makeRatioPlot( TH1F* histRatio, PlotBus* pb,
		    std::string yTitle="Region C over D",
		    std::string plotTitle="Normalization Ratio") {
  TCanvas *can = new TCanvas("Ratio", "Ratio", 600, 600);
  can->SetLeftMargin(0.14); // 0.1 -> 0.14
  can->SetRightMargin(0.06); // 0.1 -> 0.06
  can->SetTickx();
  can->SetTicky();
  can->cd();

  // gStyle->SetOptFit( 1111);
  histRatio->SetStats(true);
  histRatio->SetMarkerColor(1);
  histRatio->GetXaxis()->SetTitle("Inv. W boson mass [GeV]");
  histRatio->GetYaxis()->SetTitle( yTitle.c_str());
  if (!pb->autoRatioLimits)
    histRatio->GetYaxis()->SetRangeUser( pb->ratioLow, pb->ratioHigh);
  histRatio->SetTitle( plotTitle.c_str());
  histRatio->Draw("E1");
  
  can->SaveAs((pb->filepath + "/QCD_normailzation_" + pb->filename + "_" + pb->getyear()  + ".png").c_str());
  if (pb->saveHists)
    can->SaveAs( ("histMacros/QCD_normailzation_" + pb->filename + "_" + pb->getyear()  + ".C").c_str());
};

// Helper function to sort the stack if plotting logy
// https://root-forum.cern.ch/t/thstack-using-drawing-in-wrong-order-for-log-scale/27076/10
THStack* sortStack( TList* hists) {
  THStack* stack = new THStack("MC", "MC");
  std::vector<TH1*> histsorter;
  for (auto hist : *hists)
    histsorter.push_back( (TH1 *)hist);

  std::sort( histsorter.begin(), histsorter.end(),
	    [](TH1 *a, TH1 *b) { return a->Integral() < b->Integral(); });

  for (auto &hist : histsorter)
    stack->Add( hist);
  
  return stack;
}

// Figure out which element is the tallest and draw it, such that the scaling is correct
void drawTallest( TList* thingsToDraw, PlotBus* pb) {
  // TODO: deal with logy issue...
  float scaleAxis = 1.25;
  if (pb->logy)
    scaleAxis *= 20;
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
  } else {
    if (tallest->IsA() == TClass::GetClass("THStack")) { // THStacks need max/min set prior to drawing
      if (pb->verbosity > 1)
	std::cout << ">>> Setting Maximum (THStack) to " << (maxheight*scaleAxis) << std::endl;
      // ROOT approved way, ugh
      // https://root-forum.cern.ch/t/thstack-what-is-the-correct-way-to-set-the-y-axis-limits/41851/9
      ((THStack*)tallest)->SetMaximum( (maxheight*scaleAxis));
      if (pb->logy)
	((THStack*)tallest)->SetMinimum( 0.01);
    }
    tallest->Draw("HIST");
  }
  
  if (tallest->IsA() == TClass::GetClass("TH1F")) {
    ((TH1F*)tallest)->SetTitle( pb->gettitle());
    ((TH1F*)tallest)->GetXaxis()->SetTitle( pb->getxtitle());
    ((TH1F*)tallest)->GetYaxis()->SetTitle("Events");
    if (pb->verbosity > 1)
      std::cout << ">>> Setting Maximum (TH1F) to " << (maxheight*scaleAxis) << std::endl;
    ((TH1F*)tallest)->GetYaxis()->SetRangeUser( 0.0, (maxheight*scaleAxis)); // account for error bars
    if (pb->logy)
      ((TH1F*)tallest)->GetYaxis()->SetRangeUser( 0.01, (maxheight*scaleAxis));
    if (pb->DeepTauBinLabels)
      manualbinlabels( (TH1F*)tallest);
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
	if (pb->verbosity > 1)
	  std::cout << ">>> Stacking: " << hist.first << " (" << hist.second->Integral() << ")" << std::endl;
	stack->Add( hist.second);
      } else if ((pb->plotData) && (hist.first == "data")) {
	thingsToDraw->Add( hist.second);      
      } else if ((pb->plotSignal) && (hist.first == "signal")) {
	thingsToDraw->Add( hist.second);
      }
    } else {
      hist.second->SetLineColor( getColors(hist.first));
      if (pb->verbosity > 1)
	std::cout << ">>> Plotting: " << hist.first << std::endl;
      thingsToDraw->Add( hist.second);
    }
  } // for (auto hist& : ...

  if (pb->stack) {
    if (pb->logy)
      stack = sortStack( stack->GetHists());
    thingsToDraw->Add( stack);
  }
  
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

  if (pb->drawLegend)
    legend->Draw();
  
  if (pb->doRatioDataMC || pb->doRatioMCData) {
    if (pb->plotDataSR && pb->stack)
      makeMyRatio( pb, stack, hists["data"], can);
    else
      std::cout << ">>> ERROR: Can't make ratio unless you plot stack and data" << std::endl;
  }
  

  if (pb->logy) 
    can->SaveAs(( pb->filepath + "/QuickPlot_"+pb->filename+pb->getRegionString()+"_"+pb->getyear()+"_logy.png").c_str());
  else
    can->SaveAs(( pb->filepath + "/QuickPlot_"+pb->filename+pb->getRegionString()+"_"+pb->getyear()+".png").c_str());

  if (pb->saveCanvas)
    can->Print( ( pb->filepath + "/QuickPlot_"+pb->filename+pb->getRegionString()+"_"+pb->getyear()+".C").c_str());
  
  if (pb->saveHists) {
    std::cout << ">>> Saving histograms as .C files in histMacros/" << std::endl;
    for (auto const &hist : hists) {
      (hist.second)->SaveAs( TString( "histMacros/" + pb->filename + "_" + hist.first  + ".C"));
    }
  }

  // Random option
  if (pb->getBinSig)
    signalSignifigance( hists["signal"], stack, pb);
  
}

// Is this smart?
void makeRegionPlot( std::map<std::string, TH1F*> hists, PlotBus* pb, std::string region) {
  pb->currentRegion = region;
  if (pb->qcdInfo)
    pb->title = pb->getRegionTitle();
  makePlot( hists, pb);
}
#endif
