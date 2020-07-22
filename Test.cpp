#include "doctest.h"
#include "solver.hpp"

using namespace solver;
using namespace std;

#define EPSILON 0.0001

TEST_CASE("Check the correctness of addition")
{
      RealVariable x;

      CHECK_LT(abs(solve(2 + x == 5) - 3.0), EPSILON);
      CHECK_LT(abs(solve(x + 2 == 5) - 3.0), EPSILON);
      CHECK_LT(abs(solve(x + 2 + x + 2 == 10) - 3.0), EPSILON);
      CHECK_LT(abs(solve(x + x + x + x + x + x + x + x + x + x == 10) - 1.0), EPSILON);
      CHECK_LT(abs(solve(x == 6) - 6.0), EPSILON);
      CHECK_LT(abs(solve(2 + 10 + 15 + x + 5 + x == 0.0) + 16.0), EPSILON);
      CHECK_LT(abs(solve(x + x + x + x == 0.0)), EPSILON);
      CHECK_LT(abs(solve(4 + x + x + x + x == 0.0) + 1.0), EPSILON);

      ComplexVariable y;
      CHECK_LT(abs(solve(2 + y == 5).real() - 3.0), EPSILON);
      CHECK_LT(abs(solve(2 + y == 5).imag()), EPSILON);
      CHECK_LT(abs(solve(y + 2i == 5).imag() - 2), EPSILON);
      CHECK_LT(abs(solve(y + 2i == 5).real() - 5.0), EPSILON);
      CHECK_LT(abs(solve(y + 5i == y + y + 3i).real()), EPSILON);
      CHECK_LT(abs(solve(y + 5i == y + y + 3i).imag() - 2), EPSILON);
}

TEST_CASE("Check the correctness of subtraction")
{
      RealVariable x;

      CHECK_LT(abs(solve(x - 3 == 5) - 8.0), EPSILON);                                   //x = 8
      CHECK_LT(abs(solve(x - 2 - x - 2 - x - x == 10) + 7.0), EPSILON);                  //x = -7
      CHECK_LT(abs(solve(x - x - x - x - x - x - x - x - x - x == 8.0) + 1.0), EPSILON); // x = -8
      CHECK_LT(abs(solve(x == -6) + 6.0), EPSILON);
      CHECK_LT(abs(solve(x - 2 - 10 - 15 - x - 5 - x - x == 0.0) + 16.0), EPSILON);
      CHECK_LT(abs(solve(x - x - x - x - x - x == 0.0)), EPSILON);
      CHECK_LT(abs(solve(x - 3 - x - x - x - x == 0.0) + 1.0), EPSILON);
      CHECK_LT(abs(solve(x - 3 - x - x - x - x == -3.0)), EPSILON); //x = 0
      CHECK_LT(abs(solve(x - 3 - x - x - x - x == -12.0) - 3.0), EPSILON);

      ComplexVariable y;
      CHECK_LT(abs(solve(y - 2 == 5).real() - 7.0), EPSILON);
      CHECK_LT(abs(solve(y - 2 == 5).imag()), EPSILON);
      CHECK_LT(abs(solve(y - 15 - (y + 1i) == y - y - 5.0 - (y + 1i)).imag()), EPSILON);        //y.img = 0
      CHECK_LT(abs(solve(y - 15 - (y + 1i) == y - y - 5.0 - (y + 1i)).real() - 10.0), EPSILON); // y.real = 10
      CHECK_THROWS(abs(solve(y - y - 2 - y - (y + 5i) == y - y - 2 - y - (y + 5i))));           //no solution, should throw
      CHECK_THROWS(abs(solve(y - y - 2 - y - (y + 5i) == y - y - 2 - y - (y + 5i))));           //no solution, should throw
}

