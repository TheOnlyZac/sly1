struct VTBLOT
{
    void *pfnInitBlot;
    void *pfnPostBlotLoad;
    void *pfnUpdateBlot;
    void *pfnOnBlotActive;
    void *pfnUpdateBlotActive;
    void *pfnOnBlotReset;
    void *pfnOnBlotPush;
    void *pfnOnBlotPop;
    void *pfnSetBlotAchzDraw;
    void *pfnDrawBlot;
    void *pfnRenderBlot;
    void *pfnDtAppearBlot;
    void *pfnDtVisibleBlot;
    void *pfnDtDisappearBlot;
    void *pfnShowBlot;
    void *pfnHideBlot;
    void *pfnSetBlotBlots;
    void *pfnSetBlotClock;
    void *pfnFIncludeBlotForPeg;
};

struct VTNOTE
{
    void *pfnInitBlot;
    void *pfnPostNoteLoad;
    void *pfnUpdateBlot;
    void *pfnOnBlotActive;
    void *pfnUpdateBlotActive;
    void *pfnOnBlotReset;
    void *pfnOnBlotPush;
    void *pfnOnBlotPop;
    void *pfnSetNoteAchzDraw;
    void *pfnDrawNote;
    void *pfnRenderBlot;
    void *pfnDtAppearBlot;
    void *pfnDtVisibleBlot;
    void *pfnDtDisappearBlot;
    void *pfnShowBlot;
    void *pfnHideBlot;
    void *pfnSetBlotBlots;
    void *pfnSetBlotClock;
    void *pfnFIncludeBlotForPeg;
};
