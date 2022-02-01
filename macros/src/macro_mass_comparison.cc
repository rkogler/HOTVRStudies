// macro to plot two different HOTVR SD configurations for ttbar and QCD in one plot
// You need to change:
// input directories, outdir, labels
// run with
// ./macro_mass_condition

#include "TSystem.h"
#include <vector>

#include <iostream>
#include "../include/CentralInclude.h"

int main(){
  SetStyle();

  TString root_in_ttbar = " /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/HOTVR_jets_mu_condition/subjet_permutations_include_single_particles/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_nnpdf23.root";
  TString root_in_QCD = " /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/HOTVR_jets_mu_condition/subjet_permutations_include_single_particles/uhh2.AnalysisModuleRunner.MC.QCD_flat_prod1.root";

  TString root_in_ttbar2 = " /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/HOTVR_jets_mu_condition/no_subjet_permutations/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_nnpdf23.root";
  TString root_in_QCD2 = " /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/HOTVR_jets_mu_condition/no_subjet_permutations/uhh2.AnalysisModuleRunner.MC.QCD_flat_prod1.root";

  TString outdir = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/plots/mu_condition_lonely_particle/";
  TString label = "jet";
  TString label2 = "sum subjets";

  TString SD_param = "HOTVR SD subjet perm., no doubling";

  TFile *files_ttbar = new TFile(root_in_ttbar, "READ");
  TFile *files_QCD = new TFile(root_in_QCD, "READ");

  TFile *files_ttbar2 = new TFile(root_in_ttbar2, "READ");
  TFile *files_QCD2 = new TFile(root_in_QCD2, "READ");

    //parameter
  uint njets = 2;
  TString jets[njets];
  jets[0]="hotvr_jets";
   jets[1]="hotvr_jets_Nsub1";

  TString jetnames[njets];
  jetnames[0]="HOTVR jets";
   jetnames[1]="HOTVR jets, n_{subjets}==1";


uint nptmin = 6;
TString ptmin[nptmin];
ptmin[0]="";
ptmin[1]="_200";
ptmin[2]="_400";
ptmin[3]="_600";
ptmin[4]="_800";
ptmin[5]="_1000";

uint nvariables = 18;
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
variables[10]="subjet5_p_{T}";
variables[11]="sumsubjetsp_{T}";
variables[12]="subjet1_dR";
variables[13]="subjet2_dR";
variables[14]="subjet3_dR";
variables[15]="subjet4_dR";
variables[16]="subjet5_dR";
variables[17]="sumsubjetsmass";

TString variablenames[nvariables];
variablenames[0]="p_{T} [GeV]";
variablenames[1]="m_{jet} [GeV]";
variablenames[2]="m_{min} [GeV]";
variablenames[3]="f_{p_{T}}";
variablenames[4]="n_{subjets}";
variablenames[5]="#tau_{3,2}";
variablenames[6]="subjet 1 p_{T} [GeV]";
variablenames[7]="subjet 2 p_{T} [GeV]";
variablenames[8]="subjet 3 p_{T} [GeV]";
variablenames[9]="subjet 4 p_{T} [GeV]";
variablenames[10]="subjet 5 p_{T} [GeV]";
variablenames[11]="sum subjets p_{T} [GeV]";
variablenames[12]="subjet 1 dR";
variablenames[13]="subjet 2 dR";
variablenames[14]="subjet 3 dR";
variablenames[15]="subjet 4 dR";
variablenames[16]="subjet 5 dR";
variablenames[17]="sum subjets mass [GeV]";


TString ptbins[nptmin];
ptbins[0]="";
ptbins[1]=", 200 < p_{T} [GeV] < 400";
ptbins[2]=", 400 < p_{T} [GeV] < 600";
ptbins[3]=", 600 < p_{T} [GeV] < 800";
ptbins[4]=", 800 < p_{T} [GeV] < 1000";
ptbins[5]=", 1000 < p_{T} [GeV] < 1200";

std::cout << "Before starting loops " << '\n';
  for (size_t i = 0; i < 1; i++) { // loop over jets
    for (size_t j = 0; j < nptmin; j++) { // loop over pt bins
Int_t k = 1;
std::cout << "jet = "<< i << " , ptbin = "<<j <<" , variable = "<<k << '\n';

  TH1F* hist_ttbar_SD = (TH1F*)files_ttbar->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+ "/"+variables[1]);
  TH1F* hist_QCD_SD = (TH1F*)files_QCD->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+"/"+variables[1]);

  TH1F* hist_ttbar_SD2 = (TH1F*)files_ttbar->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+ "/"+variables[17]);
  TH1F* hist_QCD_SD2 = (TH1F*)files_QCD->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+"/"+variables[17]);

TCanvas* canvas = new TCanvas("c", "c", 600, 600);
gPad->SetLeftMargin(0.2);
gPad->SetBottomMargin(0.2);

hist_ttbar_SD->SetTitle("");

hist_ttbar_SD->Scale(1/hist_ttbar_SD->Integral());
hist_ttbar_SD->SetLineColor(kRed);
hist_ttbar_SD->SetLineWidth(2);
hist_ttbar_SD->Draw("H");
hist_QCD_SD->Scale(1/hist_QCD_SD->Integral());
hist_QCD_SD->SetLineColor(kBlue);
hist_QCD_SD->SetLineStyle(kDotted);
hist_QCD_SD->SetLineWidth(2);
hist_QCD_SD->Draw("H same");

hist_ttbar_SD2->Scale(1/hist_ttbar_SD2->Integral());
hist_ttbar_SD2->SetLineColor(49);
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
//  hist_ttbar_SD->GetXaxis()->SetRangeUser(0,160);

  auto legend = new TLegend(0.25, 0.6, 0.85, 0.85);
  legend->SetTextSize(.03);
  legend->SetHeader(jetnames[i]+" "+ptbins[j]);
  legend->SetNColumns(2);
  legend->AddEntry(hist_ttbar_SD," " + SD_param , "");
  legend->AddEntry(hist_ttbar_SD," " , "");
  legend->AddEntry(hist_ttbar_SD,"t#bar{t} "+label, "l");
  legend->AddEntry(hist_QCD_SD,"QCD ", "l");
  legend->AddEntry(hist_ttbar_SD2,"t#bar{t} "+label2, "l");
  legend->AddEntry(hist_QCD_SD2,"QCD ", "l");

  legend->Draw();
  canvas->SaveAs(outdir + jets[i] + ptmin[j] + "_"+ variables[k] + "_comparison_sub_perm_no_doubling.pdf");

  }//end pt loop
  }// end jets loop

  return 0;
 }
