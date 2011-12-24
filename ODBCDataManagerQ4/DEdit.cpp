/*!
 * \file
 *
 * \author  Peter Harvey <pharvey@peterharvey.org>
 * \author  \sa AUTHORS file
 * \version 2
 * \date    2007
 * \license Copyright unixODBC-GUI-Qt Project 2007-2012, See GPL.txt
 */
#include "DEdit.h"

DEdit::DEdit( QWidget *pwidgetParent, DNode *pNode )
    : QWidget( pwidgetParent )
{
    this->pNode = pNode;

    setWindowIcon( pNode->icon( 0 ) );
    setWindowTitle( pNode->text( 0 ) );
}

void DEdit::setActionSubmit( QAction * )
{
}
