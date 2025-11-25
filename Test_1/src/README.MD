# ReadPLC Dashboard

## Overview

ReadPLC is a backend application built in **Rust** using **Axum** that reads values from PLCs (Programmable Logic Controllers) at Allpack and exposes them via a REST API. These values can be displayed in a **frontend dashboard** for real-time monitoring and analytics.

The system is intended for the following **departments**:

- Engineering
- HR
- Production
- Safety
- Health & Welfare
- Maintenance

## Features

- Reads values like motor speed, temperature, pressure, and conveyor status from PLCs.
- Provides a simple API endpoint for frontend applications to fetch real-time data.
- Can be extended to work with multiple PLCs and multiple departments.
- Simulates PLC readings for testing before connecting to actual hardware.

## Technologies

- **Rust** for backend logic
- **Axum** for API server
- **Serde** for serializing PLC data into JSON
- **Tokio** for asynchronous programming
- **Frontend**: Any frontend framework (React, Next.js, etc.) can fetch API data

## PLC Integration

- Current simulation returns fake data.
- Real PLC integration requires:
  - **Mitsubishi PLCs**: Use **MC Protocol** (Ethernet) or **Modbus TCP**
  - Network access to the PLC
  - Knowledge of PLC register mapping (e.g., D0 = motor speed, D1 = temperature)

## API Example

```bash
GET http://127.0.0.1:3000/plc
