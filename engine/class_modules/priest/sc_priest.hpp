// ==========================================================================
// Dedmonwakeen's Raid DPS/TPS Simulator.
// Send questions to natehieter@gmail.com
// ==========================================================================
//
// This file contains all definitions for priests. Implementations should
// be done on sc_priest.cpp if they are shared by more than one spec or
// in the respective spec file if they are limited to one spec only.

#pragma once
#include "simulationcraft.hpp"

namespace priestspace
{
/* Forward declarations
 */
struct priest_t;

namespace actions
{
namespace spells
{
struct mind_sear_tick_t;
struct shadowy_apparition_spell_t;
struct sphere_of_insanity_spell_t;
struct blessed_dawnlight_medallion_t;
struct angelic_feather_t;
struct divine_star_t;
struct halo_t;
struct levitate_t;
struct power_infusion_t;
struct smite_t;
struct summon_pet_t;
struct summon_shadowfiend_t;
struct summon_mindbender_t;
}  // namespace spells
namespace heals
{
struct power_word_shield_t;
struct insanity_drain_stacks_t;
}  // namespace heals
}  // namespace actions

namespace pets
{
}

/**
 * Priest target data
 * Contains target specific things
 */
struct priest_td_t final : public actor_target_data_t
{
public:
  struct dots_t
  {
    propagate_const<dot_t*> shadow_word_pain;
    propagate_const<dot_t*> vampiric_touch;
    propagate_const<dot_t*> holy_fire;
    propagate_const<dot_t*> power_word_solace;
  } dots;

  struct buffs_t
  {
    propagate_const<buff_t*> schism;
  } buffs;

  priest_t& priest()
  {
    return *debug_cast<priest_t*>( source );
  }
  const priest_t& priest() const
  {
    return *debug_cast<priest_t*>( source );
  }

  priest_td_t( player_t* target, priest_t& p );
  void reset();
  void target_demise();
};

/**
 * Priest class definition
 * Derived from player_t. Contains everything that defines the priest class.
 */
struct priest_t final : public player_t
{
public:
  using base_t = player_t;

  // Buffs
  struct
  {
    // Talents
    propagate_const<buff_t*> power_infusion;
    propagate_const<buff_t*> twist_of_fate;

    // Discipline
    propagate_const<buff_t*> archangel;
    propagate_const<buff_t*> borrowed_time;
    propagate_const<buff_t*> holy_evangelism;
    propagate_const<buff_t*> inner_focus;

    // Holy

    // Shadow
    propagate_const<buff_t*> dispersion;
    propagate_const<buff_t*> insanity_drain_stacks;
    propagate_const<buff_t*> lingering_insanity;
    propagate_const<buff_t*> shadowform;
    propagate_const<buff_t*> shadowform_state;  // Dummy buff to track whether player entered Shadowform initially
    propagate_const<buff_t*> shadowy_insight;
    propagate_const<buff_t*> sphere_of_insanity;
    propagate_const<buff_t*> surrender_to_madness;
    propagate_const<buff_t*> surrendered_to_madness;
    propagate_const<buff_t*> vampiric_embrace;
    propagate_const<buff_t*> void_ray;
    propagate_const<buff_t*> void_torrent;
    propagate_const<buff_t*> voidform;

    // Set Bonus
    propagate_const<stat_buff_t*> power_overwhelming;  // T19OH
    propagate_const<buff_t*> void_vb;                  // T19 Shadow 4pc
    propagate_const<buff_t*> empty_mind;               // T20 Shadow 2pc
    propagate_const<buff_t*> overwhelming_darkness;    // T21 Shadow 4pc

    // Legion Legendaries
    propagate_const<haste_buff_t*> sephuzs_secret;
    // Shadow
    propagate_const<buff_t*> anunds_last_breath;       // Anund's Seared Shackles stack counter
    propagate_const<buff_t*> the_twins_painful_touch;  // To track first casting
    propagate_const<buff_t*> zeks_exterminatus;        // Aura for Zeks proc
    propagate_const<buff_t*> iridis_empowerment;       // Fake aura for Helm

    // Azerite Powers
    // Shadow
    propagate_const<buff_t*> chorus_of_insanity;
    propagate_const<buff_t*> harvested_thoughts;
    propagate_const<buff_t*> whispers_of_the_damned;

  } buffs;

  // Talents
  struct
  {
    const spell_data_t* shining_force;
    const spell_data_t* divine_star;
    const spell_data_t* halo;

    const spell_data_t* twist_of_fate;

    const spell_data_t* angelic_feather;

    const spell_data_t* psychic_voice;

    const spell_data_t* power_infusion;
    const spell_data_t* mindbender;

    // Discipline
    const spell_data_t* the_penitent;
    const spell_data_t* castigation;
    const spell_data_t* schism;

    const spell_data_t* body_and_soul;
    const spell_data_t* masochism;

    const spell_data_t* power_word_solace;
    const spell_data_t* shield_discipline;
    const spell_data_t* dominant_mind;

    const spell_data_t* sanctuary;
    const spell_data_t* clarity_of_will;
    const spell_data_t* shadow_covenant;

    const spell_data_t* purge_the_wicked;

