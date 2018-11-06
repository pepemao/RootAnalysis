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

};
