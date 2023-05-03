{
//========= Macro generated from object: procW+JetsA/PionTriplet_MassInv {(((LHE_Njets==0?0.000243068:1)*(LHE_Njets==1?4.76252e-05:1)*(LHE_Njets==2?5.72344e-05:1)*(LHE_Njets>2?3.33674e-05:1) * (PUweight * PionTriplet_TauSFweight))) * ( (PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso >= 0) && (abs(PionTriplet_pion1_dxy) < 100.000000) && (abs(PionTriplet_pion2_dxy) < 100.000000) && (abs(PionTriplet_pion3_dxy) < 100.000000) && (abs(PionTriplet_pion1_dz) < 100.000000) && (abs(PionTriplet_pion2_dz) < 100.000000) && (abs(PionTriplet_pion3_dz) < 100.000000) && ((PionTriplet_pion3_iso < 0.1)) && ((PionTriplet_LowestDeepTauVsJet >= 31)) &&  (1)  && (PionTriplet_pt > 40))) && Trigger_ditau && !LeptonVeto && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (abs(PionTriplet_charge) == 1) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso >= 0) && (abs(PionTriplet_pion1_dxy) < 100.000000) && (abs(PionTriplet_pion2_dxy) < 100.000000) && (abs(PionTriplet_pion3_dxy) < 100.000000) && (abs(PionTriplet_pion1_dz) < 100.000000) && (abs(PionTriplet_pion2_dz) < 100.000000) && (abs(PionTriplet_pion3_dz) < 100.000000) && 1 &&  (1)  && (PionTriplet_pt > 40) && ((PionTriplet_pion3_iso < 0.1)) && ((PionTriplet_LowestDeepTauVsJet >= 31)))}
//========= by ROOT version6.19/01
   
   TH1F *procWpLJetsA__7 = new TH1F("procWpLJetsA__7","PionTriplet_MassInv {(((LHE_Njets==0?0.000243068:1)*(LHE_Njets==1?4.76252e-05:1)*(LHE_Njets==2?5.72344e-05:1)*(LHE_Njets>2?3.33674e-05:1) * (PUweight * PionTriplet_TauSFweight))) * ( (PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso >= 0) && (abs(PionTriplet_pion1_dxy) < 100.000000) && (abs(PionTriplet_pion2_dxy) < 100.000000) && (abs(PionTriplet_pion3_dxy) < 100.000000) && (abs(PionTriplet_pion1_dz) < 100.000000) && (abs(PionTriplet_pion2_dz) < 100.000000) && (abs(PionTriplet_pion3_dz) < 100.000000) && ((PionTriplet_pion3_iso < 0.1)) && ((PionTriplet_LowestDeepTauVsJet >= 31)) &&  (1)  && (PionTriplet_pt > 40))) && Trigger_ditau && !LeptonVeto && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (abs(PionTriplet_charge) == 1) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso >= 0) && (abs(PionTriplet_pion1_dxy) < 100.000000) && (abs(PionTriplet_pion2_dxy) < 100.000000) && (abs(PionTriplet_pion3_dxy) < 100.000000) && (abs(PionTriplet_pion1_dz) < 100.000000) && (abs(PionTriplet_pion2_dz) < 100.000000) && (abs(PionTriplet_pion3_dz) < 100.000000) && 1 &&  (1)  && (PionTriplet_pt > 40) && ((PionTriplet_pion3_iso < 0.1)) && ((PionTriplet_LowestDeepTauVsJet >= 31)))}",35,0,350);
   procWpLJetsA__7->SetBinContent(8,3.90062e-05);
   procWpLJetsA__7->SetBinContent(11,3.15314e-05);
   procWpLJetsA__7->SetBinContent(27,1.95045e-05);
   procWpLJetsA__7->SetBinContent(36,4.54915e-05);
   procWpLJetsA__7->SetBinError(8,3.90062e-05);
   procWpLJetsA__7->SetBinError(11,3.15314e-05);
   procWpLJetsA__7->SetBinError(27,1.95045e-05);
   procWpLJetsA__7->SetBinError(36,4.54915e-05);
   procWpLJetsA__7->SetEntries(4);
   procWpLJetsA__7->SetStats(0);
   procWpLJetsA__7->SetFillColor(50);
   procWpLJetsA__7->GetXaxis()->SetLabelFont(42);
   procWpLJetsA__7->GetXaxis()->SetLabelSize(0.035);
   procWpLJetsA__7->GetXaxis()->SetTitleSize(0.035);
   procWpLJetsA__7->GetXaxis()->SetTitleOffset(1);
   procWpLJetsA__7->GetXaxis()->SetTitleFont(42);
   procWpLJetsA__7->GetYaxis()->SetLabelFont(42);
   procWpLJetsA__7->GetYaxis()->SetLabelSize(0.035);
   procWpLJetsA__7->GetYaxis()->SetTitleSize(0.035);
   procWpLJetsA__7->GetYaxis()->SetTitleFont(42);
   procWpLJetsA__7->GetZaxis()->SetLabelFont(42);
   procWpLJetsA__7->GetZaxis()->SetLabelSize(0.035);
   procWpLJetsA__7->GetZaxis()->SetTitleSize(0.035);
   procWpLJetsA__7->GetZaxis()->SetTitleOffset(1);
   procWpLJetsA__7->GetZaxis()->SetTitleFont(42);
   procWpLJetsA__7->Draw("");
}
