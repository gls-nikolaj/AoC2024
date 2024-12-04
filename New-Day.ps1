$today = Get-Date # -Date "2023-12-01"

$day = ($today).ToString("dd")
$dayInt = $today.Day
$yearInt = $today.Year

if(!(Test-Path -Path $day -PathType Container)) {
    New-Item -ItemType Directory -Path $day
    Copy-Item -Recurse .\template\* $day

    $session = Get-Content -Path "session.txt"
    Invoke-WebRequest -Uri "https://adventofcode.com/$yearInt/day/$dayInt/input" -OutFile $day\input.txt -Headers @{"Cookie" = "session=$session"}

    git add $day

}
code .