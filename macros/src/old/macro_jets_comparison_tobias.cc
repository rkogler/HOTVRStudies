#include "../include/CentralInclude.h"

int main(){
  SetStyle();
// my study
TFile *input_ttbar_AK10 = new TFile(" /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/root_09_06_AK10/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_ROC_09_06_AK10.root", "READ");
TFile *input_QCD_AK10 = new TFile(" /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/root_09_06_AK10/uhh2.AnalysisModuleRunner.MC.QCD_flat_ROC_09_06_AK10.root", "READ");

TFile *input_ttbar = new TFile(" /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/root_12_06_AK4/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_ROC_12_06.root", "READ");
TFile *input_QCD = new TFile(" /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/root_12_06_AK4/uhh2.AnalysisModuleRunner.MC.QCD_flat_ROC_12_06.root", "READ");

  // HOTVR paper
  TFile *input_ttbar_tobias = new TFile(" /nfs/dust/cms/user/albrecha/ROC_Tobias/HOTVRCycle.MC.TTbarEff_gen_ptcut30_hotvr.root", "READ");
  TFile *input_QCD_tobias = new TFile(" /nfs/dust/cms/user/albrecha/ROC_Tobias/HOTVRCycle.MC.QCD_gen_ptcut30_hotvr.root", "READ");

  uint njets = 2;
  TString jets[njets];
  jets[0]="matched_jets";
  jets[1]="tagged_jets";
  // jets[2]="matched_jets_Nsub3";
  // jets[3]="matched_jets_fpt";

  TString jetnames[njets];
  jetnames[0]="matched jets";
  jetnames[1]="tagged jets";
  // jetnames[2]="matched jets Nsub3";
  // jetnames[3]="matched jets f_{p_{T}}";

  uint nptmin = 6;
  TString ptmin[nptmin];
  ptmin[0]="";
  ptmin[1]="_200";
  ptmin[2]="_400";
  ptmin[3]="_600";
  ptmin[4]="_800";
  ptmin[5]="_1000";

  uint nvariables = 10;
  TString variables[nvariables];
  variables[0]="p_{T}";
  variables[1]="mass";
  variables[2]="mmin";
  variables[3]="fpt";
  variables[4]="nsubjets";
  variables[5]="tau1";
  variables[6]="tau2";
  variables[7]="tau3";
  variables[8]="tau21";
  variables[9]="tau32";

  TString variablesnames[nvariables];
  variablesnames[0]="p_{T} [GeV]";
  variablesnames[1]="m_{jet} [GeV]";
  variablesnames[2]="m_{min} [GeV]";
  variablesnames[3]="f_{p{T}}";
  variablesnames[4]="n_{subjets}";
  variablesnames[5]="#tau_{1}";
  variablesnames[6]="#tau_{2}";
  variablesnames[7]="#tau_{3}";
  variablesnames[8]="#tau_{2,1}";
  variablesnames[9]="#tau_{3,2}";

  TString jets_tobias[njets];
  jets_tobias[0]="_beforetag/";
  jets_tobias[1]="/";
  // jets_tobias[2]="_nsub3/";
  // jets_tobias[3]="_ptfraction/";

  TString ptbins_tobias[nptmin];
  ptbins_tobias[0]="_all";
  ptbins_tobias[1]="200-400";
  ptbins_tobias[2]="400-600";
  ptbins_tobias[3]="600-800";
  ptbins_tobias[4]="800-1000";
  ptbins_tobias[5]="1000-1200";

  TString variables_tobias[nvariables];
  variables_tobias[0]="jet_pT";
  variables_tobias[1]="mjet";
  variables_tobias[2]="mmin";
  variables_tobias[3]="ptfraction1";
  variables_tobias[4]="nsubjets";
  variables_tobias[5]="tau1";
  variables_tobias[6]="tau2";
  variables_tobias[7]="tau3";
  variables_tobias[8]="tau2tau1";
  variables_tobias[9]="tau3tau2";

  TString ptbins[nptmin];
  ptbins[0]="";
  ptbins[1]=", 200 < p_{T} [GeV] < 400";
  ptbins[2]=", 400 < p_{T} [GeV] < 600";
  ptbins[3]=", 600 < p_{T} [GeV] < 800";
  ptbins[4]=", 800 < p_{T} [GeV] < 1000";
  ptbins[5]=", 1000 < p_{T} [GeV] < 1200";

  for (size_t i = 0; i < njets; i++) { // loop over jets
    for (size_t j = 1; j < nptmin; j++) { // loop over pt bins
      for (size_t k = 0; k < nvariables; k++) { // loop over variables

  TH1F* hist_ttbar = (TH1F*)input_ttbar->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+ "/"+variables[k]);
  TH1F* hist_QCD = (TH1F*)input_QCD->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+"/"+variables[k]);

  TH1F* hist_ttbar_AK10 = (TH1F*)input_ttbar_AK10->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+ "/"+variables[k]);
  TH1F* hist_QCD_AK10 = (TH1F*)input_QCD_AK10->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+"/"+variables[k]);

  TH1F* hist_ttbar_tobias = (TH1F*)input_ttbar_tobias->Get("HOTVR_hists" +ptbins_tobias[j] +jets_tobias[i]+variables_tobias[k]);
  TH1F* hist_QCD_tobias = (TH1F*)input_QCD_tobias->Get("HOTVR_hists" +ptbins_tobias[j] +jets_tobias[i]+variables_tobias[k]);

  TCanvas* canvas = new TCanvas("c", "c", 600, 600);
  gPad->SetLeftMargin(0.2);
  gPad->SetBottomMargin(0.2);

  hist_ttbar->SetTitle("");

  hist_ttbar->Scale(1/hist_ttbar->Integral());
  hist_ttbar->SetLineColor(kBlack);
  hist_ttbar->SetLineWidth(2);
  hist_ttbar->Draw("H");
  hist_QCD->Scale(1/hist_QCD->Integral());
  hist_QCD->SetLineColor(kBlack);
  hist_QCD->SetLineStyle(kDotted);
  hist_QCD->SetLineWidth(2);
  hist_QCD->Draw("H same");

  hist_ttbar_tobias->Scale(1/hist_ttbar_tobias->Integral());
  hist_ttbar_tobias->SetLineColor(kAzure+9);
  hist_ttbar_tobias->SetLineWidth(2);
  hist_ttbar_tobias->Draw("H same");
  hist_QCD_tobias->Scale(1/hist_QCD_tobias->Integral());
  hist_QCD_tobias->SetLineColor(kAzure+9);
  hist_QCD_tobias->SetLineStyle(kDotted);
  hist_QCD_tobias->SetLineWidth(2);
  hist_QCD_tobias->Draw("H same");

  hist_ttbar_AK10->Scale(1/hist_ttbar_AK10->Integral());
  hist_ttbar_AK10->SetLineColor(kRed);
  hist_ttbar_AK10->SetLineWidth(2);
  hist_ttbar_AK10->Draw("H same");
  hist_QCD_AK10->Scale(1/hist_QCD_AK10->Integral());
  hist_QCD_AK10->SetLineColor(kRed);
  hist_QCD_AK10->SetLineStyle(kDotted);
  hist_QCD_AK10->SetLineWidth(2);
  hist_QCD_AK10->Draw("H same");

  hist_ttbar->GetXaxis()->SetTitle(variablesnames[k]);
  hist_ttbar->GetXaxis()->SetLabelSize(0.04);
  hist_ttbar->GetXaxis()->SetTitleSize(0.06);
  hist_ttbar->GetYaxis()->SetTitle("fraction of jets");
  hist_ttbar->GetYaxis()->SetLabelSize(0.04);
  hist_ttbar->GetYaxis()->SetTitleSize(0.06);

  hist_ttbar->GetYaxis()->SetRangeUser(0,0.1);
  if(k==0){ // pt
    hist_ttbar->GetXaxis()->SetRangeUser(0,1400);
  }

  auto legend = new TLegend(0.25, 0.7, 0.85, 0.85);
  legend->SetTextSize(.03);
  legend->SetHeader(jetnames[i]+" "+ptbins[j]);
  legend->SetNColumns(2);
  legend->AddEntry(hist_ttbar,"t#bar{t} AK4 ", "l");
  legend->AddEntry(hist_QCD,"QCD AK4", "l");
  legend->AddEntry(hist_ttbar_AK10,"t#bar{t} AK10", "l");
  legend->AddEntry(hist_QCD_AK10,"QCD AK10", "l");
  legend->AddEntry(hist_ttbar_tobias,"t#bar{t} HOTVR paper", "l");
  legend->AddEntry(hist_QCD_tobias,"QCD HOTVR paper ", "l");

  legend->Draw();

  canvas->SaveAs("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/plots/comparison_tobias/"+ jets[i] + ptmin[j] +"_"+ variables[k]+ ".eps");
  }//end variables loop
  }//end pt loop
  }// end jets loop

  return 0;
 }
