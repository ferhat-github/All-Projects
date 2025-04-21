
--
-- User: `CNG443user`
--
CREATE USER IF NOT EXISTS 'cng443user'@'localhost' IDENTIFIED BY '1234';


--
-- Database: `BasicDB`
--
CREATE DATABASE IF NOT EXISTS `CyprusDryCleanDB` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;

--
-- Give all privileges to CNG443user on this database
--
GRANT ALL PRIVILEGES ON `CyprusDryCleanDB`.* TO 'cng443user'@'localhost';


--
-- Use this database to create the tables
--
USE `CyprusDryCleanDB`;


--
-- Table structure for table `Customer`
--

CREATE TABLE `Customer` (
  `customerID` int(6) NOT NULL,
  `dateOfBirth` date NOT NULL,
  `name` char(50) NOT NULL,
  `surname` char(50) NOT NULL,
  `registrationDate` date NOT NULL,
  `type` char(1) NOT NULL,
  `subscriptionDate` date,
  `depositPaid` double
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Table structure for table `Employee`
--

CREATE TABLE `Employee` (
  `employeeID` int(11) NOT NULL,
  `dateOfBirth` date NOT NULL,
  `name` char(50) NOT NULL,
  `surname` char(50) NOT NULL,
  `startDate` date NOT NULL,
  `nationality` char(50) NOT NULL,
  `workPermitEndDate` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `User`
--
ALTER TABLE `Customer`
  ADD PRIMARY KEY (`customerID`);

--
-- Indexes for table `Employee`
--
ALTER TABLE `Employee`
  ADD PRIMARY KEY (`employeeID`);
