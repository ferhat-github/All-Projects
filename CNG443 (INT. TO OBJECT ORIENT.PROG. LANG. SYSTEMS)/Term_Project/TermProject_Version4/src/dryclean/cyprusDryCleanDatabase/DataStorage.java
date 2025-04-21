package dryclean.cyprusDryCleanDatabase;

import dryclean.cyprusDryCleanEntities.*;

import java.sql.*;
import java.util.ArrayList;


/**
 * The DataStorage class manages the database operations for Employee and Customer data.
 * It can connect to the database, load data from the database, save data into the database,
 * and delete data based on an ID number.
 *
 * The class uses MySQL as the database and requires proper database connection credentials.
 *
 * @author Ferhat Kasim Koc
 * @version 23.0
 */
public class DataStorage {

    //Important Note! Dear Hocam, instead of having only readData() and writeData() methods, I distributed them and have more methods
    //in this class so that I can do more operations such that inserting single employee/customer deleting employee/customer etc.
    //I talked with Yeliz Hocam and I got her permission about these changes.
    //To conclude, instead of saving data to the database when user Exits from the application, I'm doing these operations during
    //all adding and deleting operations so that database and the source code always have the same data.


    //I am keeping them at the top of the program so that in case of any changes, you can easily access them and can do necessary changes.
    private static final String urladress = "jdbc:mysql://localhost:3306/cyprusdrycleandb";
    private static final String username = "cng443user";
    private static final String password = "1234";

    private Connection connection;


