# 🌕 Lunar Sculpture

> Open-source interactive lunar sculpture based on a XIAO ESP32-C3, 41 addressable LEDs, a rotary encoder and real-time lunar phase data.

---

## Table of Contents

* [01 — Concept](#01--concept)
* [02 — Research](#02--research)
* [03 — System Design](#03--system-design)
* [04 — Electronics](#04--electronics)
* [05 — Electronics Design and manufacturing](#05--Electronics-design-and-manufacturing)
* [06 — Fabrication](#06--fabrication)
* [07 — Firmware](#07--firmware)
* [08 — Interaction](#08--interaction)
* [09 — Final Result](#09--final-result)
* [10 — Future Development](#10--future-development)
* [11 — Replication](#11--replication)
* [12 — License](#12--license)
* [13 — References](#13--references)

---

# 01 — Concept

## Background

The first iteration of this project was built for the [ArteFab exhibition](https://textile-academy.org/artefab-2024/) in Puebla, México, during the [Fab24 conference](https://fab24.fabevent.org/), where some very talented people showcased their work on digital fabrication + artistic expression in one of the most amazing venues in the city of Puebla: The former-psychiatric hospital of San Roque, in the very historical city center.

![Initial Sketch](/assets/images/ArteFab.jpg)

## Initial Concept

The working principle was simple: On the press of a button, the sculpture would show the current phase of the moon, which at the moment was enough. But after having it for some time i realized it was time for a upgrade/update. What if the interface included more options? What kind of device/app would be propper for this project? What kind of "options" should be included in the program? How is the program written? What kind of architecture would be needed for this sculpture.

![Initial Sketch](/assets/images/Sketch.jpeg)

# 02 — Research
The first part of the project was designing the "moon", and the question was if it was going to be either 3D-printed or CNC Routed. The reason why it was done with the CNC router was the size, as 3D printing several pieces and glueing, sanding, finishing, etc. would be a long and tedious. The final size of the moon is 1m in diameter, plus an offset for the posts and the encoder.

For the first iteration of this project, it was only a matter of connecting with an online API, in this case it was [VisualCrossing](https://www.visualcrossing.com/) weather app. So the devices requests information and the API sends back a string of data which includes the percentage of illumination on the moon, and if it is waxing or waning.
Having this information it was time to figure out the best way to select which LEDs should be turned on and off, to show the appropiate phase of the moon.

## Lunar Phases

Some time ago I tried to photograph every part of the lunar cycle with the telescope and animate the result (which is below). So this project gave me a lot of clarity about how does the moon phases behave and how the LEDs should be controlled.

![Moon animation](/assets/images/Luna.gif)

# 03 — System Design

## General Architecture

So the system works something like this through magic and a bit of programming.

```text
                    INTERNET
                        │
                        ▼
                   Lunar API
                        │
                      WiFi
                        │
                        ▼
                 XIAO ESP32-C3
                  /     |     \
                 /      |      \
           Encoder ---Logic--NeoPixels
                              │
                              ▼
                       Lunar Sculpture
```

## System Components

## Data Flow

Basically (logically?) the workflow goes like this:

```text
XIAO ESP32-C3
    ↓
WIFI
    ↓
Lunar API
    ↓
XIAO ESP32-C3
    ↓
Interpretation of lunar phase
    ↓
LED positioning
    ↓
Light output
```

I have included the code for you to check it out and modify, at the end of the document.

---

# 04 — Electronics

## Electronic Components

| Component       | Quantity | Function                   |
| --------------- | -------: | -------------------------- |
| XIAO ESP32-C3   |        1 | Main controller            |
| Addressable LED |       41 | Lunar illumination         |
| Rotary encoder  |        1 | User interaction           |
| Custom PCB      |        1 | Electrical interconnection |
| Power supply    |        1 | System power               |
| Other           |        — | —                          |


## Pinout

| XIAO Pin | Function       |
| -------- | -------------- |
| GPIO2    | Encoder CLK    |
| GPIO3    | Encoder DT     |
| GPIO4    | Encoder SW     |
| GPIO6    | NeoPixel data  |
| 3V3      | Encoder power  |
| GND      | Common ground  |
| 5V       | NeoPixel power |

## 05 - Electronics Design and manufacturing

The electronic schematic is quite straightforward, it was designed in [KiCad](https://www.kicad.org/), so the workflow is as smooth as possible. I downloaded the [FabLabs KiCad Library](https://github.com/SainsburyWellcomeCentre/fablabs-kicad-library) that has all the footprints for components like the microcontroller, pins, switches, etc.

![Wiring diagram](images/Diagrama.jpg)

Using KiCad the PCB design was very easy, as it almosts designs it on its own, based on the schematic, and only a few corrections were done for the paths. But that is where the problems began.

## Prototype 01

This first prototype was designed to have all the components soldered on the surface of the PCB (surface mounted components i guess it's called?). It was cut with the [Xtool F1 Ultra](https://www.xtool.com/products/xtool-f1-ultra-20w-fiber-diode-dual-laser-engraver) laser engraver on a phenolic plate, which was at the beginning quite satisfying and succesful, but the problem came with soldering the components and my minimum patience.

![Xtool prototype 1](images/KiCad_01.jpg)
![PCB prototype 01](images/PCB_01.jpg)

So a new solution was needed. Instead of surface mounting the components, they should go through holes and soldered underneath. The PCB was redesigned on this premise, maintaining the same schematic and distribution. One important thing to have in consideration is to mirror the PCB, as it will be "upside down", either from KiCad or at the manufacturing software.

![Xtool prototype 1](images/KiCad_02.jpg)
![PCB prototype 01](images/PCB_02.jpg)

And it also didn't work. Apparently the paths weren't completelly separated and there was a small resistance between them, so the encoder was malfunctioning and the LED strip died. So the PCB was cut using different parameters, the LED strip replaced and voilá! it was working properly.

![Xtool prototype 3](images/Xtool_final.jpg)
![PCB prototype 03](images/PCB_final.jpg)

# 06 — Fabrication

## Requirements
These are the basic requirements for replicating this project.

### Tools
Most of this tools can be found at your local [FabLab](https://fablabs.io/) or Makerspace.

* CNC Router
* 3D Printer
* Minimill/laser engraver for the PCB.
* Soldering station
* PC for programming the microcontroller.

### Materials

* XIAO ESP32-C3.
* Rotary encoder KY-040.
* Addressable neopixel strip (the distance between the neopixels depends on the overall diameter of the lamp you are creating).
* Soldering consumables (flux, lead-free solder, etc).
* Female dupont wires for connecting to the PCB.
* Male pin headers for the connections to the neopixels and encoder.
* Female pin headers for the connection to the microcontroller.
* Paint for the Moon part
* 12mm MDF (around 120cm x 120cm is enough)
* Wood screws (around 1 in in lenght)

### Skills

* 3D modelling
* CNC Machining skills, for both configuration and operation.
* 3D Printing skills, for both configuration and operation.
* Laser engraving or minimill skills for the PCB, both configutarion and operation.
* Steady hand for soldering small components
* PATIENCE

## Download

All files required to reproduce the project can be found in this repository.

### Hardware

→ [Hardware files](hardware/)

### Firmware

→ [Firmware](firmware/)

## Build Process

### 01 — Fabricate

* Starting with the Moon photo + the outside vector, it needs to be carved and cut with the CNC Router.
* Sand and paint the sculpture, preferably with sealant as a base.
* The PCB is then milled/laser engraved (Carefully) and tested for connection errors.
* 3D Print the posts for the neopixel strip.
* 3D print the case for the PCB.

### 02 — Assemble

* Solder the PCB components and test conductivity with the neopixel and encoder before installing it.
* Review the firmware through the [Arduino IDE](https://www.arduino.cc/en/software),, and add your own Wifi address and password where it is indicated. Make sure the the ESP32 chip family package is installed previously. Check out [this documentation](https://fabacademy.org/2023/labs/puebla/students/alberto-blanco/W04.html) for more information on the instalation.
* Install the PCB in the case and attach to the back of the lamp.
* Paste the neopixel strip into the posts, following a clock-wise path, route the cable through the hole and attach female dupont terminals for easy connection.
* Connect the cables as the diagram shows. The encoder can be connected with female-female dupont cables.
Diagrama

### 03 - Operation
* Connect the device to a power source and hope for the best (just kidding). The whole lamp should turn on until it connects to the wifi and requests the phase data, then it will transform to the current phase, if you press the encoder's button, you can select the phase to be shown, the next click allows you to adjust the brightness, and the next click let's you change the colour, a gradient between white, orange as the moonrise, and red as a blood moon.

### 04 - Adaptations

On the firmware file, the parts that can be customized are the following:

* Wifi address and password - In order for the device to work properly, it must be connected to the internet, with a valid wifi address. Make sure to change it or it won't work.
* The steps for each of the settings can be adjusted for your own commodity, the default is 30 for the phase selection, 10 for the brightness, and 15 for the colour changing.
* The colours in which it changes can be customized easily, the format used is RGB.
* You can find all this parameters on the firmware, under a title.

## The structure

The sculpture is based on a real photo (i took) from the moon. I was searching online for different solutions on turning this photo into a 3D model, I even thought about modelling it with software like [Blender](https://www.blender.org/) or similars, but the real solution came from the [Ultimaker Cura](https://ultimaker.com/software/ultimaker-cura/) software, an (almost) universal slicer used for 3D printing. The photo is imported and the colours are matched to different heights until i got something i liked.

![Cura parameters](images/Cura_01.jpg)
![3D model](images/Cura_02.jpg)

The sculpture was designed on [Autodesk Fusion 360](https://www.autodesk.com/ca-en/products/fusion-360), both the central piece and the posts for the LED strip. Both models are included below.

![Base outline](images/Fusion_01.jpg)
![Post](images/Fusion_02.jpg)

The posts are 3D printed on PLA, but you can choose the material you prefer, and 41 of them are needed. The base is CNC Routed on MDF, the 3D model of the moon is imported on [Vcarve](https://www.vectric.com/products/vcarve/), and configured, then the outline vector is also added for it to be cut. 

![Cura posts](images/Cura_03.jpg)
![CNC Router](images/CNC_Router.jpg)

I used a water-based sealant for better finishing, and then a coat of white paint. The posts are inserted in the holes and secured with wood screws. The flat part is where the LED strip will adhere, you could use the integrated glue or use more if you prefer.

The LED numbering follows a clockwise direction.

* LED 1 → 0°
* LED 10 → 270°
* LED 20 → 180°
* LED 41 → approximately 355°

---

# 07 — Firmware

## Firmware Development

The firmware was vibecoded with the help of [ChatGPT](https://chatgpt.com/) with a long and thorough conversation that started with the basic functionality needed, a ton of debugging for the encoder and tests of brightness, colours and responses, which led to the final output. If you'd be interested on this different tests and diagnosis tools, contact me so I can share them.

## Libraries

The libraries used on this project are the following:

```text
WiFi
WiFiClientSecure
HTTPClient
ArduinoJson
FastLED
```

Make sure you have the most updated versions of the Arduino IDE, the ESP32 cards, and the libraries for the proper functioning.

---

# 08 — Interaction

## User Interface

The sculpture contains four interaction modes.

```text
MODE 0
Current Moon Phase
       │
       │ Button
       ▼
MODE 1
Phase Selection
30 steps
       │
       │ Button
       ▼
MODE 2
Brightness
10 steps
       │
       │ Button
       ▼
MODE 3
Eclipse
15 steps
       │
       │ Button
       ▼
MODE 0
Current Moon Phase
```

## Mode 0 — Current Moon Phase

This state shows the current moon phase based on the API response.

## Mode 1 — Phase Selection

The encoder allows the user to manually select a lunar phase using 30 steps.

```text
🌑 ─────────────── 🌕 ─────────────── 🌑
0                  15                  30
```

## Mode 2 — Brightness

The brightness can be adjusted using 10 steps.

```text
10% ───────────────────────────── 100%
```

## Mode 3 — Eclipse

The color can be adjusted using 15 steps.

```text
WHITE ───────── ORANGE ───────── RED
  1                ~8              15
```

---

# 09 — Final Result

[![Youtube video](/assets/images/Cover.jpeg)](http://www.youtube.com/watch?v=Jj1wgF8snc0?si=hzCaXsZvxEteh3Uh "Lunatic Light")

# 10 — Future Development

## Possible Improvements

* Improve the fixture for the neopixel stripe so it looks better, more elegant.
* Adding real time eclipse display.
* A phone app to control the different phases, colours and brightness.
* Optimization for using with smart home controllers like Alexas, Google Nest, or with open projects like [Home Assistant](https://www.home-assistant.io/)
* Adding weather forecast for the day.

# 11 — Replication
I encourage you, the reader, to replicate this project and share it, give the proper credits, though. Knowledge only matters when it is shared. I have included all the files needed for its completion, for free.

> Free as in speech, free as in beer.

## Reproducibility Notes

MAKE SURE TO GIVE CREDITS IF YOU REPRODUCE THIS PIECE!

---

# 12 — License

The firmware is licensed under the GNU General Public License v3.0 (GPL-3.0).

See the [LICENSE](LICENSE) file.

Lunatic Light © 2026 by Alberto Blanco is licensed under [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International](https://creativecommons.org/licenses/by-nc-sa/4.0/)

# 13 — References

## APIs

* [wttr.in](https://wttr.in/)
