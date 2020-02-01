```python
%load_ext sql
```


```python
import json
with open('/home/shadowleaf/.local/config/mysql_config.json') as f:
  data = json.load(f)
```


```python
import os
DATABASE_URL = 'mysql+pymysql://{}:{}@localhost:3306/students'.format(data['user'], data['password'])
os.environ['DATABASE_URL'] = DATABASE_URL
```

## Show the databases


```python
%sql SHOW DATABASES
```

    5 rows affected.
    




<table>
    <tr>
        <th>Database</th>
    </tr>
    <tr>
        <td>information_schema</td>
    </tr>
    <tr>
        <td>mysql</td>
    </tr>
    <tr>
        <td>performance_schema</td>
    </tr>
    <tr>
        <td>students</td>
    </tr>
    <tr>
        <td>sys</td>
    </tr>
</table>



## Select a Database


```python
%sql USE students;
```

     * mysql+pymysql://shadowleaf:***@localhost:3306/students
    0 rows affected.
    




    []



## Show Tables


```python
%sql SHOW TABLES
```

     * mysql+pymysql://shadowleaf:***@localhost:3306/students
    1 rows affected.
    




<table>
    <tr>
        <th>Tables_in_students</th>
    </tr>
    <tr>
        <td>student_list</td>
    </tr>
</table>



## Create a Table and Insert Data into it


```python
%%sql

-- if the table already exists then drop it

DROP TABLE IF EXISTS `student_list`;

-- create a table with the attributes

CREATE TABLE `student_list` (
  `student_id` int(11) DEFAULT NULL,
  `student_name` char(20) DEFAULT NULL,
  `student_address` char(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- insert data into the table

LOCK TABLES `student_list` WRITE;
INSERT INTO `student_list` VALUES (101,'satyajit ghana','bangalore'),(102,'shikhar singh','bangalore'),(103,'shubham agarwal','haryana'),(104,'pritam das','kolkata');
UNLOCK TABLES;
```

     * mysql+pymysql://shadowleaf:***@localhost:3306/students
    0 rows affected.
    0 rows affected.
    0 rows affected.
    4 rows affected.
    0 rows affected.
    




    []



## Describe Table


```python
%sql DESC `student_list`
```

     * mysql+pymysql://shadowleaf:***@localhost:3306/students
    3 rows affected.
    




<table>
    <tr>
        <th>Field</th>
        <th>Type</th>
        <th>Null</th>
        <th>Key</th>
        <th>Default</th>
        <th>Extra</th>
    </tr>
    <tr>
        <td>student_id</td>
        <td>int(11)</td>
        <td>YES</td>
        <td></td>
        <td>None</td>
        <td></td>
    </tr>
    <tr>
        <td>student_name</td>
        <td>char(20)</td>
        <td>YES</td>
        <td></td>
        <td>None</td>
        <td></td>
    </tr>
    <tr>
        <td>student_address</td>
        <td>char(50)</td>
        <td>YES</td>
        <td></td>
        <td>None</td>
        <td></td>
    </tr>
</table>



## View the Data stored in Table


```python
%sql SELECT * FROM student_list;
```

     * mysql+pymysql://shadowleaf:***@localhost:3306/students
    4 rows affected.
    




<table>
    <tr>
        <th>student_id</th>
        <th>student_name</th>
        <th>student_address</th>
    </tr>
    <tr>
        <td>101</td>
        <td>satyajit ghana</td>
        <td>bangalore</td>
    </tr>
    <tr>
        <td>102</td>
        <td>shikhar singh</td>
        <td>bangalore</td>
    </tr>
    <tr>
        <td>103</td>
        <td>shubham agarwal</td>
        <td>haryana</td>
    </tr>
    <tr>
        <td>104</td>
        <td>pritam das</td>
        <td>kolkata</td>
    </tr>
</table>



## Update a row in the table

UPDATE statement that changes the data of one or more records in a table. It is used to update a row of a table. Either all the rows can be updated, or a subset may be chosen using a condition. 


