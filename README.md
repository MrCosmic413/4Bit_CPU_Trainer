4-Bit Logic Trainer

A hands-on 4-bit trainer for exploring how registers, logic gates, an adder, and multiplexers work together. This repository is intended to stand on its own, separate from the NAND project.

## At a glance

- Four input bits (`IN0`–`IN3`) feed the A and B registers.
- Two select switches choose AND, OR, XOR, or ADD.
- A third register captures the result, displayed on four LEDs.
- A shared clock and reset control the registers.

| SEL1 | SEL0 | Operation |
|:---:|:---:|---|
| 0 | 0 | A AND B |
| 0 | 1 | A OR B |
| 1 | 0 | A XOR B |
| 1 | 1 | A + B (low four bits) |

## Build photos

Add your photos to [`docs/photos`](docs/photos), then replace the example paths below with the actual filenames.

<!-- Example: ![Completed 4-bit trainer](docs/photos/finished-trainer.jpg) -->
<!-- Example: ![Breadboard or PCB close-up](docs/photos/build-closeup.jpg) -->

**Build notes:** Add the board revision, power supply, notable wiring choices, and anything you changed during assembly here.

## KiCad design

Put the KiCad project, schematic, PCB, and any exported PDFs or fabrication files in [`hardware/kicad`](hardware/kicad). Add a screenshot of the schematic or board layout here when ready.

<!-- Example: ![KiCad PCB layout](docs/photos/kicad-pcb.png) -->

**Design status:** KiCad files have not been added yet.

## Simulation

The [`simulation`](simulation) folder contains the Wokwi circuit, Arduino power-source sketch, six custom chip models, and expected test results. The Arduino in this simulation supplies simulated 5 V and ground; it does not compute the logic result.

To set it up in Wokwi:

1. Create a new Arduino Uno project.
2. Add six C custom chips named `hc173`, `hc153`, `hc283`, `hc08`, `hc32`, and `hc86`.
3. Replace each generated `.chip.c` and `.chip.json` file with its matching file from [`simulation`](simulation).
4. Replace `diagram.json` and `sketch.ino` with the files in that folder.
5. Start the simulation.

<!-- Example: ![Simulation running an addition test](docs/simulation/add-test.png) -->

### Controls

The four `IN` buttons are momentary. In Wokwi, Ctrl-click can latch a button while entering a multi-bit value. `LOAD A`, `LOAD B`, and `LOAD OUT` are active low: move the switch right to load, and left for idle. Move `CLK` right and then left for one pulse. Do the same with `RESET` to clear the registers. `SEL0` and `SEL1` set the operation according to the table above.

### Quick check

1. Pulse `RESET`.
2. Enter `0101`; enable `LOAD A`, pulse `CLK`, then disable `LOAD A`.
3. Enter `0011`; enable `LOAD B`, pulse `CLK`, then disable `LOAD B`.
4. Select an operation; enable `LOAD OUT`, pulse `CLK`, then disable `LOAD OUT`.

| Operation | Expected four LED result |
|---|:---:|
| AND | `0001` |
| OR | `0111` |
| XOR | `0110` |
| ADD | `1000` |

See [`EXPECTED_TESTS.txt`](simulation/EXPECTED_TESTS.txt) for the compact test list.

## Hardware used in the simulation

- 3 × CD74HC173E 4-bit registers (A, B, output)
- 1 × 74HC08 AND, 1 × 74HC32 OR, 1 × 74HC86 XOR
- 1 × CD74HC283E 4-bit adder
- 2 × CD74HC153E dual 4-to-1 multiplexers
- Four input buttons, control switches, and four output LEDs

## Project layout

```text
4-bit-trainer/
├── README.md
├── simulation/       Wokwi project files and test expectations
├── hardware/kicad/    KiCad files to add
├── docs/photos/       Build and board photos to add
└── docs/simulation/   Simulation screenshots to add
```

## Notes

This repository documents a trainer project in progress. Verify the hardware design and wiring before applying power to a physical build.
