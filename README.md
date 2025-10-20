# FS_A8S Arduino Library

A lightweight Arduino library for decoding serial data from the **FlySky FS-A8S receiver**.  
It reads raw data frames via UART, extracts up to 6 channel values, and provides both raw and normalized outputs for use in your RC projects.

---

## ✨ Features

- ✅ Reads serial data frames (starting with `0x20 0x40`)
- ✅ Supports up to 6 RC channels  
- ✅ Provides both raw and scaled (0–255) channel values  
- ✅ Compatible with Arduino boards supporting hardware serial (e.g. Uno, Nano, Mega)  
- ✅ Easy-to-integrate class-based design

---

## 📦 Installation

1. Download or clone this repository:
   ```bash
   git clone https://github.com/yourusername/FS_A8S.git
