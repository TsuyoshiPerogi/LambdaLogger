# LambdaLogger
Arduino based tool for vehicles with OEM wide band O2 sensors. Written by TsuYoshi Perogi, (hasherbasher@protonmail.com)

Uses OBD-2 port on wide band equipped vehicles, most honda/audi/VW, some others.

Logs Lambda readings and AFR values(Directly from OBD-2 Service Mode $01 PID 24) against RPM's(Directly from OBD-2 Service Mode $01 PID 0C) for 60 seconds, file is logged as datalog.txt file on the SDcard, and this data can be viewed easily with any spreadhseet program . Great for fine tuning on the dyno. file should be removed every logging run as datalog.txt file gets overwritten every log cycle. 

Fully complies with the latest OBD-II standard, SAE J1979. 

Easily adaptable for LCD screens. Can easily be change to log or trigger any 2 PIDs available in the OBD-2 system service mode 01,02, 03, 04, and 08 (list:https://en.wikipedia.org/wiki/OBD-II_PIDs#). 

Easily attaptable to use the LambdaShield and a Bosch wide band o2 to provide external wide band o2 logging for any vehicle.

