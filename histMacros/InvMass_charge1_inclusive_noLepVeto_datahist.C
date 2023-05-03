{
//========= Macro generated from object: data/PionTriplet_MassInv {(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 0) && (PionTriplet_LowestDeepTauVsMu >= 0) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso < 100.000000))) && Trigger_ditau && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (abs(PionTriplet_charge) == 1) && (PionTriplet_LowestDeepTauVsEl >= 0) && (PionTriplet_LowestDeepTauVsMu >= 0) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso < 100.000000)}
//========= by ROOT version6.19/01
   
   TH1F *data__2 = new TH1F("data__2","PionTriplet_MassInv {(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 0) && (PionTriplet_LowestDeepTauVsMu >= 0) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso < 100.000000))) && Trigger_ditau && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (abs(PionTriplet_charge) == 1) && (PionTriplet_LowestDeepTauVsEl >= 0) && (PionTriplet_LowestDeepTauVsMu >= 0) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso < 100.000000)}",24,0,360);
   data__2->SetBinContent(1,184);
   data__2->SetBinContent(2,3868);
   data__2->SetBinContent(3,11276);
   data__2->SetBinContent(4,17334);
   data__2->SetBinContent(5,19729);
   data__2->SetBinContent(6,18828);
   data__2->SetBinContent(7,16014);
   data__2->SetBinContent(8,12849);
   data__2->SetBinContent(9,9506);
   data__2->SetBinContent(10,7271);
   data__2->SetBinContent(11,5173);
   data__2->SetBinContent(12,3845);
   data__2->SetBinContent(13,2901);
   data__2->SetBinContent(14,2045);
   data__2->SetBinContent(15,1563);
   data__2->SetBinContent(16,1145);
   data__2->SetBinContent(17,873);
   data__2->SetBinContent(18,639);
   data__2->SetBinContent(19,465);
   data__2->SetBinContent(20,373);
   data__2->SetBinContent(21,260);
   data__2->SetBinContent(22,226);
   data__2->SetBinContent(23,168);
   data__2->SetBinContent(24,121);
   data__2->SetBinContent(25,573);
   data__2->SetEntries(137229);
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
