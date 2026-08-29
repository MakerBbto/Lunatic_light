# 🌕 Lunar Sculpture

> An open-source interactive lunar sculpture based on a XIAO ESP32-C3,
> 41 addressable LEDs, an encoder and real-time lunar phase data.

---

## Table of Contents

- [01 — Concept](#01--concept)
- [02 — Research](#02--research)
- [03 — System Design](#03--system-design)
- [04 — Electronics](#04--electronics)
- [05 — PCB Design](#05--pcb-design)
- [06 — Fabrication](#06--fabrication)
- [07 — Firmware](#07--firmware)
- [08 — Interaction](#08--interaction)
- [09 — Testing & Troubleshooting](#09--testing--troubleshooting)
- [10 — Final Assembly](#10--final-assembly)
- [11 — Final Result](#11--final-result)
- [12 — Future Development](#12--future-development)
- [13 — Replication](#13--replication)
- [14 — License](#14--license)
- [15 — Credits](#15--credits)

---

# 01 — Concept

## Background

[¿De dónde nace la idea?]

## Motivation

[¿Qué problema, pregunta o interés dio origen al proyecto?]

## Project Goal

[¿Qué se quería conseguir?]

## Initial Concept

[Primeros bocetos, referencias, ideas, renders, etc.]

![Initial concept](images/concept/initial-concept.jpg)

---

# 02 — Research

## Lunar Phases

[Investigación sobre las fases lunares y cómo representarlas físicamente.]

## Visual References

[Referencias visuales y conceptuales.]

## Existing Projects

[Proyectos similares que sirvieron como referencia.]

## Data Sources

[Investigación sobre APIs y fuentes de datos lunares.]

## Design Decisions

[¿Por qué 41 LEDs?]
[¿Por qué un encoder?]
[¿Por qué una representación circular?]

---

# 03 — System Design

## General Architecture

![System architecture](images/diagrams/system-architecture.png)

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
           /     |      \
          /      |       \
     Encoder   Logic    NeoPixels
                         │
                         ▼
                  Lunar Sculpture
