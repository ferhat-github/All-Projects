package dryclean.cyprusDryCleanData;

import dryclean.cyprusDryCleanApplication.CyprusDryClean;
import dryclean.cyprusDryCleanEntities.*;


import java.util.ArrayList;
import java.util.Date;

/**
 * This class is just created for producing some dummy data for our application CyprusDryClean.
 * It produces 3 employee and 4 customer instances(2 of them are subscribed and others are unsubscribed)
 * Each customer has one order that has 2 laundry items(one dry-clean one wet-clean)
 */
public class PopulateData {

    /**
     * Initializes the CyprusDryClean application with sample data.
     * @return A populated CyprusDryClean object.
     */
    public static CyprusDryClean initializeData() {
        ArrayList<Employee> employees = new ArrayList<>();
        ArrayList<Customer> customers = new ArrayList<>();

        // Creating dummy data for employee list
        employees.add(new Employee(1001, new Date(92, 4, 24), "Mustafa", "Olgun", new Date(118, 1, 1), "Turkish", new Date(125, 1, 1)));
        employees.add(new Employee(2002, new Date(88, 10, 10), "Buse", "Gezgin", new Date(120, 8, 5), "Cypriot", new Date(125, 8, 5)));
        employees.add(new Employee(3003, new Date(85, 7, 15), "Adriana", "Moldova", new Date(119, 11, 8), "Moldovan", new Date(125, 11, 8)));

        // Creating dummy data for customer list

        // Dummy Subscribed Customer 1
        Subscribed subscribedCustomer1 = new Subscribed(101, new Date(90, 1, 15), "Murat", "Atilgan", new Date(121, 2, 9), new Date(121, 2, 9), 100.0);
        Order order1 = new Order(new Date(123, 0, 15), true);
        order1.setLaundryItem(new DryClean("Shirt", 2, 5.0, "No starch", employees.get(0)));
        order1.setLaundryItem(new WetClean("Pants", 1, 7.0, "Light press", employees.get(1)));
        subscribedCustomer1.putOrder(order1);

        // Dummy Subscribed Customer 2
        Subscribed subscribedCustomer2 = new Subscribed(102, new Date(85, 9, 20), "Marlyn", "Williams", new Date(121, 9, 1), new Date(121, 9, 1), 80.0);
        Order order2 = new Order(new Date(123, 1, 10), false);
        order2.setLaundryItem(new DryClean("Jacket", 1, 10.0, "Dry clean only", employees.get(2)));
        order2.setLaundryItem(new WetClean("Blouse", 3, 4.0, "Delicate wash", employees.get(0)));
        subscribedCustomer2.putOrder(order2);

        // Dummy Unsubscribed Customer 1
        Unsubscribed unsubscribedCustomer1 = new Unsubscribed(103, new Date(95, 6, 30), "Carol", "Taylor", new Date(122, 6, 15));
        Order order3 = new Order(new Date(123, 2, 5), true);
        order3.setLaundryItem(new DryClean("Skirt", 2, 6.0, "No bleach", employees.get(1)));
        order3.setLaundryItem(new WetClean("Scarf", 1, 3.0, "Soft detergent", employees.get(2)));
        unsubscribedCustomer1.putOrder(order3);

        // Dummy Unsubscribed Customer 2
        Unsubscribed unsubscribedCustomer2 = new Unsubscribed(104, new Date(99, 4, 12), "John", "Smith", new Date(123, 3, 8));
        Order order4 = new Order(new Date(123, 3, 10), false);
        order4.setLaundryItem(new DryClean("Dress", 1, 15.0, "Steam only", employees.get(2)));
        order4.setLaundryItem(new WetClean("T-shirt", 5, 2.5, "Cold wash", employees.get(0)));
        unsubscribedCustomer2.putOrder(order4);


        customers.add(subscribedCustomer1);
        customers.add(subscribedCustomer2);
        customers.add(unsubscribedCustomer1);
        customers.add(unsubscribedCustomer2);



        CyprusDryClean populatedApplication = new CyprusDryClean(employees, customers);
        return populatedApplication;
    }
}
