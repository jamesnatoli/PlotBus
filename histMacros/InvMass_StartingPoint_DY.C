{
//========= Macro generated from object: procDYA/PionTriplet_MassInv {(((LHE_Njets==0?1.83962:1)*(LHE_Njets==1?0.628821:1)*(LHE_Njets==2?0.492408:1)*(LHE_Njets==3?0.233581:1)*(LHE_Njets==4?0.263824:1)*(LHE_Njets>4?1.83962:1) * (PUweight * PionTriplet_TauSFweight))) * ( (PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso >= 0) && (abs(PionTriplet_pion1_dxy) < 100.000000) && (abs(PionTriplet_pion2_dxy) < 100.000000) && (abs(PionTriplet_pion3_dxy) < 100.000000) && (abs(PionTriplet_pion1_dz) < 100.000000) && (abs(PionTriplet_pion2_dz) < 100.000000) && (abs(PionTriplet_pion3_dz) < 100.000000) && ((PionTriplet_pion3_iso < 0.1)) && ((PionTriplet_LowestDeepTauVsJet >= 31)) &&  (1)  && (PionTriplet_pt > 40))) && Trigger_ditau && !LeptonVeto && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (abs(PionTriplet_charge) == 1) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso >= 0) && (abs(PionTriplet_pion1_dxy) < 100.000000) && (abs(PionTriplet_pion2_dxy) < 100.000000) && (abs(PionTriplet_pion3_dxy) < 100.000000) && (abs(PionTriplet_pion1_dz) < 100.000000) && (abs(PionTriplet_pion2_dz) < 100.000000) && (abs(PionTriplet_pion3_dz) < 100.000000) && 1 &&  (1)  && (PionTriplet_pt > 40) && ((PionTriplet_pion3_iso < 0.1)) && ((PionTriplet_LowestDeepTauVsJet >= 31)))}
//========= by ROOT version6.19/01
   
   TH1F *procDYA__1 = new TH1F("procDYA__1","PionTriplet_MassInv {(((LHE_Njets==0?1.83962:1)*(LHE_Njets==1?0.628821:1)*(LHE_Njets==2?0.492408:1)*(LHE_Njets==3?0.233581:1)*(LHE_Njets==4?0.263824:1)*(LHE_Njets>4?1.83962:1) * (PUweight * PionTriplet_TauSFweight))) * ( (PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso >= 0) && (abs(PionTriplet_pion1_dxy) < 100.000000) && (abs(PionTriplet_pion2_dxy) < 100.000000) && (abs(PionTriplet_pion3_dxy) < 100.000000) && (abs(PionTriplet_pion1_dz) < 100.000000) && (abs(PionTriplet_pion2_dz) < 100.000000) && (abs(PionTriplet_pion3_dz) < 100.000000) && ((PionTriplet_pion3_iso < 0.1)) && ((PionTriplet_LowestDeepTauVsJet >= 31)) &&  (1)  && (PionTriplet_pt > 40))) && Trigger_ditau && !LeptonVeto && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (abs(PionTriplet_charge) == 1) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso >= 0) && (abs(PionTriplet_pion1_dxy) < 100.000000) && (abs(PionTriplet_pion2_dxy) < 100.000000) && (abs(PionTriplet_pion3_dxy) < 100.000000) && (abs(PionTriplet_pion1_dz) < 100.000000) && (abs(PionTriplet_pion2_dz) < 100.000000) && (abs(PionTriplet_pion3_dz) < 100.000000) && 1 &&  (1)  && (PionTriplet_pt > 40) && ((PionTriplet_pion3_iso < 0.1)) && ((PionTriplet_LowestDeepTauVsJet >= 31)))}",35,0,350);
   procDYA__1->SetBinContent(3,3.48934);
   procDYA__1->SetBinContent(4,2.40404);
   procDYA__1->SetBinContent(5,4.50642);
   procDYA__1->SetBinContent(6,2.93479);
   procDYA__1->SetBinContent(7,3.54381);
   procDYA__1->SetBinContent(8,3.63279);
   procDYA__1->SetBinContent(9,6.44888);
   procDYA__1->SetBinContent(10,5.39419);
   procDYA__1->SetBinContent(11,3.26563);
   procDYA__1->SetBinContent(12,5.69036);
   procDYA__1->SetBinContent(13,8.07976);
   procDYA__1->SetBinContent(14,8.28192);
   procDYA__1->SetBinContent(15,4.69642);
   procDYA__1->SetBinContent(16,2.71513);
   procDYA__1->SetBinContent(17,3.47642);
   procDYA__1->SetBinContent(18,1.41962);
   procDYA__1->SetBinContent(19,2.94829);
   procDYA__1->SetBinContent(20,1.90364);
   procDYA__1->SetBinContent(21,2.30377);
   procDYA__1->SetBinContent(24,1.18989);
   procDYA__1->SetBinContent(25,0.374673);
   procDYA__1->SetBinContent(26,1.59244);
   procDYA__1->SetBinContent(27,0.232325);
   procDYA__1->SetBinContent(28,2.8491);
   procDYA__1->SetBinContent(30,1.28661);
   procDYA__1->SetBinContent(31,0.135525);
   procDYA__1->SetBinContent(33,0.191704);
   procDYA__1->SetBinContent(36,2.80826);
   procDYA__1->SetBinError(3,2.35046);
   procDYA__1->SetBinError(4,1.50863);
   procDYA__1->SetBinError(5,2.43138);
   procDYA__1->SetBinError(6,0.810137);
   procDYA__1->SetBinError(7,1.36928);
   procDYA__1->SetBinError(8,1.017);
   procDYA__1->SetBinError(9,2.40721);
   procDYA__1->SetBinError(10,1.10556);
   procDYA__1->SetBinError(11,0.835694);
   procDYA__1->SetBinError(12,1.40899);
   procDYA__1->SetBinError(13,1.99714);
   procDYA__1->SetBinError(14,2.82631);
   procDYA__1->SetBinError(15,1.82327);
   procDYA__1->SetBinError(16,1.51676);
   procDYA__1->SetBinError(17,1.14691);
   procDYA__1->SetBinError(18,0.588225);
   procDYA__1->SetBinError(19,1.94014);
   procDYA__1->SetBinError(20,0.837726);
   procDYA__1->SetBinError(21,1.41569);
   procDYA__1->SetBinError(24,0.575127);
   procDYA__1->SetBinError(25,0.301576);
   procDYA__1->SetBinError(26,0.785924);
   procDYA__1->SetBinError(27,0.232325);
   procDYA__1->SetBinError(28,2.01461);
   procDYA__1->SetBinError(30,0.606868);
   procDYA__1->SetBinError(31,0.135525);
   procDYA__1->SetBinError(33,0.191704);
   procDYA__1->SetBinError(36,0.817261);
   procDYA__1->SetEntries(280);
   procDYA__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#3399cc");
   procDYA__1->SetFillColor(ci);
   procDYA__1->GetXaxis()->SetLabelFont(42);
   procDYA__1->GetXaxis()->SetLabelSize(0.035);
   procDYA__1->GetXaxis()->SetTitleSize(0.035);
   procDYA__1->GetXaxis()->SetTitleOffset(1);
   procDYA__1->GetXaxis()->SetTitleFont(42);
   procDYA__1->GetYaxis()->SetLabelFont(42);
   procDYA__1->GetYaxis()->SetLabelSize(0.035);
   procDYA__1->GetYaxis()->SetTitleSize(0.035);
   procDYA__1->GetYaxis()->SetTitleFont(42);
   procDYA__1->GetZaxis()->SetLabelFont(42);
   procDYA__1->GetZaxis()->SetLabelSize(0.035);
   procDYA__1->GetZaxis()->SetTitleSize(0.035);
   procDYA__1->GetZaxis()->SetTitleOffset(1);
   procDYA__1->GetZaxis()->SetTitleFont(42);
   procDYA__1->Draw("");
}
