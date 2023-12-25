
#include <iostream>
#include <cmath>
using namespace std;

double f0(double x[4], double t, double L) {            // function
    return x[0] * (exp(-x[1] * t) + exp(-x[1] * (L - t))) + x[2] * pow(-1., t) * (exp(-x[3] * t) + exp(-x[3] * (L - t)));
}

void f(double x[4], double y[4], double t, double L) {      //Set of functions
    y[0] = f0(x, t + 0, L) - 0.2047 * 1000;
    y[1] = f0(x, t + 1, L) - 0.1473 * 1000;
    y[2] = f0(x, t + 2, L) - 0.1059 * 1000;
    y[3] = f0(x, t + 3, L) - 0.7634 * 100;
    //cout << y[0] << "\n";
}

void df(double x[4], double y[4][4], double t, double L) {      // Jacobian
    for (int i = 0; i < 4; i++) {
        y[0][i] = exp(-x[1] * (t + i)) + exp(-x[1] * (L - (t + i)));
        y[1][i] = -x[0] * ((t + i) * exp(-x[1] * (t + i)) + (L - (t + i)) * exp(-x[1] * (L - (t + i))));
        y[2][i] = pow((-1.),(t + i)) * (exp(-x[3] * (t + i)) + exp(-x[3] * (L - (t + i))));
        y[3][i] = -x[2] * pow((-1.), (t + i)) * ((t + i) * exp(-x[3] * (t + i)) + (L - (t + i)) * exp(-x[3] * (L - (t + i))));
    }
}

bool InvertMatrix(double mm[4][4], double invOutttt[4][4])   // Finding invert matrix
{
    double m[16];
    double invOut[16];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i*4 + j] = mm[j][i];
        }
    }



    double inv[16], det;
    int i;


    inv[0] = m[5] * m[10] * m[15] -
        m[5] * m[11] * m[14] -
        m[9] * m[6] * m[15] +
        m[9] * m[7] * m[14] +
        m[13] * m[6] * m[11] -
        m[13] * m[7] * m[10];

    inv[4] = -m[4] * m[10] * m[15] +
        m[4] * m[11] * m[14] +
        m[8] * m[6] * m[15] - 
        m[8] * m[7] * m[14] - 
        m[12] * m[6] * m[11] +
        m[12] * m[7] * m[10];

    inv[8] = m[4] * m[9] * m[15] -
        m[4] * m[11] * m[13] -
        m[8] * m[5] * m[15] +
        m[8] * m[7] * m[13] +
        m[12] * m[5] * m[11] -
        m[12] * m[7] * m[9];

    inv[12] = -m[4] * m[9] * m[14] +
        m[4] * m[10] * m[13] +
        m[8] * m[5] * m[14] -
        m[8] * m[6] * m[13] -
        m[12] * m[5] * m[10] +
        m[12] * m[6] * m[9];

    inv[1] = -m[1] * m[10] * m[15] +
        m[1] * m[11] * m[14] +
        m[9] * m[2] * m[15] -
        m[9] * m[3] * m[14] -
        m[13] * m[2] * m[11] +
        m[13] * m[3] * m[10];

    inv[5] = m[0] * m[10] * m[15] -
        m[0] * m[11] * m[14] -
        m[8] * m[2] * m[15] +
        m[8] * m[3] * m[14] +
        m[12] * m[2] * m[11] -
        m[12] * m[3] * m[10];

    inv[9] = -m[0] * m[9] * m[15] +
        m[0] * m[11] * m[13] +
        m[8] * m[1] * m[15] -
        m[8] * m[3] * m[13] -
        m[12] * m[1] * m[11] +
        m[12] * m[3] * m[9];

    inv[13] = m[0] * m[9] * m[14] -
        m[0] * m[10] * m[13] -
        m[8] * m[1] * m[14] +
        m[8] * m[2] * m[13] +
        m[12] * m[1] * m[10] -
        m[12] * m[2] * m[9];

    inv[2] = m[1] * m[6] * m[15] -
        m[1] * m[7] * m[14] -
        m[5] * m[2] * m[15] +
        m[5] * m[3] * m[14] +
        m[13] * m[2] * m[7] -
        m[13] * m[3] * m[6];

    inv[6] = -m[0] * m[6] * m[15] +
        m[0] * m[7] * m[14] +
        m[4] * m[2] * m[15] -
        m[4] * m[3] * m[14] -
        m[12] * m[2] * m[7] +
        m[12] * m[3] * m[6];

    inv[10] = m[0] * m[5] * m[15] -
        m[0] * m[7] * m[13] -
        m[4] * m[1] * m[15] +
        m[4] * m[3] * m[13] +
        m[12] * m[1] * m[7] -
        m[12] * m[3] * m[5];

    inv[14] = -m[0] * m[5] * m[14] +
        m[0] * m[6] * m[13] +
        m[4] * m[1] * m[14] -
        m[4] * m[2] * m[13] -
        m[12] * m[1] * m[6] +
        m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
        m[1] * m[7] * m[10] +
        m[5] * m[2] * m[11] -
        m[5] * m[3] * m[10] -
        m[9] * m[2] * m[7] +
        m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
        m[0] * m[7] * m[10] -
        m[4] * m[2] * m[11] +
        m[4] * m[3] * m[10] +
        m[8] * m[2] * m[7] -
        m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
        m[0] * m[7] * m[9] +
        m[4] * m[1] * m[11] -
        m[4] * m[3] * m[9] -
        m[8] * m[1] * m[7] +
        m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
        m[0] * m[6] * m[9] -
        m[4] * m[1] * m[10] +
        m[4] * m[2] * m[9] +
        m[8] * m[1] * m[6] -
        m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
    
    if (det == 0)
        return false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            invOutttt[j][i] = invOut[i * 4 + j];
        }
    }

    return true;
}

