
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_CONTEXTRUNNER_H
#define IGLOO_CONTEXTRUNNER_H

namespace igloo {

  
  struct BaseContextRunner : public MetaData
  {
    BaseContextRunner(const std::string& contextName) : contextName_(contextName) {}
    virtual ~BaseContextRunner() {}
    void Run(TestResults& results, TestListener& testListener) const
    {
      testListener.ContextRunStarting(ContextName(), *this);

      RunContext(results);
      
      testListener.ContextRunEnded(ContextName(), *this);
    }

    const std::string& ContextName() const
    {
      return contextName_;
    }

    protected:
    virtual void RunContext(TestResults& results) const = 0;

    private:
      std::string contextName_;
  };
  
  template <typename ContextRegistryType, typename ContextType>
  struct ContextSelector
  {
    typedef ContextRegistryType ContextToExecute;
    typedef ContextType ContextToCreate;
  };
  
  template <typename ContextType>
  struct ContextSelector<void, ContextType>
  {
    typedef ContextType ContextToExecute;
    typedef ContextType ContextToCreate;
  };

  template <typename ContextRegistryType, typename ContextType>
  class ContextRunner : public BaseContextRunner
  {
  public:   
    typedef typename ContextSelector<ContextRegistryType, ContextType>::ContextToExecute CTE;
    typedef typename ContextSelector<ContextRegistryType, ContextType>::ContextToCreate CTC;

    ContextRunner(const std::string& contextName) : BaseContextRunner(contextName) {}

    void InstantiateContext() const
    {
      CTC ctc;
    }
    
    void RunContext(TestResults& results) const
    {
      typedef ContextRegistry<CTE> CR;

      CR::template Run<CTC>(ContextName(), results);
    }

    const std::string& GetMetaData(const std::string& name) const
    {
      return ContextMetaData<CTE>::Get(name);
    }
  };
}

#endif
