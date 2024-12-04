const express = require('express');
const path = require('path');
const app = express();
const port = 3000;

// Serve static files (HTML, CSS, JS, and JSON)
app.use(express.static(path.join(__dirname, 'public')));

// Start the server
app.listen(port, '0.0.0.0', () => {
    console.log(`Server running at http://localhost:${port}`);
});
