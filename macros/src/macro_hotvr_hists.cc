#include "TSystem.h"
#include <vector>

#include <iostream>
#include "../include/CentralInclude.h"

int main(){
  SetStyle();

// my study
  TFile *input_ttbar = new TFile(" /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/root_09_06_AK10/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_ROC_09_06_AK10.root", "READ");
  TFile *input_QCD = new TFile(" /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/root_09_06_AK10/uhh2.AnalysisModuleRunner.MC.QCD_flat_ROC_09_06_AK10.root", "READ");

    //parameter
  uint njets = 3;
  TString jets[njets];
  jets[0]="hotvr_jets";
  jets[1]="matched_jets";
  jets[2]="tagged_jets";
  // jets[3]="matched_jets_Nsub3";
  // jets[4]="matched_jets_fpt";

  TString jetnames[njets];
  jetnames[0]="HOTVR jets";
  jetnames[1]="matched jets";
  jetnames[2]="tagged jets";
  // jetnames[3]="matched jets n_{subjets}>2";
  // jetnames[4]="matched jets f_{p_{T}}";

uint nptmin = 6;
TString ptmin[nptmin];
ptmin[0]="";
ptmin[1]="_200";
ptmin[2]="_400";
ptmin[3]="_600";
ptmin[4]="_800";
ptmin[5]="_1000";

uint nvariables = 6;
TString variables[nvariables];
variables[0]="p_{T}";
variables[1]="mass";
// variables[2]="eta";
// variables[3]="phi";
// variables[4]="energy";
// variables[5]="max_distance";
variables[2]="mmin";
variables[3]="fpt";
variables[4]="nsubjets";
// variables[9]="tau1";
// variables[10]="tau2";
// variables[11]="tau3";
// variables[12]="tau21";
variables[5]="tau32";
// variables[14]="matching_radius";
// variables[15]="max_distance_minus_matching_radius";

TString variablesnames[nvariables];
variablesnames[0]="p_{T} [GeV]";
variablesnames[1]="m_{jet} [GeV]";
// variablesnames[2]="eta";
// variablesnames[3]="phi";
// variablesnames[4]="energy";
// variablesnames[5]="max_distance";
variablesnames[2]="m_{min} [GeV]";
variablesnames[3]="f_{p_{T}}";
variablesnames[4]="n_{subjets}";
// variablesnames[9]="tau1";
// variablesnames[10]="tau2";
// variablesnames[11]="tau3";
// variablesnames[12]="tau21";
variablesnames[5]="#tau_{3,2}";
// variablesnames[14]="matching_radius";
// variablesnames[15]="max_distance_minus_matching_radius";

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

TCanvas* canvas = new TCanvas("c", "c", 600, 600);
gPad->SetLeftMargin(0.2);
gPad->SetBottomMargin(0.2);

TH1F* hist_ttbar;
TH1F* hist_QCD;

hist_ttbar = (TH1F*)input_ttbar->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+ "/"+variables[k]);
hist_QCD = (TH1F*)input_QCD->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+"/"+variables[k]);

hist_ttbar->SetTitle("");
double n_ttbar = hist_ttbar->Integral();
double n_qcd = hist_QCD->Integral();

hist_ttbar->Scale(1/n_ttbar);
hist_ttbar->SetLineColor(kBlack);
hist_ttbar->SetLineWidth(2);
hist_ttbar->Draw("H");
hist_QCD->Scale(1/n_qcd);
hist_QCD->SetLineColor(kRed);
hist_QCD->SetLineStyle(kDotted);
hist_QCD->SetLineWidth(2);
hist_QCD->Draw("H same");


  hist_ttbar->GetXaxis()->SetTitle(variablesnames[k]);
  hist_ttbar->GetXaxis()->SetLabelSize(0.04);
  hist_ttbar->GetXaxis()->SetTitleSize(0.06);

  hist_ttbar->GetYaxis()->SetTitle("fraction of jets");
  hist_ttbar->GetYaxis()->SetLabelSize(0.04);
  hist_ttbar->GetYaxis()->SetTitleSize(0.06);

  if(k==3){ // fpt
    hist_ttbar->GetYaxis()->SetRangeUser(0,0.25);
  }
  else if(k==4){ // nsubjets
    hist_ttbar->GetYaxis()->SetRangeUser(0,1.2);
    hist_ttbar->GetXaxis()->SetRangeUser(0,8);
  }
  else if(k==1 && j>2){ // mass high
    hist_ttbar->GetYaxis()->SetRangeUser(0,0.14);
  }
  else if(k==1 && j<2){ // mass low
    hist_ttbar->GetYaxis()->SetRangeUser(0,0.07);
  }
  else if(k==2 && j<2){ // mmin low
    hist_ttbar->GetYaxis()->SetRangeUser(0,0.05);
    hist_ttbar->GetXaxis()->SetRangeUser(0,160);
  }
  else if(k==2 && j>2){ // mmin high
    hist_ttbar->GetYaxis()->SetRangeUser(0,0.1);
    hist_ttbar->GetXaxis()->SetRangeUser(0,160);
  }
  else if(k==5){ // tau 32
    hist_ttbar->GetYaxis()->SetRangeUser(0,0.06);
  }
  else if(k==0 && j==0){ // pt
    hist_ttbar->GetYaxis()->SetRangeUser(0,0.05);
  }
  else{
    hist_ttbar->GetYaxis()->SetRangeUser(0,0.1);
  }

  auto legend = new TLegend(0.25, 0.7, 0.85, 0.85);
  legend->SetTextSize(.04);
  legend->SetHeader(jetnames[i]+" "+ptbins[j]);
  legend->AddEntry(hist_ttbar,"t#bar{t}", "l");
  legend->AddEntry(hist_QCD,"QCD", "l");

  legend->Draw();

  TString outdir = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/plots/hotvr_jets/";
  canvas->SaveAs(outdir + jets[i] + ptmin[j] +"_"+ variables[k]+".eps");
  }//end variables loop
  }//end pt loop
  }// end jets loop

  return 0;
 }
