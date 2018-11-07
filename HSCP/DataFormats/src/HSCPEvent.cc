/*
#ifdef PROJECT_NAME
#include "m2n/HTTDataFormats/interface/HTTEvent.h"
#include "m2n/HTT/interface/GenInfoHelper.h"
#else
*/

#include "HSCPEvent.h"

// #endif

void CandidatePair::clear(){

  event_nr = 0;
  run_nr = 0;

  quality_index_1 = 0;
  quality_index_2 = 0;

  pt_1 = 0;
  pt_2 = 0;

  eta_1 = 0;
  eta_2 = 0;

  phi_1 = 0;
  phi_2 = 0;

  void set_quality_index(int index, int x){
	if (index == 1) quality_index_1 = x;
	if (index == 2) quality_index_2 = x;
	else {cout << "ERROR: The value of set_quality_index(?) should be 1 or 2!!!"; exit(0);}}
  
  void set_pt(int index, double x){
	if (index == 1) pt_1 = x;
	if (index == 2) pt_2 = x;
	else {cout << "ERROR: The value of set_pt(?) should be 1 or 2!!!"; exit(0);}}

  void set_eta(int index, double x){
	if (index == 1) eta_1 = x;
	if (index == 2) eta_2 = x;
	else {cout << "ERROR: The value of set_pt(?) should be 1 or 2!!!"; exit(0);}}

  void set_phi(int index, double x){
	if (index == 1) phi_1 = x;
	if (index == 2) pt_2 = x;
	else {cout << "ERROR: The value of set_pt(?) should be 1 or 2!!!"; exit(0);}}

  double CandidatePair::pt(int index){
	if (index == 1) return pt_1;
	if (index == 2) return pt_2;
	else {cout << "ERROR: The value of pt(?) should be 1 or 2!!!"; exit(0);}}

  double CandidatePair::eta(int index){
	if (index == 1) return eta_1;
	if (index == 2) return eta_2;
	else {cout << "ERROR: The value of eta(?) should be 1 or 2!!!"; exit(0);}}

  double CandidatePair::phi(int index){
	if (index == 1) return phi_1;
	if (index == 2) return phi_2;
	else {cout << "ERROR: The value of phi(?) should be 1 or 2!!!"; exit(0);}}

  int CandidatePair::quality_index(int index){
	if (index == 1) return quality_index_1;
	if (index == 2) return quality_index_2;
	else {cout << "ERROR: The value of quality_index(?) should be 1 or 2!!!"; exit(0);}}
};
