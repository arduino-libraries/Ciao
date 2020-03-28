# Arduino Ciao 
Ciao Library is a lightweight library that can be used inside sketches for MCU to send and receive data, via serial communication, in a simple and intuitive way.

## Ciao library

**Arduino Ciao** is an easy-to-use and powerful technology that enables Arduino sketches to communicate intuitively with the "outside world". It aims to simplify interaction between a microcontroller and Linino OS, allowing a variety of connections with most common protocols, social networks, third-party services and applications.

**Arduino Ciao** - (from now-on simply "Ciao") has been designed and developed to be modular and easily configurable. Its goal is to support several Connectors capable of interacting with system resources (filesystem, console, etc...) and to communicate with the most common and useful protocols (MQTT, XMPP, HTTP, SMTP, etc..) and applications (Jabber, Twitter, Facebook, etc.).

Ciao is made of two main parts:

* Ciao Library: developed in C
* Ciao Core: developed in Python

## Ciao Core

To communicate with the "outside world" the Ciao Library interacts with Ciao Core: the key component of the Ciao technology on the MPU (microprocessor) side. Ciao Core runs over Linino OS, it is developed in python and it has been designed to enable communication with "outside world" via several modules called Connectors. Such connectors communicate with Ciao Core using JSON strings sent over a TCP socket.

Ciao Core, thanks to this smart and effective design, is able to:

* interact with as many connectors as you can possibly imagine;
* support connectors written in any programming language available on Linino OS.
  
For more details about the **Ciao Library** visit us at https://www.arduino.cc/en/Reference/Ciao
