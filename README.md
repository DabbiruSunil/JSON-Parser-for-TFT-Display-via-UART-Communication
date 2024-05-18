##JSON Parser for UART to TFT Display

This project implements a JSON parser that reads in JSON strings over the UART, parses them, and displays the transmitted drawing commands on a TFT display. The project is structured to handle the reception, parsing, and display of JSON protocols using the Erika OS and follows a modular design for clarity and maintainability.


##Table of Contents

Project Overview
Features
Requirements
Installation
Usage
Contributing


##Project Overview

The main objective of this project is to create a system that can:

Receive JSON data via UART interrupts.
Parse the JSON data in a high-priority task.
Display drawing commands extracted from the JSON data on a TFT display via a low-priority task.
This involves three different contexts:

UART ISR: Receives data and stores it in a ring buffer.
High-priority Task (tsk_json): Parses the JSON string and sends commands to the drawing task.
Low-priority Task (tsk_hmi): Draws the content on the TFT display.

##Features

Interrupt-Driven UART Reception: Efficiently handles incoming data.
Ring Buffer Implementation: Manages data reception and prevents overflow.
JSON Parsing: Uses the jsmn library for parsing JSON data.
TFT Display Integration: Displays parsed drawing commands on a TFT screen.
Thread Safety: Ensures safe access to shared resources using semaphores.
Error Handling: Robust error detection and handling during data reception and parsing.

##Requirements

Erika OS: The system is developed based on Erika OS.
TFT Display: For visual output.
UART Interface: For receiving JSON data.
SPI Interface: For communicating with the TFT display.
JSMN Library: For JSON parsing.

##Installation

Clone the repository:

bash
Copy code
git clone https://github.com/your-username/json-uart-tft.git
cd json-uart-tft
Set up the Erika OS environment and install necessary tools.

Add the jsmn library to your project:

bash
Copy code
git submodule add https://github.com/zserge/jsmn externals/jsmn
Include the TFT library and configure the SPI component as per the project requirements.

##Usage

Compile and Flash the Firmware: Build the project using your development environment and flash it to your hardware.

Run the System: Power up your hardware. The system will:

Receive JSON strings over UART.
Parse the JSON data to extract drawing commands.
Display the drawings on the TFT screen.
Test the System: Use a UART terminal to send JSON strings to the system. Example JSON strings for testing:

json
Copy code
{ "c" : "red", "d" : [10, 10, 10, 100], "d" : [10, 100, 100, 100], "d" : [100, 100, 100, 10], "d" : [100, 10, 10, 10] }

##Contributing

Contributions are welcome! Please follow these steps:

Fork the repository.
Create a new branch for your feature or bugfix.
Commit your changes.
Push the branch to your fork.
Open a pull request.


