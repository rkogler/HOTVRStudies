// macro to plot two different HOTVR SD configurations for ttbar and QCD in one plot
// You need to change:
// input directories, outdir, labels
// run with
// ./macro_two_SD_hists

#include "TSystem.h"
#include <vector>

#include <iostream>
#include "../include/CentralInclude.h"

int main(){
  SetStyle();

  TString root_in_ttbar = " /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/HOTVR_jets_mu_condition/rho_600_alpha_1/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_all.root";
  TString root_in_QCD = " /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/HOTVR_jets_mu_condition/rho_600_alpha_1/uhh2.AnalysisModuleRunner.MC.QCD_flat_all.root";

  TString root_in_ttbar2 = " /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/HOTVR_jets_mu_condition/rho_600_alpha_1_no_subjet_permutations/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_nnpdf23.root";
  TString root_in_QCD2 = " /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/HOTVR_jets_mu_condition/rho_600_alpha_1_no_subjet_permutations/uhh2.AnalysisModuleRunner.MC.QCD_flat_prod1.root";

  // TString root_in_ttbar2 = " /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/HOTVR_SD_final/ptt0_mu40/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_ptt0_mu40.root";
  // TString root_in_QCD2 = " /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/HOTVR_SD_final/ptt0_mu40/uhh2.AnalysisModuleRunner.MC.QCD_flat_ptt0_mu40.root";

  // TString root_in_ttbar2 = " /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/HOTVR_SD_final/ptt30_mu0/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_ptt30_mu0.root";
  // TString root_in_QCD2 = " /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/HOTVR_SD_final/ptt30_mu0/uhh2.AnalysisModuleRunner.MC.QCD_flat_ptt30_mu0.root";

  TString outdir = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/plots/mu_condition_test/";
  TString label = "subjet permutations";
  TString label2 = "pseudojets";

  TString SD_param = "HOTVR SD #beta=1, z_{cut}=0.05, #mu=40 GeV";

// my study
  // TFile *input_ttbar = new TFile(" /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/root_09_06_AK10/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_ROC_09_06_AK10.root", "READ");
  // TFile *input_QCD = new TFile(" /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/root_09_06_AK10/uhh2.AnalysisModuleRunner.MC.QCD_flat_ROC_09_06_AK10.root", "READ");

  TFile *files_ttbar = new TFile(root_in_ttbar, "READ");
  TFile *files_QCD = new TFile(root_in_QCD, "READ");

  TFile *files_ttbar2 = new TFile(root_in_ttbar2, "READ");
  TFile *files_QCD2 = new TFile(root_in_QCD2, "READ");

    //parameter
  uint njets = 4;
  TString jets[njets];
  jets[0]="hotvr_jets";
   jets[1]="hotvr_jets_Nsub3";
   jets[2]="hotvr_jets_fpt";
   jets[3]="hotvr_jets_mass";
  // jets[1]="matched_jets";
  // jets[2]="tagged_jets";

  TString jetnames[njets];
  jetnames[0]="HOTVR jets";
   jetnames[1]="HOTVR jets, n_{subjets}>2";
   jetnames[2]="HOTVR jets, f_{p_{T}}>0.8";
   jetnames[3]="HOTVR jets mass";
  // jetnames[4]="matched jets";
  // jetnames[5]="tagged jets";


uint nptmin = 6;
TString ptmin[nptmin];
ptmin[0]="";
ptmin[1]="_200";
ptmin[2]="_400";
ptmin[3]="_600";
ptmin[4]="_800";
ptmin[5]="_1000";

uint nvariables = 17;
TString variables[nvariables];
variables[0]="p_{T}";
variables[1]="mass";
variables[2]="mmin";
variables[3]="fpt";
variables[4]="nsubjets";
variables[5]="tau32";
variables[6]="subjet1_p_{T}";
variables[7]="subjet2_p_{T}";
variables[8]="subjet3_p_{T}";
variables[9]="subjet4_p_{T}";
variables[10]="subjet0_p_{T}";
variables[11]="sumsubjetsp_{T}";
variables[12]="subjet1_dR";
variables[13]="subjet2_dR";
variables[14]="subjet3_dR";
variables[15]="subjet4_dR";
variables[16]="subjet0_dR";

TString variablenames[nvariables];
variablenames[0]="p_{T} [GeV]";
variablenames[1]="m_{jet} [GeV]";
variablenames[2]="m_{min} [GeV]";
variablenames[3]="f_{p_{T}}";
variablenames[4]="n_{subjets}";
variablenames[5]="#tau_{3,2}";
variablenames[6]="subjet 2 p_{T} [GeV]";
variablenames[7]="subjet 3 p_{T} [GeV]";
variablenames[8]="subjet 4 p_{T} [GeV]";
variablenames[9]="subjet 5 p_{T} [GeV]";
variablenames[10]="subjet 1 p_{T} [GeV]";
variablenames[11]="sum subjets p_{T} [GeV]";
variablenames[12]="subjet 2 dR";
variablenames[13]="subjet 3 dR";
variablenames[14]="subjet 4 dR";
variablenames[15]="subjet 5 dR";
variablenames[16]="subjet 1 dR";

TString ptbins[nptmin];
ptbins[0]="";
ptbins[1]=", 200 < p_{T} [GeV] < 400";
ptbins[2]=", 400 < p_{T} [GeV] < 600";
ptbins[3]=", 600 < p_{T} [GeV] < 800";
ptbins[4]=", 800 < p_{T} [GeV] < 1000";
ptbins[5]=", 1000 < p_{T} [GeV] < 1200";

  for (size_t i = 0; i < njets; i++) { // loop over jets
    for (size_t j = 0; j < nptmin; j++) { // loop over pt bins
      for (size_t k = 0; k < nvariables; k++) { // loop over variables

  TH1F* hist_ttbar_SD = (TH1F*)files_ttbar->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+ "/"+variables[k]);
  TH1F* hist_QCD_SD = (TH1F*)files_QCD->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+"/"+variables[k]);

//for VR jets
//  TH1F* hist_ttbar_SD = (TH1F*)files_ttbar->Get("HOTVRStudiesHists/mass_jets_SD_"+ptmin[j]);
//  TH1F* hist_QCD_SD = (TH1F*)files_QCD->Get("HOTVRStudiesHists/mass_jets_SD_"+ptmin[j]);
// if(k==1){
//   TH1F* hist_ttbar_SD = (TH1F*)files_ttbar->Get("HOTVRStudiesHists/mass_jets_SD_"+ptmin[j]);
//   TH1F* hist_QCD_SD = (TH1F*)files_QCD->Get("HOTVRStudiesHists/mass_jets_SD_"+ptmin[j]);
// }

  TH1F* hist_ttbar_SD2 = (TH1F*)files_ttbar2->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+ "/"+variables[k]);
  TH1F* hist_QCD_SD2 = (TH1F*)files_QCD2->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+"/"+variables[k]);

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
// if (k<6 && i== 0) { // if possible, include old HOTVR jets to the plot
// hist_ttbar = (TH1F*)input_ttbar->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+ "/"+variables[k]);
// hist_QCD = (TH1F*)input_QCD->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+"/"+variables[k]);
//
// double n_ttbar = hist_ttbar->Integral();
// double n_qcd = hist_QCD->Integral();
//
// hist_ttbar->Scale(1/n_ttbar);
// hist_ttbar->SetLineColor(kBlack);
// hist_ttbar->SetLineWidth(2);
// hist_ttbar->Draw("H same");
// hist_QCD->Scale(1/n_qcd);
// hist_QCD->SetLineColor(kBlack);
// hist_QCD->SetLineStyle(kDotted);
// hist_QCD->SetLineWidth(2);
// hist_QCD->Draw("H same");
// }

