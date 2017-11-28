#ifndef PID_H
#define PID_H

#include <vector>

class PID {
private:
    /**
     * Twiddle parameters
     */
    double best_err, err;
    std::vector<double> p, dp;
    const double tol = std::numeric_limits<double>::min();
    int idx, steps, state;
    bool use_twiddle;

    /**
     * Parameter optimization with twiddle
     */
    void Twiddle(double cte);

    void NextTwiddleParam();

public:
    /**
    * Errors
    */
    double p_error, i_error, d_error;

    /**
    * Coefficients
    */
    double Kp, Ki, Kd;

    /**
    * Constructor
    */
    PID();

    /**
    * Destructor.
    */
    virtual ~PID();

    /**
    * Initialize PID.
    */
    void Init(double Kp, double Ki, double Kd, bool use_twiddle);

    /**
    * Update the PID error variables given cross track error.
    */
    void UpdateError(double cte);

    /**
    * Calculate the total PID error.
    */
    double TotalError();
};

#endif /* PID_H */
