/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#ifndef ODBCDELEGATECELL_H
#define ODBCDELEGATECELL_H

#include <QItemDelegate>

/*!
 * \brief   Creates cell editor.
 *
 *          Creates cell editor based upon \sa ODBCValueCell as the uber value.
 *          
 */
class ODBCDelegateCell : public QItemDelegate
{
    Q_OBJECT
public:
    ODBCDelegateCell( QObject *pobjectParent = 0 );

    QWidget *createEditor(QWidget *pwidgetParent, const QStyleOptionViewItem &styleoptionviewitem, const QModelIndex &modelindex) const;
    void setEditorData( QWidget *pwidgetEditor, const QModelIndex &modelindex ) const;
    void setModelData( QWidget *pwidgetEditor, QAbstractItemModel *abstractitemmodel, const QModelIndex &modelindex) const;
    void updateEditorGeometry( QWidget *pwidgetEditor, const QStyleOptionViewItem &styleoptionviewitem, const QModelIndex &modelindex ) const;
};

#endif

