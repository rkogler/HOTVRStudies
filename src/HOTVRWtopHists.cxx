#include "UHH2/HOTVRStudies/include/HOTVRWtopHists.h"

using namespace std;
using namespace uhh2;

HOTVRWtopHists::HOTVRWtopHists(Context & ctx, const string & dirname, bool is_qcd):
Hists(ctx, dirname),
b_is_qcd(is_qcd)
{
// book all histograms here
// processed events
processed_events_ttbar = book<TH1F>("processed_jets_signal", "processed jets signal", 1,0,1);
processed_events_qcd = book<TH1F>("processed_jets_qcd", "processed jets qcd", 1,0,1);
// general hists
hist_pt = book<TH1F>("p_{T}", "p_{T} [GeV]", 200, 0, 2000);
hist_mass = book<TH1F>("mass", "mass [GeV]", 100, 0, 300);
hist_eta = book<TH1F>("eta", "#eta", 100, -6, 6);
hist_phi = book<TH1F>("phi", "#phi", 40, -4, 4);
hist_energy = book<TH1F>("energy", "energy [GeV]", 100, 0, 2200);
// HOTVR specific parameters
hist_distance = book<TH1F>("distance", "distance [GeV]", 100, 0, 2);
hist_mmin = book<TH1F>("mmin", "mmin [GeV]", 100, 0, 200);
hist_fpt1 = book<TH1F>("fpt", "fpt", 20, 0, 1);
hist_nsubjets = book<TH1F>("nsubjets", "nsubjets", 20, -0.5, 19.5);
// N-subjettiness
hist_tau1 = book<TH1F>("tau1", "tau1", 100, 0, 1);
hist_tau2 = book<TH1F>("tau2", "tau2", 100, 0, 1);
hist_tau3 = book<TH1F>("tau3", "tau3", 100, 0, 1);
hist_tau21 = book<TH1F>("tau21", "tau21", 100, 0, 1);
hist_tau32 = book<TH1F>("tau32", "tau32", 100, 0, 1);
hist_pt_ratio = book<TH1F>("pt_ratio", "p_{T} (W jet)/ p_{T} (top jet)", 100, 0, 2);

}

void HOTVRWtopHists::fill(const Event & event){}

void HOTVRWtopHists::fill_topjet(const Event & event, TopJet & jet, TopJet & parton_jet){
  if (b_is_qcd) {processed_events_qcd->Fill(0);}
  else{processed_events_ttbar->Fill(0);}

    hist_pt->Fill(jet.pt());
    hist_mass->Fill(jet.v4().M());
    hist_eta->Fill(jet.eta());
    hist_phi->Fill(jet.phi());
    hist_energy->Fill(jet.v4().E());

    hist_mmin->Fill(jet.hotvr_mmin());
    hist_fpt1->Fill(jet.hotvr_fpt1());
    hist_nsubjets->Fill(jet.subjets().size());

    hist_tau1->Fill(jet.tau1_groomed());
    hist_tau2->Fill(jet.tau2_groomed());
    hist_tau3->Fill(jet.tau3_groomed());
    hist_tau21->Fill(jet.tau2_groomed()/jet.tau1_groomed());
    hist_tau32->Fill(jet.tau3_groomed()/jet.tau2_groomed());

    hist_distance->Fill(deltaR(parton_jet, jet));
    hist_pt_ratio->Fill(jet.pt()/parton_jet.pt());
}


HOTVRWtopHists::~HOTVRWtopHists(){}