```python
%%sql

UPDATE `student_list` SET student_id=105 WHERE student_id=104;

SELECT * FROM `student_list`;
```

     * mysql+pymysql://shadowleaf:***@localhost:3306/students
    1 rows affected.
    4 rows affected.
    




<table>
    <tr>
        <th>student_id</th>
        <th>student_name</th>
        <th>student_address</th>
    </tr>
    <tr>
        <td>101</td>
        <td>satyajit ghana</td>
        <td>bangalore</td>
    </tr>
    <tr>
        <td>102</td>
        <td>shikhar singh</td>
        <td>bangalore</td>
    </tr>
    <tr>
        <td>103</td>
        <td>shubham agarwal</td>
        <td>haryana</td>
    </tr>
    <tr>
        <td>105</td>
        <td>pritam das</td>
        <td>kolkata</td>
    </tr>
</table>




```python
%%sql

DELETE FROM `student_list` WHERE student_id=105;

SELECT * FROM `student_list`;
```

     * mysql+pymysql://shadowleaf:***@localhost:3306/students
    1 rows affected.
    3 rows affected.
    




<table>
    <tr>
        <th>student_id</th>
        <th>student_name</th>
        <th>student_address</th>
    </tr>
    <tr>
        <td>101</td>
        <td>satyajit ghana</td>
        <td>bangalore</td>
    </tr>
    <tr>
        <td>102</td>
        <td>shikhar singh</td>
        <td>bangalore</td>
    </tr>
    <tr>
        <td>103</td>
        <td>shubham agarwal</td>
        <td>haryana</td>
    </tr>
</table>



## Aggregate Functions


```python
%sql SELECT COUNT(*), AVG(student_id), SUM(student_id), MIN(student_id), MAX(student_id)  FROM `student_list`
```

     * mysql+pymysql://shadowleaf:***@localhost:3306/students
    1 rows affected.
    




<table>
    <tr>
        <th>COUNT(*)</th>
        <th>AVG(student_id)</th>
        <th>SUM(student_id)</th>
        <th>MIN(student_id)</th>
        <th>MAX(student_id)</th>
    </tr>
    <tr>
        <td>3</td>
        <td>102.0000</td>
        <td>306</td>
        <td>101</td>
        <td>103</td>
    </tr>
</table>



# Lab01

    1. Display the details of all the students


```python
%sql SELECT * FROM `student_list`
```

     * mysql+pymysql://shadowleaf:***@localhost:3306/students
    3 rows affected.
    




<table>
    <tr>
        <th>student_id</th>
        <th>student_name</th>
        <th>student_address</th>
    </tr>
    <tr>
        <td>101</td>
        <td>satyajit ghana</td>
        <td>bangalore</td>
    </tr>
    <tr>
        <td>102</td>
        <td>shikhar singh</td>
        <td>bangalore</td>
    </tr>
    <tr>
        <td>103</td>
        <td>shubham agarwal</td>
        <td>haryana</td>
    </tr>
</table>



    2. Display the name and address of the student with id = 101


```python
%sql SELECT student_name, student_address FROM `student_list`
```

     * mysql+pymysql://shadowleaf:***@localhost:3306/students
    3 rows affected.
    




<table>
    <tr>
        <th>student_name</th>
        <th>student_address</th>
    </tr>
    <tr>
        <td>satyajit ghana</td>
        <td>bangalore</td>
    </tr>
    <tr>
        <td>shikhar singh</td>
        <td>bangalore</td>
    </tr>
    <tr>
        <td>shubham agarwal</td>
        <td>haryana</td>
    </tr>
</table>



    3. Insert a new student <105, ‘John’, ‘Bangalore’>


```python
%%sql

INSERT INTO student_list VALUES(105, 'John', 'Bangalore');

SELECT * FROM `student_list`;
```

     * mysql+pymysql://shadowleaf:***@localhost:3306/students
    1 rows affected.
    4 rows affected.
    