    const spell_data_t* grace;
    const spell_data_t* evangelism;

    // Holy

    const spell_data_t* trail_of_light;
    const spell_data_t* enduring_renewal;
    const spell_data_t* enlightenment;

    const spell_data_t* body_and_mind;  // NYI
    const spell_data_t* perseverance;   // NYI

    const spell_data_t* light_of_the_naaru;
    const spell_data_t* guardian_angel;
    const spell_data_t* after_life;  // NYI

    const spell_data_t* censure;  // NYI

    const spell_data_t* surge_of_light;
    const spell_data_t* binding_heal;
    const spell_data_t* circle_of_healing;

    const spell_data_t* benediction;

    const spell_data_t* cosmic_ripple;
    const spell_data_t* apotheosis;
    const spell_data_t* holy_word_salvation;

    // Shadow
    // T15
    const spell_data_t* fortress_of_the_mind;
    const spell_data_t* shadow_word_void;
    const spell_data_t* shadowy_insight;
    // T30
    const spell_data_t* mania;
    const spell_data_t* sanlayn;  // NYI
    // T45
    const spell_data_t* dark_void;
    const spell_data_t* misery;
    // T60
    const spell_data_t* last_word;  // NYI
    const spell_data_t* mind_bomb;
    const spell_data_t* psychic_horror;  // NYI
    // T75
    const spell_data_t* auspicious_spirits;
    const spell_data_t* shadow_word_death;
    const spell_data_t* shadow_crash;
    // T90
    const spell_data_t* lingering_insanity;
    const spell_data_t* void_torrent;
    // T100
    const spell_data_t* legacy_of_the_void;
    const spell_data_t* dark_ascension;
    const spell_data_t* surrender_to_madness;
  } talents;

  struct legendary_t
  {
    const spell_data_t* sephuzs_secret;

    legendary_t() : sephuzs_secret( spell_data_t::not_found() )
    {
    }
  } legendary;

  // Specialization Spells
  struct
  {
    const spell_data_t* priest;  /// General priest data

    // Discipline
    const spell_data_t* discipline;  /// General discipline data
    const spell_data_t* archangel;
    const spell_data_t* atonement;
    const spell_data_t* borrowed_time;
    const spell_data_t* divine_aegis;
    const spell_data_t* evangelism;
    const spell_data_t* grace;
    const spell_data_t* mysticism;
    const spell_data_t* spirit_shell;
    const spell_data_t* enlightenment;

    // Holy
    const spell_data_t* holy;  /// General holy data
    const spell_data_t* rapid_renewal;
    const spell_data_t* serendipity;
    const spell_data_t* divine_providence;

    const spell_data_t* focused_will;

    // Shadow
    const spell_data_t* shadow;  /// General shadow data
    const spell_data_t* shadowy_apparitions;
    const spell_data_t* voidform;
    const spell_data_t* void_eruption;
    const spell_data_t* shadow_priest;
  } specs;

  // Mastery Spells
  struct
  {
    const spell_data_t* absolution;  // NYI
    const spell_data_t* echo_of_light;
    const spell_data_t* madness;
  } mastery_spells;

  // Cooldowns
  struct
  {
    propagate_const<cooldown_t*> chakra;
    propagate_const<cooldown_t*> mindbender;
    propagate_const<cooldown_t*> penance;
    propagate_const<cooldown_t*> power_word_shield;
    propagate_const<cooldown_t*> shadowfiend;
    propagate_const<cooldown_t*> silence;

    propagate_const<cooldown_t*> mind_blast;
    propagate_const<cooldown_t*> void_bolt;
    propagate_const<cooldown_t*> mind_bomb;
    propagate_const<cooldown_t*> psychic_horror;
    propagate_const<cooldown_t*> sephuzs_secret;
    propagate_const<cooldown_t*> dark_ascension;
  } cooldowns;

  // Gains
  struct
  {
    propagate_const<gain_t*> mindbender;
    propagate_const<gain_t*> power_word_solace;
    propagate_const<gain_t*> insanity_auspicious_spirits;
    propagate_const<gain_t*> insanity_dispersion;
    propagate_const<gain_t*> insanity_void_torrent;
    propagate_const<gain_t*> insanity_drain;
    propagate_const<gain_t*> insanity_mind_blast;
    propagate_const<gain_t*> insanity_mind_flay;
    propagate_const<gain_t*> insanity_mind_sear;
    propagate_const<gain_t*> insanity_pet;
    propagate_const<gain_t*> insanity_power_infusion;
    propagate_const<gain_t*> insanity_shadow_crash;
    propagate_const<gain_t*> insanity_shadow_word_death;
    propagate_const<gain_t*> insanity_shadow_word_pain_ondamage;
    propagate_const<gain_t*> insanity_shadow_word_pain_onhit;
    propagate_const<gain_t*> insanity_shadow_word_void;
    propagate_const<gain_t*> insanity_surrender_to_madness;
    propagate_const<gain_t*> insanity_wasted_surrendered_to_madness;
    propagate_const<gain_t*> insanity_vampiric_touch_ondamage;
    propagate_const<gain_t*> insanity_vampiric_touch_onhit;
    propagate_const<gain_t*> insanity_void_bolt;
    propagate_const<gain_t*> insanity_blessing;
    propagate_const<gain_t*> shadowy_insight;
    propagate_const<gain_t*> vampiric_touch_health;
    propagate_const<gain_t*> insanity_call_to_the_void;
    propagate_const<gain_t*> insanity_dark_void;
    propagate_const<gain_t*> insanity_dark_ascension;
  } gains;

