// COEN79 poly.cpp
#include <iostream>
#include "poly.h"
#include <iomanip>
#include <math.h>
#include <cassert>
#include <climits>
#include <cmath>
 
using namespace std;

namespace coen79_lab4 {
    void polynomial::update_current_degree() {
	for(int i = 0; i <= MAXIMUM_DEGREE; ++i) {
	    // set current_degree to i if i is greater and has a non-zero coefficient
            if(polynomials[i] != 0 && i > current_degree) {
                current_degree = i;
            }
        }
    }
    
    polynomial::polynomial(double c, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        // initialize current_degree
        current_degree = 0;
        // initialie values in array
        for(int i = 0; i <= MAXIMUM_DEGREE; ++i) {
            if(i == exponent)
            polynomials[exponent] = c;
            else
            polynomials[i] = 0.0;
        }
        update_current_degree();
    }
    
    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        polynomials[exponent] = coefficient;
        update_current_degree();
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        polynomials[exponent] += amount;
        update_current_degree();
    }

    void polynomial::clear() {
        // set all values in array to 0
        for(int i = 0; i <= MAXIMUM_DEGREE; i++)
            polynomials[i] = 0;
    	current_degree = 0;
    }

    double polynomial::coefficient(unsigned int exponent) const {
        if(exponent > MAXIMUM_DEGREE)
            return 0;
        return polynomials[exponent];
    }

    double polynomial::definite_integral(double x0, double x1) const {
        // initialize temporary polynomial that holds the antiderivative
        polynomial temp;
        temp = antiderivative();
        // evalute from x0 to x1 using the antiderivative
        return(temp.eval(x1)-temp.eval(x0));
    }
    
    unsigned int polynomial::degree( ) const {
        if(is_zero())
            return 0;
        return current_degree;
    }
    
    polynomial polynomial::derivative( ) const {
        polynomial d;
        // multiply each coefficient by its degree to get the derivative
        for(int i = MAXIMUM_DEGREE; i > 0; --i)
            d.polynomials[i] = (polynomials[i]*i);
        // shift coefficients back
        for(int j = 0; j <= MAXIMUM_DEGREE-1; j++)
            d.polynomials[j] = d.polynomials[j+1];
        d.update_current_degree();
        return d;
    }
    
    polynomial polynomial::antiderivative( ) const { 
        assert(degree() <= MAXIMUM_DEGREE);
        polynomial a;
        // divide each coefficient by its degree+1 to get the antiderivative
        for(int i = 0; i <= MAXIMUM_DEGREE; ++i)
            a.polynomials[i] = (polynomials[i]/(i+1));
        // shift coefficients forward
        for(int j = MAXIMUM_DEGREE; j > 0; --j)
            a.polynomials[j] = a.polynomials[j-1];
        a.polynomials[0] = 0.0;
        a.update_current_degree();
        return a;
    }
    
    double polynomial::eval(double x) const {
        double total = 0.0;
	// multiply each coefficient by x^degree
        for(int i = 0; i <= degree(); ++i)
            total += (polynomials[i]*pow(x,i));
        return total;
    }
    
    bool polynomial::is_zero() const {
        for(int i = 0; i <= MAXIMUM_DEGREE; i++) {
            if(polynomials[i] != 0)
                return false;
        }
        return true;
    }
    
    unsigned int polynomial::next_term(unsigned int e) const {
        // starting at the next degree, look for the degree with a non-zero coefficient
        for(int i = e+1; i <= MAXIMUM_DEGREE; i++) {
            if(polynomials[i] != 0.0)
                return i;
        }
        return 0;
    }
    
    unsigned int polynomial::previous_term(unsigned int e) const {
        // starting at previous degree, look for degree with non-zero coefficient
        for(int i = e-1; i >= 0; --i) {
            if(polynomials[i] != 0.0)
                return i;
        }
        return UINT_MAX;
    }

    double polynomial::operator() (double x) const {
        return eval(x);
    }
    
    // NON-MEMBER FUNCTIONS
    polynomial operator +(const polynomial& p1, const polynomial& p2) {
        polynomial p;
        for(int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++) {
            // add coefficients of p1 and p2 to p's coefficients
	    p.add_to_coef(p2.coefficient(i),i);
            p.add_to_coef(p1.coefficient(i),i);
        }
        return p;
    }
    polynomial operator -(const polynomial& p1, const polynomial& p2) {
        polynomial p;
        for(int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++) {
            // add coefficients of p2 from p
            p.add_to_coef(p2.coefficient(i),i);
            // subtract coefficients of p1 from p
            p.add_to_coef((p1.coefficient(i)*-1),i);
        }
        return p;
    }
    polynomial operator *(const polynomial& p1, const polynomial& p2) {
        polynomial p;
        // multiply term by term and add result to index i+j of resulting polynomial
        for(int i = 0; i <= p1.degree(); i++) {
            for(int j = 0; j <= p2.degree(); j++)
                p.add_to_coef(p1.coefficient(i)*p2.coefficient(j),i+j);
        }
        return p;
    }
    std::ostream& operator << (std::ostream& out, const polynomial& p) {
        // output 0 if polynomial is 0
        int pres = out.precision();
        if(p.is_zero()) {
            out << "0.0";
            return out;
        }
        for(int i = p.degree(); i > -1; --i) {
            if(p.coefficient(i) != 0) {  // only print non-zero coefficients
                // print corresponding sign
                if(p.coefficient(i) < 0)
                    out << " - "; 
                else if(i != p.degree() && p.coefficient(i) > 0)
                    out << " + ";
                // print coefficient with 1 decimal place
                out << fixed << setprecision(1) << fabs(p.coefficient(i));
                // if degree is 1, print only x
                // if degree is 0, pring only coefficient
                if(i != 1  && i != 0)
                    out << "x^" << i;
                else if(i == 1)
                    out << "x";
            }
        }
        out << setprecision(pres);
        return out;
    }
}