<table>
    <tr>
        <th>student_id</th>
        <th>student_name</th>
        <th>student_address</th>
    </tr>
    <tr>
        <td>101</td>
        <td>satyajit ghana</td>
        <td>bangalore</td>
    </tr>
    <tr>
        <td>102</td>
        <td>shikhar singh</td>
        <td>bangalore</td>
    </tr>
    <tr>
        <td>103</td>
        <td>shubham agarwal</td>
        <td>haryana</td>
    </tr>
    <tr>
        <td>105</td>
        <td>John</td>
        <td>Bangalore</td>
    </tr>
</table>



    4. Change the address of the student John to ‘Delhi’


```python
%%sql

UPDATE `student_list` SET student_address='Delhi' WHERE student_id=105;

SELECT * FROM `student_list`;
```

     * mysql+pymysql://shadowleaf:***@localhost:3306/students
    1 rows affected.
    4 rows affected.
    




<table>
    <tr>
        <th>student_id</th>
        <th>student_name</th>
        <th>student_address</th>
    </tr>
    <tr>
        <td>101</td>
        <td>satyajit ghana</td>
        <td>bangalore</td>
    </tr>
    <tr>
        <td>102</td>
        <td>shikhar singh</td>
        <td>bangalore</td>
    </tr>
    <tr>
        <td>103</td>
        <td>shubham agarwal</td>
        <td>haryana</td>
    </tr>
    <tr>
        <td>105</td>
        <td>John</td>
        <td>Delhi</td>
    </tr>
</table>



    5. Delete the details of a student with student id=105


```python
%%sql

DELETE FROM `student_list` WHERE student_id=105;

SELECT * FROM `student_list`;
```

     * mysql+pymysql://shadowleaf:***@localhost:3306/students
    1 rows affected.
    3 rows affected.
    




<table>
    <tr>
        <th>student_id</th>
        <th>student_name</th>
        <th>student_address</th>
    </tr>
    <tr>
        <td>101</td>
        <td>satyajit ghana</td>
        <td>bangalore</td>
    </tr>
    <tr>
        <td>102</td>
        <td>shikhar singh</td>
        <td>bangalore</td>
    </tr>
    <tr>
        <td>103</td>
        <td>shubham agarwal</td>
        <td>haryana</td>
    </tr>
</table>



    6. Add a column to the schema Student with appropriate data type 


```python
%%sql

ALTER TABLE `student_list` ADD marks int(11);

DESC `student_list`;
```

     * mysql+pymysql://shadowleaf:***@localhost:3306/students
    0 rows affected.
    4 rows affected.
    




<table>
    <tr>
        <th>Field</th>
        <th>Type</th>
        <th>Null</th>
        <th>Key</th>
        <th>Default</th>
        <th>Extra</th>
    </tr>
    <tr>
        <td>student_id</td>
        <td>int(11)</td>
        <td>YES</td>
        <td></td>
        <td>None</td>
        <td></td>
    </tr>
    <tr>
        <td>student_name</td>
        <td>char(20)</td>
        <td>YES</td>
        <td></td>
        <td>None</td>
        <td></td>
    </tr>
    <tr>
        <td>student_address</td>
        <td>char(50)</td>
        <td>YES</td>
        <td></td>
        <td>None</td>
        <td></td>
    </tr>
    <tr>
        <td>marks</td>
        <td>int(11)</td>
        <td>YES</td>
        <td></td>
        <td>None</td>
        <td></td>
    </tr>
</table>




```python
%sql SELECT * FROM `student_list`;
```

     * mysql+pymysql://shadowleaf:***@localhost:3306/students
    3 rows affected.
    




<table>
    <tr>
        <th>student_id</th>
        <th>student_name</th>
        <th>student_address</th>
        <th>marks</th>
    </tr>
    <tr>
        <td>101</td>
        <td>satyajit ghana</td>
        <td>bangalore</td>
        <td>None</td>
    </tr>
    <tr>
        <td>102</td>
        <td>shikhar singh</td>
        <td>bangalore</td>
        <td>None</td>
    </tr>
    <tr>
        <td>103</td>
        <td>shubham agarwal</td>
        <td>haryana</td>
        <td>None</td>
    </tr>
</table>




```python

```
