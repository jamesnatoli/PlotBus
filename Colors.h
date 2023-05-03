#ifndef COLORS_H
#define COLORS_H

#include "TColor.h"

std::map<std::string, int> colors{
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
			  {"ST_Top",kBlack},
			    {"ST_TopUp", kBlue},
			      {"ST_TopDown", kGreen},
				{"ST_AntiTop", kBlack},
				  {"ST_AntiTopUp", kBlue},
				    {"ST_AntiTopDown", kGreen},
				      {"", kGray}
};
#endif // COLORS_H
