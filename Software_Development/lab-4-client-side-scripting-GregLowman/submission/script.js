document.addEventListener("DOMContentLoaded", () => {
  // --- Weekday dropdown: keep selected value on the button ---
  const weekdayBtn = document.getElementById("weekday_dropdown");
  const weekdayMenu = document.getElementById("event_weekday");
  const categoryBtn = document.getElementById("category_dropdown");
  const categoryMenu = document.getElementById("event_category");
  const removeBtn = document.createElement("button");
  removeBtn.type="button";
  removeBtn.className = "btn btn-sm bt-outline-danger mt-2";
  removeBtn.textContent = "Remove";



  if (weekdayBtn && weekdayMenu) {
    weekdayMenu.addEventListener("click", (e) => {
      const item = e.target.closest(".dropdown-item");
      if (!item) return;
      e.preventDefault();

      weekdayBtn.textContent = item.textContent.trim();
      weekdayBtn.dataset.value = item.textContent.trim(); // store selection
    });
  }

  if(categoryBtn &&categoryMenu) {
    categoryMenu.addEventListener("click", (e) => {
        const value = e.target.closest(".dropdown-item");
        if(!value) return;
        e.preventDefault();

        categoryBtn.textContent = value.textContent.trim();
        categoryBtn.dataset.value = value.textContent.trim();
    })
  }

  // --- Modality select: show/hide fields based on appointment type ---
  const modalitySelect = document.getElementById("event_modality");
  const inPersonFields = document.getElementById("inPersonFields");
  const remoteFields = document.getElementById("remoteFields");
  const locationInput = document.getElementById("event_location");
  const remoteUrlInput = document.getElementById("event_remote_url");

  function updateLocationOptions(value) {
    if (!inPersonFields || !remoteFields) return;

    if (value === "in-person") {
      inPersonFields.classList.remove("d-none");
      remoteFields.classList.add("d-none");
      if (locationInput) locationInput.required = true;
      if (remoteUrlInput) remoteUrlInput.required = false;
    } else if (value === "remote") {
      remoteFields.classList.remove("d-none");
      inPersonFields.classList.add("d-none");
      if (remoteUrlInput) remoteUrlInput.required = true;
      if (locationInput) locationInput.required = false;
    }
  }

  if (modalitySelect) {
    updateLocationOptions(modalitySelect.value);
    modalitySelect.addEventListener("change", (e) => updateLocationOptions(e.target.value));
  }

  // --- Save event and add to calendar ---
  const form = document.getElementById("event_form");

  function getDayId() {
    if (!weekdayBtn) return null;
    const day = (weekdayBtn.dataset.value || weekdayBtn.textContent || "").trim().toLowerCase();
    const valid = ["sunday","monday","tuesday","wednesday","thursday","friday","saturday"];
    return valid.includes(day) ? day : null;
  }

  if (!form) return;

  form.addEventListener("submit", (e) => {

    e.preventDefault();

    const dayId = getDayId();
    if (!dayId) {
      alert("Select a weekday.");
      return;
    }

    const name = document.getElementById("event_name").value.trim();
    const category = categoryBtn.dataset.value;
    const time = document.getElementById("event_time").value;
    const modality = document.getElementById("event_modality").value;

    const location = document.getElementById("event_location")?.value.trim() || "";
    const url = document.getElementById("event_remote_url")?.value.trim() || "";
    const attendees = document.getElementById("event_attendees")?.value.trim() || "";

    if (!name || !time) return;
    if (modality === "in-person" && !location) return;
    if (modality === "remote" && !url) return;

    const dayCol = document.getElementById(dayId);

    const eventEl = document.createElement("div");
    eventEl.dataset.name=name;
    eventEl.dataset.time = time;
    eventEl.dataset.category = category;
    eventEl.dataset.modality = modality;
    eventEl.dataset.location = location;
    eventEl.dataset.url = url;
    eventEl.dataset.attendees=attendees;
    eventEl.dataset.dayId = dayId;

    eventEl.className = "border rounded p-2 my-2";


    eventEl.style.cursor = "pointer";
    eventEl.style.pointerEvents = "auto";
    eventEl.style.zIndex = "9999";


    eventEl.addEventListener("click", (e) => {

        document.getElementById("event_name").value = eventEl.dataset.name || "";
        document.getElementById("event_time").value = eventEl.dataset.time || "";
        document.getElementById("event_category").value = eventEl.dataset.category || "";
        document.getElementById("event_modality").value = eventEl.dataset.modality || "";
        document.getElementById("event_location").value = eventEl.dataset.location || "";
        document.getElementById("event_remote_url").value = eventEl.dataset.url || "";
        document.getElementById("event_attendees").value = eventEl.dataset.attendees || "";

        const modalEl = document.getElementById("event_modal"); // <-- use your actual modal ID
        const modal = bootstrap.Modal.getOrCreateInstance(modalEl);
        modal.show();

    })


    //REMOVE BUTTON

    removeBtn.addEventListener("click",(e) => {
    e.stopPropagation();
    eventEl.remove()
    })

    eventEl.appendChild(removeBtn);

    
    // Title
    const title = document.createElement("div");
    title.className = "fw-bold";
    title.textContent = name;
    eventEl.appendChild(title);

    // Time
    const timeEl = document.createElement("div");
    timeEl.textContent = `Time: ${time}`;
    eventEl.appendChild(timeEl);

    // Modality
    const modalityEl = document.createElement("div");
    modalityEl.textContent = `Type: ${modality === "remote" ? "Remote" : "In Person"}`;
    eventEl.appendChild(modalityEl);


    // Conditional fields
    if (modality === "in-person") {
      const locEl = document.createElement("div");
      locEl.textContent = `Location: ${location}`;
      eventEl.appendChild(locEl);
    } else {
      const urlEl = document.createElement("div");
      urlEl.textContent = `URL: ${url}`;
      eventEl.appendChild(urlEl);
    }

    // Attendees
    if (attendees) {
      const attEl = document.createElement("div");
      attEl.textContent = `Attendees: ${attendees}`;
      eventEl.appendChild(attEl);
    }


    switch(category){
        case("Athletic"):
            eventEl.style.backgroundColor = "blue";
            break;

        case("Concert"):
            eventEl.style.backgroundColor = "red";
            break;
        
        case("Birthday"):
            eventEl.style.backgroundColor = "yellow";
            break;

        case("Anniversary"):
            eventEl.style.backgroundColor = "green";
            break;

        case("Project"):
            eventEl.style.backgroundColor = "orange";
            break;
    }

    dayCol.appendChild(eventEl);



  });
});
