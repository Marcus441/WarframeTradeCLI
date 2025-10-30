# WarframeTradeCLI

A command-line tool to query [warframe.market](https://warframe.market/) with
optional terminal UI, live updates, and OCR support for scanning in-game item
feeds. Ideal for Warframe players who want fast, real-time market insights for
fissures, without having an annoying and bloated overlay.

## Features

- Query Warframe items and market orders from warframe.market.
- Optional **interactive terminal UI** with:
  - Auto-refreshing watchlists **TODO**
  - Colored charts and price trends **TODO**
  - Platform-specific filtering (PC, PS4, Xbox, Switch)
- Optional **OCR support** to scan Warframe game windows and update item feeds
  in real-time. **TODO**
- Configurable via command-line arguments:
  - `--search` / `-s` to query items
  - `--orders` / `-o` to fetch specific orders
  - `--platforms=` to specify platform filters
  - `--version` / `-v` to display the CLI version

## Dependencies

<!-- markdownlint-disable MD013 -->

| Dependency    | Purpose          | Platform | Notes                                                   |
| ------------- | ---------------- | -------- | ------------------------------------------------------- |
| CMake, Nix    | Build system     | ✅ All   | Portable and cross-platform                             |
| FTXUI         | Terminal UI      | ✅ All   | Reactive UI with automatic updates for watched items    |
| Tesseract OCR | Text recognition | ✅ All   | Requires ~50MB training data; for optional OCR features |
| cpr           | HTTP requests    | ✅ All   | Simplifies network queries                              |
| nlohmann/json | JSON parsing     | ✅ All   | Modern and easy-to-use JSON handling                    |

<!-- markdownlint-enable MD013 -->

## Installation

```bash
# Clone the repository
git clone https://github.com/YourUsername/WarframeTradeCLI.git
cd WarframeTradeCLI

# Build with CMake & Nix
nix build .#wftcli
```

## Usage

```bash
# Search for an item
./wftcli --search "rubico_prime"

# Fetch orders for a specific item on PC and Xbox
./wftcli --orders "rubico_prime_set" --platforms=pc,xbox
```
