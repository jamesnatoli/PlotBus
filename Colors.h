#ifndef COLORS_H
#define COLORS_H

#include "TColor.h"
#include "PlotBus.cc"
// Maybe add a thing such that if the color isn't found it gives is a random one?

std::map<std::string, int> PlotBus::colors{
  {"DY", 865},
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
			{"W3pi", 2},
			  {"MultiBoson", kOrange},
			    {"Top", kGreen},
			      {"Others", kGreen},
				{"ST_Top",kBlack},
				  {"ST_AntiTop", kBlack},
				    {"ST Nominal", kBlack},
				      {"TTo2L2Nu",kBlack},
					{"TTToSemiLeptonic", kBlack},
					  {"TTTohadronic", kBlack},
					    { "TT Nominal", kBlack},
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
									  {"", kGray}
};

// strip the region if necessary
int getColors( std::string proc) {
  if ( proc.find("_") != std::string::npos)
    return PlotBus::colors[proc];
  else
    return PlotBus::colors[ proc.substr(0, proc.find("_"))];
}
#endif // COLORS_H
