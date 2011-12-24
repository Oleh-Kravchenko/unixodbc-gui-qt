/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2008, LGPL
 */
#ifndef OQGPROPERTIESDIALOG_H
#define OQGPROPERTIESDIALOG_H

#include <QtGui>

#include "OQGProperty.h"
#include "OQGPropertiesModel.h"

class OQGPropertiesDelegate;

class OQGPropertiesDialog : public QDialog
{
    Q_OBJECT
public:
    OQGPropertiesDialog( QVector<OQGProperty> vectorProperties, QWidget* pwidgetParent = NULL );
    virtual ~OQGPropertiesDialog();

    QVector<OQGProperty> getProperties() { return ppropertiesmodel->getProperties(); }

protected:
    void loadState();
    void saveState();

private:
    OQGPropertiesModel *      ppropertiesmodel;
    OQGPropertiesDelegate *   ppropertiesdelegate;
};

#endif

