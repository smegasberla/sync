$InstallDir = "$env:LOCALAPPDATA\Programs\FolderSync"
$Target = "$InstallDir\sync_tool.exe"if (Test-Path $Target) {
Remove-Item -Path $Target -Force
Write-Host "Removed sync binary." -ForegroundColor Green
} else {
Write-Host "sync binary not found." -ForegroundColor Yellow
}if (Test-Path $InstallDir) {
Remove-Item -Path $InstallDir -Recurse -Force
}Remove directory from User PATH$UserPath = [Environment]::GetEnvironmentVariable("Path", "User")
if ($UserPath -like "$InstallDir") {
$NewPath = ($UserPath -split ';' | Where-Object { $_ -ne$InstallDir }) -join ';'
[Environment]::SetEnvironmentVariable("Path", $NewPath, "User")
Write-Host "Removed installation directory from User PATH." -ForegroundColor Yellow
}Write-Host "Folder Sync Tool successfully uninstalled." -ForegroundColor Green