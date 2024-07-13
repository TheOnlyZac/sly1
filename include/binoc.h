/**
 * @file binoc.h
 *
 * @brief Binoc-u-com
 */
#ifndef BINOC_H
#define BINOC_H

#include "common.h"

/**
 * @brief Horizontal text justification
*/
typedef enum JH
{
    JH_Nil = -1,
    JH_Left = 0,
    JH_Center = 1,
    JH_Right = 2,
    JH_Max = 3
} JH;

/**
 * @brief Vertical text justification
*/
typedef enum JV
{
    JV_Nil = -1,
    JV_Top = 0,
    JV_Center = 1,
    JV_Bottom = 2,
    JV_Max = 3
} JV;

/**
 * @brief RGBA color value
*/
struct RGBA
{
    uchar bRed;
    uchar bGreen;
    uchar bBlue;
    uchar bAlpha;

    inline void operator=(const int rgba)
    {
        bRed = (rgba >> 24) & 0xFF;
        bGreen = (rgba >> 16) & 0xFF;
        bBlue = (rgba >> 8) & 0xFF;
        bAlpha = rgba & 0xFF;
    }
};

class CTextBox
{
public:
    void SetPos(float x, float y);
    void SetSize(float dx, float dy);
    void SetTextColor(RGBA* rgba);
    void SetHorizontalJust(JH jh);
    void SetVerticalJust(JV jv);

private:
    float m_x;
    float m_y;
    float m_dx;
    float m_dy;
    RGBA m_rgba;
    enum JH m_jh;
    enum JV m_jv;
};

#endif /* BINOC_H */
