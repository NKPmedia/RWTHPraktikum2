#pragma once
class MathTools
{
public:
	MathTools();
	~MathTools();
	static bool nearly_equal(double a, double b);
	static bool nearly_equal(double a, double b, double delta);
};

