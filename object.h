
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;
typedef double f64;

typedef u16 object_ref_t;
typedef u16 model_ref_t;

enum {
    OBJECT_ITEM,
    OBJECT_ITEM_DEFINITION,
    OBJECT_DODAD
    OBJECT_CONTAINER,
    OBJECT_CHARACTER,
    OBJECT_MISSILE
};

enum {
    ITEM_1H_DAGGER,
    ITEM_1H_SWORD,
    ITEM_1H_AXE,
    ITEM_1H_MACE,
    ITEM_2H_SWORD,
    ITEM_2H_AXE,
    ITEM_2H_MACE,
    ITEM_BOW,
    ITEM_ARROW,
    ITEM_HELM,
    ITEM_ARMOR,
    ITEM_GLOVES,
    ITEM_BOOTS,
    ITEM_SHEILD,
    ITEM_RING,
    ITEM_AMULET,
    ITEM_INGREDIENT,
    ITEM_POTION
};

enum {
    RACE_ALTMER,
    RACE_ARGONIAN,
    RACE_BOSMER,
    RACE_BRETON,
    RACE_DUNMER,
    RACE_IMPERIAL,
    RACE_KHAJIT,
    RACE_NORD,
    RACE_ORC,
    RACE_REDGUARD
};

enum {
    SKILL_ALTERATION,
    SKILL_CONJURATION,
    SKILL_DESTRUCTION,
    SKILL_ENCHANTING,
    SKILL_ILLUSION,
    SKILL_RESTORATION,
    SKILL_ARCHERY,
    SKILL_BLOCK,
    SKILL_HEAVY_ARMOR,
    SKILL_ONE_HANDED,
    SKILL_SMITHING,
    SKILL_TWO_HANDED,
    SKILL_ARCHERY,
    SKILL_LIGHT_ARMOR,
    SKILL_LOCKPICKING,
    SKILL_PICKPOCKET,
    SKILL_SNEAK,
    SKILL_SPEACH,
    SKILL_NUM
};

enum {
    // alteration
    PERK_NOVICE_ALTERATION,
    PERK_ALTERATION_DUAL_CASTING,
    PERK_APPRENTICE_ALTERATION,
    PERK_MAGIC_RESISTANCE_0,
    PERK_MAGIC_RESISTANCE_1,
    PERK_MAGIC_RESISTANCE_2,
    PERK_ADEPT_ALTERATION,
    PERK_EXPERT_ALTERATION,
    PERK_ATRONACH,
    PERK_MASTER_ALTERATION,
    PERK_STABILITY,
    PERK_MAGE_ARMOR_0,
    PERK_MAGE_ARMOR_1,
    PERK_MAGE_ARMOR_2,

    // conjuration
    PERK_NOVICE_CONJURATION,
    PERK_APPRENTICE_CONJURATION,
    PERK_ADEPT_CONJURATION,
    PERK_EXPER_CONJURATION,
    PERK_MASTER_CONJURATION,
    PERK_CONJURATION_DUAL_CASTING,
    PERK_MYSTIC_BINDING,
    PERK_SOUL_STEELER,
    PERK_OBLIVION_BINDER,
    PERK_NECROMANCY,
    PERK_DARK_SOULS,
    PERK_SUMMONER_0,
    PERK_SUMMONER_1,
    PERK_ATROMANCY,
    PERK_ELEMENTAL_POTENCY,
    PERK_TWIN_SOULS,

    // destruction
    PERK_NOVICE_DESTRUCTION,
    PERK_APPRENTICE_DESTRUCTION,
    PERK_ADEPT_DESTRUCTION,
    PERK_EXPERT_DESTRUCTION,
    PERK_MASTER_DESTRUCTION,
    PERK_RUNE_MASTER,
    PERK_AUGMENTED_FLAMES_0,
    PERK_AUGMENTED_FLAMES_1,
    PERK_INTENSE_FLAMES,
    PERK_AUGMENTED_FROST_0,
    PERK_AUGMENTED_FROST_1,
    PERK_DEEP_FREEZE,
    PERK_AUGMENTED_SHOCK_0,
    PERK_AUGMENTED_SHOCK_1,
    PERK_DISENTIGRATE,
    PERK_DESTRUCTION_DUAL_CASTING,
    PERK_IMPACT,

    // encanting
    PERK_ENCHANTER_0,
    PERK_ENCHANTER_1,
    PERK_ENCHANTER_2,
    PERK_ENCHANTER_3,
    PERK_ENCHANTER_4,
    PERK_FIRE_ENCHANTER,
    PERK_FROST_ENCHANTER,
    PERK_SHOCK_ENCHANTER,
    PERK_INSIGHTFUL_ENCHANTER,
    PERK_CORPUS_ENCHANTER,
    PERK_EXTRA_EFFECT,
    PERK_SOUL_SQUEEZER,
    PERK_SIPHON,

