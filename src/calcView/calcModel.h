#ifndef CALCMODEL_H
#define CALCMODEL_H
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <vector>

namespace s21 {
class CalcModel {
 public:
  CalcModel() = default;

  void setXvalue(std::string input);
  void setInput(std::string input);
  void toPostfix();
  void solution();
  std::string getResult();
  void makeGraph(std::vector<double> &x, std::vector<double> &y, double x_start,
                 double x_end, double y_start, double y_end, std::string input);

 private:
  std::string input_;
  std::stack<std::string> stack_;
  std::queue<std::string> output_;
  std::string result_ = "";
  double x_value_ = 0;
  std::map<std::string, int> priority_ = {
      {"+", 1},   {"-", 1},    {"*", 2},    {"/", 2},    {"mod", 2},
      {"#", 3},   {"~", 3},    {"^", 4},    {"sin", 5},  {"cos", 5},
      {"tan", 5}, {"atan", 5}, {"asin", 5}, {"acos", 5}, {"ln", 5},
      {"log", 5}, {"sqrt", 5},
  };

  bool isDigit(char input);
  bool isDigit(std::string input);
  size_t readFunction(size_t index);
  size_t readOperator(size_t index);
  void readBrackets(size_t index);
  void solutionFunction();
  void solutionOperator();
  void checkResult();
};
}  // namespace s21

#endif  // CALCMODEL_H
