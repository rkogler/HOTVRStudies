#include "TSystem.h"
#include <vector>
#include <iostream>

#include "../include/CentralInclude.h"

int main(int argc, char* argv[]){
  SetStyle();

  std::vector<TFile*> new_files_AK4;
  TFile *new_file_AK4_1 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/comparison_tobias_10_06_AK4_AK10/AK4_Performance_PtBin_2.root");
  new_files_AK4.push_back(new_file_AK4_1);
  TFile *new_file_AK4_2 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/comparison_tobias_10_06_AK4_AK10/AK4_Performance_PtBin_3.root");
  new_files_AK4.push_back(new_file_AK4_2);
  TFile *new_file_AK4_3 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/comparison_tobias_10_06_AK4_AK10/AK4_Performance_PtBin_4.root");
  new_files_AK4.push_back(new_file_AK4_3);
  TFile *new_file_AK4_4 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/comparison_tobias_10_06_AK4_AK10/AK4_Performance_PtBin_5.root");
  new_files_AK4.push_back(new_file_AK4_4);

  std::vector<TFile*> new_files_AK10;
  TFile *new_file_AK10_1 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/comparison_tobias_10_06_AK4_AK10/AK10_Performance_PtBin_2.root");
  new_files_AK10.push_back(new_file_AK10_1);
  TFile *new_file_AK10_2 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/comparison_tobias_10_06_AK4_AK10/AK10_Performance_PtBin_3.root");
  new_files_AK10.push_back(new_file_AK10_2);
  TFile *new_file_AK10_3 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/comparison_tobias_10_06_AK4_AK10/AK10_Performance_PtBin_4.root");
  new_files_AK10.push_back(new_file_AK10_3);
  TFile *new_file_AK10_4 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/comparison_tobias_10_06_AK4_AK10/AK10_Performance_PtBin_5.root");
  new_files_AK10.push_back(new_file_AK10_4);

  std::vector<TFile*> new_files_max_distance;
  TFile *new_file_max_distance_1 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/comparison_tobias_10_06_AK4_AK10/max_distance_Performance_PtBin_2.root");
  new_files_max_distance.push_back(new_file_max_distance_1);
  TFile *new_file_max_distance_2 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/comparison_tobias_10_06_AK4_AK10/max_distance_Performance_PtBin_3.root");
  new_files_max_distance.push_back(new_file_max_distance_2);
  TFile *new_file_max_distance_3 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/comparison_tobias_10_06_AK4_AK10/max_distance_Performance_PtBin_4.root");
  new_files_max_distance.push_back(new_file_max_distance_3);
  TFile *new_file_max_distance_4 = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/comparison_tobias_10_06_AK4_AK10/max_distance_Performance_PtBin_5.root");
  new_files_max_distance.push_back(new_file_max_distance_4);

  std::vector<TFile*> old_files;
  TFile *old_file_1 = new TFile("/nfs/dust/cms/user/albrecha/ROC_Tobias/ROC_gen200-400.root");
  old_files.push_back(old_file_1);
  TFile *old_file_2 = new TFile("/nfs/dust/cms/user/albrecha/ROC_Tobias/ROC_gen400-600.root");
  old_files.push_back(old_file_2);
  TFile *old_file_3 = new TFile("/nfs/dust/cms/user/albrecha/ROC_Tobias/ROC_gen600-1000.root");
  old_files.push_back(old_file_3);
  TFile *old_file_4 = new TFile("/nfs/dust/cms/user/albrecha/ROC_Tobias/ROC_gen1000-2000.root");
  old_files.push_back(old_file_4);

  Int_t n_ptbins = 4;
  Double_t pt_xbins[6] = {200, 400, 600, 1000, 2000};
  int n_points = 100;

  for (size_t bin = 0; bin < 4; bin++) { // loop over pt bins
  TString pt_bin = to_string(bin+1);
  TFile *newfile_AK4 = new_files_AK4[bin];
  TFile *newfile_AK10 = new_files_AK10[bin];
  TFile *newfile_max_distance = new_files_max_distance[bin];
  TFile *oldfile = old_files[bin];

  TCanvas *canvas = new TCanvas("canvas", "canvas", 600, 600);
  TGraphErrors * new_graph_AK4 = (TGraphErrors*) newfile_AK4->Get("Graph");
  TGraphErrors * new_graph_AK10 = (TGraphErrors*) newfile_AK10->Get("Graph");
  TGraphErrors * new_graph_max_distance = (TGraphErrors*) newfile_max_distance->Get("Graph");
  TGraphErrors * old_graph = (TGraphErrors*) oldfile->Get("Graph");

  new_graph_AK4->SetLineWidth(2);
  new_graph_AK4->SetLineColor(kRed);
  new_graph_AK4->SetTitle();
  new_graph_AK4->GetXaxis()->SetTitle("#varepsilon_{S}");
  new_graph_AK4->GetXaxis()->SetLabelSize(0.04);
  new_graph_AK4->GetXaxis()->SetTitleSize(0.06);

  new_graph_AK4->GetYaxis()->SetTitle("#varepsilon_{B}");
  new_graph_AK4->GetYaxis()->SetLabelSize(0.04);
  new_graph_AK4->GetYaxis()->SetTitleSize(0.06);
  new_graph_AK4->SetMaximum(0.1);
  new_graph_AK4->SetMinimum(1e-4);
  new_graph_AK4->GetXaxis()->SetLimits(0,0.6);
  new_graph_AK4->Draw();

  new_graph_AK10->SetLineWidth(2);
  new_graph_AK10->SetLineColor(kAzure+7);
  new_graph_AK10->SetLineStyle(9);
  new_graph_AK10->Draw("same");

  new_graph_max_distance->SetLineWidth(2);
  new_graph_max_distance->SetLineColor(kGreen+2);
  new_graph_max_distance->SetLineStyle(kDashed);
  new_graph_max_distance->Draw("same");

  old_graph->SetLineWidth(2);
  old_graph->SetLineColor(kBlack);
  old_graph->SetLineStyle(kDotted);
  old_graph->Draw("same");

  gPad->SetLeftMargin(0.2);
  gPad->SetBottomMargin(0.2);

  gPad->SetTickx();
  gPad->SetTicky();

// AUC values
  // string AUC_new = "AUC " + to_string(new_graph->Integral());
  // string AUC_old = "AUC " + to_string(old_graph->Integral());

  std::string interval;
  interval = to_string((int)pt_xbins[bin]) + " < p_{T} [GeV] < " + to_string((int)pt_xbins[bin+1]);

  TLegend *leg = new TLegend(0.44,0.25,0.7,0.45);
  leg->SetTextSize(.03);
  leg->SetHeader(interval.c_str());
  leg->AddEntry(new_graph_AK4, "this study AK4, #rho/p_{T}", "l");
  leg->AddEntry(new_graph_AK10, "this study AK10, #rho/p_{T}", "l");
  leg->AddEntry(new_graph_max_distance, "this study AK4, max distance", "l");
  leg->AddEntry(old_graph, "HOTVR paper", "l");
  leg->Draw();

  canvas->SetLogy();

  canvas->SaveAs("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/ROC_curves/comparison_tobias_10_06_AK4_AK10/comparison_10_06_ptbin" + pt_bin +".eps");
  }
  return 0;
}
