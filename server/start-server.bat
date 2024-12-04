@echo off

:: Check if Node.js is installed by using the 'where' command
where node > nul 2> nul
if %errorlevel% neq 0 (
    echo Node.js is not installed. Please install Node.js from https://nodejs.org/.
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
start /B npm start

:: Wait for the server to fully start (10 seconds)
timeout /t 10

:: Check if the server is running by testing the port
:: This waits for the server to be accessible at localhost:3000 before proceeding
echo Checking if server is running at http://localhost:3000
curl -s http://localhost:3000 > nul
if %errorlevel% neq 0 (
    echo Server failed to start. Please check the server logs.
    pause
    exit /b
)

:: After the server is up, open the index.html file in the default web browser
start http://localhost:3000/index.html

echo Server is running at http://localhost:3000/index.html
pause
