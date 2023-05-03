{
//========= Macro generated from object: data/PionTriplet_MassInv {(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))&&(HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg) && (Sum$(abs(Lepton_pdgId)==15) == Length$(Lepton_pdgId))&&(abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)&&(PionTriplet_pt>40)}
//========= by ROOT version6.19/01
   
   TH1F *data__1 = new TH1F("data__1","PionTriplet_MassInv {(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))&&(HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg) && (Sum$(abs(Lepton_pdgId)==15) == Length$(Lepton_pdgId))&&(abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)&&(PionTriplet_pt>40)}",50,0,500);
   data__1->SetBinContent(1,1);
   data__1->SetBinContent(2,71);
   data__1->SetBinContent(3,476);
   data__1->SetBinContent(4,1218);
   data__1->SetBinContent(5,2174);
   data__1->SetBinContent(6,3112);
   data__1->SetBinContent(7,3811);
   data__1->SetBinContent(8,3986);
   data__1->SetBinContent(9,4005);
   data__1->SetBinContent(10,3597);
   data__1->SetBinContent(11,3112);
   data__1->SetBinContent(12,2740);
   data__1->SetBinContent(13,2411);
   data__1->SetBinContent(14,1964);
   data__1->SetBinContent(15,1765);
   data__1->SetBinContent(16,1401);
   data__1->SetBinContent(17,1235);
   data__1->SetBinContent(18,1011);
   data__1->SetBinContent(19,848);
   data__1->SetBinContent(20,771);
   data__1->SetBinContent(21,604);
   data__1->SetBinContent(22,529);
   data__1->SetBinContent(23,441);
   data__1->SetBinContent(24,349);
   data__1->SetBinContent(25,308);
   data__1->SetBinContent(26,281);
   data__1->SetBinContent(27,218);
   data__1->SetBinContent(28,201);
   data__1->SetBinContent(29,174);
   data__1->SetBinContent(30,154);
   data__1->SetBinContent(31,116);
   data__1->SetBinContent(32,87);
   data__1->SetBinContent(33,95);
   data__1->SetBinContent(34,77);
   data__1->SetBinContent(35,62);
   data__1->SetBinContent(36,67);
   data__1->SetBinContent(37,44);
   data__1->SetBinContent(38,42);
   data__1->SetBinContent(39,34);
   data__1->SetBinContent(40,43);
   data__1->SetBinContent(41,29);
   data__1->SetBinContent(42,29);
   data__1->SetBinContent(43,23);
   data__1->SetBinContent(44,24);
   data__1->SetBinContent(45,13);
   data__1->SetBinContent(46,13);
   data__1->SetBinContent(47,14);
   data__1->SetBinContent(48,16);
   data__1->SetBinContent(49,8);
   data__1->SetBinContent(50,14);
   data__1->SetBinContent(51,120);
   data__1->SetEntries(43938);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   data__1->SetLineColor(ci);
   data__1->SetMarkerStyle(8);
   data__1->SetMarkerSize(0.8);
   data__1->GetXaxis()->SetLabelFont(42);
   data__1->GetXaxis()->SetLabelSize(0.035);
   data__1->GetXaxis()->SetTitleSize(0.035);
   data__1->GetXaxis()->SetTitleOffset(1);
   data__1->GetXaxis()->SetTitleFont(42);
   data__1->GetYaxis()->SetLabelFont(42);
   data__1->GetYaxis()->SetLabelSize(0.035);
   data__1->GetYaxis()->SetTitleSize(0.035);
   data__1->GetYaxis()->SetTitleFont(42);
   data__1->GetZaxis()->SetLabelFont(42);
   data__1->GetZaxis()->SetLabelSize(0.035);
   data__1->GetZaxis()->SetTitleSize(0.035);
   data__1->GetZaxis()->SetTitleOffset(1);
   data__1->GetZaxis()->SetTitleFont(42);
   data__1->Draw("");
}
