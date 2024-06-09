#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "calcView/calcController.h"

class CalcTest : public ::testing::Test {
 protected:
  s21::CalcController test;
};

TEST_F(CalcTest, test1) {
  std::string result = test.calc("546.021598745+78.2356487", "45");
  EXPECT_TRUE(result == "624.257247");
}

TEST_F(CalcTest, test2) {
  std::string result = test.calc("546.021598745-78.2356487", "");
  EXPECT_TRUE(result == "467.78595");
}

TEST_F(CalcTest, test3) {
  std::string result1 = test.calc("45^5", "");
  std::string result2 = test.calc("-7^5", "");
  std::string result3 = test.calc("45^(-3)", "");
  std::string result4 = test.calc("0.123^0.456", "");
  std::string result5 = test.calc("2^3^3", "");
  std::string result6 = test.calc("2^(2*3)", "");
  EXPECT_TRUE(result1 == "184528125");
  EXPECT_TRUE(result2 == "-16807");
  EXPECT_TRUE(result3 == "0.000011");
  EXPECT_TRUE(result4 == "0.384589");
  EXPECT_TRUE(result5 == "134217728");
  EXPECT_TRUE(result6 == "64");
}

TEST_F(CalcTest, test4) {
  std::string result1 = test.calc("(75.02456-0.456)*0.45", "");
  std::string result2 = test.calc("(75.02456-0.456)*(123+456)", "");
  EXPECT_TRUE(result1 == "33.555852");
  EXPECT_TRUE(result2 == "43175.19624");
}

TEST_F(CalcTest, test5) {
  std::string result1 = test.calc("(X-0.456)*0.45", "0.98");
  std::string result2 = test.calc("(75.02456-0.456)*X^X", "0.5");
  EXPECT_TRUE(result1 == "0.2358");
  EXPECT_TRUE(result2 == "52.727951");
}

TEST_F(CalcTest, test6) {
  std::string result = test.calc(
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))",
      "");
  EXPECT_TRUE(result == "-30.072166");
}

TEST_F(CalcTest, test7) {
  std::string result = test.calc("-0.45/(-0.02*78)", "");
  EXPECT_TRUE(result == "0.288462");
}

TEST_F(CalcTest, test8) {
  std::string result = test.calc("0.25/(0.02*45)", "");
  EXPECT_TRUE(result == "0.277778");
}

TEST_F(CalcTest, test9) {
  std::string result = test.calc("90mod(45+7)", "");
  EXPECT_TRUE(result == "38");
}

TEST_F(CalcTest, test10) {
  std::string result = test.calc("90mod45+7", "");
  EXPECT_TRUE(result == "7");
}

TEST_F(CalcTest, test11) {
  std::string result = test.calc("90mod80mod7", "");
  EXPECT_TRUE(result == "3");
}

TEST_F(CalcTest, test12) {
  std::string result = test.calc("111.23mod78+0.5", "");
  EXPECT_TRUE(result == "33.73");
}

TEST_F(CalcTest, test13) {
  std::string result = test.calc("111.23modX+0.5", "7");
  EXPECT_TRUE(result == "6.73");
}

TEST_F(CalcTest, test14) {
  std::string result = test.calc("sin(X)*0.789", "0.78");
  EXPECT_TRUE(result == "0.554887");
}

TEST_F(CalcTest, test15) {
  std::string result = test.calc("sin(sin(X^0.7))", "4.02");
  EXPECT_TRUE(result == "0.456073");
}

TEST_F(CalcTest, test16) {
  std::string result = test.calc("sin(78mod(10+0.45))", "");
  EXPECT_TRUE(result == "-0.990547");
}

TEST_F(CalcTest, test17) {
  std::string result = test.calc("cos(X)*0.789", "0.78");
  EXPECT_TRUE(result == "0.560911");
}

TEST_F(CalcTest, test18) {
  std::string result = test.calc("cos(sin(X^0.7))", "4.02");
  EXPECT_TRUE(result == "0.889943");
}

TEST_F(CalcTest, test19) {
  std::string result = test.calc("cos(78mod(10+0.45))", "0");
  EXPECT_TRUE(result == "0.137177");
}

TEST_F(CalcTest, test20) {
  std::string result =
      test.calc("tan(-X)*sin(X)*cos(-X)*atan(X)*asin(-X)*acos(X)", "0.56");
  EXPECT_TRUE(result == "0.083595");
}

