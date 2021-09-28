#pragma once

#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/TopJet.h"

#include "UHH2/common/include/TopJetIds.h"

#include <vector>

/**  Class to fill histograms for the top tag performance. The NSubjettiness is scanned and the
* pt_matched (pt_missmatched) hists are filled for the ttbar (QCD) sample. The pt refers to the
* matching parton jet.
*
*/
class EfficiencyHists: public uhh2::Hists {
public:

  EfficiencyHists(uhh2::Context & ctx, const std::string & dirname, bool is_qcd, TopJetId id, uhh2::Event::Handle<std::vector<std::pair<TopJet, TopJet>> >  &topjetcollection);

  virtual void fill(const uhh2::Event & event) override;
  virtual ~EfficiencyHists();

protected:

  TH1F *N_evt, *N_mat;
  TH1F *pt_top, *pt_matched, *pt_mismatched, *pt_gen;
  bool b_is_qcd;
  TopJetId m_id;
  uhh2::Event::Handle<std::vector<std::pair<TopJet, TopJet> > > h_matched_pairs;

};
