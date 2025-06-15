@echo off
setlocal

:: 参数解析
set ARG=%1

:: 默认路径（根据你的结构修改）
set SHADER_DIR=shaders
set BUILD_DIR=build
set VERT_SHADER=%SHADER_DIR%\vert.glsl
set FRAG_SHADER=%SHADER_DIR%\frag.glsl
set VERT_SPV=%SHADER_DIR%\vert.spv
set FRAG_SPV=%SHADER_DIR%\frag.spv
set EXE=%BUILD_DIR%\glfw_demo.exe

:: 选择操作
if "%ARG%"=="shader" (
    echo Compiling shaders...
    glslc -fshader-stage=vert %VERT_SHADER% -o %VERT_SPV%
    glslc -fshader-stage=frag %FRAG_SHADER% -o %FRAG_SPV%
    goto :done
)

if "%ARG%"=="build" (
    echo Building application...
    cmake -S . -B %BUILD_DIR% -G "MinGW Makefiles"
    cmake --build %BUILD_DIR%
    goto :done
)

if "%ARG%"=="run" (
    echo Running application...
    %EXE%
    goto :done
)

if "%ARG%"=="all" (
    echo === Compiling shaders...
    glslc -fshader-stage=vert %VERT_SHADER% -o %VERT_SPV%
    glslc -fshader-stage=frag %FRAG_SHADER% -o %FRAG_SPV%

    echo === Building application...
    cmake -S . -B %BUILD_DIR% -G "MinGW Makefiles"
    cmake --build %BUILD_DIR%

    echo === Running application...
    %EXE%
    goto :done
)

echo Usage: run.bat [shader | build | run | all]

:done
endlocal
