// Header file for PlotTrain
#ifndef PLOT_TRAIN_H
#define PLOT_TRAIN_H

#include <iostream>

#include "PlotBus.h"

class PlotTrain : public PlotBus {
 public:
  // Constructors
  PlotTrain();
  PlotTrain( std::vector<std::string>);

  // Fields
  std::string yearName;
  std::vector<std::string> years;
  std::vector<PlotBus*> train;

  // Member Functions
  // std::map<std::string, TH1F*> SimplePlot();
  void SimplePlot();
  void AddToHists( std::pair<std::string, TH1*>);
  std::string getyear();
  const char* getTopLabel();
};

#endif
