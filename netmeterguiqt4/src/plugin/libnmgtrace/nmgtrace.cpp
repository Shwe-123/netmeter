/***************************************************************************
 *   Copyright (C) 2005 by Ernest Nieto                                    *
 *   ernest.nieto@gmail.com                                                *
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

#include "nmgtrace.h"

#ifndef DEBUG
#define DEBUG 1
#endif

#include <iostream>
using namespace std;

NMGTrace::NMGTrace()
{
	moduleName = MOD_NAME;
	moduleCapabilities = MOD_CAPABILITIES;
	moduleVersion = MOD_VERSION;
	moduleCoreMatching = CORE_MATCHING;
	moduleGUIName = GUI_NAME;
	m_tracewidget = 0;
}

NMGTrace::~NMGTrace()
{
}

void NMGTrace::initModuleGUI()
{
	
}

void NMGTrace::removeModuleGUI()
{
	
}

QWidget *NMGTrace::getWidget()
{
	if(!m_tracewidget) m_tracewidget = new NMGTraceWidget(this);
	return m_tracewidget;
}

void NMGTrace::dataReceived(QString data)
{
	if(!m_tracewidget) return;
	m_tracewidget->resultReceived(data);
}

void NMGTrace::statusReceived(QString data)
{
	if(!m_tracewidget) return;
	m_tracewidget->statusReceived(data);
}

void NMGTrace::errorReceived(int errorType, QString errorMessage)
{
	if(!m_tracewidget) return;
	m_tracewidget->errorRecieved(errorType, errorMessage);	
}

