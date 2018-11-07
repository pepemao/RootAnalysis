#ifndef WarsawAnalysis_HSCPDataFormats_HSCPEvent_h
#define WarsawAnalysis_HSCPDataFormats_HSCPEvent_h

#include "TLorentzVector.h"
#include "TVector3.h"
#include "TBits.h"
#include <map>
#include <vector>
#include <bitset>
#include <iostream>
#include <math> // #include <math.h> ?

#include "PropertyEnum.h"
#include "TriggerEnum.h"
#include "SelectionBitsEnum.h"
#include "AnalysisEnums.h"

///////////////////////////////////////////////////
///////////////////////////////////////////////////

/*
struct momentum_pair{  // px = pt*cos(phi), py = pt*sin(phi), pz = pt*sinh(eta), |p| = pt*cosh(eta)

	double pt_1, pt_2, eta_1, eta_2, phi_1, phi_2
	double px_1, px_2, py_1, py_2, pz_1, pz_2, p_tot_1, p_tot_2
};
*/ // załączenie funkcji wyciągającej pęd jest chyba prostsze za pomocą klasy, nie structa

class CandidatePair{

 public:

  CandidatePair(){clear();}

  ~CandidatePair(){}

  ///Data member setters

  void set_event_nr(int x){event_nr = x;}

  void set_run_nr(int x){run_nr = x;}

  void set_quality_index(int index, int x);
  
  void set_pt(int index, double x);

  void set_eta(int index, double x);

  void set_phi(int index, double x);

  ///Reset class data members
  void clear();

  ///Data member getters

  int get_event_nr() const {return event_nr;}

  int get_run_nr() const {return run_nr;}

  int quality_index(int index);

  double pt(int index);

  double eta(int index);

  double phi(int index);

 private:

  int event_nr, run_nr;

  int quality_index_1, quality_index_2;
  
  double pt_1, pt_2, eta_1, eta_2, phi_1, phi_2;

  double get_mom_1() const {return  pt_1*cosh(eta_1);}

  double get_mom_2() const {return  pt_2*cosh(eta_2);}

};

