#ifndef CWAYPOINTEXTRA_H
#define CWAYPOINTEXTRA_H

#include "CScriptExtra.h"
#include "CSplinePathExtra.h"
#include <Common/CColor.h>

class CWaypointExtra : public CScriptExtra
{
    // Draw waypoint paths formed by script connections
    CColor mColor;
    bool mLinksBuilt;
    std::list<CSplinePathExtra*> mPaths;

    struct SWaypointLink
    {
        CScriptNode *pWaypoint;
        CAABox LineAABB;
    };
    std::vector<SWaypointLink> mLinks;

public:
    explicit CWaypointExtra(CScriptObject *pInstance, CScene *pScene, CScriptNode *pParent = 0);
    ~CWaypointExtra();
    void CheckColor();
    void AddToSplinePath(CSplinePathExtra *pPath);
    void RemoveFromSplinePath(CSplinePathExtra *pPath);
    void BuildLinks();
    bool IsPathLink(CLink *pLink);
    void GetLinkedWaypoints(std::list<CWaypointExtra*>& rOut);

    void OnTransformed();
    void LinksModified();
    void AddToRenderer(CRenderer *pRenderer, const SViewInfo& rkViewInfo);
    void Draw(FRenderOptions Options, int ComponentIndex, ERenderCommand Command, const SViewInfo& rkViewInfo);
    CColor TevColor();
};

#endif // CWAYPOINTEXTRA_H
