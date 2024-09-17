// Useful plotting things hidden away

#ifndef PLOT_UTILS_H
#define PLOT_UTILS_H

#include "TList.h"
#include "TLine.h"
#include "TColor.h"
#include "TLatex.h"

#include <iostream>

#include "Analyzers.h"
#include "PlotUtils.h"

// Think about making a Plot class...
// Allow ratios with 2 stacks??
// Helper function to make a ratio just like TRatioPlot and draw it at the bottom
void makeMyRatio( PlotBus* pb, THStack* st, TH1* dh, TCanvas* canMain) {
  TCanvas *canRatio = new TCanvas( ("c" + pb->year).c_str(), "Ratio", 800, 800);
  TH1* histRatio = (TH1*)dh->Clone();
  TList *stackHists = st->GetHists();
  std::cout << ">>> Making Ratio... " << std::endl;

  if ((!stackHists) || (stackHists->GetSize() == 0)) {
    std::cout << ">> ERROR: Stack is empty or does not have histograms, skipping ratio!" << std::endl;
    return; // returns NULL object
  } else if (!dh) {
    std::cout << ">> ERROR: Data (" << pb->dataName << ") is empty!" << std::endl;
    return;
  }
  TH1* tmpHist = (TH1*)stackHists->At(0)->Clone();
  tmpHist->Reset();
  
  for (int i=0;i<stackHists->GetSize();++i) {
    tmpHist->Add((TH1*)stackHists->At(i));
  }
  if (pb->doRatioDataMC) { 
    histRatio->Divide( tmpHist);
  } else { // MC over Data (not standard)
    histRatio = (TH1*)tmpHist->Clone();
    histRatio->Divide( dh);
  }
  histRatio->Sumw2();
    
  // Now make a new pad below
  TPad *top = new TPad("top", "top", 0, 0.08, 1, 1.0);
  top->SetBottomMargin(0.18);
  top->Draw();
  top->cd();
  // Draw the main canvas on top pad
  canMain->DrawClonePad();
  // go back to Ratio Canvas before defining bottom
  canRatio->cd();

  // Now the Ratio on bottom
  TPad *bottom = new TPad("bottom", "bottom", 0, 0.0, 1, 0.20);
  bottom->SetTopMargin(0.03);
  bottom->SetBottomMargin(0.3);
  bottom->SetLeftMargin( canMain->GetLeftMargin());
  bottom->SetRightMargin( canMain->GetRightMargin());
  bottom->Draw();
  // bottom becomes the current pad
  bottom->cd();
  histRatio->SetMarkerStyle(8);
  // Use option "HIST" to override the associated errors
  // do I want to do that???
  // https://root-forum.cern.ch/t/draw-option-c-in-histogram-is-not-responding/30820/3
  histRatio->Draw("HIST PXE1");

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

  // quick get max
  float maxVal = 0.0, minVal = 0.0;
  float scaleAxis = 1.25;
  for (unsigned int nb = 0; nb < histRatio->GetNbinsX(); ++nb) {
    float tempMax = histRatio->GetBinContent(nb) + histRatio->GetBinError(nb);
    float tempMin = histRatio->GetBinContent(nb) - histRatio->GetBinError(nb);
    // this is so hacky...
    if ( (maxVal < tempMax) && (tempMax < 5))
      maxVal = tempMax;
    if ( ( minVal > tempMin) && (tempMin > -4))
      minVal = tempMin;
  }

  histRatio->GetYaxis()->SetRangeUser( -1 * (maxVal - 1), scaleAxis * maxVal);
  // histRatio->GetYaxis()->SetRangeUser( scaleAxis * minVal, scaleAxis * maxVal);
 
  // X axis ratio plot settings
  histRatio->GetXaxis()->SetTitle(pb->getxtitle());
  histRatio->GetXaxis()->SetTitleSize(20);
  histRatio->GetXaxis()->SetTitleFont(43);
  histRatio->GetXaxis()->SetTitleOffset(1);
  histRatio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  histRatio->GetXaxis()->SetLabelSize(15);

  // And finally, a line at x = 1
  // NB: the x and y coords are for the axis
  double rend = histRatio->GetBinLowEdge( histRatio->GetNbinsX()+1);
  TLine* unity = new TLine( 0.0, 1.0, rend, 1.0);
  unity->SetLineStyle( kDashed);
  unity->Draw("same");
  
  if (pb->logy) 
    canRatio->SaveAs(( pb->getfilepath() + "/QuickPlot_"+pb->filename+pb->getRegionString()+"_"+pb->getyear()+"_Ratio_logy.png").c_str());
  else
    canRatio->SaveAs(( pb->getfilepath() + "/QuickPlot_"+pb->filename+pb->getRegionString()+"_"+pb->getyear()+"_Ratio.png").c_str());

  // Saving Canvas as macro
  if (pb->saveCanvas)
    canRatio->Print( ( pb->getfilepath() + "/QuickPlot_"+pb->filename+pb->getRegionString()+"_"+pb->getyear()+"_Ratio.C").c_str());
  
  // change back to main Canvas before leaving
  if (pb->saveHists)
    canRatio->SaveAs(( pb->getfilepath() + "/QuickPlot_"+pb->filename+pb->getRegionString()+"_"+pb->getyear()+"_Ratio.C").c_str());
  canMain->cd(); 
}

