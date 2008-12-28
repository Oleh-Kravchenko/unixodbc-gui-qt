/*********************************************************************
 *
 * Written by Nick Gorham
 * (nick@lurcher.org).
 *
 * copyright (c) 1999 Nick Gorham
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 **********************************************************************
 *
 * 2008-12-10   Code adopted by unixODBC-GUI-Qt project. Heavily altered
 * pharvey      to be Qt4 only code.
 * 
 **********************************************************************/

#include "DlgToolsManageTestGroup.h"
#include "DlgToolsNewGroup.h"
#include "OdbcTest.h"

DlgToolsManageTestGroup::DlgToolsManageTestGroup( OdbcTest *pOdbcTest, QString name )
    : QDialog( pOdbcTest )
{
    setWindowTitle( name );

    this->pOdbcTest = pOdbcTest;

    nw = new QPushButton( "New", this );
    nw->setGeometry( 300,15, 70,25 );

    del = new QPushButton( "Delete", this );
    del->setGeometry( 380,15, 70,25 );

    add = new QPushButton( "Add >", this );
    add->setGeometry( 280,90, 70,25 );

    remove = new QPushButton( "< Remove", this );
    remove->setGeometry( 280,130, 70,25 );

    close = new QPushButton( "Close", this );
    close->setGeometry( 280,200, 70,25 );

    group = new QComboBox( this );
    group->setGeometry( 100, 15, 180, 20 );

    l_group = new QLabel( "Test Group:", this );
    l_group->setGeometry( 10, 15, 60, 20 );

    l_auto = new QLabel( "Installed Auto Tests:", this );
    l_auto->setGeometry( 10, 60, 160, 20 );

    l_sauto = new QLabel( "Selected Auto Tests:", this );
    l_sauto->setGeometry( 370, 60, 160, 20 );

    auto_list = new QListWidget( this );
    auto_list->setGeometry( 10, 80, 250, 160 );

    sauto_list = new QListWidget( this );
    sauto_list->setGeometry( 370, 80, 250, 160 );

    connect( close, SIGNAL(clicked()), SLOT(Ok()) );
    connect( close, SIGNAL(clicked()), SLOT(accept()) );
    connect( add, SIGNAL(clicked()), SLOT(Add()) );
    connect( remove, SIGNAL(clicked()), SLOT(Remove()) );
    connect( nw, SIGNAL(clicked()), SLOT(New()) );
    connect( del, SIGNAL(clicked()), SLOT(Delete()) );

    //
    // fill up combo box
    //

    section *s = find_section( "GROUPS" );

    if ( s )
    {
        prop *p;

        for ( p = s->first(); 
            p != 0; 
            p = s->next())
        {
            group->addItem( p->name() );
        }
    }

    Activated( 0 );
    connect( group, SIGNAL(activated(const QString &)), 
             this, SLOT( Activated(const QString &)));
}

DlgToolsManageTestGroup::~DlgToolsManageTestGroup()
{
    // sync settings with disk (mostly means 'save changes')
    {
        pOdbcTest->pSettings->sync();
        QSettings::Status nStatus = pOdbcTest->pSettings->status();
        switch ( nStatus )
        {
            case QSettings::AccessError:
                QMessageBox::critical( pOdbcTest, "OdbcTest", QString( tr("AccessError when sync() settings to %1") ).arg( pOdbcTest->pSettings->fileName() ) );
                break;
            case QSettings::FormatError:
                QMessageBox::critical( pOdbcTest, "OdbcTest", QString( tr("FormatError when sync() settings to %1") ).arg( pOdbcTest->pSettings->fileName() ) );
                break;
            case QSettings::NoError:
            default:
                break;
        }
    }

    delete close;
    delete add;
    delete remove;
    delete nw;
    delete del;
    delete group;
    delete l_group;
    delete l_auto;
    delete l_sauto;
    delete auto_list;
    delete sauto_list;
}

void DlgToolsManageTestGroup::Ok()
{
}

//
// for a given test, look at each entry in the auto test section, see if it 
// is in the group section, if so it goes in the selected, else the installed list
//

void DlgToolsManageTestGroup::update_test_lists( void )
{
    QString current_text        = group->currentText();
    int     nSectionAutoTests   = gOdbcTools->ini.indexSection( "Auto Tests" );
    int     nSectionGroup       = gOdbcTools->ini.indexSection( current_text );

    auto_list->clear();
    sauto_list->clear();

    if ( nSectionAutoTests < 0 )
        return;

    // for each "Auto Tests"...
    for ( int nEntry = 0; nEntry < gOdbcTools->ini.vectorSectionEntries[nSectionAutoTests].size(); nEntry++ )
    {
        QString stringTest = gOdbcTools->ini.vectorSectionEntries[nSectionAutoTests][nEntry].at( 0 );
        if ( gOdbcTools->ini.indexEntry( nSectionGroup, stringTest ) >= 0 )
            sauto_list->addItem( stringTest );
        else
            auto_list->addItem( stringTest );
    }
}

void DlgToolsManageTestGroup::Activated( const QString & )
{
    update_test_lists();
}

void DlgToolsManageTestGroup::Activated( int val )
{
    if ( group->count() > 0 )
        Activated( group->itemText( val ) );
}

void DlgToolsManageTestGroup::Add()
{
    QListWidgetItem *pListWidgetItem = auto_list->currentItem();
    if ( !pListWidgetItem )
        return;

    gOdbcTools->ini.appendEntry( group->currentText(), pListWidgetItem->text(), "Installed" );
    update_test_lists();
}

void DlgToolsManageTestGroup::Remove()
{
    QListWidgetItem *pListWidgetItem = sauto_list->currentItem();
    if ( !pListWidgetItem )
        return;

    gOdbcTools->ini.removeEntry( group->currentText(), pListWidgetItem->text() );
    update_test_lists();
}

void DlgToolsManageTestGroup::New()
{
    DlgToolsNewGroup *dlg = new DlgToolsNewGroup( this->odbctest, "New Test Group", this );

    dlg->exec();

    delete dlg;
}

void DlgToolsManageTestGroup::Delete()
{
    if ( group->count() == 0 )
        return;

    if ( QMessageBox::information( this, "OdbcTest",
                                   QString( "Delete the test group %1?" ).arg( group->currentText() ),
                                   "&Delete", "&Cancel", 0,
                                   0, 1 ) != 0 )
    {
        return;
    }

    // remove from GROUPS section...
    gOdbcTools->ini.removeEntry( "GROUPS", group->currentText() );

    // remove its section...
    gOdbcTools->ini.removeSection( group->currentText() );

    // reload list...
    group->clear();

    s = find_section( "GROUPS" );

    if ( s )
    {
        prop *p;

        for ( p = s->first(); 
            p != 0; 
            p = s->next())
        {
            group->addItem( p->name() );
        }
    }
    group->setCurrentIndex( 0 );
    Activated( 0 );
}


