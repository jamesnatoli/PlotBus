// Header file for PlotTrain
#ifndef PLOT_TRAIN_H
#define PLOT_TRAIN_H

#include <iostream>

#include "PlotBus.h"

class PlotTrain : public PlotBus {
 public:
  // Constructors
  PlotTrain();
  PlotTrain( std::string);
  PlotTrain( std::string, std::string , std::string);
  PlotTrain( std::vector<std::string>);

  // Fields
  bool singleyear;
  bool drawAllYears;
  std::string yearName;
  std::vector<std::string> years;
  std::vector<PlotBus*> train;

  // Member Functions
  void SimplePlot();
  void AddToHists( std::pair<std::string, TH1*>);
  std::string getyear();
  std::string getTopLabel();
};

#endif
