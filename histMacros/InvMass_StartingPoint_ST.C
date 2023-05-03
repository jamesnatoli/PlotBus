{
//========= Macro generated from object: procSTA/PionTriplet_MassInv {((XSecMCweight * Generator_weight * PUweight * PionTriplet_TauSFweight)) * ( (PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso >= 0) && (abs(PionTriplet_pion1_dxy) < 100.000000) && (abs(PionTriplet_pion2_dxy) < 100.000000) && (abs(PionTriplet_pion3_dxy) < 100.000000) && (abs(PionTriplet_pion1_dz) < 100.000000) && (abs(PionTriplet_pion2_dz) < 100.000000) && (abs(PionTriplet_pion3_dz) < 100.000000) && ((PionTriplet_pion3_iso < 0.1)) && ((PionTriplet_LowestDeepTauVsJet >= 31)) &&  (1)  && (PionTriplet_pt > 40))) && Trigger_ditau && !LeptonVeto && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (abs(PionTriplet_charge) == 1) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso >= 0) && (abs(PionTriplet_pion1_dxy) < 100.000000) && (abs(PionTriplet_pion2_dxy) < 100.000000) && (abs(PionTriplet_pion3_dxy) < 100.000000) && (abs(PionTriplet_pion1_dz) < 100.000000) && (abs(PionTriplet_pion2_dz) < 100.000000) && (abs(PionTriplet_pion3_dz) < 100.000000) && 1 &&  (1)  && (PionTriplet_pt > 40) && ((PionTriplet_pion3_iso < 0.1)) && ((PionTriplet_LowestDeepTauVsJet >= 31)))}
//========= by ROOT version6.19/01
   
   TH1F *procSTA__3 = new TH1F("procSTA__3","PionTriplet_MassInv {((XSecMCweight * Generator_weight * PUweight * PionTriplet_TauSFweight)) * ( (PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso >= 0) && (abs(PionTriplet_pion1_dxy) < 100.000000) && (abs(PionTriplet_pion2_dxy) < 100.000000) && (abs(PionTriplet_pion3_dxy) < 100.000000) && (abs(PionTriplet_pion1_dz) < 100.000000) && (abs(PionTriplet_pion2_dz) < 100.000000) && (abs(PionTriplet_pion3_dz) < 100.000000) && ((PionTriplet_pion3_iso < 0.1)) && ((PionTriplet_LowestDeepTauVsJet >= 31)) &&  (1)  && (PionTriplet_pt > 40))) && Trigger_ditau && !LeptonVeto && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (abs(PionTriplet_charge) == 1) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso >= 0) && (abs(PionTriplet_pion1_dxy) < 100.000000) && (abs(PionTriplet_pion2_dxy) < 100.000000) && (abs(PionTriplet_pion3_dxy) < 100.000000) && (abs(PionTriplet_pion1_dz) < 100.000000) && (abs(PionTriplet_pion2_dz) < 100.000000) && (abs(PionTriplet_pion3_dz) < 100.000000) && 1 &&  (1)  && (PionTriplet_pt > 40) && ((PionTriplet_pion3_iso < 0.1)) && ((PionTriplet_LowestDeepTauVsJet >= 31)))}",35,0,350);
   procSTA__3->SetBinContent(5,0.112343);
   procSTA__3->SetBinContent(6,0.225092);
   procSTA__3->SetBinContent(10,0.254118);
   procSTA__3->SetBinContent(11,0.138421);
   procSTA__3->SetBinContent(13,0.134161);
   procSTA__3->SetBinContent(17,0.279798);
   procSTA__3->SetBinContent(19,0.0403781);
   procSTA__3->SetBinError(5,0.112343);
   procSTA__3->SetBinError(6,0.225092);
   procSTA__3->SetBinError(10,0.254118);
   procSTA__3->SetBinError(11,0.104764);
   procSTA__3->SetBinError(13,0.127272);
   procSTA__3->SetBinError(17,0.24275);
   procSTA__3->SetBinError(19,0.0403781);
   procSTA__3->SetEntries(10);
   procSTA__3->SetStats(0);
   procSTA__3->SetFillColor(38);
   procSTA__3->GetXaxis()->SetLabelFont(42);
   procSTA__3->GetXaxis()->SetLabelSize(0.035);
   procSTA__3->GetXaxis()->SetTitleSize(0.035);
   procSTA__3->GetXaxis()->SetTitleOffset(1);
   procSTA__3->GetXaxis()->SetTitleFont(42);
   procSTA__3->GetYaxis()->SetLabelFont(42);
   procSTA__3->GetYaxis()->SetLabelSize(0.035);
   procSTA__3->GetYaxis()->SetTitleSize(0.035);
   procSTA__3->GetYaxis()->SetTitleFont(42);
   procSTA__3->GetZaxis()->SetLabelFont(42);
   procSTA__3->GetZaxis()->SetLabelSize(0.035);
   procSTA__3->GetZaxis()->SetTitleSize(0.035);
   procSTA__3->GetZaxis()->SetTitleOffset(1);
   procSTA__3->GetZaxis()->SetTitleFont(42);
   procSTA__3->Draw("");
}
