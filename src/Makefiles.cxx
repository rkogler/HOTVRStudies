#include "UHH2/HOTVRStudies/include/Makefiles.h"

using namespace std;
using namespace fastjet;

Makefiles::Makefiles(string m_csvfile_ttbar, string m_csvfile_qcd, vector<pair<PseudoJet,vector<PseudoJet>>> jets_and_constituents, bool is_qcd):
m_csvfile_ttbar("csvfile_ttbar"), m_csvfile_qcd("csvfile_qcd")
{
  // open file and fill with info
  ofstream myfile;
  if (is_qcd) { // open qcd file
    myfile.open(m_csvfile_qcd, std::ofstream::out | std::ofstream::app);
  }
  if (!is_qcd){ // open ttbar file
    myfile.open(m_csvfile_ttbar, std::ofstream::out | std::ofstream::app);
  }
  if (myfile.is_open()) { // fill file
    for (size_t j = 0; j < jets_and_constituents.size(); j++) { // loop over jets
      auto vr_jet = jets_and_constituents[j].first;
      auto constituents = jets_and_constituents[j].second;
      myfile << "jet " + to_string(j) + "\n";
        for (size_t i = 0; i < constituents.size(); i++) { // loop over constituents
          PseudoJet jet = constituents[i];
          myfile << to_string(jet.px()) + ","+ to_string(jet.py()) +","+ to_string(jet.pz()) +","+ to_string(jet.m()) + " \n";
      } // end constituents loop
      } // end jets loop
      myfile.close();
    }
  else{
  std::cout << "Cannot open file!" << '\n';
  }
}
