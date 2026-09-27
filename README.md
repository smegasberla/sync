# Folder Sync Tool

A lightweight, high-performance command-line utility written in modern C++ (`C++17`) designed to synchronize files between two directories efficiently.

Instead of re-copying every file during every sync run, this tool inspects the destination directory, compares file metadata, and only transfers files that are missing or modified.

---

## How It Works

1. **Validation**: The tool ensures the source directory exists and contains data before proceeding.
2. **Directory Traversal**: It recursively walks through all subdirectories in the source folder using `<filesystem>`.
3. **Smart Comparison**: For every entry encountered, it compares destination presence and file size.
4. **Targeted Transfer**:
   - If a file exists in the destination and matches the source size, it is flagged as **Up To Date** and skipped.
   - If a file is missing or has a modified size, the tool automatically constructs any missing parent subdirectories and copies/overwrites the target file.
5. **Execution Summary**: Outputs total files scanned, copied files count, and up-to-date files count.

---

## Prerequisites

To build the tool from source, ensure you have a C++ compiler supporting **C++17** or higher installed on your system:

- **Linux / macOS**: `g++` (GCC 8+) or `clang++` (LLVM 7+)
- **Windows**: `g++` (via MinGW-w64) or `cl` (MSVC via Visual Studio Build Tools)

---

## Installation

### 1. Clone the Repository

```bash
git clone https://github.com/smegasberla/sync.git
cd folder-sync-tool
```

### 2. Run the Installer

#### On Linux / macOS
Grant execution permissions and run `install.sh`:

```bash
chmod +x install.sh uninstall.sh
./install.sh
```

#### On Windows (PowerShell)
Run `install.ps1`:

```powershell
.\install.ps1
```

> **Note:** On Windows, you may need to adjust execution permissions if script running is disabled (`Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass`).

---

## Usage

Run the `sync_tool` executable from any terminal session by passing the path to the source folder and the destination folder:

```bash
sync <path/to/source> <path/to/destination>
```

### Example

```bash
sync ~/Documents/Projects /Volumes/BackupDrive/Projects
```

**Output:**
```text
Total Files: 128
Copied Files: 3
Up To Date Files: 125
Copy is successful!
```

---

## Uninstallation

If you wish to remove the tool and its binaries from your system PATH:

- **Linux / macOS**: Run `./uninstall.sh`
- **Windows**: Run `.\uninstall.ps1`

---

## License

This project is licensed under the MIT License. Feel free to modify and distribute as needed.