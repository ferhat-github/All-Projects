package dryclean.cyprusDryCleanInterfaces;


/**
 * Provides methods for managing customers in the system.
 * Includes functionality for calculating discounts and total income.
 *
 *
 *
 * @author Ferhat Kasim Koc
 * @version 23.0
 */
public interface customerManagement {
    public double minDeposit = 50.0; // Minimum deposit for subscribed customers

    /**
     * Calculate discount based on customer type and years of loyalty.
     * @return The discount percentage.
     */
    public double calculateDiscount();

    /**
     * Calculate the total income generated from a customer's orders.
     * @return The total income from all orders.
     */
    public double calculateTotalOrderIncome();
}
