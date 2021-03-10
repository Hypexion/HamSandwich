#ifndef SCRAMBLER_H
#define SCRAMBLER_H

#include <string>
#include <random>
#include <vector>

struct player_t;

class Scrambler {
public:
	Scrambler();
	Scrambler(std::string seed);
	~Scrambler() = default;

	void performScramble();

private:
	// functions
	void scrambleSkills();
	void scrambleTalents();

	void shuffle(std::vector<int> &v);

	// members
	std::default_random_engine m_rng;
};

#endif // !SCRAMBLER_H
