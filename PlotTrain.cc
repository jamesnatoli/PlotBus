#ifndef PLOT_TRAIN_CC
#define PLOT_TRAIN_CC

#include <iomanip>

#include "PlotTrain.h"
#include "PlotUtils.h"

// Default Constructor for Full Run 2 Plots
PlotTrain::PlotTrain(): PlotBus() {
  // PlotBus::Init();

  years = {"2016_preVFP", "2016_postVFP", "2017", "2018"};
  yearName = "Run 2 UL";
  train = {};
}

// For single plotting
PlotTrain::PlotTrain( std::string year): PlotBus(year){ 
  singleyear   = true;
  drawAllYears = true;

  train = {};
  years = {year};
}

// Multipurpose 
PlotTrain::PlotTrain( std::vector<std::string> years) {
  PlotBus::Init(); // year will be setup later...

  singleyear = (years.size() == 1);
  drawAllYears = false || singleyear;
  yearName = "";
  train = {};
  PlotTrain::years = years;
}

// Overwritten from PlotBus, draws the Busses
void PlotTrain::SimplePlot() {
  PlotBus* temp; // do I need temp?
  for (auto year : years) {
    setupYear(year);
    justDraw = !drawAllYears;
    temp = new PlotBus( *this); // cast?
    train.push_back( temp);
  }

  filepath = "plots";
  for (auto pb : train) {
    std::cout << "Drawing Year: " << pb->year << std::endl;
    filepath += "_" + pb->year;
    pb->SimplePlot();
    if (verbosity > 1)
      pb->PrintYields();
    Luminosity += pb->Luminosity;
    for (auto&& ele : pb->hists)
      AddToHists( ele);
  }
    
  filepath += "/";
  // Do I need this? I don't make a Train plot if it's just one year...
  if (train.size() == 1) {
    std::cout << "train[0]->filepath: " << train[0]->filepath << std::endl;
    filepath = train[0]->filepath;
  }

  // Quick chi2 for qcd
  if (doChi2) {
    TH1* prediction = dynamic_cast<TH1*>(hists["QCD"]->Clone());
    for (auto&& ele : hists) {
      if (!(isSignal(ele.first)) && !(isData(ele.first)) && (ele.first != "QCD")) { // because it's a Clone of QCD
	if (verbosity > 1) {
	  std::cout << "adding to prediction: " << ele.first << "(" << ele.second->GetSumOfWeights() << ")" << std::endl;
	}
	prediction->Add(ele.second);
      }
    }
    CalcChi2( hists[dataName], prediction);
  }

  if (!singleyear) {
    year = "train";
    std::cout << "\n*** Starting combined plot... " << std::endl;
    makeRegionPlot( hists, this, "A");
  } else {
    std::cout << "Only one year... skipping train plot" << std::endl;
  }
  std::cout << "Train filepath: " << filepath << std::endl;
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

std::string PlotTrain::getTopLabel() {
  std::string topLabel = "";
  for (auto yr : years) {
    if (topLabel == "")
      topLabel += "UL" + yr;
    else
      topLabel += "+UL" + yr;
  }
  topLabel += ", ";

  if (yearName != "")
    topLabel = yearName + ", ";

  std::cout << "Luminosity: " << Luminosity << std::endl;
  std::cout << "getLumi(): " <<  getLumi()  << std::endl;
  if (verbosity > -1)
    std::cout << "Top Label: " << topLabel << std::endl;
  topLabel += getLumi() + " fb^{-1} (13 TeV)";
  return topLabel;
}

#endif
