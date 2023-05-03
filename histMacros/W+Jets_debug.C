{
//========= Macro generated from object: bkgW+Jets/PionTriplet_MassInv {(((LHE_Njets==0?0.000243068:1)*(LHE_Njets==1?4.76252e-05:1)*(LHE_Njets==2?5.72344e-05:1)*(LHE_Njets>2?3.33674e-05:1) * PUweight)) * ((PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 31) && (PionTriplet_pion3_iso < 0.100000))) && Trigger_ditau && !LeptonVeto && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (abs(PionTriplet_charge) == 1) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 31) && (PionTriplet_pion3_iso < 0.100000))}
//========= by ROOT version6.19/01
   
   TH1F *bkgWpLJets__1 = new TH1F("bkgWpLJets__1","PionTriplet_MassInv {(((LHE_Njets==0?0.000243068:1)*(LHE_Njets==1?4.76252e-05:1)*(LHE_Njets==2?5.72344e-05:1)*(LHE_Njets>2?3.33674e-05:1) * PUweight)) * ((PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 31) && (PionTriplet_pion3_iso < 0.100000))) && Trigger_ditau && !LeptonVeto && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (abs(PionTriplet_charge) == 1) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 31) && (PionTriplet_pion3_iso < 0.100000))}",40,0,400);
   bkgWpLJets__1->SetBinContent(2,5.76283e-05);
   bkgWpLJets__1->SetBinContent(8,4.72558e-05);
   bkgWpLJets__1->SetBinContent(11,9.7363e-05);
   bkgWpLJets__1->SetBinContent(12,4.66684e-05);
   bkgWpLJets__1->SetBinContent(13,4.8979e-05);
   bkgWpLJets__1->SetBinContent(14,5.76283e-05);
   bkgWpLJets__1->SetBinContent(27,3.26971e-05);
   bkgWpLJets__1->SetBinContent(39,5.73172e-05);
   bkgWpLJets__1->SetBinError(2,5.76283e-05);
   bkgWpLJets__1->SetBinError(8,4.72558e-05);
   bkgWpLJets__1->SetBinError(11,6.99467e-05);
   bkgWpLJets__1->SetBinError(12,4.66684e-05);
   bkgWpLJets__1->SetBinError(13,4.8979e-05);
   bkgWpLJets__1->SetBinError(14,5.76283e-05);
   bkgWpLJets__1->SetBinError(27,3.26971e-05);
   bkgWpLJets__1->SetBinError(39,5.73172e-05);
   bkgWpLJets__1->SetEntries(9);
   bkgWpLJets__1->SetFillColor(19);
   bkgWpLJets__1->GetXaxis()->SetLabelFont(42);
   bkgWpLJets__1->GetXaxis()->SetLabelSize(0.035);
   bkgWpLJets__1->GetXaxis()->SetTitleSize(0.035);
   bkgWpLJets__1->GetXaxis()->SetTitleOffset(1);
   bkgWpLJets__1->GetXaxis()->SetTitleFont(42);
   bkgWpLJets__1->GetYaxis()->SetLabelFont(42);
   bkgWpLJets__1->GetYaxis()->SetLabelSize(0.035);
   bkgWpLJets__1->GetYaxis()->SetTitleSize(0.035);
   bkgWpLJets__1->GetYaxis()->SetTitleFont(42);
   bkgWpLJets__1->GetZaxis()->SetLabelFont(42);
   bkgWpLJets__1->GetZaxis()->SetLabelSize(0.035);
   bkgWpLJets__1->GetZaxis()->SetTitleSize(0.035);
   bkgWpLJets__1->GetZaxis()->SetTitleOffset(1);
   bkgWpLJets__1->GetZaxis()->SetTitleFont(42);
   bkgWpLJets__1->Draw("");
}
