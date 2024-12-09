$today = Get-Date # -Date "2023-12-01"

$dayInt = $today.Day
$yearInt = $today.Year

$i = 1;
while ($i -le $dayInt) {    

    $day = '{0:d2}' -f $i
    if (!(Test-Path -Path $day -PathType Container)) {
        New-Item -ItemType Directory -Path $day
        Copy-Item -Recurse .\template\* $day
    
        $session = Get-Content -Path "session.txt"
        Invoke-WebRequest -Uri "https://adventofcode.com/$yearInt/day/$i/input" -OutFile $day\input.txt -Headers @{"Cookie" = "session=$session" }
    
        git add $day
    
    }

    $i = $i + 1
}
code .