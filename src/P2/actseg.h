#include <vec.h>
#include <util.h>

struct ACTLA
{
    int fUseTarget;
    struct ALO_conflict* paloTarget;
    struct VECTOR posTargetLocal;
    float sIgnore;
    int nPriorityEnabled;
    int nPriorityDisabled;
    int fPaused;
    struct CLQ clqPanToPan;
    struct LM lmPan;
    struct CLQ clqTiltToTilt;
    struct LM lmTilt;
};
