#include "MathTools.h"
#include <algorithm>
#include <cmath>

using namespace std;

MathTools::MathTools()
{
}


MathTools::~MathTools()
{
}

bool MathTools::nearly_equal(double a, double b)
{
	return fabs(a - b) <= max(fabs(a), fabs(b)) * numeric_limits<double>::epsilon() * 3;
}