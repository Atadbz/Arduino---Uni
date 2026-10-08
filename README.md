# Arduino RFID and Keypad Door Lock

An Arduino sketch for an electronic lock that opens with an RFID card, a keypad code, or a code sent over a serial (Bluetooth) link.

<sub>HARDWARE PROJECT · 2023 · ARDUINO C++</sub>

## Overview

The main sketch combines an MFRC522 RFID reader, a 4x4 keypad, and a 16x2 I2C LCD into a lock controller. A card whose UID is stored in EEPROM, or the access code typed on the keypad, triggers an unlock; a separate pairing code saves the next scanned card's UID to EEPROM. The access code sent over the serial port (labelled BT, for Bluetooth, in the code comments) and followed by one more character, such as a newline, also unlocks, and each unlock drives pin 6 low for five seconds before the LCD returns to `BLOCKED`. A small, unrelated LED blink sketch is kept separately under `experiments/`.

## Contents

| Path | Description |
| --- | --- |
| [`README.md`](README.md) | This overview. |
| [`src/`](src) | The lock sketch, `rfid_keypad_door_lock/rfid_keypad_door_lock.ino`: RFID card check and pairing stored in EEPROM, masked keypad entry, serial unlock, and LCD status messages. |
| [`experiments/`](experiments) | `led_blink/led_blink.ino`, a short sketch meant to blink LEDs on pins 2 and 8 with a delay that shrinks each cycle, then set pin 12 high. |

## Usage

The lock sketch includes `MFRC522`, `LiquidCrystal_I2C`, and `Keypad`, plus `EEPROM`, `SPI`, and `Wire`, which come with the Arduino board cores.

```bash
arduino-cli lib install MFRC522 "LiquidCrystal I2C" Keypad
```

The target board is not named in the files. Set `FQBN` to your board's identifier, install its core with `arduino-cli core install`, and set `PORT` to the board's serial port. Each sketch already sits in a folder with a matching name, so from the repository root:

```bash
arduino-cli compile --fqbn "$FQBN" src/rfid_keypad_door_lock
arduino-cli upload -p "$PORT" --fqbn "$FQBN" src/rfid_keypad_door_lock
```

Wiring as defined in the code: RFID SS on pin 10 and RST on pin 9, LCD at I2C address `0x27`, keypad rows on pins 2 to 5 and columns on A0, 7, 8, and 9, lock output on pin 6 (driven low to unlock). The serial link runs at 9600 baud. Pins A1 to A3 also switch during a card or keypad unlock; their purpose is not documented in the files.

## Notes

Kept for reference. The access and pairing codes are hardcoded demo values near the top of the sketch, and the serial unlock sequence repeats the access code separately in `loop()`, so all of them must be changed before any real use. Pin 9 is assigned to both the RFID reset line and a keypad column, and `experiments/led_blink/led_blink.ino` contains a stray preprocessor line in `setup()` and does not compile as written.

<sub>This repository follows the [Repository Standard](https://github.com/Atadbz/Atadbz/blob/main/REPOSITORY_STANDARD.md).</sub>