TEST_CASE("Check the correctness of multiplication")
{
      RealVariable x;

      CHECK_LT(abs(solve(3 * x == 6) - 2.0), EPSILON);                     //x = 2
      CHECK_LT(abs(solve(4 * (3 * x) == -24) + 2.0), EPSILON);             //x = -2
      CHECK_LT(abs(solve(5 * (4 * (3 * (2 * x))) == 120) - 1.0), EPSILON); //x = -1
      CHECK_LT(abs(solve(11 * x == 0)), EPSILON);                          //x = 0
      CHECK_LT(abs(solve(12 * x == -0)), EPSILON);                         //x = 0
      CHECK_LT(abs(solve(1 * x == 1) - 1.0), EPSILON);                     //x = 1

      ComplexVariable y;

      CHECK_LT(abs(solve(3 * y == 6).real() - 2.0), EPSILON);                             //y.real = 2
      CHECK_LT(abs(solve(3 * y == 6).imag()), EPSILON);                                   //y.imag = 0
      CHECK_THROWS(abs(solve(4 * y + 15i == y + 8i + 3 * y)));                            //no real solution
      CHECK_THROWS(abs(solve(4 * y + 15i == y + 8i + 3 * y)));                            //no real solution
      CHECK_LT(abs(solve(4 * y + 15i - 6 == 4 * y + 17i + 3 * y).imag() + 2), EPSILON);   //y.imag = - 2i
      CHECK_LT(abs(solve(4 * y + 15i - 6 == 4 * y + 17i + 3 * y).real() + 2.0), EPSILON); //y.real = -2
}

TEST_CASE("Check the correctness of division")
{
      RealVariable x;

      CHECK_LT(abs(solve(x / 3 == ((1 / 3.0))) - 1.0), EPSILON);                             //x = 1
      CHECK_LT(abs(solve(x / 2 / 3 == (1 / 3.0)) - 2.0), EPSILON);                           //x = 2
      CHECK_LT(abs(solve(x / 2 / 3 / 4 / 5 == (1 / 2.0 / 3.0 / 4.0 / 5.0)) - 1.0), EPSILON); //x = 1
      CHECK_LT(abs(solve(x / 72 == 0.0)), EPSILON);                                          //x = 0
      CHECK_LT(abs(solve(x / 1 == 1.0)) - 1.0, EPSILON);                                     //x = 1
      CHECK_THROWS(abs(solve(x / 0 == 0.0)));                                                //throw exception
      CHECK_THROWS(abs(solve(x / 5 / 0 == 5.0)));                                            //throw exception
      CHECK_THROWS(abs(solve(x / 5 / 0 / 10 == 1 / 5.0 / 10.0)));                            //throw exception

      ComplexVariable y;
      CHECK_LT(abs(solve(y / 3 == (1 / 3.0)).real() - 1.0), EPSILON);                                          //y.real = 1
      CHECK_LT(abs(solve(y / 3 == (1 / 3.0)).imag()), EPSILON);                                                //y.imag = 0
      CHECK_LT(abs(solve(y / 2 / 3.0 / 4.0 / 5.0 + 5i == (1 / 2.0 / 3.0 / 4.0 / 5.0)).real() - 1.0), EPSILON); //y.real = 1
      CHECK_LT(abs(solve(y / 2 / 3.0 / 4.0 / 5.0 + 5i == (1 / 2.0 / 3.0 / 4.0 / 5.0)).imag() - 5), EPSILON);   //y.imag = 5i
      CHECK_THROWS(abs(solve(y / 0.0 == 0)));                                                                  //throw exception
      CHECK_THROWS(abs(solve(y / 5.0 / 0.0 == 5)));                                                            //throw exception
}

TEST_CASE("Check the correctness of power")
{
      RealVariable x;

      CHECK_LT(abs(solve((x ^ 2) == 9) - 3.0), EPSILON);        //x = 3
      CHECK_LT(abs(solve(((x ^ 2) ^ 1) == 64) - 8.0), EPSILON); //x = 8
      CHECK_THROWS(abs(solve((x ^ 2) == -64)));                 // throw exception
      CHECK_THROWS(abs(solve(((x ^ 2) ^ 1) == -16)));           // throw exception
      CHECK_GT(abs(solve((x ^ 2) == 17) - 4.0), EPSILON);       // x = 4.12

      ComplexVariable y;
      CHECK_LT(abs(solve((y ^ 2) == 9).real() - 3.0), EPSILON); //y.real = 3
      CHECK_LT(abs(solve((y ^ 2) == 9).imag()), EPSILON);       //y.imag = 0
      CHECK_LT(abs(solve((y ^ 2) == -16).real()), EPSILON);     //y.real = 0
      bool check = (((abs(solve((y ^ 2) == -16).imag() - 4)) < EPSILON) ||
                    ((abs(solve((y ^ 2) == -16).imag() + 4)) < EPSILON));
      CHECK(check);
      CHECK_LT(abs(solve((y ^ 2) == -16).imag() - 4), EPSILON); //y.real = 4i
}

