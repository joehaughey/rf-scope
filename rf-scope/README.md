 


RF Scope – Arduino A0 + TM1637 Display + USB/WebSocket Dock
This project reads an RF‑related envelope or detector output on Arduino Uno A0, applies a correction curve, displays the processed value on a TM1637 4‑digit 7‑segment display, and streams live JSON data over USB to a Python WebSocket bridge for viewing in a browser.

It is designed as a simple, low‑cost RF activity monitor and data logger.

📦 Project Structure
Code
firmware/uno_rf_reader/   Arduino sketch + TM1637 wrapper
server/                   Python USB → WebSocket bridge
web/                      HTML/JS/CSS docking page
hardware/                 Photos, schematics, panel layouts
🔧 Hardware Overview
Arduino Uno (or compatible CH340 board)

TM1637 4‑digit display

CLK → D2

DIO → D3

RF detector / envelope source → A0

Optional SMA panel, shielded enclosure, or RF front‑end

⚠ Important Caveats & Notes
1. A0 is NOT a true RF input
A0 only measures DC or low‑frequency envelope.
You must feed it with an RF detector or rectified signal — direct RF will not work.

2. ADC noise & jitter
The Uno ADC is 10‑bit and sensitive to USB noise and ground loops.
Expect small fluctuations even with a stable input.

3. Correction curve
The firmware uses:

Code
corrected = max(raw - 289, 0)
volts = corrected / 1023 * 5.0
Adjust these constants to match your detector’s characteristics.

4. TM1637 display quirks
The module multiplexes internally and can flicker if updated too fast.
The firmware refreshes at a safe 20 Hz.

5. WebSocket timing
The Python bridge forwards each JSON line immediately.
If you increase sampling speed, browser updates may lag.

6. COM port auto‑detection
If detection fails, edit usb_ws_bridge.py and set your port manually:

python
return "COM4"
🧩 Firmware (Arduino Uno)
Located in:

Code
firmware/uno_rf_reader/uno_rf_reader.ino
Features:

Reads A0

Applies correction

Displays volts × 100 on TM1637

Sends JSON over Serial at 115200 baud

Install the library:

Code
TM1637Display by Avishay Orpaz
Upload using Arduino IDE.

🖥 Python USB → WebSocket Bridge
Located in:

Code
server/usb_ws_bridge.py
Install dependencies:

bash
pip install -r requirements.txt
Run:

bash
python usb_ws_bridge.py
Starts:

Code
ws://localhost:8765
🌐 Web Docking Page
Located in:

Code
web/index.html
Open in any browser.
Displays raw ADC, corrected value, and voltage (3 decimal places).
Automatically reconnects if the WebSocket drops.

📸 Hardware Folder
Place:

SMA panel photos

FR4 mounting plates

Display module photos

Schematics

DXF layouts

in:

Code
hardware/photos/
⚡ Quick Start (Windows run.bat)
From the server/ directory:

Double‑click run.bat

It installs dependencies and starts the WebSocket bridge

Open web/index.html in your browser

Watch live RF envelope data from your Arduino Uno

Example contents of run.bat:

bat
@echo off
echo -----------------------------------------
echo  RF Scope - USB WebSocket Bridge Launcher
echo -----------------------------------------
echo.
echo Installing Python dependencies...
pip install -r requirements.txt
echo.
echo Starting WebSocket bridge...
python usb_ws_bridge.py
echo.
echo Bridge stopped.
pause
📄 License
MIT License (or your choice)

🤝 Contributions
Pull requests welcome — especially:

improved correction curves

better ADC filtering

alternative displays

ESP32 or RP2040 versions
ESP32 or RP2040 versions

📡 Ham Radio Organisations for Beginners
If you’re new to amateur radio, these national organisations are the best starting points for learning, licensing, and joining local clubs. Each provides beginner guides, exam information, and community support.

🌍 Region	🏢 Organisation	📖 Description	🔗 Official Link
Worldwide	International Amateur Radio Union (IARU)	Global umbrella body representing amateur radio societies; promotes spectrum protection and international cooperation.	https://www.iaru.org
United States	ARRL – American Radio Relay League	National association for amateur radio; offers licensing guides, clubs, contests, and emergency communications programs.	https://www.arrl.org
United Kingdom	RSGB – Radio Society of Great Britain	Official UK body for amateur radio; provides training, licensing guidance, and local club directories.	https://rsgb.org
China	CRSA – Chinese Radio Sports Association	National organisation managing amateur radio licensing and contests under the Chinese Amateur Radio League.	http://www.crsa.org.cn
Russia	SRR – Soyuz Radiolyubitelei Rossii (Union of Radio Amateurs of Russia)	National amateur radio society coordinating licensing, contests, and emergency radio networks.	https://www.srr.ru
Australia	WIA – Wireless Institute of Australia	The world’s oldest national amateur radio society; provides licensing, education, and advocacy.	https://www.wia.org.au


💡 Getting Started Tips
Visit your national organisation’s “Getting Started” or “Licensing” page.

Join a local club listed on their site — most offer beginner training and exam prep.

Explore IARU Region 1 (Europe/Africa), Region 2 (Americas), or Region 3 (Asia‑Pacific) for international band plans and coordination.
