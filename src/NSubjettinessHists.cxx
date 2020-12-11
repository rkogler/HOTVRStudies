#include "UHH2/HOTVRStudies/include/NSubjettinessHists.h"

using namespace std;
using namespace uhh2;
using namespace fastjet;
using namespace contrib;

NSubjettinessHists::NSubjettinessHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
  // book all histograms here
hist_hotvr_jets_tau1 = book<TH1F>("tau1_hotvr_jets", "HOTVR jets tau1", 100, 0, 1);
hist_hotvr_jets_tau2 = book<TH1F>("tau2_hotvr_jets", "HOTVR jets tau2", 100, 0, 1);
hist_hotvr_jets_tau3 = book<TH1F>("tau3_hotvr_jets", "HOTVR jets tau3", 100, 0, 1);
hist_hotvr_jets_tau21 = book<TH1F>("tau21_hotvr_jets", "HOTVR jets tau21", 100, 0, 1);
hist_hotvr_jets_tau32 = book<TH1F>("tau32_hotvr_jets", "HOTVR jets tau32", 100, 0, 1);

hist_hotvr_jets_tagged_tau1 = book<TH1F>("tau1_tagged_jets", "HOTVR jets_tagged tau1", 100, 0, 1);
hist_hotvr_jets_tagged_tau2 = book<TH1F>("tau2_tagged_jets", "HOTVR jets_tagged tau2", 100, 0, 1);
hist_hotvr_jets_tagged_tau3 = book<TH1F>("tau3_tagged_jets", "HOTVR jets_tagged tau3", 100, 0, 1);
hist_hotvr_jets_tagged_tau21 = book<TH1F>("tau21_tagged_jets", "HOTVR jets_tagged tau21", 100, 0, 1);
hist_hotvr_jets_tagged_tau32 = book<TH1F>("tau32_tagged_jets", "HOTVR jets_tagged tau32", 100, 0, 1);

hist_tagged_jets_tau32_00 = book<TH1F>("tau32_tagged_jets_00", "tagged jets tau32_00", 100, 0, 1);
hist_tagged_jets_tau32_200 = book<TH1F>("tau32_tagged_jets_200", "tagged jets tau32_200", 100, 0, 1);
hist_tagged_jets_tau32_400 = book<TH1F>("tau32_tagged_jets_400", "tagged jets tau32_400", 100, 0, 1);
hist_tagged_jets_tau32_600 = book<TH1F>("tau32_tagged_jets_600", "tagged jets tau32_600", 100, 0, 1);
hist_tagged_jets_tau32_800 = book<TH1F>("tau32_tagged_jets_800", "tagged jets tau32_800", 100, 0, 1);
hist_tagged_jets_tau32_1000 = book<TH1F>("tau32_tagged_jets_1000", "tagged jets tau32_1000", 100, 0, 1);
hist_tagged_jets_tau32_ptcut200 = book<TH1F>("tau32_tagged_jets_ptcut200", "tagged jets tau32_ptcut200", 100, 0, 1);


hist_matched_jets_tau1 = book<TH1F>("tau1_matched_jets", "matched jets tau1", 100, 0, 1);
hist_matched_jets_tau2 = book<TH1F>("tau2_matched_jets", "matched jets tau2", 100, 0, 1);
hist_matched_jets_tau3 = book<TH1F>("tau3_matched_jets", "matched jets tau3", 100, 0, 1);
hist_matched_jets_tau21 = book<TH1F>("tau21_matched_jets", "matched jets tau21", 100, 0, 1);
hist_matched_jets_tau32 = book<TH1F>("tau32_matched_jets", "matched jets tau32", 100, 0, 1);

