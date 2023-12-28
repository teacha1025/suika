Get-ChildItem E:\programing\suika -Recurse -Include *.cpp | Rename-Item -NewName {$_.FullName + ".bkup"}

Get-ChildItem E:\programing\suika -Recurse -Include *.cpp.bkup | ForEach-Object {Get-Content $_.FullName | Out-File -Encoding utf8BOM ($_.FullName -replace '.cpp.bkup','.cpp')}

Get-ChildItem E:\programing\suika -Recurse -Include *.cpp.bkup | Remove-Item