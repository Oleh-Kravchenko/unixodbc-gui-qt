#ifndef ODBCVALUECELL_H
#define ODBCVALUECELL_H

#include <QtCore>

/*!
 * \class   ODBCValueCell
 * \brief   Provided by some models, as cell/item date, to \sa ODBCDelegateCell.
 *
 *          This class can be loaded - then passed to/from model and delegate. This
 *          basically describes display and editing features for data in a 'cell' incl.
 *          the data itself. In this way a single delegate (ODBCDelegateCell) can handle 
 *          just about any editing tasks.
 * 
 * \author  pharvey (8/9/2008)
 */
class ODBCValueCell
{
public:
    enum PromptTypes
    {
        PromptTypeDefault, // based upon QVariant::Type
        PromptTypeLabel,
        PromptTypeCombo,
        PromptTypeList,
        PromptTypeText,
        PromptTypePassword,
        PromptTypeDir,
        PromptTypeFile,
        PromptTypeBool,
        PromptTypeHidden
    };

    ODBCValueCell();

    PromptTypes         nPromptType;
    QVariant            vValue;                     // current value
    QVariant            vValueOriginal;             // original value
    QVariant            vValueDefault;              // default value
    QString             stringDescription;          // describes this data item

    // for list/combo boxs
    QVector<QVariant>   vectorValues;               // for display
    QVector<QVariant>   vectorDescriptions;         // descriptions of each value
};

#endif

