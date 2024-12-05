const express = require('express');
const fs = require('fs');
const path = require('path');

const app = express();
const port = 3000;

app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

app.post('/api/store-input', (req, res) => {
    const { state, county } = req.body;

    console.log('Received input:', req.body); // Debugging

    if (!state || !county) {
        return res.status(400).json({ message: 'State and County are required.' });
    }

    const data = { state, county };
    const filePath = path.join(__dirname, 'public', 'webInputs.json');

    if (!fs.existsSync(filePath)) {
        fs.writeFileSync(filePath, '{}', 'utf8'); // Create empty JSON file if missing
    }

    fs.writeFile(filePath, JSON.stringify(data, null, 2), 'utf8', (err) => {
        if (err) {
            console.error('Error writing to webInputs.json:', err);
            return res.status(500).json({ message: 'Failed to write data to file.' });
        }

        console.log('Data successfully written to webInputs.json');
        res.status(200).json({ message: 'Data successfully stored.' });
    });
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
