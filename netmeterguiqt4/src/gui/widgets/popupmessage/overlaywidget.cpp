/***************************************************************************
 *   Copyright (C) 2007 by Roberto Barreda <rbarreda@ac.upc.edu>           *
 *   Copyright (C) 2005 by Ernest Nieto <ernest.nieto@gmail.com>           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "overlaywidget.h"

#include <QPoint>

OverlayWidget::OverlayWidget( QWidget *parent, QWidget *anchor, const char* name )
		: QFrame( parent ), m_anchor( anchor ), m_parent( parent )
{
	setObjectName( name );
	parent->installEventFilter( this );
	//hide();
}

void OverlayWidget::reposition()
{
	setMaximumSize( parentWidget()->size() );
	adjustSize();

	// p is in the alignWidget's coordinates
	QPoint p;

	p.setX( m_anchor->width() - width() );
	p.setY( -height() );

	// Position in the toplevelwidget's coordinates
	QPoint pTopLevel = m_anchor->mapTo( topLevelWidget(), p );

	// Position in the widget's parentWidget coordinates
	QPoint pParent = parentWidget()->mapFrom( topLevelWidget(), pTopLevel );
	// keep it on the screen
	if ( pParent.x() < 0 )
		pParent.rx() = 0;

	// Move 'this' to that position.
	move( pParent );
}

bool OverlayWidget::eventFilter( QObject* o, QEvent* e )
{
	if ( e->type() == QEvent::Move || e->type() == QEvent::Resize )
		reposition();
	return QFrame::eventFilter( o, e );
}

void OverlayWidget::resizeEvent( QResizeEvent* ev )
{
	reposition();
	QFrame::resizeEvent( ev );
}

bool OverlayWidget::event( QEvent *e )
{
	if ( e->type() == QEvent::ChildAdded )
		adjustSize();
	return QFrame::event( e );
}
