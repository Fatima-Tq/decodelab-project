# 🔐 Password Strength Checker

> **Project 1: Industrial Training Kit** | **Batch 2026** | **Powered by DecodeLabs**

A professional-grade password strength analysis tool built with **C++**. This project demonstrates fundamental security principles including entropy calculation, input validation, and defensive programming.

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [How It Works](#how-it-works)
- [Example Output](#example-output)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
  
---

## 🎯 Overview

This **Password Strength Checker** evaluates user passwords based on:

- **Entropy** (bits of randomness)
- **Character diversity** (uppercase, lowercase, digits, special characters)
- **Length** (overall password size)
- **Common patterns** (leaked/breached password detection)

The program provides actionable feedback to help users create stronger passwords.

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| 🔢 **Entropy Calculation** | Measures password randomness using `length × log₂(pool_size)` |
| 🔍 **Character Analysis** | Checks for uppercase, lowercase, digits, and special characters |
| 📊 **Strength Rating** | Classifies passwords as: Very Weak → Weak → Medium → Strong → Very Strong |
| 🚫 **Common Password Detection** | Flags passwords from the most common/leaked lists |
| 💡 **Actionable Recommendations** | Provides specific suggestions for improvement |
| 🔒 **Security-First Design** | Passwords are never stored or logged |

---

## 🛡️ Security Principles Implemented

### ✅ The Gatekeeper Rule
All input is validated **before** processing.

### ✅ Memory Protection
- Passwords are processed and immediately discarded
- Only masked versions (`********`) appear in reports
- No persistence or logging of sensitive data

### ✅ C++ Best Practices
- RAII for automatic resource management
- Const correctness for data integrity
- Exception handling for robust error management

---

## 📦 Installation

### Prerequisites
- **C++17 compiler** (GCC 7+, Clang 5+, MSVC 2017+)
- No external dependencies

### Compile
```bash
g++ -std=c++17 -O2 -Wall -o password_checker password_checker.cpp
```

### Run
```bash
./password_checker
```

---

## 🚀 Usage

### Interactive Mode
```bash
./password_checker
```

Then:
1. Select option **1** to check a password
2. Enter your password
3. Review the comprehensive report
4. Select option **2** to exit

### Programmatic Usage
```cpp
PasswordStrengthChecker checker;
auto report = checker.analyze("MySecureP@ssw0rd!");
checker.displayReport(report);
```

---

## 📊 How It Works

### The IPO Model

```
┌─────────────┐     ┌──────────────┐     ┌─────────────┐
│   INPUT     │────▶│   PROCESS    │────▶│   OUTPUT    │
│  Password   │     │   Analysis   │     │   Report    │
└─────────────┘     └──────────────┘     └─────────────┘
```

### Entropy Calculation
```
Pool Size = 26 (lowercase) + 26 (uppercase) + 10 (digits) + 33 (specials)
Entropy = Length × log₂(Pool Size)
```

---

## 🖥️ Example Output

```
============================================================
  PASSWORD STRENGTH ANALYSIS REPORT
  Powered by DecodeLabs | Batch 2026
============================================================
  Strength Rating:        Strong
  Entropy (bits):         78.54
  Length:                 14
  Criteria Met:           4/4
------------------------------------------------------------
  CHARACTER DIVERSITY:
    - Lowercase:           ✓
    - Uppercase:           ✓
    - Digits:              ✓
    - Special Characters:  ✓
------------------------------------------------------------
  RECOMMENDATIONS:
    - Password meets all recommended criteria.
============================================================
  Note: Your actual password was not stored or logged.
============================================================
```

---

## 📁 Project Structure

```
password-strength-checker/
│
├── password_checker.cpp        # Main application
├── README.md                  # This file
└── LICENSE                    # MIT License
```

---

## 🛠️ Technologies Used

| Technology | Purpose |
|------------|---------|
| **C++17** | Core programming language |
| **STL** | Standard Template Library |
| **Git** | Version control |

---

## 🤝 Contributing

1. **Fork** the repository
2. **Create** a feature branch: `git checkout -b feature/amazing-feature`
3. **Commit** changes: `git commit -m 'Add amazing feature'`
4. **Push** to branch: `git push origin feature/amazing-feature`
5. **Open** a Pull Request

## 🙏 Acknowledgments

- **DecodeLabs** - For providing the training framework

**🌟 Star this repository if you found it helpful!**
