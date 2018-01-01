
#include "Whirlwind.h"

#include <iostream>

int Whirlwind::spell_effect(const int) const {
    // TODO: Find weapon skill for mainhand.
    AttackResult* result = roll->get_melee_ability_result(300);

    if (result->is_miss()) {
        add_fail_stats("Miss");
    }
    // TODO: Apply Overpower
    if (result->is_dodge()) {
        add_fail_stats("Dodge");
    }
    if (result->is_parry()) {
        add_fail_stats("Parry");
    }

    int damage_dealt = std::max(1, pchar->get_mh_dmg());

    // TODO: Apply Flurry
    if (result->is_critical()) {
        // TODO: Remove hardcoding of 2/2 Impale.
        damage_dealt *= 2.2;
        add_success_stats("Critical", damage_dealt);
    }
    else if (result->is_hit())
        add_success_stats("Hit", damage_dealt);

    add_gcd_event();
    add_spell_cd_event();

    return resource_cost;
}