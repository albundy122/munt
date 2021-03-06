#ifndef MASTER_H
#define MASTER_H

#include <QObject>

#include "SynthRoute.h"

class AudioDriver;
class MidiDriver;
class MidiSession;
class QSystemTrayIcon;
class MidiPropertiesDialog;

class Master : public QObject {
	Q_OBJECT
private:
	QList<SynthRoute *> synthRoutes;
	QList<AudioDriver *> audioDrivers;
	QList<AudioDevice *> audioDevices;
	MidiDriver *midiDriver;
	SynthRoute *pinnedSynthRoute;

	QSettings *settings;
	QString synthProfileName;
	QSystemTrayIcon *trayIcon;
	QString defaultAudioDriverId;
	QString defaultAudioDeviceName;
	qint64 lastAudioDeviceScan;

	void init();
	~Master();

	void initAudioDrivers();
	void initMidiDrivers();
	const AudioDevice *findAudioDevice(QString driverId, QString name) const;
	const QString getROMPathName(const QDir &romDir, QString romFileName) const;
	void makeROMImages(SynthProfile &synthProfile);
	SynthRoute *startSynthRoute();

public:
	static Master *getInstance();
	static void freeROMImages(const MT32Emu::ROMImage* &controlROMImage, const MT32Emu::ROMImage* &pcmROMImage);

	// May only be called from the application thread
	const QList<AudioDevice *> getAudioDevices();
	void setDefaultAudioDevice(QString driverId, QString name);
	void setTrayIcon(QSystemTrayIcon *trayIcon);
	QString getDefaultSynthProfileName();
	bool setDefaultSynthProfileName(QString name);
	const QStringList enumSynthProfiles() const;
	void loadSynthProfile(SynthProfile &synthProfile, QString name);
	void storeSynthProfile(const SynthProfile &synthProfile, QString name) const;
	QSystemTrayIcon *getTrayIcon() const;
	QSettings *getSettings() const;
	bool isPinned(const SynthRoute *synthRoute) const;
	void setPinned(SynthRoute *synthRoute);
	void startPinnedSynthRoute();
	void startMidiProcessing();
	void processCommandLine(QStringList args);
	bool canCreateMidiPort();
	bool canDeleteMidiPort(MidiSession *midiSession);
	bool canSetMidiPortProperties(MidiSession *midiSession);
	void createMidiPort(MidiPropertiesDialog *mpd, SynthRoute *synthRoute = NULL);
	void deleteMidiPort(MidiSession *midiSession);
	void setMidiPortProperties(MidiPropertiesDialog *mpd, MidiSession *midiSession);

private slots:
	void createMidiSession(MidiSession **returnVal, MidiDriver *midiDriver, QString name);
	void deleteMidiSession(MidiSession *midiSession);
	void showBalloon(const QString &title, const QString &text);

signals:
	void synthRouteAdded(SynthRoute *route, const AudioDevice *audioDevice);
	void synthRouteRemoved(SynthRoute *route);
	void synthRoutePinned();
	void romsNotSet();
	void playMidiFiles(const QStringList &);
	void convertMidiFiles(const QStringList &);
};

#endif
