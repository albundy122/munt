/* Copyright (C) 2011 Jerome Fisher, Sergey V. Mikayev
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "MidiDriver.h"

#include <QtGlobal>

MidiDriver::MidiDriver(Master *useMaster): master(useMaster), name("Unknown") {
	connect(this, SIGNAL(midiSessionInitiated(MidiSession **, MidiDriver *, QString)), master, SLOT(createMidiSession(MidiSession **, MidiDriver *, QString)), Qt::BlockingQueuedConnection);
	connect(this, SIGNAL(midiSessionDeleted(MidiSession *)), master, SLOT(deleteMidiSession(MidiSession *)));
	connect(this, SIGNAL(balloonMessageAppeared(const QString &, const QString &)), master, SLOT(showBalloon(const QString &, const QString &)));
}

MidiDriver::~MidiDriver() {
	while (!midiSessions.isEmpty()) {
		emit midiSessionDeleted(midiSessions.takeFirst());
	}
}

QString MidiDriver::getName() const {
	 return name;
}

Master *MidiDriver::getMaster() {
	return master;
}

MidiSession *MidiDriver::createMidiSession(QString sessionName) {
	MidiSession *midiSession = NULL;
	emit midiSessionInitiated(&midiSession, this, sessionName);
	if (midiSession != NULL) {
		midiSessions.append(midiSession);
	}
	return midiSession;
}

void MidiDriver::deleteMidiSession(MidiSession *midiSession) {
	midiSessions.removeOne(midiSession);
	emit midiSessionDeleted(midiSession);
}

void MidiDriver::showBalloon(const QString &title, const QString &text) {
	if (master->getSettings()->value("Master/showConnectionBalloons", "1").toBool()) {
		emit balloonMessageAppeared(title, text);
	}
}

bool MidiDriver::canCreatePort() {
	return false;
}

bool MidiDriver::canDeletePort(MidiSession *) {
	return false;
}

bool MidiDriver::canSetPortProperties(MidiSession *) {
	return false;
}

bool MidiDriver::createPort(MidiPropertiesDialog *, MidiSession *) {
	return false;
}

bool MidiDriver::setPortProperties(MidiPropertiesDialog *, MidiSession *) {
	return false;
}

QString MidiDriver::getNewPortName(MidiPropertiesDialog *) {
	return "";
}
