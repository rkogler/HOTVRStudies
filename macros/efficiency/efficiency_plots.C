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

void efficiency_plots()
{
  Int_t n_ptbins = 12;
  Double_t pt_xbins[13] = {0, 200, 400, 500, 600, 700, 800, 1000, 1200, 1400, 1600, 1800, 2000};
  Double_t pt_xmiddle[11] = {300, 450, 550, 650, 750, 900, 1100, 1300, 1500, 1700, 1900};

  vector<char*> filenames = get_filenames(".root");
  int n_alpha = 5;
  const char *alpha_values[5] = {"alpha1", "alpha092", "alpha084", "alpha083", "alpha0815"};

  TH1F* hists_a_ttbar[5];
  TH1F* hists_a_qcd[5];
  TH1F* hists_b_ttbar[5];
  TH1F* hists_b_qcd[5];

  gStyle->SetOptStat(0);
  SetStyle();

  TCanvas *canvas = new TCanvas("c", "c", 600, 600);
  gPad->SetLeftMargin(0.2);
  gPad->SetBottomMargin(0.2);

  Double_t x, y;
  Double_t y_sig[n_alpha][n_ptbins-1], y_bkg[n_alpha][n_ptbins-1];
  Double_t y_er[n_ptbins-1];
  Double_t x_er[11] = {100, 50, 50, 50, 50, 100, 100, 100, 100, 100, 100};

  TMultiGraph *mg = new TMultiGraph();

  TGraphErrors* signal_eff[n_alpha];
  TGraphErrors* bkg_eff[n_alpha];

  for (int i = 0; i < filenames.size(); ++i) //loop over root files
  {
    TString filename = filenames.at(i);
    TFile *f = new TFile(filename);
    if (filename.Contains(".ttbar") && filename.Contains("flat")) // fill ttbar
    {
      for (size_t k = 0; k < n_alpha; ++k) { // loop over alpha values
        if (filename.Contains(alpha_values[k])) {
          TH1F* a_ttbar_hotvr = new TH1F("A_ttbar_HOTVR", "P_{T}", n_ptbins, pt_xbins);
          TH1F* b_ttbar_hotvr = new TH1F("B_ttbar_HOTVR", "P_{T}", n_ptbins, pt_xbins);

          a_ttbar_hotvr->Add((TH1F*)f->Get("HOTVR_Eff/pt_gentop"));
          b_ttbar_hotvr->Add((TH1F*)f->Get("HOTVR_Eff/pt_top_matched"));
          hists_a_ttbar[k] = a_ttbar_hotvr;
          hists_b_ttbar[k] = b_ttbar_hotvr;
        }
      }
    } // end if ttbar
    if (filename.Contains(".QCD")) // fill QCD
    {
      for (size_t k = 0; k < n_alpha; ++k) { // loop over alpha values
        if (filename.Contains(alpha_values[k])) {
          TH1F* a_QCD_hotvr = new TH1F("A_QCD_HOTVR", "P_{T}", n_ptbins, pt_xbins);
          TH1F* b_QCD_hotvr = new TH1F("B_QCD_HOTVR", "P_{T}", n_ptbins, pt_xbins);

          a_QCD_hotvr->Add((TH1F*)f->Get("HOTVR_Eff/pt_gen"));
          b_QCD_hotvr->Add((TH1F*)f->Get("HOTVR_Eff/pt_top_mismatched"));
          hists_a_qcd[k] = a_QCD_hotvr;
          hists_b_qcd[k] = b_QCD_hotvr;
        }
      }
    } // end if QCD
  }

  for (size_t k = 0; k < n_alpha; ++k) { // loop over alpha values
    for (int i = 1; i < n_ptbins; ++i)
    {
      x = hists_b_ttbar[k]->GetBinContent(i) / hists_a_ttbar[k]->GetBinContent(i);
      y = hists_b_qcd[k]->GetBinContent(i) / hists_a_qcd[k]->GetBinContent(i);
      y_sig[k][i-1]=x;
      y_bkg[k][i-1]=y;
      y_er[i-1]=0;
    }

    signal_eff[k] = new TGraphErrors(n_ptbins-1, pt_xmiddle, y_sig[k], x_er, y_er);
    bkg_eff[k] = new TGraphErrors(n_ptbins-1, pt_xmiddle, y_bkg[k], x_er, y_er);
    signal_eff[k]->SetMarkerStyle(20+k);
    bkg_eff[k]->SetMarkerStyle(20+k);
    signal_eff[k]->SetMarkerColor(2+k);
    bkg_eff[k]->SetMarkerColor(2+k);
    //mg->Add(signal_eff[k]);
    mg->Add(bkg_eff[k]);
  }
  mg->Draw("APZ");

  mg->SetTitle("");
  mg->GetYaxis()->SetTitle("Mistag rate");
  mg->GetYaxis()->SetLimits(0,0.2);
  // mg->GetYaxis()->SetTitle("Signal efficiency");
  // mg->GetYaxis()->SetLimits(0,0.6);

  mg->GetXaxis()->SetTitleOffset(1.5);
  mg->GetYaxis()->SetTitleOffset(1.5);

  mg->GetXaxis()->SetTitle("p_{T} [GeV]");
  mg->GetXaxis()->SetLimits(200,2000);
  mg->GetXaxis()->SetLabelSize(0.03);
  mg->GetYaxis()->SetLabelSize(0.03);
  mg->GetXaxis()->SetTitleSize(0.05);
  mg->GetYaxis()->SetTitleSize(0.05);

  TLegend *leg = new TLegend(0.45,0.25,0.85,0.45);
  leg->SetTextSize(.03);
  leg->SetHeader("HOTVR TopTagger: #tau_{3/2}<0.47");
  leg->AddEntry(bkg_eff[0], "#alpha = 1, #rho = 600 GeV", "lep");
  leg->AddEntry(bkg_eff[1], "#alpha = 0.92, #rho = 180 GeV", "lep");
  leg->AddEntry(bkg_eff[2], "#alpha = 0.84, #rho = 190 GeV", "lep");
  leg->AddEntry(bkg_eff[3], "#alpha = 0.83, #rho = 200 GeV", "lep");
  leg->AddEntry(bkg_eff[4], "#alpha = 0.815, #rho = 210 GeV", "lep");
  leg->Draw();

  TString outdir = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/plots/alphascan/2106/eff_plots/";
  canvas->SaveAs(outdir + "bkg_eff.eps");

}