void makeMyRatio( PlotBus* pb, TH1* h1, TH1* dh, TCanvas* canMain) {
  THStack* tempStack = new THStack( h1->GetName(), h1->GetTitle());
  tempStack->Add( h1);
  makeMyRatio( pb, tempStack, dh, canMain);
}

// defaults defined in header
// only used by QCDestimation
void makeRatioPlot( TH1* histRatio, PlotBus* pb, std::string yTitle, std::string plotTitle) {
  TCanvas *can = new TCanvas( ("Ratio" + pb->year).c_str(), "Ratio", 600, 600);
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
  
  can->SaveAs((pb->getfilepath() + "/QCD_normailzation_" + pb->filename + "_" + pb->getyear()  + ".png").c_str());
  if (pb->saveHists)
    can->SaveAs( ("histMacros/QCD_normailzation_" + pb->filename + "_" + pb->getyear()  + ".C").c_str());
};

// Simple function that just plots the hists that you give it
// the std::map hists should look like { "process", histogram pointer}
void makePlot( std::map<std::string, TH1*> hists, PlotBus* pb) {
  std::map<std::string, std::vector<std::string>> yields;
  TCanvas *can = new TCanvas( (pb->getfilename()+pb->getRegionString()+pb->year).c_str(), pb->getfilename(), 600, 600);
  TList *thingsToDraw = new TList();
  can->SetTopMargin(0.04);
  can->SetBottomMargin(0.13);
  can->SetLeftMargin(0.145); // 0.1 -> 0.14 -> 0.145 (copy TauFW Plotter)
  can->SetRightMargin(0.06); // 0.1 -> 0.06 -> 0.02  (copy TauFW Plotter?)
  can->cd();
  can->SetLogy( pb->logy);
  TLegend *legend = new TLegend( 0.6, 0.75, 1 - can->GetRightMargin(), 1 - can->GetTopMargin());
  THStack *stack = new THStack("MC","MC");
  THStack *signalStack = new THStack("Sig","Sig");
  
  // Backgrounds
  for (auto const &hist : hists){
    // add overflows to final bin (default)
    if (pb->overflow)
      hist.second->SetBinContent( hist.second->GetNbinsX(),
				  hist.second->GetBinContent( hist.second->GetNbinsX()) +
				  hist.second->GetBinContent( hist.second->GetNbinsX() + 1));
    
    // Stats and norm
    hist.second->SetStats(false);
    if (pb->normalize == "1") {
      std::cout << ">>> Normalizing Integral to 1" << std::endl;
      pb->ytitle = "a.u.";
      hist.second->Scale( 1 / hist.second->GetSumOfWeights());
      // hist.second->Scale( 1 / hist.second->GetEntries());
    } else if (pb->normalize != "") {
      std::cout << ">>> Normalizing to bin width" << std::endl;
      pb->ytitle = "a.u.";
      hist.second->Scale( 1, pb->normalize.c_str());
    }

    // Stack and *draw* only the bkgs we want
    // Data first, easy
    if ((pb->plotData) && (hist.first == pb->dataName))
      thingsToDraw->Add( hist.second);
    
    // Now Backgrounds...
    if ((pb->stack) && (std::find( pb->procsToStack.begin(), pb->procsToStack.end(), hist.first) != pb->procsToStack.end())) {
      hist.second->SetLineColor( kBlack);
      if (pb->fillHists)
	hist.second->SetFillColor( pb->getColors( hist.first));
      else 
	hist.second->SetFillColor(0);
      if (pb->verbosity > 1)
	std::cout << ">>> Stacking: " << hist.first << " (" << hist.second->Integral() << ")" << std::endl;
      stack->Add( hist.second);
    } else if ( !(hist.first == pb->dataName) && (std::find( pb->signals.begin(), pb->signals.end(), hist.first) == pb->signals.end())) {
      if (pb->verbosity > 0)
	std::cout << ">>> Plotting (no stack): " << hist.first << std::endl;
      hist.second->SetLineColor( pb->getColors(hist.first));
      thingsToDraw->Add( hist.second);
      // if (!stack->GetHists()) {
      // 	std::cout << ">>> ERROR: NOTHING added to Stack" << std::endl;
      // 	pb->stack = false;
      // }
      // else 
      // 	thingsToDraw->Add( hist.second);
    }
    
    // Lastly Signal
    if ((pb->plotSignal) && (std::find( pb->signals.begin(), pb->signals.end(), hist.first) != pb->signals.end())) {
      hist.second->SetFillStyle( pb->signalFillStyle); 
      if (pb->fillSignal) {
	hist.second->SetLineColor( kBlack);
	hist.second->SetFillColor( pb->getColors( hist.first));
	hist.second->SetFillStyle( pb->getSignalFillStyle());
      } else {
	hist.second->SetLineColor( pb->getColors( hist.first));
      }
      hist.second->SetLineWidth(2);
      hist.second->SetLineStyle(kDashed);
      hist.second->SetMarkerStyle(0);
      hist.second->SetStats(false);
      if ((pb->stackSignal) && (std::find( pb->signalsToStack.begin(), pb->signalsToStack.end(), hist.first) != pb->signalsToStack.end())) {
	if (pb->verbosity > 1)
	  std::cout << ">>> Stacking: " << hist.first << " (" << hist.second->Integral() << ")" << std::endl;
	signalStack->Add( hist.second);
      } else {
	if (pb->verbosity > 1)
	  std::cout << ">>> Plotting: " << hist.first << std::endl;
	thingsToDraw->Add( hist.second);
      }
    }
  } // for (auto hist& : ...

  // Take care of our stacks...
  if (pb->stack) {
    stack = sortStack( stack->GetHists(), pb);
    thingsToDraw->Add( stack);
  }

  // Signal stack here
  if (pb->stackSignal) {
    if (pb->logy)
      signalStack = sortStack( signalStack->GetHists(), pb);
    thingsToDraw->Add( signalStack);
  }

  // Two Dimensional
  if (pb->twoDimensional) {
    drawTwoDimensional( thingsToDraw, pb, can);
    return;
  }

  // Draw the tallest, now we can do whatever order we want
  TObject* tallest = drawTallest( thingsToDraw, pb, can);
  // if I have this nice TList of all the things that I want to draw... why not use it?
  for (const auto&& thing : *thingsToDraw) {
    if (!pb->isData(thing))
      thing->Draw( pb->getDrawingOpts());
    // Only draw hist errors for backgrounds (stack or single)
    if ( (!pb->isData(thing)) && (!pb->isSignal(thing)) && (pb->histErrors)) {
      TH1* errors = 0;
      if (dynamic_cast<TH1*>(thing)) { 
	errors = dynamic_cast<TH1*>(thing);
      } else if (dynamic_cast<THStack*>(thing)){
	errors = dynamic_cast<TH1*>( getStackSum( dynamic_cast<THStack*>(thing))->Clone());
      } else {
	std::cout << "ERROR! Unknown type in TList" << std::endl;
      }
      errors->SetFillStyle(3354);
      errors->SetFillColor(kBlack);
      errors->Draw("e2 same");
    } // if ( (!pb->isData...
  } // for (const auto&&...
  
  // Signal, beause we want it in front
  if (pb->plotSignal) {
    if (pb->stackSignal) {
      if (pb->verbosity > 0)
	std::cout << ">>> Plotting Signal Stack..." << std::endl;
      signalStack->Draw(pb->getDrawingOpts());
    } else {
      if (pb->verbosity > 0)
	std::cout << ">>> Plotting Signal(s)..." << std::endl;
      for (const auto&& thing : *thingsToDraw) {
	if (pb->isSignal( thing))
	  thing->Draw( pb->getDrawingOpts());
      }
    }
  }
  
  // Data (not in SR (unless I say so))
  // Put this last so error bars are visible
  if (pb->currentRegion != "A" || pb->plotDataSR) {
    std::cout << ">>> Plotting Data (" << pb->dataName << ")..." << std::endl;
    if (pb->verbosity > 1) {
      for (auto const &hist : hists)
	std::cout << "hist in hists: " << hist.first << " (" << hist.second->GetSumOfWeights() << ")" << std::endl;
    }

    hists[pb->dataName]->SetFillStyle(0);
    hists[pb->dataName]->SetMarkerStyle(8);
    hists[pb->dataName]->SetMarkerSize(0.8);
    hists[pb->dataName]->SetStats(false);
    if (pb->blindData){
      std::cout << ">>> Blinding Data in [ " << pb->blindRegion[0] << ", " << pb->blindRegion[1] << "]" << std::endl;
      for (int nb = 0; nb < hists[pb->dataName]->GetNbinsX(); ++nb) {
	if ((hists[pb->dataName]->GetBinLowEdge(nb) > pb->blindRegion[0]) &&
	    (hists[pb->dataName]->GetBinLowEdge(nb) < pb->blindRegion[1])) {
	  hists[pb->dataName]->SetBinContent(nb, 0);
	  hists[pb->dataName]->SetBinError(nb, 0);
	}
      }
    }
      
    hists[pb->dataName]->Draw("E1SAME");
  }
  
  // NOW fill the legend and everything...
  pb->getYieldsAndEntries( hists, legend);
  
  // Draw the legend
  if (pb->drawLegend)
    legend->Draw();

  // Put the pretty labels on (before ratio plot)
  drawTopLabel( pb->getTopLabel(), can);
  drawInfoLabels( pb, can);

  tallest->Draw("AXIS SAME"); // redraw ticks
  // Ratio with MC and Data
  if (pb->doRatioDataMC || pb->doRatioMCData) {
    if (pb->plotDataSR && pb->stack) {
      makeMyRatio( pb, stack, hists[pb->dataName], can);
      if (dynamic_cast<TH1*>(tallest))
	dynamic_cast<TH1*>(tallest)->GetXaxis()->SetTitle(pb->getxtitle());
      else if (dynamic_cast<THStack*>(tallest)) 
	dynamic_cast<THStack*>(tallest)->GetXaxis()->SetTitle(pb->getxtitle());
    } else {
      std::cout << ">>> ERROR: Can't make ratio unless you plot stack and data" << std::endl;
    }
  }

  // Ratio with Signal and Data
  if (pb->doRatioDataSignal || pb->doRatioSignalData) {
    if (pb->plotDataSR) {
      if (!pb->stackSignal)
	makeMyRatio( pb, hists["Signal WJetsTo3Pi"], hists[pb->dataName], can);
      makeMyRatio( pb, signalStack, hists[pb->dataName], can);
    } else {
      std::cout << ">>> ERROR: Can't make signal ratio unless you plot signal and data" << std::endl;
    }
  }

  // TODO: Fix this
  // Ratio with MC and Signal
  // if (pb->doRatioSignalMC || pb->doRatioMCSignal) {
  //   if (!pb->stackSignal) {
  //     for (const auto&& thing : *thingsToDraw) {
  // 	if (pb->isSignal(thing)) {
  // 	  stackSignal->Add( thing);
  // 	}
  //     }
  //   }
  //   if ((pb->signals.size()) != 0 && pb->stack)
  //     makeMyRatio( pb, stack, signalStack, can);
  //   else 
  //     std::cout << ">>> ERROR: Can't make ratio unless you plot stack and data" << std::endl;
  // }

  // Saving Canvas as image
  if (pb->logy) 
    can->SaveAs(( pb->getfilepath() + "/QuickPlot_"+pb->filename+pb->getRegionString()+"_"+pb->getyear()+"_logy.png").c_str());
  else
    can->SaveAs(( pb->getfilepath() + "/QuickPlot_"+pb->filename+pb->getRegionString()+"_"+pb->getyear()+".png").c_str());

  // Saving Canvas as macro
  if (pb->saveCanvas)
    can->Print( ( pb->getfilepath() + "/QuickPlot_"+pb->filename+pb->getRegionString()+"_"+pb->getyear()+".C").c_str());

  // Saving Histograms as macros
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
void makeRegionPlot( std::map<std::string, TH1*> hists, PlotBus* pb, std::string region) {
  pb->currentRegion = region;
  if (pb->qcdInfo) {
    if (region != "A") {
      if (pb->verbosity > 1)
	std::cout << "Skipping Data/MC Ratio plot in Region " << region << std::endl;
      pb->doRatioDataMC = false;
    }
  }
  makePlot( hists, pb);
}

// (different file?)
// ***************
// *** Helpers *** 
// ***************

// Figure out which element is the tallest and draw it, such that the scaling is correct
// Now we RETURN the tallest, in case we want to do something with it later
TObject* drawTallest( TList* thingsToDraw, PlotBus* pb, TCanvas* can) {
  float scaleAxis = 1.25;
  if (pb->logy)
    scaleAxis *= 80;
  TObject* tallest;
  float maxheight = -1, thisMax = 0;
  for (const auto&& obj : *thingsToDraw) {
    if (pb->verbosity > 1)
      std::cout << "name: " << obj->GetName() << std::endl;
    if (dynamic_cast<TH1*>(obj))
      thisMax = getMaximumWithErrors(dynamic_cast<TH1*>(obj));
    else if (dynamic_cast<THStack*>(obj)) {
      if (!getStackSum(dynamic_cast<THStack*>(obj)))
	std::cout << "uh oh... stack DOES NOT EXIST" << std::endl;
      thisMax = getMaximumWithErrors(dynamic_cast<TH1*>(getStackSum(dynamic_cast<THStack*>(obj))->Clone()));
    }
    else
      std::cout << "ERROR! Unknown type in TList" << std::endl;
    
    if (thisMax > maxheight) {
      maxheight = thisMax;
      tallest = thingsToDraw->FindObject( obj);
    } 
  }

  if ( pb->isData( tallest)) {
    tallest->Draw("E1");    
  } else {
    if (dynamic_cast<THStack*>(tallest)) {
      if (pb->verbosity > 1)
	std::cout << ">>> Setting Maximum (THStack) to " << (maxheight*scaleAxis) << std::endl;
      // ROOT approved way, ugh
      // https://root-forum.cern.ch/t/thstack-what-is-the-correct-way-to-set-the-y-axis-limits/41851/9
      dynamic_cast<THStack*>(tallest)->SetMaximum(maxheight*scaleAxis);
      if (pb->logy) // this doesn't alwyas work well...
	dynamic_cast<THStack*>(tallest)->SetMinimum( 0.0001);
    }
    tallest->Draw("HIST");
  }
  if (dynamic_cast<TH1*>(tallest)) {
    TH1* tempTall = dynamic_cast<TH1*>(tallest);
    tempTall->SetTitle( pb->gettitle());
    if (!(pb->doRatioDataMC || pb->doRatioMCData || pb->doRatioDataSignal || pb->doRatioSignalData))
      tempTall->GetXaxis()->SetTitle( pb->getxtitle());
    else { // not working :(
      tempTall->GetYaxis()->ChangeLabel(1, -1, 0);
    }
    tempTall->GetYaxis()->SetTitle( pb->getytitle());
    if (pb->verbosity > 1)
      std::cout << ">>> Setting Maximum (TH1) to " << (maxheight*scaleAxis) << std::endl;
    tempTall->GetYaxis()->SetRangeUser( 0.0, (maxheight*scaleAxis)); // account for error bars
    if (pb->logy)
      tempTall->GetYaxis()->SetRangeUser( 0.01, (maxheight*scaleAxis));
    if (pb->DeepTauBinLabels)
      manualbinlabels( pb, tempTall);
  } else if (dynamic_cast<THStack*>(tallest)) {
    dynamic_cast<THStack*>(tallest)->SetTitle( pb->gettitle());
    if (!(pb->doRatioDataMC || pb->doRatioMCData || pb->doRatioDataSignal || pb->doRatioSignalData))
      dynamic_cast<THStack*>(tallest)->GetXaxis()->SetTitle( pb->getxtitle());
    else // not working :(
      dynamic_cast<THStack*>(tallest)->GetYaxis()->ChangeLabel(1, -1, 0);
    dynamic_cast<THStack*>(tallest)->GetYaxis()->SetTitle( pb->getytitle());
    if (pb->DeepTauBinLabels)
      manualbinlabels( pb, dynamic_cast<THStack*>(tallest)->GetHistogram());
  }
  
  return tallest;
}

// Helper function to sort the stack if plotting logy
// https://root-forum.cern.ch/t/thstack-using-drawing-in-wrong-order-for-log-scale/27076/10
THStack* sortStack( TList* hists, PlotBus* pb) {
  THStack* stack = new THStack("MC", "MC");
  std::vector<TH1*> histsorter;

  // NB: if you force stack order it is up to YOU to make sure things look good
  if (pb->keepStackOrder) { // just take order as given (default)
    for (auto proc : pb->procsToStack) {
      for (auto hist : *hists) {
	if (std::string(hist->GetName()).find(proc) != std::string::npos)
	  stack->Add( (TH1 *)hist);
      }
    }
  } else if (pb->logy) { // ensure smallest is on the BOTTOM
    for (auto hist : *hists) // add to a std::vector so we can sort
      histsorter.push_back( (TH1 *)hist);
    
    // now sort from smallest to largest
    std::sort( histsorter.begin(), histsorter.end(),
	       [](TH1 *a, TH1 *b) { return a->Integral() < b->Integral(); });
    
    for (auto &hist : histsorter)
      stack->Add( hist);
  } else { // just add normally, who even cares
    for (auto hist : *hists) {
      stack->Add( (TH1 *)hist);
    }
  }
  
  return stack;
}

float getMaximumWithErrors( TH1* hist) {
  float maxBin = -1, binTotal = 0;
  for (int ibin = 0; ibin <= hist->GetNbinsX()+1; ++ibin) {
    binTotal = hist->GetBinContent(ibin) + hist->GetBinError(ibin);
    if ( binTotal > maxBin)
      maxBin = binTotal;
  }
  return maxBin;
}

TH1* getStackSum( THStack* st) { // remember to Clone() the return value of this
  TH1* temp = 0;
  for (auto ele : *(st->GetHists())) {
    if (!temp)
      temp = dynamic_cast<TH1*>(ele->Clone());
    else
      temp->Add(dynamic_cast<TH1*>(ele->Clone()));
  }
  return temp;
}

void drawTwoDimensional( TList* thingsToDraw, PlotBus* pb, TCanvas* can) {
  std::cout << ">>> Drawing 2D Plot" << std::endl;
  can->SetRightMargin(0.145); // match left margin
  can->SetLogz(pb->logz);
  
  for (const auto&& obj : *thingsToDraw) {    
    if (dynamic_cast<TH1*>(obj)) {
      dynamic_cast<TH1*>(obj)->GetXaxis()->SetTitle(pb->getxtitle());
      dynamic_cast<TH1*>(obj)->GetYaxis()->SetTitle(pb->getytitle());
    } else if (dynamic_cast<THStack*>(obj)) {
      dynamic_cast<THStack*>(obj)->GetXaxis()->SetTitle(pb->getxtitle());
      dynamic_cast<THStack*>(obj)->GetYaxis()->SetTitle(pb->getytitle());
    }
    
    obj->Draw("COLZ");
    
    if (pb->logz) 
      can->SaveAs(( pb->getfilepath() + "/QuickPlot_"+pb->filename+"_"+obj->GetName()+"_"+pb->getyear()+"_logz.png").c_str());
    else
      can->SaveAs(( pb->getfilepath() + "/QuickPlot_"+pb->filename+"_"+obj->GetName()+"_"+pb->getyear()+".png").c_str());
  }
}

void drawTopLabel( std::string label, TCanvas* can) {
  TLatex Toplabel = TLatex();
  Toplabel.SetTextFont(42);
  Toplabel.SetTextAlign(31); // https://root.cern.ch/doc/master/classTAttText.html#ATTTEXT1
  Toplabel.SetTextSize(0.025);
  Toplabel.DrawLatexNDC( 1 - can->GetRightMargin(), 1 - can->GetTopMargin() + 0.01, label.c_str());
}

void drawInfoLabels( PlotBus* pb, TCanvas* can) {
  float textSize = 0.045;
  TLatex Infolabel = TLatex();
  Infolabel.SetTextFont(42);
  Infolabel.SetTextAlign(31); // https://root.cern.ch/doc/master/classTAttText.html#ATTTEXT1
  Infolabel.SetTextSize( textSize);
  
  if ((pb->qcdInfo) || (pb->ControlRegion)) {
    Infolabel.DrawLatexNDC( 1 - can->GetRightMargin() - 0.01, 0.75 - textSize, (pb->getRegionTitle()).c_str());
    for (unsigned int i = 0; i < pb->canvasTags.size(); ++i)
      Infolabel.DrawLatexNDC( 1 - can->GetRightMargin() - 0.01, 0.75 - (((i+2) * textSize) + (i*0.01)), (pb->canvasTags[i]).c_str());
  } else {
    for (unsigned int i = 0; i < pb->canvasTags.size(); ++i)
      Infolabel.DrawLatexNDC( 1 - can->GetRightMargin() - 0.01, 0.75 - (((i+1) * textSize) + (i*0.01)), (pb->canvasTags[i]).c_str());
  }
}

void drawCMSLabel() {
  TLatex CMSlabel = TLatex();
  CMSlabel.DrawLatexNDC( 0.13, 0.95, "#bf{CMS} #it{Preliminary}");
}

void manualbinlabels( PlotBus* pb, TH1* hist) {
  if ( pb->variable.find( "Mu") != std::string::npos)
    manualbinlabelsVsMu( hist);
  else
    manualbinlabelsVsJetEle( hist);
}

void manualbinlabelsVsJetEle( TH1* hist) {
  // hist->GetXaxis()->SetTitle("WP");
  hist->GetXaxis()->SetBinLabel( 4,  "VVVLoose");
  hist->GetXaxis()->SetBinLabel( 6,  "VVLoose");
  hist->GetXaxis()->SetBinLabel( 8,  "VLoose");
  hist->GetXaxis()->SetBinLabel( 10,  "Loose");
  hist->GetXaxis()->SetBinLabel( 12, "Medium");
  hist->GetXaxis()->SetBinLabel( 14, "Tight");
  hist->GetXaxis()->SetBinLabel( 16, "VTight");
  hist->GetXaxis()->SetBinLabel( 18, "VVTight");
}

void manualbinlabelsVsMu( TH1* hist) {
  // hist->GetXaxis()->SetTitle("WP");
  hist->GetXaxis()->SetBinLabel( 4,  "VLoose");
  hist->GetXaxis()->SetBinLabel( 6,  "Loose");
  hist->GetXaxis()->SetBinLabel( 8, "Medium");
  hist->GetXaxis()->SetBinLabel( 10, "Tight");
}

#endif
