#ifndef VTABLES_H
#define VTABLES_H

struct BLOT;

struct VTBLOT
{
    void (*pfnInitBlot)(BLOT *);
    void (*pfnPostBlotLoad)(BLOT *);
    void (*pfnUpdateBlot)(BLOT *);
    void (*pfnOnBlotActive)(BLOT *);
    void (*pfnUpdateBlotActive)(BLOT *);
    void (*pfnOnBlotReset)(BLOT *);
    void (*pfnOnBlotPush)(BLOT *);
    void (*pfnOnBlotPop)(BLOT *);
    void (*pfnSetBlotAchzDraw)(BLOT *, const char *);
    void (*pfnDrawBlot)(BLOT *);
    void (*pfnRenderBlot)(BLOT *);
    void (*pfnDtAppearBlot)(BLOT *);
    void (*pfnDtVisibleBlot)(BLOT *);
    void (*pfnDtDisappearBlot)(BLOT *);
    void (*pfnShowBlot)(BLOT *);
    void (*pfnHideBlot)(BLOT *);
    void (*pfnSetBlotBlots)(BLOT *);
    void (*pfnSetBlotClock)(BLOT *);
    int  (*pfnFIncludeBlotForPeg)(BLOT *);
};

struct VTNOTE
{
    void (*pfnInitBlot)(BLOT *);
    void (*pfnPostNoteLoad)(BLOT *);
    void (*pfnUpdateBlot)(BLOT *);
    void (*pfnOnBlotActive)(BLOT *);
    void (*pfnUpdateBlotActive)(BLOT *);
    void (*pfnOnBlotReset)(BLOT *);
    void (*pfnOnBlotPush)(BLOT *);
    void (*pfnOnBlotPop)(BLOT *);
    void (*pfnSetNoteAchzDraw)(BLOT *, const char *);
    void (*pfnDrawNote)(BLOT *);
    void (*pfnRenderBlot)(BLOT *);
    void (*pfnDtAppearBlot)(BLOT *);
    void (*pfnDtVisibleBlot)(BLOT *);
    void (*pfnDtDisappearBlot)(BLOT *);
    void (*pfnShowBlot)(BLOT *);
    void (*pfnHideBlot)(BLOT *);
    void (*pfnSetBlotBlots)(BLOT *);
    void (*pfnSetBlotClock)(BLOT *);
    int  (*pfnFIncludeBlotForPeg)(BLOT *);
};

#endif // VTABLES_H
