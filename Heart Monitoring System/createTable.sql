CREATE TABLE patient_health_data (
    id SERIAL PRIMARY KEY,       -- Auto-incrementing primary key
    name VARCHAR(100),           -- Name of the person
    gender VARCHAR(10),          -- Gender of the person
    ageGroup VARCHAR(50),        -- Age group (e.g., "child", "adult", etc.)
    exactAge VARCHAR(10),        -- Exact age (as a string, e.g., "25")
    heartRate VARCHAR(10),       -- Heart rate (as a string, e.g., "72 bpm")
    bloodPressure1 VARCHAR(10),  -- Systolic blood pressure (as a string, e.g., "120 mmHg")
    bloodPressure2 VARCHAR(10),  -- Diastolic blood pressure (as a string, e.g., "80 mmHg")
    temperature VARCHAR(10)      -- Temperature (as a string, e.g., "36.6°C")
);

CREATE TABLE patient_health_data (
    id SERIAL PRIMARY KEY,
    name VARCHAR(50),
    gender VARCHAR(50),
    ageGroup VARCHAR(50),
    exactAge VARCHAR,
    heartRate INTEGER,
    bloodPressure1 INTEGER,
    bloodPressure2 INTEGER,
    temperature DOUBLE PRECISION
);

DROP TABLE patient_health_data;

SELECT * FROM patient_health_data;

SELECT id FROM patient_health_data WHERE NAME = 'Tina';

SELECT id FROM patient_health_data WHERE id > $1 ORDER BY id ASC LIMIT 1;