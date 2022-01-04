# LambdaLogger
Arduino based tool for vehicles with OEM wide band O2 sensors. Written by TsuYoshi Perogi (hasherbasher@protonmail.com)

Uses OBD-2 port on wide band equipped vehicles(most honda/audi/VW, all vehicles with 12v 6-wire Oxygen sensors)

Logs Lambda readings and AFR values(Directly from OBD-2 Service Mode $01 PID 24) against RPM's(Directly from OBD-2 Service Mode $01 PID 0C) for 60 seconds, file is logged as datalog.txt file on the SDcard, and this data can be viewed easily with any spreadhseet program . Great for fine tuning on the dyno. file should be removed every logging run as datalog.txt file gets overwritten every log cycle. 

Fully complies with the latest OBD-II standard, SAE J1979. 

Easily adaptable for LCD screens. Can easily be change to log any 2 items available in the OBD-2 systems service mode 01 list(https://en.wikipedia.org/wiki/OBD-II_PIDs#) or could be used to read and clear DTC codes. 

