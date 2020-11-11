#pragma once

#include <vector>
#include "AntennaArray.h"

class Particle
{
public:

	Particle(std::vector<double> pos, std::vector<double> vel, double evalue);

	void Update(AntennaArray currentAntennae, std::vector<double> g_best);


	std::vector<double> getPBest(void);
	double getBestValue(void);


private:

	std::vector<double> AddVectors(std::vector<double> vectorA, std::vector<double> vectorB);
	std::vector<double> HadavardProduct(std::vector<double> vectorA, std::vector<double> vectorB);
	std::vector<double> RandomUniformVector(int size);
	std::vector<double> DistanceVector(std::vector<double> pointA, std::vector<double> pointB);
	std::vector<double> DirectionVector(std::vector<double> pointA, std::vector<double> pointB);
	std::vector<double> MultiplyVectorByScalar(std::vector<double> v, double k);
	std::vector<double> position;
	std::vector<double> p_best;
	std::vector<double> velocity;
	double p_best_value;
	
};

