 


📦Project Structure
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

Optional SMA panel, shielded enclosure, or RF front‑end.

⚠ Important Caveats & Notes
1. A0 is NOT a true RF input
A0 only measures DC or low‑frequency envelope.
You must feed it with:

an RF detector

an envelope output
or a rectified / filtered signal

Direct RF into A0 will not work and may damage 
the board.

2. ADC noise & jitter
The Uno ADC is:

10‑bit

~9.5 effective bits

susceptible to USB noise, ground loops, and RF ingress

Expect small fluctuations even with a stable input.

3. Correction curve is project‑specific
The example firmware uses:

Code
corrected = max(raw - 289, 0)
volts = corrected / 1023 * 5.0
This is not universal.
You should adjust the offset and scaling to match 
your RF detector’s characteristics.

4. TM1637 display refresh quirks
The TM1637:

multiplexes internally

can flicker if updated too fast

has limited brightness resolution

The firmware updates it at a safe rate (20 Hz).

5. WebSocket timing
The Python bridge forwards each JSON line immediately.
If you increase sampling speed:

browser updates may lag

CPU usage may rise

WebSocket reconnects may occur

The default 50 ms loop is stable.

6. COM port auto‑detection
The bridge attempts to detect:

“Arduino”

“CH340”

“USB‑SERIAL”

If it fails, edit:

python
return "COM3"
to your actual port.

🧩 Firmware (Arduino Uno)
Located in:

Code
firmware/uno_rf_reader/uno_rf_reader.ino
Features:

Reads A0

Applies correction

Displays volts × 100 on TM1637

Sends JSON over Serial at 115200 baud

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

Displays:

Raw ADC

Corrected value

Voltage (3 decimal places)

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
🚀 Quick Start
Upload Arduino firmware

Run Python WebSocket bridge

Open web/index.html

Watch live RF envelope data

📄 License
MIT License (or your choice)

🤝 Contributions
Pull requests welcome — especially:

improved correction curves

better ADC filtering

alternative displays

ESP32 or RP2040 versions
