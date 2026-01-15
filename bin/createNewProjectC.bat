@echo off
setlocal

REM Überprüfen, ob ein Argument übergeben wurde (Projektname)
if "%1"=="" (
    REM Falls kein Argument übergeben wurde, den Benutzer zur Eingabe auffordern
    set /p project_name="Bitte geben Sie einen C Projektnamen ein: "
) else (
    REM Projektname aus dem Argument übernehmen
    set "project_name=%2"
)

REM Für ASM-Projekt
echo Erstelle C-Projekt mit dem Namen: %project_name%
REM Aufruf des PowerShell-Skripts
powershell -ExecutionPolicy Bypass -File createGenericProject.ps1 --c %project_name%

REM Beende das Skript
exit /b 0