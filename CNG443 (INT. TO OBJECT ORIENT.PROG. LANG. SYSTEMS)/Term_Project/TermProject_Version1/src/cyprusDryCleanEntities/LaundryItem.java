package cyprusDryCleanEntities;


/**
 * This LaundryItem class represents a laundry item brought in by a customer for cleaning.
 * Each item includes details which are type, quantity, price,
 * notes, and the employee assigned to clean it.
 *
 *
 *
 * @author Ferhat Kasim Koc
 * @version 23.0
 */


public class LaundryItem {
    private String type;
    private int quantity;
    private double price;
    private String notes;
    private Employee assigned;  // Assigned employee for this item

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
     * This Constructor is initializing a laundry item with quantity, price, and assigned employee.
     * @param quantity the quantity of the item
     * @param priceOfItem the price per item
     * @param assignedEmployee the employee assigned to clean this item
     */
    public LaundryItem(int quantity, double priceOfItem, Employee assignedEmployee) {
        this.type = "Unknown";
        this.quantity = quantity;
        this.price = priceOfItem;
        this.notes = "Unknown";
        this.assigned = assignedEmployee;
    }


    /**
     * This Constructor is  initializing a laundry item with all fields.
     * @param type the type of item (e.g., shirt, skirt)
     * @param quantity the quantity of the item
     * @param priceOfItem the price per item
     * @param notes special notes about the item
     * @param assignedEmployee the employee assigned to handle this item
     */
    public LaundryItem(String type, int quantity, double priceOfItem, String notes, Employee assignedEmployee) {
        this.type = type;
        this.quantity = quantity;
        this.price = priceOfItem;
        this.notes = notes;
        this.assigned = assignedEmployee;
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


    public Employee getAssignedEmployee() {
        return assigned;
    }
    public void setAssignedEmployee(Employee assignedEmployee) {
        this.assigned = assignedEmployee;
    }

    /**
     * Calculates the total cost for the laundry item.
     * @return the total cost of the item (quantity * price per item)
     */
    public double totalCost() {
        return quantity * price;
    }


}
