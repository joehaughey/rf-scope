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
