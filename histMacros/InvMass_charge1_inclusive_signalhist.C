{
//========= Macro generated from object: signal/PionTriplet_MassInv {((XSecMCweight / XSec) * (192900*1e-3) * PUweight) * ((PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso < 0.100000))) && Trigger_ditau && !LeptonVeto && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (abs(PionTriplet_charge) == 1) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso < 0.100000))}
//========= by ROOT version6.19/01
   
   TH1F *signal__1 = new TH1F("signal__1","PionTriplet_MassInv {((XSecMCweight / XSec) * (192900*1e-3) * PUweight) * ((PionTriplet_CountOfItsKind == MinIf$(PionTriplet_CountOfItsKind, (abs(PionTriplet_charge) == 1) && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso < 0.100000))) && Trigger_ditau && !LeptonVeto && (abs(PionTriplet_pdgId) == 15*15*15) && (PionTriplet_trailingIsTrack) && (abs(PionTriplet_charge) == 1) && (PionTriplet_LowestDeepTauVsEl >= 3) && (PionTriplet_LowestDeepTauVsMu >= 15) && (PionTriplet_LowestDeepTauVsJet >= 1) && (PionTriplet_pion3_iso < 0.100000))}",24,0,360);
   signal__1->SetBinContent(2,31.1982);
   signal__1->SetBinContent(3,202.772);
   signal__1->SetBinContent(4,1364.44);
   signal__1->SetBinContent(5,13206.7);
   signal__1->SetBinContent(6,67522.3);
   signal__1->SetBinContent(7,15635.2);
   signal__1->SetBinContent(8,11971.5);
   signal__1->SetBinContent(9,7856.98);
   signal__1->SetBinContent(10,4773.01);
   signal__1->SetBinContent(11,4287.11);
   signal__1->SetBinContent(12,3056.36);
   signal__1->SetBinContent(13,2006.21);
   signal__1->SetBinContent(14,1487.95);
   signal__1->SetBinContent(15,1012.97);
   signal__1->SetBinContent(16,962.57);
   signal__1->SetBinContent(17,596.423);
   signal__1->SetBinContent(18,229.833);
   signal__1->SetBinContent(19,563.288);
   signal__1->SetBinContent(20,358.943);
   signal__1->SetBinContent(21,268.269);
   signal__1->SetBinContent(22,154.487);
   signal__1->SetBinContent(23,71.2476);
   signal__1->SetBinContent(24,67.837);
   signal__1->SetBinContent(25,639.713);
   signal__1->SetBinError(2,31.1982);
   signal__1->SetBinError(3,83.0363);
   signal__1->SetBinError(4,211.432);
   signal__1->SetBinError(5,664.487);
   signal__1->SetBinError(6,1530.5);
   signal__1->SetBinError(7,748.654);
   signal__1->SetBinError(8,657.741);
   signal__1->SetBinError(9,506.343);
   signal__1->SetBinError(10,406.994);
   signal__1->SetBinError(11,376.949);
   signal__1->SetBinError(12,319.037);
   signal__1->SetBinError(13,257.924);
   signal__1->SetBinError(14,220.411);
   signal__1->SetBinError(15,182.599);
   signal__1->SetBinError(16,176.481);
   signal__1->SetBinError(17,140.902);
   signal__1->SetBinError(18,87.2132);
   signal__1->SetBinError(19,137.258);
   signal__1->SetBinError(20,108.406);
   signal__1->SetBinError(21,96.6005);
   signal__1->SetBinError(22,69.172);
   signal__1->SetBinError(23,50.4374);
   signal__1->SetBinError(24,47.968);
   signal__1->SetBinError(25,147.925);
   signal__1->SetEntries(4183);
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
