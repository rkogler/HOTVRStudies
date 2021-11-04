#include "TSystem.h"
#include <vector>

#include <iostream>

#include "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/CMSSW_10_2_17/src/UHH2/HOTVRStudies/macros/include/CentralInclude.h"

vector<char*> get_filenames(const char* ext)
{
  const char* inDir = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/alphascan_2106";
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

void alpha_scan_jet_substructure()
{
  uint njets = 4;
  TString jets[njets];
  jets[0]="hotvr_jets";
  jets[1]="hotvr_jets_Nsub3";
  jets[2]="matched_jets";
  jets[3]="tagged_jets";

  TString jetnames[njets];
  jetnames[0]="HOTVR jets";
  jetnames[1]="HOTVR jets (Nsub>2)";
  jetnames[2]="matched jets";
  jetnames[3]="matched+tagged jets";

  uint nptmin = 6;
  TString ptmin[nptmin];
  ptmin[0]="";
  ptmin[1]="_200";
  ptmin[2]="_400";
  ptmin[3]="_600";
  ptmin[4]="_800";
  ptmin[5]="_1000";

  uint nvariables = 13;
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
  variables[12]="max_distance";

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
  variablenames[12]="max distance";

  TString ptbins[nptmin];
  ptbins[0]="";
  ptbins[1]=", 200 < p_{T} [GeV] < 400";
  ptbins[2]=", 400 < p_{T} [GeV] < 600";
  ptbins[3]=", 600 < p_{T} [GeV] < 800";
  ptbins[4]=", 800 < p_{T} [GeV] < 1000";
  ptbins[5]=", 1000 < p_{T} [GeV] < 1200";


  vector<char*> filenames = get_filenames(".root");
  int n_alpha = 5;
  const char *alpha_values[5] = {"alpha1", "alpha092", "alpha084", "alpha083", "alpha0815"};

  TFile* files_ttbar[n_alpha];
  TFile* files_qcd[n_alpha];

  TH1F* hist_ttbar[n_alpha];
  TH1F* hist_qcd[n_alpha];

  THStack* stack[njets][nptmin][nvariables];
  THStack* stack_QCD[njets][nptmin][nvariables];

  gStyle->SetOptStat(0);
  SetStyle();

  TCanvas *canvas = new TCanvas("c", "c", 600, 600);
  gPad->SetLeftMargin(0.2);
  gPad->SetBottomMargin(0.2);

  for (int i = 0; i < filenames.size(); ++i) //loop over root files
  {
    TString filename = filenames.at(i);
    TFile *f = new TFile(filename);
    if (filename.Contains(".ttbar") && filename.Contains("flat")) // fill ttbar
    {
      for (size_t k = 0; k < n_alpha; ++k) { // loop over alpha values
        if (filename.Contains(alpha_values[k])) {
          files_ttbar[k]=f;
        }
      }
    } // end if ttbar
    if (filename.Contains(".QCD")) // fill QCD
    {
      for (size_t k = 0; k < n_alpha; ++k) { // loop over alpha values
        if (filename.Contains(alpha_values[k])) {
          files_qcd[k]=f;
        }
      }
    } // end if QCD
  }

for (Int_t j = 0; j < njets; j++) {
  for (Int_t l = 0; l < nptmin; l++) {
    for (Int_t m = 0; m < nvariables; m++) {
      //initialise stack!
      TString hname_stack = TString::Format("hotvr_jets_%i_bin_%i_variable_%i.eps",j,l,m);
      stack[j][l][m] = new THStack(hname_stack,"");
      // loop over alpha values
      for (Int_t k = 0; k < n_alpha; k++) {
        //cout << files_ttbar[k]->GetName() << endl;
        hist_ttbar[k] = (TH1F*)files_ttbar[k]->Get("HOTVRJetsHists_"+jets[j]+ptmin[l]+ "/"+variables[m]);
        hist_ttbar[k]->Scale(1/hist_ttbar[k]->Integral());
        hist_ttbar[k]->SetLineColor(2+k);
        hist_ttbar[k]->SetLineWidth(2);
        //add to stack
        stack[j][l][m]->Add(hist_ttbar[k]);
      }

      stack[j][l][m]->Draw("");
      stack[j][l][m]->GetXaxis()->SetTitle(variablenames[m]);
      stack[j][l][m]->GetYaxis()->SetTitle("fraction of jets");
      stack[j][l][m]->GetXaxis()->SetLabelSize(0.04);
      stack[j][l][m]->GetXaxis()->SetTitleSize(0.06);
      stack[j][l][m]->GetYaxis()->SetLabelSize(0.04);
      stack[j][l][m]->GetYaxis()->SetTitleSize(0.06);
      stack[j][l][m]->GetXaxis()->SetTitleOffset(1.2);
      stack[j][l][m]->GetYaxis()->SetTitleOffset(1.2);

      Double_t ymax = hist_ttbar[0]->GetMaximum() > hist_ttbar[1]->GetMaximum() ? hist_ttbar[0]->GetMaximum() : hist_ttbar[1]->GetMaximum();
      Double_t ymin = 0;
      stack[j][l][m]->SetMinimum(ymin);
      stack[j][l][m]->SetMaximum(ymax*2);

      if(m==4){ // nsubjets
        stack[j][l][m]->GetXaxis()->SetRangeUser(0,10);
      }
      else if(m==2){ // mmin
        stack[j][l][m]->GetXaxis()->SetRangeUser(0,200);
        stack[j][l][m]->SetMinimum(0);
        stack[j][l][m]->SetMaximum(0.3);
      }
      else if(m>5){ // pt subjets
        stack[j][l][m]->GetXaxis()->SetRangeUser(0,250);
      }

      stack[j][l][m]->Draw("H nostack");
      gPad->Update();

      TLegend *leg = new TLegend(0.25,0.6,0.85,0.85);
      leg->SetTextSize(.03);
      //leg->SetHeader("QCD, "+jetnames[j]+ptbins[l]);
      leg->SetHeader("t#bar{t}, "+jetnames[j]+ptbins[l]);
      leg->AddEntry(hist_ttbar[0], "#alpha = 1, #rho = 600 GeV", "l");
      leg->AddEntry(hist_ttbar[1], "#alpha = 0.92, #rho = 180 GeV", "l");
      leg->AddEntry(hist_ttbar[2], "#alpha = 0.84, #rho = 190 GeV", "l");
      leg->AddEntry(hist_ttbar[3], "#alpha = 0.83, #rho = 200 GeV", "l");
      leg->AddEntry(hist_ttbar[4], "#alpha = 0.815, #rho = 210 GeV", "l");
      leg->Draw();

      TString outdir = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/plots/alphascan/SD_with_Reff/ttbar_all_jets/ttbar_";
      canvas->SaveAs(outdir + jets[j] + ptmin[l]+ "_"+variables[m] +".pdf");
      // TODO store results.root with root hists
    } // end loop over variables
  } // end loop over pt bins
} // end loop over jets (hotvr, matched, matched + tagged)

} // end void