void mat_mul(double df[4][4], double x0[4], double y[4]) {      //matrix multipection 
    for (int i = 0; i < 4; i++) {
        y[i] = 0;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            y[i] += df[j][i] * x0[j];
        }
    }
    
}






bool newtons_method(
    double x0[4],                         // The initial guess
    double x1[4],                         // Array for Answer
    double ff[4],                           // Array for Function in point x0
    double ff1[4],                          // Array for Part of Newton's metod
    double y[4][4],                         // Array for Jacobian
    double inv[4][4],                       // Array for Invert Jacobian
    double tolerance,                   // Stop when iterations change by less than this
    double a1[4],                         // Left side of interval
    double a2[4],                         // Right side of interval
    int max_iterations                  // The maximum number of iterations to compute
    ) {
    double norm = 0;                        // Norm of answer
    for (int i = 0; i < max_iterations; i++) {
        norm = 0;
        df(x0, y, 10., 60.);                // Jacobian in point x0

        InvertMatrix(y, inv);               // Invert Jacobian in point x0
      
        f(x0, ff, 10., 64.);                // Function in point x0

        mat_mul(inv, ff, ff1);              // Part of Newton's metod

        //cout << x0[0];
        
        for (int j = 0; j < 4; j++) {
            x1[j] = x0[j] - ff1[j];             // Do Newton's computation
        }

        f(x1, ff, 10, 64);
        for (int j = 0; j < 4; j++) {
            norm += pow(ff[j],2);               // Computing norm of f(x1)
        }

        if (norm <= tolerance) {                // Stop when the result is within the desired tolerance
            bool q = true;
            for (int j = 0; j < 4; j++) {
                q = q and (a1[j] < x1[j]) and (x1[j] < a2[j]); // Checking interval
            }
            if (not q) {
                cout << "not in interval";
                return false;
            }

            return true;
        }

        for (int j = 0; j < 4; j++) {
            x0[j] = x1[j];
        }
    }
    cout << "Method failled";
    return false;
    
}

int main()
{

    double x0[4] {0.52 * pow(10, 4), 0.18, 0.18 * pow(10, 8), 1.05} ;
    double x1[4]{};
    double ff[4]{};
    double ff1[4]{};
    double y[4][4];
    double inv[4][4];
    double a1[4]{ 0.5 * pow(10, 4), 0.1, 0.1 * pow(10, 8), 0.1 };
    double a2[4]{ 0.6 * pow(10, 4), 0.5, 0.5 * pow(10, 8), 5 };
    bool flag = false;

    flag = newtons_method(x0, x1, ff, ff1, y, inv, 0.4, a1, a2, 1000);

    if (flag) {
        cout << "Z1 = " << x1[0] << "\n";
        cout << "m1 = " << x1[1] << "\n";
        cout << "Z2 = " << x1[2] << "\n";
        cout << "m2 = " << x1[3] << "\n";
    }
    else {
        cout << "ERROR";
    }
    
}