    // illusion
    PERK_NOVICE_ILLUSION,
    PERK_ANIMAGE,
    PERK_KINDRED_MAGE,
    PERK_QUIET_CASTING,
    PERK_APPRENTICE_ILLUSION,
    PERK_ADEPT_ILLUSION,
    PERK_EXPERT_ILLUSION,
    PERK_MASTER_ILLUSION,
    PERK_HYPNOTIC_GAZE,
    PERK_ASPECT_OF_TERROR,
    PERK_RAGE,
    PERK_MASTER_OF_THE_MIND,
    PERK_ILLUSION_DUAL_CASTING,

    // restoration
    PERK_NOVICE_RESTORATION,
    PERK_APPRENTICE_RESTORATION,
    PERK_ADEPT_RESTORATION,
    PERK_EXPERT_RESTORATION,
    PERK_MASTER_RESTORATION,
    PERK_RECOVERY_0,
    PERK_RECOVERY_1,
    PERK_AVOID_DEATH,
    PERK_REGENERATION,
    PERK_NECROMAGE,
    PERK_RESPITE,
    PERK_RESTORATION_DUAL_CASTING,
    PERK_WARD_ABSORB,

    // achery
    PERK_OVERDRAW_0,
    PERK_OVERDRAW_1,
    PERK_OVERDRAW_2,
    PERK_OVERDRAW_3,
    PERK_OVERDRAW_4,
    PERK_CRITICAL_SHOT_0,
    PERK_CRITICAL_SHOT_1,
    PERK_CRITICAL_SHOT_2,
    PERK_HUNTERS_DISCIPLINE,
    PERK_RANGER,
    PERK_EAGLE_EYE,
    PERK_POWER_SHOT,
    PERK_QUICK_SHOT,
    PERK_STEADY_HAND_0,
    PERK_STEADY_HAND_1,
    PERK_BULLSEYE,

    // block
    PERK_SHIELD_WALL_0,
    PERK_SHIELD_WALL_1,
    PERK_SHIELD_WALL_2,
    PERK_SHIELD_WALL_3,
    PERK_SHIELD_WALL_4,
    PERK_DEFLECT_ARROWS,
    PERK_ELEMENTAL_PROTECTION,
    PERK_BLOCK_RUNNER,
    PERK_POWER_BASH,
    PERK_DEADLY_BASH,
    PERK_DISARMING_BASH,
    PERK_SHIELD_CHARGE,
    PERK_QUICK_REFLEXES,

    // heavy armor
    PERK_JUGGERNAUT_0,
    PERK_JUGGERNAUT_1,
    PERK_JUGGERNAUT_2,
    PERK_JUGGERNAUT_3,
    PERK_JUGGERNAUT_4,
    PERK_FISTS_OF_STEEL,
    PERK_CUSHIONED,
    PERK_CONDITIONING,
    PERK_WELL_FITTED,
    PERK_TOWER_OF_STRENGTH,
    PERK_MATCHING_SET,
    PERK_REFLECT_BLOWS,

    // one-handed weapon
    PERK_ARMSMAN_0,
    PERK_ARMSMAN_1,
    PERK_ARMSMAN_2,
    PERK_ARMSMAN_3,
    PERK_ARMSMAN_4,
    PERK_BLADESMAN_0,
    PERK_BLADESMAN_1,
    PERK_BLADESMAN_2,
    PERK_BONE_BREAKER_0,
    PERK_BONE_BREAKER_1,
    PERK_BONE_BREAKER_2,
    PERK_DUAL_FLURRY_0,
    PERK_DUAL_FLURRY_1,
    PERK_DUAL_SAVEGERY,
    PERK_FIGHTING_CHANCE,
    PERK_CRITICAL_CHARGE,
    PERK_SAVAGE_STRIKE,
    PERK_PARALYZING_STRIKE,
    PERK_HACK_AND_SLASH_0,
    PERK_HACK_AND_SLASH_1,
    PERK_HACK_AND_SLASH_2,

    // smithing
    PERK_STEEL_SMITHING,
    PERK_ARCANE_BLACKSMITHING,
    PERK_DWARVEN_SMITHING,
    PERK_ORCISH_SMITHING,
    PERK_EBONY_SMITHING,
    PERK_DEADRIC_SMITHING,
    PERK_ELVEN_SMITHING,
    PERK_ADVANCED_ARMORS,
    PERK_GLASS_SMITHING,
    PERK_DRAGON_ARMOR,

    // two-handed weapon
    PERK_BARBARIAN_0,
    PERK_BARBARIAN_1,
    PERK_BARBARIAN_2,
    PERK_BARBARIAN_3,
    PERK_BARBARIAN_4,
    PERK_CHAMPIONS_STANCE,
    PERK_DEVASTATING_BLOW,
    PERK_GREAT_CRITICAL_CHARGE,
    PERK_SWEEP,
    PERK_WARMASTER,
    PERK_DEEP_WOUNDS_0,
    PERK_DEEP_WOUNDS_1,
    PERK_DEEP_WOUNDS_2,
    PERK_LIMBSPLITTER_0,
    PERK_LIMBSPLITTER_1,
    PERK_LIMBSPLITTER_2,
    PERK_SKULLCRUSHER_0,
    PERK_SKULLCRUSHER_1,
    PERK_SKULLCRUSHER_2,