TEST_CASE("Check the correctness of equality")
{
      RealVariable x;

      CHECK_THROWS(abs(solve((x ^ 2) == (x ^ 2))));                                 //No real solution
      CHECK_LT(abs(solve(2 * x == 3 * x)), EPSILON);                                //x = 0
      CHECK_LT(abs(solve(2 * x == 3 * x + 15) + 15.0), EPSILON);                    //x = -15
      CHECK_LT(abs(solve(5 * x + 5 == 9 * x + 5)), EPSILON);                        //x = 0
      CHECK_LT(abs(solve(5 + x == 3 * x + 15) + 5.0), EPSILON);                     //x = -5
      CHECK_LT(abs(solve(3 * (x ^ 2) == 3 * (x ^ 2) + 3 * x + 15) + 5.0), EPSILON); //x = -5

      ComplexVariable y;
      CHECK_LT(abs(solve(y == 0).real()), EPSILON);                   //y.real = 0
      CHECK_LT(abs(solve(y == 0).imag()), EPSILON);                   //y.real = 0
      CHECK_THROWS(abs(solve((y ^ 2) == (y ^ 2))));                   //No real solution
      CHECK_THROWS(abs(solve((y ^ 2) == (y ^ 2))));                   //No real solution
      CHECK_THROWS(abs(solve(3 * y - (y + 6i) == 3 * y - (y + 6i)))); //No real solution
      CHECK_THROWS(abs(solve(3 * y - (y + 6i) == 3 * y - (y + 6i)))); //No real solution
}

