# Define installation paths
$InstallDir = "$env:LOCALAPPDATA\Programs\FSync"
$Target     = "$InstallDir\fsync.exe"

# Remove the binary file if present
if (Test-Path $Target) {
    Remove-Item -Path $Target -Force
    Write-Host "Removed fsync binary." -ForegroundColor Green
} else {
    Write-Host "fsync binary not found." -ForegroundColor Yellow
}

# Remove the installation folder
if (Test-Path $InstallDir) {
    Remove-Item -Path $InstallDir -Recurse -Force
    Write-Host "Removed installation directory." -ForegroundColor Green
}

# Remove directory from User PATH environment variable
$UserPath = [Environment]::GetEnvironmentVariable("Path", "User")
if ($UserPath -like "*$InstallDir*") {
    $NewPath = ($UserPath -split ';' | Where-Object { $_ -ne $InstallDir }) -join ';'
    [Environment]::SetEnvironmentVariable("Path", $NewPath, "User")
    Write-Host "Removed installation directory from User PATH." -ForegroundColor Yellow
}

Write-Host "Folder Sync Tool successfully uninstalled." -ForegroundColor Green