    // alchemy
    PERK_ALCHEMIST_0,
    PERK_ALCHEMIST_1,
    PERK_ALCHEMIST_2,
    PERK_ALCHEMIST_3,
    PERK_ALCHEMIST_4,
    PERK_PHYSICIAN,
    PERK_BENEFACTOR,
    PERK_EXPERIMENTER_0,
    PERK_EXPERIMENTER_1,
    PERK_EXPERIMENTER_2,
    PERK_POISONER,
    PERK_CONSETRATED_POISON,
    PERK_GREEN_THUMB,
    PERK_SNAKEBLOOD,
    PERK_PURITY,

    // light armor
    PERK_AGILE_DEFENDER_0,
    PERK_AGILE_DEFENDER_1,
    PERK_AGILE_DEFENDER_2,
    PERK_AGILE_DEFENDER_3,
    PERK_AGILE_DEFENDER_4,
    PERK_CUSTOM_FIT,
    PERK_MATCHING_SET,
    PERK_UNHINDERED,
    PERK_WIND_WALKER,
    PERK_DEFT_MOVEMENT,

    // lockpicking
    PERK_NOVICE_LOCKS,
    PERK_APPRENTICE_LOCKS,
    PERK_QUICK_HANDS,
    PERK_WAX_KEY,
    PERK_ADEPT_LOCKS,
    PERK_EXPERT_LOCKS,
    PERK_GOLDEN_TOUCH,
    PERK_TREASURE_HUNTER,
    PERK_LOCKSMITH,
    PERK_UNBREAKABLE,
    PERK_MASTER_LOCKS,

    // pickpocket
    PERK_LIGHT_FINGERS_0,
    PERK_LIGHT_FINGERS_1,
    PERK_LIGHT_FINGERS_2,
    PERK_LIGHT_FINGERS_3,
    PERK_LIGHT_FINGERS_4,
    PERK_NIGHT_THEIF,
    PERK_CUTPURSE,
    PERK_KEYMASTER,
    PERK_MISDIRECTION,
    PERK_PERFECT_TOUCH,
    PERK_EXTRA_POCKETS,
    PERK_POISONED,

    // sneak
    PERK_STEALTH_0,
    PERK_STEALTH_1,
    PERK_STEALTH_2,
    PERK_STEALTH_3,
    PERK_STEALTH_4,
    PERK_BACKSTAB,
    PERK_DEADLY_AIM,
    PERK_ASSASSINS_BLADE,
    PERK_MUFFLED_MOVEMENT,
    PERK_LIGHT_FOOT,
    PERK_SILENT_ROLL,
    PERK_SILENCE,
    PERK_SHADOW_WARRIOR,

    // speech
    PERK_HAGGLING_0,
    PERK_HAGGLING_1,
    PERK_HAGGLING_2,
    PERK_HAGGLING_3,
    PERK_HAGGLING_4,
    PERK_ALLURE,
    PERK_MERCHANT,
    PERK_INVESTOR,
    PERK_FENCE,
    PERK_MASTER_TRADER,
    PERK_BRIBERY,
    PERK_PERSUASION,
    PERK_INTIMIDATION,

    PERK_NUM
};

// object is designed to be easy to seralize
struct object_head {
    u16 id;
    u16 base;
    u8  tag;
};
struct object_name {
    char name[64];
};
struct object_matrix {
    f32 matrix[4*4];
};
struct object_model {
    u16 model;
};
struct object_inventory {
    u16 inventory_items;
    u16 *inventory;
};
struct object_owner {
    u16 owner;
};
struct object_item_data {
    u16 weight;
    u16 price;
    u8  kind;
    u8  effects[4];
    u8  effect_strength;
};
struct object_character_data {
    u8  level;
    u16 experince;
    u16 hand_1;
    u16 hand_2;
    u16 helm;
    u16 armor;
    u16 gloves;
    u16 boots;
    u16 ring;
    u16 amulet;
    u8  skills[SKILL_NUM];
    u8  perks[(PERK_NUM+7)>>3];
    u8  race;
    u32 face;
};

struct item {
    struct object_head   head;
    struct object_matrix matrix;
    struct object_owner  owner;
};
struct item_def {
    struct object_head      head;
    struct object_name      name;
    struct object_model     model;
    struct object_owner     owner;
    struct object_item_data data;
};
struct missile {
    struct object_head   head;
    struct object_matrix matrix;
    struct object_model  model;
    struct object_owner  owner;
};
struct dodad {
    struct object_head   head;
    struct object_matrix matrix;
    struct object_model  model;
};
struct container {
    struct object_head      head;
    struct object_name      name;
    struct object_matrix    matrix;
    struct object_model     model;
    struct object_inventory inventory;
};
struct character {
    struct object_head           head;
    struct object_name           name;
    struct object_matrix         matrix;
    struct object_inventory      inventory;
    struct object_character_data data;
};

union object {
    struct object_head head;
    struct item        item;
    struct item_def    item_def;
    struct missile     missile;
    struct dodad       dodad;
    struct container   container;
    struct character   character;
};

