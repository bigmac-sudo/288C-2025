class Autonomous{
    public:
    Autonomous();
     static void driveBackward(float distance);
     static void moveMotors(double distancePID, double rotationVal1);
     static void autonManager(void* param);
     static void driveFor(float distance);
     static void turnTo(double rotation);
    
     static float distanceV;
    private:
    double avgdist;    

};

//Position in terms of x,y,heading.
struct Position{
    double x;
    double y;
    double heading;
};

struct parameters{
    float driveForward;
    float driveBackward;
    float turn;
    float isAutonEnabled;
};

extern parameters par;