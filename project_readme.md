# ClubFinX - Royal Fencing Center Financial Ledger System

![C++ Version](https://img.shields.io/badge/C%2B%2B-17%2F20-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Status](https://img.shields.io/badge/Status-In%20Active%20Development-gold.svg)

**ClubFinX** is a dedicated financial ledger and vault management system designed for **Royal Fencing Center** (Mirpur, Dhaka). The platform transitions traditional local text-file financial tracking into a secure, multi-user, real-time client-server environment for finance officers, coaches, and club executive leadership.

---

## 📌 Features

### Core C++ Engine (Current Implementation)
* **Real-time Balance Synchronization:** Auto-calculates vault balances from historical transaction vectors without reset glitches.
* **Auto-generated Unique Identifiers:** Smart sequence allocation for incoming deposits and operational expenses.
* **Chrono-stamped Records:** Captures exact local timestamps (`YYYY-MM-DD HH:MM:SS`) using standard C++ `<chrono>` and `<ctime>` headers.
* **Persistent File I/O:** Automatic backup to `Fin_Records.txt` upon exit and silent reloading upon application initialization.

### Server Architecture Roadmap (In Development)
* **RESTful C++ Server Backend:** Lightweight HTTP server layer built with **Crow C++**.
* **Centralized SQLite Database:** Concurrent multi-user request safety replacing single flat files.
* **Role-Based Access Control (RBAC):**
  * **Finance Officers:** Record deposits, withdrawals, and equipment purchases.
  * **Executive Leadership:** Read-only access to audit live vault balances and review transaction trends.
* **Cross-Platform Dashboard:** Modern web interface styled with custom gold & crimson accents for desktop and mobile devices.

---

## 🛠️ Project Structure

```
RFC Projects/
├── main.cpp              # C++ Engine Entry Point & Interactive Loop
├── Wallet.h / Wallet.cpp # Vault Balance and Fund Handling Class
├── Ledger.h / Ledger.cpp # Transaction History Vector & Persistence Stream
├── Fin_Records.txt       # Local Data Storage File
└── README.md             # Documentation
```

---

## 🚀 Getting Started

### Prerequisites
* **Compiler:** GCC / MinGW (`g++` supporting standard C++17 or later) or MSVC.
* **Build System:** Make, CMake, or standard command terminal.

### Compilation & Execution

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/saleh0089j/ClubFinX.git
   cd ClubFinX
   ```

2. **Compile the C++ Core:**
   ```bash
   g++ -std=c++17 main.cpp Wallet.cpp Ledger.cpp -o ClubFinX.exe
   ```

3. **Run the Executable:**
   * **Windows:**
     ```powershell
     .\ClubFinX.exe
     ```
   * **Linux / macOS:**
     ```bash
     ./ClubFinX.exe
     ```

---

## 📊 Sample Ledger Output Format

```text
ID     TIMESTAMP            CATEGORY                    TYPE      AMOUNT
-------------------------------------------------------------------------
101    2026-10-25 10:15:00  Monthly Membership Fees     INCOME    ৳15,000.00
102    2026-10-26 14:20:10  Target Board Maintenance    EXPENSE   ৳4,500.00
103    2026-10-28 09:30:45  Student Admission           INCOME    ৳8,000.00
```

---

## 👨‍💻 Maintainer

* **Developer:** Saleh
* **Organization:** Royal Fencing Center (Mirpur, Dhaka) / AIUB Data Science Project

---

## 📄 License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.