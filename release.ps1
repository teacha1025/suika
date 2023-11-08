$sourceFolders = @('bin', 'docs', 'shader', 'include')
$zipFilePath = 'suika.zip'

Remove-Item -Path $zipFilePath -Force
Compress-Archive -Path $sourceFolders -DestinationPath $zipFilePath
