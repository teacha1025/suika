Get-ChildItem E:\programing\suika -Recurse -Include *.h | Rename-Item -NewName {$_.FullName + ".bkup"}

Get-ChildItem E:\programing\suika -Recurse -Include *.h.bkup | ForEach-Object {Get-Content $_.FullName | Out-File -Encoding utf8-no-bom ($_.FullName -replace '.h.bkup','.h')}

Get-ChildItem E:\programing\suika -Recurse -Include *.h.bkup | Remove-Item