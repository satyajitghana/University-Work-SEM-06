USE students;

-- Drop the table if it exists
DROP TABLE IF EXISTS MANAGER;

-- Create the table
CREATE TABLE MANAGER (Name VARCHAR(50), Id INT PRIMARY KEY, Department CHAR(20), Address VARCHAR(255), Salary FLOAT);

-- Insert Values
INSERT INTO MANAGER VALUES 
('SATYAJIT GHANA', 0, 'CSE', 'BEL', 12500),
('ANUSHA', 1, 'CSE', 'JP NAGAR', 12000),
('SHIKHAR', 2, 'ASE', 'J.CROSS', 15000);

-- Show the table
SELECT * FROM MANAGER;
