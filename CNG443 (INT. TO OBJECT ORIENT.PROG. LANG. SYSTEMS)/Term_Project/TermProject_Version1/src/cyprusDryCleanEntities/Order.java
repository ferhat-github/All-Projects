package cyprusDryCleanEntities;



import java.util.ArrayList;
import java.util.Date;

/**
 * This Order Class represents an order placed by a customer, which keeps track
 * of the order date, payment status, and items within the order.
 * It helps organize all laundry items for a single customer order.
 *
 *
 *
 * @author Ferhat Kasim Koc
 * @version 23.0
 */


public class Order {
    private Date orderDate;
    private boolean isPaid;
    private ArrayList<LaundryItem> itemList;  // List of laundry items for the order


    /**
     * Default constructor that sets up an order with the current date
     * and marks it as unpaid. An empty list is also created for laundry items.
     */
    public Order() {
        this.orderDate = new Date();  // Set to current date by default
        this.isPaid = false;
        this.itemList = new ArrayList<>();
    }

    /**
     * Constructor that lets you set the order date.
     * By default, the order is marked as unpaid.
     * @param orderDate the date when the order was placed
     */
    public Order(Date orderDate) {
        this.orderDate = orderDate;
        this.isPaid = false;
        this.itemList = new ArrayList<>();
    }

    /**
     * Constructor that allows setting both the order date and payment status.
     * @param orderDate the date when the order was placed
     * @param isPaid true if the order is paid, false if not
     */
    public Order(Date orderDate, boolean isPaid) {
        this.orderDate = orderDate;
        this.isPaid = isPaid;
        this.itemList = new ArrayList<>();
    }


    public Date getOrderDate() {
        return orderDate;
    }
    public void setOrderDate(Date orderDate) {
        this.orderDate = orderDate;
    }


    public boolean isPaid() {
        return isPaid;
    }
    public void setPaid(boolean paid) {
        isPaid = paid;
    }


    public ArrayList<LaundryItem> getLaundryItems() {
        return itemList;
    }
    public void setLaundryItems(LaundryItem item) {
        itemList.add(item);
    }



    /**
     * Calculates the total cost for this order by summing up the cost of each item.
     * @return the total cost of all laundry items in the order
     */
    public double totalOrderCost() {
        double total = 0;
        for (LaundryItem item : itemList) {
            total += item.totalCost();
        }
        return total;
    }

}
