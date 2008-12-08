
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
