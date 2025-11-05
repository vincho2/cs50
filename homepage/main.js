// Sends an alert when message is submitted
document.addEventListener('DOMContentLoaded', function() {

    // Define the areas of the html
    const textarea = document.querySelector('#message');
    const remaining = document.querySelector('#remainingCharCount');

    // Get the maximum allowed characters from max length
    const max = parseInt(textarea.getAttribute('maxlength'));
    remaining.innerHTML = max;

    // Display the remaining number of characters for the message typed
    textarea.addEventListener('keyup', function(event) {
        remaining.innerHTML = max - textarea.value.length;
    });

    // Get the form inside the contact section
    const form = document.querySelector('#contact form');

    if (form) {
        form.addEventListener('submit', function(event) {
            // Prevent default submit
            event.preventDefault();

            // Get fields values
            const firstName = document.querySelector('#firstName').value;
            const lastName = document.querySelector('#lastName').value;
            const email = document.querySelector('#inputEmail').value;
            const message = document.querySelector('#message').value;

            // Display values on the console
            console.log('Form submitted:', { firstName, lastName, email, message });

            // Send an alert
            alert('Thank you ' + firstName + ', message sent !');
        });
    }
});
