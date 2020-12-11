#include "UHH2/HOTVRStudies/include/SoftClusterHists.h"

using namespace std;
using namespace uhh2;

SoftClusterHists::SoftClusterHists(Context & ctx, const string & dirname):
Hists(ctx, dirname)
{
// book all histograms here
// general hists
hist_pt = book<TH1F>("p_{T}", "p_{T} [GeV]", 200, 0, 1000);
hist_mass = book<TH1F>("mass", "mass [GeV]", 100, 0, 300);
hist_eta = book<TH1F>("eta", "#eta", 100, -6, 6);
hist_phi = book<TH1F>("phi", "#phi", 40, -4, 4);
hist_energy = book<TH1F>("energy", "energy [GeV]", 100, 0, 2200);

hist_rejected_subjets = book<TH1F>("rejected_subjets", "rejected_subjets", 30, -0.5, 29.5);
hist_rejected_jets = book<TH1F>("rejected_jets", "rejected_jets", 80, -0.5, 79.5);
}

void SoftClusterHists::fill(const Event & event){}

void SoftClusterHists::fill_rejected_subjets(const Event & ev, const Jet & subjet){
        hist_pt->Fill(subjet.pt());
        hist_mass->Fill(subjet.v4().M());
        hist_eta->Fill(subjet.eta());
        hist_phi->Fill(subjet.phi());
        hist_energy->Fill(subjet.v4().E());
}

void SoftClusterHists::fill_n_rejected_subjets(const Event & ev, const vector<Jet> & subjets){
    hist_rejected_subjets->Fill(subjets.size());
}

void SoftClusterHists::fill_cluster(const Event & ev, const TopJet & jet){
        hist_pt->Fill(jet.pt());
        hist_mass->Fill(jet.v4().M());
        hist_eta->Fill(jet.eta());
        hist_phi->Fill(jet.phi());
        hist_energy->Fill(jet.v4().E());
}

void SoftClusterHists::fill_n_cluster(const Event & ev, const vector<TopJet> & jets){
    hist_rejected_jets->Fill(jets.size());
}



SoftClusterHists::~SoftClusterHists(){}
