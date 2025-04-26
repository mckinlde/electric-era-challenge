---

# Electric Era Coding Challenge Submission

## Project Overview

This project solves the Electric Era charger uptime calculation challenge.  
It is implemented in C++ with a flake-based Nix development environment for reproducibility and portability.

The program:
- Parses a structured input file describing station-to-charger mappings and charger availability reports
- Tracks per-charger uptime and downtime
- Aggregates charger data to compute per-station uptime
- Outputs station uptimes as integers [0-100] to standard output, sorted by station ID

---

## How to Build and Run

**Requirements:**  
- Linux (amd64 architecture)  
- Nix with flakes enabled

**Building:**

```bash
make
```

**Running:**

```bash
./hello path/to/input.txt
```

Example:

```bash
./hello test_data/input_1.txt
```

---

## Challenge Solution Details

**Input Handling:**
- The program expects a structured input text file.
- `[Stations]` section maps station IDs to charger IDs.
- `[Charger Availability Reports]` section provides time intervals and availability status for each charger.
- Input is strictly validated. Bad input causes `ERROR` to be printed to stdout and the program to exit immediately.

**Per-Charger Tracking:**
- Each `Charger` object stores multiple availability reports (start time, end time, availability).
- Monitoring window is determined **only** between the first report's start time and the last report's end time.
- Gaps between reports are treated as downtime.
- Time outside of first-to-last report is not monitored.

**Station Uptime Calculation:**
- For each station:
  - Uptime is calculated by aggregating available seconds and monitored seconds from all associated chargers.
  - Final uptime is `(available_time / monitored_time) * 100`, rounded down to the nearest integer.
- Stations with no chargers reporting data are treated as 0% uptime.
- Output is sorted by Station ID ascending.

---

## Development Environment

This project uses a reproducible development environment built with Nix flakes:
- GCC toolchain (C++17)
- Automatic environment validation with `nix develop`
- Build reproducibility guaranteed via Git-tracked `flake.nix`
- No external dependencies beyond standard C++ STL

**Benefits:**
- No "works on my machine" problems
- Easy, fast rebuilds across machines
- Ready for CI/CD workflows if extended

---

## File Structure

```text
electric-era-challenge/
├── charger.cpp        # Charger class implementation
├── charger.hpp        # Charger class header
├── main.cpp           # Program entry point
├── makefile           # Build instructions
├── test_data/         # Example input/output files
├── README.md          # This document
├── flake.nix          # Nix flake for reproducible dev environment
└── test.sh            # (Optional) test script
```

---

## Notes on Assumptions

- If a charger has no availability reports, it is not included in uptime calculation.
- Monitoring time starts at the **first observed report** and ends at the **last observed report** per charger.
- Gaps between reports are considered downtime.
- Input is strictly validated per challenge requirements.
- No assumptions are made beyond what is explicitly specified in the prompt.

---

## Compilation and Runtime Example

```bash
make
./hello test_data/input_1.txt
# Outputs:
# 0 100
# 1 0
# 2 75
```

```bash
./hello test_data/input_2.txt
# Outputs:
# 0 66
# 1 100
```

---

✅ Submission package includes full source code, build instructions, and this README.  
✅ Code passes provided Electric Era test cases exactly.

---

# End of README

---

