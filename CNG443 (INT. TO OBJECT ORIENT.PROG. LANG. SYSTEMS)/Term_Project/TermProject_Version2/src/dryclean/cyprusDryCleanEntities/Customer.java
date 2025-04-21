package dryclean.cyprusDryCleanEntities;
import dryclean.cyprusDryCleanInterfaces.customerManagement;

import java.util.ArrayList;
import java.util.Date;

/**
 * Represents a customer in the system.
 * Customers can place orders and may have specific attributes depending on their subscription type.
 * This abstract class extends the {@link User} class and implements {@link customerManagement} and {@link Comparable}.
 *
 *
 *
 * @author Ferhat Kasim Koc
 * @version 23.0
 */

public abstract class Customer extends User implements customerManagement, Comparable<Customer> {
    private Date registrationDate;
    private ArrayList<Order> orders;


    /**
     * Default constructor initializing a customer with default values.
     */
    public Customer() {
        super(0, null, "Unknown", "Unknown");
        this.registrationDate = null;
        this.orders = new ArrayList<>();
    }


    /**
     * Constructs a customer with basic details.
     * @param ID The unique identifier for the customer.
     * @param name The first name of the customer.
     * @param surname The last name of the customer.
     * @param registrationDate The registration date of the customer.
     */
    public Customer(int ID, String name, String surname, Date registrationDate) {
        super(ID, null, name, surname);
        this.registrationDate = registrationDate;
        this.orders = new ArrayList<>();
    }


    /**
     * Constructs a customer with full details.
     * @param ID The unique identifier for the customer.
     * @param dateOfBirth The birthdate of the customer.
     * @param name The first name of the customer.
     * @param surname The last name of the customer.
     * @param registrationDate The registration date of the customer.
     */
    public Customer(int ID, Date dateOfBirth, String name, String surname, Date registrationDate) {
        super(ID, dateOfBirth, name, surname);
        this.registrationDate = registrationDate;
        this.orders = new ArrayList<>();
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
        this.orders.add(order);
    }


    /**
     * Abstract method to display the details of the customer.
     * Each subclass must implement this method to provide specific details about the customer.
     */
    public abstract void displayCustomerDetails();


    /**
     * Compares this customer with another customer based on total order income (ignoring discounts).
     * @param other The other customer to compare to.
     * @return A negative integer, zero, or a positive integer as this customer brings less, equal, or more income than the other customer.
     */
    @Override
    public int compareTo(Customer other) {
        double thisIncome = this.calculateTotalOrderIncome();
        double otherIncome = other.calculateTotalOrderIncome();
        return Double.compare(thisIncome, otherIncome);
    }

}

