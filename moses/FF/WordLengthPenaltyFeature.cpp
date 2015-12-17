#include <vector>
#include "WordLengthPenaltyFeature.h"
#include "moses/Hypothesis.h"
#include "moses/ScoreComponentCollection.h"
#include "moses/TargetPhrase.h"

using namespace std;

namespace Moses
{
WordLengthPenaltyFeature::WordLengthPenaltyFeature(const std::string &line)
  :StatelessFeatureFunction(1, line)
{
  ReadParameters();
}

void WordLengthPenaltyFeature::EvaluateInIsolation(const Phrase &source
    , const TargetPhrase &targetPhrase
    , ScoreComponentCollection &scoreBreakdown
    , ScoreComponentCollection &estimatedFutureScore) const
{
  int numWords = - targetPhrase.GetSize();
  scoreBreakdown.Assign(this, (float) numWords);
}

}

