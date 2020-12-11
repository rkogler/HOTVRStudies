#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"

#include <iostream>

#include "fastjet/PseudoJet.hh"
#include "fastjet/contrib/HOTVR.hh"

#include "TH1F.h"
#include "TH2F.h"

/**  Class for filling histograms for the NSubjettiness.
 *
 * NOTE: This class uses the 'hist' method to retrieve histograms.
 * This requires a string lookup and is therefore slow if you have
 * many histograms. Therefore, it is recommended to use histogram
 * pointers as member data instead, like in 'common/include/ElectronHists.h'.
 */
class NSubjettinessHists: public uhh2::Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
    NSubjettinessHists(uhh2::Context & ctx, const std::string & dirname);

    virtual void fill(const uhh2::Event & ev) override;

    virtual ~NSubjettinessHists();

 private:

    TH1F *hist_hotvr_jets_tau1, *hist_hotvr_jets_tau2, *hist_hotvr_jets_tau3, *hist_hotvr_jets_tau21, *hist_hotvr_jets_tau32; // Definition of hists for generel studies
    TH1F *hist_hotvr_jets_tagged_tau1, *hist_hotvr_jets_tagged_tau2, *hist_hotvr_jets_tagged_tau3, *hist_hotvr_jets_tagged_tau21, *hist_hotvr_jets_tagged_tau32;
    TH1F *hist_tagged_jets_tau32_00, *hist_tagged_jets_tau32_200,*hist_tagged_jets_tau32_400,*hist_tagged_jets_tau32_600,*hist_tagged_jets_tau32_800,*hist_tagged_jets_tau32_1000;
    TH1F *hist_tagged_jets_tau32_ptcut200;
    TH1F *hist_matched_jets_tau1, *hist_matched_jets_tau2, *hist_matched_jets_tau3, *hist_matched_jets_tau21, *hist_matched_jets_tau32;
    TH1F *hist_matched_jets_tau32_00, *hist_matched_jets_tau32_200,*hist_matched_jets_tau32_400,*hist_matched_jets_tau32_600,*hist_matched_jets_tau32_800,*hist_matched_jets_tau32_1000;
    TH1F *hist_matched_jets_tau32_ptcut200;

    TH1F *hist_matched_jets_tau2_00, *hist_matched_jets_tau2_200,*hist_matched_jets_tau2_400,*hist_matched_jets_tau2_600,*hist_matched_jets_tau2_800,*hist_matched_jets_tau2_1000;
    TH1F *hist_matched_jets_tau3_00, *hist_matched_jets_tau3_200,*hist_matched_jets_tau3_400,*hist_matched_jets_tau3_600,*hist_matched_jets_tau3_800,*hist_matched_jets_tau3_1000;
    TH1F *hist_matched_jets_mass_00, *hist_matched_jets_mass_200,*hist_matched_jets_mass_400,*hist_matched_jets_mass_600,*hist_matched_jets_mass_800,*hist_matched_jets_mass_1000;


 protected:

    uhh2::Event::Handle<std::vector<TopJet>> h_top_hotvr_jets;
    uhh2::Event::Handle<std::vector<TopJet>> h_HOTVRjets_tagged;
    uhh2::Event::Handle<std::vector<TopJet>> h_matched_jets;
    uhh2::Event::Handle<std::vector<std::pair<TopJet, TopJet>>> h_matched_pairs;
    // uhh2::Event::Handle<std::vector<std::pair<TopJet, TopJet>>> h_matched_pairs_notag;

};
