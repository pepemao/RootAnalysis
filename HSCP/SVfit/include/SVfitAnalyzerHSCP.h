#ifndef RootAnalysis_SVfitAnalyzer_H
#define RootAnalysis_SVfitAnalyzer_H

#include <string>
#include <vector>
#include <map>
#include <tuple>

#include "ObjectMessenger.h"
#include "EventProxyBase.h"
#include "EventProxyHTT.h"

#include "strbitset.h"
#include "TDirectory.h"

//ROOT includes
#include "TTree.h"

#include "HSCPAnalyzer.h"
#include "ChannelSpecifics.h"
#include "AnalysisEnums.h"

#include "TauAnalysis/ClassicSVfit/interface/ClassicSVfit.h"
#include "TauAnalysis/ClassicSVfit/interface/FastMTT.h"

class SVfitHistograms;

class TH1F;
class TH2F;
class TH3F;
class TLorentzVector;
class TF1;

class SVfitAnalyzerHSCP: public HTTAnalyzer{

 public:

  SVfitAnalyzerHSCP(const std::string & aName, const std::string & aDecayMode = "None");

  virtual ~SVfitAnalyzerHSCP();

  ///Initialize the analyzer
  virtual void initialize(TDirectory* aDir,
			  pat::strbitset *aSelections);

  virtual void setAnalysisObjects(const EventProxyHTT & myEventProxy);

  virtual bool analyze(const EventProxyBase& iEvent) {return analyze(iEvent, 0); }

  virtual bool analyze(const EventProxyBase& iEvent, ObjectMessenger *aMessenger);

  virtual void finalize();

  virtual void fillControlHistos(const std::string & hNameSuffix);

 private:

  TLorentzVector computeMTT(const std::string & algoName);
  
  TLorentzVector runSVFitAlgo(const std::vector<classic_svFit::MeasuredTauLepton> & measuredTauLeptons,
                              const HTTParticle &aMET, const TMatrixD &covMET);

  TLorentzVector runFastMTTAlgo(const std::vector<classic_svFit::MeasuredTauLepton> & measuredTauLeptons,
				const HTTParticle &aMET, const TMatrixD &covMET);

  double runCAAlgo(const HTTParticle & aLeg1, const HTTParticle & aLeg2,
		   const HTTParticle & aMET);

  std::tuple<double, double> getTauMomentum(const TLorentzVector & visP4, double cosGJ);

  ///Histograms storage.
  SVfitHistograms *myHistos_;

  ///ROOT file containing current TTree
  TFile *ntupleFile_;

  ClassicSVfit SVFitAlgo;
  FastMTT fastMTTAlgo;

  TMatrixD aCovMET;
  TLorentzVector SVFitLeg1P4, SVFitLeg2P4;
  /////////

};

#endif
