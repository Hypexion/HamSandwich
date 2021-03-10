#include "scrambler.h"

#include "log.h"
#include "player.h"
#include "skill.h"
#include "talents.h"

#include <algorithm>
#include <vector>

Scrambler::Scrambler()
{
	m_rng.seed(timeGetTime());
}

Scrambler::Scrambler(std::string seed)
{
	std::seed_seq seq(seed.begin(), seed.end());
	m_rng.seed(seq);
}

void Scrambler::performScramble() {
	scrambleSkills();
	scrambleTalents();
}

void Scrambler::scrambleSkills()
{
	// For the standard scramble, basic axe skills aren't changed
	// Also note that skills are one-indexed
	player.skillMap[SKILL_AXEMASTERY - 1] = SKILL_AXEMASTERY;
	player.skillMap[SKILL_THROWING - 1] = SKILL_THROWING;

	std::vector<int> skills;
	LogDebug("Prep Skills");
	for (int i = 1; i <= MAX_SKILLS; ++i) {
		if (i == SKILL_AXEMASTERY || i == SKILL_THROWING) {
			continue;
		}
		skills.push_back(i);
	}

	shuffle(skills);

	for (int i = 0; i < MAX_SKILLS; ++i) {
		if (i == (SKILL_AXEMASTERY - 1) || i == (SKILL_THROWING - 1)) {
			continue;
		}
		int skill = skills.back();
		player.skillMap[i] = skill;
		skills.pop_back();
	}

#ifdef NOTDEFINED
	for (int i = 1; i <= MAX_SKILLS; ++i) {
		LogDebug("Skill #%i became skill #%i", i, (int)player.skillMap[i-1]);
	}
#endif
}

void Scrambler::scrambleTalents()
{
	// For the standard scramble, movement and gladiator talents aren't changed
	player.talentMap[TLT_MOBILITY] = TLT_MOBILITY;
	player.talentMap[TLT_GLADIATOR] = TLT_GLADIATOR;

	std::vector<int> talents;
	for (int i = 0; i < MAX_TALENTS; ++i) {
		if (i == TLT_MOBILITY || i == TLT_GLADIATOR) {
			continue;
		}
		talents.push_back(i);
	}

	for (int i = 0; i < MAX_TALENTS; ++i) {
		if (i == TLT_MOBILITY || i == TLT_GLADIATOR) {
			continue;
		}
		int talent = talents.back();
		player.talentMap[i] = talent;
		talents.pop_back();
	}
}

void Scrambler::shuffle(std::vector<int> &v)
{
	std::shuffle(std::begin(v), std::end(v), m_rng);
}
