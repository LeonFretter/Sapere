#include <memory>

struct Equation
{
    int _dim;
    int* _constants;
    double _result;

    Equation(int dim, int* constants, double result) {
        _dim = dim;
        _constants = constants;
        _result = result;
    }
    ~Equation() {
        free(_constants);
    }

    friend Equation operator+(const Equation& a, const Equation& b) {
        const int dim = a._dim;
        int* resConstants = malloc(sizeof(int) * dim);
        for(int i=0; i<dim; i++) { resConstants[i] = a._constants[i] + b._constants[i]; }
        return Equation(dim, resConstants, a._result+b._result);
    }
    friend Equation operator*(const Equation& eq, const int scalar) {
        const int dim = eq._dim;
        int* resConstants = malloc(sizeof(int) * dim);
        for(int i=0; i<dim; i++) { resConstants[i] = eq._constants[i] * scalar; }
        return Equation(dim, resConstants, eq._result * (double)scalar);
    }
};

class Gaussian {
private:
    int _equationCount;
    Equation** _equations;
    bool _solved;
public:
    Gaussian(int equationCount, Equation** equations) {
        _equationCount = equationCount;
        _equations = equations;
        _solved = false;
    }

    void solve() {

    }
    void order() {
        for(int i=0; i<_equationCount; i++) {
            
        }
    }
private:
};

int main(int argc, char** argv) {
    int eq1[] = {1, 1, 1};
    int eq2[] = {1, 2, 3};
    int eq3[] = {3, 2, 1};
    double res1 = 6, res2 = 14, res3 = 10;

    Equation* equations[3] = {
        new Equation(3, eq1, res1),
        new Equation(3, eq2, res2),
        new Equation(3, eq3, res3)
    };

    Gaussian* gauss = new Gaussian(3, equations);
}


