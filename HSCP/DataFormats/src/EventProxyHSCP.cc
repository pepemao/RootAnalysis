// Pozmieniałem nazwy metod i klasy na HSCP


#include "EventProxyHSCP.h"

#include "TSystem.h"

#include <iostream>

EventProxyHSCP::EventProxyHSCP(){}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
EventProxyHSCP::~EventProxyHSCP(){}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
EventProxyBase* EventProxyHSCP::clone() const{

  return new EventProxyHSCP();

}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void EventProxyHSCP::init(std::vector<std::string> const& iFileNames){

  treeName_ = "HscpTree";

  EventProxyBase::init(iFileNames);
  //fChain->SetMakeClass(0);

  pt_1_ = 0;
  pt_2_ = 0;
  eta_1_ = 0;
  eta_2_ = 0;
  phi_1_ = 0;
  phi_2_ = 0;
  ibeta_1_ = 0;
  ibeta_2_ = 0;
  err_ibeta_1_ = 0;
  err_ibeta_2_ = 0;
  n_CSC_hits_1_ = 0;
  n_CSC_hits_2_ = 0;
  n_DT_hits_1_ = 0;
  n_DT_hits_2_ = 0;
  n_RPC_hits_1_ = 0;
  n_RPC_hits_2_ = 0;
  n_strip_hits_1_ = 0;
  n_strip_hits_2_ = 0;
  n_pixel_hits_1_ = 0;
  n_pixel_hits_2_ = 0;
  n_TOF_meas_1_ = 0;
  n_TOF_meas_2_ = 0;
  I_h_1_ = 0;
  I_h_2_ = 0;
  I_as_1_ = 0;
  I_as_2_ = 0;
  mass_I_h_1_ = 0;
  mass_I_h_2_ = 0;
  mass_ibeta_1_ = 0;
  mass_ibeta_2_ = 0;
  pt_err_1_ = 0;
  pt_err_2_ = 0;
  lumi_sec_ = 0;
  event_nr_ = 0;
  run_nr_ = 0;
  quality_index_1_ = 0;
  quality_index_2_ = 0;
  
  fChain->SetBranchAddress("pt_1", &myPair.pt(1));
  fChain->SetBranchAddress("pt_2", &myPair.pt(2));
  fChain->SetBranchAddress("eta_1", &myPair.eta(1));
  fChain->SetBranchAddress("eta_2", &myPair.eta(2));
  fChain->SetBranchAddress("phi_1", &myPair.phi(1));
  fChain->SetBranchAddress("phi_2", &myPair.phi(2));
  fChain->SetBranchAddress("ibeta_1", &myPair.ibeta(1));
  fChain->SetBranchAddress("ibeta_2", &myPair.ibeta(2));
  fChain->SetBranchAddress("err_ibeta_1", &myPair.err(ibeta(1));
  fChain->SetBranchAddress("err_ibeta_2", &myPair.err(ibeta(2));
  fChain->SetBranchAddress("n_CSC_hits_1", &myPair.n_CSC_hits(1));
  fChain->SetBranchAddress("n_CSC_hits_2", &myPair.n_CSC_hits(2));
  fChain->SetBranchAddress("n_DT_hits_1", &myPair.n_DT_hits(1));
  fChain->SetBranchAddress("n_DT_hits_2", &myPair.n_DT_hits(2));
  fChain->SetBranchAddress("n_RPC_hits_1", &myPair.n_RPC_hits(1));
  fChain->SetBranchAddress("n_RPC_hits_2", &myPair.n_RPC_hits(2));
  fChain->SetBranchAddress("n_strip_hits_1", &myPair.n_strip_hits(1));
  fChain->SetBranchAddress("n_strip_hits_2", &myPair.n_strip_hits(2));
  fChain->SetBranchAddress("n_pixel_hits_1", &myPair.n_pixel_hits(1));
  fChain->SetBranchAddress("n_pixel_hits_2", &myPair.n_pixel_hits(2));
  fChain->SetBranchAddress("n_TOF_meas_1", &myPair.n_TOF_meas(1));
  fChain->SetBranchAddress("n_TOF_meas_2", &myPair.n_TOF_meas(2));
  fChain->SetBranchAddress("I_h_1", &myPair.I_h(1));
  fChain->SetBranchAddress("I_h_2", &myPair.I_h(2));
  fChain->SetBranchAddress("I_as_1", &myPair.I_as(1));
  fChain->SetBranchAddress("I_as_2", &myPair.I_as(2));
  fChain->SetBranchAddress("mass_I_h_1", &myPair.mass_I_h(1));
  fChain->SetBranchAddress("mass_I_h_2", &myPair.mass_I_h(2));
  fChain->SetBranchAddress("mass_ibeta_1", &myPair.mass_ibeta(1));
  fChain->SetBranchAddress("mass_ibeta_2", &myPair.mass_ibeta(2));
  fChain->SetBranchAddress("pt_err_1", &myPair.pt_err(1));
  fChain->SetBranchAddress("pt_err_2", &myPair.pt_err(2));
  fChain->SetBranchAddress("lumi_sec", &myPair.lumi_sec));
  fChain->SetBranchAddress("event_nr", &myPair.event_nr));
  fChain->SetBranchAddress("run_nr", &myPair.run_nr));
  fChain->SetBranchAddress("quality_index_1", &myPair.quality_index(1));
  fChain->SetBranchAddress("quality_index_2", &myPair.quality_index(2));

  fChain->SetBranchStatus("*",0);
  fChain->SetBranchStatus("pt_1*",1);
  fChain->SetBranchStatus("pt_2*",1);
  fChain->SetBranchStatus("eta_1*",1);
  fChain->SetBranchStatus("eta_2*",1);
  fChain->SetBranchStatus("phi_1*",1);
  fChain->SetBranchStatus("phi_2*",1);
  fChain->SetBranchStatus("ibeta_1*",1);
  fChain->SetBranchStatus("ibeta_2*",1);
  fChain->SetBranchStatus("err_ibeta_1*",1);
  fChain->SetBranchStatus("err_ibeta_2*",1);
  fChain->SetBranchStatus("n_CSC_hits_1*",1);
  fChain->SetBranchStatus("n_CSC_hits_2*",1);
  fChain->SetBranchStatus("n_DT_hits_1*",1);
  fChain->SetBranchStatus("n_DT_hits_2*",1);
  fChain->SetBranchStatus("n_RPC_hits_1*",1);
  fChain->SetBranchStatus("n_RPC_hits_2*",1);
  fChain->SetBranchStatus("n_strip_hits_1*",1);
  fChain->SetBranchStatus("n_strip_hits_2*",1);
  fChain->SetBranchStatus("n_pixel_hits_1*",1);
  fChain->SetBranchStatus("n_pixel_hits_2*",1);
  fChain->SetBranchStatus("n_TOF_meas_1*",1);
  fChain->SetBranchStatus("n_TOF_meas_2*",1);
  fChain->SetBranchStatus("I_h_1*",1);
  fChain->SetBranchStatus("I_h_2*",1);
  fChain->SetBranchStatus("I_as_1*",1);
  fChain->SetBranchStatus("I_as_2*",1);
  fChain->SetBranchStatus("mass_I_h_1*",1);
  fChain->SetBranchStatus("mass_I_h_2*",1);
  fChain->SetBranchStatus("mass_ibeta_1*",1);
  fChain->SetBranchStatus("mass_ibeta_2*",1);
  fChain->SetBranchStatus("pt_err_1*",1);
  fChain->SetBranchStatus("pt_err_2*",1);
  fChain->SetBranchStatus("lumi_sec*",1);
  fChain->SetBranchStatus("event_nr*",1);
  fChain->SetBranchStatus("run_nr*",1);
  fChain->SetBranchStatus("quality_index_1*",1);
  fChain->SetBranchStatus("quality_index_2*",1);

}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
void  EventProxyHSCP::enableBranches(){

  fChain->SetBranchStatus("*",1);

}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
void  EventProxyHSCP::disableBranches(){

  fChain->SetBranchStatus("*",0);

}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
void  EventProxyHSCP::clear(){

  if(pt([12]) pt_1->clear();
  if(pt([12]) pt_2->clear();
  if(eta([12]) eta_1->clear();
  if(eta([12]) eta_2->clear();
  if(phi([12]) phi_1->clear();
  if(phi([12]) phi_2->clear();
  if(ibeta([12]) ibeta_1->clear();
  if(ibeta([12]) ibeta_2->clear();
  if(err_ibeta([12]) err_ibeta_1->clear();
  if(err_ibeta([12]) err_ibeta_2->clear();
  if(n_CSC_hits([12]) n_CSC_hits_1->clear();
  if(n_CSC_hits([12]) n_CSC_hits_2->clear();
  if(n_DT_hits([12]) n_DT_hits_1->clear();
  if(n_DT_hits([12]) n_DT_hits_2->clear();
  if(n_RPC_hits([12]) n_RPC_hits_1->clear();
  if(n_RPC_hits([12]) n_RPC_hits_2->clear();
  if(n_strip_hits([12]) n_strip_hits_1->clear();
  if(n_strip_hits([12]) n_strip_hits_2->clear();
  if(n_pixel_hits([12]) n_pixel_hits_1->clear();
  if(n_pixel_hits([12]) n_pixel_hits_2->clear();
  if(n_TOF_meas([12]) n_TOF_meas_1->clear();
  if(n_TOF_meas([12]) n_TOF_meas_2->clear();
  if(I_h([12]) I_h_1->clear();
  if(I_h([12]) I_h_2->clear();
  if(I_as([12]) I_as_1->clear();
  if(I_as([12]) I_as_2->clear();
  if(mass_I_h([12]) mass_I_h_1->clear();
  if(mass_I_h([12]) mass_I_h_2->clear();
  if(mass_ibeta([12]) mass_ibeta_1->clear();
  if(mass_ibeta([12]) mass_ibeta_2->clear();
  if(pt_err([12]) pt_err_1->clear();
  if(pt_err([12]) pt_err_2->clear();
  if(lumi_sec) lumi_sec->clear();
  if(event_nr) event_nr->clear();
  if(run_nr) run_nr->clear();
  if(quality_index([12]) quality_index_1->clear();
  if(quality_index([12]) quality_index_2->clear();

}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
