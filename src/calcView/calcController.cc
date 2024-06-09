#include "calcController.h"

namespace s21 {
std::string CalcController::calc(std::string input, std::string x) {
  if (!x.empty() && input.find("X") != std::string::npos) {
    model_.setXvalue(x);
  }
  model_.setInput(input);
  model_.toPostfix();
  model_.solution();

  std::string res = model_.getResult();
  return res;
}

void CalcController::makeGraph(std::vector<double> &x, std::vector<double> &y,
                               double x_start, double x_end, double y_start,
                               double y_end, std::string input) {
  model_.makeGraph(x, y, x_start, x_end, y_start, y_end, input);
}
}  // namespace s21
