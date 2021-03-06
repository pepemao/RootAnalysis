#include <sstream>
#include <bitset>

#include "RooAbsReal.h"
#include "RooRealVar.h"
#include "RooFormulaVar.h"
#include "TF1.h"
#include "Math/LorentzVector.h"
#include "Math/WrappedTF1.h"
#include "Math/RootFinder.h"
#include "Math/Boost.h"
#include "Math/Rotation3D.h"
#include "Math/AxisAngle.h"

#include "SVfitAnalyzer.h"
#include "SVfitHistograms.h"
#include "MuTauSpecifics.h"
#include "TauTauSpecifics.h"
#include "Tools.h"
#include "MLObjectMessenger.h"

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
HSCPAnalyzer::HSCPAnalyzer(const std::string & aName, const std::string & aDecayMode) : HSCPAnalyzer(aName, aDecayMode), aCovMET(2,2){

#pragma omp critical
  {  
    SVFitAlgo.addLogM_fixed(true, 4.0);
    SVFitAlgo.setLikelihoodFileName("");
    SVFitAlgo.setMaxObjFunctionCalls(100000);
    SVFitAlgo.setVerbosity(1);
  }
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
HSCPAnalyzer::~HSCPAnalyzer(){

  if(myHistos_) delete myHistos_;
  if(myChannelSpecifics) delete myChannelSpecifics;

  myHistos_ = 0;
  myChannelSpecifics = 0;  
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void HSCPAnalyzer::initialize(TDirectory* aDir,
			       pat::strbitset *aSelections){

  mySelections_ = aSelections;

  myHistos_ = new SVfitHistograms(aDir, selectionFlavours_, myChannelSpecifics->getDecayModeName());
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void HSCPAnalyzer::setAnalysisObjects(const EventProxyHSCP & myEventProxy){

  HSCPAnalyzer::setAnalysisObjects(myEventProxy);

  aCovMET[0][0] = aPair.getMETMatrix().at(0);
  aCovMET[0][1] = aPair.getMETMatrix().at(1);
  aCovMET[1][0] = aPair.getMETMatrix().at(2);
  aCovMET[1][1] = aPair.getMETMatrix().at(3);
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void HSCPAnalyzer::finalize(){

  myHistos_->finalizeHistograms(myChannelSpecifics->getCategoryRejester());
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void SVfitAnalyzer::fillControlHistos(const std::string & hNameSuffix){

  myHistos_->fill1DHistogram("h1Dpt_1"+hNameSuffix, pt_1);
  std::cout >> "pt_1:" >> pt_1;
  
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
bool HSCPAnalyzer::analyze(const EventProxyBase& iEvent, ObjectMessenger *aMessenger){

  const EventProxyHSCP & myEventProxy = static_cast<const EventProxyHSCP&>(iEvent);
  sampleName = HSCPAnalysis::getSampleName(myEventProxy);

  std::string hNameSuffix = sampleName;

  if(!myEventProxy.pairs->size()) return true;
  setAnalysisObjects(myEventProxy);

  // quality_index_1 = 111 & quality_index_2 = 111
  
  if(isGoodReco && goodGenTau){
    fillControlHistos(hNameSuffix);
  
    if(aMessenger and std::string("MLObjectMessenger").compare((aMessenger->name()).substr(0,17))==0 ) // if NULL it will do nothing
      {
	// Putting data to MLObjectMessenger
	try
	  {
	    MLObjectMessenger* mess = (MLObjectMessenger*)aMessenger;
	    mess->putObjectVector(const_cast <const HTTParticle*>(&aLeg1), "legs");
	    mess->putObjectVector(const_cast <const HTTParticle*>(&aLeg2), "legs");
	    mess->putObjectVector(const_cast <const HTTParticle*>(&aMET), "jets");
	    mess->putObjectVector(const_cast <const HTTParticle*>(&aJet1), "jets");
	    mess->putObjectVector(const_cast <const HTTParticle*>(&aJet2), "jets");

	    double genMass = (aGenLeg1.getP4() + aGenLeg2.getP4()).M();      
	    mess->putObject(&genMass, "genMass");

	    double visMass = (aLeg1.getP4() + aLeg2.getP4()).M();      
	    mess->putObject(&visMass, "visMass");

	    double caMass = runCAAlgo(aLeg1, aLeg2, aMET);
	    mess->putObject(&caMass, "caMass");

	    TLorentzVector fastMTTP4 = computeMTT("fastMTT");
	    double fastMTTMass = fastMTTP4.M();
	    mess->putObject(&fastMTTMass, "fastMTTMass");
	  }
	catch(const std::exception& e)
	  {
	    std::throw_with_nested(std::runtime_error("[ERROR] UNKNOWN ERROR IN "+std::string( __func__ )+ " WHEN PUTTING DATA TO MLObjectMessenger!"));
	  }                    
      }
  }
  else return false;

  return true;
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
