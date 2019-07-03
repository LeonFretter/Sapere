#include "Vector.hpp"
#include <memory>

namespace Algebra
{
    /* constructors/destructors */

    Vector::Vector() {}
    Vector::Vector(int dim) {
        _dim = dim;
        _values = (double*)malloc(dim*sizeof(double));
        for(int i=0; i<dim; i++) { _values[i] = 1; }
    }
    Vector::Vector(int dim, double* values) {
        _dim = dim;
        _values = (double*)malloc(dim*sizeof(double));
        for(int i=0; i<dim; i++) { _values[i] = values[i]; }
    }
    Vector::~Vector() {
        free(_values);
    }

    /* public */

    double* Vector::getValues() const { return _values; }
    int Vector::getDimension() const { return _dim; }




    /* static */

    Vector** Vector::gramSchmidt(int count, Vector** vectors) {
        Vector* result[count];
        result[0] = vectors[0];

        Vector* test = vectors[0];

        //start from i=1, as first vector will remain the same
        for(int i=1; i<count; i++) {
            Vector proj = *result[i-1] * (innerProduct(vectors[i], result[i-1]) / innerProduct(result[i-1], result[i-1]));
            Vector* v = vectors[i];
            Vector res = *v - proj;
        }
    }
    double Vector::innerProduct(const Vector* a, const Vector* b){
        int dim = a->getDimension();
        if(dim != b->getDimension()) throw "Trying to calculate inner-product of vectors of unequal dimension!";

        double* aVals = a->getValues();
        double* bVals = b->getValues();
        double result = 0;
        
        for(int i=0; i<dim; i++) { result += aVals[i] * bVals[i]; }

        return result;
    }



    /* operator-overloading */

    Vector operator+(const Vector& a, const Vector& b) {
        int dim = a.getDimension();
        if(dim != b.getDimension()) throw "Trying to add vectors of unequal dimension!";
        
        double* aVals = a.getValues(); 
        double* bVals = b.getValues();
        double resVals[dim];

        for(int i=0; i<dim; i++) { resVals[i] = aVals[i] + bVals[i]; }

        return Vector(dim, resVals);
    }
    Vector operator-(const Vector& a, const Vector& b) {
        int dim = a.getDimension();
        if(dim != b.getDimension()) throw "Trying to subtract vectors of unequal dimension!";

        double* aVals = a.getValues(); 
        double* bVals = b.getValues();
        double resVals[dim];

        for(int i=0; i<dim; i++) { resVals[i] = aVals[i] - bVals[i]; }

        return Vector(dim, resVals);
    }
    Vector operator*(const Vector& vector, const double scalar) {
        int dim = vector.getDimension();
        double* vals = vector.getValues();
        double resVals[dim];
        for(int i=0; i<dim; i++) { resVals[i] = vals[i] * scalar; }
        return Vector(dim, resVals);
    }
} // namespace Algebra
