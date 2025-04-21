package dryclean.cyprusDryCleanEntities;



import java.util.Date;
import java.util.HashMap;
import java.text.SimpleDateFormat;

/**
 * Represents an employee in the system.
 * Employees have unique IDs, work-related details, and health inspection records.
 * Extends the {@link User} class.
 *
 *
 *
 * @author Ferhat Kasim Koc
 * @version 23.0
 */
public class Employee extends User {
    private Date startDate;
    private String nationality;
    private HashMap<Date, String> healthInspection;
    private Date workPermitEndDate;


    /**
     * Default constructor initializing an employee with default values.
     */
    public Employee() {
        super(0, null, "Unknown", "Unknown");
        this.startDate = null;
        this.nationality = "Unknown";
        this.healthInspection = new HashMap<>();
        this.workPermitEndDate = null;
    }


    /**
     * Constructs an employee with basic details.
     * @param ID The unique identifier for the employee.
     * @param dateOfBirth The birthdate of the employee.
     * @param name The first name of the employee.
     * @param surname The last name of the employee.
     * @param startDate The start date of the employee.
     * @param workPermitEndDate The work permit expiration date of the employee.
     */
    public Employee(int ID, Date dateOfBirth, String name, String surname, Date startDate, Date workPermitEndDate) {
        super(ID, dateOfBirth, name, surname);
        this.startDate = startDate;
        this.healthInspection = new HashMap<>();
        this.workPermitEndDate = workPermitEndDate;
    }


    /**
     * Constructs an employee with full details.
     * @param ID The unique identifier for the employee.
     * @param dateOfBirth The birthdate of the employee.
     * @param name The first name of the employee.
     * @param surname The last name of the employee.
     * @param startDate The start date of the employee.
     * @param nationality The nationality of the employee.
     * @param workPermitEndDate The work permit expiration date of the employee.
     */
    public Employee(int ID, Date dateOfBirth, String name, String surname, Date startDate, String nationality, Date workPermitEndDate) {
        super(ID, dateOfBirth, name, surname);
        this.startDate = startDate;
        this.nationality = nationality;
        this.healthInspection = new HashMap<>();
        this.workPermitEndDate = workPermitEndDate;
    }


    public Date getStartDate() {
        return startDate;
    }
    public void setStartDate(Date startDate) {
        this.startDate = startDate;
    }


    public String getNationality() {
        return nationality;
    }
    public void setNationality(String nationality) {
        this.nationality = nationality;
    }


    public HashMap<Date, String> getHealthInspection() {
        return healthInspection;
    }

    /**
     * Adds a health inspection record for the employee.
     * @param inspectionDate The date of the health inspection.
     * @param report The report of the health inspection.
     */
    public void addHealthInspection(Date inspectionDate, String report) {
        healthInspection.put(inspectionDate, report);
    }


    public Date getWorkPermitEndDate() {
        return workPermitEndDate;
    }
    public void setWorkPermitEndDate(Date workPermitEndDate) {
        this.workPermitEndDate = workPermitEndDate;
    }



    /**
     * Displays the details of the employee, including their health inspections.
     */
    public void displayEmployeeDetails() {

        SimpleDateFormat dateFormat = new SimpleDateFormat("d MMMM yyyy");

        System.out.println("Employee ID: " + getID());
        System.out.println("Name: " + getName() + " " + getSurname());
        System.out.println("Date of Birth: " + getDateOfBirth());
        System.out.println("Start Date: " + getStartDate());
        System.out.println("Nationality: " + getNationality());
        System.out.println("Work Permit End Date: " + getWorkPermitEndDate());
        System.out.println("Health Inspections: ");



        if (healthInspection.isEmpty()) {
            System.out.println("No health inspections recorded.");
        } else {
            for (Date date : healthInspection.keySet()) {
                String formattedDate = dateFormat.format(date);
                System.out.println(formattedDate + " – \"" + healthInspection.get(date) + "\"");
            }
        }
    }
}
