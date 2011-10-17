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
#ifndef NMGTASKPROGRESSBAR_H
#define NMGTASKPROGRESSBAR_H

#include "nmgtaskwidget.h"
#include <nmgrandomgenerator.h>

#include <QProgressBar>
#include <QMenu>
#include <QMap>
#include <QMouseEvent>

typedef QMap<QString,NMGTaskWidget *> QTaskMap;
typedef QTaskMap::iterator TaskMapIterator;

#define MAXPROGRESS 100

class NMGTaskProgressBar : public QProgressBar
{
		Q_OBJECT
	public:
		NMGTaskProgressBar ( QWidget *parent = 0, const char *name = 0 );
		~NMGTaskProgressBar();
		void mousePressEvent ( QMouseEvent * e );
		QWidget * getParentTasks();
		QString newTaskId();
		void addTask ( NMGTaskWidget * t );
		void removeTask ( NMGTaskWidget * t );

	public slots:
		void newTask ( QString id, QString moduleName );
		void finishedTask ( QString id, QString moduleName, QString data );

	private:
		QMenu * menu;
		QTaskMap taskMap;
		int count;
		NMGRandomGenerator random;
};

#endif
