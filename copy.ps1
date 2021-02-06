$drives = Get-Volume
foreach ($drive in $drives) {
	if ($drive.FileSystemLabel -eq "RPI-RP2") {
		copy-item "*.uf2" $drive.path
		write-host "Copied."
	}
}