/**
 * @file zap.h
 *
 * @brief Declarations for the zap (damage) system.
*/
#ifndef ZAP_H
#define ZAP_H

/**
 * @brief Zap
 *
 * A volume that damages the player upon contact.
*/
struct ZAP
{
    // todo
    // ...
};

/**
 * @brief Zap Kind?
 *
 * @note Unsure what the O stands for.
*/
enum ZOK
{
    ZOK_Inherit = 0,
    ZOK_Zap = 1,
    ZOK_NoZap = 2,
    ZOK_Ignore = 3,
    ZOK_ZapAndIgnore = 4,
    ZOK_Max = 5
};

#endif // ZAP_H
