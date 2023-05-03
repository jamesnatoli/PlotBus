{
//========= Macro generated from object: data/PionTriplet_MassInv {(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 3) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))&&(HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg) && (Sum$(abs(Lepton_pdgId)==15) == Length$(Lepton_pdgId))&&(abs(PionTriplet_charge) == 3) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)&&(PionTriplet_pt>40)}
//========= by ROOT version6.19/01
   
   TH1F *data__3 = new TH1F("data__3","PionTriplet_MassInv {(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 3) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))&&(HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg) && (Sum$(abs(Lepton_pdgId)==15) == Length$(Lepton_pdgId))&&(abs(PionTriplet_charge) == 3) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)&&(PionTriplet_pt>40)}",50,0,500);
   data__3->SetBinContent(2,9);
   data__3->SetBinContent(3,133);
   data__3->SetBinContent(4,292);
   data__3->SetBinContent(5,502);
   data__3->SetBinContent(6,700);
   data__3->SetBinContent(7,815);
   data__3->SetBinContent(8,867);
   data__3->SetBinContent(9,822);
   data__3->SetBinContent(10,767);
   data__3->SetBinContent(11,684);
   data__3->SetBinContent(12,598);
   data__3->SetBinContent(13,554);
   data__3->SetBinContent(14,459);
   data__3->SetBinContent(15,382);
   data__3->SetBinContent(16,310);
   data__3->SetBinContent(17,271);
   data__3->SetBinContent(18,234);
   data__3->SetBinContent(19,210);
   data__3->SetBinContent(20,159);
   data__3->SetBinContent(21,160);
   data__3->SetBinContent(22,132);
   data__3->SetBinContent(23,116);
   data__3->SetBinContent(24,81);
   data__3->SetBinContent(25,89);
   data__3->SetBinContent(26,75);
   data__3->SetBinContent(27,67);
   data__3->SetBinContent(28,50);
   data__3->SetBinContent(29,53);
   data__3->SetBinContent(30,38);
   data__3->SetBinContent(31,25);
   data__3->SetBinContent(32,23);
   data__3->SetBinContent(33,26);
   data__3->SetBinContent(34,21);
   data__3->SetBinContent(35,23);
   data__3->SetBinContent(36,14);
   data__3->SetBinContent(37,8);
   data__3->SetBinContent(38,16);
   data__3->SetBinContent(39,7);
   data__3->SetBinContent(40,6);
   data__3->SetBinContent(41,6);
   data__3->SetBinContent(42,6);
   data__3->SetBinContent(43,2);
   data__3->SetBinContent(44,4);
   data__3->SetBinContent(45,6);
   data__3->SetBinContent(46,4);
   data__3->SetBinContent(47,4);
   data__3->SetBinContent(48,4);
   data__3->SetBinContent(49,5);
   data__3->SetBinContent(50,3);
   data__3->SetBinContent(51,23);
   data__3->SetEntries(9865);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   data__3->SetLineColor(ci);
   data__3->SetMarkerStyle(8);
   data__3->SetMarkerSize(0.8);
   data__3->GetXaxis()->SetLabelFont(42);
   data__3->GetXaxis()->SetLabelSize(0.035);
   data__3->GetXaxis()->SetTitleSize(0.035);
   data__3->GetXaxis()->SetTitleOffset(1);
   data__3->GetXaxis()->SetTitleFont(42);
   data__3->GetYaxis()->SetLabelFont(42);
   data__3->GetYaxis()->SetLabelSize(0.035);
   data__3->GetYaxis()->SetTitleSize(0.035);
   data__3->GetYaxis()->SetTitleFont(42);
   data__3->GetZaxis()->SetLabelFont(42);
   data__3->GetZaxis()->SetLabelSize(0.035);
   data__3->GetZaxis()->SetTitleSize(0.035);
   data__3->GetZaxis()->SetTitleOffset(1);
   data__3->GetZaxis()->SetTitleFont(42);
   data__3->Draw("");
}
