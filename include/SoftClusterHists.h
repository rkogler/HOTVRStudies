#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"

#include <iostream>

#include "TH1F.h"
#include "TH2F.h"

/**  Class to fill general hists for the rejected subjets.
 *
 * NOTE: This class uses the 'hist' method to retrieve histograms.
 * This requires a string lookup and is therefore slow if you have
 * many histograms. Therefore, it is recommended to use histogram
 * pointers as member data instead, like in 'common/include/ElectronHists.h'.
 */
class SoftClusterHists: public uhh2::Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
    SoftClusterHists(uhh2::Context & ctx, const std::string & dirname);
    virtual void fill(const uhh2::Event & ev) override;
    virtual void fill_rejected_subjets(const uhh2::Event & ev, const Jet & subjet);
    virtual void fill_cluster(const uhh2::Event & ev, const TopJet & jet);
    virtual void fill_n_rejected_subjets(const uhh2::Event & ev, const std::vector<Jet> & subjets);
    virtual void fill_n_cluster(const uhh2::Event & ev, const std::vector<TopJet> & jets);

    virtual ~SoftClusterHists();

 private:
    TH1F *hist_pt, *hist_mass,  *hist_eta, *hist_phi, *hist_energy; // Definition of hists for generel studies
    TH1F *hist_rejected_subjets; // number of rejected subjets
    TH1F *hist_rejected_jets; // number of rejected jets
};
