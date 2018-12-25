# Vessel Monitor
Work in progress...
Project to create boat pc to my sailing boat. Initial idea is to have following components:
 - Vessel monitor running in Rasperry PI, having 7 inc youch screen.
 - [Battery monitor](https://github.com/abrox/bms) running in ESP8266 using wifi & mqtt to communicate with monitor.
 

## Requires
- qt
- [qwt](http://qwt.sourceforge.net/)
- [Simple Mqtt](https://github.com/abrox/simplemqtt) 

After qwt installation libqwt did not found, so I add link /usr/lib
>sudo ln -s /usr/local/qwt-6.1.3/lib/libqwt.so.6 /usr/lib/libqwt.so.6
