#include "Slam.h"

#include "CastComplete.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "HeroicStrike.h"
#include "MainhandAttack.h"
#include "NoEffectBuff.h"
#include "OffhandAttack.h"
#include "OverpowerBuff.h"
#include "Warrior.h"
#include "WarriorSpells.h"

Slam::Slam(Character* pchar) :
    SpellCastingTime("Slam", "Assets/ability/Ability_warrior_decisivestrike.png",
                     pchar, RestrictedByGcd::Yes,
                     0.0,
                     ResourceType::Rage,
                     15,
                     1500),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Slam", 5, DisabledAtZero::No)}),
    warr(dynamic_cast<Warrior*>(pchar))
{
    talent_ranks = {1500, 1400, 1300, 1200, 1100, 1000};
}

void Slam::increase_talent_rank_effect(const QString&, const int curr) {
    casting_time_ms = talent_ranks[curr];
}

void Slam::decrease_talent_rank_effect(const QString&, const int curr) {
    casting_time_ms = talent_ranks[curr];
}

SpellStatus Slam::is_ready_spell_specific() const {
    return warr->on_stance_cooldown() ? SpellStatus::OnStanceCooldown : SpellStatus::Available;
}

void Slam::spell_effect() {
    add_gcd_event();
    start_cast();

    pchar->get_spells()->stop_attack();
    dynamic_cast<WarriorSpells*>(warr->get_spells())->get_heroic_strike()->cancel();
}

void Slam::complete_cast_effect() {
    const int result = roll->get_melee_ability_result(warr->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    pchar->get_spells()->get_mh_attack()->reset_swingtimer();
    pchar->get_spells()->get_oh_attack()->reset_swingtimer();
    pchar->get_spells()->start_attack();

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        warr->lose_rage(resource_cost);
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        warr->get_overpower_buff()->apply_buff();
        warr->lose_rage(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        warr->lose_rage(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }

    double damage_dealt = damage_after_modifiers(warr->get_random_normalized_mh_dmg() + 87);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= warr->get_stats()->get_melee_ability_crit_dmg_mod();
        warr->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, double(casting_time_ms) / 1000);
    }
    else if (result == PhysicalAttackResult::HIT) {
        warr->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, double(casting_time_ms) / 1000);
    }

    warr->lose_rage(resource_cost);
}
