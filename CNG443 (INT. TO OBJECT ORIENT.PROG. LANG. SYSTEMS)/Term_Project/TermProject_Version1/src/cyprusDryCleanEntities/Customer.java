package cyprusDryCleanEntities;


import java.util.ArrayList;
import java.util.Date;

/**
 * The Customer class is used to represent a customer in the system.
 * It stores essential details about the customer, like their name, ID,
 * registration date, and any orders they’ve placed.
 *
 *
 *
 * @author Ferhat Kasim Koc
 * @version 23.0
 */


public class Customer {
    private int customerId;
    private String name;
    private String surname;
    private Date registrationDate;
    private ArrayList<Order> orders;  // List of orders for the customer


    /**
     * Default constructor that initializes a new customer with default values.
     * The customer ID is set to 0, name and surname are set to "Unknown",
     * and the registration date is set to the current date. An empty order list
     * is also created for this customer.
     */
    public Customer() {
        this.customerId = 0;
        this.name = "Unknown";
        this.surname = "Unknown";
        this.registrationDate = new Date();
        this.orders = new ArrayList<>();
    }


    /**
     * This constructor will be used to set up a customer with all the main information.
     * @param customerId unique ID for each customer
     * @param name first name of the customer
     * @param surname last name of the customer
     * @param registrationDate the date when the customer registered
     */
    public Customer(int customerId, String name, String surname, Date registrationDate) {
        this.customerId = customerId;
        this.name = name;
        this.surname = surname;
        this.registrationDate = registrationDate;
        this.orders = new ArrayList<>();
    }



    /**
     * Constructor that initializes a new customer with a unique ID, name, and surname.
     * The registration date is set to the current date, and an empty order list is created.
     * @param customerId the unique ID for the customer
     * @param name the first name of the customer
     * @param surname the last name of the customer
     */
    public Customer(int customerId, String name, String surname) {
        this.customerId = customerId;
        this.name = name;
        this.surname = surname;
        this.registrationDate = new Date();
        this.orders = new ArrayList<>();
    }


    public int getCustomerId() {
        return customerId;
    }
    public void setCustomerId(int customerId) {
        this.customerId = customerId;
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


    public Date getRegistrationDate() {
        return registrationDate;
    }
    public void setRegistrationDate(Date registrationDate) {
        this.registrationDate = registrationDate;
    }


    public ArrayList<Order> getOrders() {
        return orders;
    }
    public void putOrder(Order order) {
        orders.add(order);
    }



    /**
     * Shows the customer’s details, like their ID, name, registration date,
     * and how many orders they've made so far.
     */
    public void displayCustomerDetails() {
        System.out.println("Customer ID: " + customerId);
        System.out.println("Name: " + name);
        System.out.println("Surname: " + surname);
        System.out.println("Registration Date: " + registrationDate);
        System.out.println("Total Orders: " + orders.size());
    }
}
