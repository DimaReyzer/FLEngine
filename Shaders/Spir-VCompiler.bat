@echo off
setlocal

:: Create the Spir-V directory if it doesn't exist
if not exist "Spir-V" mkdir "Spir-V"

rem Clear the Spir-V folder
del /q "Spir-V\*.spv"

:: Compile each .glsl file in the current directory
for %%f in (*.frag *.vert) do (
    echo Compiling %%f...
    glslangValidator -V %%f -o "Spir-V/%%~nf%%~xf.spv"
)

echo Compilation complete.
pause
