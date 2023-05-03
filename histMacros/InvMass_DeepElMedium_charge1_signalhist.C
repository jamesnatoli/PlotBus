{
//========= Macro generated from object: signal/PionTriplet_MassInv {((XSecMCweight / XSec) * (192900*1e-3) * PUweight)*(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))&&(HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg) && (Sum$(abs(Lepton_pdgId)==15) == Length$(Lepton_pdgId))&&(abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)&&(PionTriplet_pt>40)}
//========= by ROOT version6.19/01
   
   TH1F *signal__1 = new TH1F("signal__1","PionTriplet_MassInv {((XSecMCweight / XSec) * (192900*1e-3) * PUweight)*(PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)))&&(HLT_DoubleMediumChargedIsoPFTauHPS35_Trk1_eta2p1_Reg) && (Sum$(abs(Lepton_pdgId)==15) == Length$(Lepton_pdgId))&&(abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15)&&(PionTriplet_pt>40)}",50,0,500);
   signal__1->SetBinContent(2,1);
   signal__1->SetBinContent(3,1);
   signal__1->SetBinContent(4,3);
   signal__1->SetBinContent(5,12);
   signal__1->SetBinContent(6,60);
   signal__1->SetBinContent(7,211);
   signal__1->SetBinContent(8,1059);
   signal__1->SetBinContent(9,1079);
   signal__1->SetBinContent(10,315);
   signal__1->SetBinContent(11,221);
   signal__1->SetBinContent(12,138);
   signal__1->SetBinContent(13,119);
   signal__1->SetBinContent(14,77);
   signal__1->SetBinContent(15,67);
   signal__1->SetBinContent(16,69);
   signal__1->SetBinContent(17,45);
   signal__1->SetBinContent(18,44);
   signal__1->SetBinContent(19,23);
   signal__1->SetBinContent(20,27);
   signal__1->SetBinContent(21,30);
   signal__1->SetBinContent(22,18);
   signal__1->SetBinContent(23,19);
   signal__1->SetBinContent(24,12);
   signal__1->SetBinContent(25,8);
   signal__1->SetBinContent(26,8);
   signal__1->SetBinContent(27,5);
   signal__1->SetBinContent(28,4);
   signal__1->SetBinContent(29,3);
   signal__1->SetBinContent(30,10);
   signal__1->SetBinContent(31,6);
   signal__1->SetBinContent(32,4);
   signal__1->SetBinContent(33,3);
   signal__1->SetBinContent(34,7);
   signal__1->SetBinContent(35,3);
   signal__1->SetBinContent(36,2);
   signal__1->SetBinContent(37,1);
   signal__1->SetBinContent(38,3);
   signal__1->SetBinContent(39,3);
   signal__1->SetBinContent(40,3);
   signal__1->SetBinContent(42,3);
   signal__1->SetBinContent(43,2);
   signal__1->SetBinContent(50,1);
   signal__1->SetBinContent(51,2);
   signal__1->SetEntries(3731);
   signal__1->SetFillStyle(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   signal__1->SetLineColor(ci);
   signal__1->SetLineWidth(2);
   signal__1->SetMarkerStyle(0);
   signal__1->GetXaxis()->SetLabelFont(42);
   signal__1->GetXaxis()->SetLabelSize(0.035);
   signal__1->GetXaxis()->SetTitleSize(0.035);
   signal__1->GetXaxis()->SetTitleOffset(1);
   signal__1->GetXaxis()->SetTitleFont(42);
   signal__1->GetYaxis()->SetLabelFont(42);
   signal__1->GetYaxis()->SetLabelSize(0.035);
   signal__1->GetYaxis()->SetTitleSize(0.035);
   signal__1->GetYaxis()->SetTitleFont(42);
   signal__1->GetZaxis()->SetLabelFont(42);
   signal__1->GetZaxis()->SetLabelSize(0.035);
   signal__1->GetZaxis()->SetTitleSize(0.035);
   signal__1->GetZaxis()->SetTitleOffset(1);
   signal__1->GetZaxis()->SetTitleFont(42);
   signal__1->Draw("");
}
