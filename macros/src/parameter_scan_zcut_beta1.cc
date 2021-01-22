#include "TSystem.h"
#include <vector>

#include <iostream>
#include "../include/CentralInclude.h"

vector<char*> get_filenames(const char* ext)
{
  const char* inDir = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/parameter_scan/ptt30/";
  char* dir = gSystem->ExpandPathName(inDir);
  void* dirp = gSystem->OpenDirectory(dir);
  const char* entry;
  vector<char*> filenames;
  TString str;
  while((entry = (char*)gSystem->GetDirEntry(dirp))) {
    str = entry;
    if(str.Contains(ext))
      filenames.push_back(gSystem->ConcatFileName(dir, entry));
  }
  return filenames;
}

int main(){
  SetStyle();
// my study
  TFile *input_ttbar = new TFile(" /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/root_09_06_AK10/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_ROC_09_06_AK10.root", "READ");
  TFile *input_QCD = new TFile(" /nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/root_09_06_AK10/uhh2.AnalysisModuleRunner.MC.QCD_flat_ROC_09_06_AK10.root", "READ");

    //parameter
  uint njets = 1;
  TString jets[njets];
  jets[0]="hotvr_jets";
//  jets[1]="matched_jets";
//  jets[2]="tagged_jets";
//  jets[3]="matched_jets_Nsub3";
//  jets[4]="matched_jets_fpt";

TString jetnames[njets];
jetnames[0]="HOTVR jets";

uint nptmin = 6;
TString ptmin[nptmin];
ptmin[0]="";
ptmin[1]="_200";
ptmin[2]="_400";
ptmin[3]="_600";
ptmin[4]="_800";
ptmin[5]="_1000";

uint nvariables = 11;
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
variables[6]="subjet1_p_{T}";
variables[7]="subjet2_p_{T}";
variables[8]="subjet3_p_{T}";
variables[9]="subjet4_p_{T}";
variables[10]="subjet5_p_{T}";


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

TString ptbins[nptmin];
ptbins[0]="";
ptbins[1]=", 200 < p_{T} [GeV] < 400";
ptbins[2]=", 400 < p_{T} [GeV] < 600";
ptbins[3]=", 600 < p_{T} [GeV] < 800";
ptbins[4]=", 800 < p_{T} [GeV] < 1000";
ptbins[5]=", 1000 < p_{T} [GeV] < 1200";

  vector<char*> filenames = get_filenames(".root");
  std::cout << "get filenames" << '\n';
  vector<TFile*> files_ttbar;
  vector<TFile*> files_QCD;

  for (int i = 0; i < filenames.size(); ++i) //loop over root files
  {
      TFile *f = new TFile(filenames.at(i)); // create file
      TString filename = filenames.at(i);
      if (filename.Contains(".ttbar")) {
        files_ttbar.push_back(f); // list of files
        std::cout << filenames.at(i) << '\n';
      }
      if (filename.Contains(".QCD")) {
        files_QCD.push_back(f); // list of files
        std::cout << filenames.at(i) << '\n';
      }
    }

  for (size_t i = 0; i < njets; i++) { // loop over jets
    for (size_t j = 0; j < nptmin; j++) { // loop over pt bins
      for (size_t k = 0; k < nvariables; k++) { // loop over variables

        TH1F* hist_ttbar_SD = (TH1F*)files_ttbar.at(6)->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+ "/"+variables[k]);
        TH1F* hist_QCD_SD = (TH1F*)files_QCD.at(6)->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+"/"+variables[k]);

        TH1F* hist_ttbar_SD1 = (TH1F*)files_ttbar.at(7)->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+ "/"+variables[k]);
        TH1F* hist_QCD_SD1 = (TH1F*)files_QCD.at(9)->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+"/"+variables[k]);

        TH1F* hist_ttbar_SD2 = (TH1F*)files_ttbar.at(11)->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+ "/"+variables[k]);
        TH1F* hist_QCD_SD2 = (TH1F*)files_QCD.at(7)->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+"/"+variables[k]);

        TH1F* hist_ttbar_SD3 = (TH1F*)files_ttbar.at(15)->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+ "/"+variables[k]);
        TH1F* hist_QCD_SD3 = (TH1F*)files_QCD.at(8)->Get("HOTVRJetsHists_"+jets[i]+ptmin[j]+"/"+variables[k]);


        TCanvas* canvas = new TCanvas("c", "c", 600, 600);
        gPad->SetLeftMargin(0.2);
        gPad->SetBottomMargin(0.2);

        hist_ttbar_SD->SetTitle("");

        hist_ttbar_SD->Scale(1/hist_ttbar_SD->Integral());
        hist_ttbar_SD->SetLineColor(kOrange-3);
        hist_ttbar_SD->SetLineWidth(2);
        hist_ttbar_SD->Draw("H");
        hist_QCD_SD->Scale(1/hist_QCD_SD->Integral());
        hist_QCD_SD->SetLineColor(kOrange-3);
        hist_QCD_SD->SetLineStyle(kDotted);
        hist_QCD_SD->SetLineWidth(2);
        hist_QCD_SD->Draw("H same");

        TH1F* hist_ttbar;
        TH1F* hist_QCD;
        if (k<6) {
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
        }

  hist_ttbar_SD1->Scale(1/hist_ttbar_SD1->Integral());
  hist_ttbar_SD1->SetLineColor(kRed);
  hist_ttbar_SD1->SetLineWidth(2);
  hist_ttbar_SD1->Draw("H same");
  hist_QCD_SD1->Scale(1/hist_QCD_SD1->Integral());
  hist_QCD_SD1->SetLineColor(kRed);
  hist_QCD_SD1->SetLineStyle(kDotted);
  hist_QCD_SD1->SetLineWidth(2);
  hist_QCD_SD1->Draw("H same");

  hist_ttbar_SD2->Scale(1/hist_ttbar_SD2->Integral());
  hist_ttbar_SD2->SetLineColor(kRed+2);
  hist_ttbar_SD2->SetLineWidth(2);
  hist_ttbar_SD2->Draw("H same");
  hist_QCD_SD2->Scale(1/hist_QCD_SD2->Integral());
  hist_QCD_SD2->SetLineColor(kRed+2);
  hist_QCD_SD2->SetLineStyle(kDotted);
  hist_QCD_SD2->SetLineWidth(2);
  hist_QCD_SD2->Draw("H same");

  hist_ttbar_SD3->Scale(1/hist_ttbar_SD3->Integral());
  hist_ttbar_SD3->SetLineColor(kViolet-1);
  hist_ttbar_SD3->SetLineWidth(2);
  hist_ttbar_SD3->Draw("H same");
  hist_QCD_SD3->Scale(1/hist_QCD_SD3->Integral());
  hist_QCD_SD3->SetLineColor(kViolet-1);
  hist_QCD_SD3->SetLineStyle(kDotted);
  hist_QCD_SD3->SetLineWidth(2);
  hist_QCD_SD3->Draw("H same");

  hist_ttbar_SD->GetXaxis()->SetTitle(variablenames[k]);
  hist_ttbar_SD->GetXaxis()->SetLabelSize(0.04);
  hist_ttbar_SD->GetXaxis()->SetTitleSize(0.06);
  hist_ttbar_SD->GetYaxis()->SetTitle("fraction of jets");
  hist_ttbar_SD->GetYaxis()->SetLabelSize(0.04);
  hist_ttbar_SD->GetYaxis()->SetTitleSize(0.06);
  if(k==3){ // fpt
    hist_ttbar_SD->GetYaxis()->SetRangeUser(0,0.25);
  }
  else if(k==4){ // nsubjets
    hist_ttbar_SD->GetYaxis()->SetRangeUser(0,2);
  }
  else if(k==1&&j>2){ // mass
    hist_ttbar_SD->GetYaxis()->SetRangeUser(0,0.2);
  }
  else if(k==1&&j<3){ // mass
    hist_ttbar_SD->GetYaxis()->SetRangeUser(0,0.12);
  }
  else if(k==2 && j<2){ // mmin low
    hist_ttbar_SD->GetYaxis()->SetRangeUser(0,0.08);
    hist_ttbar_SD->GetXaxis()->SetRangeUser(0,160);
  }
  else if(k==2 && j>2){ // mmin high
    hist_ttbar_SD->GetYaxis()->SetRangeUser(0,0.12);
    hist_ttbar_SD->GetXaxis()->SetRangeUser(0,160);
  }
  else if(k>5){ // pt subjets
    hist_ttbar_SD->GetYaxis()->SetRangeUser(0,0.4);
    hist_ttbar_SD->GetXaxis()->SetRangeUser(0,200);
  }
  else{
    hist_ttbar_SD->GetYaxis()->SetRangeUser(0,0.1);
  }

  auto legend = new TLegend(0.25, 0.6, 0.85, 0.85);
  legend->SetTextSize(.03);
  legend->SetHeader(jetnames[i]+" "+ptbins[j]);
  legend->SetNColumns(2);

  if (k<6) {
    legend->AddEntry(hist_ttbar,"t#bar{t} HOTVR MJ", "l");
    legend->AddEntry(hist_QCD,"QCD HOTVR MJ", "l");
  }
  legend->AddEntry((TObject*)0, "", "");
  legend->AddEntry((TObject*)0, "", "");
  legend->AddEntry(hist_ttbar_SD,"HOTVR SD, #beta=1", "");
  legend->AddEntry(hist_ttbar_SD," ", "");

  legend->AddEntry(hist_ttbar_SD,"t#bar{t} z_{cut}=0.01", "l");
  legend->AddEntry(hist_QCD_SD,"QCD z_{cut}=0.01", "l");

  legend->AddEntry(hist_ttbar_SD1,"t#bar{t} z_{cut}=0.05", "l");
  legend->AddEntry(hist_QCD_SD1,"QCD z_{cut}=0.05", "l");

  legend->AddEntry(hist_ttbar_SD2,"t#bar{t} z_{cut}=0.1", "l");
  legend->AddEntry(hist_QCD_SD2,"QCD z_{cut}=0.1", "l");

  legend->AddEntry(hist_ttbar_SD3,"t#bar{t} z_{cut}=0.2", "l");
  legend->AddEntry(hist_QCD_SD3,"QCD z_{cut}=0.2", "l");

  legend->Draw();
  canvas->SaveAs("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/plots/SD_comparison/parameter_scan/ptt30_zcutscan/" + jets[i] + ptmin[j] +"_"+ variables[k]+"_beta1_ptt30.eps");
  }//end variables loop
  }//end pt loop
  }// end jets loop

  return 0;
 }