  // Benefits
  struct
  {
  } benefits;

  // Procs
  struct
  {
    propagate_const<proc_t*> legendary_zeks_exterminatus;
    propagate_const<proc_t*> legendary_zeks_exterminatus_overflow;
    propagate_const<proc_t*> legendary_anunds_last_breath;
    propagate_const<proc_t*> legendary_anunds_last_breath_overflow;
    propagate_const<proc_t*> shadowy_insight;
    propagate_const<proc_t*> shadowy_insight_overflow;
    propagate_const<proc_t*> serendipity;
    propagate_const<proc_t*> serendipity_overflow;
    propagate_const<proc_t*> shadowy_apparition;
    propagate_const<proc_t*> shadowy_apparition_overflow;
    propagate_const<proc_t*> surge_of_light;
    propagate_const<proc_t*> surge_of_light_overflow;
    propagate_const<proc_t*> void_eruption_has_dots;
    propagate_const<proc_t*> void_eruption_no_dots;
    propagate_const<proc_t*> void_tendril;
  } procs;

  struct realppm_t
  {
    propagate_const<real_ppm_t*> call_to_the_void;
    propagate_const<real_ppm_t*> shadowy_insight;
  } rppm;

  // Special
  struct
  {
    propagate_const<actions::spells::mind_sear_tick_t*> mind_sear_tick;
    propagate_const<actions::spells::shadowy_apparition_spell_t*> shadowy_apparitions;
    propagate_const<action_t*> sphere_of_insanity;
    propagate_const<action_t*> mental_fortitude;
    propagate_const<action_t*> void_tendril;
  } active_spells;

  struct
  {
    // Legion Legendaries Shadow
    const special_effect_t* anunds_seared_shackles;     // wrist
    const special_effect_t* mother_shahrazs_seduction;  // shoulder
    const special_effect_t* mangazas_madness;           // belt
    const special_effect_t* zenkaram_iridis_anadem;     // helm
    const special_effect_t* the_twins_painful_touch;    // ring
    const special_effect_t* zeks_exterminatus;          // cloak
    const special_effect_t* sephuzs_secret;             // ring
    const special_effect_t* heart_of_the_void;          // chest
  } active_items;

  // Pets
  struct
  {
    propagate_const<pet_t*> shadowfiend;
    propagate_const<pet_t*> mindbender;
  } pets;

  // Options
  struct
  {
    bool autoUnshift                 = true;  // Shift automatically out of stance/form
    bool priest_fixed_time           = true;
    bool priest_ignore_healing       = false;  // Remove Healing calculation codes
    bool priest_suppress_sephuz      = false;  // Sephuz's Secret won't proc if set true
    int priest_set_voidform_duration = 0;      // Voidform will always have this duration
  } options;

  // Azerite
  struct azerite_t
  {
    azerite_power_t sanctum;
    // Holy
    // Disc
    // Shadow
    azerite_power_t chorus_of_insanity;
    azerite_power_t death_throes;
    azerite_power_t depth_of_the_shadows;
    azerite_power_t harvested_thoughts;
    azerite_power_t searing_dialogue;
    azerite_power_t spiteful_apparitions;
    azerite_power_t torment_of_torments;
    azerite_power_t whispers_of_the_damned;
  } azerite;

  struct insanity_end_event_t;

  priest_t( sim_t* sim, const std::string& name, race_e r );

  priest_td_t* find_target_data( player_t* target ) const;

  // player_t overrides
  void init_base_stats() override;
  void init_resources( bool force ) override;
  void init_spells() override;
  void create_buffs() override;
  void init_scaling() override;
  void reset() override;
  void create_options() override;
  std::string create_profile( save_e ) override;
  action_t* create_action( const std::string& name, const std::string& options ) override;
  virtual action_t* create_proc_action( const std::string& name, const special_effect_t& effect ) override;
  pet_t* create_pet( const std::string& name, const std::string& type = std::string() ) override;
  void create_pets() override;
  void copy_from( player_t* source ) override;
  resource_e primary_resource() const override
  {
    return RESOURCE_MANA;
  }
  role_e primary_role() const override;
  stat_e convert_hybrid_stat( stat_e s ) const override;
  stat_e primary_stat() const override
  {
    return STAT_INTELLECT;
  }
  void assess_damage( school_e school, dmg_e dtype, action_state_t* s ) override;
  double composite_melee_haste() const override;
  double composite_melee_speed() const override;
  double composite_spell_haste() const override;
  double composite_spell_speed() const override;
  double composite_player_multiplier( school_e school ) const override;
  double composite_player_absorb_multiplier( const action_state_t* s ) const override;
  double composite_player_heal_multiplier( const action_state_t* s ) const override;
  double composite_player_target_multiplier( player_t* t, school_e school ) const override;
  double matching_gear_multiplier( attribute_e attr ) const override;
  void target_mitigation( school_e, dmg_e, action_state_t* ) override;
  void pre_analyze_hook() override;
  void init_action_list() override;
  void combat_begin() override;
  void init_rng() override;
  priest_td_t* get_target_data( player_t* target ) const override;
  expr_t* create_expression( const std::string& name_str ) override;
  void trigger_sephuzs_secret( const action_state_t* state, spell_mechanic mechanic, double proc_chance = -1.0 );
  void trigger_call_to_the_void( const dot_t* d );

