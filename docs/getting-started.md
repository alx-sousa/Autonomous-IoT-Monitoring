# V1 setup

The repository preserves the prototype firmware with local secret configuration. No fully pinned build environment or repeated hardware validation is available for this portfolio revision. This guide prepares a reproducible attempt; it does not guarantee immediate compilation on every board/core combination.

## 1. Prepare the environment

Use Arduino IDE with ESP32 board support compatible with the specific ESP32-C6 board. Original core and library versions were not recorded, so document the versions used for any new build. The ESP-NOW callback uses the `esp_now_recv_info` interface; a signature error indicates that core compatibility should be checked.

Libraries and platform components used:

- ArduinoIoTCloud and Arduino_ConnectionHandler.
- Adafruit GFX Library and Adafruit SSD1306.
- Adafruit PN532 for the exit node.
- WiFi, ESP-NOW, Wire and HardwareSerial from the ESP32 environment.

## 2. Select the sketch

| Device | File |
|---|---|
| Transmitter | `firmware/transmitter/transmitter.ino` |
| Area receiver | `firmware/area_node/area_node.ino` |
| Exit receiver | `firmware/exit_node/exit_node.ino` |

Open and compile each sketch separately. Each sketch folder matches the `.ino` file name.

## 3. Configure credentials and destinations

For each receiver, copy `secrets.example.h` to `secrets.h` in the same folder. Fill in your own SSID, password and Arduino IoT Cloud device credentials. Do not reuse values from historical material and do not commit the local file; it is excluded through `.gitignore`.

Create the corresponding cloud configuration with the properties and types defined by `initProperties()`; see [communication.md](communication.md).

In the transmitter, replace `receptor1` and `receptor2` with the station MAC addresses of the receivers being used. Published MAC addresses are identifiers from the original prototype, not passwords. Channel sweeping does not by itself eliminate Wi-Fi/ESP-NOW coexistence losses.

## 4. Verify hardware and compile

Review [V1 hardware](../hardware/rev1/README.md): exact board, available GPIOs, voltage levels, PN532 configuration and power stage. Report figures are not verified manufacturing schematics.

Compile all three sketches and record ESP32 core version, library versions, board target and result. This repository does not claim a repeated successful build because the current portfolio revision did not execute the original toolchain on the original hardware.

## 5. Bench checks

1. Confirm boot, OLED, RFID reading and receiver outputs.
2. Verify packet reception and RSSI with the transmitter nearby before calibration.
3. Repeat departure/return behavior and inspect physical outputs, especially on the area node.
4. Verify exit alarm, card reset and re-arm after 6 s.
5. Disconnect the transmitter and Wi-Fi separately; record differences between logical state, physical outputs and telemetry.
6. Record results using the protocol proposed in [testing.md](testing.md).

Do not connect this reproduction to a clinical-care workflow based only on the repository. Its scope is experimental and its technical limitations are documented.
