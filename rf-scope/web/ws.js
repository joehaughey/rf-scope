let statusEl = document.getElementById("status");
let rawEl = document.getElementById("raw");
let corEl = document.getElementById("cor");
let voltsEl = document.getElementById("volts");

function connect() {
  let ws = new WebSocket("ws://localhost:8765");

  ws.onopen = () => {
    statusEl.textContent = "Connected to WebSocket";
  };

  ws.onmessage = (ev) => {
    try {
      let d = JSON.parse(ev.data);
      rawEl.textContent = d.raw;
      corEl.textContent = d.cor;
      voltsEl.textContent = d.v.toFixed(3);
    } catch (e) {
      console.error("Bad JSON", e);
    }
  };

  ws.onclose = () => {
    statusEl.textContent = "Disconnected. Reconnecting…";
    setTimeout(connect, 1000);
  };

  ws.onerror = () => {
    statusEl.textContent = "WebSocket error";
  };
}

connect();
