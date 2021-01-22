#include "TSystem.h"
#include <vector>

#include <iostream>
#include "../include/CentralInclude.h"

int main(){
  SetStyle();

// VR SD
  TString root_in_ttbar2 =" /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/VR_SD/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_nnpdf23_VR_SD_24_02_z01_b01.root";
  TString root_in_QCD2 =" /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/VR_SD/uhh2.AnalysisModuleRunner.MC.QCD_flat_VR_SD_24_02_z01_b01.root";

// HOTVR SD beta 1 zcut 01
 TString root_in_ttbar = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/parameter_scan/ptt30/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_nnpdf23_30_0.1_1.root";
 TString root_in_QCD = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/parameter_scan/ptt30/uhh2.AnalysisModuleRunner.MC.QCD_flat_30_0.1_1.root";

  TString outdir = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/plots/VR_SD_vs_HOTVR_SD/";
  TString label = "HOTVR SD, #beta=1, z_{cut}=0.1";
  TString label2 = "VR SD, #beta=1, z_{cut}=0.1";

// my study
  TFile *input_ttbar = new TFile(" /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/root_09_06_AK10/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_ROC_09_06_AK10.root", "READ");
  TFile *input_QCD = new TFile(" /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/root_09_06_AK10/uhh2.AnalysisModuleRunner.MC.QCD_flat_ROC_09_06_AK10.root", "READ");

  TFile *files_ttbar = new TFile(root_in_ttbar, "READ");
  TFile *files_QCD = new TFile(root_in_QCD, "READ");

  TFile *files_ttbar2 = new TFile(root_in_ttbar2, "READ");
  TFile *files_QCD2 = new TFile(root_in_QCD2, "READ");

    //parameter
  uint njets = 1;
  TString jets[njets];
  jets[0]="hotvr_jets";

uint nptmin = 1;
TString ptmin[nptmin];
ptmin[0]="";
// ptmin[1]="_200";
// ptmin[2]="_400";
// ptmin[3]="_600";
// ptmin[4]="_800";
//ptmin[5]="_1000";

uint nvariables = 1;
TString variables[nvariables];
variables[0]="p_{T}";
//variables[0]="mass";

TString variablenames[nvariables];
variablenames[0]="p_{T} [GeV]";
//variablenames[0]="m_{jet} [GeV]";

TString ptbins[nptmin];
ptbins[0]="";
// ptbins[1]="200 < p_{T} [GeV] < 400";
// ptbins[2]="400 < p_{T} [GeV] < 600";
// ptbins[3]="600 < p_{T} [GeV] < 800";
// ptbins[4]="800 < p_{T} [GeV] < 1000";
//ptbins[5]=", 1000 < p_{T} [GeV] < 1200";

  for (size_t i = 0; i < njets; i++) { // loop over jets
    for (size_t j = 0; j < nptmin; j++) { // loop over pt bins
      for (size_t k = 0; k < nvariables; k++) { // loop over variables
  TH1F* hist_ttbar_SD = (TH1F*)files_ttbar->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+ "/"+variables[k]);
  TH1F* hist_QCD_SD = (TH1F*)files_QCD->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+"/"+variables[k]);

  // TH1F* hist_ttbar_SD2 = (TH1F*)files_ttbar2->Get("HOTVRStudiesHists/mass_jets_SD"+ptmin[j]);
  // TH1F* hist_QCD_SD2 = (TH1F*)files_QCD2->Get("HOTVRStudiesHists/mass_jets_SD"+ptmin[j]);

  TH1F* hist_ttbar_SD2 = (TH1F*)files_ttbar2->Get("HOTVRStudiesHists/p_{T}_jets_SD"+ptmin[j]);
  TH1F* hist_QCD_SD2 = (TH1F*)files_QCD2->Get("HOTVRStudiesHists/p_{T}_jets_SD"+ptmin[j]);

// std::cout << "bins" << '\n';
// for (size_t bin = 0; bin < 1800; bin++) {
//     std::cout << "before"<< hist_ttbar_SD->GetBinContent(bin) << '\n';
//     hist_ttbar_SD->SetBinContent(bin, 0);
//     std::cout << "after"<< hist_ttbar_SD->GetBinContent(bin) << '\n';
//
// }

TCanvas* canvas = new TCanvas("c", "c", 600, 600);
gPad->SetLeftMargin(0.2);
gPad->SetBottomMargin(0.2);

hist_ttbar_SD->SetTitle("");
hist_ttbar_SD->Scale(1/hist_ttbar_SD->Integral());
hist_ttbar_SD->SetLineColor(kRed);
hist_ttbar_SD->SetLineWidth(2);
hist_ttbar_SD->Draw("H");
hist_QCD_SD->Scale(1/hist_QCD_SD->Integral());
hist_QCD_SD->SetLineColor(kRed);
hist_QCD_SD->SetLineStyle(kDotted);
hist_QCD_SD->SetLineWidth(2);
hist_QCD_SD->Draw("H same");

TH1F* hist_ttbar;
TH1F* hist_QCD;

hist_ttbar = (TH1F*)input_ttbar->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+ "/"+variables[k]);
hist_QCD = (TH1F*)input_QCD->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+"/"+variables[k]);

