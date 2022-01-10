//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)
#include "helpers.hpp"

#include <cstdlib>
#include <random>

// Do generowania wysokiej jakości ciągów liczb pseudolosowych warto użyć
// zaawansowanych generatorów, np. algorytmu Mersenne Twister.
// zob. https://en.cppreference.com/w/cpp/numeric/random
std::random_device rd;
std::mt19937 rng(rd());

double default_probability_generator()
{
    // Generuj liczby pseudolosowe z przedziału [0, 1); 10 bitów losowości.
    return std::generate_canonical<double, 10>(rng);
}

std::function<double()> probability_generator = default_probability_generator;
//1b: Bartoszewski (406690), Gajek (400365), Gąsior (407326), Kowalczyk (406185)