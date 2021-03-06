#include "Day24.h"

using namespace std;

namespace Day24 {

	DamageType toDamageType(string typeToParse) {
		if(typeToParse == "fire") {
			return Fire;
		}
		else if(typeToParse == "cold") {
			return Cold;
		}
		else if(typeToParse == "slashing") {
			return Slashing;
		}
		else if(typeToParse == "bludgeoning") {
			return Bludgeoning;
		}
		else if (typeToParse == "radiation") {
			return Radiation;
		}

		throw exception("unknown damage type");
	}

	set<DamageType> toDamageTypes(vector<string> typesToParse) {
		set<DamageType> result;
		transform(begin(typesToParse), end(typesToParse), inserter(result, result.begin()), toDamageType);
		return result;
	}

	Side toSide(string side) {
		if (side == "Immune System") {
			return Defense;
		}
		if (side == "Infection") {
			return Attack;
		}
		throw exception("unknown side");
	}

	void AttackPlan::targetOrder() {
		sort(begin(this->groups), end(this->groups), [](Group &g1, Group &g2){
			if (g1.effectivePower() == g2.effectivePower()) {
				return g1.combatInitiative() > g2.combatInitiative();
			}
			return g1.effectivePower() > g2.effectivePower();
		});
	}

	bool AttackPlan::sideIsAlive(Side side) {
		return count_if(begin(this->groups), end(this->groups), [side](Group &g) {
			return g.side() == side && g.isAlive();
		}) > 0;
	}

	bool AttackPlan::sideHasWon() {
		return this->sideIsAlive(Defense) && this->sideIsAlive(Attack);
	}

	int AttackPlan::result() {
		if (this->sideHasWon()) {
			throw exception("no side has won");
		}

		if (this->sideIsAlive(Defense)) {
			return accumulate(begin(this->groups), end(this->groups), 0, [](int acc, Group &g) {
				return g.isAlive() && g.side() == Defense ? acc += g.units() : acc;
			});
		}
		else {
			return accumulate(begin(this->groups), end(this->groups), 0, [](int acc, Group &g) {
				return g.isAlive() && g.side() == Attack ? acc += g.units() : acc;
			});
		}
	}

	int Group::attackDamage(Group &attacker) {
			int amount = attacker.effectivePower();
			if (this->isWeak(attacker)) {
				amount *= 2;
			}
			if (this->isImmune(attacker)) {
				amount = 0;
			}
			return amount;
	}

	void AttackPlan::executePlan() {
		// sort by initiative
		vector<pair<tuple<int, int>, int>> result;
		copy(begin(this->plan), end(this->plan), back_inserter(result));
		sort(begin(result), end(result), [](const pair<tuple<int,int>, int> &p1, const pair<tuple<int,int>, int> &p2){
			int idx, initiative, idx2, initiative2;
			tie(idx, initiative) = p1.first;
			tie(idx2, initiative2) = p2.first;
			return initiative > initiative2;
		});

		// execute attack
		for (auto &p : result) {
			int idx, initiative;
			tie(idx, initiative) = p.first;
			auto attacker = this->groups[idx];
			if (!attacker.isAlive()) {
				continue;
			}
			this->groups[p.second].takeDamage(attacker);
		}
		this->plan.clear();
	}

	void AttackPlan::selectTargets() {
		set<int> usedIndexes;
		for (int i = 0; i < this->groups.size(); i++) {
			auto attacker = this->groups[i];
			if (!attacker.isAlive()) {
				continue;
			}
			// find candidates
			vector<tuple<int, Group>> potentialCandidates;
			for (auto j = 0; j < this->groups.size(); j++) {
				auto defender = this->groups[j];
				if (!defender.isAlive()) {
					continue;
				}
				if (attacker.side() != defender.side() && usedIndexes.find(j) == usedIndexes.end()) {
					if (defender.attackDamage(attacker) > 0) {
						potentialCandidates.push_back(make_tuple(j, defender));
					}
				}
			}
			// no candidates found?
			if (potentialCandidates.size() == 0) {
				continue;
			}
			// select target
			sort(begin(potentialCandidates), end(potentialCandidates), [&attacker](tuple<int, Group> &t1, tuple<int, Group> &t2) {
				Group g1, g2; int i1, i2;
				tie(i1, g1) = t1;
				tie(i2, g2) = t2;
				if (g1.attackDamage(attacker) == g2.attackDamage(attacker)) {
					if (g1.effectivePower() == g2.effectivePower()) {
						return g1.combatInitiative() > g2.combatInitiative();
					}
					else {
						g1.effectivePower() > g2.effectivePower();
					}
				}
				return g1.attackDamage(attacker) > g2.attackDamage(attacker);
			});
			Group group; int idx;
			tie(idx, group) = potentialCandidates[0];
			usedIndexes.insert(idx);
			this->plan[make_tuple(i, attacker.combatInitiative())] = idx;
		}
	}

	void AttackPlan::boost(int factor) {
		for_each(begin(this->groups), end(this->groups), [factor](Group &group) {
			if (group.side() == Defense) {
				group.boost(factor);
			}
		});
	}

	bool AttackPlan::immuneSystemWon() {
		return this->sideIsAlive(Defense);
	}

	int Part1(vector<Group> armies) {
		auto plan = AttackPlan(armies);

		while (plan.sideHasWon()) {
			// target selection
			plan.targetOrder();
			plan.selectTargets();

			// attacking
			plan.executePlan();
		}

		return plan.result();
	}

	int Part2(vector<Group> armies, int factor) {
		auto plan = AttackPlan(armies);
		plan.boost(factor);

		while (plan.sideHasWon()) {
			// target selection
			plan.targetOrder();
			plan.selectTargets();

			// attacking
			plan.executePlan();
		}

		if (!plan.immuneSystemWon()) {
			throw exception("immune system did not win");
		}

		return plan.result();
	}
}
