#include "Particle.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include "AntennaArray.h"
#include <iostream>


Particle::Particle(std::vector<double> pos, std::vector<double> vel, double eValue)
	:	position(pos), p_best(pos), velocity(vel), p_best_value(eValue){}




void Particle::Update(AntennaArray currentAntennae, std::vector<double> g_best)
{
	//Update Position
	/*------------------------------------------------------------------------------------------------*/
	std::transform(position.begin(), position.end(), velocity.begin(), position.begin(), std::plus<double>());
	position.push_back(currentAntennae.MAX_APERTURE);
	std::cout << "pbest: " << p_best_value << "\n";
	if(currentAntennae.is_valid(position))
	{
		double currentValue = currentAntennae.evaluate(position);
		position.pop_back();
		if (currentValue < p_best_value)
		{
			p_best_value = currentValue;
			
			p_best = position;
		}

	}
	else
	{
		position.pop_back();
	}

	

	/*------------------------------------------------------------------------------------------------*/
	//Update Velocity
	/*--------------------------------------------------------------*/

	double inertial = 1/(2*log(2));
	double cogsocial = 0.5 + log(2);
	std::vector<double> temp = AddVectors(
		MultiplyVectorByScalar(velocity, inertial),
		AddVectors(
			MultiplyVectorByScalar(
				HadavardProduct(
					RandomUniformVector(velocity.size()),
					DirectionVector(p_best, position)), 
				cogsocial), 
			MultiplyVectorByScalar(
				HadavardProduct(
					RandomUniformVector(velocity.size()),
					DirectionVector(g_best, position)), 
				cogsocial)));
	velocity.clear();
	velocity = temp;

	/*-------------------------------------------------------------*/
	

}




std::vector<double> Particle::getPBest(void)
{
	return p_best;
}




double Particle::getBestValue(void)
{
	return p_best_value;
}





std::vector<double> Particle::AddVectors(std::vector<double> vectorA, std::vector<double> vectorB)
{
	std::vector<double> returnVector;
	for (unsigned int i = 0; i < vectorA.size(); i++)
	{
		returnVector.insert(returnVector.begin(), vectorA[i] + vectorB[i]);
	}

	return returnVector;
}




std::vector<double> Particle::HadavardProduct(std::vector<double> vectorA, std::vector<double> vectorB)
{
	std::vector<double> returnVector;
	for (unsigned int i = 0; i < vectorA.size(); i++)
	{
		returnVector.insert(returnVector.begin(), vectorA[i] * vectorB[i]);
	}

	return returnVector;
}




std::vector<double> Particle::RandomUniformVector(int size)
{
	std::vector<double> returnVector;
	for (int i = 0; i < size; i++)
	{
		std::random_device rd; // obtain a random number from hardware
		std::mt19937 gen(rd()); // seed the generator
		std::uniform_real_distribution<> distr(0, 1); // define the range

		double position = distr(gen);
		returnVector.insert(returnVector.begin(), position);
	}
	

	return returnVector;
}




std::vector<double> Particle::DistanceVector(std::vector<double> pointA, std::vector<double> pointB)
{
	std::vector<double> returnVector;
	for (unsigned int i = 0; i < pointA.size(); i++)
	{
		returnVector.insert(returnVector.begin(), abs(pointA[i] - pointB[i]));
	}

	return returnVector;
}

std::vector<double> Particle::DirectionVector(std::vector<double> pointA, std::vector<double> pointB)
{
	std::vector<double> returnVector;
	for (unsigned int i = 0; i < pointA.size(); i++)
	{
		returnVector.insert(returnVector.begin(), pointA[i] - pointB[i]);
	}

	return returnVector;
}


std::vector<double> Particle::MultiplyVectorByScalar(std::vector<double> v, double k)
{

	for (unsigned int i = 0; i < v.size(); i++)
	{
		v[i] = v[i]*k;
	}

	return v;
}

