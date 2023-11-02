// These are messy so put them here
#ifndef SET_WEIGHTS
#define SET_WEIGHTS

#include <iostream>

#include "PlotBus.h"

void PlotBus::SetWeights() {
  TTbar_NNLOweight = "Weight_TTbar_NNLO";
  std::string kFactor = "((0.0112 * PionTriplet_pt) + 0.9525)";
  // Keep the various MC weights here
  // DxyDzWeight = "IPweight( abs(PionTriplet_pion1_dxy), abs(PionTriplet_pion1_dz), abs(PionTriplet_pion2_dxy), abs(PionTriplet_pion2_dz), abs(PionTriplet_pion3_dxy), abs(PionTriplet_pion3_dz))";
  // DxyDzWeight = "(PionTriplet_DxyDz_Weight)";
  DxyDzWeight = "(1)";
  // this sucks
  dataWeight  = "(1)";
  stdMCweight = "(XSecMCweight * Generator_weight * PUweight * PionTriplet_TauSFweight * " + DxyDzWeight + ")";
  stitchMCweight = "(Generator_weight * PUweight * PionTriplet_TauSFweight * " + DxyDzWeight + ")";

  if (year == 2018) {
    Luminosity  = 59.8;
    dataTakingEras = {"A", "B", "C", "D"};

    // Year specific weights
    stitchDY    = "(LHE_Njets==0?1.83962:1)*(LHE_Njets==1?0.628821:1)*(LHE_Njets==2?0.492408:1)*(LHE_Njets==3?0.233581:1)*(LHE_Njets==4?0.263824:1)*(LHE_Njets>4?1.83962:1)";
    stitchWJ    = "(LHE_Njets==0?2.1238030067e-04:1)*(LHE_Njets==1?9.4034644862e-05:1)*(LHE_Njets==2?7.8360783678e-05:1)*(LHE_Njets>2?8.1203167262e-05:1)";
    stitchSig = "";
    // Filter Eff * XSec * Lumi * 1000 / SumW
    weights["Wto3pi_LO"] = "( 0.1784 * 193200 * " + getLumi() + " * 1000 * (1/SumOfWeights)) * " + stitchMCweight + " * " + kFactor;
    // Not produced yet...
    weights["WJetsTo3Pi_Incl"] = "1.449E-02 * " + stitchMCweight; 
    // weights["WJetsTo3Pi_0J"] =   " * " + stitchMCweight; 
    // weights["WJetsTo3Pi_1J"] =   " * " + stitchMCweight;
    // weights["WJetsTo3Pi_2J"] =   " * " + stitchMCweight; 
  } else if (year == 2017) {
    Luminosity  = 41.5;
    dataTakingEras = {"B", "C", "D", "E", "F"};

    // Year specific weights
    stitchDY = "(LHE_Njets==0?1.23734:1)*(LHE_Njets==1?0.414618:1)*(LHE_Njets==2?0.370996:1)*(LHE_Njets==3?0.215047:1)*(LHE_Njets==4?0.164546:1)*(LHE_Njets>4?1.23734:1)";
    stitchWJ = "(LHE_Njets==0?1.5334343878e-04:1)*(LHE_Njets==1?6.7497287730e-05:1)*(LHE_Njets==2?5.4048680964e-05:1)*(LHE_Njets>2?5.5666140133e-05:1)";
    stitchSig = "";
    // Filter Eff * XSec * Lumi * 1000 / SumW
    weights["Wto3pi_LO"] = "(0.0807 * 193200 * " + getLumi() + " * 1000 * (1/SumOfWeights)) * " + stitchMCweight + " * " + kFactor;
    weights["WJetsTo3Pi_Incl"] = "8.962E-03 * " + stitchMCweight;
    // Not produced yet... 
    // weights["WJetsTo3Pi_0J"] =   " * " + stitchMCweight; 
    // weights["WJetsTo3Pi_1J"] =   " * " + stitchMCweight;
    // weights["WJetsTo3Pi_2J"] =   " * " + stitchMCweight; 
  } else if (year == 2016){
    if (postVFP) {
      Luminosity  = 16.8;
      dataTakingEras = {"F", "G", "H"};

      // Year specific weights
      stitchDY  = "(LHE_Njets==0?1.23905:1)*(LHE_Njets==1?0.369997:1)*(LHE_Njets==2?0.301981:1)*(LHE_Njets==3?0.188731:1)*(LHE_Njets==4?0.163158:1)*(LHE_Njets>4?1.23905:1)";
      stitchWJ  = "(LHE_Njets==0?6.3492381179e-05:1)*(LHE_Njets==1?2.8788703517e-05:1)*(LHE_Njets==2?2.4297924110e-05:1)*(LHE_Njets>2?2.5215777910e-05:1)";
      stitchSig = "(LHE_Njets==0?0.00215321187273397:1)*(LHE_Njets==1?0.00184967752063547:1)*(LHE_Njets==2?0.00104531704219893:1)*(LHE_Njets>2?0.00102972287986206:1)";
      weights["WJetsTo3Pi_Incl"] = "3.280E-03 * " + stitchMCweight;
      weights["WJetsTo3Pi_0J"] =   "6.268E-03 * " + stitchMCweight; 
      weights["WJetsTo3Pi_1J"] =   "3.506E-03 * " + stitchMCweight;
      weights["WJetsTo3Pi_2J"] =   "1.501E-03 * " + stitchMCweight; 

    } else if (preVFP) {
      Luminosity  = 19.5;
      dataTakingEras = {"B", "C", "D", "E", "F"};
      
      std::cout << "No DY stitching weights for year: " << std::to_string( year) << std::endl;
      stitchDY = "(LHE_Njets==0?1.24647:1)*(LHE_Njets==1?0.407339:1)*(LHE_Njets==2?0.37297:1)*(LHE_Njets==3?0.20135:1)*(LHE_Njets==4?0.178672:1)*(LHE_Njets>4?1.24647:1)";
      stitchWJ = "(LHE_Njets==0?7.6176665591e-05:1)*(LHE_Njets==1?3.2866842007e-05:1)*(LHE_Njets==2?2.7493712509e-05:1)*(LHE_Njets>2?2.8571509261e-05:1)";
      stitchSig = "";
      weights["WJetsTo3Pi_Incl"] = "6.471E-03 * " + stitchMCweight;
    }
  } else {
    stitchDY    = "(1)";
    stitchWJ    = "(1)";
    stitchSig   = "(1)";
    TTbar_NNLOweight = "(1)";
    std::cout << "ERROR!!! Not a valid year: " << std::to_string( year) << std::endl;
    std::cout << "Will use 2018 Luminosity (59.83) by default, unless set manually" << std::endl;
    Luminosity  = 59.8;
  }

  // this needs to be after years... kind of weird
  MCweights   = {
		 {"DY10",   stdMCweight},
		 {"DY",     "(" + stitchDY + " * " + stitchMCweight + ")"},
		 {"DY1",    "(" + stitchDY + " * " + stitchMCweight + ")"},
		 {"DY2",    "(" + stitchDY + " * " + stitchMCweight + ")"},
		 {"DY3",    "(" + stitchDY + " * " + stitchMCweight + ")"},
		 {"DY4",    "(" + stitchDY + " * " + stitchMCweight + ")"},
		 {"W+Jets", "(" + stitchWJ + " * " + stitchMCweight + ")"},
		 {"ST",     stdMCweight},
		 {"TT",     "(" + stdMCweight + "*" + TTbar_NNLOweight + ")"},
		 {"ttV",    stdMCweight},
		 {"VV",     stdMCweight},
		 {"VVV",    stdMCweight},
		 {"QCD MC", qcdMCweight},
  };
  for (auto ele : MCweights)
    weights[ele.first] = ele.second;
}

#endif
