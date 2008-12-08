/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC Project 2007-2008, LGPL
 */
#ifndef ODBCQGPROPERTIESDIALOG_H
#define ODBCQGPROPERTIESDIALOG_H

#include <QtGui>

#include "ODBCQGProperty.h"
#include "ODBCQGPropertiesModel.h"

class ODBCQGPropertiesDelegate;

class ODBCQGPropertiesDialog : public QDialog
{
    Q_OBJECT
public:
    ODBCQGPropertiesDialog( QVector<ODBCQGProperty> vectorProperties, QWidget* pwidgetParent = NULL );
    virtual ~ODBCQGPropertiesDialog();

    QVector<ODBCQGProperty> getProperties() { return ppropertiesmodel->getProperties(); }

protected:
    void loadState();
    void saveState();

private:
    ODBCQGPropertiesModel *      ppropertiesmodel;
    ODBCQGPropertiesDelegate *   ppropertiesdelegate;
};

#endif

