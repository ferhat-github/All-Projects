package cyprusDryCleanData;

import cyprusDryCleanApplication.CyprusDryClean;
import cyprusDryCleanEntities.Employee;
import cyprusDryCleanEntities.LaundryItem;
import cyprusDryCleanEntities.Order;
import cyprusDryCleanEntities.Customer;

import java.util.ArrayList;
import java.util.Date;

/**
 * This class is just created for producing some dummy data for our application CyprusDryClean.
 * It produces 3 employee and 3 customer instances
 * Then it will assign an order to each customer with a laundry item
 */
public class PopulateData {

    /**
     * Initializes the CyprusDryClean application with sample data.
     * Creates three employees, three customers, and assigns an order with a laundry item to each customer.
     * @return A populated CyprusDryClean object.
     */
    public static CyprusDryClean initializeData() {

        // Creating dummy data for employee list
        ArrayList<Employee> employees = new ArrayList<>();
        employees.add(new Employee(1001, "Mustafa", "Olgun", new Date(92, 4, 24), new Date(118, 1, 1)));
        employees.add(new Employee(2002, "Buse", "Gezgin", new Date(88, 10, 10), new Date(120, 8, 5)));
        employees.add(new Employee(3003, "Adriana", "Moldova", new Date(85, 7, 15), new Date(119, 11, 8)));


        // Creating dummy data for customer list
        ArrayList<Customer> customers = new ArrayList<>();



        Customer customer1 = new Customer(101, "Murat", "Atilgan", new Date(121, 2, 9));
        Order order1 = new Order(new Date(121,2,9), true);
        order1.setLaundryItems(new LaundryItem("Shirt", 2, 5.0, "No starch", employees.get(0)));
        customer1.putOrder(order1);


        Customer customer2 = new Customer(102, "Marlyn", "Williams", new Date(121, 9, 1));
        Order order2 = new Order(new Date(121,9,1), false);
        order2.setLaundryItems(new LaundryItem("Pants", 1, 7.0, "Light press", employees.get(1)));
        customer2.putOrder(order2);


        Customer customer3 = new Customer(103, "Carol", "Taylor", new Date(121, 12, 6));
        Order order3 = new Order(new Date(121,12,6), true);
        order3.setLaundryItems(new LaundryItem("Jacket", 1, 10.0, "Dry clean only", employees.get(2)));
        customer3.putOrder(order3);



        customers.add(customer1);
        customers.add(customer2);
        customers.add(customer3);

        CyprusDryClean populatedApplication = new CyprusDryClean(employees, customers);

        return populatedApplication;
    }
}
