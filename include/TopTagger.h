#include "UHH2/common/include/CommonModules.h"

#include "fastjet/PseudoJet.hh"
#include "fastjet/contrib/HOTVR.hh"

/** Class that takes a TopJet and checks the top tagging conditions. The Method Is_tagged returns
* true if the jet is tagged by the given tagger.
*/

class TopTagger{
private:
  bool Is_HOTVR_tagged(TopJet &jet);
  bool Is_SD_tagged(TopJet &jet);

public:
  TopTagger();
  bool Is_tagged(std::string tagger, TopJet &jet);
};