hist_matched_jets_tau32_00 = book<TH1F>("tau32_matched_jets_00", "matched jets tau32_00", 100, 0, 1);
hist_matched_jets_tau32_200 = book<TH1F>("tau32_matched_jets_200", "matched jets tau32_200", 100, 0, 1);
hist_matched_jets_tau32_400 = book<TH1F>("tau32_matched_jets_400", "matched jets tau32_400", 100, 0, 1);
hist_matched_jets_tau32_600 = book<TH1F>("tau32_matched_jets_600", "matched jets tau32_600", 100, 0, 1);
hist_matched_jets_tau32_800 = book<TH1F>("tau32_matched_jets_800", "matched jets tau32_800", 100, 0, 1);
hist_matched_jets_tau32_1000 = book<TH1F>("tau32_matched_jets_1000", "matched jets tau32_1000", 100, 0, 1);
hist_matched_jets_tau32_ptcut200 = book<TH1F>("tau32_matched_jets_ptcut200", "matched jets tau32_ptcut200", 100, 0, 1);

hist_matched_jets_tau2_00 = book<TH1F>("tau2_matched_jets_00", "matched jets tau2_00", 100, 0, 1);
hist_matched_jets_tau2_200 = book<TH1F>("tau2_matched_jets_200", "matched jets tau2_200", 100, 0, 1);
hist_matched_jets_tau2_400 = book<TH1F>("tau2_matched_jets_400", "matched jets tau2_400", 100, 0, 1);
hist_matched_jets_tau2_600 = book<TH1F>("tau2_matched_jets_600", "matched jets tau2_600", 100, 0, 1);
hist_matched_jets_tau2_800 = book<TH1F>("tau2_matched_jets_800", "matched jets tau2_800", 100, 0, 1);
hist_matched_jets_tau2_1000 = book<TH1F>("tau2_matched_jets_1000", "matched jets tau2_1000", 100, 0, 1);

hist_matched_jets_tau3_00 = book<TH1F>("tau3_matched_jets_00", "matched jets tau3_00", 100, 0, 1);
hist_matched_jets_tau3_200 = book<TH1F>("tau3_matched_jets_200", "matched jets tau3_200", 100, 0, 1);
hist_matched_jets_tau3_400 = book<TH1F>("tau3_matched_jets_400", "matched jets tau3_400", 100, 0, 1);
hist_matched_jets_tau3_600 = book<TH1F>("tau3_matched_jets_600", "matched jets tau3_600", 100, 0, 1);
hist_matched_jets_tau3_800 = book<TH1F>("tau3_matched_jets_800", "matched jets tau3_800", 100, 0, 1);
hist_matched_jets_tau3_1000 = book<TH1F>("tau3_matched_jets_1000", "matched jets tau3_1000", 100, 0, 1);

hist_matched_jets_mass_00 = book<TH1F>("mass_matched_jets_00", "matched jets mass_00", 100, 0, 300);
hist_matched_jets_mass_200 = book<TH1F>("mass_matched_jets_200", "matched jets mass_200", 100, 0, 300);
hist_matched_jets_mass_400 = book<TH1F>("mass_matched_jets_400", "matched jets mass_400", 100, 0, 300);
hist_matched_jets_mass_600 = book<TH1F>("mass_matched_jets_600", "matched jets mass_600", 100, 0, 300);
hist_matched_jets_mass_800 = book<TH1F>("mass_matched_jets_800", "matched jets mass_800", 100, 0, 300);
hist_matched_jets_mass_1000 = book<TH1F>("mass_matched_jets_1000", "matched jets mass_1000", 100, 0, 300);


// hist_matched_jets_notag_tau1 = book<TH1F>("tau1_matched_jets_notag", "matched jets notag tau1", 100, 0, 1);
// hist_matched_jets_notag_tau2 = book<TH1F>("tau2_matched_jets_notag", "matched jets notag tau2", 100, 0, 1);
// hist_matched_jets_notag_tau3 = book<TH1F>("tau3_matched_jets_notag", "matched jets notag tau3", 100, 0, 1);
// hist_matched_jets_notag_tau21 = book<TH1F>("tau21_matched_jets_notag", "matched jets notag tau21", 100, 0, 1);
// hist_matched_jets_notag_tau32 = book<TH1F>("tau32_matched_jets_notag", "matched jets notag tau32", 100, 0, 1);

  // initialise handle
  h_top_hotvr_jets = ctx.get_handle<vector<TopJet>>("top_hotvr_jets");
  h_HOTVRjets_tagged = ctx.get_handle<vector<TopJet>>("HOTVRjets_tagged");
  h_matched_jets = ctx.get_handle<vector<TopJet>>("matched_jets");
