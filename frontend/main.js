const { client, Empty } = require("./grpcClient.js");

// Get UI elements
const listingsContainer = document.getElementById("listings");
const minPriceInput = document.getElementById("minPrice");
const maxPriceInput = document.getElementById("maxPrice");
const locationInput = document.getElementById("location");
const searchButton = document.getElementById("searchButton");

// Function to render a property listing
function renderProperty(property) {
    const card = document.createElement("div");
    card.classList.add("property-card");
    card.innerHTML = `
        <h3>${property.city}, ${property.state}</h3>
        <p>Price: $${property.price.toLocaleString()}</p>
        <p>${property.bed} Beds | ${property.bath} Baths</p>
        <p>Size: ${property.houseSize} sq ft</p>
    `;
    listingsContainer.appendChild(card);
}

// Function to fetch properties from the gRPC stream
function fetchProperties() {
    listingsContainer.innerHTML = ""; // Clear old listings
    const request = new Empty();

    const stream = client.streamPropertyListings(request, {});

    stream.on("data", (response) => {
        const property = response.toObject();

        // Apply filters
        const minPrice = parseInt(minPriceInput.value) || 0;
        const maxPrice = parseInt(maxPriceInput.value) || Infinity;
        const location = locationInput.value.toLowerCase();

        if (
            property.price >= minPrice &&
            property.price <= maxPrice &&
            (location === "" || property.city.toLowerCase().includes(location) || property.state.toLowerCase().includes(location))
        ) {
            renderProperty(property);
        }
    });

    stream.on("error", (err) => {
        console.error("gRPC Error:", err);
    });
}

// Run search when button is clicked
searchButton.addEventListener("click", fetchProperties);