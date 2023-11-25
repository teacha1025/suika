$sourceFolders = @('bin', 'docs', 'shader', 'include')
$zipFilePath = 'suika.zip'

Remove-Item -Path .\suika.zip -Force

Copy-Item -Path .\bin\suika.lib -Destination .\dist\bin\suika.lib
Copy-Item -Path .\bin\suika_d.lib -Destination .\dist\bin\suika_d.lib
Copy-Item -Path .\docs -Destination .\dist -Recurse -Force
Copy-Item -Path .\include -Destination .\dist -Recurse -Force
Copy-Item -Path .\shader -Destination .\dist -Recurse -Force

Compress-Archive -Path .\dist\* -DestinationPath .\suika.zip