param(
    [string] $ZipName
)

$ErrorActionPreference = "Stop"

# get full download path
$downloadpath = Join-Path -Path $HOME -ChildPath "downloads"
$zip = Join-Path -Path $downloadpath -ChildPath $ZipName


# get full destination path
$destinationName = Split-Path $ZipName -Leaf
$destinationName = $destinationName.Replace(".zip", "")
$destination = [System.IO.Path]::Combine(
    $PSScriptRoot,
    "..",
    "py_v",
    "data",
    $destinationName
)

Write-Host "Resolved download path: '$zip'." 
Write-Host "Resolved destination path: '$destination'."

Expand-Archive $zip -DestinationPath $destination