package dryclean.cyprusDryCleanEntities;

import java.util.Date;

/**
 * Represents a subscribed customer in the system.
 * Subscribed customers receive a 10% discount on all orders and are required to pay a deposit.
 * Extends the {@link Customer} class.
 *
 *
 *
 * @author Ferhat Kasim Koc
 * @version 23.0
 */
public class Subscribed extends Customer {
    private Date subscriptionDate;
    private double depositPaid;


    /**
     * Default constructor initializing a subscribed customer with default values.
     */
    public Subscribed() {
        super(0, null, "Unknown", "Unknown", null);
        this.subscriptionDate = null;
        this.depositPaid = 0;
    }


    /**
     * Constructs a subscribed customer with basic details.
     * @param ID The unique identifier for the customer.
     * @param name The first name of the customer.
     * @param surname The last name of the customer.
     * @param registrationDate The registration date of the customer.
     * @param subscriptionDate The date when the customer subscribed.
     * @param depositPaid The deposit amount paid by the customer.
     */
    public Subscribed(int ID, String name, String surname, Date registrationDate, Date subscriptionDate, double depositPaid) {
        super(ID, null, name, surname, registrationDate);
        this.subscriptionDate = subscriptionDate;
        this.depositPaid = depositPaid;
    }



    /**
     * Constructs a subscribed customer with full details.
     * @param ID The unique identifier for the customer.
     * @param dateOfBirth The birthdate of the customer.
     * @param name The first name of the customer.
     * @param surname The last name of the customer.
     * @param registrationDate The registration date of the customer.
     * @param subscriptionDate The date when the customer subscribed.
     * @param depositPaid The deposit amount paid by the customer.
     */
    public Subscribed(int ID, Date dateOfBirth, String name, String surname, Date registrationDate, Date subscriptionDate, double depositPaid) {
        super(ID, dateOfBirth, name, surname, registrationDate);
        this.subscriptionDate = subscriptionDate;
        this.depositPaid = depositPaid;
    }


    public Date getSubscriptionDate() {
        return subscriptionDate;
    }
    public void setSubscriptionDate(Date subscriptionDate) {
        this.subscriptionDate = subscriptionDate;
    }


    public double getDepositPaid() {
        return depositPaid;
    }
    public void setDepositPaid(double depositPaid) {
        this.depositPaid = depositPaid;
    }


    /**
     * Displays the details of the subscribed customer, including subscription and deposit information.
     */
    @Override
    public void displayCustomerDetails() {
        System.out.println("Customer ID: " + getID());
        System.out.println("Name: " + getName());
        System.out.println("Surname: " + getSurname());
        System.out.println("Birthday Date: " + getDateOfBirth());
        System.out.println("Registration Date: " + getRegistrationDate());
        System.out.println("Mr/Mrs. " + getSurname() + " is a subscribed customer since " + getSubscriptionDate() + " and paid " + getDepositPaid() + " for deposit.");
        System.out.println("Total Orders: " + getOrders().size());
    }


    /**
     * Calculates the discount for the subscribed customer.
     * Subscribed customers always receive a 10% discount.
     * @return The discount rate as a percentage (e.g., 0.10 for 10%).
     */
    @Override
    public double calculateDiscount() {
        return 0.10; // Subscribed customers always receive a 10% discount
    }


    /**
     * Calculates the total income generated by the customer's orders,
     * ignoring any discounts.
     * @return The total income without discounts applied.
     */
    @Override
    public double calculateTotalOrderIncome() {
        double totalIncome = 0.0;
        for (Order order : this.getOrders()) {
            totalIncome += order.totalOrderCost(); // Total cost without discount
        }
        return totalIncome;
    }


    @Override
    public String toString() {
        return "Subscribed Customer ID: " + getID() +
                "\nName: " + getName() +
                "\nSurname: " + getSurname() +
                "\nRegistration Date: " + getRegistrationDate() +
                "\nSubscription Date: " + getSubscriptionDate() +
                "\nDeposit Paid: " + getDepositPaid() +
                "\nTotal Orders: " + getOrders().size();
    }


}


