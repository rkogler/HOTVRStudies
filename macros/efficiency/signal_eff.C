#include "TSystem.h"
#include <vector>

#include <iostream>

#include "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/CMSSW_10_2_17/src/UHH2/HOTVRStudies/macros/include/CentralInclude.h"

vector<char*> get_filenames(const char* ext)
{
  const char* inDir = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/HISTS_alphascan";
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

void signal_eff()
{
  uint nptmin = 6;
  Double_t pt_xmiddle[5] = {300, 500, 700, 900, 1500};
  Double_t x_er[5] = {100, 100, 100, 100, 500};
  TString ptmin[nptmin];
  ptmin[0]="";
  ptmin[1]="_200";
  ptmin[2]="_400";
  ptmin[3]="_600";
  ptmin[4]="_800";
  ptmin[5]="_1000";

  vector<char*> filenames = get_filenames(".root");
  int n_alpha = 5;
  const char *alpha_values[5] = {"alpha1", "alpha092", "alpha084", "alpha083", "alpha0815"};

  TH1F* hists_tau_ttbar[5][nptmin];
  TH1F* hists_tau_qcd[5];
  TH1F* hists_tau_ttbar_matched[5][nptmin];
  TH1F* hists_tau_qcd_matched[5];
  TH1F* hists_tau_ttbar_tagged[5][nptmin];
  TH1F* hists_tau_qcd_tagged[5];

  gStyle->SetOptStat(0);
  SetStyle();

  TCanvas *canvas = new TCanvas("c", "c", 600, 600);
  gPad->SetLeftMargin(0.2);
  gPad->SetBottomMargin(0.2);

  Double_t x, y;
  Double_t y_sig[n_alpha][nptmin-1], y_bkg[n_alpha][nptmin-1];
  Double_t y_er[nptmin-1];

  Double_t y_mis[n_alpha][99];
  Double_t y_er_tau[99];
  Double_t x_er_tau[99];
  Double_t tau_middle[99];

  Int_t tau_bin[n_alpha];

  TMultiGraph *mg = new TMultiGraph();

  TGraphErrors* signal_eff[n_alpha];
  TH1F* tau_ttbar;
  TH1F* tau_qcd;
  TH1F* tau_ttbar_matched;
  TH1F* tau_qcd_matched;
  TH1F* tau_ttbar_tagged;
  TH1F* tau_qcd_tagged;

  // get the hists from root files
  for (int i = 0; i < filenames.size(); ++i) //loop over root files
  {
    TString filename = filenames.at(i);
    TFile *f = new TFile(filename);
    if (filename.Contains(".ttbar") && filename.Contains("flat")) // fill ttbar
    {
      for (size_t k = 0; k < n_alpha; ++k) { // loop over alpha values
        if (filename.Contains(alpha_values[k])) {
          for (size_t l = 0; l < nptmin; l++) {
            tau_ttbar = ((TH1F*)f->Get("HOTVRJetsHists_hotvr_jets"+ptmin[l]+ "/tau32")); // get the tau 32 distr. for matched_jets
            tau_ttbar_matched = ((TH1F*)f->Get("HOTVRJetsHists_matched_jets"+ptmin[l]+ "/tau32")); // get the tau 32 distr. for matched_jets
            tau_ttbar_tagged = ((TH1F*)f->Get("HOTVRJetsHists_tagged_jets"+ptmin[l]+ "/tau32")); // get the tau 32 distr.
            //tau_ttbar = ((TH1F*)f->Get("HOTVRJetsHists_hotvr_jets_mass"+ptmin[l]+ "/tau32")); // get the tau 32 distr.
            hists_tau_ttbar[k][l] = tau_ttbar;
            hists_tau_ttbar_matched[k][l] = tau_ttbar_matched;
            hists_tau_ttbar_tagged[k][l] = tau_ttbar_tagged;
          }
        }
      }
    } // end if ttbar
    if (filename.Contains(".QCD")) // fill QCD
    {
      for (size_t k = 0; k < n_alpha; ++k) { // loop over alpha values
        if (filename.Contains(alpha_values[k])) {
            tau_qcd = ((TH1F*)f->Get("HOTVRJetsHists_hotvr_jets/tau32")); // get the tau 32 distr.
            tau_qcd_matched = ((TH1F*)f->Get("HOTVRJetsHists_matched_jets/tau32")); // get the tau 32 distr.
            tau_qcd_tagged = ((TH1F*)f->Get("HOTVRJetsHists_tagged_jets/tau32")); // get the tau 32 distr.
            //tau_qcd = ((TH1F*)f->Get("HOTVRJetsHists_hotvr_jets_mass/tau32")); // get the tau 32 distr.
            hists_tau_qcd[k] = tau_qcd;
            hists_tau_qcd_matched[k] = tau_qcd_matched;
            hists_tau_qcd_tagged[k] = tau_qcd_tagged;
        }
      }
    } // end if QCD
  }

for (size_t k = 0; k < n_alpha; ++k) { // loop over alpha values
  //find the correct tau cut for epsilon_B = 5
  for (size_t bin = 0; bin < 100; bin++) {  // loop over tau cuts
    // get bin content for pt gen and pt top mismatched
    // b
    // double gen = hists_tau_qcd_matched[k]->Integral(); // total #QCD (inclusive integral)
    // double top_mismatched = hists_tau_qcd_matched[k]->Integral(0, bin); // mismatched with certain cut on tau distr.
    // d
    double gen = hists_tau_qcd_matched[k]->Integral(); // total #QCD (inclusive integral)
    double top_mismatched = hists_tau_qcd_tagged[k]->Integral(0, bin); // mismatched with certain cut on tau distr.

    double epsilon_B = top_mismatched / gen;
    tau_bin[k] = 56;

    if (epsilon_B >= 0.03) {
      tau_bin[k] = bin;
      cout << "mistag rate" << epsilon_B << endl;
      break;
    }
  }
  cout << " --------tau cut at bin: " << tau_bin[k] << endl;
  cout << " tau value is " << hists_tau_qcd_tagged[k]->GetBinCenter(tau_bin[k]) << endl;

  // draw final signal efficiency hist
  for (size_t l = 0; l < nptmin; l++) {
      // a matched / HOTVR (no tau cut; no fix mistag rate )
       double gentop = hists_tau_ttbar[k][l]->Integral();
       double top_matched = hists_tau_ttbar_matched[k][l]->Integral();
      // // b matched + tau / matched
      // double gentop = hists_tau_ttbar_matched[k][l]->Integral();
      // double top_matched = hists_tau_ttbar_matched[k][l]->Integral(0, tau_bin[k]);
      // // c matched + tagged / tagged (no tau cut, no fix mistag rate)
      // double gentop = hists_tau_ttbar_matched[k][l]->Integral();
      // double top_matched = hists_tau_ttbar_tagged[k][l]->Integral(0, 100);
      // // d matched + tagged + tau / matched
      //double gentop = hists_tau_ttbar_matched[k][l]->Integral();
      //double top_matched = hists_tau_ttbar_tagged[k][l]->Integral(0, tau_bin[k]);

      x = top_matched / gentop;

      cout << "top matched= " << top_matched << "  gentop = "<< gentop << endl;

      cout << "Signal efficiency " << x << endl;

      y_sig[k][l-1]=x;
      y_er[l-1]=0;
    }

    signal_eff[k] = new TGraphErrors(nptmin-1, pt_xmiddle, y_sig[k], x_er, y_er);// nbins, position of bin, y value, x error, y_error
    signal_eff[k]->SetMarkerStyle(20+k);
    signal_eff[k]->SetMarkerColor(2+k);
    mg->Add(signal_eff[k]);
  } // end loop over k values
  mg->Draw("APZ");

  mg->SetTitle("");
  mg->GetYaxis()->SetTitle("Signal efficiency");

  double ymax = signal_eff[0]->GetMaximum() > signal_eff[1]->GetMaximum() ? signal_eff[0]->GetMaximum() : signal_eff[1]->GetMaximum();
  double ymin = signal_eff[0]->GetMinimum() < signal_eff[1]->GetMinimum() ? signal_eff[0]->GetMinimum() : signal_eff[1]->GetMinimum();
  mg->SetMinimum(0.0);
  //mg->SetMaximum(0.6);

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
  //leg->SetHeader("HOTVR tagged/matched: #varepsilon_{B} = 4%");
  leg->SetHeader("HOTVR matched / HOTVR jets"); // a
  //leg->SetHeader("HOTVR matched+tau / matched #varepsilon_{B} = 5%"); // b
  //leg->SetHeader("HOTVR matched+tagged / matched"); // c
  //leg->SetHeader("HOTVR tagged+tau32 / matched #varepsilon_{B} = 1%"); // d

  leg->AddEntry(signal_eff[0], "#alpha = 1, #rho = 600 GeV", "lep");
  leg->AddEntry(signal_eff[1], "#alpha = 0.92, #rho = 180 GeV", "lep");
  leg->AddEntry(signal_eff[2], "#alpha = 0.84, #rho = 190 GeV", "lep");
  leg->AddEntry(signal_eff[3], "#alpha = 0.83, #rho = 200 GeV", "lep");
  leg->AddEntry(signal_eff[4], "#alpha = 0.815, #rho = 210 GeV", "lep");
  leg->Draw();

  TString outdir = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/plots/alphascan/SD_and_matching_with_Reff/eff_plots/";
  canvas->SaveAs(outdir + "signal_eff_matching.pdf"); // a
  //canvas->SaveAs(outdir + "signal_eff_tau_cut.pdf"); // b
  //canvas->SaveAs(outdir + "signal_eff_tagging_cuts.pdf"); // c
  //canvas->SaveAs(outdir + "signal_eff_inclusive_tagging_cuts.pdf"); // d


}
