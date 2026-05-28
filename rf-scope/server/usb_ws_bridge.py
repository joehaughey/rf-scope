import asyncio
import json
import serial
import serial.tools.list_ports
import websockets

SERIAL_BAUD = 115200
WS_HOST = "localhost"
WS_PORT = 8765

def find_arduino():
    ports = serial.tools.list_ports.comports()
    for p in ports:
        if "Arduino" in p.description or "CH340" in p.description or "USB-SERIAL" in p.description:
            return p.device
    # fallback: user can edit this
    return "COM3"

async def serial_reader(ws, ser):
    while True:
        line = ser.readline().decode(errors="ignore").strip()
        if not line:
            await asyncio.sleep(0.01)
            continue
        try:
            data = json.loads(line)
        except json.JSONDecodeError:
            continue
        await ws.send(json.dumps(data))

async def handler(websocket):
    port = find_arduino()
    ser = serial.Serial(port, SERIAL_BAUD, timeout=1)
    try:
        await serial_reader(websocket, ser)
    finally:
        ser.close()

async def main():
    async with websockets.serve(handler, WS_HOST, WS_PORT):
        print(f"WebSocket server on ws://{WS_HOST}:{WS_PORT}")
        await asyncio.Future()  # run forever

if __name__ == "__main__":
    asyncio.run(main())