hist_ttbar_SD2->Scale(1/hist_ttbar_SD2->Integral());
hist_ttbar_SD2->SetLineColor(kGreen+2);
hist_ttbar_SD2->SetLineStyle(9);
hist_ttbar_SD2->SetLineWidth(2);
hist_ttbar_SD2->Draw("H same");
hist_QCD_SD2->Scale(1/hist_QCD_SD2->Integral());
hist_QCD_SD2->SetLineColor(kGreen+2);
hist_QCD_SD2->SetLineStyle(2);
hist_QCD_SD2->SetLineWidth(2);
hist_QCD_SD2->Draw("H same");

hist_ttbar_SD->GetXaxis()->SetTitle(variablenames[k] );
hist_ttbar_SD->GetXaxis()->SetLabelSize(0.04);
hist_ttbar_SD->GetXaxis()->SetTitleSize(0.06);
hist_ttbar_SD->GetYaxis()->SetTitle("fraction of jets");
hist_ttbar_SD->GetYaxis()->SetLabelSize(0.04);
hist_ttbar_SD->GetYaxis()->SetTitleSize(0.06);

double ymax = hist_ttbar_SD->GetMaximum() > hist_QCD_SD->GetMaximum() ? hist_ttbar_SD->GetMaximum() : hist_QCD_SD->GetMaximum();

hist_ttbar_SD->GetYaxis()->SetRangeUser(0,ymax*2);

// if(k==4){ // nsubjets
//   hist_ttbar_SD->GetXaxis()->SetRangeUser(0,8);
// }
// else if(k>5){ // pt subjets
//   hist_ttbar_SD->GetXaxis()->SetRangeUser(0,400);
// }
// else if(k==2){ // mmin
//   hist_ttbar_SD->GetXaxis()->SetRangeUser(0,160);
// }

  auto legend = new TLegend(0.25, 0.6, 0.85, 0.85);
  legend->SetTextSize(.03);
  legend->SetHeader(jetnames[i]+" "+ptbins[j]);
  legend->SetNColumns(2);
// if (k<6) {
//   legend->AddEntry((TObject*)0,"HOTVR MJ ", "");
//   legend->AddEntry((TObject*)0,"" , "");
//   legend->AddEntry(hist_ttbar,"t#bar{t}", "l");
//   legend->AddEntry(hist_QCD,"QCD ", "l");
//   legend->AddEntry(hist_ttbar_SD," " , "");
//   legend->AddEntry(hist_ttbar_SD," " , "");
// }
  legend->AddEntry(hist_ttbar_SD," " + SD_param , "");
  legend->AddEntry(hist_ttbar_SD," " , "");
  legend->AddEntry(hist_ttbar_SD,"t#bar{t} "+label, "l");
  legend->AddEntry(hist_QCD_SD,"QCD ", "l");
  legend->AddEntry(hist_ttbar_SD2,"t#bar{t} "+label2, "l");
  legend->AddEntry(hist_QCD_SD2,"QCD ", "l");

  legend->Draw();
  canvas->SaveAs(outdir + jets[i] + ptmin[j] + variables[k] + ".pdf");
  }//end variables loop
  }//end pt loop
  }// end jets loop

  return 0;
 }
