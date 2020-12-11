#include "UHH2/HOTVRStudies/include/TopTagPerformanceHists.h"

#include "TH1F.h"
#include "TH2F.h"

using namespace std;
using namespace uhh2;


TopTagPerformanceHists::TopTagPerformanceHists(Context & ctx, const string & dirname, bool is_qcd, TopJetId id , Event::Handle<std::vector<pair<TopJet, TopJet> > > &topjetcollection):
  Hists(ctx, dirname),
  b_is_qcd(is_qcd),
  m_id(id),
  h_matched_pairs(topjetcollection)
{
  double pt_intervall[] = {0, 200, 400, 600, 1000, 2000};

  pt_top = book<TH1F>("pt_gentop", "p_{T, topjet}", 5, pt_intervall);
  pt_matched = book<TH1F>("pt_top_matched", "p_{T, topjet}", 5, pt_intervall);
  pt_mismatched = book<TH1F>("pt_top_mismatched", "p_{T, topjet}", 5, pt_intervall);
  pt_gen = book<TH1F>("pt_gen", "p_{T, gen}", 5, pt_intervall);

}

void TopTagPerformanceHists::fill(const Event & event){

  double weight = event.weight;
  //specific handle to get the matched jets
  const vector<pair<TopJet, TopJet>> topjets = event.get(h_matched_pairs);
  // const vector<TopJet> partons = event.get(h_partons);

  if (b_is_qcd)
  {
		//mismatched jets
		for(auto matched : topjets)
		{
      TopJet topjet = matched.first;
      TopJet gen = matched.second;
      pt_gen->Fill(gen.pt(), weight); // fill one hist before matching
      double pt = -1;
			if(m_id(topjet, event)) pt = gen.pt(); // take the pt of the corresponding parton jet if a match is found
      if (pt < 0) continue; // no match found
			if (pt < 2000) pt_mismatched->Fill(pt, weight);
		  else           pt_mismatched->Fill(1999., weight);
		}
  }
  else
    {
			//matched jets
      for(auto matched : topjets)
  		{
        TopJet topjet = matched.first;
        TopJet gen = matched.second;
        pt_top->Fill(gen.pt(), weight); // fill one hist before matching
        double pt = -1;
  			if(m_id(topjet, event)) pt = gen.pt(); // take the pt of the corresponding parton jet if a match is found
        if (pt < 0) continue; // no match found
  			if (pt < 2000) pt_matched->Fill(pt, weight);
  		  else           pt_matched->Fill(1999., weight);
  		}
    }
  }

TopTagPerformanceHists::~TopTagPerformanceHists() {}
