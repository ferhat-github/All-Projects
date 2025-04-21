package dryclean.cyprusDryCleanEntities;


import java.util.ArrayList;
import java.util.Date;

/**
 * Represents an order placed by a customer.
 * An order consists of multiple laundry items and includes details like the order date and payment status.
 *
 *
 *
 * @author Ferhat Kasim Koc
 * @version 23.0
 */
public class Order {
    private Date orderDate;
    private boolean paidStatus;
    private ArrayList<LaundryItem> itemList;



    /**
     * Default constructor initializing an order with the current date and unpaid status.
     */
    public Order() {
        this.orderDate = new Date();  // Set to current date by default
        this.paidStatus = false;
        this.itemList = new ArrayList<>();
    }

    /**
     * Constructor that lets you set the order date.
     * By default, the order is marked as unpaid.
     * @param orderDate the date when the order was placed
     */
    public Order(Date orderDate) {
        this.orderDate = orderDate;
        this.paidStatus = false;
        this.itemList = new ArrayList<>();
    }



    /**
     * Constructs an order with a specific date and payment status.
     * @param orderDate The date when the order was placed.
     * @param paidStatus The payment status of the order.
     */
    public Order(Date orderDate, boolean paidStatus) {
        this.orderDate = orderDate;
        this.paidStatus = paidStatus;
        this.itemList = new ArrayList<>();
    }

    public Date getOrderDate() {
        return orderDate;
    }
    public void setOrderDate(Date orderDate) {
        this.orderDate = orderDate;
    }


    public boolean isPaidStatus() {
        return paidStatus;
    }
    public void setPaidStatus(boolean paidStatus) {
        this.paidStatus = paidStatus;
    }


    public ArrayList<LaundryItem> getLaundryItems() {
        return itemList;
    }
    public void setLaundryItem(LaundryItem item) {
        this.itemList.add(item);
    }


    /**
     * Calculates the total cost of the order based on the laundry items.
     * @return The total cost of the order.
     */
    public double totalOrderCost() {
        double totalCost = 0.0;
        for (LaundryItem item : itemList) {
            totalCost += item.totalCost();
        }
        return totalCost;
    }


    @Override
    public String toString() {
        StringBuilder itemsDetails = new StringBuilder();
        for (LaundryItem item : itemList) {
            itemsDetails.append(item.toString()).append("; ");
        }
        return "Order Date: " + orderDate +
                ", Paid Status: " + (paidStatus ? "Paid" : "Not Paid") +
                ", Laundry Items: " + itemsDetails;
    }


}
