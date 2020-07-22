#include "solver.hpp"
#include <iostream>
#include <exception>

namespace solver
{

      // Variable class
      complex<double> Variable::solve_function(void)
      {
            double a(_a), b(_b), c(_c);
            double discriminant = b * b - 4 * a * c;
            complex<double> result(0.0, 0);

            if (a == 0.0 && b == 0.0)
            {
                  throw invalid_argument("No real solution exsits");
            }
            if (a != 0)
            {
                  if (discriminant >= 0)
                  {                                                   // Linear equation
                        result = (-b + sqrt(discriminant)) / (2 * a); // One solution
                  }
                  else
                  { // disc is negative
                        handle_imag(result, a, b, discriminant);
                  }
            }
            else
            {
                  result.real(-c / b); // The only solution we have
                  result.imag(_im.imag());
            }
            return result;
      }
      //RealVariable class

      RealVariable operator+(const RealVariable &r1, const RealVariable &r2)
      {
            return RealVariable(r1._a + r2._a, r1._b + r2._b, r1._c + r2._c);
      }

      RealVariable operator+(const RealVariable &r, const double num)
      {
            return RealVariable(r._a, r._b, r._c + num);
      }

      RealVariable operator+(const double num, const RealVariable &r)
      {
            return r + num;
      }
      RealVariable operator-(const RealVariable &r1, const RealVariable &r2)
      {
            return RealVariable(r1._a - r2._a, r1._b - r2._b, r1._c - r2._c);
      }

      RealVariable operator-(const RealVariable &r, const double num)
      {
            return RealVariable(r._a, r._b, r._c - num);
      }

      RealVariable operator*(const double num, const RealVariable &r)
      {
            return r._a > 0 ? RealVariable(r._a * num, r._b, r._c) : RealVariable(r._a, num * r._b, r._c);
      }

      RealVariable operator/(const RealVariable &r, const double num)
      {
            if (num == 0)
            {
                  throw invalid_argument("Can't divide by zero");
            }

            return r._a > 0 ? RealVariable(r._a / num, r._b, r._c) : RealVariable(r._a, r._b / num, r._c);
      }

      RealVariable operator^(RealVariable const &r, const double num)
      {
            if (num == 0.0)
            {
                  throw invalid_argument("Can't power by zero");
            }
            return RealVariable(1, 0, r._c); //Sign it as x^2(we don't want 1x also)
      }

      RealVariable operator==(const RealVariable &r1, const RealVariable &r2)
      {
            return r1 - r2;
      }

      RealVariable operator==(const RealVariable &r, const double num)
      {
            return r - num;
      }

      void RealVariable::handle_imag(complex<double> &result, double a, double b, double discriminant)
      {
            throw exception(invalid_argument("There is no solution"));
      }

      double solve(RealVariable r)
      {
            return r.solve_function().real();
      }

      //ComplexVariable class

      ComplexVariable operator+(const ComplexVariable &c1, const ComplexVariable &c2)
      {
            return ComplexVariable(c1._a + c2._a, c1._b + c2._b, c1._c + c2._c, c1._im + c2._im);
      }

      ComplexVariable operator+(const ComplexVariable &c, const double num)
      {
            return ComplexVariable(c._a, c._b, c._c + num, c._im);
      }

      ComplexVariable operator+(const double num, const ComplexVariable &c)
      {
            return c + num;
      }

      ComplexVariable operator+(const ComplexVariable &c, complex<double> num)
      {
            return ComplexVariable(c._a, c._b, c._c, c._im + num);
      }

      ComplexVariable operator-(const ComplexVariable &c1, const ComplexVariable &c2)
      {
            return ComplexVariable(c1._a - c2._a, c1._b - c2._b, c1._c - c2._c, c1._im - c2._im);
      }

      ComplexVariable operator-(const ComplexVariable &c, const double num)
      {
            return ComplexVariable(c._a, c._b, c._c - num, c._im);
      }

      ComplexVariable operator*(const double num, ComplexVariable const &c)
      {
            return c._a > 0 ? ComplexVariable(c._a * num, c._b, c._c, c._im) : ComplexVariable(c._a, c._b * num, c._c, c._im);
      }

      ComplexVariable operator/(ComplexVariable const &c, const double num)
      {
            if (num == 0)
            {
                  throw invalid_argument("Can't divide by zero");
            }

            return c._a > 0 ? ComplexVariable(c._a / num, c._b, c._c, c._im) : ComplexVariable(c._a, c._b / num, c._c, c._im);
      }

      ComplexVariable operator^(ComplexVariable const &c, const double num)
      {
            if (num == 0)
            {
                  throw invalid_argument("can't power by zero");
            }
            return ComplexVariable(1, 0, c._c, c._im);
      }

      ComplexVariable operator==(const ComplexVariable &c, const double num)
      {
            return ComplexVariable(c._a, c._b, c._c - num, c._im);
      }

      ComplexVariable operator==(const ComplexVariable &c1, const ComplexVariable &c2)
      {
            return ComplexVariable(c1._a - c2._a, c1._b - c2._b, c1._c - c2._c, c1._im - c2._im);
      }

      void ComplexVariable::handle_imag(complex<double> &result, double a, double b, double discriminant)
      {
            result.real(-b / (2 * a));
            result.imag(sqrt(-discriminant) / (2 * a));
      }

      complex<double> solve(ComplexVariable c)
      {
            return c.solve_function();
      }

} // namespace solver