double n_ttbar = hist_ttbar->Integral();
double n_qcd = hist_QCD->Integral();

hist_ttbar->Scale(1/n_ttbar);
hist_ttbar->SetLineColor(kBlack);
hist_ttbar->SetLineWidth(2);
hist_ttbar->Draw("H same");
hist_QCD->Scale(1/n_qcd);
hist_QCD->SetLineColor(kBlack);
hist_QCD->SetLineStyle(kDotted);
hist_QCD->SetLineWidth(2);
hist_QCD->Draw("H same");

hist_ttbar_SD2->Scale(1/hist_ttbar_SD2->Integral());
hist_ttbar_SD2->SetLineColor(kAzure+2);
hist_ttbar_SD2->SetLineStyle(9);
hist_ttbar_SD2->SetLineWidth(2);
hist_ttbar_SD2->Draw("H same");
hist_QCD_SD2->Scale(1/hist_QCD_SD2->Integral());
hist_QCD_SD2->SetLineColor(kAzure+2);
hist_QCD_SD2->SetLineStyle(2);
hist_QCD_SD2->SetLineWidth(2);
hist_QCD_SD2->Draw("H same");

hist_ttbar_SD->GetXaxis()->SetTitle(variablenames[k]);
hist_ttbar_SD->GetXaxis()->SetLabelSize(0.04);
hist_ttbar_SD->GetXaxis()->SetTitleSize(0.06);
hist_ttbar_SD->GetYaxis()->SetTitle("fraction of jets");
hist_ttbar_SD->GetYaxis()->SetLabelSize(0.04);
hist_ttbar_SD->GetYaxis()->SetTitleSize(0.06);

  // if(j>2){ // mass high
  //   hist_ttbar_SD->GetYaxis()->SetRangeUser(0,0.16);
  // }
  // else if(j==1){ // mass low
  //   hist_ttbar_SD->GetYaxis()->SetRangeUser(0,0.08);
  // }
  // else{ // mass low
  //   hist_ttbar_SD->GetYaxis()->SetRangeUser(0,0.16);
  //   hist_ttbar_SD->GetXaxis()->SetRangeUser(0,1000);
  // }
  hist_ttbar_SD->GetYaxis()->SetRangeUser(0,0.2);
  hist_ttbar_SD->GetXaxis()->SetRangeUser(0,2000);

  auto legend = new TLegend(0.25, 0.65, 0.85, 0.85);
  legend->SetTextSize(.03);
//  legend->SetHeader(ptbins[j]);
  legend->SetNColumns(2);
  legend->AddEntry(hist_ttbar,"t#bar{t} HOTVR MJ", "l");
  legend->AddEntry(hist_QCD,"QCD ", "l");
  legend->AddEntry(hist_ttbar_SD,"t#bar{t} "+label, "l");
  legend->AddEntry(hist_QCD_SD,"QCD ", "l");
  legend->AddEntry(hist_ttbar_SD2,"t#bar{t} "+label2, "l");
  legend->AddEntry(hist_QCD_SD2,"QCD ", "l");

  legend->Draw();
  canvas->SaveAs(outdir + jets[i] + ptmin[j] +"_"+ variables[k]+".eps");
  }//end variables loop
  }//end pt loop
  }// end jets loop

  return 0;
 }
