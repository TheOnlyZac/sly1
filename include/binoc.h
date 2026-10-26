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
 * @brief Binoc-u-com Edge Info (?)
 * 
 * @note Used for Binoc-u-com outline rendering
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

/**
 * @brief Binoc-u-com State.
 */
enum BINOCS
{
    BINOCS_Nil = -1,
    BINOCS_None = 0,
    BINOCS_Peek = 1,
    BINOCS_Dialog = 2,
    BINOCS_Instruct = 3,
    BINOCS_Confront = 4,
    BINOCS_Sniper = 5,
    BINOCS_Max = 6
};

struct BINOC : public BLOT
{
    int binocs;
    float tBinocs;
    float tAchzSet;
    int cichLR;
    int aichLR[32];
    float svch;
    RGBA rgbaText;
    char chPause;
    char pad_0x2f9[3];
    ALO *paloLookat;
    float uZoom;
    float dxReticle;
    float dyReticle;
    float radReticle;
    CFont *pfontCompass;
    float uCompassBarOffset;
    undefined4 unk3;
    undefined4 unk4;
};

/**
 * @brief Initializes a BEI struct for Binoc-u-com outline rendering.
 *
 * @details Sets up the quadratic curve parameters and calculates segment indices for the
 *          notch region in the Binoc-u-com outline. The notch is positioned at the midpoint
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
 * @brief Evaluates the Binoc-u-com edge curve at a given segment.
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
 * @brief Checks if the Binoc-u-com text reveal animation is complete.
 *
 * @param pbinoc Pointer to BINOC instance.
 * @return true if the text animation is complete, false otherwise.
 */
bool FDoneBinocAchz(BINOC *pbinoc);

void SetBinocLookat(BINOC *binoc, ALO *paloLookat);

void SetBinocZoom(BINOC *binoc, float zoom);

void open_close_binoc(void *pbinoc, BINOCS binocs);

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

extern BINOC g_binoc;

#endif /* BINOC_H */
