#include "TSystem.h"
#include <vector>

#include <iostream>
#include "../include/CentralInclude.h"

int main(){
  SetStyle();

  TString root_in_ttbar = " /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/HOTVR_ML/hists/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_nnpdf23_hotvr.root";
  TString root_in_QCD = " /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/HOTVR_ML/hists/uhh2.AnalysisModuleRunner.MC.QCD_flat_prod1_hotvr.root";

  TString root_in_ttbar2 = " /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/HOTVR_ML/hists/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_nnpdf23_vr.root";
  TString root_in_QCD2 = " /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/HOTVR_ML/hists/uhh2.AnalysisModuleRunner.MC.QCD_flat_prod1_vr.root";

  TString outdir = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/plots/VR_comparison/HOTVR_ML/";
  TString label = "HOTVR SD ";
  TString label2 = "VR ";

  TString SD_param = "#beta=1, z_{cut}=0.05 ";

  TFile *files_ttbar = new TFile(root_in_ttbar, "READ");
  TFile *files_QCD = new TFile(root_in_QCD, "READ");

  TFile *files_ttbar2 = new TFile(root_in_ttbar2, "READ");
  TFile *files_QCD2 = new TFile(root_in_QCD2, "READ");

    //parameter
  uint njets = 1;
  TString jets[njets];
  jets[0]="jets";

  TString jetnames[njets];
  jetnames[0]="matched jets";

uint nptmin = 4;
TString ptmin[nptmin];
ptmin[0]="";
ptmin[1]="_200";
ptmin[2]="_350";
ptmin[3]="_500";

uint nvariables = 3;
TString variables[nvariables];
variables[0]="p_{T}";
variables[1]="mass";
variables[2]="tau32";

TString variablenames[nvariables];
variablenames[0]="p_{T} [GeV]";
variablenames[1]="m_{jet} [GeV]";
variablenames[2]="#tau_{3,2}";

TString ptbins[nptmin];
ptbins[0]="";
ptbins[1]=" 200 < p_{T} [GeV] < 350";
ptbins[2]=" 350 < p_{T} [GeV] < 500";
ptbins[3]=" 500 < p_{T} [GeV] ";

  for (size_t i = 0; i < njets; i++) { // loop over jets
    for (size_t j = 0; j < nptmin; j++) { // loop over pt bins
      for (size_t k = 0; k < nvariables; k++) { // loop over variables

  TH1F* hist_ttbar_SD = (TH1F*)files_ttbar->Get("VRJetsHists_jets"+ptmin[j]+ "/"+variables[k]);
  TH1F* hist_QCD_SD = (TH1F*)files_QCD->Get("VRJetsHists_jets"+ptmin[j]+"/"+variables[k]);

  TH1F* hist_ttbar_VR = (TH1F*)files_ttbar2->Get("VRJetsHists_jets"+ptmin[j]+"/"+variables[k]);
  TH1F* hist_QCD_VR = (TH1F*)files_QCD2->Get("VRJetsHists_jets"+ptmin[j]+"/"+variables[k]);

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

hist_ttbar_VR->Scale(1/hist_ttbar_VR->Integral());
hist_ttbar_VR->SetLineColor(kBlack);
hist_ttbar_VR->SetLineWidth(2);
hist_ttbar_VR->Draw("H same");
hist_QCD_VR->Scale(1/hist_QCD_VR->Integral());
hist_QCD_VR->SetLineColor(kBlack);
hist_QCD_VR->SetLineStyle(kDotted);
hist_QCD_VR->SetLineWidth(2);
hist_QCD_VR->Draw("H same");

hist_ttbar_SD->GetXaxis()->SetTitle(variablenames[k]);
hist_ttbar_SD->GetXaxis()->SetLabelSize(0.04);
hist_ttbar_SD->GetXaxis()->SetTitleSize(0.06);
hist_ttbar_SD->GetYaxis()->SetTitle("fraction of jets");
hist_ttbar_SD->GetYaxis()->SetLabelSize(0.04);
hist_ttbar_SD->GetYaxis()->SetTitleSize(0.06);

  if(k==1&&j>2){ // mass
    hist_ttbar_SD->GetYaxis()->SetRangeUser(0,0.1);
  }
  else if(k==1&&j<3){ // mass low
    hist_ttbar_SD->GetYaxis()->SetRangeUser(0,0.06);
  }
  else if(k==0){ // pt
    hist_ttbar_SD->GetYaxis()->SetRangeUser(0,0.1);
    hist_ttbar_SD->GetXaxis()->SetRangeUser(0,1000);
  }
  else{
    hist_ttbar_SD->GetYaxis()->SetRangeUser(0,0.1);
  }

  auto legend = new TLegend(0.25, 0.7, 0.85, 0.85);
  legend->SetTextSize(.03);
  legend->SetHeader("matched jets "+ptbins[j]);
  legend->SetNColumns(2);
  //legend->AddEntry(hist_ttbar_SD, label+SD_param, "");
//  legend->AddEntry(hist_QCD_SD," ", "");
  legend->AddEntry(hist_ttbar_SD,"t#bar{t} " +label+SD_param, "l");
  legend->AddEntry(hist_QCD_SD,"QCD ", "l");
  //legend->AddEntry(hist_ttbar_VR,label2, "");
//  legend->AddEntry(hist_QCD_VR," ", "");
  legend->AddEntry(hist_ttbar_VR,"t#bar{t} "+label2, "l");
  legend->AddEntry(hist_QCD_VR,"QCD ", "l");

  legend->Draw();
  canvas->SaveAs(outdir + "matched_jets" + ptmin[j] +"_"+ variables[k]+".eps");
  }//end variables loop
  }//end pt loop
  }// end jets loop

  return 0;
 }
