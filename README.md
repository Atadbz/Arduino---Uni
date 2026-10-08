# Arduino RFID and Keypad Door Lock

An Arduino sketch for an electronic lock that opens with an RFID card, a keypad code, or a code sent over the serial port.

<sub>HARDWARE PROJECT · 2023 · ARDUINO C++</sub>

## Overview

The main sketch combines an MFRC522 RFID reader, a 4x4 keypad, and a 16x2 I2C LCD into a lock controller. A card whose UID is stored in EEPROM, or the access code typed on the keypad, triggers an unlock. A separate pairing code saves the next scanned card's UID to EEPROM. The access code sent over the serial port, followed by one more character, also unlocks.

## Contents

| Path | Description |
| --- | --- |
| `src/` | The lock sketch, `rfid_keypad_door_lock/rfid_keypad_door_lock.ino`: RFID card check and pairing stored in EEPROM, masked keypad entry, serial unlock, and LCD status messages. |
| `experiments/` | `01_led_blink/01_led_blink.ino`, a short, unrelated sketch. It is meant to blink LEDs on pins 2 and 8 with a delay that shrinks each cycle, then set pin 12 high. A stray preprocessor line in `setup()` means it does not compile as written. |

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

The code wires the RFID reader with SS on pin 10 and RST on pin 9. The LCD is at I2C address `0x27`. Keypad rows use pins 2 to 5, and columns use A0, 7, 8, and 9. Every unlock drives pin 6 low for five seconds, likely the lock or relay output, before the LCD returns to `BLOCKED`.

The serial link runs at 9600 baud. The code comments call the serial unlock path BT, likely for a Bluetooth module. Pins A1 to A3 also switch during a card or keypad unlock, but their purpose is not documented in the files.

## Notes

The access and pairing codes are hardcoded near the top of the sketch. The serial unlock sequence repeats the access code separately in `loop()`, so change all of them before any real use. Pin 9 is assigned to both the RFID reset line and a keypad column.

<sub>This repository follows the [Repository Standard](https://github.com/Atadbz/Atadbz/blob/main/REPOSITORY_STANDARD.md).</sub>
