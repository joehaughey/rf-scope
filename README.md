# rf-scope

RF Scope – Arduino A0 + TM1637 Display + USB/WebSocket Dock This project reads an RF‑related envelope or detector output on Arduino Uno A0, applies a correction curve, displays the processed value on a TM1637 4‑digit 7‑segment display, and streams live JSON data over USB to a Python WebSocket bridge for viewing in a browser.

It is designed as a simple, low‑cost RF activity monitor and data logger.

📦 Project Structure Code firmware/uno_rf_reader/ Arduino sketch + TM1637 wrapper server/ Python USB → WebSocket bridge web/ HTML/JS/CSS docking page hardware/ Photos, schematics, panel layouts 🔧 Hardware Overview Arduino Uno (or compatible CH340 board)

TM1637 4‑digit display

CLK → D2

DIO → D3

RF detector / envelope source → A0

Optional SMA panel, shielded enclosure, or RF front‑end

⚠ Important Caveats & Notes

    A0 is NOT a true RF input A0 only measures DC or low‑frequency envelope. You must feed it with an RF detector or rectified signal — direct RF will not work.

    ADC noise & jitter The Uno ADC is 10‑bit and sensitive to USB noise and ground loops. Expect small fluctuations even with a stable input.

    Correction curve The firmware uses:

Code corrected = max(raw - 289, 0) volts = corrected / 1023 * 5.0 Adjust these constants to match your detector’s characteristics.

    TM1637 display quirks The module multiplexes internally and can flicker if updated too fast. The firmware refreshes at a safe 20 Hz.

    WebSocket timing The Python bridge forwards each JSON line immediately. If you increase sampling speed, browser updates may lag.

    COM port auto‑detection If detection fails, edit usb_ws_bridge.py and set your port manually:

python return "COM4" 🧩 Firmware (Arduino Uno) Located in:

Code firmware/uno_rf_reader/uno_rf_reader.ino Features:

Reads A0

Applies correction

Displays volts × 100 on TM1637

Sends JSON over Serial at 115200 baud

Install the library:

Code TM1637Display by Avishay Orpaz Upload using Arduino IDE.

🖥 Python USB → WebSocket Bridge Located in:

Code server/usb_ws_bridge.py Install dependencies:

bash pip install -r requirements.txt Run:

bash python usb_ws_bridge.py Starts:

Code ws://localhost:8765 🌐 Web Docking Page Located in:

Code web/index.html Open in any browser. Displays raw ADC, corrected value, and voltage (3 decimal places). Automatically reconnects if the WebSocket drops.

📸 Hardware Folder Place:

SMA panel photos

FR4 mounting plates

Display module photos

Schematics

DXF layouts

in:

Code hardware/photos/ ⚡ Quick Start (Windows run.bat) From the server/ directory:

Double‑click run.bat

It installs dependencies and starts the WebSocket bridge

Open web/index.html in your browser

Watch live RF envelope data from your Arduino Uno

Example contents of run.bat:

bat @echo off echo ----------------------------------------- echo RF Scope - USB WebSocket Bridge Launcher echo ----------------------------------------- echo. echo Installing Python dependencies... pip install -r requirements.txt echo. echo Starting WebSocket bridge... python usb_ws_bridge.py echo. echo Bridge stopped. pause 📄 License MIT License (or your choice)

🤝 Contributions Pull requests welcome — especially:

improved correction curves

better ADC filtering

alternative displays

ESP32 or RP2040 versions ESP32 or RP2040 versions

📡 Ham Radio Organisations for Beginners If you’re new to amateur radio, these national organisations are the best starting points for learning, licensing, and joining local clubs. Each provides beginner guides, exam information, and community support.

🌍 Region 🏢 Organisation 📖 Description 🔗 Official Link Worldwide International Amateur Radio Union (IARU) Global umbrella body representing amateur radio societies; promotes spectrum protection and international cooperation. https://www.iaru.org United States ARRL – American Radio Relay League National association for amateur radio; offers licensing guides, clubs, contests, and emergency communications programs. https://www.arrl.org United Kingdom RSGB – Radio Society of Great Britain Official UK body for amateur radio; provides training, licensing guidance, and local club directories. https://rsgb.org China CRSA – Chinese Radio Sports Association National organisation managing amateur radio licensing and contests under the Chinese Amateur Radio League. http://www.crsa.org.cn Russia SRR – Soyuz Radiolyubitelei Rossii (Union of Radio Amateurs of Russia) National amateur radio society coordinating licensing, contests, and emergency radio networks. https://www.srr.ru Australia WIA – Wireless Institute of Australia The world’s oldest national amateur radio society; provides licensing, education, and advocacy. https://www.wia.org.au

