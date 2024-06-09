#ifndef CALCCONTROLLER_H
#define CALCCONTROLLER_H
#include "calcModel.h"

namespace s21 {
class CalcController {
 public:
  CalcController() = default;
  std::string calc(std::string input, std::string x);
  void makeGraph(std::vector<double> &x, std::vector<double> &y, double x_start,
                 double x_end, double y_start, double y_end, std::string input);

 private:
  CalcModel model_;
};
}  // namespace s21

#endif  // CALCCONTROLLER_H
