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
#include "nmgmodtabwidgetmanager.h"
#include "nmgmodule.h"
#include <nmgapplicationinformation.h>
#include <nmgmaintabwidget.h>
#include <nmgmainwindow.h>

#include <iostream>
using namespace std;


/**
 * Constructor of the class
 * @return
 */
NMGModTabWidgetManager::NMGModTabWidgetManager( NMGModule * mod, QObject *parent, const char *name )
		: QObject( parent )
{
	setObjectName( name );
	module = mod;
	animationEnabled = false;
	connect( &timer, SIGNAL( timeout() ), this, SLOT( changeImage() ) );
}

/**
 * Destroyer of the class
 * @return
 */
NMGModTabWidgetManager::~NMGModTabWidgetManager()
{}

/**
 * Sets the image of the tab of the module
 * @param image Name of the file with the image at the image directory
 */
void NMGModTabWidgetManager::setTabImage( const QString & image )
{
	NMGMainTabWidget * tabWidget = NMGApplicationInformation::getApplicationInformation()->getMainWindow()->getTabWidget();
	if ( tabWidget )
	{
		int i = tabWidget->getIndexFromWidgetInsideScrollView( module->getWidget() );
		if ( i >= 0 ) tabWidget->setImage( i, image );
		else cerr << "[panic] There is no tab for a existing module!" << endl;
	}
	else cerr << "[panic] There is no tab widget in the main window!" << endl;
}

/**
 * Sets the images of the tab as an animation
 * @param image1 Image 1 of the animation
 * @param image2 Image 2 of the animation
 * @param delayMseg Delay between images
 */
void NMGModTabWidgetManager::setTabAnimation( const QString & image1, const QString& image2, int delayMseg )
{
	animationEnabled = true; //TODO Is really necessary this instruction??
	animationImage1 = image1;
	animationImage2 = image2;
	animationDelayMseg = delayMseg;
	if ( animationEnabled ) timer.start( delayMseg );
	else
	{
		animationEnabled = true;
		timer.start( delayMseg );
	}
	animationStep = 0;
	setTabImage( image1 );
}

/**
 * Stops the tab animation
 */
void NMGModTabWidgetManager::stopTabAnimation()
{
	animationEnabled = false;
	timer.stop();
}

/**
 * Changes the image of the animation
 */
void NMGModTabWidgetManager::changeImage()
{
	animationStep = ( animationStep + 1 ) % 2;
	setTabImage( animationStep == 0 ? animationImage1 : animationImage2 );
}

/**
 * Removes the image of the tab of the module
 * If the module has an icon image associated (with the macro NMMODULE_MODULEICON), this image wiil be shown at the tab
 */
void NMGModTabWidgetManager::removeTabImage()
{
	NMGMainTabWidget * tabWidget = NMGApplicationInformation::getApplicationInformation()->getMainWindow()->getTabWidget();
	if ( tabWidget )
	{
		int i = tabWidget->getIndexFromWidgetInsideScrollView( module->getWidget() );
		if ( i >= 0 )
		{
			NMGModuleParent * parent = NMGModuleManager::self()->getModuleParent( module );
			if ( parent and !(QString( parent->getModuleIcon().c_str() ).isEmpty()) ) 
				tabWidget->setImage( i, parent->getModuleIcon().c_str() );
			else tabWidget->removeImage( i );
		}
		else cerr << "[panic] There is no tab for an existing module!" << endl;
	}
	else cerr << "[panic] There is no tab widget in the main window!" << endl;
}

#include "nmgmodtabwidgetmanager.moc"
