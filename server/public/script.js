document.addEventListener('DOMContentLoaded', () => {
    const ctx = document.getElementById('myChart').getContext('2d');

    // Fetch the JSON data from the server
    fetch('/chartData.json')  // This path is relative to the server root
        .then(response => {
            if (!response.ok) {
                throw new Error('Failed to load JSON file');
            }
            return response.json(); // Parse the JSON data
        })
        .then(jsonData => {
            console.log('JSON Data:', jsonData); // Log the JSON data to the console

            // Initialize the chart with the JSON data
            new Chart(ctx, {
                type: 'line',
                data: {
                    labels: ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December'],
                    datasets: [{
                        label: 'Air Quality',
                        data: jsonData,  // Use the data from the JSON file
                        borderColor: 'rgba(75, 192, 192, 1)',
                        borderWidth: 2
                    }]
                },
                options: {
                    responsive: true,
                }
            });
        })
        .catch(error => {
            console.error('Error fetching JSON data:', error);
        });
});
