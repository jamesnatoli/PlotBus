#ifndef PLOT_TRAIN_CC
#define PLOT_TRAIN_CC

#include "PlotTrain.h"
#include "PlotUtils.h"

PlotTrain::PlotTrain( std::vector<std::string> years) {
  PlotBus::Init();
  
  train = {};
  yearName = "";
  PlotTrain::years = years;
}

// Overwritten from PlotBus, draws the Busses
void PlotTrain::SimplePlot() {
  for (auto year : years) {
    setupYear(year);
    filepath = "plots_" + getyear() + "/";
    justDraw = true;
    train.push_back(new PlotBus( *dynamic_cast<PlotBus*>(this)));
  }
  
  for (auto pb : train) {
    pb->SimplePlot();
    Luminosity += pb->Luminosity;
    for (auto&& ele : pb->hists)
      AddToHists( ele);
  }

  makeRegionPlot( hists, this, "A");
  return;
}

void PlotTrain::AddToHists( std::pair<std::string, TH1*> ele) {
  if ( hists.find(ele.first) != hists.end())
    hists[ele.first]->Add( ele.second);
  else
    hists[ele.first] = ele.second;
}

// Overwritten again
std::string PlotTrain::getyear() {
  std::string out = "";
  for (auto yr : years)
    if (out == "")
      out += yr;
    else
      out += "_" + yr;

  return out;
}

const char* PlotTrain::getTopLabel() {
  std::string label = "";
  for (auto yr : years) {
    if (label == "")
      label += "UL" + yr;
    else
      label += "+UL" + yr;
  }
  
  if (yearName != "")
    label = yearName;
  
  label += ", " + getLumi().substr(0, 4)+" fb^{-1} (13 TeV)";
  return label.c_str();
}

#endif
