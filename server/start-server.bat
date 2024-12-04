@echo off
:: Check if Node.js is installed
where node > nul 2> nul
if %errorlevel% neq 0 (
    echo Node.js is not installed. Please install Node.js from https://nodejs.org/.
    pause
    exit /b
)

:: Check if npm is available
where npm > nul 2> nul
if %errorlevel% neq 0 (
    echo npm is not installed. Please install Node.js (which includes npm) from https://nodejs.org/.
    pause
    exit /b
)

:: Install dependencies if they are missing
if not exist "node_modules" (
    echo Installing dependencies...
    npm install
    if %errorlevel% neq 0 (
        echo npm install failed. Please ensure your environment is set up correctly.
        pause
        exit /b
    )
)

:: Start the server using npm start (which uses the start script in package.json)
npm start

:: Wait for the server to start (optional)
timeout /t 5

:: Open the index.html file in the default web browser
start http://localhost:3000/index.html

echo Server is running at http://localhost:3000/index.html
pause
