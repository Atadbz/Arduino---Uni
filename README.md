# Arduino RFID and Keypad Lock

An Arduino sketch for an electronic lock that opens with an RFID card, a keypad code, or a code sent over a serial (Bluetooth) link.

<sub>HARDWARE PROJECT · 2023 · ARDUINO · C++</sub>

## Overview

The main sketch combines an MFRC522 RFID reader, a 4x4 keypad, and a 16x2 I2C LCD into a lock controller. A card whose UID is stored in EEPROM, or an 8-character access code typed on the keypad, triggers an unlock; a separate pairing code saves the next scanned card's UID to EEPROM. The same code sent over the serial port (marked as Bluetooth in the code) and followed by any further character, such as a newline, also unlocks; each unlock drives pin 6 low for five seconds before the LCD returns to `BLOCKED`. The repository also holds a small, unrelated LED blink sketch.

## Contents

| Path | Description |
| --- | --- |
| [`rfid_keypad_door_lock.ino`](rfid_keypad_door_lock.ino) | Lock sketch: RFID card check and pairing stored in EEPROM, masked keypad entry, serial unlock, and LCD status messages. |
| [`led_blink.ino`](led_blink.ino) | Small sketch that blinks LEDs on pins 2 and 8 with a delay that shrinks each cycle, then sets pin 12 high. |

## Usage

The lock sketch includes `MFRC522`, `LiquidCrystal_I2C`, and `Keypad`, plus the bundled `EEPROM`, `SPI`, and `Wire` libraries.

```bash
arduino-cli lib install MFRC522 "LiquidCrystal I2C" Keypad
```

The target board is not named in the files. Set `FQBN` to your board's identifier and install its core with `arduino-cli core install` first. The Arduino tools compile every `.ino` file in a folder as one sketch, so give each sketch its own folder with a matching name:

```bash
mkdir rfid_keypad_door_lock
cp rfid_keypad_door_lock.ino rfid_keypad_door_lock/
arduino-cli compile --fqbn "$FQBN" rfid_keypad_door_lock
```

Wiring as defined in the code: RFID SS on pin 10 and RST on pin 9, LCD at I2C address `0x27`, keypad rows on pins 2 to 5 and columns on A0, 7, 8, and 9, lock output on pin 6 (driven low to unlock). Pins A1 to A3 also switch during a card or keypad unlock; their purpose is not documented in the files.

## Notes

Kept for reference. The access and pairing codes are hardcoded near the top of the sketch, and the serial unlock sequence is hardcoded again separately in `loop()`, so all of them must be changed before any real use; pin 9 is assigned to both the RFID reset line and a keypad column. `led_blink.ino` contains a stray preprocessor line in `setup()` and does not compile as written.
