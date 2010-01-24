#ifndef IGLOO_EXPRESSIONITEM_H
#define IGLOO_EXPRESSIONITEM_H

#include "operators/operator.h"

namespace igloo {
       
  typedef std::stack<bool> ResultStack;
  typedef std::stack<const Operator*> OperatorStack_;

  template <typename ExpressionType, typename ExpressionItemType>
    struct expression_evaluation_trait
  {
    template <typename ActualType>
    static void Evaluate(const ExpressionType& expression, const ActualType& actual, ResultStack& resultStack, OperatorStack_&)
    {
      resultStack.push(expression(actual));
    }
  };

  template <typename ExpressionItemType>
    struct expression_evaluation_trait<NotOperator, ExpressionItemType>
  {
    template <typename ActualType>
    static void Evaluate(const Operator& expression, const ActualType&, ResultStack& resultStack, OperatorStack_& operatorStack)
    {
      expression.Evaluate(operatorStack, resultStack);
    }
  };     
 
  template <typename ExpressionItemType>
    struct expression_evaluation_trait<OrOperator, ExpressionItemType>
  {
    template <typename ActualType>
    static void Evaluate(const Operator& expression, const ActualType&, ResultStack& resultStack, OperatorStack_& operatorStack)
    {
      expression.Evaluate(operatorStack, resultStack);
    }
  };

  template <typename ExpressionItemType>
    struct expression_evaluation_trait<AndOperator_OLD, ExpressionItemType>
  {
    template <typename ActualType>
    static void Evaluate(const Operator& expression, const ActualType&, ResultStack& resultStack, OperatorStack_& operatorStack)
    {
      expression.Evaluate(operatorStack, resultStack);
    }
  };

  class NoopExpressionItem
  {
  public:
    template <typename ActualType>
      void Evaluate(const ActualType&, ResultStack&, OperatorStack_&) const
    {
    }

    void ToString(std::string&, bool) const {}
  };
  
  template <typename ExpressionType, typename PreviousExpressionItemType>
  class ExpressionItem
  {
  public:
    typedef ExpressionItem<ExpressionType, PreviousExpressionItemType> MyType;

    ExpressionItem(const MyType& rhs) : m_expression(rhs.m_expression), m_previous(rhs.m_previous) {}
    explicit ExpressionItem(const ExpressionType& expression, const PreviousExpressionItemType& previous) : m_expression(expression), m_previous(previous) {}

    template <typename ActualType>
      bool Evaluate(const ActualType& actual) const
    {
      ResultStack resultStack;
      OperatorStack_ operatorStack;

      Evaluate(actual, resultStack, operatorStack);
      Operator::EvaluateOperatorsOnStack(operatorStack, resultStack);

      return resultStack.top();
    }

    void ToString(std::string& str, bool last = true) const
    {
      m_previous.ToString(str, false);
			str += Stringize(m_expression);

      if(!last)
      {
        str += " ";
      }
    }

    template <typename ActualType>
      void Evaluate(const ActualType& actual, ResultStack& resultStack, OperatorStack_& operatorStack) const
    {
      m_previous.Evaluate(actual, resultStack, operatorStack);
      expression_evaluation_trait<ExpressionType, MyType>::Evaluate(m_expression, actual, resultStack, operatorStack);
    }

  public:
    ExpressionType m_expression;
    PreviousExpressionItemType m_previous;
  };

}

#endif
