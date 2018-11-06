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

  pair =0

  fChain->SetBranch
/* stara wersja

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
  
  fChain->SetBranchAddress("pt_1", &pt_1_);
  fChain->SetBranchAddress("pt_2", &pt_2_);
  fChain->SetBranchAddress("eta_1", &eta_1_);
  fChain->SetBranchAddress("eta_2", &eta_2_);
  fChain->SetBranchAddress("phi_1", &phi_1_);
  fChain->SetBranchAddress("phi_2", &phi_2_);
  fChain->SetBranchAddress("ibeta_1", &ibeta_1_);
  fChain->SetBranchAddress("ibeta_2", &ibeta_2_);
  fChain->SetBranchAddress("err_ibeta_1", &err_ibeta_1_);
  fChain->SetBranchAddress("err_ibeta_2", &err_ibeta_2_);
  fChain->SetBranchAddress("n_CSC_hits_1", &n_CSC_hits_1_);
  fChain->SetBranchAddress("n_CSC_hits_2", &n_CSC_hits_2_);
  fChain->SetBranchAddress("n_DT_hits_1", &n_DT_hits_1_);
  fChain->SetBranchAddress("n_DT_hits_2", &n_DT_hits_2_);
  fChain->SetBranchAddress("n_RPC_hits_1", &n_RPC_hits_1_);
  fChain->SetBranchAddress("n_RPC_hits_2", &n_RPC_hits_2_);
  fChain->SetBranchAddress("n_strip_hits_1", &n_strip_hits_1_);
  fChain->SetBranchAddress("n_strip_hits_2", &n_strip_hits_2_);
  fChain->SetBranchAddress("n_pixel_hits_1", &n_pixel_hits_1_);
  fChain->SetBranchAddress("n_pixel_hits_2", &n_pixel_hits_2_);
  fChain->SetBranchAddress("n_TOF_meas_1", &n_TOF_meas_1_);
  fChain->SetBranchAddress("n_TOF_meas_2", &n_TOF_meas_2_);
  fChain->SetBranchAddress("I_h_1", &I_h_1_);
  fChain->SetBranchAddress("I_h_2", &I_h_2_);
  fChain->SetBranchAddress("I_as_1", &I_as_1_);
  fChain->SetBranchAddress("I_as_2", &I_as_2_);
  fChain->SetBranchAddress("mass_I_h_1", &mass_I_h_1_);
  fChain->SetBranchAddress("mass_I_h_2", &mass_I_h_2_);
  fChain->SetBranchAddress("mass_ibeta_1", &mass_ibeta_1_);
  fChain->SetBranchAddress("mass_ibeta_2", &mass_ibeta_2_);
  fChain->SetBranchAddress("pt_err_1", &pt_err_1_);
  fChain->SetBranchAddress("pt_err_2", &pt_err_2_);
  fChain->SetBranchAddress("lumi_sec", &lumi_sec_);
  fChain->SetBranchAddress("event_nr", &event_nr_);
  fChain->SetBranchAddress("run_nr", &run_nr_);
  fChain->SetBranchAddress("quality_index_1", &quality_index_1_);
  fChain->SetBranchAddress("quality_index_2", &quality_index_2_);

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
*/
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

  if(pair) pair->clear();

}
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