  void do_dynamic_regen() override
  {
    player_t::do_dynamic_regen();

    // Drain insanity, and adjust the time when all insanity is depleted from the actor
    insanity.drain();
    insanity.adjust_end_event();
  }

private:
  void create_cooldowns();
  void create_gains();
  void create_procs();
  void create_benefits();
  void create_apl_precombat();
  void create_apl_default();
  void fixup_atonement_stats( const std::string& trigger_spell_name, const std::string& atonement_spell_name );

  void create_buffs_shadow();
  void init_rng_shadow();
  void init_spells_shadow();
  void generate_apl_shadow();
  expr_t* create_expression_shadow( const std::string& name_str );
  action_t* create_action_shadow( const std::string& name, const std::string& options_str );

  void create_buffs_discipline();
  void init_spells_discipline();
  void init_rng_discipline();
  void generate_apl_discipline_d();
  void generate_apl_discipline_h();
  expr_t* create_expression_discipline( action_t* a, const std::string& name_str );
  action_t* create_action_discipline( const std::string& name, const std::string& options_str );

  void create_buffs_holy();
  void init_spells_holy();
  void init_rng_holy();
  void generate_apl_holy_d();
  void generate_apl_holy_h();
  expr_t* create_expression_holy( action_t* a, const std::string& name_str );
  action_t* create_action_holy( const std::string& name, const std::string& options_str );

  target_specific_t<priest_td_t> _target_data;

public:
  void generate_insanity( double num_amount, gain_t* g, action_t* action );

  /**
   * Insanity tracking
   *
   * Handles the resource gaining from abilities, and insanity draining and manages an event that forcibly punts the
   * actor out of Voidform the exact moment insanity hitszero (millisecond resolution).
   */
  struct insanity_state_t final
  {
    event_t* end;             // End event for dropping out of voidform (insanity reaches 0)
    timespan_t last_drained;  // Timestamp when insanity was last drained
    priest_t& actor;

    const double base_drain_per_sec;
    const double stack_drain_multiplier;
    double base_drain_multiplier;

    insanity_state_t( priest_t& a );

    /// Deferred init for actor dependent stuff not ready in the ctor
    void init();

    /// Start the insanity drain tracking
    void set_last_drained();

    /// Start (or re-start) tracking of the insanity drain plus end event
    void begin_tracking();

    timespan_t time_to_end() const;

    void reset();

    /// Compute insanity drain per second with current state of the actor
    double insanity_drain_per_second() const;

    /// Gain some insanity
    void gain( double value, gain_t* gain_obj, action_t* source_action );

    /**
     * Triggers the insanity drain, and is called in places that changes the insanity state of the actor in a relevant
     * way.
     * These are:
     * - Right before the actor decides to do something (scans APL for an ability to use)
     * - Right before insanity drain stack increases (every second)
     */
    void drain();

    /**
     * Predict (with current state) when insanity is going to be fully depleted, and adjust (or create) an event for it.
     * Called in conjunction with insanity_state_t::drain(), after the insanity drain occurs (and potentially after a
     * relevant state change such as insanity drain stack buff increase occurs). */
    void adjust_end_event();
  } insanity;

  std::string default_potion() const override;
  std::string default_flask() const override;
  std::string default_food() const override;
  std::string default_rune() const override;
};

namespace pets
{
/**
 * Pet base class
 *
 * Defines characteristics common to ALL priest pets.
 */
struct priest_pet_t : public pet_t
{
  priest_pet_t( sim_t* sim, priest_t& owner, const std::string& pet_name, pet_e pt, bool guardian = false )
    : pet_t( sim, &owner, pet_name, pt, guardian )
  {
  }

  void init_base_stats() override
  {
    pet_t::init_base_stats();

    base.position = POSITION_BACK;
    base.distance = 3;

    owner_coeff.ap_from_sp = 1.0;
    owner_coeff.sp_from_sp = 1.0;
  }

  void schedule_ready( timespan_t delta_time, bool waiting ) override
  {
    if ( main_hand_attack && !main_hand_attack->execute_event )
    {
      main_hand_attack->schedule_execute();
    }

    pet_t::schedule_ready( delta_time, waiting );
  }

  double composite_player_multiplier( school_e school ) const override
  {
    double m = pet_t::composite_player_multiplier( school );

    // Orc racial
    m *= 1.0 + o().racials.command->effectN( 1 ).percent();

    return m;
  }

  resource_e primary_resource() const override
  {
    return RESOURCE_ENERGY;
  }

