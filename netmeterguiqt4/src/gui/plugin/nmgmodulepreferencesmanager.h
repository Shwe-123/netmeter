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
#ifndef NMGMODULEPREFERENCESMANAGER_H
#define NMGMODULEPREFERENCESMANAGER_H

#include <QString>

class NMGModule;

class NMGModulePreferencesManager
{
	public:
		NMGModulePreferencesManager ( NMGModule * mod );
		~NMGModulePreferencesManager();
		bool existsValue ( QString id );
		void removeValue ( QString id );
		void addValue ( QString id, QString val );
		QString getValue ( QString id );

	private:
		QString transformId ( QString id );

	private:
		NMGModule * module;
};

#endif
