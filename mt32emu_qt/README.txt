Munt mt32emu-qt
===============

mt32emu-qt makes use of libmt32emu and Qt to provide for:

1) Multiple simultaneous synths, GUI to configure synths, manage ROMs and connections
2) Funny LCD
3) Easy usage in different operating system environments:
   Windows multimedia, PulseAudio, ALSA, OSS and CoreMIDI supported
4) Play and record Standard MIDI files
5) Perform batch conversion of Standard MIDI files directly to .wav / .raw audio files


Building
========
Cmake is required to building. The minimum set of dependencies is:

1) Cmake - cross platform make utility
   @ http://www.cmake.org/

2) Qt library
   @ http://qt.digia.com/

3) PortAudio - cross-platform audio I/O library (included to the main munt repository)
   @ http://www.portaudio.com/

4) GLib - Gnome library (for building smf2wav console tool only)
   @ http://developer.gnome.org/glib/

Additional dependencies maybe needed (depending on the platform):

1) PulseAudio - sound system for POSIX OSes - provides for accurate audio rendering
   @ http://www.pulseaudio.org/ or http://www.freedesktop.org/wiki/Software/PulseAudio

2) DirectX SDK - for building PortAudio with DirectSound and WDMKS support


License
=======

Copyright (C) 2011, 2012 Jerome Fisher, Sergey V. Mikayev

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


Trademark disclaimer
====================

Roland is a trademark of Roland Corp. All other brand and product names are
trademarks or registered trademarks of their respective holder. Use of
trademarks is for informational purposes only and does not imply endorsement by
or affiliation with the holder.