  priest_t& o()
  {
    return static_cast<priest_t&>( *owner );
  }
  const priest_t& o() const
  {
    return static_cast<priest_t&>( *owner );
  }
};

struct priest_pet_melee_t : public melee_attack_t
{
  bool first_swing;

  priest_pet_melee_t( priest_pet_t& p, const char* name )
    : melee_attack_t( name, &p, spell_data_t::nil() ), first_swing( true )
  {
    school            = SCHOOL_SHADOW;
    weapon            = &( p.main_hand_weapon );
    weapon_multiplier = 1.0;
    base_execute_time = weapon->swing_time;
    may_crit          = true;
    background        = true;
    repeating         = true;
  }

  void reset() override
  {
    melee_attack_t::reset();
    first_swing = true;
  }

  timespan_t execute_time() const override
  {
    // First swing comes instantly after summoning the pet
    if ( first_swing )
      return timespan_t::zero();

    return melee_attack_t::execute_time();
  }

  void schedule_execute( action_state_t* state = nullptr ) override
  {
    melee_attack_t::schedule_execute( state );

    first_swing = false;
  }
};

struct priest_pet_spell_t : public spell_t
{
  priest_pet_spell_t( priest_pet_t& p, const std::string& n ) : spell_t( n, &p, p.find_pet_spell( n ) )
  {
    may_crit = true;
  }

  priest_pet_spell_t( const std::string& token, priest_pet_t* p, const spell_data_t* s = spell_data_t::nil() )
    : spell_t( token, p, s )
  {
    may_crit = true;
  }

  priest_pet_t& p()
  {
    return static_cast<priest_pet_t&>( *player );
  }
  const priest_pet_t& p() const
  {
    return static_cast<priest_pet_t&>( *player );
  }
};

namespace fiend
{
/**
 * Abstract base class for Shadowfiend and Mindbender
 */
struct base_fiend_pet_t : public priest_pet_t
{
  struct gains_t
  {
    propagate_const<gain_t*> fiend;
  } gains;

  double direct_power_mod;

  base_fiend_pet_t( sim_t* sim, priest_t& owner, pet_e pt, const std::string& name )
    : priest_pet_t( sim, owner, name, pt ), gains(), direct_power_mod( 0.0 )
  {
    main_hand_weapon.type       = WEAPON_BEAST;
    main_hand_weapon.swing_time = timespan_t::from_seconds( 1.5 );

    owner_coeff.health = 0.3;
  }

  virtual double mana_return_percent() const = 0;
  virtual double insanity_gain() const       = 0;

  void init_action_list() override;

  void init_gains() override
  {
    priest_pet_t::init_gains();

    if ( o().specialization() == PRIEST_SHADOW )
    {
      gains.fiend = o().gains.insanity_pet;
    }
    else
    {
      switch ( pet_type )
      {
        case PET_MINDBENDER:
        {
          gains.fiend = o().gains.mindbender;
        }
        break;
        default:
          gains.fiend = get_gain( "basefiend" );
          break;
      }
    }
  }

  void init_resources( bool force ) override
  {
    priest_pet_t::init_resources( force );

    resources.initial[ RESOURCE_MANA ] = owner->resources.max[ RESOURCE_MANA ];
    resources.current = resources.max = resources.initial;
  }

  action_t* create_action( const std::string& name, const std::string& options_str ) override;
};

struct shadowfiend_pet_t final : public base_fiend_pet_t
{
  shadowfiend_pet_t( sim_t* sim, priest_t& owner, const std::string& name = "shadowfiend" )
    : base_fiend_pet_t( sim, owner, PET_SHADOWFIEND, name )
  {
    direct_power_mod = 0.6;  // According to Sephuz 2018-02-07 -- N1gh7h4wk hardcoded

    main_hand_weapon.min_dmg = owner.dbc.spell_scaling( owner.type, owner.level() ) * 2;
    main_hand_weapon.max_dmg = owner.dbc.spell_scaling( owner.type, owner.level() ) * 2;

    main_hand_weapon.damage = ( main_hand_weapon.min_dmg + main_hand_weapon.max_dmg ) / 2;
  }

  double mana_return_percent() const override
  {
    return 0.0;
  }
  double insanity_gain() const override
  {
    return o().find_spell( 262485 )->effectN( 1 ).resource( RESOURCE_INSANITY );
  }
};

struct mindbender_pet_t final : public base_fiend_pet_t
{
  const spell_data_t* mindbender_spell;

  mindbender_pet_t( sim_t* sim, priest_t& owner, const std::string& name = "mindbender" )
    : base_fiend_pet_t( sim, owner, PET_MINDBENDER, name ), mindbender_spell( owner.find_spell( 123051 ) )
  {
    direct_power_mod = 0.65;  // According to Sephuz 2018-02-07 -- N1gh7h4wk hardcoded

    main_hand_weapon.min_dmg = owner.dbc.spell_scaling( owner.type, owner.level() ) * 2;
    main_hand_weapon.max_dmg = owner.dbc.spell_scaling( owner.type, owner.level() ) * 2;
    main_hand_weapon.damage  = ( main_hand_weapon.min_dmg + main_hand_weapon.max_dmg ) / 2;
  }

