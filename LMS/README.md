# LMS / Meshmerize Tasks

This repository contains my work for the nine LMS / Meshmerize fresher selection tasks.

## Folder structure

- `BOM/` — BOM table, power-block diagram and power budget.
- `docs/task1/` — Basic coding functions and their input/output examples.
- `docs/task2_datasheet_literacy/` — Datasheet analysis.
- `docs/task3_pid_control/` — PID control explanation.
- `docs/task6_electronics_hardware/` — Wiring diagram reference and troubleshooting analysis.
- `docs/task7_wireless_diagnostics/` — Wireless protocol notes and system architecture.
- `docs/task8_maze_solving/` — Maze-solving comparison, exploratory/replay notes and pseudocode.
- `src/task9_lms_implementation/` — ESP32 Arduino line-following code and PID tuning notes.
- `assets/diagrams/` — Wiring and maze diagrams.
- `assets/chassis/` — Chassis-related note.

## Running the code

### Task 1

The two C++ files are in `docs/task1/`:
- `task1_1.cpp`
- `task1_2.cpp`

Compile and run each file separately with a C++ compiler.

### Task 9

Open `src/task9_lms_implementation/task9_lmscode.ino` in the Arduino IDE and select the ESP32 board before compiling. The code is written for the ESP32 Arduino framework and uses the sensor and motor pin assignments defined in the task brief.

The hardware has not been physically tested as part of this submission. The PID tuning notes describe the adjustments that would be made during testing.

## Notes

- The power budget and BOM files are in `BOM/`.
- The diagrams are stored in `assets/diagrams/`.
- Check the pin assignments and power connections against the supplied hardware before running the program on a physical robot.
