// Function definitions for PlotUtils.cc
#ifndef PLOTUTILS_H
#define PLOTUTILS_H

#include "TH1F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TList.h"

#include <string>

#include "PlotBus.h"

// Plotters
void makeMyRatio( PlotBus*, THStack*, TH1*, TCanvas*);
void makeMyRatio( PlotBus*, TH1*, TH1*, TCanvas*);
void makeRatioPlot( TH1*, PlotBus*, std::string="Region C over D", std::string="Normalization Ratio");
void makePlot( std::map<std::string, TH1*>, PlotBus*);
void makeRegionPlot( std::map<std::string, TH1*>, PlotBus*, std::string);

// Helpers
void drawTallest( TList*, PlotBus*);
THStack* sortStack( TList*);
float getMaximumWithErrors( TH1*);
TH1* getStackSum(THStack*);
void drawTopLabel( std::string, TCanvas*);
void drawInfoLabels( PlotBus*, TCanvas*);
void drawCMSLabel();
void manualbinlabels( PlotBus*, TH1*);
void manualbinlabelsVsMu( TH1*);
void manualbinlabelsVsJetEle( TH1*);

#endif
