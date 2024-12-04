document.addEventListener('DOMContentLoaded', () => {
    // Debug Elements
    const toggleInsert = document.getElementById('insertToggle');
    const toggleDelete = document.getElementById('deleteToggle');
    const insertButton = document.getElementById('insert');
    const deleteButton = document.getElementById('delete');
    const inputSect = document.getElementById('inputSection');

    // Ensure elements exist before adding listeners
    if (!toggleInsert || !toggleDelete || !insertButton || !deleteButton || !inputSect) {
        console.error('One or more elements are missing');
        return;
    }

    // Functions
    function changeEdit(toggle1, toggle2, button1, button2) {
        toggle1.classList.add('active');
        toggle2.classList.remove('active');
        button1.classList.remove('hidden');
        button2.classList.add('hidden');
        //clears values in input fields
        document.getElementById("state").value = "";
        document.getElementById("county").value = "";
        document.getElementById("date").value = "";
        document.getElementById("aqi").value = "";

    }

    // Events
    toggleInsert.addEventListener('click', () => {
        changeEdit(toggleInsert, toggleDelete, insertButton, deleteButton);
        inputSect.classList.add('dataInputSection');
    });
    toggleDelete.addEventListener('click', () => {
        changeEdit(toggleDelete, toggleInsert, deleteButton, insertButton);
        inputSect.classList.add('dataInputSection');
    });
});

const myObject = {name: "John", age: 20};

const jsonString = JSON.stringify(myObject);
