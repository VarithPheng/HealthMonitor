CREATE TABLE patient_health_data (
    id SERIAL PRIMARY KEY,
    name VARCHAR(50),
    gender VARCHAR(50),
    ageGroup VARCHAR(50),
    exactAge VARCHAR(20),
    heartRate INTEGER,
    bloodPressure1 INTEGER,
    bloodPressure2 INTEGER,
    temperature DOUBLE PRECISION
);