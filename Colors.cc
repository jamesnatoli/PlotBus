#ifndef COLORS_H
#define COLORS_H

#include "TColor.h"

#include <iostream>

#include "PlotBus.h"

std::map<std::string, int> PlotBus::colors{
  {"DY", kOrange-4},
    {"ST", 38},
      {"TT", 592},
	{"ttV", 408},
	  {"VV", 45},
	    {"VVV", 794},
	      {"W+Jets", 50},
		{"QCD MC", 606},
		  {"QCD Estimation", 632},
		  // Bin by bin Estimation
		    {"QCD Est Bins", kOrange},
		      {"QCD", 606},
			{"QCD SS", 606},
			  {"W3pi", 2},
			    {"MultiBoson", 45},
			      {"Top", kBlue-8},
				{"tt and single t", kBlue-8},
				  {"Others", kGreen-3},
				    {"ST_Top",kBlack},
				      {"ST_AntiTop", kBlack},
					{"ST Nominal", kBlack},
					  {"TTo2L2Nu",kBlack},
					    {"TTToSemiLeptonic", kBlack},
					      {"TTTohadronic", kBlack},
						{ "TT Nominal", kBlack},
						  {"MC", kGreen},
						  // Tuned Samples
						    {"ST Up", kBlue},
						      {"ST Down", kGreen},
							{"ST_TopUp", kBlue},
							  {"ST_TopDown", kGreen},
							    {"ST_AntiTopUp", kRed},
							      {"ST_AntiTopDown", kOrange},
								{"TT Up", kBlue},
								  {"TT Down", kGreen},
								    {"TTTo2L2Nu_Up", kBlue},
								      {"TTTo2L2Nu_Down", kGreen},
									{"TTToSemiLeptnic_Up", kBlue},
									  {"TTToSemiLeptonic_Down", kGreen},
									    {"TTToHadronic_Up", kBlue},
									      {"TTTohadronic_Down", kGreen},
										{"Wto3pi2017", kRed},
										  {"Wto3pi2018", kGreen},
										    {"Wto3pi_LO", kRed},
										      {"Signal WJetsTo3Pi", kBlue},
											{"WJetsTo3Pi", kBlue},
											  {"W0JetsTo3Pi", kRed-3},
											    {"W1JetsTo3Pi", kOrange-4},
											      {"W2JetsTo3Pi", kGreen-3},
												{"WJetsTo3Pi_0J", kRed-3},
												  {"WJetsTo3Pi_1J", kOrange-4},
												    {"WJetsTo3Pi_2J", kGreen-3},
												      {"WJetsTo3Pi_012J", kBlue-8},
													{"WJetsTo3Pi_Incl", kBlue},
													  {"", kGray}
};

// strip the region if necessary
int PlotBus::getColors( std::string proc) {
  if (usePalette) {
    if (paletteColors.find( proc) != paletteColors.end()) {
      std::cout << "color already exists: " << paletteColors[proc] << std::endl;
      return paletteColors[proc];
    } else {
      std::cout << "adding color: " << TColor::GetPalette()[colorIdx] << std::endl;
      paletteColors[proc] = TColor::GetPalette()[colorIdx++];
    }
  }
  
  if ( proc.find("_") != std::string::npos)
    return colors[proc];
  else
    return colors[ proc.substr(0, proc.find("_"))];
}

const char* PlotBus::getSignalFill() {
  if (fillSignal)
    return "f";
  else
    return "l";
      
}

const char* PlotBus::getHistFill() {
  if (fillHists)
    return "f";
  else
    return "l";
      
}


#endif // COLORS_H
