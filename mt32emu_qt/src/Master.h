#ifndef MASTER_H
#define MASTER_H

#include <QObject>

#include "SynthRoute.h"

class AudioDriver;
class MidiDriver;
class MidiSession;
class QSystemTrayIcon;
class MT32Emu::ROMImage;

class Master : public QObject {
	Q_OBJECT
private:
	static Master *INSTANCE;

	QList<SynthRoute *> synthRoutes;
	QList<AudioDriver *> audioDrivers;
	QList<AudioDevice *> audioDevices;
	MidiDriver *midiDriver;

	QSettings *settings;
	QDir romDir;
	QString controlROMFileName;
	QString pcmROMFileName;
	const MT32Emu::ROMImage *controlROMImage;
	const MT32Emu::ROMImage *pcmROMImage;
	QSystemTrayIcon *trayIcon;
	QString defaultAudioDriverId;
	QString defaultAudioDeviceName;
	qint64 lastAudioDeviceScan;

	Master();
	void initAudioDrivers();
	void initMidiDrivers();
	const AudioDevice *findAudioDevice(QString driverId, QString name) const;

public:
	MidiSession *createMidiSession(MidiDriver *midiDriver, QString name);
	void deleteMidiSession(MidiSession *midiSession);
	// May only be called from the application thread
	const QList<AudioDevice *> getAudioDevices();
	void setDefaultAudioDevice(QString driverId, QString name);
	void setROMDir(QDir romDir);
	void setROMFileNames(QString useControlROMFileName, QString usePCMROMFileName);
	void setTrayIcon(QSystemTrayIcon *trayIcon);
	QDir getROMDir();
	void getROMFileNames(QString &controlROMFileName, QString &pcmROMFileName);
	void getROMImages(const MT32Emu::ROMImage &controlROMImage, const MT32Emu::ROMImage &pcmROMImage);
	QSystemTrayIcon *getTrayIcon();
	QSettings *getSettings();
	void showBalloon(const QString &title, const QString &text);

	static Master *getInstance();

	// These two methods are only intended to be called at application startup/shutdown
	static void init();
	static void deinit();

private slots:
	void reallyCreateMidiSession(MidiSession **returnVal, MidiDriver *midiDriver, QString name);
	void reallyDeleteMidiSession(MidiSession *midiSession);
	void reallyShowBalloon(const QString &title, const QString &text);

signals:
	void synthRouteAdded(SynthRoute *route, const AudioDevice *audioDevice);
	void synthRouteRemoved(SynthRoute *route);
	void audioDeviceAdded(AudioDevice *audioDevice);
	void audioDeviceRemoved(AudioDevice *audioDevice);
};

#endif