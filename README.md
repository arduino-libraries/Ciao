## Arduino Ciao (MCU side)
Simple library in C to make MCU communicate with "outside World" through Ciao Core.

### What is Arduino Ciao?

**Arduino Ciao or simply Ciao** is a easy-to-use and powerful technology that enables Arduino sketches to communicate intuitively with the "outside World". It aims to simplify interaction between microcontroller and [Linino OS](https://www.linino.org) allowing a variety of connections with most common protocols, third-party services and social networks.

Arduino Ciao is open-source and distributed under MIT license: feel free to read it, suggest improvements, provide feedbacks and develop new features.

More information about Arduino Ciao project can be found at https://www.arduino.cc/en/Reference/Ciao

### Arduino Ciao (MCU side) - Ciao Library

Arduino Ciao is made of two main parts:
 * The **Ciao Library** - usable inside *sketches*, it's written in C.
 * The [Ciao Core](https://github.com/bcmi-labs/arduino-library-ciao) - a library developed in python that runs on the CPU/MIPS side of the board.(archived source code available [here](https://github.com/arduino-org/Ciao))

**Ciao Library**  allows you to send and receive data outside the microcontroller, through a serial communication, in a simple and intuitive way.
This architecture is currently available on the following products:

 * Arduino Industrial 101
 * Arduino Tian
 * Arduino Yún LininoOS
 * Arduino Yún Mini

Details about **Ciao Library** architecture are available in the [Arduino wiki](https://www.arduino.cc/en/Reference/Ciao)
