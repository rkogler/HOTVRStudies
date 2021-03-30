#include <iostream>
#include <fstream>
#include "UHH2/core/include/GenParticle.h"
#include "UHH2/common/include/CommonModules.h"

#include "fastjet/PseudoJet.hh"
#include "fastjet/JetDefinition.hh"

/**
* This class can produce .csv files containing informations about the jets.
* Input: files, vector of pairs containing jets with the corresponding constituents
* 
*/

class Makefiles{
  private:
    std::string m_csvfile_ttbar;
    std::string m_csvfile_qcd;
    std::vector<fastjet::PseudoJet> _jets;

  public:
    Makefiles(std::string m_csvfile_ttbar, std::string m_csvfile_qcd, std::vector<std::pair<fastjet::PseudoJet, std::vector<fastjet::PseudoJet>>> jets_and_constituents, bool is_qcd);

};