💡 Getting Started Tips Visit your national organisation’s “Getting Started” or “Licensing” page.

Join a local club listed on their site — most offer beginner training and exam prep.

Explore IARU Region 1 (Europe/Africa), Region 2 (Americas), or Region 3 (Asia‑Pacific) for international band plans and coordination.

🚀 Next Steps for New Operators Once you’ve joined your national amateur radio organisation and obtained your licence, here’s how to begin operating confidently:

🛡️ Safety and Operating Etiquette Amateur radio is both a technical and social hobby. Following good safety and etiquette ensures reliable operation and respect for the spectrum.

⚡ Electrical & RF Safety Always ground your equipment properly — use a dedicated earth rod or bonded ground bus.

Keep coax connectors and exposed terminals insulated to prevent accidental contact.

Avoid transmitting near sensitive electronics or medical devices.

Be aware of RF exposure limits — maintain safe distances from antennas during transmission.

Use fused power supplies and check polarity before connecting radios or amplifiers.

Never operate high‑power transmitters indoors or near people.

🌩️ Lightning & Grounding Install a lightning arrestor or surge protector on outdoor antennas.

Disconnect coax and power leads during storms.

Bond all grounds (radio, mast, and electrical) to a single point to prevent potential differences.

🎙️ On‑Air Etiquette Listen before transmitting — ensure the frequency is clear.

Identify yourself with your call sign at regular intervals.

Keep transmissions concise and courteous.

Avoid political, commercial, or offensive content — amateur bands are for technical and personal communication.

Respect band plans and regional frequency allocations.

When joining nets, wait for the net control operator to invite check‑ins.

🧠 Good Practice Log your contacts accurately.

Share knowledge with newcomers.

Maintain your equipment and antennas regularly.

Follow your national regulations — they protect your licence and the hobby’s reputation. Get your call sign – Your licensing authority will issue a unique identifier (e.g., M7ABC in the UK or KJ7XYZ in the US). This is your radio identity.

Start simple – Begin with VHF/UHF handheld or mobile radios for local contacts. These are inexpensive and easy to use.

Join nets and local repeaters – Listen first, then check in when invited. It’s the best way to learn etiquette and meet other operators.

Explore HF bands – When ready, move to shortwave (HF) for worldwide communication. Learn about propagation, antennas, and band conditions.

Log your contacts – Keep a station log (paper or digital). It helps track progress and QSL confirmations.

Experiment and build – Try antennas, SDRs, or Arduino‑based signal tools like your RF Scope project. Amateur radio thrives on experimentation.

Stay curious – Read your national organisation’s magazine, join contests, and follow IARU updates for global developments.

🔧 Recommended Starter Equipment 🌍 Region 📻 Typical Beginner Radio 📡 Antenna Type 🔋 Power Supply 🧰 Notes United States Baofeng UV‑5R or Yaesu FT‑65 Dual‑band whip or mag‑mount 12 V DC supply or Li‑ion pack Affordable handhelds; ARRL guides cover setup and repeater use. United Kingdom Yaesu FT‑4X or Icom IC‑V86 2 m/70 cm whip or collinear 13.8 V PSU or battery pack RSGB Foundation licence training includes radio basics and antenna safety. China Quansheng UV‑K5 or TYT TH‑UV88 Dual‑band whip USB‑charged Li‑ion Widely available; CRSA clubs often help with programming and band plans. Russia Alinco DJ‑500 or Baofeng UV‑82 2 m/70 cm whip 12 V DC or internal battery SRR regional groups assist with repeater coordination and call‑sign registration. Australia Yaesu FT‑70DR or Icom IC‑T10 2 m/70 cm whip or mobile mag‑mount 13.8 V PSU or car adapter WIA recommends starting with VHF/UHF handhelds before HF expansion.

💡 Starter Advice Begin with VHF/UHF handhelds for local contacts — simple, safe, and inexpensive.

Use a mag‑mount antenna if operating from a vehicle or indoors near a window.

Always check your national band plan before transmitting.

Upgrade gradually: HF transceivers, directional antennas, and SDRs come later.

Keep your first setup portable — it encourages experimentation and learning.
