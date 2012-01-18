#ifndef DATA_H
#define DATA_H

enum {
    SWORD,
    MACE,
    WAR_AXE,
    DAGGER,

    GREATSWORD,
    WARHAMMER,
    BATTLEAXE,

    BOW,
    ARROW,

    LIGHT_ARMOR,
    LIGHT_BOOT,
    LIGHT_GUANTLET,
    LIGHT_HELMET,
    LIGHT_SHEILD,
    HEAVY_ARMOR,
    HEAVY_BOOT,
    HEAVY_GUANTLET,
    HEAVY_HELMET,
    HEAVY_SHEILD,

    INGREDIENT,
    POTION,
    POISON,
    BOOK,
    SCROLL,
    SPELL_BOOK,
    MISC,

    ITEM_INSTANCE,

    HUMAN,
    ORC,
    ELF,
    DWARF,
    HALF_ELF,

    MODEL, // simply a model, referenced by dodads
    DODAD
};

enum {
#define DATUM(ENUM, ...) DATUM_ ## ENUM,
#include "data.x"
#undef DATUM
    DATUM_NUM
};

struct data {
    char *name;
    int  kind;
    char *contents; // book
    float x, y;
    float rotation;
    float damage;
    float armor;
    float price;
    float weight;
    float speed;
    float width;
    float height;
    unsigned int base;
    const char *model;
};

extern struct data game_data[DATUM_NUM];

#endif
