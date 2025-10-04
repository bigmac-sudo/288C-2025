#include "robot_config.h"
class utilities{
    public:
    static float WheelSize;
    static const double circumference; 
    static const float oneTickis;
    static double ticks_to_degrees(float ticks);
    static float degrees_to_radian(float deg);
    static float rad_to_degrees(float rad);
    static float getwheelDiameter(enum Wheel wheel);
    static float calculateCircumference(float WheelSize);
    static double calculateGearing(double motorRotations);
    static double rad_to_inch(double rad);
    static double ticks_to_inch(float ticks);
    static double wrapHeading(double currentHeading);
    private:

};