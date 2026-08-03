# mouseF1

# Project Overview
Mini cars for mice, used to compare motor/learning task
performance between TBI and non-TBI mice. Part of the Harris Lab's TBI research.

# Hardware
- Chassis: Unknown
- Motor shield: HW-130 (L293D-based, AFMotor-compatible clone of Adafruit Motor Shield V1)
- Microcontroller: Arduino Uno
- Motors: 4x DC motors (Mecanum wheels)

# Status
Actively debugging motor control code (see Issues tab).
Current known bug: turn function doesn't deactivate — see Issue #1, #2.

# Repo Structure
- /firmware — Arduino sketches
- /hardware — wiring photos and diagrams
- /docs — pin maps, debugging log, known issues
