#include <vector>
#include "PhraseLengthPenaltyFeature.h"
#include "moses/Hypothesis.h"
#include "moses/ScoreComponentCollection.h"

using namespace std;

namespace Moses
{
PhraseLengthPenaltyFeature::PhraseLengthPenaltyFeature(const std::string &line)
  :StatelessFeatureFunction(1, line)
{
  ReadParameters();
}

void PhraseLengthPenaltyFeature::EvaluateWhenApplied(const Hypothesis& hypo,
                           ScoreComponentCollection* accumulator) const
{
  TargetPhrase targetPhrase = hypo.GetCurrTargetPhrase();
  
  int numChars = 0;
  for (int i = 0; i < targetPhrase.GetSize(); i++) {
    numChars += targetPhrase.GetWord(i).GetString(0).length();
  }

  accumulator->Assign(this, (float) -numChars);
}

}

