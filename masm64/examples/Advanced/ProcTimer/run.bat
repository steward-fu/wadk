@echo off

@echo.
@echo     pTimer.exe is designed to time a process that you start that runs and finishes by itself.
@echo.
@echo     It is suitable to time running application that have durations from seconds to minutes.
@echo.
@echo     Close pTimer when the demo has run.
@echo.
@echo     Press any key to start demo.
@echo.

pause > nul

cmd.exe /c pTimer.exe TimerTest.exe