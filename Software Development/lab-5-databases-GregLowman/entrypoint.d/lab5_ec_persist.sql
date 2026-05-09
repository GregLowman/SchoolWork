/* Create tables for calendar events based on the HTML event form fields */
CREATE TABLE events (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    category VARCHAR(50) NOT NULL,
    weekday VARCHAR(15) NOT NULL,
    time TIME NOT NULL,
    modality VARCHAR(20) NOT NULL,
    location VARCHAR(150),
    remote_url TEXT
);

CREATE TABLE attendees (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL
);

CREATE TABLE events_to_attendees (
    event_id INT,
    attendee_id INT
);


/* Add constraints to keep data clean and relational */
ALTER TABLE events
ADD CONSTRAINT modality_check CHECK (
    (modality = 'in-person' AND location IS NOT NULL AND remote_url IS NULL)
    OR
    (modality = 'remote' AND remote_url IS NOT NULL AND location IS NULL)
);

ALTER TABLE events_to_attendees
ADD CONSTRAINT fk_event_id FOREIGN KEY (event_id) REFERENCES events(id) ON DELETE CASCADE;

ALTER TABLE events_to_attendees
ADD CONSTRAINT fk_attendee_id FOREIGN KEY (attendee_id) REFERENCES attendees(id) ON DELETE CASCADE;

ALTER TABLE events_to_attendees
ADD CONSTRAINT pk_events_to_attendees PRIMARY KEY (event_id, attendee_id);


/*
    CREATE TABLE
    CREATE TABLE
    CREATE TABLE
    ALTER TABLE
    ALTER TABLE
    ALTER TABLE
    ALTER TABLE
*/
