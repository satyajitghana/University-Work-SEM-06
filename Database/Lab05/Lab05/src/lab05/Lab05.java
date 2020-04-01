/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab05;

import java.sql.*;

/**
 *
 * @author shadowleaf
 * 
 * Table Details : MANAGER (Name VARCHAR(50), Id INT PRIMARY KEY, Department CHAR(20), Address VARCHAR(255), Salary FLOAT);
 */
public class Lab05 {
    
    public static void addData(Statement stmt) throws SQLException {
            stmt.executeUpdate("INSERT INTO MANAGER VALUE ('SAMHITHA', 3, 'ISE', 'MALLESHWARAM', 15000)");
            stmt.executeUpdate("INSERT INTO MANAGER VALUE ('SHOBHAN', 4, 'ECE', 'RAJAJINAGAR', 20000)");
            stmt.executeUpdate("INSERT INTO MANAGER VALUE ('SOUMYADIP', 5, 'EEE', 'BEL', 12000)");
    }
    
    public static void viewAllData(Statement stmt) throws SQLException {
        ResultSet rs = stmt.executeQuery("SELECT * FROM MANAGER");
        
        System.out.printf("%20s | %3s | %5s | %10s | %9s\n", "Name", "Id", "Dept", "Address", "Salary\n");
        // iterate through the result
        while (rs.next()) {
            String name = rs.getString("Name");
            Integer id = rs.getInt("Id");
            String dept = rs.getString("Department");
            String address = rs.getString("Address");
            Double salary = rs.getDouble("Salary");
            
            System.out.printf("%20s | %3d | %5s | %10s | %8.2f\n", name, id, dept, address, salary);
        }
    }
    
    public static void viewDeptCount(Statement stmt) throws SQLException {
        ResultSet rs = stmt.executeQuery("SELECT Department, COUNT(Department) FROM MANAGER GROUP BY Department");
        
        System.out.printf("%10s | %10s", "Dept", "Count\n\n");
        while (rs.next()) {
            String dept = rs.getString("Department");
            Integer count = rs.getObject(2, Integer.class);
            
            System.out.printf("%10s | %10d\n", dept, count);
        }
    }
    
    public static void findManagers(Statement stmt) throws SQLException {
        ResultSet rs = stmt.executeQuery("SELECT Address, COUNT(Address) FROM MANAGER GROUP BY Address HAVING COUNT(Address) >= 2");
        
        System.out.printf("%20s | %10s", "Address", "Count\n\n");
        while (rs.next()) {
            String address = rs.getString("Address");
            Integer count = rs.getObject(2, Integer.class);
            
            System.out.printf("%20s | %10d\n", address, count);
        }
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        try {
            // load the registered driver
            Class.forName("com.mysql.jdbc.Driver");
            
            // create a connection object
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/students", "shadowleaf", "redosmiumtetroxide");
            
            // create a statement object
            Statement st = conn.createStatement();
            
            // add data to the table
            addData(st);
            
            System.out.println("ALL DETAILS");
            // display all the details of the managers
            viewAllData(st);
            
            System.out.println();
            
            System.out.println("DEPARTMENT COUNT");
            // view the department count
            viewDeptCount(st);
            
            System.out.println();
            
            System.out.println("LOCATION MANAGER COUNT >= 2");
            // view the locations with managers count >=2
            findManagers(st);
            
                        
        } catch (ClassNotFoundException | SQLException e) {
            System.out.println("Exception Occured : " + e.getMessage());
        }
    }
    
}
