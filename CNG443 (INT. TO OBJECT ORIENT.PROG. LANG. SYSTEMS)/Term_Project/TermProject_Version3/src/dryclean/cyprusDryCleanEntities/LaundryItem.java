package dryclean.cyprusDryCleanEntities;

import dryclean.cyprusDryCleanInterfaces.CleaningStyle;


/**
 * Represents a laundry item in an order.
 * Each laundry item has a type, quantity, price, notes, and an assigned employee for processing.
 * This is an abstract class that defines common properties for specific laundry items
 * such as dry cleaning or wet cleaning.
 * Implements the {@link CleaningStyle} interface.
 *
 *
 *
 * @author Ferhat Kasim Koc
 * @version 23.0
 */
public abstract class LaundryItem implements CleaningStyle {
    private String type;
    private int quantity;
    private double price;
    private String notes;
    private Employee assigned;


    /**
     * Default constructor initializing a laundry item with default values.
     */
    public LaundryItem() {
        this.type = "Unknown";
        this.quantity = 0;
        this.price = 0;
        this.notes = "Unknown";
        this.assigned = null;
    }


    /**
     * Constructs a laundry item with a specified quantity, price, and assigned employee.
     * @param quantity The quantity of the laundry item.
     * @param price The price per unit of the laundry item.
     * @param assigned The employee assigned to process this laundry item.
     */
    public LaundryItem(int quantity, double price, Employee assigned) {
        this.type = "Unknown";
        this.quantity = quantity;
        this.price = price;
        this.notes = "Unknown";
        this.assigned = assigned;
    }


    /**
     * Constructs a laundry item with full details.
     * @param type The type of the laundry item (e.g., shirt, skirt).
     * @param quantity The quantity of the laundry item.
     * @param price The price per unit of the laundry item.
     * @param notes Any special notes about the laundry item.
     * @param assigned The employee assigned to process this laundry item.
     */
    public LaundryItem(String type, int quantity, double price, String notes, Employee assigned) {
        this.type = type;
        this.quantity = quantity;
        this.price = price;
        this.notes = notes;
        this.assigned = assigned;
    }

    public String getType() {
        return type;
    }
    public void setType(String type) {
        this.type = type;
    }


    public int getQuantity() {
        return quantity;
    }
    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }


    public double getPrice() {
        return price;
    }
    public void setPrice(double price) {
        this.price = price;
    }


    public String getNotes() {
        return notes;
    }
    public void setNotes(String notes) {
        this.notes = notes;
    }


    public Employee getAssigned() {
        return assigned;
    }
    public void setAssigned(Employee assigned) {
        this.assigned = assigned;
    }



    /**
     * Gets the total cost of the laundry item.
     * This method must be implemented by subclasses to provide specific cost calculations.
     * @return The total cost of the laundry item.
     */
    public abstract double totalCost();


    @Override
    public String toString() {
        return "Laundry Item Type: " + type +
                ", Quantity: " + quantity +
                ", Price: " + price +
                ", Notes: " + notes +
                ", Assigned Employee: " + assigned.getName() + " " + assigned.getSurname();
    }

}
