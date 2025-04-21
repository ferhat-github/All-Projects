package dryclean.cyprusDryCleanEntities;

import java.util.Date;

/**
 * Represents a user in the system.
 * This abstract class serves as a base for different types of users,
 * such as employees and customers.
 *
 *
 *
 * @author Ferhat Kasim Koc
 * @version 23.0
 */
public abstract class User {
    private int ID;
    private Date dateOfBirth;
    private String name;
    private String surname;


    /**
     * Default constructor for User.
     * Initializes fields with default values.
     */
    public User() {
        this.ID = 0;
        this.dateOfBirth = null;
        this.name = "Unknown";
        this.surname = "Unknown";
    }


    /**
     * Constructs a User with an ID, name, and surname.
     * @param ID The unique identifier for the user.
     * @param name The first name of the user.
     * @param surname The last name of the user.
     */
    public User(int ID, String name, String surname) {
        this.ID = ID;
        this.dateOfBirth = null;
        this.name = name;
        this.surname = surname;
    }


    /**
     * Constructs a User with an ID, date of birth, name, and surname.
     * @param ID The unique identifier for the user.
     * @param dateOfBirth The birthdate of the user.
     * @param name The first name of the user.
     * @param surname The last name of the user.
     */
    public User(int ID, Date dateOfBirth, String name, String surname) {
        this.ID = ID;
        this.dateOfBirth = dateOfBirth;
        this.name = name;
        this.surname = surname;
    }


    public int getID() {
        return ID;
    }
    public void setID(int ID) {
        this.ID = ID;
    }


    public Date getDateOfBirth() {
        return dateOfBirth;
    }
    public void setDateOfBirth(Date dateOfBirth) {
        this.dateOfBirth = dateOfBirth;
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

    @Override
    public String toString() {
        return "User:" + "ID=" + getID() +  ", Name=" + getName() + ", Surname=" + getSurname()  + ", Date of Birth=" + getDateOfBirth();
    }
}

