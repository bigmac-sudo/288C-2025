#include "ColorSorting.h"
bool sortingEnabled = false;
int targetColor;
   pros::Optical optical_sensor(3);//Change to Port number
isSortingEnabled(bool type){
sortingEnabled = type;
}

removeColor(int type){
targetColor = type;
}
