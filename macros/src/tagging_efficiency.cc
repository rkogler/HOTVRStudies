#include "TSystem.h"
#include <vector>

#include <iostream>
#include "../include/CentralInclude.h"

int main(){
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


  TH1F* hists_tau_ttbar[nptmin];
  TH1F* hists_tau_qcd;
  TH1F* hists_tau_ttbar_matched[nptmin];
  TH1F* hists_tau_qcd_matched;
  TH1F* hists_tau_ttbar_tagged[nptmin];
  TH1F* hists_tau_qcd_tagged;

  gStyle->SetOptStat(0);
  SetStyle();

  TCanvas *canvas = new TCanvas("c", "c", 600, 600);
  gPad->SetLeftMargin(0.2);
  gPad->SetBottomMargin(0.2);

  Double_t x, y;
  Double_t y_sig[nptmin-1], y_bkg[nptmin-1];
  Double_t y_er[nptmin-1];

  Double_t y_mis[99];
  Double_t y_er_tau[99];
  Double_t x_er_tau[99];
  Double_t tau_middle[99];

  Int_t tau_bin;

  TGraphErrors* signal_eff;
  TH1F* tau_ttbar;
  TH1F* tau_qcd;
  TH1F* tau_ttbar_matched;
  TH1F* tau_qcd_matched;
  TH1F* tau_ttbar_tagged;
  TH1F* tau_qcd_tagged;

  // get the hists from root files
    TString filename = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/paper_jet_collections/HOTVR_SD_adaptive_R/HISTS/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_nnpdf23.root";
    TString filename_QCD = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/paper_jet_collections/HOTVR_SD_adaptive_R/HISTS/uhh2.AnalysisModuleRunner.MC.QCD_flat_prod1.root";
    TFile *f = new TFile(filename);
    TFile *f_QCD = new TFile(filename_QCD);

          for (size_t l = 0; l < nptmin; l++) {
            tau_ttbar = ((TH1F*)f->Get("HOTVRJetsHists_hotvr_jets"+ptmin[l]+ "/tau32")); // get the tau 32 distr. for matched_jets
            tau_ttbar_matched = ((TH1F*)f->Get("HOTVRJetsHists_matched_jets"+ptmin[l]+ "/tau32")); // get the tau 32 distr. for matched_jets
            tau_ttbar_tagged = ((TH1F*)f->Get("HOTVRJetsHists_tagged_jets"+ptmin[l]+ "/tau32")); // get the tau 32 distr.
            //tau_ttbar = ((TH1F*)f->Get("HOTVRJetsHists_hotvr_jets_mass"+ptmin[l]+ "/tau32")); // get the tau 32 distr.
            hists_tau_ttbar[l] = tau_ttbar;
            hists_tau_ttbar_matched[l] = tau_ttbar_matched;
            hists_tau_ttbar_tagged[l] = tau_ttbar_tagged;

            tau_qcd = ((TH1F*)f->Get("HOTVRJetsHists_hotvr_jets/tau32")); // get the tau 32 distr.
            tau_qcd_matched = ((TH1F*)f->Get("HOTVRJetsHists_matched_jets/tau32")); // get the tau 32 distr.
            tau_qcd_tagged = ((TH1F*)f->Get("HOTVRJetsHists_tagged_jets/tau32")); // get the tau 32 distr.
            //tau_qcd = ((TH1F*)f->Get("HOTVRJetsHists_hotvr_jets_mass/tau32")); // get the tau 32 distr.
            hists_tau_qcd = tau_qcd;
            hists_tau_qcd_matched = tau_qcd_matched;
            hists_tau_qcd_tagged = tau_qcd_tagged;
          }

  //find the correct tau cut for epsilon_B = 5
  for (size_t bin = 0; bin < 100; bin++) {  // loop over tau cuts
    // get bin content for pt gen and pt top mismatched
    // b
    // double gen = hists_tau_qcd_matched[k]->Integral(); // total #QCD (inclusive integral)
    // double top_mismatched = hists_tau_qcd_matched[k]->Integral(0, bin); // mismatched with certain cut on tau distr.
    // d
    double gen = hists_tau_qcd_matched->Integral(); // total #QCD (inclusive integral)
    double top_mismatched = hists_tau_qcd_tagged->Integral(0, bin); // mismatched with certain cut on tau distr.

    double epsilon_B = top_mismatched / gen;
    tau_bin = 56;

    if (epsilon_B >= 0.03) {
      tau_bin = bin;
      cout << "mistag rate" << epsilon_B << endl;
      break;
    }
  }
  cout << " --------tau cut at bin: " << tau_bin << endl;
  cout << " tau value is " << hists_tau_qcd_tagged->GetBinCenter(tau_bin) << endl;

  // draw final signal efficiency hist
  for (size_t l = 0; l < nptmin; l++) {
      // a matched / HOTVR (no tau cut; no fix mistag rate )
       // double gentop = hists_tau_ttbar[l]->Integral();
       // double top_matched = hists_tau_ttbar_matched[l]->Integral();
      // // b matched + tau / matched
      // double gentop = hists_tau_ttbar_matched[k][l]->Integral();
      // double top_matched = hists_tau_ttbar_matched[k][l]->Integral(0, tau_bin[k]);
      // // c matched + tagged / tagged (no tau cut, no fix mistag rate)
      // double gentop = hists_tau_ttbar_matched[k][l]->Integral();
      // double top_matched = hists_tau_ttbar_tagged[k][l]->Integral(0, 100);
      // // d matched + tagged + tau / matched
      double gentop = hists_tau_ttbar_matched[l]->Integral();
      double top_matched = hists_tau_ttbar_tagged[l]->Integral(0, tau_bin);

      x = top_matched / gentop;

      cout << "top matched= " << top_matched << "  gentop = "<< gentop << endl;

      cout << "Signal efficiency " << x << endl;

      y_sig[l-1]=x;
      y_er[l-1]=0;
    }

    signal_eff = new TGraphErrors(nptmin-1, pt_xmiddle, y_sig, x_er, y_er);// nbins, position of bin, y value, x error, y_error
    signal_eff->SetMarkerStyle(20);
    signal_eff->SetMarkerColor(2);
  signal_eff->Draw("APZ");

  signal_eff->SetTitle("");
  signal_eff->GetYaxis()->SetTitle("Signal efficiency");

  double ymax = signal_eff->GetMaximum() ;
  double ymin = signal_eff->GetMinimum() ;
  signal_eff->SetMinimum(0.0);
  //signal_eff->SetMaximum(0.6);

  signal_eff->GetXaxis()->SetTitleOffset(1.5);
  signal_eff->GetYaxis()->SetTitleOffset(1.5);

  signal_eff->GetXaxis()->SetTitle("p_{T} [GeV]");
  signal_eff->GetXaxis()->SetLimits(200,2000);
  signal_eff->GetXaxis()->SetLabelSize(0.03);
  signal_eff->GetYaxis()->SetLabelSize(0.03);
  signal_eff->GetXaxis()->SetTitleSize(0.05);
  signal_eff->GetYaxis()->SetTitleSize(0.05);

  TLegend *leg = new TLegend(0.35,0.25,0.85,0.45);
  leg->SetTextSize(.03);
  //leg->SetHeader("HOTVR tagged/matched: #varepsilon_{B} = 4%");
  //leg->SetHeader("HOTVR matched / HOTVR jets"); // a
  //leg->SetHeader("HOTVR matched+tau / matched #varepsilon_{B} = 5%"); // b
  //leg->SetHeader("HOTVR matched+tagged / matched"); // c
  leg->SetHeader("HOTVR tagged+tau32 / matched #varepsilon_{B} = 3%"); // d

  leg->AddEntry(signal_eff, "HOTVR SD adaptive radius", "lep");
  leg->Draw();

  TString outdir = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/plots/paper_plots/";
  //canvas->SaveAs(outdir + "signal_eff_matching.pdf"); // a
  //canvas->SaveAs(outdir + "signal_eff_tau_cut.pdf"); // b
  //canvas->SaveAs(outdir + "signal_eff_tagging_cuts.pdf"); // c
  canvas->SaveAs(outdir + "signal_eff_inclusive_tagging_cuts.pdf"); // d

  return 0;
}