  double mana_return_percent() const override
  {
    double m = mindbender_spell->effectN( 1 ).percent();
    return m / 100;
  }
  double insanity_gain() const override
  {
    return o().find_spell( 200010 )->effectN( 1 ).resource( RESOURCE_INSANITY );
  }
};

namespace actions
{
struct shadowcrawl_t final : public priest_pet_spell_t
{
  shadowcrawl_t( base_fiend_pet_t& p ) : priest_pet_spell_t( p, "Shadowcrawl" )
  {
    may_miss = false;
    harmful  = false;
  }

  base_fiend_pet_t& p()
  {
    return static_cast<base_fiend_pet_t&>( *player );
  }
  const base_fiend_pet_t& p() const
  {
    return static_cast<base_fiend_pet_t&>( *player );
  }
};

struct fiend_melee_t : public priest_pet_melee_t
{
  fiend_melee_t( base_fiend_pet_t& p ) : priest_pet_melee_t( p, "melee" )
  {
    weapon                  = &( p.main_hand_weapon );
    weapon_multiplier       = 0.0;
    base_dd_min             = weapon->min_dmg;
    base_dd_max             = weapon->max_dmg;
    attack_power_mod.direct = p.direct_power_mod;
  }

  base_fiend_pet_t& p()
  {
    return static_cast<base_fiend_pet_t&>( *player );
  }
  const base_fiend_pet_t& p() const
  {
    return static_cast<base_fiend_pet_t&>( *player );
  }

  timespan_t execute_time() const override
  {
    if ( base_execute_time == timespan_t::zero() )
      return timespan_t::zero();

    if ( !harmful && !player->in_combat )
      return timespan_t::zero();

    return base_execute_time * player->cache.spell_speed();
  }

  void impact( action_state_t* s ) override
  {
    priest_pet_melee_t::impact( s );

    if ( result_is_hit( s->result ) )
    {
      if ( p().o().specialization() == PRIEST_SHADOW )
      {
        double amount = p().insanity_gain();
        if ( p().o().buffs.surrendered_to_madness->up() )
        {
          amount = 0.0;  // generation with debuff is zero N1gh7h4wk 2018/01/26
        }
        if ( p().o().buffs.surrender_to_madness->up() )
        {
          p().o().resource_gain(
              RESOURCE_INSANITY,
              ( amount * ( 1.0 + p().o().talents.surrender_to_madness->effectN( 1 ).percent() ) ) - amount,
              p().o().gains.insanity_surrender_to_madness );
        }
        p().o().insanity.gain( amount, p().gains.fiend, nullptr );
      }
      else
      {
        double mana_reg_pct = p().mana_return_percent();
        if ( mana_reg_pct > 0.0 )
        {
          p().o().resource_gain( RESOURCE_MANA, p().o().resources.max[ RESOURCE_MANA ] * p().mana_return_percent(),
                                 p().gains.fiend );
        }
      }
    }
  }
};
}  // namespace actions
}  // namespace fiend
}  // namespace pets

namespace actions
{
/**
 * Priest action base class
 *
 * This is a template for common code between priest_spell_t, priest_heal_t and priest_absorb_t.
 * The template is instantiated with either spell_t, heal_t or absorb_t as the 'Base' class.
 * Make sure you keep the inheritance hierarchy and use base_t in the derived class, don't skip it and call
 * spell_t/heal_t or absorb_t directly.
 */
template <typename Base>
struct priest_action_t : public Base
{
  bool shadow_damage_increase;
  bool shadow_dot_increase;

public:
  priest_action_t( const std::string& n, priest_t& p, const spell_data_t* s = spell_data_t::nil() )
    : ab( n, &p, s ),
      shadow_damage_increase( ab::data().affected_by( p.specs.shadow_priest->effectN( 1 ) ) ),
      shadow_dot_increase( ab::data().affected_by( p.specs.shadow_priest->effectN( 2 ) ) )
  {
    ab::may_crit          = true;
    ab::tick_may_crit     = true;
    ab::weapon_multiplier = 0.0;
    if ( shadow_damage_increase || s->id() == 280711u )
      ab::base_dd_multiplier *= 1.0 + p.specs.shadow_priest->effectN( 1 ).percent();
    if ( shadow_dot_increase )
      ab::base_td_multiplier *= 1.0 + p.specs.shadow_priest->effectN( 2 ).percent();
  }

  priest_td_t& get_td( player_t* t )
  {
    return *( priest().get_target_data( t ) );
  }

  priest_td_t* find_td( player_t* t )
  {
    return priest().find_target_data( t );
  }

  const priest_td_t* find_td( player_t* t ) const
  {
    return priest().find_target_data( t );
  }

  bool trigger_shadowy_insight()
  {
    int stack = priest().buffs.shadowy_insight->check();
    if ( priest().buffs.shadowy_insight->trigger() )
    {
      priest().cooldowns.mind_blast->reset( true );

      if ( priest().buffs.shadowy_insight->check() == stack )
      {
        priest().procs.shadowy_insight_overflow->occur();
      }
      else
      {
        priest().procs.shadowy_insight->occur();
      }
      return true;
    }
    return false;
  }

