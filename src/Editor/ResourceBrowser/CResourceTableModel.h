#ifndef CRESOURCETABLEMODEL
#define CRESOURCETABLEMODEL

#include "Editor/UICommon.h"
#include <Core/GameProject/CResourceEntry.h>
#include <Core/GameProject/CResourceIterator.h>
#include <Core/GameProject/CResourceStore.h>
#include <Core/Resource/CResource.h>
#include <QAbstractTableModel>
#include <QIcon>

class CResourceTableModel : public QAbstractTableModel
{
    Q_OBJECT
    QList<CResourceEntry*> mEntries;

public:
    CResourceTableModel(QObject *pParent = 0)
        : QAbstractTableModel(pParent)
    {}

    int rowCount(const QModelIndex& /*rkParent*/) const
    {
        return mEntries.size();
    }

    int columnCount(const QModelIndex& /*rkParent*/) const
    {
        return 3;
    }

    QVariant data(const QModelIndex& rkIndex, int Role) const
    {
        CResourceEntry *pEntry = mEntries[rkIndex.row()];
        u32 Col = rkIndex.column();

        if (Role == Qt::DisplayRole)
        {
            if (Col == 0) return TO_QSTRING(pEntry->Name());
            if (Col == 1) return TO_QSTRING(GetResourceTypeName(pEntry->ResourceType()));

            if (Col == 2)
            {
                u64 Size = pEntry->Size();
                return Size ? TO_QSTRING( TString::FileSizeString(pEntry->Size()) ) : "";
            }
        }

        else if (Role == Qt::ToolTipRole)
            return TO_QSTRING(pEntry->Directory()->FullPath() + pEntry->Name());

        else if (Role == Qt::TextAlignmentRole && rkIndex.column() == 2)
            return Qt::AlignRight;

        return QVariant::Invalid;
    }

    CResourceEntry* IndexEntry(const QModelIndex& rkIndex) const
    {
        return mEntries[rkIndex.row()];
    }

    void FillEntryList(CResourceStore *pStore)
    {
        beginResetModel();
        mEntries.clear();

        for (CResourceIterator It(pStore); It; ++It)
        {
            if (It->IsTransient()) continue;
            EResType Type = It->ResourceType();

            switch (Type)
            {
            case eArea:
            case eAreaCollision:
            case eAreaLights:
            case eAreaMaterials:
            case eAreaSurfaceBounds:
            case eAreaOctree:
            case eAreaVisibilityTree:
            case eMapArea:
            case eMapWorld:
            case ePathfinding:
            case ePortalArea:
            case eSaveArea:
            case eSaveWorld:
            case eStaticGeometryMap:
            case eTweak:
            case eWorld:
                continue;
            default:
                mEntries << *It;
            }
        }

        endResetModel();
    }
};

#endif // CRESOURCELISTMODEL
