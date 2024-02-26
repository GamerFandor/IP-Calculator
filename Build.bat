@ECHO OFF
SetLocal EnableDelayedExpansion

:: Collect every source file
set Source=
for /R %%f in (*.cpp) do call set Source=%%Source%% %%f

:: Make 'Binary' folder if it does not exist
if not exist Binary mkdir Binary

:: Compile the files
clang++ %Source% -o Binary/ip-calculator.exe -ISource

:: If there are errors then print it to the screen and exit the program
if %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

:: Print a success text
echo Binary files successfully created!