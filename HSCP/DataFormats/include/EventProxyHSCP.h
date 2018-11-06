#ifndef EVENTPROXYHSCP_h
#define EVENTPROXYHSCP_h

#include <string>
#include <typeinfo>
#include <vector>
#include "boost/shared_ptr.hpp"

#include "EventProxyBase.h"
#include "HSCPEvent.h"

#include "TBranch.h"

   class EventProxyHSCP: public EventProxyBase{

   public:

      EventProxyHSCP();
      virtual ~EventProxyHSCP();

      void init(std::vector<std::string> const& iFileNames);

      virtual EventProxyBase* clone() const;

      CandidatePair *pair;
  
      ///Enable branches to be read
      void enableBranches();

      ///Disable selected branches 
      void disableBranches();

      ///Reset the data members.
      void clear();
      
   };
#endif
