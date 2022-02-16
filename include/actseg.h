#include <vec.h>

struct ACTLA
{
    int fUseTarget;
    struct ALO_conflict* paloTarget;
    struct VECTOR posTargetLocal;
    float sIgnore;
    int nPriorityEnabled;
    int nPriorityDisabled;
    int fPaused;
    //struct CLQ_21 clqPanToPan;
    //struct LM_21 lmPan;
    //struct CLQ_21 clqTiltToTilt;
    //struct LM_21 lmTilt;
};