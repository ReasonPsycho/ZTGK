//
// Created by redkc on 17/04/2024.
//

#include <cmath>
#include "LightHelpers.h"


float ComputeFarPlane(float constant, float linear, float quadratic)
{
// We consider the light to be "out of range" when the attenuation would be less than 1%
float threshold = 0.01f;

// Solve quadratic: constant + linear * r + quadratic * r^2 = 1 / threshold
float discr = linear * linear - 4 * quadratic * (constant - 1 / threshold);
float dist = (-linear + sqrt(discr)) / (2 * quadratic);
dist+= 1.0; //just in case
return dist;
}