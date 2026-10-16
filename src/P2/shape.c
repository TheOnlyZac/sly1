#include <shape.h>
#include <brx.h>

extern MATRIX4 g_mat4Identity; // TODO: Move elsewhere.

void LoadShapeFromBrx(SHAPE *pshape, CBinaryInputStream *pbis)
{
    CRVK crvk = (CRVK)pbis->U8Read();
    CRV *pcrv = PcrvNew(crvk);
    pshape->pcrv = pcrv;

    if (pcrv->pvtcrv->pfnLoadCrvFromBrx)
    {
        pcrv->pvtcrv->pfnLoadCrvFromBrx(pcrv, pbis);
    }

    LoadOptionsFromBrx(pshape, pbis);
}

void SetShapeParent(SHAPE *pshape, ALO *paloParent)
{
    MATRIX4 matSrc;
    if (pshape->paloParent)
    {
        LoadMatrixFromPosRot(&pshape->paloParent->xf.posWorld, &pshape->paloParent->xf.matWorld, &matSrc);
    }
    else
    {
        matSrc.data[0] = g_mat4Identity.data[0];
        matSrc.data[1] = g_mat4Identity.data[1];
        matSrc.data[2] = g_mat4Identity.data[2];
        matSrc.data[3] = g_mat4Identity.data[3];
    }

    MATRIX4 matDst;
    if (paloParent)
    {
        LoadMatrixFromPosRot(&paloParent->xf.posWorld, &paloParent->xf.matWorld, &matDst);
    }
    else
    {
        matDst.data[0] = g_mat4Identity.data[0];
        matDst.data[1] = g_mat4Identity.data[1];
        matDst.data[2] = g_mat4Identity.data[2];
        matDst.data[3] = g_mat4Identity.data[3];
    }

    if (pshape->pcrv->pvtcrv->pfnConvertCrv)
    {
        pshape->pcrv->pvtcrv->pfnConvertCrv(pshape->pcrv, &matSrc, &matDst);
    }

    SetLoParent(pshape, paloParent);
}
