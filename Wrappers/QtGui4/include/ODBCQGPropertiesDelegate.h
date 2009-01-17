/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2007-2008, LGPL
 */
#ifndef OQGPROPERTIESDELEGATE_H
#define OQGPROPERTIESDELEGATE_H

#include <QItemDelegate>

/*!
 * \brief   Creates cell editor.
 *
 *          Creates cell editor for a property based upon OQGProperty. This is 
 *          applied to the second column of the QTableView.
 *          
 */
class OQGPropertiesDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    OQGPropertiesDelegate( QObject *pobjectParent = 0 );

    QWidget *createEditor(QWidget *pwidgetParent, const QStyleOptionViewItem &styleoptionviewitem, const QModelIndex &modelindex) const;
    void setEditorData( QWidget *pwidgetEditor, const QModelIndex &modelindex ) const;
    void setModelData( QWidget *pwidgetEditor, QAbstractItemModel *abstractitemmodel, const QModelIndex &modelindex) const;
    void updateEditorGeometry( QWidget *pwidgetEditor, const QStyleOptionViewItem &styleoptionviewitem, const QModelIndex &modelindex ) const;
};

#endif

