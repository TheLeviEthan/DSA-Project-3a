document.addEventListener('DOMContentLoaded', () => {
    const insertButton = document.getElementById('search');

    // Fetch and initialize the chart
    let myChart = null;

    const fetchChartData = async () => {
        try {
            const response = await fetch('/path/to/chartData.json');
            if (response.ok) {
                const data = await response.json();

                // Format the data into Chart.js format
                const labels = data.map(item => item.date);
                const aqiData = data.map(item => item.aqi);

                // Create or update the chart
                if (!myChart) {
                    const ctx = document.getElementById('myChart').getContext('2d');
                    myChart = new Chart(ctx, {
                        type: 'line',
                        data: {
                            labels: labels,
                            datasets: [{
                                label: 'Air Quality Index (AQI)',
                                data: aqiData,
                                borderColor: 'rgba(75, 192, 192, 1)',
                                backgroundColor: 'rgba(75, 192, 192, 0.2)',
                                fill: true,
                            }],
                        },
                        options: {
                            responsive: true,
                            scales: {
                                y: {
                                    beginAtZero: true,
                                    ticks: {
                                        stepSize: 10,
                                    },
                                },
                            },
                        },
                    });
                } else {
                    myChart.data.labels = labels;
                    myChart.data.datasets[0].data = aqiData;
                    myChart.update();
                }
            } else {
                console.error('Failed to load chart data');
            }
        } catch (error) {
            console.error('Error fetching chart data:', error);
        }
    };

    // Fetch chart data when the page loads
    fetchChartData();

    insertButton.addEventListener('click', async (event) => {
        event.preventDefault(); // Prevent form from reloading the page

        // Get user inputs
        const stateInput = document.getElementById('state').value.trim();
        const countyInput = document.getElementById('county').value.trim();

        if (!stateInput || !countyInput) {
            alert("Please enter both State and County.");
            return;
        }

        // Send data to the backend
        try {
            const response = await fetch('/api/store-input', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({ state: stateInput, county: countyInput }),
            });

            if (response.ok) {
                alert("Input successfully stored!");
                // After storing, update the chart with new data
                fetchChartData();  // Re-fetch the chart data to update the graph
            } else {
                const error = await response.json();
                alert(`Failed to store input: ${error.message}`);
            }
        } catch (error) {
            console.error('Error sending data:', error);
            alert('An error occurred while sending the data.');
        }
    });
});
