#include <vector>
#include <iostream>
#include "WordComplexityFeature.h"
#include "moses/Hypothesis.h"
#include "moses/ScoreComponentCollection.h"
#include "moses/TargetPhrase.h"

#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>

using namespace std;

namespace Moses
{

const string WordComplexityFeature::RPC_PORT_NUMBER = "8000";

WordComplexityFeature::WordComplexityFeature(const std::string &line)
  :StatelessFeatureFunction(1, line)
{
  ReadParameters();
}

void WordComplexityFeature::EvaluateInIsolation(const Phrase &source
    , const TargetPhrase &targetPhrase
    , ScoreComponentCollection &scoreBreakdown
    , ScoreComponentCollection &estimatedFutureScore) const
{
  // Connect to the RPC server that gives us word complexity measurements.
  string const serverUrl = "http://127.0.0.1:" + RPC_PORT_NUMBER + "/RPC2";
  string const methodName = "predict";

  xmlrpc_c::clientSimple client;

  // Right now, just take the sum of the score of each word.
  double total_score = 0.0;

  // First, get the word that we want.
  for (int i = 0; i < targetPhrase.GetSize(); i++) {
    string word = targetPhrase.GetWord(0).GetString(m_factorTypeSource).as_string();

    xmlrpc_c::value complexity_score;
    client.call(serverUrl, methodName, "s", &complexity_score, word.c_str());
    total_score += xmlrpc_c::value_double(complexity_score);
  }

  scoreBreakdown.Assign(this, (float) total_score);
}

void WordComplexityFeature::SetParameter(const std::string& key, const std::string& value)
{
  if (key == "factor") {
    m_factorTypeSource = Scan<FactorType>(value);
  } else {
    StatelessFeatureFunction::SetParameter(key, value);
  }
}

}
