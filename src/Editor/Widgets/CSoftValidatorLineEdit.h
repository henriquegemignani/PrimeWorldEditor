#ifndef CSOFTVALIDATORLINEEDIT_H
#define CSOFTVALIDATORLINEEDIT_H

#include "CTimedLineEdit.h"
#include <QValidator>

/**
 * A QLineEdit subclass that can use a QValidator to check if the input meets certain criteria.
 * If the criteria is met, the line edit has a green outline; otherwise, a red outline.
 * Unlike the normal QLineEdit validator, the effects of this are strictly cosmetic.
 */
class CSoftValidatorLineEdit : public CTimedLineEdit
{
    Q_OBJECT

    /** The validator that input is checked against */
    QValidator* mpSoftValidator;

    /** Whether to only validate when the user stops typing. Good for slow validators. */
    bool mOnlyValidateOnFinishedTyping;

    /** Whether the current input is valid */
    bool mInputIsValid;

signals:
    /** Emitted when the validity of the input changes */
    void SoftValidityChanged(bool NewValid);

protected slots:
    /** Internal update function */
    void InternalUpdate()
    {
        bool NewValidity = false;

        if ( mpSoftValidator )
        {
            int DummyPos;
            if ( mpSoftValidator->validate(text(), DummyPos) == QValidator::Acceptable )
            {
                NewValidity = true;
                setStyleSheet("border: 1px solid green");
            }
            else
            {
                NewValidity = false;
                setStyleSheet("border: 1px solid red");
            }
        }
        else
        {
            NewValidity = true;
            setStyleSheet("");
        }

        if (NewValidity != mInputIsValid)
        {
            mInputIsValid = NewValidity;
            emit SoftValidityChanged(mInputIsValid);
        }
    }

public:
    CSoftValidatorLineEdit(QWidget *pParent = 0)
        : CTimedLineEdit(pParent)
        , mpSoftValidator(nullptr)
        , mOnlyValidateOnFinishedTyping(false)
        , mInputIsValid(true)
    {}

    /** Set the soft validator to use */
    void SetSoftValidator(QValidator* pValidator)
    {
        if (mpSoftValidator)
        {
            disconnect(mpSoftValidator);
            mpSoftValidator = nullptr;
        }

        if (pValidator)
        {
            mpSoftValidator = pValidator;
            connect(mpSoftValidator, SIGNAL(changed()), this, SLOT(InternalUpdate()));
        }

        InternalUpdate();
    }

    /** Set whether the input should only be validated when the user finishes typing. */
    void SetOnlyDoSoftValidationOnFinishedTyping(bool Enable)
    {
        mOnlyValidateOnFinishedTyping = Enable;

        if (!mOnlyValidateOnFinishedTyping)
            InternalUpdate();
    }

    /** Check whether the input is valid */
    inline bool IsInputValid() const
    {
        return mInputIsValid;
    }

public slots:
    virtual void OnTextChanged()
    {
        CTimedLineEdit::OnTextChanged();

        if (!mOnlyValidateOnFinishedTyping)
        {
            InternalUpdate();
        }
    }

    virtual void OnTimeout()
    {
        CTimedLineEdit::OnTimeout();

        if (mOnlyValidateOnFinishedTyping)
        {
            InternalUpdate();
        }
    }
};

#endif // CSOFTVALIDATORLINEEDIT_H
