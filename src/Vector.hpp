#pragma once

namespace Algebra
{
    class Vector {
    private:
        int _dim;
        double* _values;
    public:
        Vector();
        Vector(int dim);
        Vector(int dim, double* values);
        ~Vector();

        double* getValues() const;
        int getDimension() const;

        static Vector** gramSchmidt(int count, Vector** vectors);
        static double innerProduct(const Vector* a, const Vector* b);

        friend Vector operator+(const Vector& a, const Vector& b);
        friend Vector operator-(const Vector& a, const Vector& b);
        friend Vector operator*(const Vector& vector, const double scalar);
    private:

    };
} // namespace Algebra