TEST_CASE("Check the correctness of all operators together")
{
      RealVariable x;
      RealVariable x1;

      CHECK_LT(abs(solve(2 * x1 - 4 == 10) - 7.0), EPSILON); //x1 = 7
      bool check = (((abs(solve((x ^ 2) + 2 * x + 4.0 == 20 + 6.0 * x / 2 - x) - 4.0)) < EPSILON) ||
                    ((abs(solve((x ^ 2) + 2 * x + 4.0 == 20 + 6.0 * x / 2 - x) + 4.0)) < EPSILON));
      CHECK(check);                                                                              // x = 4 or -4
      CHECK_LT(abs(solve(3 * x - x - x - x - x + x + x + x + x - 4 == 10) - 14 / 3.0), EPSILON); // x = 14/3
      check = (((abs(solve((x ^ 2) + 3 - 4 == 0) - 1.0)) < EPSILON) ||
               ((abs(solve((x ^ 2) + 3 - 4 == 0) + 1.0)) < EPSILON));
      CHECK(check);                                                             // x = 1 o r-1
      CHECK_THROWS(abs(solve((x ^ 2) + 1 * x + 4 == 0.0) - 1.0));               //no real solution
      CHECK_LT(abs(solve(2 * x / 4 + 3 * x == -2 * x / 4 + 4) - 1.0), EPSILON); //x = 1
      CHECK_THROWS(abs(solve(2 * x / 4 + 3 * x == 2 * x / 4 + 3 * x)));         //no real solution
      CHECK_LT(abs(solve(x - 2 + 3 * x == x - 3 + 2 * x) + 1.0), EPSILON);      //x = -1
      CHECK_THROWS(abs(solve((x ^ 2) + 9 * x == x - 25) - 1));                  //no real solution
      CHECK_LT(abs(solve((x1 ^ 2) + 4 * x1 == -4) + 2.0), EPSILON);             // x1 = -2

      ComplexVariable y;
      check = (((abs(solve((y ^ 2) + 2 * y + 4 == 20 + 6 * y / 2 - y).real() - 4.0)) < EPSILON) ||
               ((abs(solve((y ^ 2) + 2 * y + 4 == 20 + 6 * y / 2 - y).real() + 4.0)) < EPSILON));
      CHECK(check);                                                                    // y.real = 4 or -4
      CHECK_LT(abs(solve((y ^ 2) + 2 * y + 4 == 20 + 6 * y / 2 - y).imag()), EPSILON); //y.imag = 0
      check = (((abs(solve((y ^ 2) + 9 * y == 1 * y - 25).imag() - 3)) < EPSILON) ||
               ((abs(solve((y ^ 2) + 9 * y == 1 * y - 25).imag() + 3)) < EPSILON));
      CHECK(check);                                                                                     // y.imag = 3i or -3i
      CHECK_LT(abs(solve((y ^ 2) + 9 * y == 1 * y - 25).real() + 4.0), EPSILON);                        //y.real = -4
      CHECK_LT(abs(solve(3 * y - y - y - y - y + y + y + y + y - 4 == 10).real() - 14 / 3.0), EPSILON); // y.real = 14/3
      CHECK_LT(abs(solve(3 * y - y - y - y - y + y + y + y + y - 4 == 10).imag()), EPSILON);            // y.imag = 0
      CHECK_LT(abs(solve(3 * y - (y + 1i) - (y + 1i) - 4 == 3 * y + 15i).real() + 2.0), EPSILON);       // y.real = -2
      CHECK_LT(abs(solve(3 * y - (y + 1i) - (y + 1i) - 4 == 3 * y + 15i).imag() + 17.0), EPSILON);      // y.imag = -17i
      check = (((abs(solve(4 * (y ^ 2) + 8 * y + 5 == 0).imag() - 0.5)) < EPSILON) ||
               ((abs(solve(4 * (y ^ 2) + 8 * y + 5 == 0).imag() + 0.5)) < EPSILON));
      CHECK(check);                                                                                   // y.imag = 0.5i or -0.5i
      CHECK_LT(abs(solve(4 * (y ^ 2) + 8 * y + 5 == 0).real() + 1.0), EPSILON);                       //y.real = -1
      CHECK_THROWS(abs(solve(2 * y / 4 + 3 * y - (6 * y + 1i) == 2 * y / 4 + 3 * y - (6 * y + 2i)))); //no real solution
      CHECK_THROWS(abs(solve(2 * y / 4 + 3 * y - (6 * y + 1i) == 2 * y / 4 + 3 * y - (6 * y + 2i)))); //no real solution
      CHECK_LT(abs(solve((y ^ 2) / 4 + 3 * y + 4i == (y ^ 2) / 4 + 2i).imag() - 2), EPSILON);         //y.imag = 2i
      CHECK_LT(abs(solve((y ^ 2) / 4 + 3 * y + 4i == -1 * (y ^ 2) + 2i).real()), EPSILON);            //y.real = 0
      check = (((abs(solve((y ^ 2) / 4.0 + y + 5 / 4.0 == 0).imag() - 1)) < EPSILON) ||
               ((abs(solve((y ^ 2) / 4.0 + y + 5 / 4.0 == 0).imag() + 1)) < EPSILON));
      CHECK(check);                                                                 // y.imag = i or -i
      CHECK_LT(abs(solve((y ^ 2) / 4.0 + y + 5 / 4.0 == 0).real() + 2.0), EPSILON); //y.real = -2.0
      CHECK_LT(abs(solve(y - 2 + 3 * y == y - 3 + 2 * y).real() + 1.0), EPSILON);   //y.real = -1
      CHECK_LT(abs(solve(y - 2 + 3 * y == y - 3 + 2 * y).imag()), EPSILON);         //y.imag = 0
      CHECK_LT(abs(solve((y ^ 2) + 4 * y == -4).real() + 2.0), EPSILON);            // y.real = -2
      CHECK_LT(abs(solve((y ^ 2) + 4 * y == -4).imag()), EPSILON);                  // y.imag = 0
}
