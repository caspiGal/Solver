#ifndef SOLVER_A_SOLVER_HPP
#define SOLVER_A_SOLVER_HPP

#include <complex>

using namespace std;

namespace solver
{

      class RealVariable;
      class ComplexVariable;
      double solve(RealVariable);
      complex<double> solve(ComplexVariable);

      class Variable
      {
      protected:
            complex<double> _im;
            double _a; //Coefficient of x^2
            double _b; //Coefficient of x
            double _c; //Free number

            Variable() : _a(0.0), _b(1.0), _c(0.0), _im(0.0) {} //Default C'tor
            Variable(double a, double b, double c) : Variable(a, b, c, 0.0) {}
            Variable(double a, double b, double c, complex<double> im) : _a(a), _b(b), _c(c), _im(im) {}

            // Pure virtual => abstract class
            virtual void handle_imag(complex<double> &result, double a, double b, double discriminant) = 0;

      public:
            virtual complex<double> solve_function(void);
      };

      class RealVariable : public Variable
      {
            // Inherit Base's constructors, default ctor is Inherited by default(if not other Ctor implemented)
            using Variable::Variable;

      public:
            void handle_imag(complex<double> &result, double a, double b, double discriminant) override;

            //We want make it friend in order to enable private member of RealVariable.

            friend RealVariable operator+(const RealVariable &, const RealVariable &);

            friend RealVariable operator+(const RealVariable &, const double);

            friend RealVariable operator+(const double, const RealVariable &);

            friend RealVariable operator-(const RealVariable &, const RealVariable &);

            friend RealVariable operator-(const RealVariable &, const double);

            friend RealVariable operator*(const double, const RealVariable &);

            friend RealVariable operator/(const RealVariable &, const double);

            friend RealVariable operator^(RealVariable const &, const double);

            friend RealVariable operator==(const RealVariable &, const RealVariable &);

            friend RealVariable operator==(const RealVariable &, const double);
      };

      class ComplexVariable : public Variable
      {
            // Inherit Base's constructors, default ctor is Inherited by default(if not other Ctor implemented)
            using Variable::Variable;

      public:
            void handle_imag(complex<double> &result, double a, double b, double discriminant) override;

            friend ComplexVariable operator+(const ComplexVariable &, const ComplexVariable &);

            friend ComplexVariable operator+(const ComplexVariable &, const double);

            friend ComplexVariable operator+(const double, const ComplexVariable &);

            friend ComplexVariable operator+(const ComplexVariable &, complex<double>);

            friend ComplexVariable operator-(const ComplexVariable &, const ComplexVariable &);

            friend ComplexVariable operator-(const ComplexVariable &, const double);

            friend ComplexVariable operator*(const double, ComplexVariable const &);

            friend ComplexVariable operator/(ComplexVariable const &, const double);

            friend ComplexVariable operator^(ComplexVariable const &, const double);

            friend ComplexVariable operator==(const ComplexVariable &, const double);

            friend ComplexVariable operator==(const ComplexVariable &, const ComplexVariable &);
      };
} // namespace solver

#endif //SOLVER_A_SOLVER_HPP