TEST_F(CalcTest, test21) {
  std::string result = test.calc("asin(-X)", "-0.78923");
  EXPECT_TRUE(result == "0.909554");
}

TEST_F(CalcTest, test22) {
  std::string result = test.calc("acos(-X)", "-0.78923");
  EXPECT_TRUE(result == "0.661242");
}

TEST_F(CalcTest, test23) {
  std::string result = test.calc("asin(0.236)^acos(-1)", "");
  EXPECT_TRUE(result == "0.011038");
}

TEST_F(CalcTest, test24) {
  std::string result = test.calc("asin(0.236)/acos(-1)*sin(-85.65)", "");
  EXPECT_TRUE(result == "0.055809");
}

TEST_F(CalcTest, test25) {
  std::string result = test.calc("sqrt(asin(0.5)/acos(-0.002))", "-789.23");
  EXPECT_TRUE(result == "0.576984");
}

TEST_F(CalcTest, test26) {
  std::string result = test.calc("tan(-X)", "-789.23");
  EXPECT_TRUE(result == "0.825746");
}

TEST_F(CalcTest, test27) {
  std::string result = test.calc("tan(65)^(-2)/9.01", "");
  EXPECT_TRUE(result == "0.051359");
}

TEST_F(CalcTest, test28) {
  std::string result = test.calc("tan(tan(-X))", "100.023");
  EXPECT_TRUE(result == "0.622348");
}

TEST_F(CalcTest, test29) {
  std::string result = test.calc("atan(X)", "-789.23");
  EXPECT_TRUE(result == "-1.569529");
}

TEST_F(CalcTest, test30) {
  std::string result = test.calc("atan(65)^2/9.01", "");
  EXPECT_TRUE(result == "0.268514");
}

TEST_F(CalcTest, test31) {
  std::string result = test.calc("atan(atan(X))", "100.023");
  EXPECT_TRUE(result == "1.000988");
}

TEST_F(CalcTest, test32) {
  std::string result = test.calc("sqrt(X)", "0.001");
  EXPECT_TRUE(result == "0.031623");
}

TEST_F(CalcTest, test33) {
  std::string result =
      test.calc("sqrt(-1*(cos(89)*sin(67)*sqrt(97)+0.235))", "");
  EXPECT_TRUE(result == "2.015863");
}

TEST_F(CalcTest, test34) {
  std::string result = test.calc("sqrt(sqrt(sqrt(56.555)))", "");
  EXPECT_TRUE(result == "1.655995");
}

TEST_F(CalcTest, test35) {
  std::string result1 = test.calc("ln(58.456)", "");
  std::string result2 = test.calc("log(0.000007)", "");
  EXPECT_TRUE(result1 == "4.068274");
  // EXPECT_TRUE(result2 == "-5.154902");
}

TEST_F(CalcTest, test36) {
  std::string result = test.calc("sin(X)*cos(X)*ln(X)^3", "45");
  EXPECT_TRUE(result == "24.656958");
}

TEST_F(CalcTest, test37) {
  std::string result = test.calc("log(32.02)^ln(10)", "");
  EXPECT_TRUE(result == "2.564913");
}

TEST_F(CalcTest, test38) {
  std::string result1 = test.calc("log(1)", "");
  std::string result2 = test.calc("log(0.0001)", "");
  EXPECT_TRUE(result1 == "0");
  EXPECT_TRUE(result2 == "-4");
}

TEST_F(CalcTest, test39) {
  std::string result = test.calc("log(X)^3", "45");
  EXPECT_TRUE(result == "4.518418");
}

TEST_F(CalcTest, test40) {
  std::string result = test.calc("log(32.02)^log(4)", "");
  EXPECT_TRUE(result == "1.279266");
}

TEST_F(CalcTest, test41) {
  std::string result = test.calc("sin(-0)", "");
  EXPECT_TRUE(result == "0");
}

TEST_F(CalcTest, test42) {
  std::string result = test.calc("sin(-45*(-23))", "");
  EXPECT_TRUE(result == "-0.988046");
}

TEST_F(CalcTest, test43) {
  std::string result = test.calc("tan(+2)", "");
  EXPECT_TRUE(result == "-2.18504");
}

TEST_F(CalcTest, test44) {
  std::string result = test.calc("2^3^ln(2)", "");
  EXPECT_TRUE(result == "4.412163");
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}