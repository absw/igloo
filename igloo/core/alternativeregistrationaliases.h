
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_ALTERNATIVEREGISTRATIONALIASES_H
#define IGLOO_ALTERNATIVEREGISTRATIONALIASES_H

#include <igloo/core/registration.h>

// Spec aliases

#define Describe(contextName) \
IGLOO_CONTEXT_REGISTRATION(contextName)

#define Describe_Only(contextName) \
IGLOO_CONTEXT_REGISTRATION_ONLY(contextName)

#define Describe_Skip(contextName) \
IGLOO_CONTEXT_REGISTRATION_SKIP(contextName)

#define It(specName) \
IGLOO_SPEC_REGISTRATION(specName)  

#define It_Skip(specName) \
IGLOO_SPEC_REGISTRATION_SKIP(specName)  

#define It_Only(specName) \
IGLOO_SPEC_REGISTRATION_ONLY(specName)  

#define DescriptionAttribute(attributeName, attributeValue) \
IGLOO_CONTEXT_ATTRIBUTE_REGISTRATION(attributeName, attributeValue)

#define ScenarioAttribute(attributeName, attributeValue) \
IGLOO_CONTEXT_ATTRIBUTE_REGISTRATION(attributeName, attributeValue)

/* All below is Bluefruit BDD extensions */

#define Construct \
    static void SetUpContext()

#define End };

#define CAT__(X,Y) X##Y
#define CAT_(X,Y) CAT__( X, Y)
#define DBG_(line) std::cout << line << std::endl;

#define FeatureLog(stepDescription) \
static std::vector<std::string>& MetaLog() \
{ \
    static std::vector<std::string> ret; \
    if(ret.size()==0) ret.push_back("Feature: " stepDescription); \
    return ret; \
}               

#define Metalog Root().MetaLog()

#define ContextSet(ClassName) \
   static void SetUpContext() {} \
   static void TearDownContext{}

#define HandlerSet(ClassName) \
static ClassName *HRef() \
{ \
    static ClassName instance; \
    return &instance; \
} \

#define Handler(ClassName) \
    HandlerSet(ClassName) 
 
#define FeatureImpl(uid, stepDescription) \
    IGLOO_CONTEXT_REGISTRATION(uid) \
    {FeatureLog(stepDescription)

#define Feature(stepDescription) \
    FeatureImpl(CAT_(F_, __COUNTER__),stepDescription)

#define MetaLogPush(source,stepDescription) \
    {std::string src = source;  \
     std::string desc = stepDescription; \
     HRef()->SetCurrentLine(stepDescription); \
     HRef()->ExtractParameters(); \
     Metalog.push_back(src + " " + desc);

#define WhenImpl(uid,stepDescription) \
    IGLOO_SPEC_REGISTRATION(uid) \
    MetaLogPush("When:",stepDescription)

#define When(stepDescription) \
    WhenImpl(CAT_(F_, __COUNTER__),stepDescription)

#define ThenImpl(uid,stepDescription) \
    IGLOO_SPEC_REGISTRATION(uid) \
    MetaLogPush("Then:",stepDescription)

#define Then(stepDescription) \
    ThenImpl(CAT_(F_, __COUNTER__),stepDescription)

#define AndImpl(uid,stepDescription) \
    IGLOO_SPEC_REGISTRATION(uid) \
    MetaLogPush("And:",stepDescription)

#define And(stepDescription) \
    AndImpl(CAT_(F_, __COUNTER__),stepDescription)

#define GivenImpl(uid,stepDescription) \
    IGLOO_SPEC_REGISTRATION(uid) \
    MetaLogPush("Given:",stepDescription)

#define Given(stepDescription) \
    GivenImpl(CAT_(F_, __COUNTER__),stepDescription)

#define ScenarioImpl(uid,stepDescription) \
    IGLOO_SPEC_REGISTRATION(uid) \
    MetaLogPush("Scenario:",stepDescription)

#define Scenario(stepDescription) \
    ScenarioImpl(CAT_(F_, __COUNTER__),stepDescription)

#define SweepImpl(uid,stepDescription) \
    IGLOO_SPEC_REGISTRATION(uid) \
    MetaLogPush("Sweep:",stepDescription)

#define Sweep(stepDescription) \
    SweepImpl(CAT_(F_, __COUNTER__),stepDescription)

#define TagsImpl(uid,stepDescription) \
    IGLOO_SPEC_REGISTRATION(uid) \
    MetaLogPush("Tags:",stepDescription)

#define Tags(stepDescription) \
    TagsImpl(CAT_(F_, __COUNTER__),stepDescription) End 

#define CurrStep Root().MetaLog()[Root().MetaLog().size() - 1]
#define ErrEcho cout << " !" + CurrStep + "! "<< endl
#define StepEcho cout << CurrStep << endl;};
#define _StepEcho cout << CurrStep << endl;
#define StepPlay(handler) \
   _StepEcho \
   HRef()->handler(); End



#endif
