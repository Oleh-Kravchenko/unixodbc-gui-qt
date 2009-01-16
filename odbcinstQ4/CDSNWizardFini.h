/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2009, LGPL
 */
#ifndef CDSNWIZARDFINI_H
#define CDSNWIZARDFINI_H

#include "CODBCInst.h"

#include <QWizardPage>

/*! 
 * \class   CDSNWizardFini
 * \brief   Last page of create data source name wizard.
 * 
 *          This page states that all needed info has been collected - click
 *          and your done.
 *
 * \sa      CDSNWizard
 */
class CDSNWizardFini : public QWizardPage
{
     Q_OBJECT
public:
     CDSNWizardFini( CDSNWizardData *pWizardData, QWidget *pwidgetParent = 0 );

     int nextId() const;
     void initializePage();
     void cleanupPage();

protected:
     CDSNWizardData *pWizardData;
};

#endif


