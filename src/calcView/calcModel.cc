#include "calcModel.h"

namespace s21 {
void CalcModel::setInput(std::string input) { input_ = input; }

void CalcModel::setXvalue(std::string input) { x_value_ = std::stod(input); }

std::string CalcModel::getResult() { return result_; }

void CalcModel::toPostfix() {
  std::string str = "";
  for (size_t i = 0; i < input_.length(); i++) {
    if (isDigit(input_[i])) {
      str += input_[i];
      if ((i == input_.length() - 1) ||
          (!isDigit(input_[i + 1]) && input_[i] != '.')) {
        output_.push(str);
        str = "";
      }
    }
    readBrackets(i);
    i = readOperator(i);
    i = readFunction(i);
  }
  while (!stack_.empty()) {
    output_.push(stack_.top());
    stack_.pop();
  }
}

size_t CalcModel::readOperator(size_t index) {
  std::string str = "";
  std::string current(1, input_[index]);
  if ((input_[index] == '+' || input_[index] == '-') &&
      ((index == 0) || (input_[index - 1] == '('))) {
    while (!stack_.empty() && priority_[stack_.top()] >= 3) {
      output_.push(stack_.top());
      stack_.pop();
    }
    if (input_[index] == '+') {
      stack_.push("#");
    } else {
      stack_.push("~");
    }
  } else if ((priority_[current] <= 2 && priority_[current] != 0) ||
             input_[index] == 'm') {
    while (!stack_.empty() && priority_[stack_.top()] >= priority_[current] &&
           priority_[stack_.top()] != 0) {
      output_.push(stack_.top());
      stack_.pop();
    }
    str += input_[index];
    if (input_[index] == 'm') {
      str += "od";
      index += 2;
    }
    stack_.push(str);
    str = "";
  }
  return index;
}

size_t CalcModel::readFunction(size_t index) {
  std::string str;
  if ((isalpha(input_[index]) && input_[index] != 'X' &&
       input_[index] != 'd') ||
      input_[index] == '^') {
    while (!stack_.empty() && priority_[stack_.top()] == 5) {
      output_.push(stack_.top());
      stack_.pop();
    }
    if (isalpha(input_[index]) && input_[index] != 'm') {
      while (isalpha(input_[index])) {
        str += input_[index];
        index++;
      }
      stack_.push(str);
      index--;
    }
    if (input_[index] == '^') {
      stack_.push("^");
    }
  }
  return index;
}

void CalcModel::readBrackets(size_t index) {
  if (input_[index] == '(') {
    stack_.push("(");
  }
  if (input_[index] == ')') {
    while (!stack_.empty() && stack_.top() != "(") {
      output_.push(stack_.top());
      stack_.pop();
    }
    if (!stack_.empty() && stack_.top() == "(") {
      stack_.pop();
    }
  }
}

bool CalcModel::isDigit(char input) {
  bool res = false;
  if ((input >= '0' && input <= '9') || (input == 'X') || (input == '.')) {
    res = true;
  }
  return res;
}

bool CalcModel::isDigit(std::string input) {
  bool res = true;
  for (size_t i = 0; i < input.length() && res; i++) {
    if (!(input[i] >= '0' && input[i] <= '9') && !(input[i] == 'X') &&
        !(input[i] == '.')) {
      res = false;
    }
  }
  return res;
}

void CalcModel::solutionFunction() {
  if (priority_[output_.front()] == 5) {
    double num = std::stod(stack_.top());

    if (output_.front() == "sin") {
      stack_.top() = std::to_string(std::sin(num));
    } else if (output_.front() == "cos") {
      stack_.top() = std::to_string(std::cos(num));
    } else if (output_.front() == "tan") {
      stack_.top() = std::to_string(std::tan(num));
    } else if (output_.front() == "asin") {
      stack_.top() = std::to_string(std::asin(num));
    } else if (output_.front() == "acos") {
      stack_.top() = std::to_string(std::acos(num));
    } else if (output_.front() == "atan") {
      stack_.top() = std::to_string(std::atan(num));
    } else if (output_.front() == "sqrt") {
      stack_.top() = std::to_string(pow(num, 0.5));
    } else if (output_.front() == "ln") {
      stack_.top() = std::to_string(std::log(num));
    } else if (output_.front() == "log") {
      stack_.top() = std::to_string(std::log10(num));
    }
  }
}

void CalcModel::solutionOperator() {
  if (output_.front() == "~") {
    double num = std::stod(stack_.top());
    stack_.top() = std::to_string(num * (-1));
  }
  if (priority_[output_.front()] == 1 || priority_[output_.front()] == 2 ||
      priority_[output_.front()] == 4) {
    double num2 = std::stod(stack_.top());
    stack_.pop();
    double num1 = std::stod(stack_.top());

    if (output_.front() == "+") {
      stack_.top() = std::to_string(num1 + num2);
    } else if (output_.front() == "-") {
      stack_.top() = std::to_string(num1 - num2);
    } else if (output_.front() == "*") {
      stack_.top() = std::to_string(num1 * num2);
    } else if (output_.front() == "/") {
      stack_.top() = std::to_string(num1 / num2);
    } else if (output_.front() == "mod") {
      stack_.top() = std::to_string(std::fmod(num1, num2));
    } else if (output_.front() == "^") {
      stack_.top() = std::to_string(pow(num1, num2));
    }
  }
}

void CalcModel::solution() {
  while (!output_.empty()) {
    if (isDigit(output_.front())) {
      if (output_.front() == "X") {
        stack_.push(std::to_string(x_value_));
      } else {
        stack_.push(output_.front());
      }
    }
    solutionOperator();
    solutionFunction();
    output_.pop();
  }
  result_ = stack_.top();
  checkResult();
  stack_.pop();
}

void CalcModel::checkResult() {
  if (!result_.empty() && result_.find('.') != std::string::npos) {
    int index = result_.length() - 1;
    while (result_[index] == '0') {
      result_.pop_back();
      index--;
    }
    if (result_[index] == '.') {
      result_.pop_back();
    }
  }
  if (result_ == "-0") {
    result_ = "0";
  }
}

void CalcModel::makeGraph(std::vector<double> &x, std::vector<double> &y,
                          double x_start, double x_end, double y_start,
                          double y_end, std::string input) {
  x.clear();
  y.clear();
  input_ = input;
  double h = (x_end - x_start) / 20000;

  for (double X = x_start; X <= x_end; X += h) {
    x_value_ = X;
    toPostfix();
    solution();

    double yValue = std::stod(result_);
    if (!std::isnan(yValue)) {
      if (yValue >= y_start && yValue <= y_end) {
        x.push_back(X);
        y.push_back(yValue);
      }
    } else if (std::isnan(yValue) || std::isinf(yValue)) {
      x.push_back(X);
      y.push_back(std::numeric_limits<double>::quiet_NaN());
    }
  }
}
}  // namespace s21
