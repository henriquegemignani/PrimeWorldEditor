#ifndef CRESOURCEBROWSER_H
#define CRESOURCEBROWSER_H

#include "CResourceDelegate.h"
#include "CResourceProxyModel.h"
#include "CResourceTableModel.h"
#include "CVirtualDirectoryModel.h"
#include <QCheckBox>
#include <QTimer>
#include <QUndoStack>
#include <QVBoxLayout>

namespace Ui {
class CResourceBrowser;
}

class CResourceBrowser : public QWidget
{
    Q_OBJECT
    Ui::CResourceBrowser *mpUI;
    CResourceEntry *mpSelectedEntry;
    CResourceStore *mpStore;
    CResourceTableModel *mpModel;
    CResourceProxyModel *mpProxyModel;
    CResourceBrowserDelegate *mpDelegate;
    CVirtualDirectory *mpSelectedDir;
    CVirtualDirectoryModel *mpDirectoryModel;
    bool mEditorStore;
    bool mAssetListMode;
    bool mSearching;

    // Type Filter
    QWidget *mpFilterBoxesContainerWidget;
    QVBoxLayout *mpFilterBoxesLayout;
    QCheckBox *mpFilterAllBox;
    QFont mFilterBoxFont;

    struct SResourceType
    {
        CResTypeInfo *pTypeInfo;
        QCheckBox *pFilterCheckBox;
    };
    QList<SResourceType> mTypeList;

    // Undo/Redo
    QUndoStack mUndoStack;
    QAction *mpUndoAction;
    QAction *mpRedoAction;
    QWidget *mpActionContainerWidget;

public:
    explicit CResourceBrowser(QWidget *pParent = 0);
    ~CResourceBrowser();

    void SelectResource(CResourceEntry *pEntry);
    void SelectDirectory(CVirtualDirectory *pDir);
    void CreateFilterCheckboxes();

    bool RenameResource(CResourceEntry *pEntry, const TString& rkNewName);
    bool RenameDirectory(CVirtualDirectory *pDir, const TString& rkNewName);
    bool MoveResources(const QList<CResourceEntry*>& rkResources, const QList<CVirtualDirectory*>& rkDirectories, CVirtualDirectory *pNewDir);

    // Interface
    bool eventFilter(QObject *pWatched, QEvent *pEvent);

    // Accessors
    inline CResourceStore* CurrentStore() const     { return mpStore; }
    inline CResourceEntry* SelectedEntry() const    { return mpSelectedEntry; }
    inline bool InAssetListMode() const             { return mAssetListMode || mSearching; }

public slots:
    void RefreshResources();
    void RefreshDirectories();
    void UpdateDescriptionLabel();
    void SetResourceTreeView();
    void SetResourceListView();
    void OnSortModeChanged(int Index);
    void OnSearchStringChanged(QString SearchString);
    void OnDirectorySelectionChanged(const QModelIndex& rkNewIndex, const QModelIndex& rkPrevIndex);
    void OnDoubleClickTable(QModelIndex Index);
    void OnResourceSelectionChanged(const QModelIndex& rkNewIndex, const QModelIndex& rkPrevIndex);
    void SetAssetIdDisplayEnabled(bool Enable);

    void UpdateStore();
    void SetProjectStore();
    void SetEditorStore();
    void ImportPackageContentsList();
    void GenerateAssetNames();
    void ImportAssetNameMap();
    void ExportAssetNames();
    void RebuildResourceDB();
    void UpdateFilter();

    void ResetTypeFilter();
    void OnFilterTypeBoxTicked(bool Checked);

    void UpdateUndoActionStates();
    void Undo();
    void Redo();

signals:
    void SelectedResourceChanged(CResourceEntry *pNewRes);
    void ResourceMoved(CResourceEntry *pRes, CVirtualDirectory *pOldDir, TString OldName);
    void DirectoryMoved(CVirtualDirectory *pDir, CVirtualDirectory *pOldDir, TString OldName);
};

#endif // CRESOURCEBROWSER_H