  bool trigger_zeks()
  {
    if ( priest().buffs.zeks_exterminatus->trigger() )
    {
      // proc doesn't reset the CD :
      // priest().cooldowns.shadow_word_death->reset(true);

      if ( priest().buffs.zeks_exterminatus->check() )
      {
        priest().procs.legendary_zeks_exterminatus_overflow->occur();
      }
      else
      {
        priest().procs.legendary_zeks_exterminatus->occur();
      }
      return true;
    }
    return false;
  }

  void trigger_anunds()
  {
    int stack = priest().buffs.anunds_last_breath->check();
    priest().buffs.anunds_last_breath->trigger();

    if ( priest().buffs.anunds_last_breath->check() == stack )
    {
      priest().procs.legendary_anunds_last_breath_overflow->occur();
    }
    else
    {
      priest().procs.legendary_anunds_last_breath->occur();
    }
  }

  double cost() const override
  {
    double c = ab::cost();

    if ( priest().buffs.power_infusion->check() && priest().specialization() != PRIEST_SHADOW )
    {
      c *= 1.0 + priest().buffs.power_infusion->data().effectN( 2 ).percent();
      c = std::floor( c );
    }

    return c;
  }

  void consume_resource() override
  {
    ab::consume_resource();

    if ( ab::base_execute_time > timespan_t::zero() && !this->channeled )
      priest().buffs.borrowed_time->expire();
  }

protected:
  priest_t& priest()
  {
    return *debug_cast<priest_t*>( ab::player );
  }
  const priest_t& priest() const
  {
    return *debug_cast<priest_t*>( ab::player );
  }

  /// typedef for priest_action_t<action_base_t>
  using base_t = priest_action_t;

private:
  /// typedef for the templated action type, eg. spell_t, attack_t, heal_t
  using ab = Base;
};

struct priest_absorb_t : public priest_action_t<absorb_t>
{
public:
  priest_absorb_t( const std::string& n, priest_t& player, const spell_data_t* s = spell_data_t::nil() )
    : base_t( n, player, s )
  {
    may_crit      = true;
    tick_may_crit = false;
    may_miss      = false;
  }
};

struct priest_heal_t : public priest_action_t<heal_t>
{
  priest_heal_t( const std::string& n, priest_t& player, const spell_data_t* s = spell_data_t::nil() )
    : base_t( n, player, s )
  {
  }

  double action_multiplier() const override
  {
    double am = base_t::action_multiplier();

    am *= 1.0 + priest().buffs.archangel->current_value;

    return am;
  }

  void execute() override
  {
    priest().buffs.archangel->up();  // benefit tracking

    base_t::execute();

    may_crit = true;
  }

  void impact( action_state_t* s ) override
  {
    double save_health_percentage = s->target->health_percentage();

    base_t::impact( s );

    if ( s->result_amount > 0 )
    {
      if ( priest().specialization() != PRIEST_SHADOW && priest().talents.twist_of_fate->ok() &&
           ( save_health_percentage < priest().talents.twist_of_fate->effectN( 1 ).base_value() ) )
      {
        priest().buffs.twist_of_fate->trigger();
      }
    }
  }
};

struct priest_spell_t : public priest_action_t<spell_t>
{
  bool is_sphere_of_insanity_spell;
  bool is_mastery_spell;

  priest_spell_t( const std::string& n, priest_t& player, const spell_data_t* s = spell_data_t::nil() )
    : base_t( n, player, s ), is_sphere_of_insanity_spell( false ), is_mastery_spell( false )
  {
    weapon_multiplier = 0.0;
  }

  bool usable_moving() const override
  {
    if ( priest().buffs.surrender_to_madness->check() )
    {
      return true;
    }

    return spell_t::usable_moving();
  }

  void impact( action_state_t* s ) override
  {
    double save_health_percentage = s->target->health_percentage();

    base_t::impact( s );

    if ( result_is_hit( s->result ) )
    {
      if ( priest().specialization() == PRIEST_SHADOW && priest().talents.twist_of_fate->ok() &&
           ( save_health_percentage < priest().talents.twist_of_fate->effectN( 1 ).base_value() ) )
      {
        priest().buffs.twist_of_fate->trigger();
      }
    }
  }

  double action_multiplier() const override
  {
    double m = spell_t::action_multiplier();

    if ( is_mastery_spell && priest().mastery_spells.madness->ok() )
    {
      m *= 1.0 + priest().cache.mastery_value();
    }

    return m;
  }

  void assess_damage( dmg_e type, action_state_t* s ) override
  {
    base_t::assess_damage( type, s );

    if ( is_sphere_of_insanity_spell && priest().buffs.sphere_of_insanity->up() && s->result_amount > 0 )
    {
      double damage = s->result_amount * priest().buffs.sphere_of_insanity->data().effectN( 3 ).percent();
      priest().active_spells.sphere_of_insanity->base_dd_min = damage;
      priest().active_spells.sphere_of_insanity->base_dd_max = damage;
      priest().active_spells.sphere_of_insanity->schedule_execute();
    }
    if ( aoe == 0 && result_is_hit( s->result ) && priest().buffs.vampiric_embrace->up() )
      trigger_vampiric_embrace( s );
  }

