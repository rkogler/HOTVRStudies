#include "TSystem.h"
#include <vector>
#include <iostream>

#include "../include/CentralInclude.h"

int main(int argc, char* argv[]){
  SetStyle();

  std::vector<TFile*> files_HOTVR_MJ;
  TFile *files_HOTVR_MJ_1 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/comparison_tobias_10_06_AK4_AK10/AK10_Performance_PtBin_2.root");
  files_HOTVR_MJ.push_back(files_HOTVR_MJ_1);
  TFile *files_HOTVR_MJ_2 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/comparison_tobias_10_06_AK4_AK10/AK10_Performance_PtBin_3.root");
  files_HOTVR_MJ.push_back(files_HOTVR_MJ_2);
  TFile *files_HOTVR_MJ_3 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/comparison_tobias_10_06_AK4_AK10/AK10_Performance_PtBin_4.root");
  files_HOTVR_MJ.push_back(files_HOTVR_MJ_3);
  TFile *files_HOTVR_MJ_4 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/comparison_tobias_10_06_AK4_AK10/AK10_Performance_PtBin_5.root");
  files_HOTVR_MJ.push_back(files_HOTVR_MJ_4);

  std::vector<TFile*> files_HOTVR_SD1;
  TFile *files_HOTVR_SD1_1 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_Performance_PtBin_2.root");
  files_HOTVR_SD1.push_back(files_HOTVR_SD1_1);
  TFile *files_HOTVR_SD1_2 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_Performance_PtBin_3.root");
  files_HOTVR_SD1.push_back(files_HOTVR_SD1_2);
  TFile *files_HOTVR_SD1_3 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_Performance_PtBin_4.root");
  files_HOTVR_SD1.push_back(files_HOTVR_SD1_3);
  TFile *files_HOTVR_SD1_4 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_Performance_PtBin_5.root");
  files_HOTVR_SD1.push_back(files_HOTVR_SD1_4);

  std::vector<TFile*> files_HOTVR_SD_ptt0_mu20;
  TFile *files_HOTVR_SD_ptt0_mu20_1 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt0_mu20_Performance_PtBin_2.root");
  files_HOTVR_SD_ptt0_mu20.push_back(files_HOTVR_SD_ptt0_mu20_1);
  TFile *files_HOTVR_SD_ptt0_mu20_2 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt0_mu20_Performance_PtBin_3.root");
  files_HOTVR_SD_ptt0_mu20.push_back(files_HOTVR_SD_ptt0_mu20_2);
  TFile *files_HOTVR_SD_ptt0_mu20_3 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt0_mu20_Performance_PtBin_4.root");
  files_HOTVR_SD_ptt0_mu20.push_back(files_HOTVR_SD_ptt0_mu20_3);
  TFile *files_HOTVR_SD_ptt0_mu20_4 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt0_mu20_Performance_PtBin_5.root");
  files_HOTVR_SD_ptt0_mu20.push_back(files_HOTVR_SD_ptt0_mu20_4);
  //
  std::vector<TFile*> files_HOTVR_SD_ptt0_mu40;
  TFile *files_HOTVR_SD_ptt0_mu40_1 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt0_mu40_Performance_PtBin_2.root");
  files_HOTVR_SD_ptt0_mu40.push_back(files_HOTVR_SD_ptt0_mu40_1);
  TFile *files_HOTVR_SD_ptt0_mu40_2 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt0_mu40_Performance_PtBin_3.root");
  files_HOTVR_SD_ptt0_mu40.push_back(files_HOTVR_SD_ptt0_mu40_2);
  TFile *files_HOTVR_SD_ptt0_mu40_3 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt0_mu40_Performance_PtBin_4.root");
  files_HOTVR_SD_ptt0_mu40.push_back(files_HOTVR_SD_ptt0_mu40_3);
  TFile *files_HOTVR_SD_ptt0_mu40_4 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt0_mu40_Performance_PtBin_5.root");
  files_HOTVR_SD_ptt0_mu40.push_back(files_HOTVR_SD_ptt0_mu40_4);

  std::vector<TFile*> files_HOTVR_SD_ptt10_mu30;
  TFile *files_HOTVR_SD_ptt10_mu30_1 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt10_mu30_Performance_PtBin_2.root");
  files_HOTVR_SD_ptt10_mu30.push_back(files_HOTVR_SD_ptt10_mu30_1);
  TFile *files_HOTVR_SD_ptt10_mu30_2 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt10_mu30_Performance_PtBin_3.root");
  files_HOTVR_SD_ptt10_mu30.push_back(files_HOTVR_SD_ptt10_mu30_2);
  TFile *files_HOTVR_SD_ptt10_mu30_3 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt10_mu30_Performance_PtBin_4.root");
  files_HOTVR_SD_ptt10_mu30.push_back(files_HOTVR_SD_ptt10_mu30_3);
  TFile *files_HOTVR_SD_ptt10_mu30_4 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt10_mu30_Performance_PtBin_5.root");
  files_HOTVR_SD_ptt10_mu30.push_back(files_HOTVR_SD_ptt10_mu30_4);

  std::vector<TFile*> files_HOTVR_SD_ptt20_mu30;
  TFile *files_HOTVR_SD_ptt20_mu30_1 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt20_mu30_Performance_PtBin_2.root");
  files_HOTVR_SD_ptt20_mu30.push_back(files_HOTVR_SD_ptt20_mu30_1);
  TFile *files_HOTVR_SD_ptt20_mu30_2 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt20_mu30_Performance_PtBin_3.root");
  files_HOTVR_SD_ptt20_mu30.push_back(files_HOTVR_SD_ptt20_mu30_2);
  TFile *files_HOTVR_SD_ptt20_mu30_3 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt20_mu30_Performance_PtBin_4.root");
  files_HOTVR_SD_ptt20_mu30.push_back(files_HOTVR_SD_ptt20_mu30_3);
  TFile *files_HOTVR_SD_ptt20_mu30_4 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt20_mu30_Performance_PtBin_5.root");
  files_HOTVR_SD_ptt20_mu30.push_back(files_HOTVR_SD_ptt20_mu30_4);

  std::vector<TFile*> files_HOTVR_SD_ptt30_mu30;
  TFile *files_HOTVR_SD_ptt30_mu30_1 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt30_mu30_Performance_PtBin_2.root");
  files_HOTVR_SD_ptt30_mu30.push_back(files_HOTVR_SD_ptt30_mu30_1);
  TFile *files_HOTVR_SD_ptt30_mu30_2 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt30_mu30_Performance_PtBin_3.root");
  files_HOTVR_SD_ptt30_mu30.push_back(files_HOTVR_SD_ptt30_mu30_2);
  TFile *files_HOTVR_SD_ptt30_mu30_3 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt30_mu30_Performance_PtBin_4.root");
  files_HOTVR_SD_ptt30_mu30.push_back(files_HOTVR_SD_ptt30_mu30_3);
  TFile *files_HOTVR_SD_ptt30_mu30_4 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/root_SD/SD_ptt30_mu30_Performance_PtBin_5.root");
  files_HOTVR_SD_ptt30_mu30.push_back(files_HOTVR_SD_ptt30_mu30_4);

  Int_t n_ptbins = 4;
  Double_t pt_xbins[6] = {200, 400, 600, 1000, 2000};
  int n_points = 100;

  for (size_t bin = 0; bin < 4; bin++) { // loop over pt bins
  TString pt_bin = to_string(bin+1);
  std::string interval;
  interval = to_string((int)pt_xbins[bin]) + " < p_{T} [GeV] < " + to_string((int)pt_xbins[bin+1]);

  TFile *file_HOTVR_MJ = files_HOTVR_MJ[bin];
  TFile *file_HOTVR_SD1 = files_HOTVR_SD1[bin];
  TFile *file_HOTVR_SD_ptt0_mu20 = files_HOTVR_SD_ptt0_mu20[bin];
  TFile *file_HOTVR_SD_ptt0_mu40 = files_HOTVR_SD_ptt0_mu40[bin];
  // TFile *file_HOTVR_SD_ptt10_mu30 = files_HOTVR_SD_ptt10_mu30[bin];
  // TFile *file_HOTVR_SD_ptt20_mu30 = files_HOTVR_SD_ptt20_mu30[bin];
  // TFile *file_HOTVR_SD_ptt30_mu30 = files_HOTVR_SD_ptt30_mu30[bin];

  TCanvas *canvas = new TCanvas("canvas", "canvas", 600, 600);
  TGraphErrors *ROC_HOTVR_MJ = (TGraphErrors*) file_HOTVR_MJ->Get("Graph");
  TGraphErrors *ROC_HOTVR_SD1 = (TGraphErrors*) file_HOTVR_SD1->Get("Graph");
  TGraphErrors *ROC_HOTVR_SD_ptt0_mu20 = (TGraphErrors*) file_HOTVR_SD_ptt0_mu20->Get("Graph");
  TGraphErrors *ROC_HOTVR_SD_ptt0_mu40 = (TGraphErrors*) file_HOTVR_SD_ptt0_mu40->Get("Graph");
  // TGraphErrors *ROC_HOTVR_SD_ptt10_mu30 = (TGraphErrors*) file_HOTVR_SD_ptt10_mu30->Get("Graph");
  // TGraphErrors *ROC_HOTVR_SD_ptt20_mu30 = (TGraphErrors*) file_HOTVR_SD_ptt20_mu30->Get("Graph");
  // TGraphErrors *ROC_HOTVR_SD_ptt30_mu30 = (TGraphErrors*) file_HOTVR_SD_ptt30_mu30->Get("Graph");

  //Int_t e_bins[9] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
  Double_t e_sMJ[100], e_bMJ[100];
  Double_t e_s[100], e_b[100];

  std::cout << "-----------------------------------------------" << '\n';
  std::cout << interval.c_str() << '\n';
  for (Int_t i = 0; i < 100; i++) {
    ROC_HOTVR_MJ->GetPoint(i, e_sMJ[i], e_bMJ[i]);
    std::cout << " MJ: epsilon_s="<< e_sMJ[i] << ", epsilon_b="<< e_bMJ[i] << '\n';

    ROC_HOTVR_SD_ptt0_mu40->GetPoint(i, e_s[i], e_b[i]);
    std::cout << " SD mu 40: epsilon_s="<< e_s[i] << ", epsilon_b="<< e_b[i] << '\n';
  }

  ROC_HOTVR_MJ->SetLineWidth(2);
  ROC_HOTVR_MJ->SetLineColor(kBlack);
  ROC_HOTVR_MJ->SetTitle();
  ROC_HOTVR_MJ->GetXaxis()->SetTitle("#varepsilon_{S}");
  ROC_HOTVR_MJ->GetXaxis()->SetLabelSize(0.04);
  ROC_HOTVR_MJ->GetXaxis()->SetTitleSize(0.06);

  ROC_HOTVR_MJ->GetYaxis()->SetTitle("#varepsilon_{B}");
  ROC_HOTVR_MJ->GetYaxis()->SetLabelSize(0.04);
  ROC_HOTVR_MJ->GetYaxis()->SetTitleSize(0.06);
  ROC_HOTVR_MJ->SetMaximum(0.1);
  ROC_HOTVR_MJ->SetMinimum(1e-4);
  ROC_HOTVR_MJ->GetXaxis()->SetLimits(0,0.6);
  ROC_HOTVR_MJ->Draw();

  ROC_HOTVR_SD1->SetLineWidth(2);
  ROC_HOTVR_SD1->SetLineColor(kAzure+7);
  ROC_HOTVR_SD1->SetLineStyle(9);
  ROC_HOTVR_SD1->Draw("same");

  ROC_HOTVR_SD_ptt0_mu20->SetLineWidth(2);
  ROC_HOTVR_SD_ptt0_mu20->SetLineColor(kGreen+2);
  ROC_HOTVR_SD_ptt0_mu20->SetLineStyle(7);
  ROC_HOTVR_SD_ptt0_mu20->Draw("same");

  ROC_HOTVR_SD_ptt0_mu40->SetLineWidth(2);
  ROC_HOTVR_SD_ptt0_mu40->SetLineColor(kRed);
  ROC_HOTVR_SD_ptt0_mu40->SetLineStyle(8);
  ROC_HOTVR_SD_ptt0_mu40->Draw("same");

  // ROC_HOTVR_SD_ptt10_mu30->SetLineWidth(2);
  // ROC_HOTVR_SD_ptt10_mu30->SetLineColor(kBlue);
  // ROC_HOTVR_SD_ptt10_mu30->SetLineStyle(6);
  // ROC_HOTVR_SD_ptt10_mu30->Draw("same");
  //
  // ROC_HOTVR_SD_ptt20_mu30->SetLineWidth(2);
  // ROC_HOTVR_SD_ptt20_mu30->SetLineColor(kBlack);
  // ROC_HOTVR_SD_ptt20_mu30->SetLineStyle(5);
  // ROC_HOTVR_SD_ptt20_mu30->Draw("same");
  //
  // ROC_HOTVR_SD_ptt30_mu30->SetLineWidth(2);
  // ROC_HOTVR_SD_ptt30_mu30->SetLineColor(kOrange);
  // ROC_HOTVR_SD_ptt30_mu30->SetLineStyle(5);
  // ROC_HOTVR_SD_ptt30_mu30->Draw("same");

  gPad->SetLeftMargin(0.2);
  gPad->SetBottomMargin(0.2);

  gPad->SetTickx();
  gPad->SetTicky();

  TLegend *leg = new TLegend(0.4,0.25,0.85,0.45);
  leg->SetTextSize(.03);
  leg->SetHeader(interval.c_str());
  leg->AddEntry(ROC_HOTVR_MJ, "HOTVR MJ", "l");
  leg->AddEntry(ROC_HOTVR_SD_ptt0_mu20, "HOTVR SD, #mu=20 GeV", "l");
  leg->AddEntry(ROC_HOTVR_SD1, "HOTVR SD, #mu=30 GeV", "l");
  leg->AddEntry(ROC_HOTVR_SD_ptt0_mu40, "HOTVR SD, #mu=40 GeV", "l");
  // leg->AddEntry(ROC_HOTVR_SD_ptt10_mu30, "HOTVR SD, #mu=30 , p_{T,thr.}=10 ", "l");
  // leg->AddEntry(ROC_HOTVR_SD_ptt20_mu30, "HOTVR SD, #mu=30 , p_{T,thr.}=20 ", "l");
  // leg->AddEntry(ROC_HOTVR_SD_ptt30_mu30, "HOTVR SD, #mu=30 , p_{T,thr.}=30 ", "l");

  leg->Draw();

  canvas->SetLogy();

  canvas->SaveAs("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/comparison_MJ_SD/comparison_12_21_ptbin" + pt_bin +".eps");
  }
  return 0;
}
