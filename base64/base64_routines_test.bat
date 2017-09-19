cl /DTEST_BASE64_ROUTINES /Gm /Zi /EHsc /O2 base64_routines_test.cpp

@if %ERRORLEVEL%==0 goto no_error

@exit /b %ERRORLEVEL%

:no_error

@REM @del base64_routines_test.obj

@echo ---
@echo Runing tests...
@base64_routines_test.exe
@echo Done