//  h_matched_pairs = ctx.get_handle<vector<pair<TopJet, TopJet>>>("matched_pairs");
  // h_matched_pairs_notag = ctx.get_handle<vector<pair<TopJet, TopJet>>>("matched_pairs_notag");

}

void NSubjettinessHists::fill(const Event & event){
  // only for check: Tau of the TOP HOTVR jets (no top tag or matching)
  const auto hotvr_jets = event.get(h_top_hotvr_jets);
  for (uint i = 0; i < hotvr_jets.size(); i++) {
    hist_hotvr_jets_tau1->Fill(hotvr_jets[i].tau1_groomed());
    hist_hotvr_jets_tau2->Fill(hotvr_jets[i].tau2_groomed());
    hist_hotvr_jets_tau3->Fill(hotvr_jets[i].tau3_groomed());
    hist_hotvr_jets_tau21->Fill(hotvr_jets[i].tau2_groomed()/hotvr_jets[i].tau1_groomed());
    hist_hotvr_jets_tau32->Fill(hotvr_jets[i].tau3_groomed()/hotvr_jets[i].tau2_groomed());
  }

  // only for check: Tau of the TOP HOTVR jets (top tag)
  const auto hotvr_jets_tagged = event.get(h_HOTVRjets_tagged);
  for (uint i = 0; i < hotvr_jets_tagged.size(); i++) {
    hist_hotvr_jets_tagged_tau1->Fill(hotvr_jets_tagged[i].tau1_groomed());
    hist_hotvr_jets_tagged_tau2->Fill(hotvr_jets_tagged[i].tau2_groomed());
    hist_hotvr_jets_tagged_tau3->Fill(hotvr_jets_tagged[i].tau3_groomed());
    hist_hotvr_jets_tagged_tau21->Fill(hotvr_jets_tagged[i].tau2_groomed()/hotvr_jets_tagged[i].tau1_groomed());
    hist_hotvr_jets_tagged_tau32->Fill(hotvr_jets_tagged[i].tau3_groomed()/hotvr_jets_tagged[i].tau2_groomed());

  double pt = hotvr_jets_tagged[i].pt();
        if(pt < 200){
          hist_tagged_jets_tau32_00->Fill(hotvr_jets_tagged[i].tau3_groomed()/hotvr_jets_tagged[i].tau2_groomed());
        }
        else if(200 <= pt && pt < 400){
          hist_tagged_jets_tau32_200->Fill(hotvr_jets_tagged[i].tau3_groomed()/hotvr_jets_tagged[i].tau2_groomed());
        }
        else if(400 <= pt && pt < 600){
          hist_tagged_jets_tau32_400->Fill(hotvr_jets_tagged[i].tau3_groomed()/hotvr_jets_tagged[i].tau2_groomed());
        }
        else if(600 <= pt && pt < 800){
          hist_tagged_jets_tau32_600->Fill(hotvr_jets_tagged[i].tau3_groomed()/hotvr_jets_tagged[i].tau2_groomed());
        }
        else if(800 <= pt && pt < 1000){
          hist_tagged_jets_tau32_800->Fill(hotvr_jets_tagged[i].tau3_groomed()/hotvr_jets_tagged[i].tau2_groomed());
        }
        else if (1000 <= pt && pt < 1200){
          hist_tagged_jets_tau32_1000->Fill(hotvr_jets_tagged[i].tau3_groomed()/hotvr_jets_tagged[i].tau2_groomed());
        }
        if(200 <= pt){
          hist_tagged_jets_tau32_ptcut200->Fill(hotvr_jets_tagged[i].tau3_groomed()/hotvr_jets_tagged[i].tau2_groomed());
        }
}

  // values for the ROC curves
  const auto &matched_jets = event.get(h_matched_jets);

  for(unsigned int i=0; i<matched_jets.size(); ++i){
    const auto &matched_jet = matched_jets[i];
  // tau of the toptagged and matched hotvr jets

    hist_matched_jets_tau1->Fill(matched_jet.tau1_groomed());
    hist_matched_jets_tau2->Fill(matched_jet.tau2_groomed());
    hist_matched_jets_tau3->Fill(matched_jet.tau3_groomed());
    hist_matched_jets_tau21->Fill(matched_jet.tau2_groomed()/matched_jet.tau1_groomed());
    hist_matched_jets_tau32->Fill(matched_jet.tau3_groomed()/matched_jet.tau2_groomed());

double pt = matched_jet.pt();
    if(pt < 200){
      hist_matched_jets_tau32_00->Fill(matched_jet.tau3_groomed()/matched_jet.tau2_groomed());
      hist_matched_jets_tau2_00->Fill(matched_jet.tau2_groomed());
      hist_matched_jets_tau3_00->Fill(matched_jet.tau3_groomed());
      hist_matched_jets_mass_00->Fill(matched_jet.v4().M());
}
    else if(200 <= pt && pt < 400){
      hist_matched_jets_tau32_200->Fill(matched_jet.tau3_groomed()/matched_jet.tau2_groomed());
      hist_matched_jets_tau2_200->Fill(matched_jet.tau2_groomed());
      hist_matched_jets_tau3_200->Fill(matched_jet.tau3_groomed());
      hist_matched_jets_mass_200->Fill(matched_jet.v4().M());
}
    else if(400 <= pt && pt < 600){
      hist_matched_jets_tau32_400->Fill(matched_jet.tau3_groomed()/matched_jet.tau2_groomed());
      hist_matched_jets_tau2_400->Fill(matched_jet.tau2_groomed());
      hist_matched_jets_tau3_400->Fill(matched_jet.tau3_groomed());
      hist_matched_jets_mass_400->Fill(matched_jet.v4().M());
}
    else if(600 <= pt && pt < 800){
      hist_matched_jets_tau32_600->Fill(matched_jet.tau3_groomed()/matched_jet.tau2_groomed());
      hist_matched_jets_tau2_600->Fill(matched_jet.tau2_groomed());
      hist_matched_jets_tau3_600->Fill(matched_jet.tau3_groomed());
      hist_matched_jets_mass_800->Fill(matched_jet.v4().M());
}
    else if(800 <= pt && pt < 1000){
      hist_matched_jets_tau32_800->Fill(matched_jet.tau3_groomed()/matched_jet.tau2_groomed());
      hist_matched_jets_tau2_800->Fill(matched_jet.tau2_groomed());
      hist_matched_jets_tau3_800->Fill(matched_jet.tau3_groomed());
      hist_matched_jets_mass_800->Fill(matched_jet.v4().M());
}
    else if(1000 <= pt && pt < 1200){
      hist_matched_jets_tau32_1000->Fill(matched_jet.tau3_groomed()/matched_jet.tau2_groomed());
      hist_matched_jets_tau2_1000->Fill(matched_jet.tau2_groomed());
      hist_matched_jets_tau3_1000->Fill(matched_jet.tau3_groomed());
      hist_matched_jets_mass_1000->Fill(matched_jet.v4().M());
}
    if(200 <= pt){
      hist_matched_jets_tau32_ptcut200->Fill(matched_jet.tau3_groomed()/matched_jet.tau2_groomed());
    }
}

}


NSubjettinessHists::~NSubjettinessHists(){}
