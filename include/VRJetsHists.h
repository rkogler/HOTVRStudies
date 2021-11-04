#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"
#include "fastjet/PseudoJet.hh"

#include "fastjet/contrib/HOTVR.hh"
#include "fastjet/contrib/HOTVRinfo.hh"
#include "fastjet/contrib/Nsubjettiness.hh"

#include <iostream>

#include "TH1F.h"
#include "TH2F.h"

/**  Class to fill general hists for the HOTVR Studies e.g. mass or pt of the pseudojets.
 *
 * NOTE: This class uses the 'hist' method to retrieve histograms.
 * This requires a string lookup and is therefore slow if you have
 * many histograms. Therefore, it is recommended to use histogram
 * pointers as member data instead, like in 'common/include/ElectronHists.h'.
 */
class VRJetsHists: public uhh2::Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
    VRJetsHists(uhh2::Context & ctx, const std::string & dirname, bool is_qcd);
    virtual void fill(const uhh2::Event & ev) override;
    virtual void fill_pseudojet(const fastjet::PseudoJet & jet);
    virtual void fill_pseudojet_constituents(const std::vector<fastjet::PseudoJet> & jets);

    virtual ~VRJetsHists();

 private:
    bool b_is_qcd;
    TH1F *processed_events_ttbar, *processed_events_qcd;

    TH1F *hist_pt, *hist_mass,  *hist_eta, *hist_phi, *hist_energy; // Definition of hists for generel studies
    TH1F *hist_nconstituents;
    TH1F *hist_mass_constituents;
    TH1F *hist_mass_sum_constituents;
    TH1F *hist_tau1, *hist_tau2, *hist_tau3, *hist_tau21, *hist_tau32;
};
