package dryclean.cyprusDryCleanEntities;


/**
 * Represents a dry cleaning laundry item.
 * Dry cleaning total cost is calculated using the quantity, price, and electricity rate.
 * Extends the {@link LaundryItem} class.
 *
 *
 *
 * @author Ferhat Kasim Koc
 * @version 23.0
 */
public class DryClean extends LaundryItem {

    /**
     * Default constructor initializing a dry cleaning item with default values.
     */
    public DryClean() {
        super("Unknown", 0, 0, "Unknown", null);
    }


    /**
     * Constructs a dry cleaning item with basic details.
     * @param quantity The quantity of the laundry item.
     * @param price The price per unit of the laundry item.
     * @param assigned The employee assigned to process this laundry item.
     */
    public DryClean(int quantity, double price, Employee assigned) {
        super("Unknown", quantity, price, "Unknown", assigned);
    }


    /**
     * Constructs a dry cleaning item with full details.
     * @param type The type of the laundry item (e.g., shirt, skirt).
     * @param quantity The quantity of the laundry item.
     * @param price The price per unit of the laundry item.
     * @param notes Any special notes about the laundry item.
     * @param assigned The employee assigned to process this laundry item.
     */
    public DryClean(String type, int quantity, double price, String notes, Employee assigned) {
        super(type, quantity, price, notes, assigned);
    }

    /**
     * Calculates the total cost of the dry cleaning item.
     * @return The total cost of the dry cleaning item.
     */
    @Override
    public double totalCost() {
        return getQuantity() * getPrice() * electricityRate;
    }


    @Override
    public String toString() {
        return "Dry Clean Type: " + getType() +
                ", Quantity: " + getQuantity() +
                ", Price: " + getPrice() +
                ", Notes: " + getNotes() +
                ", Assigned Employee: " + getAssigned().getName() + " " + getAssigned().getSurname() +
                ", Total Cost: " + totalCost();
    }

}
