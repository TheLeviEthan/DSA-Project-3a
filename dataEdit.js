// Purpose: This file is used to toggle between the insert and delete sections of the data edit page
//React MUI
//API QUESTIOn Discord

// import * as React from 'react';
// import Box from '@mui/material/Box';
// import Alert from '@mui/material/Alert';
// import IconButton from '@mui/material/IconButton';
// import Collapse from '@mui/material/Collapse';
// import Button from '@mui/material/Button';
// import CloseIcon from '@mui/icons-material/Close';




document.addEventListener('DOMContentLoaded',()=>{ 
    //buttons and sections
    const toggleInsert = document.getElementById('insertToggle');
    const toggleDelete = document.getElementById('deleteToggle');
    const insertButton = document.getElementById('insert');
    const deleteButton = document.getElementById('delete');
    const inputSect = document.getElementById('inputSection');
    

    //Debug
    console.log(toggleInsert, toggleDelete);

    //Functions
    function changeEdit(toggle1, toggle2, button1, button2){
        //toggles
        toggle1.classList.add('active');
        toggle2.classList.remove('active');
        //buttons
        button1.classList.remove('hidden');
        button2.classList.add('hidden');
    }

    //Event
    toggleInsert.addEventListener('click',()=>{
        changeEdit(toggleInsert, toggleDelete, insertButton, deleteButton);
        inputSect.classList.add('dataInputSection');
    });
    toggleDelete.addEventListener('click',()=>{
        changeEdit(toggleDelete, toggleInsert, deleteButton, insertButton);
        inputSect.classList.add('dataInputSection');
    });

});