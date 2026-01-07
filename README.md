# RTL8720DN Starter Kit

RTL8720DN/BW16 Arduino development starter kit with VSCode DevContainer - ready to code in minutes.

## Features

- **Zero-config setup** - DevContainer handles all dependencies
- **Dual-band WiFi** - 2.4GHz and 5GHz support
- **Multiple boards** - BW16-Kit v1.2 and NiceMCU 8720 v1
- **HAL libraries** - Hardware abstraction for easy development
- **Ready examples** - WiFi scan, LED control, UART test

## Supported Boards

| Board | Chip | WiFi | BLE | GPIO |
|-------|------|------|-----|------|
| BW16-Kit v1.2 | RTL8720DN | 2.4/5GHz | 5.0 | 13 pins |
| NiceMCU 8720 v1 | RTL8720DN | 2.4/5GHz | 5.0 | 10 pins |

## Quick Start

### Prerequisites

- [VSCode](https://code.visualstudio.com/)
- [Docker Desktop](https://www.docker.com/products/docker-desktop)
- [Dev Containers extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)

### Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/FatihErtugral/rtl8720dn-starter-kit.git
   cd rtl8720dn-starter-kit
   ```

2. Open in VSCode:
   ```bash
   code .
   ```

3. When prompted, click **"Reopen in Container"** or run:
   - `Ctrl+Shift+P` → "Dev Containers: Reopen in Container"

4. Wait for the container to build (first time only)

### Build & Upload

This project uses **VSCode Tasks** for building. The active file's directory is automatically used as the sketch path.

1. Open a `.ino` file (e.g., `src/examples/wifi_scan/wifi_scan.ino`)

2. Run build task:
   - Press `Ctrl+Shift+B` (default build)
   - Or `Ctrl+Shift+P` → "Tasks: Run Task" → Select board:
     - **Build: NICEMCU** - For NiceMCU 8720 v1
     - **Build: BW16-Kit** - For BW16-Kit v1.2

3. Upload to board:
   - Set your port: `export MY_PORT=/dev/ttyUSB0`
   - Run "Upload" task

4. Monitor serial output:
   - Run "Monitor: Serial (115200)" task

## Project Structure

```
├── .devcontainer/          # DevContainer configuration
├── .vscode/
│   └── tasks.json          # Build tasks for each board
├── libraries/
│   ├── RTL8720_Common/     # Board configs, HAL, Serial manager
│   ├── RTL8720_Led/        # LED and RGB LED control
│   └── RTL8720_Wireless/   # WiFi and BLE modules
├── src/examples/
│   ├── wifi_scan/          # WiFi network scanner
│   ├── led_test/           # LED blink test
│   └── uart_test/          # Serial communication test
├── variants/               # Board-specific pin definitions
│   ├── bw16_kit_v1_2/
│   └── nicemcu_8720_v1/
└── docs/                   # Board diagrams and pinouts
```

## Examples

### WiFi Scan

```cpp
#include <BoardConfig.h>
#include <WiFiModule.h>

WiFiModule wifi;

void setup() {
    DEBUG_SERIAL.begin(115200);
    wifi.beginStation();
    delay(2000);
}

void loop() {
    int networks = wifi.scan();
    for (int i = 0; i < networks; i++) {
        WiFiNetworkInfo info;
        wifi.getNetworkInfo(i, info);
        DEBUG_SERIAL.println(info.ssid);
    }
    delay(10000);
}
```

### LED Control

```cpp
#include <BoardConfig.h>
#include <Led.h>

Led led(PIN_LED_BLUE);

void setup() {
    led.begin();
}

void loop() {
    led.toggle();
    delay(500);
}
```

## Board Pinouts

### BW16-Kit v1.2

| Pin | Function | Notes |
|-----|----------|-------|
| PA7 | LOG_TX | Debug serial |
| PA8 | LOG_RX | Debug serial |
| PA12 | LED_R | RGB Red (Active HIGH) |
| PA13 | LED_B | RGB Blue (Active HIGH) |
| PA14 | LED_G | RGB Green (Active HIGH) |
| PB3 | ADC | Analog input |

### NiceMCU 8720 v1

| Pin | Function | Notes |
|-----|----------|-------|
| PA7 | LOG_TX | Debug serial |
| PA8 | LOG_RX | Debug serial |
| PA12 | LED_R | RGB Red (Active LOW) |
| PA13 | LED_B | RGB Blue (Active LOW) |
| PA14 | LED_G | RGB Green (Active LOW) |

## Libraries

### RTL8720_Common

- `BoardConfig.h` - Auto-detects board and includes correct config
- `HardwareAbstraction.h` - Hardware info and utilities
- `SerialManager` - Multi-serial port management

### RTL8720_Led

- `Led` - Simple LED control (on/off/toggle/blink)
- `RgbLed` - RGB LED with color mixing and effects

### RTL8720_Wireless

- `WiFiModule` - WiFi scanning, connecting, AP mode
- `WirelessManager` - High-level WiFi + BLE management
- `BleModule` - BLE functionality (placeholder)

## VSCode Tasks

| Task | Shortcut | Description |
|------|----------|-------------|
| Build: NICEMCU | `Ctrl+Shift+B` | Compile for NiceMCU board (default) |
| Build: BW16-Kit | - | Compile for BW16-Kit board |
| Upload | - | Upload to connected board |
| Monitor: Serial (115200) | - | Open serial monitor at 115200 baud |
| Monitor: Serial (9600) | - | Open serial monitor at 9600 baud |

## Troubleshooting

### WiFi scan shows "netif is DOWN"

This is fixed in the latest version. Make sure you have the updated `WiFiModule.h` that doesn't call `WiFi.disconnect()` before initialization.

### Can't upload to board

1. Check the correct COM port
2. Press and hold BOOT button while pressing RESET
3. Release RESET first, then BOOT
4. Start upload within 5 seconds

### DevContainer won't start

1. Make sure Docker Desktop is running
2. Try rebuilding: `Ctrl+Shift+P` → "Dev Containers: Rebuild Container"

## Resources

- [Ameba Arduino SDK](https://github.com/ambiot/ambd_arduino)
- [BW16 Getting Started](https://www.amebaiot.com/en/amebad-bw16-arduino-getting-started/)
- [RTL8720DN Datasheet](https://www.realtek.com/en/products/communications-network-ics/item/rtl8720dn)

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
