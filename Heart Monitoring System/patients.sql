-- Create the patients table
CREATE TABLE patients (
    patient_id SERIAL PRIMARY KEY,
    name VARCHAR(100),
    gender VARCHAR(10),
    age INTEGER,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Create the vital_signs table
CREATE TABLE vital_signs (
    record_id SERIAL PRIMARY KEY,
    patient_id INTEGER REFERENCES patients(patient_id),
    recorded_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    heart_rate DOUBLE PRECISION,
    blood_pressure DOUBLE PRECISION,
    temperature DOUBLE PRECISION,
    is_normal BOOLEAN,
    age_group VARCHAR(20)
);

-- Create the abnormal_readings table
CREATE TABLE abnormal_readings (
    abnormal_id SERIAL PRIMARY KEY,
    patient_id INTEGER REFERENCES patients(patient_id),
    record_id INTEGER REFERENCES vital_signs(record_id),
    abnormal_type VARCHAR(50),
    abnormal_value DOUBLE PRECISION,
    abnormal_timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

TRUNCATE patients, vital_signs, abnormal_readings RESTART IDENTITY CASCADE;

-- Create 3 test patients
INSERT INTO patients (name, gender, age, created_at) VALUES
('John Smith', 'Male', 35, NOW()),
('Mary Johnson', 'Female', 42, NOW()),
('Bob Wilson', 'Male', 28, NOW());

-- Insert vital signs for each patient across 3 weeks
-- Using exact dates for October 2023 (adjust dates as needed)

-- John Smith: Normal first 2 weeks, abnormal 3rd week
INSERT INTO vital_signs 
(patient_id, heart_rate, blood_pressure, temperature, recorded_at, is_normal, age_group) VALUES
(1, 72, 120, 98.6, '2023-10-01 10:00:00', true, 'Adult'),   -- Week 1: Normal
(1, 75, 118, 98.7, '2023-10-08 10:00:00', true, 'Adult'),   -- Week 2: Normal
(1, 120, 150, 102.0, '2023-10-15 10:00:00', false, 'Adult'); -- Week 3: Abnormal

-- Mary Johnson: All normal readings
INSERT INTO vital_signs 
(patient_id, heart_rate, blood_pressure, temperature, recorded_at, is_normal, age_group) VALUES
(2, 70, 115, 98.2, '2023-10-01 11:00:00', true, 'Adult'),
(2, 72, 118, 98.4, '2023-10-08 11:00:00', true, 'Adult'),
(2, 71, 117, 98.3, '2023-10-15 11:00:00', true, 'Adult');

-- Bob Wilson: All abnormal readings
INSERT INTO vital_signs 
(patient_id, heart_rate, blood_pressure, temperature, recorded_at, is_normal, age_group) VALUES
(3, 130, 160, 102.5, '2023-10-01 12:00:00', false, 'Adult'),
(3, 125, 155, 102.3, '2023-10-08 12:00:00', false, 'Adult'),
(3, 128, 158, 102.4, '2023-10-15 12:00:00', false, 'Adult');

-- Add abnormal readings records
INSERT INTO abnormal_readings 
(patient_id, record_id, abnormal_type, abnormal_value, abnormal_timestamp)
SELECT 
    v.patient_id,
    v.record_id,
    CASE 
        WHEN v.heart_rate > 100 THEN 'Heart Rate'
        WHEN v.blood_pressure > 140 THEN 'Blood Pressure'
        ELSE 'Temperature'
    END as abnormal_type,
    CASE 
        WHEN v.heart_rate > 100 THEN v.heart_rate
        WHEN v.blood_pressure > 140 THEN v.blood_pressure
        ELSE v.temperature
    END as abnormal_value,
    v.recorded_at
FROM vital_signs v
WHERE NOT v.is_normal;
