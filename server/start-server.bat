@echo off
:: Start the Node.js server
start /B node server.js
:: Open the index.html file in the default web browser
start http://localhost:3000/index.html