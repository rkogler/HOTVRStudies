#include "../include/CentralInclude.h"


int main(){
  SetStyle();

  TFile *input1 = new TFile(" /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/VR_SD/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_nnpdf23_VR_SD_24_02_z01_b01.root", "READ");
  TFile *input2 = new TFile(" /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/VR_SD/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_nnpdf23_VR_SD_27_02_z001_b01.root", "READ");

  //pt array
  TString pt[4];
  pt[0]="200";
  pt[1]="400";
  pt[2]="600";
  pt[3]="800";

  //hists for gaussian width
  TH1F* width_hotvr = new TH1F("width_hotvr", "width_hotvr", 4, 200, 1000);
  TH1F* width_vr = new TH1F("width_vr", "width_vr", 4, 200, 1000);
  TH1F* width_b1z01 = new TH1F("width_b1z01", "width_b1z01", 4, 200, 1000);
  TH1F* width_b1z001 = new TH1F("width_b1z001", "width_b1z001", 4, 200, 1000);

  //only HOTVR
  for(int i=0; i<4; i++){
    TH1F* hotvr = (TH1F*)input2->Get("HOTVRStudiesHists/mass_jets_" + pt[i]);
    TH1F* vr = (TH1F*)input2->Get("HOTVRStudiesHists/mass_jets_noMJ_" + pt[i]);
  //beta=1
    TH1F* b1z01 = (TH1F*)input1->Get("HOTVRStudiesHists/mass_jets_SD_" +pt[i]);
    TH1F* b1z001 = (TH1F*)input2->Get("HOTVRStudiesHists/mass_jets_SD_" + pt[i]);
    //fit gaussians and fill hist with the width
    TF1* fit = new TF1("fit", "gaus", 160, 190);
    hotvr->Fit("fit", "R");
    double gaus_width_hotvr=fit->GetParameter(2);
    width_hotvr->SetBinContent(i+1, gaus_width_hotvr);

    vr->Fit("fit", "R");
    width_vr->SetBinContent(i+1, (fit->GetParameter(2)));
    b1z01->Fit("fit", "R");
    width_b1z01->SetBinContent(i+1, (fit->GetParameter(2)));
    b1z001->Fit("fit", "R");
    width_b1z001->SetBinContent(i+1, (fit->GetParameter(2)));
  }

    TCanvas* canvas = new TCanvas("c", "c", 600, 600);
    gPad->SetLeftMargin(0.2);
    gPad->SetBottomMargin(0.2);

    width_hotvr->SetTitle("");

    width_hotvr->SetLineColor(kBlack);
    width_hotvr->SetLineWidth(2);
    width_hotvr->Draw("");
    width_vr->SetLineColor(kRed);
    width_vr->SetLineWidth(2);
    width_vr->Draw("same");
    width_b1z01->SetLineColor(kAzure+7);
    width_b1z01->SetLineWidth(2);
    width_b1z01->Draw("same");
    width_b1z001->SetLineColor(kGreen+2);
    width_b1z001->SetLineWidth(2);
    width_b1z001->Draw("same");

    width_hotvr->GetYaxis()->SetRangeUser(0,60);

    width_hotvr->GetXaxis()->SetTitle("p_{T} [GeV]");
    width_hotvr->GetXaxis()->SetLabelSize(0.04);
    width_hotvr->GetXaxis()->SetTitleSize(0.06);
    width_hotvr->GetYaxis()->SetTitle("#sigma [GeV]");
    width_hotvr->GetYaxis()->SetLabelSize(0.04);
    width_hotvr->GetYaxis()->SetTitleSize(0.06);

    auto legend = new TLegend(0.25, 0.6, 0.85, 0.85);
    legend->SetTextSize(.04);

    legend->SetHeader("Width of Gaussian (top)");
    legend->AddEntry(width_hotvr,"HOTVR", "l");
    legend->AddEntry(width_vr,"VR", "l");
    legend->AddEntry(width_b1z01,"VR+SD, z_{cut} = 0.1, #beta = 1", "l");
    legend->AddEntry(width_b1z001,"VR+SD, z_{cut} = 0.01, #beta = 1", "l");

    legend->Draw();

    canvas->SaveAs("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/plots/VR_SD/ttbar_flat_VR_SD_gaussian_width_top.eps");


  return 0;
 }
