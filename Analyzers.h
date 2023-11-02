// Function definitions for Analyzer.cc
// James Natoli
#ifndef ANALYZERS_H
#define ANALYZERS_H

#include "TH1F.h"
#include "THStack.h"
#include "TLegend.h"

#include <string>

#include "PlotBus.h"

// Analyzer.cc
void analyze( TH1*, float);
void signalSignifigance( TH1*, THStack*, PlotBus*);
void printYields( std::map<std::string, std::vector<std::string>>, int, std::string="");
void CalculateYields( std::map<std::string, TH1*>, std::map<std::string, std::vector<std::string>>*, TLegend*, PlotBus*, int);
void getYieldsAndEntries( std::map<std::string, TH1*>, TLegend*, PlotBus*);

#endif
