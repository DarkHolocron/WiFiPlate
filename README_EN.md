# WiFiPlate

## Table of Contents

- [Project Description](#chapter-0)
- [Features](#chapter-1)
- [Library Versions](#chapter-2)
- [Dependencies](#chapter-3)
- [Connection Diagram](#chapter-4)
- [Installation](#chapter-5)
- [OTA Update](#chapter-6)
- [First Boot](#chapter-7)
- [Usage](#chapter-8)
- [Controls](#chapter-9)

---

<a id="chapter-0"></a>
## Project Description

WiFiPlate is a simple WiFi door sign based on Wemos Mini and MAX7219 LED matrices.

---

<a id="chapter-1"></a>
## Features

- Display text on the matrix via web interface
- Quick selection of preset statuses:
  - Busy
  - Away
  - Available
- Wi-Fi configuration via built-in web interface
- Control via Gyver Settings mobile app
- Compatible with Arduino IDE and PlatformIO

---

<a id="chapter-2"></a>
## Library Versions

The project uses old versions of GyverLibs libraries. With new versions, the project will **NOT WORK** due to API conflicts.

---

<a id="chapter-3"></a>
## Dependencies

- [StringUtils](https://github.com/GyverLibs/StringUtils) v1.4.29
- [GyverHTTP](https://github.com/GyverLibs/GyverHTTP) v1.0.30
- [GyverDB](https://github.com/GyverLibs/GyverDB) v1.4.3
- [GTL](https://github.com/GyverLibs/GTL) v1.4.2
- [BSON](https://github.com/GyverLibs/BSON) v2.3.4
- [Settings](https://github.com/GyverLibs/Settings) v1.3.16
- [WiFiConnector](https://github.com/GyverLibs/WiFiConnector) v1.0.5
- [GyverMAX7219](https://github.com/GyverLibs/GyverMAX7219)
- [GyverGFX](https://github.com/GyverLibs/GyverGFX)

### Installing Dependencies

**PlatformIO:**

Libraries are installed automatically from platformio.ini

**Arduino IDE:**

Install libraries via Library Manager, specifying the required versions from the [Dependencies](#chapter-3) section

---

<a id="chapter-4"></a>
## Connection Diagram

The connection diagram is available at the [link](https://github.com/DarkHolocron/WiFiPlate/blob/dev/scheme/scheme.png)

---

<a id="chapter-5"></a>
## Installation

### PlatformIO (recommended)

1. Clone the repository
2. Open the project in VS Code with PlatformIO extension
3. Upload the firmware:

```bash
pio run -t upload
```

### Arduino IDE

1. Copy the code from `src/main.cpp`
2. Install libraries via Library Manager
3. Select the board and upload the firmware

---

<a id="chapter-6"></a>
## OTA Update

Ready-made firmware in `.bin` format is available in the [Releases](https://github.com/DarkHolocron/WiFiPlate/releases) section on GitHub.

To update the firmware:

1. Open the device web interface
2. Click the "hamburger menu" (☰) in the upper right corner
3. Select "OTA"
4. Click "Choose File" and select the downloaded firmware file (.bin)
5. After selecting the file, a pop-up window will appear asking to confirm the firmware update. Click "OK" and wait for the process to complete

---
<a id="chapter-7"></a>
## First Boot

On first boot, the device creates its own Wi-Fi network named "WiFiPlate". To configure:

1. Connect to the "WiFiPlate" network from your phone or computer
2. Open your browser and go to `192.168.4.1`
3. In the interface that appears, enter your Wi-Fi network name (SSID) and password
4. Click the "Connect" button
5. After successful connection, the device will reboot and connect to your Wi-Fi network. The device's IP address will be automatically displayed in the Serial port

---

<a id="chapter-8"></a>
## Usage

### Web Interface

To access the web interface, use the IP address obtained from the Serial port during connection and enter it into your browser.

### Mobile Apps

After Wi-Fi configuration, you can control the sign via apps. The apps will automatically find the device on the local network without requiring manual IP entry:

- **iOS**: [Gyver Settings](https://apps.apple.com/us/app/gyver-settings/id6751504764)
- **Android**: [Settings-discover](https://github.com/GyverLibs/Settings-discover)
- **Windows**: [Remote Settings Manager](https://github.com/TonTon-Macout/Remote-Settings-Manager)

---

<a id="chapter-9"></a>
## Controls

### Text Input Field

- Enter any text in the input field
- Click the "Send" button to display the text on the matrix

### Quick Access Buttons

- **Busy** - displays "Busy" status
- **Away** - displays "Away" status
- **Available** - displays "Available" status
- **Clear** - clears the matrix