// Copyright 2021 Pinezhanin Evgeny
#ifndef MODULES_TASK_1_PINEZHANIN_E_TASK_1_TRAPEZOIDAL_RULE_H_
#define MODULES_TASK_1_PINEZHANIN_E_TASK_1_TRAPEZOIDAL_RULE_H_

double getIntegralTrapezoidalRuleParallel(double (*f)(double), double a, double b, int n);
double getIntegralTrapezoidalRuleSequential(double (*f)(double), double a, double b, int n);

#endif // MODULES_TASK_1_PINEZHANIN_E_TASK_1_TRAPEZOIDAL_RULE_H_
