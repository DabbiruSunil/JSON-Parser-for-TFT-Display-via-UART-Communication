# 📡 JSON Parser for UART to TFT Display

This project implements a modular JSON parser that receives drawing commands over UART, parses them, and renders the graphics on a TFT display. Built on **Erika OS**, it demonstrates efficient interrupt-driven communication, robust parsing, and multitask scheduling for embedded systems.

---

## 📌 Project Overview

The system processes JSON data received through UART and updates a TFT screen in real time.
Three main contexts work together:

1️⃣ **UART ISR** – Captures incoming data and stores it in a ring buffer.
2️⃣ **High-Priority Task (`tsk_json`)** – Parses JSON strings using the *jsmn* library and forwards commands.
3️⃣ **Low-Priority Task (`tsk_hmi`)** – Draws the parsed elements on the TFT display.

This layered approach ensures smooth data flow while maintaining responsiveness.

---

## ✨ Features

* **Interrupt-Driven UART Reception** – Efficient handling of continuous data streams.
* **Ring Buffer Implementation** – Prevents overflow and manages asynchronous input.
* **Robust JSON Parsing** – Lightweight parsing using the [jsmn](https://github.com/zserge/jsmn) library.
* **TFT Display Integration** – Real-time rendering of parsed drawing commands via SPI.
* **Thread Safety** – Shared resources protected with semaphores.
* **Error Handling** – Detects and manages malformed JSON or communication errors.

---

## 🛠️ Requirements

* **Hardware**: PSoC LabBoard (or compatible board with UART & SPI), TFT display.
* **Software**: [Erika OS](https://erika-enterprise.com/), GCC toolchain, PSoC Creator (or equivalent).
* **Libraries**:

  * [jsmn](https://github.com/zserge/jsmn) for JSON parsing.
  * TFT display driver compatible with Erika OS.

---

## ⚙️ Installation

```bash
# Clone the repository
git clone https://github.com/DabbiruSunil/JSON-Parser-for-TFT-Display-via-UART-Communication.git
cd JSON-Parser-for-TFT-Display-via-UART-Communication

# Add jsmn as a submodule
git submodule add https://github.com/zserge/jsmn externals/jsmn
```

Set up the Erika OS environment and configure the SPI/TFT driver as per your hardware.

---

## ▶️ Usage

1. **Build & Flash**: Compile the firmware with your Erika OS toolchain and flash it to the target board.
2. **Run the System**:

   * Send JSON commands over UART (e.g., using a serial terminal).
   * The parser extracts drawing instructions and updates the TFT display.

**Example JSON Input**

```json
{ "c":"red", "d":[10,10,10,100], "d":[10,100,100,100] }
```

---

## 🧪 Testing

* Use a UART terminal (e.g., PuTTY, HTERM) to send test JSON strings.
* Validate real-time display updates and check error handling with malformed inputs.

---

## 📊 Project Structure

```
├─ src/                # Application and OS tasks
│  ├─ isr_uart.c       # UART interrupt & ring buffer
│  ├─ tsk_json.c       # JSON parsing task
│  ├─ tsk_hmi.c        # TFT drawing task
├─ externals/jsmn/     # JSON parser library
└─ README.md
```

---

## 🤝 Contributing

Contributions are welcome!

1. Fork the repository
2. Create a feature branch
3. Commit and push your changes
4. Open a pull request

---

**License**
MIT License – See [LICENSE](LICENSE) for details.

**Author**: [Sunil Dabbiru](https://github.com/DabbiruSunil)

