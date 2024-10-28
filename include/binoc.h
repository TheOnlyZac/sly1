/**
 * @file binoc.h
 *
 * @brief Binoc-u-com.
 */
#ifndef BINOC_H
#define BINOC_H

#include "common.h"
#include <screen.h>

struct BINOC : public BLOT {
    void *vtbinoc;
    undefined1 padding_0[116];
    float value0;
    undefined4 value1;
    undefined1 padding_1[8];
    float zoom;
};

/**
 * @brief Horizontal text justification.
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
 * @brief Vertical text justification.
 */
typedef enum JV
{
    JV_Nil = -1,
    JV_Top = 0,
    JV_Center = 1,
    JV_Bottom = 2,
    JV_Max = 3
} JV;

class CTextBox
{
public:
    /**
     * @brief Sets the position of the text box.
     *
     * @param x X position.
     * @param y Y position.
     */
    void SetPos(float x, float y);

    /**
     * @brief Sets the size of the text box.
     *
     * @param dx Width.
     * @param dy Height.
     */
    void SetSize(float dx, float dy);

    /**
     * @brief Sets the text color.
     *
     * @param rgba RGBA color value.
     */
    void SetTextColor(RGBA *rgba);

    /**
     * @brief Sets the horizontal text justification.
     *
     * @param jh Horizontal text justification.
     */
    void SetHorizontalJust(JH jh);

    /**
     * @brief Sets the vertical text justification.
     *
     * @param jv Vertical text justification.
     */
    void SetVerticalJust(JV jv);

private:
    float m_x;    // X position.
    float m_y;    // Y position.
    float m_dx;   // Width.
    float m_dy;   // Height.
    RGBA m_rgba;  // Text color.
    enum JH m_jh; // Horizontal text justification.
    enum JV m_jv; // Vertical text justification;
};

#endif /* BINOC_H */
