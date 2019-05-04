#include "Consecration.h"

#include "CharacterStats.h"
#include "CombatRoll.h"
#include "DotTick.h"
#include "Engine.h"
#include "NoEffectBuff.h"
#include "Paladin.h"
#include "Utils/Check.h"

Consecration::Consecration(Paladin* pchar) :
    Spell("Consecration", "Assets/spell/Spell_holy_innerfire.png", pchar, RestrictedByGcd::Yes, 8, ResourceType::Mana, 565),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Consecration", 1, DisabledAtZero::Yes)}),
    buff(new NoEffectBuff(pchar,
                          8,
                          "Consecration",
                          "Assets/spell/Spell_holy_innerfire.png",
                          Hidden::No))
{
    this->enabled = false;
}

Consecration::~Consecration() {
    if (buff->is_enabled())
        buff->disable_buff();

    delete buff;
}

void Consecration::perform_periodic() {
    check((ticks > 0), "No Consecration stacks to consume");

    calculate_damage();

    --ticks;

    if (ticks > 0) {
        auto* new_event = new DotTick(this, engine->get_current_priority() + 2.0);
        this->engine->add_event(new_event);
    }
}

void Consecration::calculate_damage() {
    const int hit_roll = roll->get_spell_ability_result(MagicSchool::Holy, 0.0);
    const int resist_roll = roll->get_spell_resist_result(MagicSchool::Holy);

    if (hit_roll == MagicAttackResult::MISS)
        return increment_miss();
    if (resist_roll == MagicResistResult::FULL_RESIST)
        return increment_full_resist();

    const double resist_mod = get_partial_resist_dmg_modifier(resist_roll);
    const double bonus_from_spell_dmg = pchar->get_stats()->get_spell_damage(MagicSchool::Holy) * 0.33;
    const double damage_dealt = ((full_duration_dmg + bonus_from_spell_dmg) / 4 + tick_rest) * resist_mod * pchar->get_stats()->get_spell_dmg_mod(MagicSchool::Holy);
    tick_rest = tick_rest + damage_dealt - round(damage_dealt);

    add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost / 4, pchar->global_cooldown() / 4);
}

void Consecration::spell_effect() {
    buff->apply_buff();
    pchar->lose_mana(resource_cost);
    add_gcd_event();

    if (ticks == 0)
        this->engine->add_event(new DotTick(this, engine->get_current_priority() + 2.0));

    ticks += 4;
}

void Consecration::reset_effect() {
    ticks = 0;
    tick_rest = 0;
}

void Consecration::increase_talent_rank_effect(const QString&, const int) {
    buff->enable_buff();
}

void Consecration::decrease_talent_rank_effect(const QString&, const int) {
    buff->disable_buff();
}
