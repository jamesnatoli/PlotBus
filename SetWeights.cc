// These are messy so put them hereA
#ifndef SET_WEIGHTS
#define SET_WEIGHTS

#include <iostream>

#include "PlotBus.h"

void PlotBus::SetWeights() {
  std::cout << "*** SETTING WEIGHTS *** " << std::endl;
  // Keep the various MC weights here
  DxyDzWeight = "PionTriplet_DxyDz_Weight";
  TauSFweight = "PionTriplet_TauSFweight_JetLoose_MuTight_ElVVLoose";
  // TauSFweight = "PionTriplet_TauSFweight";
  TTbar_NNLOweight = "Weight_TTbar_NNLO";
  dataWeight  = "(1)"; // this sucks
  std::string extraweight = "!(PionTriplet_genMatch_ABCD_FS)";
  // std::string extraweight = "(1)";
  stdMCweight = "(XSecMCweight * Generator_weight * PUweight * L1PreFiringWeight_Nom * " + TauSFweight + " * " + DxyDzWeight + " * " + extraweight + ")";
  stitchMCweight = "(Generator_weight * PUweight * L1PreFiringWeight_Nom * " + TauSFweight + " * " + DxyDzWeight + " * " + extraweight + ")";
  stitchDY = "StitchWeight_DY_NLO";
  
  // Signal Weights
  weights["WJetsTo3Pi_Plus"]  = "(XSecMCweight * Generator_weight * PUweight * L1PreFiringWeight_Nom * " + TauSFweight + " * " + DxyDzWeight + ")";
  weights["WJetsTo3Pi_Minus"] = "(XSecMCweight * Generator_weight * PUweight * L1PreFiringWeight_Nom * " + TauSFweight + " * " + DxyDzWeight + ")";

  if (year == "2018") {
    Luminosity  = 59.8;
    dataTakingEras = {"A", "B", "C", "D"};
    stitchDY_LO = "(LHE_Njets==0?1.83962:1)*(LHE_Njets==1?0.640187:1)*(LHE_Njets==2?0.536282:1)*(LHE_Njets==3?0.308694:1)*(LHE_Njets==4?0.29352:1)*(LHE_Njets>4?1.83962:1)";
    stitchWJ  = "(LHE_Njets==0?2.1238030067e-04:1)*(LHE_Njets==1?9.4034644862e-05:1)*(LHE_Njets==2?7.8360783678e-05:1)*(LHE_Njets>2?8.1203167262e-05:1)";
    stitchSig = "(LHE_Njets==0?0.0105299824926447:1)*(LHE_Njets==1?0.00606325562585755:1)*(LHE_Njets==2?0.00302993818070353:1)*(LHE_Njets>2?0.00298764685424956:1)";
    
    // Filter Eff * XSec * Lumi * 1000 / SumW
    // std::string kFactor = "((0.0112 * PionTriplet_pt) + 0.9525)";
    // weights["Wto3pi_LO"] = "( 0.1784 * 193200 * " + getLumi() + " * 1000 * (1/SumOfWeights)) * " + stitchMCweight + " * " + kFactor;
    // weights["Wto3pi_LO"] = "( 0.1784 * 193200 * " + getLumi() + " * 1000 * (1/SumOfWeights)) * " + stitchMCweight;
    // weights["WJetsTo3Pi_Incl"] = "1.449E-02 * " + stitchMCweight; 
    // weights["WJetsTo3Pi_0J"] =   "3.918E-02 * " + stitchMCweight; 
    // weights["WJetsTo3Pi_1J"] =   "7.082E-03 * " + stitchMCweight;
    // weights["WJetsTo3Pi_2J"] =   "3.763E-03 * " + stitchMCweight; 
  } else if (year == "2017") {
    Luminosity  = 41.5;
    dataTakingEras = {"B", "C", "D", "E", "F"};
    stitchDY_LO  = "(LHE_Njets==0?1.23734:1)*(LHE_Njets==1?0.414618:1)*(LHE_Njets==2?0.370996:1)*(LHE_Njets==3?0.215047:1)*(LHE_Njets==4?0.164546:1)*(LHE_Njets>4?1.23734:1)";
    stitchWJ  = "(LHE_Njets==0?1.5334343878e-04:1)*(LHE_Njets==1?6.7497287730e-05:1)*(LHE_Njets==2?5.4048680964e-05:1)*(LHE_Njets>2?5.5666140133e-05:1)";
    stitchSig = "(LHE_Njets==0?0.00673224070424593:1)*(LHE_Njets==1?0.00400568885684673:1)*(LHE_Njets==2?0.00208664687920168:1)*(LHE_Njets>2?0.0020592304545782:1)";
    
    // Filter Eff * XSec * Lumi * 1000 / SumW
    // std::string kFactor = "((0.0112 * PionTriplet_pt) + 0.9525)";
    // weights["Wto3pi_LO"] = "(0.0807 * 193200 * " + getLumi() + " * 1000 * (1/SumOfWeights)) * " + stitchMCweight + " * " + kFactor;
    // weights["WJetsTo3Pi_Incl"] = "8.962E-03 * " + stitchMCweight;
    // weights["WJetsTo3Pi_0J"] =   "2.706E-02 * " + stitchMCweight; 
    // weights["WJetsTo3Pi_1J"] =   "4.915E-03 * " + stitchMCweight;
    // weights["WJetsTo3Pi_2J"] =   "2.674E-03 * " + stitchMCweight; 
  } else if (year == "2016_preVFP"){
    Luminosity  = 19.5;
    dataTakingEras = {"Bv1", "Bv2", "C", "D", "E", "F"};
    stitchDY_LO  = "(LHE_Njets==0?1.24647:1)*(LHE_Njets==1?0.407339:1)*(LHE_Njets==2?0.37297:1)*(LHE_Njets==3?0.20135:1)*(LHE_Njets==4?0.178672:1)*(LHE_Njets>4?1.24647:1)";
    stitchWJ  = "(LHE_Njets==0?7.6176665591e-05:1)*(LHE_Njets==1?3.2866842007e-05:1)*(LHE_Njets==2?2.7493712509e-05:1)*(LHE_Njets>2?2.8571509261e-05:1)";
    stitchSig = "(LHE_Njets==0?0.00489486008276629:1)*(LHE_Njets==1?0.00270731990415146:1)*(LHE_Njets==2?0.0018145299943565:1)*(LHE_Njets>2?0.00180477098953077:1)";
    
    // weights["WJetsTo3Pi_Incl"] = "6.471E-03 * " + stitchMCweight;
    // weights["WJetsTo3Pi_0J"] =   "2.010E-02 * " + stitchMCweight; 
    // weights["WJetsTo3Pi_1J"] =   "3.107E-03 * " + stitchMCweight;
    // weights["WJetsTo3Pi_2J"] =   "2.503E-03 * " + stitchMCweight; 
  } else if (year == "2016_postVFP"){
    Luminosity  = 16.8;
    dataTakingEras = {"F", "G", "H"};
    
    // Year specific weights
    stitchDY_LO  = "(LHE_Njets==0?1.23905:1)*(LHE_Njets==1?0.369997:1)*(LHE_Njets==2?0.301981:1)*(LHE_Njets==3?0.188731:1)*(LHE_Njets==4?0.163158:1)*(LHE_Njets>4?1.23905:1)";
    stitchWJ  = "(LHE_Njets==0?6.3492381179e-05:1)*(LHE_Njets==1?2.8788703517e-05:1)*(LHE_Njets==2?2.4297924110e-05:1)*(LHE_Njets>2?2.5215777910e-05:1)";
    stitchSig = "(LHE_Njets==0?0.00215321187273397:1)*(LHE_Njets==1?0.00184967752063547:1)*(LHE_Njets==2?0.00104531704219893:1)*(LHE_Njets>2?0.00102972287986206:1)";
    
    // weights["WJetsTo3Pi_Incl"] = "3.280E-03 * " + stitchMCweight;
    // weights["WJetsTo3Pi_0J"] =   "6.268E-03 * " + stitchMCweight; 
    // weights["WJetsTo3Pi_1J"] =   "3.506E-03 * " + stitchMCweight;
    // weights["WJetsTo3Pi_2J"] =   "1.501E-03 * " + stitchMCweight; 
  } else {
    stitchDY    = "(1)";
    stitchWJ    = "(1)";
    stitchSig   = "(1)";
    TTbar_NNLOweight = "(1)";
    std::cout << "ERROR!!! Not a valid year: " << year << std::endl;
    std::cout << "Will use 2018 Luminosity (59.83) by default, unless set manually" << std::endl;
    Luminosity  = 59.8;
  }

  // this needs to be after years... kind of weird
  MCweights   = {
		 {"DY10",   stdMCweight},
		 {"DY",     "(" + stitchDY + " * " + stitchMCweight + ")"},
		 {"DY_LO",     "(" + stitchDY_LO + " * Generator_weight * PUweight * L1PreFiringWeight_Nom * PionTriplet_TauSFweight_Loose * " + DxyDzWeight + ")"},
		 // {"DY1",    "(" + stitchDY + " * " + stitchMCweight + ")"},
		 // {"DY2",    "(" + stitchDY + " * " + stitchMCweight + ")"},
		 // {"DY3",    "(" + stitchDY + " * " + stitchMCweight + ")"},
		 // {"DY4",    "(" + stitchDY + " * " + stitchMCweight + ")"},
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
