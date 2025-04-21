package cyprusDryCleanEntities;


import java.util.Date;
/**
 * Employee Class represents an employee with personal details.
 * This class is used to store and retrieve employee information.
 *
 *
 *
 * @author Ferhat Kasim Koc
 * @version 23.0
 */
public class Employee {
    private int id;
    private String name;
    private String surname;
    private Date dateOfBirth;
    private Date startDate;

    /**
     * Default constructor initializing an employee with default values.
     */
    public Employee() {
        this.id = 0;
        this.name = "Unknown";
        this.surname = "Unknown";
        this.dateOfBirth = null;
        this.startDate = null;
    }

    /**
     * This constructor is initializing an employee with basic personal information.
     * No need to provide Birth Date or Starting Date
     * @param employeeId the unique identifier for the employee
     * @param name the first name of the employee
     * @param surname the last name of the employee
     */
    public Employee(int employeeId, String name, String surname) {
        this.id = employeeId;
        this.name = name;
        this.surname = surname;
        this.dateOfBirth = null;
        this.startDate = null;
    }

    /**
     * This constructor is used to initialize an employee with all fields.
     * @param employeeId the unique identifier for the employee
     * @param name the first name of the employee
     * @param surname the last name of the employee
     * @param dateOfBirth the Birth Date of the employee
     * @param startDate the date the employee started work
     */
    public Employee(int employeeId, String name, String surname, Date dateOfBirth, Date startDate) {
        this.id = employeeId;
        this.name = name;
        this.surname = surname;
        this.dateOfBirth = dateOfBirth;
        this.startDate = startDate;
    }


    public int getEmployeeId() {
        return id;
    }
    public void setEmployeeId(int employeeId) {
        this.id = employeeId;
    }


    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }


    public String getSurname() {
        return surname;
    }
    public void setSurname(String surname) {
        this.surname = surname;
    }


    public Date getDateOfBirth() {
        return dateOfBirth;
    }
    public void setDateOfBirth(Date dateOfBirth) {
        this.dateOfBirth = dateOfBirth;
    }


    public Date getStartDate() {
        return startDate;
    }
    public void setStartDate(Date startDate) {
        this.startDate = startDate;
    }


    /**
     * This method is used to display the details of the employee
     * which are ID, name, surname, date of birth, and start date.
     */
    public void displayEmployeeDetails() {
        System.out.println("Employee ID: " + id);
        System.out.println("Name: " + name);
        System.out.println("Surname: " + surname);
        System.out.println("Date of Birth: " + dateOfBirth);
        System.out.println("Start Date: " + startDate);
    }
}
