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

void mistag_rate()
{
  vector<char*> filenames = get_filenames(".root");
  int n_alpha = 5;
  const char *alpha_values[5] = {"alpha1", "alpha092", "alpha084", "alpha083", "alpha0815"};

  TH1F* hists_tau_qcd[5];

  gStyle->SetOptStat(0);
  SetStyle();

  TCanvas *canvas = new TCanvas("c", "c", 600, 600);
  gPad->SetLeftMargin(0.2);
  gPad->SetBottomMargin(0.2);

  Double_t y_mis[n_alpha][99];
  Double_t y_er[99];
  Double_t x_er[99];
  Double_t tau_middle[99];

  TMultiGraph *mg = new TMultiGraph();

  TGraphErrors* mistag_rate[n_alpha];
  TH1F* tau_qcd;

  // get the hists from root files
  for (int i = 0; i < filenames.size(); ++i) //loop over root files
  {
    TString filename = filenames.at(i);
    TFile *f = new TFile(filename);
    if (filename.Contains(".QCD")) // fill QCD
    {
      for (size_t k = 0; k < n_alpha; ++k) { // loop over alpha values
        if (filename.Contains(alpha_values[k])) {
            //tau_qcd = ((TH1F*)f->Get("HOTVRJetsHists_tagged_jets/tau32")); // get the tau 32 distr.
            tau_qcd = ((TH1F*)f->Get("HOTVRJetsHists_hotvr_jets_mass/tau32")); // get the tau 32 distr.
            hists_tau_qcd[k] = tau_qcd;
        }
      }
    } // end if QCD
  }

for (size_t k = 0; k < n_alpha; ++k) { // loop over alpha values
  //find the correct tau cut for epsilon_B = 5
  for (Int_t bin = 0; bin < 100; bin++) {  // loop over tau cuts
    // get bin content for pt gen and pt top mismatched
    double gen = hists_tau_qcd[k]->Integral(); // total #QCD (inclusive integral)
    double top_mismatched = hists_tau_qcd[k]->Integral(0, bin); // mismatched with certain cut on tau distr.
    double epsilon_B = top_mismatched / gen;

    y_mis[k][bin]=epsilon_B;
    y_er[bin]=0;
    x_er[bin]=0.005;
    tau_middle[bin]=((double)bin/(double)100)+0.005;
  }

  // draw final signal efficiency hist
    mistag_rate[k] = new TGraphErrors(100, tau_middle, y_mis[k], x_er, y_er);// nbins, position of bin, y value, x error, y_error
    mistag_rate[k]->SetMarkerStyle(20+k);
    mistag_rate[k]->SetMarkerColor(2+k);

    mg->Add(mistag_rate[k]);
  } // end loop over k values

  mg->Draw("APZ");

  mg->SetTitle("");
  mg->GetYaxis()->SetTitle("mistag rate");
  //mg->GetYaxis()->SetLimits(0,0.01);
  mg->SetMinimum(0.0);
  //mg->SetMaximum(0.12);
  mg->GetXaxis()->SetTitleOffset(1.5);
  mg->GetYaxis()->SetTitleOffset(1.5);

  mg->GetXaxis()->SetTitle("#tau_{32}");
  //mg->GetXaxis()->SetLimits(0.4,0.5);
  mg->GetXaxis()->SetLabelSize(0.03);
  mg->GetYaxis()->SetLabelSize(0.03);
  mg->GetXaxis()->SetTitleSize(0.05);
  mg->GetYaxis()->SetTitleSize(0.05);

  //canvas->SetLogy();

  TLegend *leg = new TLegend(0.25,0.65,0.65,0.85);
  leg->SetTextSize(.03);
  leg->SetHeader("HOTVR Mass cut ");
  leg->AddEntry(mistag_rate[0], "#alpha = 1, #rho = 600 GeV", "lep");
  leg->AddEntry(mistag_rate[1], "#alpha = 0.92, #rho = 180 GeV", "lep");
  leg->AddEntry(mistag_rate[2], "#alpha = 0.84, #rho = 190 GeV", "lep");
  leg->AddEntry(mistag_rate[3], "#alpha = 0.83, #rho = 200 GeV", "lep");
  leg->AddEntry(mistag_rate[4], "#alpha = 0.815, #rho = 210 GeV", "lep");
  leg->Draw();

  TString outdir = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/plots/alphascan/eff_plots/";
  canvas->SaveAs(outdir + "mistag_rate_tau32_mass.eps");

}