  /* Based on previous implementation ( pets don't count but get full heal )
   * and http://www.wowhead.com/spell=15286#comments:id=1796701
   * Last checked 2013-05-25
   */
  void trigger_vampiric_embrace( action_state_t* s )
  {
    double amount = s->result_amount;
    amount *= priest().buffs.vampiric_embrace->data().effectN( 1 ).percent();  // FIXME additive or multiplicate?

    // Get all non-pet, non-sleeping players
    std::vector<player_t*> ally_list;
    range::remove_copy_if( sim->player_no_pet_list.data(), back_inserter( ally_list ), player_t::_is_sleeping );

    for ( player_t* ally : ally_list )
    {
      ally->resource_gain( RESOURCE_HEALTH, amount, ally->gains.vampiric_embrace );

      for ( pet_t* pet : ally->pet_list )
      {
        pet->resource_gain( RESOURCE_HEALTH, amount, pet->gains.vampiric_embrace );
      }
    }
  }
};

}  // namespace actions

namespace buffs
{
/**
 * This is a template for common code between priest buffs.
 * The template is instantiated with any type of buff ( buff_t, debuff_t,
 * absorb_buff_t, etc. ) as the 'Base' class.
 * Make sure you keep the inheritance hierarchy and use base_t in the derived
 * class,
 * don't skip it and call buff_t/absorb_buff_t/etc. directly.
 */
template <typename Base>
struct priest_buff_t : public Base
{
public:
  using base_t = priest_buff_t;  // typedef for priest_buff_t<buff_base_t>

  priest_buff_t( priest_td_t& td, const std::string& name, const spell_data_t* s = spell_data_t::nil(),
                 const item_t* item = nullptr )
    : Base( td, name, s, item )
  {
  }

  priest_buff_t( priest_t& p, const std::string& name, const spell_data_t* s = spell_data_t::nil(),
                 const item_t* item = nullptr )
    : Base( &p, name, s, item )
  {
  }

protected:
  priest_t& priest()
  {
    return *debug_cast<priest_t*>( Base::source );
  }
  const priest_t& priest() const
  {
    return *debug_cast<priest_t*>( Base::source );
  }
};

}  // namespace buffs

namespace items
{
void init();
}  // namespace items

/**
 * Report Extension Class
 * Here you can define class specific report extensions/overrides
 */
struct priest_report_t final : public player_report_extension_t
{
public:
  priest_report_t( priest_t& player ) : p( player )
  {
  }

  void html_customsection( report::sc_html_stream& /* os*/ ) override
  {
    (void)p;
    /*// Custom Class Section
    os << "\t\t\t\t<div class=\"player-section custom_section\">\n"
    << "\t\t\t\t\t<h3 class=\"toggle open\">Custom Section</h3>\n"
    << "\t\t\t\t\t<div class=\"toggle-content\">\n";

    os << p.name();

    os << "\t\t\t\t\t\t</div>\n" << "\t\t\t\t\t</div>\n";*/
  }

private:
  priest_t& p;
};

struct priest_module_t final : public module_t
{
  priest_module_t() : module_t( PRIEST )
  {
  }

  player_t* create_player( sim_t* sim, const std::string& name, race_e r = RACE_NONE ) const override
  {
    auto p              = new priest_t( sim, name, r );
    p->report_extension = std::unique_ptr<player_report_extension_t>( new priest_report_t( *p ) );
    return p;
  }
  bool valid() const override
  {
    return true;
  }
  void init( player_t* p ) const override
  {
    p->buffs.guardian_spirit = buff_creator_t( p, "guardian_spirit",
                                               p->find_spell( 47788 ) );  // Let the ability handle the CD
    p->buffs.pain_supression = buff_creator_t( p, "pain_supression",
                                               p->find_spell( 33206 ) );  // Let the ability handle the CD
  }
  void static_init() const override
  {
    items::init();
  }
  void register_hotfixes() const override
  {
    /** December 5th 2017 hotfixes

    hotfix::register_effect("Priest", "2017-12-05", "Shadow Priest damage increased by 3%", 191068)
    .field("base_value")
    .operation(hotfix::HOTFIX_SET)
    .modifier(23.0)
    .verification_value(20.0);

    hotfix::register_effect("Priest", "2017-12-05", "Shadow Priest damage increased by 3%", 179717)
    .field("base_value")
    .operation(hotfix::HOTFIX_SET)
    .modifier(23.0)
    .verification_value(20.0);

    hotfix::register_effect("Priest", "2017-12-05", "Vampiric Touch damage reduced by 15%.", 25010)
    .field("sp_coefficient")
    .operation(hotfix::HOTFIX_SET)
    .modifier(0.579)
    .verification_value(0.6816);

    hotfix::register_effect("Priest", "2017-12-05", "Shadow Word: Pain damage reduced by 15%.", 254257)
    .field("sp_coefficient")
    .operation(hotfix::HOTFIX_SET)
    .modifier(0.31)
    .verification_value(0.365);
    **/
  }

  void combat_begin( sim_t* ) const override
  {
  }
  void combat_end( sim_t* ) const override
  {
  }
};
}  // namespace priestspace
