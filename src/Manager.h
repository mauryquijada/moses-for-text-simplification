// $Id$

/***********************************************************************
Moses - factored phrase-based language decoder
Copyright (C) 2006 University of Edinburgh

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
***********************************************************************/

#pragma once

#include <vector>
#include <list>
#include "Input.h"
#include "Hypothesis.h"
#include "StaticData.h"
#include "TranslationOption.h"
#include "HypothesisCollection.h"
#include "TranslationOptionCollectionText.h"
#include "LatticePathList.h"
#include "SquareMatrix.h"
#include "WordsBitmap.h"
//#include "UnknownWordHandler.h"

class LatticePath;

class Manager
{
protected:	
	// data
	InputType const& m_source; /**< source sentence to be translated */

	std::vector < HypothesisCollection > m_hypoStack; /**< stacks to store hypothesis (partial translations) */ 
		// no of elements = no of words in source + 1
	StaticData &m_staticData; /**< holds various kinds of constants, counters, and global data structures */
	TranslationOptionCollection &m_possibleTranslations; /**< pre-computed list of translation options for the phrases in this sentence */
	TargetPhrase m_initialTargetPhrase; /**< used to seed 1st hypo */
	
	// functions for creating hypotheses
	void ProcessOneHypothesis(const Hypothesis &hypothesis);
	void ExpandAllHypotheses(const Hypothesis &hypothesis,const TranslationOptionList &transOptList);
	void ExpandHypothesis(const Hypothesis &hypothesis,const TranslationOption &transOpt);

	// logging
	void OutputHypoStack(int stack = -1);
	void OutputHypoStackSize();
public:
	Manager(InputType const& source, TranslationOptionCollection&, StaticData &staticData);
	~Manager();

	void ProcessSentence();
	const Hypothesis *GetBestHypothesis() const;
	void CalcNBest(size_t count, LatticePathList &ret) const;
};

