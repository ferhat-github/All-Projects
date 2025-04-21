package dryclean.cyprusDryCleanEntities;



/**
 * Represents a wet cleaning laundry item.
 * Wet cleaning total cost is calculated using the quantity, price, water rate, and ironing rate.
 * Extends the {@link LaundryItem} class.
 *
 *
 *
 * @author Ferhat Kasim Koc
 * @version 23.0
 */
public class WetClean extends LaundryItem {

    /**
     * Default constructor initializing a wet cleaning item with default values.
     */
    public WetClean() {
        super("Unknown", 0, 0, "Unknown", null);
    }


    /**
     * Constructs a wet cleaning item with basic details.
     *
     * @param quantity The quantity of the laundry item.
     * @param price The price per unit of the laundry item.
     * @param assigned The employee assigned to process this laundry item.
     */
    public WetClean(int quantity, double price, Employee assigned) {
        super("Unknown", quantity, price, "Unknown", assigned);
    }


    /**
     * Constructs a wet cleaning item with full details.
     *
     * @param type The type of the laundry item (e.g., shirt, skirt).
     * @param quantity The quantity of the laundry item.
     * @param price The price per unit of the laundry item.
     * @param notes Any special notes about the laundry item.
     * @param assigned The employee assigned to process this laundry item.
     */
    public WetClean(String type, int quantity, double price, String notes, Employee assigned) {
        super(type, quantity, price, notes, assigned);
    }


    /**
     * Calculates the total cost of the wet cleaning item.
     * @return The total cost of the wet cleaning item.
     */
    @Override
    public double totalCost() {
        return (getQuantity() * getPrice() * waterRate) + (getQuantity() * ironingRate);
    }
}
