-- phpMyAdmin SQL Dump
-- version 4.8.5
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Apr 09, 2020 at 02:16 AM
-- Server version: 8.0.13-4
-- PHP Version: 7.2.24-0ubuntu0.18.04.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `n8HhmAPObs`
--

-- --------------------------------------------------------

--
-- Table structure for table `EXHIBITION`
--

CREATE TABLE `EXHIBITION` (
  `room_id` int(5) NOT NULL,
  `room_name` char(20) COLLATE utf8_unicode_ci NOT NULL,
  `capacity` int(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `EXHIBITION`
--

INSERT INTO `EXHIBITION` (`room_id`, `room_name`, `capacity`) VALUES
(1, 'A201', 60);

-- --------------------------------------------------------

--
-- Table structure for table `PROJECT_EXHIBITION`
--

CREATE TABLE `PROJECT_EXHIBITION` (
  `room_id` int(5) NOT NULL,
  `project_id` int(5) NOT NULL,
  `table_no` int(5) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `PROJECT_EXHIBITION`
--

INSERT INTO `PROJECT_EXHIBITION` (`room_id`, `project_id`, `table_no`) VALUES
(1, 2, 1);

-- --------------------------------------------------------

--
-- Table structure for table `PROJECT_STUDENT_REGISTER`
--

CREATE TABLE `PROJECT_STUDENT_REGISTER` (
  `project_id` int(5) NOT NULL,
  `student_reg_no` char(12) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `PROJECT_STUDENT_REGISTER`
--

INSERT INTO `PROJECT_STUDENT_REGISTER` (`project_id`, `student_reg_no`) VALUES
(2, '17ETCS002159'),
(2, '17ETCS002122'),
(2, '17ETCS002168');

-- --------------------------------------------------------

--
-- Table structure for table `PROJEKT`
--

CREATE TABLE `PROJEKT` (
  `id` int(5) NOT NULL,
  `project_leader_regno` char(12) COLLATE utf8_unicode_ci NOT NULL,
  `project_name` varchar(100) COLLATE utf8_unicode_ci NOT NULL,
  `mentor_name` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `department` enum('CSE','EEE','ECE','CIVIL') COLLATE utf8_unicode_ci NOT NULL,
  `category` varchar(30) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `PROJEKT`
--

INSERT INTO `PROJEKT` (`id`, `project_leader_regno`, `project_name`, `mentor_name`, `department`, `category`) VALUES
(2, '17ETCS002159', 'KrishiAI', 'Chaitra S', 'CSE', 'DL');

-- --------------------------------------------------------

--
-- Table structure for table `STAFF_LOGIN`
--

CREATE TABLE `STAFF_LOGIN` (
  `id` int(5) NOT NULL,
  `user_name` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  `hashed_password` char(60) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

-- --------------------------------------------------------

--
-- Table structure for table `STUDENT`
--

CREATE TABLE `STUDENT` (
  `id` int(5) NOT NULL,
  `reg_no` char(12) COLLATE utf8_unicode_ci NOT NULL,
  `name` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `department` enum('CSE','EEE','ECE','CIVIL') COLLATE utf8_unicode_ci DEFAULT NULL,
  `course` enum('B.Tech','M.Tech') COLLATE utf8_unicode_ci NOT NULL,
  `contact_no` varchar(10) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `STUDENT`
--

INSERT INTO `STUDENT` (`id`, `reg_no`, `name`, `department`, `course`, `contact_no`) VALUES
(2, '17ETCS002122', 'Prachi Poddar', 'CSE', 'B.Tech', '9856523658'),
(1, '17ETCS002159', 'Satyajit Ghana', 'CSE', 'B.Tech', '7892137665'),
(3, '17ETCS002168', 'Shikhar Singh', 'CSE', 'B.Tech', '9852145896');

-- --------------------------------------------------------

--
-- Table structure for table `STUDENT_LOGIN`
--

CREATE TABLE `STUDENT_LOGIN` (
  `id` int(5) NOT NULL,
  `user_name` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  `hashed_password` char(60) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Dumping data for table `STUDENT_LOGIN`
--

INSERT INTO `STUDENT_LOGIN` (`id`, `user_name`, `hashed_password`) VALUES
(1, '17ETCS002159', '$2b$10$uVRx4ogFBi0owMljpvEilONnd9wWOMtrpgVwqw2Mw8.aNmo6yEU1u'),
(2, '17ETCS002122', '$2b$10$ATp9qxsPWBsOUXDAB1YvK.yTLi4GK1mzpIHBCfSOCQwtxLU/52Pk2'),
(3, '17ETCS002168', '$2b$10$3cfBMD3yRi3YJk.fFGrNY.Yx1RRonj4z2cqgOe2fgZ78yNaqRxFkC');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `EXHIBITION`
--
ALTER TABLE `EXHIBITION`
  ADD PRIMARY KEY (`room_id`),
  ADD UNIQUE KEY `room_name` (`room_name`);

--
-- Indexes for table `PROJECT_EXHIBITION`
--
ALTER TABLE `PROJECT_EXHIBITION`
  ADD UNIQUE KEY `project_id` (`project_id`),
  ADD KEY `room_id` (`room_id`);

--
-- Indexes for table `PROJECT_STUDENT_REGISTER`
--
ALTER TABLE `PROJECT_STUDENT_REGISTER`
  ADD KEY `project_id` (`project_id`),
  ADD KEY `student_reg_no` (`student_reg_no`);

--
-- Indexes for table `PROJEKT`
--
ALTER TABLE `PROJEKT`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `project_leader_regno` (`project_leader_regno`),
  ADD UNIQUE KEY `project_name` (`project_name`);

--
-- Indexes for table `STAFF_LOGIN`
--
ALTER TABLE `STAFF_LOGIN`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `user_name` (`user_name`);

--
-- Indexes for table `STUDENT`
--
ALTER TABLE `STUDENT`
  ADD PRIMARY KEY (`reg_no`),
  ADD UNIQUE KEY `id` (`id`);

--
-- Indexes for table `STUDENT_LOGIN`
--
ALTER TABLE `STUDENT_LOGIN`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `user_name` (`user_name`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `EXHIBITION`
--
ALTER TABLE `EXHIBITION`
  MODIFY `room_id` int(5) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `PROJEKT`
--
ALTER TABLE `PROJEKT`
  MODIFY `id` int(5) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `STAFF_LOGIN`
--
ALTER TABLE `STAFF_LOGIN`
  MODIFY `id` int(5) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `STUDENT_LOGIN`
--
ALTER TABLE `STUDENT_LOGIN`
  MODIFY `id` int(5) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `PROJECT_EXHIBITION`
--
ALTER TABLE `PROJECT_EXHIBITION`
  ADD CONSTRAINT `PROJECT_EXHIBITION_ibfk_1` FOREIGN KEY (`room_id`) REFERENCES `EXHIBITION` (`room_id`),
  ADD CONSTRAINT `PROJECT_EXHIBITION_ibfk_2` FOREIGN KEY (`project_id`) REFERENCES `PROJEKT` (`id`);

--
-- Constraints for table `PROJECT_STUDENT_REGISTER`
--
ALTER TABLE `PROJECT_STUDENT_REGISTER`
  ADD CONSTRAINT `PROJECT_STUDENT_REGISTER_ibfk_1` FOREIGN KEY (`project_id`) REFERENCES `PROJEKT` (`id`),
  ADD CONSTRAINT `PROJECT_STUDENT_REGISTER_ibfk_2` FOREIGN KEY (`student_reg_no`) REFERENCES `STUDENT` (`reg_no`);

--
-- Constraints for table `STUDENT`
--
ALTER TABLE `STUDENT`
  ADD CONSTRAINT `STUDENT_ibfk_1` FOREIGN KEY (`id`) REFERENCES `STUDENT_LOGIN` (`id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
