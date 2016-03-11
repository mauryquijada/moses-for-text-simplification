#pragma once

#include <string>
#include "StatelessFeatureFunction.h"

namespace Moses
{

class WordComplexityFeature : public StatelessFeatureFunction
{
public:
  WordComplexityFeature(const std::string &line);

  bool IsUseable(const FactorMask &mask) const {
    return true;
  }

  void EvaluateInIsolation(const Phrase &source
                           , const TargetPhrase &targetPhrase
                           , ScoreComponentCollection &scoreBreakdown
                           , ScoreComponentCollection &estimatedFutureScore) const;

  void EvaluateWithSourceContext(const InputType &input
                                 , const InputPath &inputPath
                                 , const TargetPhrase &targetPhrase
                                 , const StackVec *stackVec
                                 , ScoreComponentCollection &scoreBreakdown
                                 , ScoreComponentCollection *estimatedFutureScore = NULL) const
  {}

  void EvaluateTranslationOptionListWithSourceContext(const InputType &input
      , const TranslationOptionList &translationOptionList) const
  {}

  void EvaluateWhenApplied(const Hypothesis& hypo,
                           ScoreComponentCollection* accumulator) const
  {}

  void EvaluateWhenApplied(const ChartHypothesis &hypo,
                           ScoreComponentCollection* accumulator) const
  {}


  void SetParameter(const std::string& key, const std::string& value);

private:
  FactorType m_factorTypeSource;
  static const std::string RPC_PORT_NUMBER;
};

}
