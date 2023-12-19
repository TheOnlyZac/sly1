const express = require('express');
const app = express();

const PORT = 3000;

app.use(express.static('html'));

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/html/index.html');
});

app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});