    /**
     * This method connects to the MySQL database using the provided URL, username, and password.
     */
    public void dataConnection() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(urladress, username, password);
            System.out.println("Database connected successfully.");
        } catch (ClassNotFoundException | SQLException e) {
            System.out.println("Connection couldn't be established" + e.getMessage());
        }
    }




    /**
     * This method loads all employee data from the database.
     * Each employee record is added to an ArrayList of Employee objects.
     *
     * @return an ArrayList containing all Employee objects from the database
     */
    public ArrayList<Employee> importEmployeeInformations() {
        ArrayList<Employee> emp = new ArrayList<>();


        try {
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery("SELECT * FROM Employee");

            while (resultSet.next()) {
                int id = resultSet.getInt("employeeID");
                Date dateOfBirth = resultSet.getDate("dateOfBirth");
                String name = resultSet.getString("name");
                String surname = resultSet.getString("surname");
                Date startDate = resultSet.getDate("startDate");
                String nationality = resultSet.getString("nationality");
                Date workPermitEndDate = resultSet.getDate("workPermitEndDate");


                Employee currentEmployee = new Employee(id, dateOfBirth, name, surname, startDate, nationality, workPermitEndDate);
                emp.add(currentEmployee);
            }
        } catch (SQLException e) {
            System.out.println("Employee couldn't be loaded!" + e.getMessage());
        }
        return emp;
    }


    /**
     * This method loads all customer data from the database.
     * If the customer is subscribed, extra details like subscription date and deposit paid will be included.
     *
     * @return an ArrayList containing all Customer objects from the database
     */
    public ArrayList<Customer> importCustomerInformations() {
        ArrayList<Customer> cst = new ArrayList<>();

        try {

            Statement statement = connection.createStatement();
            ResultSet rs = statement.executeQuery("SELECT * FROM Customer");


            while (rs.next()) {
                int id = rs.getInt("customerID");
                Date dateOfBirth = rs.getDate("dateOfBirth");
                String name = rs.getString("name");
                String surname = rs.getString("surname");
                Date registrationDate = rs.getDate("registrationDate");
                String type = rs.getString("type");

                //Note! In SQL file I deleted the NOT NULL statement from subscriptionDate because unsubscribed customers do not have it.
                if ("s".equalsIgnoreCase(type)) {
                    Date subscriptionDate = rs.getDate("subscriptionDate");
                    double depositPaid = rs.getDouble("depositPaid");

                    cst.add(new Subscribed(id, dateOfBirth, name, surname, registrationDate, subscriptionDate, depositPaid));
                }
                else {
                    cst.add(new Unsubscribed(id, dateOfBirth, name, surname, registrationDate));
                }
            }
        } catch (SQLException e) {
            System.out.println("Customers couldn't be loaded!" + e.getMessage());
        }
        return cst;
    }







    /**
     * This method adds a new employee to the database by saving the employee information to the database.
     *
     * @param emp The employee to be added.
     */
    public void insertEmployeeIntoDatabase(Employee emp) {

        try {
            PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO Employee (employeeID, dateOfBirth, name, surname, startDate, nationality, workPermitEndDate) VALUES (?, ?, ?, ?, ?, ?, ?)");

            preparedStatement.setInt(1, emp.getID());
            preparedStatement.setDate(2, new java.sql.Date(emp.getDateOfBirth().getTime()));
            preparedStatement.setString(3, emp.getName());
            preparedStatement.setString(4, emp.getSurname());
            preparedStatement.setDate(5, new java.sql.Date(emp.getStartDate().getTime()));
            preparedStatement.setString(6, emp.getNationality());
            preparedStatement.setDate(7, new java.sql.Date(emp.getWorkPermitEndDate().getTime()));


            preparedStatement.executeUpdate();

        } catch (SQLException e) {
            System.out.println("Employee couldn't be inserted!" + e.getMessage());
        }
    }




    /**
     * This method adds a new customer to the database.
     * If the customer is subscribed, extra details are saved too.
     *
     * @param cst The customer to be added.
     */
    public void insertCustomerIntoDatabase(Customer cst) {

        try {
            PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO Customer (customerID, dateOfBirth, name, surname, registrationDate, type, subscriptionDate, depositPaid) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");


            preparedStatement.setInt(1, cst.getID());
            preparedStatement.setDate(2, new java.sql.Date(cst.getDateOfBirth().getTime()));
            preparedStatement.setString(3, cst.getName());
            preparedStatement.setString(4, cst.getSurname());
            preparedStatement.setDate(5, new java.sql.Date(cst.getRegistrationDate().getTime()));

            if (cst instanceof Subscribed) {
                preparedStatement.setString(6, "s");
                preparedStatement.setDate(7, new java.sql.Date(((Subscribed) cst).getSubscriptionDate().getTime()));
                preparedStatement.setDouble(8, ((Subscribed) cst).getDepositPaid());
            } else {
                preparedStatement.setString(6, "u");
                preparedStatement.setNull(7, Types.DATE);
                preparedStatement.setNull(8, Types.DOUBLE);
            }

            preparedStatement.executeUpdate();

        } catch (SQLException e) {
            System.out.println("Customer couldn't be inserted!" + e.getMessage());
        }
    }





    /**
     * This method deletes an employee from the database by using their ID.
     *
     * @param employeeId The ID of the employee to delete.
     */
    public void deleteEmployeeFromDatabaseByID(int employeeId) {
        try {
            PreparedStatement preparedStatement = connection.prepareStatement("DELETE FROM Employee WHERE employeeID = ?");
            preparedStatement.setInt(1, employeeId);

            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            System.out.println("Employee could not be deleted!" + e.getMessage());
        }
    }


    /**
     * This method deletes a customer from the database by using their ID.
     *
     * @param customerId The ID of the customer to delete.
     */
    public void deleteCustomerFromDatabaseByID(int customerId) {
        try {
            PreparedStatement preparedStatement = connection.prepareStatement("DELETE FROM Customer WHERE customerID = ?");
            preparedStatement.setInt(1, customerId);

            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            System.out.println("Customer could not be deleted!" + e.getMessage());
        }
    }




    /**
     * This method closes the connection to the database.
     */
    public void closingConnection() {
        try {
            if (connection != null && !connection.isClosed()) {
                connection.close();
                System.out.println("Database connection closed.");
            }
        } catch (SQLException e) {
            System.out.println("Database could not be closed!" + e.getMessage());
        }
    }

}


