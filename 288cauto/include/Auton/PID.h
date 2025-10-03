class PID{
    public:
    double calculateSpeed(double distance, double currentD);
    double calculateRotation(double currentHeading, float targetHeading);
    double smallerror, largeError, largeErrorRange, MaxAcceleration;
    PID(signed char type);
    private:
    float kp, kd, ki;
    double dt;
    double normalizedHeading;
    double error, pasterror, derivative, integral, proportion;

};