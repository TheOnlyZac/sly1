#pragma once
#include <util.h>

/**
 * Horizontal justification
 */
enum JH
{
    JH_Left = 0,
    JH_Center = 1,
    JH_Right = 2,
    JH_Max = 3
};

/**
 * Vertical justification
 */
enum JV
{
    JV_Top = 0,
    JV_Center = 1,
    JV_Bottom = 2,
    JV_Max = 3
};

/**
 * 4-byte color value
 */
struct RGBA {
    BYTE bRed;
    BYTE bGreen;
    BYTE bBlue;
    BYTE bAlpha;
};

/**
 * ScaleFactorRatio or ScaleFontRatio
 *
 * Unknown, used by CFont class (probably to scale fonts)
 */
struct SFR
{
    float rx;
    float ry;
};

struct _vtbl_ptr_type; // todo: fix type

/**
 * Font class
 *
 * Represents a font used for text rendering
 */
class CFont
{
protected:
    int m_dxCharUnscaled;
    int m_dxSpaceUnscaled;
    int m_dyUnscaled;
    int m_csfr;
    struct SFR m_asfr[4]; // 4 different scale factors, each to be used in a different situation?
    int m_fGstest;
    int field_0x34; // unknown
    /* todo: figure out these types
    u64 m_gstest;
    u32 m_z; */

private:
    float m_rxScale;
    float m_ryScale;
    _vtbl_ptr_type* vf5078;
};

/**
 * Text box class
 *
 * Represents a text box used for text rendering
 */
class CTextBox
{
private:
    float m_x; // x pos
    float m_y; // y pos
    float m_dx; // x size
    float m_dy; // y size
    RGBA m_rgba; // text color
    JH m_jh; // horizontal justification
    JV m_jv; // vertical justification

public:
    /**
     * @brief Set text box position.
     *
     * @param x X position.
     * @param y Y position.
     */
    void SetPos(float x, float y);

    /**
     * @brief Set text box size.
     *
     * @param dx X size.
     * @param dy Y size.
     */
    void SetSize(float dx, float dy);

    /**
     * @brief Set text box text color.
     *
     * @param rgba Text color.
     */
    void SetTextColor(RGBA rgba);

    /**
     * @brief Set text box horizontal justification.
     *
     * @param jh Horizontal justification.
      */
    void SetHorizontalJust(JH jh);

    /**
     * @brief Set text box vertical justification.
     *
     * @param jv Vertical justification.
     */
    void SetVerticalJust(JV jv);
};
