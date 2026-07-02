/**
 * @file binoc.h
 *
 * @brief Binoc-u-com.
 */
#ifndef BINOC_H
#define BINOC_H

#include "common.h"
#include <screen.h>
#include <util.h>

struct ALO;

/**
 * @brief Binocular Edge Info (?)
 * 
 * @note Used for binocular outline rendering
 */
struct BEI
{
    /* 0x00 */ CLQ clq;             // Quadratic curve parameters
    /* 0x10 */ float cseg;          // Total number of segments
    /* 0x14 */ float csegNotchHalf; // Half the number of segments in the notch
    /* 0x18 */ int isegNotchFirst;  // First segment index of the notch
    /* 0x1c */ int isegNotchMid;    // Middle segment index of the notch
    /* 0x20 */ int isegNotchLast;   // Last segment index of the notch
    /* 0x24 */ float gNotchEdge;    // Y value at the notch edges
    /* 0x28 */ float gNotchCenter;  // Y value at the notch center
};

struct BINOC : public BLOT
{
    STRUCT_PADDING(36);
    float unk0;
    undefined4 unk1; // RGBA color value?
    undefined4 unk2;
    ALO *paloLookat;
    float zoom;
    float dxReticle;
    float dyReticle;
    undefined4 unk3;
    undefined4 unk4;
    float uCompassBarOffset;
};

/**
 * @brief Initializes a BEI struct for binocular outline rendering.
 *
 * @details Sets up the quadratic curve parameters and calculates segment indices for the
 *          notch region in the binocular outline. The notch is positioned at the midpoint
 *          of the curve for UI elements like the compass.
 *
 * @param pbei Pointer to the BEI struct to initialize.
 * @param pclq Pointer to the quadratic curve (CLQ) defining the outline shape.
 * @param duWidth Width of the notch.
 * @param dgHeight Vertical offset for the notch center.
 * @param cseg Total number of segments to divide the curve into.
 */
void InitBei(BEI *pbei, CLQ *pclq, float duWidth, float dgHeight, int cseg);

/**
 * @brief Evaluates the binocular edge curve at a given segment.
 *
 * @details Returns the Y-coordinate for the outline at segment index iseg. For segments
 *          outside the notch region, evaluates the quadratic curve directly. Within the
 *          notch, performs linear interpolation between edge and center values to create
 *          a V shaped cutout.
 *
 * @param pbei Pointer to the BEI struct containing curve and notch parameters.
 * @param iseg Segment index along the outline.
 * @return Y-coordinate value for the outline at this segment.
 */
float GEvaluateBei(BEI *pbei, int iseg);

/**
 * @brief Checks if the binocular text reveal animation is complete.
 *
 * @param pbinoc Pointer to BINOC instance.
 * @return true if the text animation is complete, false otherwise.
 */
bool FDoneBinocAchz(BINOC *pbinoc);

void SetBinocLookat(BINOC *binoc, ALO *paloLookat);

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

extern "C" void open_close_binoc(BINOC *pbinoc, int state);

#endif /* BINOC_H */
