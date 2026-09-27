Write-Host "Building Folder Sync" -ForegroundColor Cyan

Check for g++ or cl compiler

if (Get-Command g++ -ErrorAction SilentlyContinue) {
g++ -std=c++17 -O2 src/main.cpp -o sync.exe
} elseif (Get-Command cl -ErrorAction SilentlyContinue) {
cl /EHsc /std:c++17 src/main.cpp /Fe:sync.exe
} else {
Write-Host "Error: No suitable C++ compiler (g++ or cl) found in PATH." -ForegroundColor Red
exit 1
}

$InstallDir = "$env:LOCALAPPDATA\Programs\FolderSync"

if (-not (Test-Path $InstallDir)) {
New-Item -ItemType Directory -Path $InstallDir | Out-Null
}

Move-Item -Path "sync.exe" -Destination "$InstallDir\sync.exe" -Force

$UserPath = [Environment]::GetEnvironmentVariable("Path", "User")
if ($UserPath -notlike "$InstallDir") {
[Environment]::SetEnvironmentVariable("Path", "$UserPath;$InstallDir", "User")
Write-Host "Added $InstallDir to your User PATH." -ForegroundColor Yellow
}

Write-Host "Installation complete! Please restart your terminal to use 'sync_tool'." -ForegroundColor Green