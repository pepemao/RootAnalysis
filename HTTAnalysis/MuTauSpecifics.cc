#include "MuTauSpecifics.h"

#include "AnalysisEnums.h"
#include "HTTAnalyzer.h"
#include "EventProxyHTT.h"
#include "Tools.h"

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
MuTauSpecifics::MuTauSpecifics(HTTAnalyzer * aAnalyzer) : ChannelSpecifics(aAnalyzer){

        decayModeName = "MuTau";

}
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void MuTauSpecifics::setAnalysisObjects(const EventProxyHTT & myEventProxy) {

        myAnalyzer->aLeg1 = myAnalyzer->aPair.getMuon();
        myAnalyzer->aLeg2 = myAnalyzer->aPair.getTau();

        myAnalyzer->aGenLeg1 = HTTParticle();
        myAnalyzer->aGenLeg2 = HTTParticle();

        if(myEventProxy.genLeptons &&
           myEventProxy.genLeptons->size()) {
                HTTParticle aGenTau =  myEventProxy.genLeptons->at(0);
                if(aGenTau.getProperty(PropertyEnum::decayMode)==HTTAnalysis::tauDecayMuon) myAnalyzer->aGenLeg1 = aGenTau;
                else if(aGenTau.getProperty(PropertyEnum::decayMode)!=HTTAnalysis::tauDecaysElectron) myAnalyzer->aGenLeg2 = aGenTau;
                if(myEventProxy.genLeptons->size()>1) {
                        aGenTau =  myEventProxy.genLeptons->at(1);
                        if(aGenTau.getProperty(PropertyEnum::decayMode)==HTTAnalysis::tauDecayMuon) myAnalyzer->aGenLeg1 = aGenTau;
                        else if(aGenTau.getProperty(PropertyEnum::decayMode)!=HTTAnalysis::tauDecaysElectron) myAnalyzer->aGenLeg2 = aGenTau;
                }
        }
};
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
std::pair<bool, bool> MuTauSpecifics::checkTauDecayMode(const EventProxyHTT & myEventProxy){

        bool goodGenDecayMode = false;
        bool goodRecoDecayMode = false;

        std::vector<std::string> decayNamesGen = HTTAnalysis::getTauDecayName(myAnalyzer->aGenLeg2.getProperty(PropertyEnum::decayMode),
                                                                             myAnalyzer->aGenLeg1.getProperty(PropertyEnum::decayMode));
        std::vector<std::string> decayNamesReco = HTTAnalysis::getTauDecayName(myAnalyzer->aLeg2.getProperty(PropertyEnum::decayMode),HTTAnalysis::tauDecayMuon);

        for(auto it: decayNamesGen) if(it.find("Lepton1Prong")!=std::string::npos) goodGenDecayMode = true;
        for(auto it: decayNamesReco) if(it.find("Lepton1Prong")!=std::string::npos) goodRecoDecayMode = true;

        return std::pair<bool, bool>(goodGenDecayMode, goodRecoDecayMode);
}
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void MuTauSpecifics::testAllCategories(const HTTAnalysis::sysEffects & aSystEffect){

        for(auto && it: myAnalyzer->categoryDecisions) it = false;

        int tauIDmask = 0;
        for(unsigned int iBit=0; iBit<myAnalyzer->aEvent.ntauIds; iBit++) {
                if(myAnalyzer->aEvent.tauIDStrings[iBit]=="byTightIsolationMVArun2v1DBoldDMwLT") tauIDmask |= (1<<iBit);
                if(myAnalyzer->aEvent.tauIDStrings[iBit]=="againstMuonTight3") tauIDmask |= (1<<iBit);
                if(myAnalyzer->aEvent.tauIDStrings[iBit]=="againstElectronVLooseMVA6") tauIDmask |= (1<<iBit);
        }
        bool tauID = ( (int)myAnalyzer->aLeg2.getProperty(PropertyEnum::tauID) & tauIDmask) == tauIDmask;
        bool muonKinematics = myAnalyzer->aLeg1.getP4().Pt()>24 && fabs(myAnalyzer->aLeg1.getP4().Eta())<2.1;
        bool trigger = myAnalyzer->aLeg1.hasTriggerMatch(TriggerEnum::HLT_IsoMu24) ||
                       myAnalyzer->aLeg1.hasTriggerMatch(TriggerEnum::HLT_IsoTkMu24);

        if(!muonKinematics || !tauID || !trigger) return;

        myAnalyzer->nJets30 = 0;
        for(auto itJet: myAnalyzer->aSeparatedJets) {
                if(itJet.getP4(aSystEffect).Pt()>30) ++myAnalyzer->nJets30;
        }

        myAnalyzer->nJetsInGap30 = 0;
        if(myAnalyzer->nJets30>=2) {
                for(unsigned int iJet=2; iJet<myAnalyzer->aSeparatedJets.size(); ++iJet) {
                        if( (myAnalyzer->aSeparatedJets.at(iJet).getP4().Eta()>myAnalyzer->aJet1.getP4().Eta() &&
                             myAnalyzer->aSeparatedJets.at(iJet).getP4().Eta()<myAnalyzer->aJet2.getP4().Eta()) ||
                            (myAnalyzer->aSeparatedJets.at(iJet).getP4().Eta()<myAnalyzer->aJet1.getP4().Eta() &&
                             myAnalyzer->aSeparatedJets.at(iJet).getP4().Eta()>myAnalyzer->aJet2.getP4().Eta()) ) {
                                if(myAnalyzer->aSeparatedJets.at(iJet).getP4(aSystEffect).Pt()>30) myAnalyzer->nJetsInGap30++;
                        }
                }
        }

        float jetsMass = (myAnalyzer->aJet1.getP4(aSystEffect)+myAnalyzer->aJet2.getP4(aSystEffect)).M();
        float higgsPt =  (myAnalyzer->aLeg1.getP4(aSystEffect) + myAnalyzer->aLeg2.getP4(aSystEffect) + myAnalyzer->aMET.getP4(aSystEffect)).Pt();
        bool mtSelection = myAnalyzer->aPair.getMTMuon(aSystEffect)<50;

        bool jet0_low =  myAnalyzer->aLeg2.getP4(aSystEffect).Pt()>20 && myAnalyzer->aLeg2.getP4(aSystEffect).Pt()<50 && myAnalyzer->nJets30==0;
        bool jet0_high = myAnalyzer->aLeg2.getP4(aSystEffect).Pt()>50 && myAnalyzer->nJets30==0;

        bool jet1_low = (myAnalyzer->nJets30==1 || (myAnalyzer->nJets30==2 && jetsMass<500)) &&
                        (myAnalyzer->aLeg2.getP4(aSystEffect).Pt()>30 && myAnalyzer->aLeg2.getP4(aSystEffect).Pt()<40 ||
                         myAnalyzer->aLeg2.getP4(aSystEffect).Pt()>40 && higgsPt<140);

        bool jet1_high = (myAnalyzer->nJets30==1 || (myAnalyzer->nJets30==2 && jetsMass<500)) &&
                         (myAnalyzer->aLeg2.getP4(aSystEffect).Pt()>40 && higgsPt>140);

        bool vbf_low = myAnalyzer->aLeg2.getP4(aSystEffect).Pt()>20 &&
                       myAnalyzer->nJets30==2 && jetsMass>500 &&
                       (jetsMass<800 || higgsPt<100);

        bool vbf_high = myAnalyzer->aLeg2.getP4(aSystEffect).Pt()>20 &&
                        myAnalyzer->nJets30==2 && jetsMass>800 && higgsPt>100;

        bool cpMuonSelection = myAnalyzer->aLeg1.getPCARefitPV().Mag()>myAnalyzer->nPCAMin_;
        bool cpTauSelection =  myAnalyzer->aLeg2.getPCARefitPV().Mag()>myAnalyzer->nPCAMin_;
        bool cpPi = cpMuonSelection && cpTauSelection && myAnalyzer->aLeg2.getProperty(PropertyEnum::decayMode)==HTTAnalysis::tauDecay1ChargedPion0PiZero;
        bool cpRho = cpMuonSelection && myAnalyzer->aLeg2.getProperty(PropertyEnum::decayMode)!=HTTAnalysis::tauDecay1ChargedPion0PiZero &&
                     HTTAnalysis::isOneProng(myAnalyzer->aLeg2.getProperty(PropertyEnum::decayMode));

        //2D categories
        bool jet0 = myAnalyzer->aLeg2.getP4(aSystEffect).Perp()>30 && myAnalyzer->nJets30 == 0;
        bool boosted = myAnalyzer->aLeg2.getP4(aSystEffect).Perp()>30 && (myAnalyzer->nJets30==1 || (myAnalyzer->nJets30==2 && jetsMass < 300) || myAnalyzer->nJets30 > 2);
        bool vbf = myAnalyzer->aLeg2.getP4(aSystEffect).Perp()>30 && myAnalyzer->nJets30==2 && jetsMass>300;

        bool wSelection = myAnalyzer->aPair.getMTMuon(aSystEffect)>80 && myAnalyzer->aLeg1.getProperty(PropertyEnum::combreliso)<0.15;
        bool muonAntiIso = myAnalyzer->aLeg1.getProperty(PropertyEnum::combreliso)>0.15 && myAnalyzer->aLeg1.getProperty(PropertyEnum::combreliso)<0.30;
        bool muonIso = myAnalyzer->aLeg1.getProperty(PropertyEnum::combreliso)<0.15;

        bool ss = myAnalyzer->aLeg2.getCharge()*myAnalyzer->aLeg1.getCharge() == 1;
        bool os = myAnalyzer->aLeg2.getCharge()*myAnalyzer->aLeg1.getCharge() == -1;

        //cpPi &= std::abs(myAnalyzer->aLeg1.getPCARefitPV().Mag() - myAnalyzer->aGenLeg1.getPCA().Mag())<0.001;//TEST
        //cpPi &= std::abs(myAnalyzer->aLeg2.getPCARefitPV().Mag() - myAnalyzer->aGenLeg2.getPCA().Mag())<0.001;//TEST
	//cpPi = true;
	//cpPi &= myAnalyzer->aLeg1.getPCARefitPV().Mag()>0.003 &&  myAnalyzer->aLeg1.getPCARefitPV().Mag()<0.004;
	//cpPi &= myAnalyzer->aLeg1.getPCARefitPV().Mag()>0.00;
        



/*
        myAnalyzer->categoryDecisions[(int)HTTAnalysis::jet0_low] = os && muonIso && mtSelection && jet0_low;
        myAnalyzer->categoryDecisions[(int)HTTAnalysis::jet0_high] = os && muonIso && mtSelection && jet0_high;

        myAnalyzer->categoryDecisions[(int)HTTAnalysis::jet1_low] = os && muonIso && mtSelection && jet1_low;
        myAnalyzer->categoryDecisions[(int)HTTAnalysis::jet1_high] = os && muonIso && mtSelection && jet1_high;

        myAnalyzer->categoryDecisions[(int)HTTAnalysis::vbf_low] = os && muonIso && mtSelection && vbf_low;
        myAnalyzer->categoryDecisions[(int)HTTAnalysis::vbf_high] = os && muonIso && mtSelection && vbf_high;
*/

        //Main categories
        myAnalyzer->categoryDecisions[ChannelSpecifics::jet0->id()] = os && muonIso && mtSelection && jet0;
        myAnalyzer->categoryDecisions[ChannelSpecifics::boosted->id()] = os && muonIso && mtSelection && boosted;
        myAnalyzer->categoryDecisions[ChannelSpecifics::vbf->id()] = os && muonIso && mtSelection && vbf;
        myAnalyzer->categoryDecisions[ChannelSpecifics::antiIso_jet0->id()] = os && muonAntiIso && jet0;
        myAnalyzer->categoryDecisions[ChannelSpecifics::antiIso_boosted->id()] = os && muonAntiIso && boosted;
        myAnalyzer->categoryDecisions[ChannelSpecifics::antiIso_vbf->id()] = os && muonAntiIso && vbf;
        myAnalyzer->categoryDecisions[ChannelSpecifics::mu_pi->id()] = os && muonIso && mtSelection && cpPi;
        myAnalyzer->categoryDecisions[ChannelSpecifics::mu_rho->id()] = os && muonIso && mtSelection && cpRho;

        //W control region
        myAnalyzer->categoryDecisions[ChannelSpecifics::jet0->wSF()->id()] = os && muonIso && wSelection && jet0;
        myAnalyzer->categoryDecisions[ChannelSpecifics::boosted->wSF()->id()] = os && muonIso && wSelection && boosted;
        myAnalyzer->categoryDecisions[ChannelSpecifics::vbf->wSF()->id()] = os && muonIso && wSelection && vbf;
        myAnalyzer->categoryDecisions[ChannelSpecifics::antiIso_jet0->wSF()->id()] = os && muonAntiIso && wSelection && jet0;
        myAnalyzer->categoryDecisions[ChannelSpecifics::antiIso_boosted->wSF()->id()] = os && muonAntiIso && wSelection && boosted;
        myAnalyzer->categoryDecisions[ChannelSpecifics::antiIso_vbf->wSF()->id()] = os && muonAntiIso && wSelection && vbf;
        myAnalyzer->categoryDecisions[ChannelSpecifics::mu_pi->wSF()->id()] = os && muonIso && wSelection && cpPi;
        myAnalyzer->categoryDecisions[ChannelSpecifics::mu_rho->wSF()->id()] = os && muonIso && wSelection && cpRho;

        ///QCD region in W SF control region
        myAnalyzer->categoryDecisions[ChannelSpecifics::jet0->wSF()->qcdEstimate()->id()] = ss && muonIso && wSelection && jet0;
        myAnalyzer->categoryDecisions[ChannelSpecifics::boosted->wSF()->qcdEstimate()->id()] = ss && muonIso && wSelection && boosted;
        myAnalyzer->categoryDecisions[ChannelSpecifics::vbf->wSF()->qcdEstimate()->id()] = ss && muonIso && wSelection && vbf;
        myAnalyzer->categoryDecisions[ChannelSpecifics::antiIso_jet0->wSF()->qcdEstimate()->id()] = ss && muonAntiIso && wSelection && jet0;
        myAnalyzer->categoryDecisions[ChannelSpecifics::antiIso_boosted->wSF()->qcdEstimate()->id()] = ss && muonAntiIso && wSelection && boosted;
        myAnalyzer->categoryDecisions[ChannelSpecifics::antiIso_vbf->wSF()->qcdEstimate()->id()] = ss && muonAntiIso && wSelection && vbf;
        myAnalyzer->categoryDecisions[ChannelSpecifics::mu_pi->wSF()->qcdEstimate()->id()] = ss && muonIso && wSelection && cpPi;
        myAnalyzer->categoryDecisions[ChannelSpecifics::mu_rho->wSF()->qcdEstimate()->id()] = ss && muonIso && wSelection && cpRho;

        ///QCD region
        myAnalyzer->categoryDecisions[ChannelSpecifics::jet0->qcdEstimate()->id()] = ss && muonIso && mtSelection && jet0;
        myAnalyzer->categoryDecisions[ChannelSpecifics::boosted->qcdEstimate()->id()] = ss && muonIso && mtSelection && boosted;
        myAnalyzer->categoryDecisions[ChannelSpecifics::vbf->qcdEstimate()->id()] = ss && muonIso && mtSelection && vbf;
        myAnalyzer->categoryDecisions[ChannelSpecifics::antiIso_jet0->qcdEstimate()->id()] = ss && muonAntiIso && jet0;
        myAnalyzer->categoryDecisions[ChannelSpecifics::antiIso_boosted->qcdEstimate()->id()] = ss && muonAntiIso && boosted;
        myAnalyzer->categoryDecisions[ChannelSpecifics::antiIso_vbf->qcdEstimate()->id()] = ss && muonAntiIso && vbf;
        myAnalyzer->categoryDecisions[ChannelSpecifics::mu_pi->qcdEstimate()->id()] = ss && muonIso && mtSelection && cpPi;
        myAnalyzer->categoryDecisions[ChannelSpecifics::mu_rho->qcdEstimate()->id()] = ss && muonIso && mtSelection && cpRho;

        ///W SF region in QCD region
        myAnalyzer->categoryDecisions[ChannelSpecifics::jet0->qcdEstimate()->wSF()->id()] = ss && muonIso && wSelection && jet0;
        myAnalyzer->categoryDecisions[ChannelSpecifics::boosted->qcdEstimate()->wSF()->id()] = ss && muonIso && wSelection && boosted;
        myAnalyzer->categoryDecisions[ChannelSpecifics::vbf->qcdEstimate()->wSF()->id()] = ss && muonIso && wSelection && vbf;
        myAnalyzer->categoryDecisions[ChannelSpecifics::antiIso_jet0->qcdEstimate()->wSF()->id()] = ss && muonAntiIso && jet0;
        myAnalyzer->categoryDecisions[ChannelSpecifics::antiIso_boosted->qcdEstimate()->wSF()->id()] = ss && muonAntiIso && boosted;
        myAnalyzer->categoryDecisions[ChannelSpecifics::antiIso_vbf->qcdEstimate()->wSF()->id()] = ss && muonAntiIso && vbf;
        myAnalyzer->categoryDecisions[ChannelSpecifics::mu_pi->qcdEstimate()->wSF()->id()] = ss && muonIso && wSelection && cpPi;
        myAnalyzer->categoryDecisions[ChannelSpecifics::mu_rho->qcdEstimate()->wSF()->id()] = ss && muonIso && wSelection && cpRho;
}
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
float MuTauSpecifics::getLeg1Correction(const HTTAnalysis::sysEffects & aSystEffect){

        return getLeptonCorrection(myAnalyzer->aLeg1.getP4(aSystEffect).Eta(),
                                   myAnalyzer->aLeg1.getP4(aSystEffect).Pt(), HTTAnalysis::hadronicTauDecayModes::tauDecayMuon, false);

}
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
float MuTauSpecifics::getLeg2Correction(const HTTAnalysis::sysEffects & aSystEffect){

        return getLeptonCorrection(myAnalyzer->aLeg2.getP4(aSystEffect).Eta(), myAnalyzer->aLeg2.getP4(aSystEffect).Pt(),
                                   static_cast<HTTAnalysis::hadronicTauDecayModes>(myAnalyzer->aLeg2.getProperty(PropertyEnum::decayMode)),false);

}
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////