{
//========= Macro generated from object: signal/PionTriplet_MassInv {((XSecMCweight / XSec) * (192900*1e-3) * PUweight) * ((PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 0) && (PionTriplet_LowestDeepTauVsMu >= 0) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso < 100.000000))) && Trigger_ditau && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (abs(PionTriplet_charge) == 1) && (PionTriplet_LowestDeepTauVsEl >= 0) && (PionTriplet_LowestDeepTauVsMu >= 0) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso < 100.000000))}
//========= by ROOT version6.19/01
   
   TH1F *signal__1 = new TH1F("signal__1","PionTriplet_MassInv {((XSecMCweight / XSec) * (192900*1e-3) * PUweight) * ((PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 0) && (PionTriplet_LowestDeepTauVsMu >= 0) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso < 100.000000))) && Trigger_ditau && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (abs(PionTriplet_charge) == 1) && (PionTriplet_LowestDeepTauVsEl >= 0) && (PionTriplet_LowestDeepTauVsMu >= 0) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso < 100.000000))}",24,0,360);
   signal__1->SetBinContent(2,52.069);
   signal__1->SetBinContent(3,147.728);
   signal__1->SetBinContent(4,1760.51);
   signal__1->SetBinContent(5,13336.2);
   signal__1->SetBinContent(6,50629.1);
   signal__1->SetBinContent(7,26437);
   signal__1->SetBinContent(8,21665.3);
   signal__1->SetBinContent(9,15319.1);
   signal__1->SetBinContent(10,10082.3);
   signal__1->SetBinContent(11,7816.32);
   signal__1->SetBinContent(12,4942.42);
   signal__1->SetBinContent(13,3255.18);
   signal__1->SetBinContent(14,2340.82);
   signal__1->SetBinContent(15,1339.56);
   signal__1->SetBinContent(16,1128.15);
   signal__1->SetBinContent(17,922.375);
   signal__1->SetBinContent(18,639.809);
   signal__1->SetBinContent(19,283.028);
   signal__1->SetBinContent(20,530.015);
   signal__1->SetBinContent(21,339.952);
   signal__1->SetBinContent(22,277.575);
   signal__1->SetBinContent(23,325.973);
   signal__1->SetBinContent(24,324.519);
   signal__1->SetBinContent(25,1151.05);
   signal__1->SetBinError(2,36.8595);
   signal__1->SetBinError(3,60.6358);
   signal__1->SetBinError(4,212.623);
   signal__1->SetBinError(5,581.175);
   signal__1->SetBinError(6,1128.7);
   signal__1->SetBinError(7,816.546);
   signal__1->SetBinError(8,738.87);
   signal__1->SetBinError(9,620.924);
   signal__1->SetBinError(10,504.704);
   signal__1->SetBinError(11,444.361);
   signal__1->SetBinError(12,352.083);
   signal__1->SetBinError(13,287.365);
   signal__1->SetBinError(14,242.603);
   signal__1->SetBinError(15,184.506);
   signal__1->SetBinError(16,168.725);
   signal__1->SetBinError(17,154.399);
   signal__1->SetBinError(18,125.665);
   signal__1->SetBinError(19,85.7992);
   signal__1->SetBinError(20,116);
   signal__1->SetBinError(21,91.2004);
   signal__1->SetBinError(22,83.7453);
   signal__1->SetBinError(23,90.456);
   signal__1->SetBinError(24,90.0815);
   signal__1->SetBinError(25,170.024);
   signal__1->SetEntries(6579);
   signal__1->SetStats(0);
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
