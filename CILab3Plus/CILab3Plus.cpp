// CILab3Plus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AntennaArray.h"
#include "Particle.h"
#include <random>
#include <cmath>
#include <list>
#include <algorithm>


std::vector<double> g_best;
double g_best_value;


std::vector<double> RandomDesign(AntennaArray GivenArray)
{
    double numAntennae = GivenArray.getAntennae();
    double max = GivenArray.MAX_APERTURE;
    std::vector<double> design;


    do
    {
        design.clear();
        design.insert(design.begin(), max);
        for (int i = 0; i < numAntennae - 1; i++)
        {
            std::random_device rd; // obtain a random number from hardware
            std::mt19937 gen(rd()); // seed the generator
            std::uniform_real_distribution<> distr(0, max); // define the range


            double position = distr(gen);
            design.insert(design.begin(), position);
        }
    } while (!GivenArray.is_valid(design));

    design.pop_back();

    return design;


}


std::list<Particle> initialise(AntennaArray GivenArray)
{
    int swarmSize = 20 + (int)sqrt(3);
    std::list<Particle> swarm;
    for (int i = 0; i < swarmSize; i++)
    {
        std::vector<double> design = RandomDesign(GivenArray);
        design.push_back(GivenArray.MAX_APERTURE);
        double eValue = GivenArray.evaluate(design);
        design.pop_back();
        std::vector<double> tempPosition = RandomDesign(GivenArray);

        std::vector<double> velocity;
        for (unsigned int i = 0; i < design.size(); i++)
        {
            
            velocity.insert(velocity.begin(), (design[i] - tempPosition[i])/2);
        }

        Particle newParticle(design, velocity, eValue);

        if (g_best_value == NULL || newParticle.getBestValue() < g_best_value)
        {
            g_best = newParticle.getPBest();
            g_best_value = newParticle.getBestValue();
            std::cout << "starting best: " << g_best_value << "\n";
        }


        swarm.push_back(newParticle);

    }
    return swarm;
}





int main()
{
    

    AntennaArray AntennaArray1(3, 90);

    std::list<Particle> swarm = initialise(AntennaArray1);
    std::cout << swarm.size() << "\n";

    int count = 0;

    std::cout << g_best_value << "\n";

    while (count < 100)
    {
        for (std::list<Particle>::iterator i = swarm.begin(); i != swarm.end(); ++i)
        {
            i->Update(AntennaArray1, g_best);

        }
        for (Particle currentParticle : swarm)
        {
           
            if (currentParticle.getBestValue() < g_best_value)
            {
                g_best_value = currentParticle.getBestValue();
                g_best = currentParticle.getPBest();
                
                
            }
        }
        std::cout << "\n" << "new best: "<< g_best_value << "\n";
        std::cout << "\n";
        count++;
    }
    
}








// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
