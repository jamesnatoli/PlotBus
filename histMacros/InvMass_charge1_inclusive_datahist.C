{
//========= Macro generated from object: data/PionTriplet_MassInv {(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso < 0.100000))) && Trigger_ditau && !LeptonVeto && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (abs(PionTriplet_charge) == 1) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso < 0.100000)}
//========= by ROOT version6.19/01
   
   TH1F *data__2 = new TH1F("data__2","PionTriplet_MassInv {(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso < 0.100000))) && Trigger_ditau && !LeptonVeto && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (abs(PionTriplet_charge) == 1) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso < 0.100000)}",24,0,360);
   data__2->SetBinContent(1,24);
   data__2->SetBinContent(2,628);
   data__2->SetBinContent(3,1571);
   data__2->SetBinContent(4,2389);
   data__2->SetBinContent(5,2525);
   data__2->SetBinContent(6,2452);
   data__2->SetBinContent(7,2130);
   data__2->SetBinContent(8,1792);
   data__2->SetBinContent(9,1348);
   data__2->SetBinContent(10,967);
   data__2->SetBinContent(11,761);
   data__2->SetBinContent(12,570);
   data__2->SetBinContent(13,394);
   data__2->SetBinContent(14,309);
   data__2->SetBinContent(15,232);
   data__2->SetBinContent(16,209);
   data__2->SetBinContent(17,137);
   data__2->SetBinContent(18,118);
   data__2->SetBinContent(19,81);
   data__2->SetBinContent(20,59);
   data__2->SetBinContent(21,42);
   data__2->SetBinContent(22,35);
   data__2->SetBinContent(23,31);
   data__2->SetBinContent(24,24);
   data__2->SetBinContent(25,114);
   data__2->SetEntries(18942);
   data__2->SetStats(0);

   ci = TColor::GetColor("#000099");
   data__2->SetLineColor(ci);
   data__2->SetMarkerStyle(8);
   data__2->SetMarkerSize(0.8);
   data__2->GetXaxis()->SetLabelFont(42);
   data__2->GetXaxis()->SetLabelSize(0.035);
   data__2->GetXaxis()->SetTitleSize(0.035);
   data__2->GetXaxis()->SetTitleOffset(1);
   data__2->GetXaxis()->SetTitleFont(42);
   data__2->GetYaxis()->SetLabelFont(42);
   data__2->GetYaxis()->SetLabelSize(0.035);
   data__2->GetYaxis()->SetTitleSize(0.035);
   data__2->GetYaxis()->SetTitleFont(42);
   data__2->GetZaxis()->SetLabelFont(42);
   data__2->GetZaxis()->SetLabelSize(0.035);
   data__2->GetZaxis()->SetTitleSize(0.035);
   data__2->GetZaxis()->SetTitleOffset(1);
   data__2->GetZaxis()->SetTitleFont(42);
   data__2->Draw("");
}
