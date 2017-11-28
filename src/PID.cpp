#include <valarray>
#include <iostream>
#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd, bool use_twiddle) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    p_error = i_error = d_error = 0.0;

    if (use_twiddle) {
        this->use_twiddle = use_twiddle;
        best_err = numeric_limits<double>::max();
        idx = steps = state = 0;
        p = {Kp, Ki, Kd};
        dp = {0.01, 0.01, 0.01};
    }
}

void PID::UpdateError(double cte) {
    d_error = cte - p_error;
    p_error = cte;
    i_error += cte;

    if (use_twiddle) {
        if (steps > 300 && steps < 1800) {
            Twiddle(cte);
        }
        ++steps;
    }

}

double PID::TotalError() {
    return -Kp * p_error - Ki * i_error - Kd * d_error;
}

void PID::Twiddle(double cte) {
    err = pow(cte, 2);

    if (fabs(dp[0]) + fabs(dp[1]) + fabs(dp[2]) > tol) {
        switch (state) {
            case 0:
                p[idx] += dp[idx];
                state = 1;
                break;
            case 1:
                if (err < best_err) {
                    best_err = err;
                    dp[idx] *= 1.1;

                    NextTwiddleParam();
                } else {
                    p[idx] -= 2 * dp[idx];
                    if (p[idx] < 0) {
                        p[idx] = 0;
                        idx = (idx + 1) % 3;
                    }
                    state = 2;
                }
                break;
            case 2:
                if (err < best_err) {
                    best_err = err;
                    dp[idx] *= 1.05;
                } else {
                    p[idx] += dp[idx];
                    dp[idx] *= 0.9;
                }
                NextTwiddleParam();
                break;
            default:
                return;
        }

        Kp = p[0];
        Ki = p[1];
        Kd = p[2];

        cout << "Kp = " << Kp << " | Ki = " << Ki << " | Kd = " << Kd << endl;
    }
}

void PID::NextTwiddleParam() {
    idx = (idx + 1) % 3;
    p[idx] += dp[idx];
    state = 1;
}