#ifndef CTEMPLATEEDITDIALOG_H
#define CTEMPLATEEDITDIALOG_H

#include "Editor/CPropertyNameValidator.h"
#include <Core/Resource/Script/Property/Properties.h>
#include <Core/Resource/Script/CGameTemplate.h>
#include <QDialog>

namespace Ui {
class CTemplateEditDialog;
}

class CTemplateEditDialog : public QDialog
{
    Q_OBJECT
    Ui::CTemplateEditDialog* mpUI;
    CPropertyNameValidator* mpValidator;

    IProperty *mpProperty;
    EGame mGame;

    TString mOriginalName;
    TString mOriginalDescription;
    TString mOriginalTypeName;
    bool mOriginalAllowTypeNameOverride;
    bool mOriginalNameWasValid;

    // These members help track what templates need to be updated and resaved after the user clicks OK
    QVector<IProperty*> mEquivalentProperties;

public:
    CTemplateEditDialog(IProperty* pProperty, QWidget *pParent = 0);
    ~CTemplateEditDialog();

signals:
    void PerformedTypeConversion();

public slots:
    void ApplyChanges();
    void RefreshTypeNameOverride();

protected slots:
    void ConvertPropertyType(EPropertyType Type);
    void ConvertToInt();
    void ConvertToChoice();
    void ConvertToSound();
    void ConvertToFlags();

protected:
    void UpdateDescription(const TString& rkNewDesc);
    void UpdateTypeName(const TString& kNewTypeName, bool AllowOverride);
    void FindEquivalentProperties(IProperty *pProperty);
};

#endif // CTEMPLATEEDITDIALOG_H
