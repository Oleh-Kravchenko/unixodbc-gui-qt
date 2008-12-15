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

dManageTestGroup::dManageTestGroup( OdbcTest *parent, QString name )
: QDialog( parent )
{
    setWindowTitle( name );

    odbctest = parent;

    init_ini_list( parent );

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
    group -> setGeometry( 100, 15, 180, 20 );

    l_group = new QLabel( "Test Group:", this );
    l_group -> setGeometry( 10, 15, 60, 20 );

    l_auto = new QLabel( "Installed Auto Tests:", this );
    l_auto -> setGeometry( 10, 60, 160, 20 );

    l_sauto = new QLabel( "Selected Auto Tests:", this );
    l_sauto -> setGeometry( 370, 60, 160, 20 );

    auto_list = new QListWidget( this );
    auto_list -> setGeometry( 10, 80, 250, 160 );

    sauto_list = new QListWidget( this );
    sauto_list -> setGeometry( 370, 80, 250, 160 );

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

        for ( p = s -> first(); 
            p != 0; 
            p = s -> next())
        {
            group -> addItem( p -> name() );
        }
    }

    Activated( 0 );
    connect( group, SIGNAL(activated(const QString &)), 
             this, SLOT( Activated(const QString &)));
}

dManageTestGroup::~dManageTestGroup()
{
    replace_ini_list( odbctest );
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

void dManageTestGroup::Ok()
{
}

//
// for a given test, look at each entry in the auto test section, see if it 
// is in the group section, if so it goes in the selected, else the installed list
//

void dManageTestGroup::update_test_lists( void )
{
    section *s = find_section( "Auto Tests" );
    QString current_text = group->currentText();
    section *s_group = find_section( current_text );

    auto_list->clear();
    sauto_list->clear();

    if ( s )
    {
        prop *p;

        for ( p = s -> first(); 
            p != 0; 
            p = s -> next())
        {
            prop *atprop;
            int found = 0;

            for ( atprop = s_group -> first();
                atprop != 0;
                atprop = s_group -> next())
            {
                if ( strcmp( atprop -> name(), p -> name()) == 0 )
                {
                    found = 1;
                    break;
                }
            }
            if ( found )
            {
                sauto_list->insertItem( p->name());
            }
            else
            {
                auto_list->insertItem( p->name());
            }
        }
    }
}

void dManageTestGroup::Activated( const QString &str )
{
    update_test_lists();
}

void dManageTestGroup::Activated( int val )
{
    if ( group -> count() > 0 )
        Activated( group -> text( val ));
}

void dManageTestGroup::Add()
{
    int index = auto_list -> currentItem();
    QString current_text = group->currentText();

    if ( index >= 0 )
    {
        QListBoxItem *lbi = auto_list -> item( index );

        section *s = find_section( current_text );
        prop *p = new prop( lbi -> text(), "Installed" );
        s -> append( p );

        update_test_lists();
    }
}

void dManageTestGroup::Remove()
{
    int index = sauto_list -> currentItem();
    QString current_group = group->currentText();

    if ( index >= 0 )
    {
        QListBoxItem *lbi = sauto_list -> item( index );

        section *s = find_section( current_group );
        prop *p;

        //
        // find element
        //
        for ( p = s->first(); p != 0; p = s -> next())
        {
            if ( strcmp( p -> name(), lbi -> text()) == 0 )
            {
                s -> remove( p );
                break;
            }
        }
        update_test_lists();
    }
}

void dManageTestGroup::New()
{
    dNewGroup *dlg = new dNewGroup( this -> odbctest, "New Test Group", this );

    dlg -> exec();

    delete dlg;
}

void dManageTestGroup::Delete()
{
    if ( group -> count() == 0 )
    {
        return;
    }

    QString grp = group -> currentText();

    char msg [128];

    sprintf( msg, "Delete the test group %s ?", grp.toAscii().constData());

    if ( QMessageBox::information( this, "OdbcTest",
                                   msg,
                                   "&Delete", "&Cancel", 0,
                                   0, 1 ) == 0 )
    {
        //
        // Remove it from the GROUPS section
        //
        section *s = find_section( "GROUPS" );

        if ( s )
        {
            prop *p;

            for ( p = s -> first(); 
                p != 0; 
                p = s -> next())
            {
                if ( strcmp( p -> name(), grp.toAscii().constData()) == 0 )
                {
                    s -> remove( p );
                    break;
                }
            }
        }

        //
        // remove the section
        //
        s = find_section( grp.toAscii().constData());
        if ( s )
        {
            ini_list.removeOne( s );
            remove_section( odbctest, s );
        }

        //
        // fill up combo box
        //

        group -> clear();

        s = find_section( "GROUPS" );

        if ( s )
        {
            prop *p;

            for ( p = s -> first(); 
                p != 0; 
                p = s -> next())
            {
                group -> addItem( p -> name() );
            }
        }
        group -> setCurrentIndex( 0 );
        Activated( 0 );
    }
}


