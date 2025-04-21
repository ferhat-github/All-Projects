package dryclean.cyprusDryCleanApplication;

import dryclean.cyprusDryCleanData.PopulateData;
import dryclean.cyprusDryCleanEntities.*;
import dryclean.cyprusDryCleanInterfaces.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

/**
 * Manages the Cyprus Dry Clean application.
 * This class serves as the main controller for the application, integrating functionality
 * for managing employees, customers, orders.
 * It allows the user to perform various operations such as adding, deleting, and listing entities,
 * placing orders, calculating discounts, comparing customer loyalty, and maintaining health inspections.
 * The class also provides a menu-driven interface to allow users to interact with the application
 * through a series of options, enabling streamlined data management and operations.
 *
 *
 *
 * @author Ferhat Kasim Koc
 * @version 23.0
 */
public class CyprusDryClean {
    public ArrayList<Employee> employees;
    public ArrayList<Customer> customers;

    /**
     * Default Constructor for CyprusDryClean that initializes empty lists for employees and customers.
     */
    public CyprusDryClean() {
        employees = new ArrayList<>();
        customers = new ArrayList<>();
    }

    /**
     * Constructor that initializes the employee and customer lists with provided lists.
     * @param emp List of employees to initialize.
     * @param cst List of customers to initialize.
     */
    public CyprusDryClean(ArrayList<Employee> emp, ArrayList<Customer> cst) {
        employees = emp;
        customers = cst;
    }

    /**
     * Constructor that initializes employees with a provided list and customers as an empty list.
     * @param emp List of employees to initialize.
     */
    public CyprusDryClean(ArrayList<Employee> emp) {
        employees = emp;
        customers = new ArrayList<>();
    }




    /**
     * Main method that starts the application and presents the menu options.
     * It uses a loop to keep the menu open until the user chooses to exit.
     * @param args is Command line arguments but not used at this project
     */
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);


        CyprusDryClean cyprusDryCleanApplication = PopulateData.initializeData();

        int choice;


        while (true) {
            cyprusDryCleanApplication.menu();


            try {
                choice = input.nextInt();
                System.out.println();


                if (choice == 1) {
                    cyprusDryCleanApplication.addEmployee();
                } else if (choice == 2) {
                    System.out.print("Enter Employee ID to delete: ");
                    int employeeId = input.nextInt();
                    cyprusDryCleanApplication.deleteEmployee(employeeId);
                } else if (choice == 3) {
                    System.out.print("Enter Employee ID to view details: ");
                    int employeeId = input.nextInt();
                    cyprusDryCleanApplication.listEmployeeDetails(employeeId);
                } else if (choice == 4) {
                    cyprusDryCleanApplication.addCustomer();
                } else if (choice == 5) {
                    System.out.print("Enter Customer ID to delete: ");
                    int customerId = input.nextInt();
                    cyprusDryCleanApplication.deleteCustomer(customerId);
                } else if (choice == 6) {
                    System.out.print("Enter Customer ID to view details: ");
                    int customerId = input.nextInt();
                    cyprusDryCleanApplication.getCustomerDetails(customerId);
                } else if (choice == 7) {
                    System.out.print("Enter Customer ID to place an order: ");
                    int customerId = input.nextInt();
                    cyprusDryCleanApplication.putOrder(customerId);
                } else if (choice == 8) {
                    System.out.print("Enter Customer ID: ");
                    int customerId = input.nextInt();
                    System.out.print("Enter Order Date (dd/MM/yyyy): ");
                    String tmpDate = input.next();
                    Date orderDate = cyprusDryCleanApplication.parseDate(tmpDate);
                    if (orderDate != null) {
                        cyprusDryCleanApplication.getCustomerOrderDetails(customerId, orderDate);
                    }
                } else if (choice == 9) {
                    System.out.print("Enter Customer ID: ");
                    int customerId = input.nextInt();
                    System.out.print("Enter Order Date (dd/MM/yyyy): ");
                    String tmpDate = input.next();
                    Date orderDate = cyprusDryCleanApplication.parseDate(tmpDate);
                    if (orderDate != null) {
                        cyprusDryCleanApplication.getCustomerOrderTotalCost(customerId, orderDate);
                    }
                } else if (choice == 10) {
                    cyprusDryCleanApplication.listEmployees();
                } else if (choice == 11) {
                    cyprusDryCleanApplication.listCustomers();
                } else if (choice == 12) {
                    System.out.print("Enter Employee ID to add a health inspection: ");
                    int empID = input.nextInt();
                    input.nextLine(); // Consume newline
                    System.out.print("Enter the health inspection report: ");
                    String report = input.nextLine();
                    cyprusDryCleanApplication.addHealthInspection(empID, report);
                } else if (choice == 13) {
                    System.out.print("Enter the first customer ID: ");
                    int customerID1 = input.nextInt();
                    System.out.print("Enter the second customer ID: ");
                    int customerID2 = input.nextInt();
                    cyprusDryCleanApplication.compareCustomerLoyalty(customerID1, customerID2);
                } else if (choice == 14) {
                    cyprusDryCleanApplication.exit();

                } else {
                    System.out.println("Your choice is invalid! Please try again.");
                }
            }catch (InputMismatchException e){
                System.out.println("Please enter a valid number.");
                input.nextLine(); // Clear the invalid input
            }
        }

    }



    /**
     * Displays the main menu with available actions and asks the user to choose one.
     */
    public void menu() {

        System.out.println("\n\n----CyprusDryClean Management System----");
        System.out.println("1) Add Employee");
        System.out.println("2) Delete Employee");
        System.out.println("3) List Employee Details");
        System.out.println("4) Add Customer");
        System.out.println("5) Delete Customer");
        System.out.println("6) Get Customer Details");
        System.out.println("7) Put Order");
        System.out.println("8) Get Customer Order Details");
        System.out.println("9) Get Customer Order Total Cost");
        System.out.println("10) List Employees");
        System.out.println("11) List Customers");
        System.out.println("12) Add Health Inspection");
        System.out.println("13) Compare Customer Loyalty");
        System.out.println("14) Exit");
        System.out.print("Please select an option: ");

    }



    /**
     * Adds a new employee to the system by prompting for details.
     * Ensures that each employee has a unique ID.
     */
    public void addEmployee() {
        Scanner input = new Scanner(System.in);

        try {
            System.out.print("Enter Employee ID: ");
            int id = input.nextInt();
            input.nextLine(); // Consume newline

            if (findEmployeeById(id) != null) {
                System.out.println("Employee with the ID number " + id + " already exist.");
                return;
            }

            System.out.print("Enter Name: ");
            String name = input.nextLine();
            System.out.print("Enter Surname: ");
            String surname = input.nextLine();
            System.out.print("Enter Birth Date (dd/MM/yyyy): ");
            Date birthdayDate = parseDate(input.nextLine());
            System.out.print("Enter Starting Date (dd/MM/yyyy): ");
            Date startingDate = parseDate(input.nextLine());
            System.out.print("Enter Nationality: ");
            String nationality = input.nextLine();
            System.out.print("Enter Work Permit End Date (dd/MM/yyyy): ");
            Date workPermitEndDate = parseDate(input.nextLine());


            // With the help of this condition, we can check the validation of the dates.
            if (birthdayDate != null && startingDate != null && nationality != null && workPermitEndDate != null) {
                Employee newEmployee = new Employee(id, birthdayDate, name, surname, startingDate, nationality, workPermitEndDate);
                employees.add(newEmployee);
                System.out.println("Employee successfully added!");
            } else {
                System.out.println("Employee couldn't be added because the some of the date format is invalid! Try again.");
            }
        }catch(InputMismatchException e){
            System.out.println("Invalid input! Please use appropriate data types for each field.");
            input.nextLine();
        }

    }



    /**
     * Deletes an employee by their ID.
     * @param empId The unique ID of the employee to delete.
     */
    public void deleteEmployee(int empId) {

        Employee tmpDeletingEmployee = findEmployeeById(empId);


        //Checking whether there is an employee with the given ID number.
        if (tmpDeletingEmployee != null) {
            employees.remove(tmpDeletingEmployee);
            System.out.println("Employee deleted successfully.");
        }
        else {
            System.out.println("Employee with the ID number " + empId + " does not exist.");
        }
    }




    /**
     * Lists details of a specific employee.
     * @param empId The unique ID of the employee.
     */
    public void listEmployeeDetails(int empId) {

        Employee tmpDetailedEmployee = findEmployeeById(empId);

        //Checking whether there is an employee with the given ID number.
        if (tmpDetailedEmployee != null) {
            tmpDetailedEmployee.displayEmployeeDetails();
        }
        else {
            System.out.println("Employee with the ID number " + empId + " does not exist.");
        }
    }




    /**
     * Adds a new customer to the system by prompting for details.
     * The customer can be either subscribed or unsubscribed.
     */
    public void addCustomer() {
        Scanner input = new Scanner(System.in);

        System.out.print("Enter Customer ID: ");
        int id = input.nextInt();
        input.nextLine();

        // Checking whether there is a customer with the given ID number.
        if (findCustomerById(id) != null) {
            System.out.println("Customer with the ID number " + id + " already exist.");
            return;
        }

        System.out.print("Enter Name: ");
        String name = input.nextLine();
        System.out.print("Enter Surname: ");
        String surname = input.nextLine();
        System.out.print("Enter Date of Birth (dd/MM/yyyy): ");
        Date dateOfBirth = parseDate(input.nextLine());
        if (dateOfBirth == null) {
            System.out.println("Date Format is Invalid!");
            return;
        }

        Date registrationDate = new Date();

        System.out.print("Would you like to subscribe? (Enter true for Yes / false for No): ");
        boolean subscribeChoice = input.nextBoolean();

        if (subscribeChoice) {
            Date subscriptionDate = new Date();
            System.out.print("Enter deposit amount (minimum amount must be" + customerManagement.minDeposit + "): ");
            double depositPaid = input.nextDouble();
            input.nextLine(); // Consume newline

            while (depositPaid < customerManagement.minDeposit) {
                System.out.println("Deposit cannot be less than " + customerManagement.minDeposit + ". Please change the amount or enter -1 to return.");
                System.out.print("Enter deposit amount (minimum amount must be" + customerManagement.minDeposit + "): ");
                depositPaid = input.nextDouble();
                input.nextLine(); // Consume newline

                if (depositPaid < 0) {
                    return;
                }
            }

            Subscribed newSubscribedCustomer = new Subscribed(id, dateOfBirth, name, surname, registrationDate, subscriptionDate, depositPaid);
            customers.add(newSubscribedCustomer);
            System.out.println("Subscribed customer added successfully.");
        }
        else {
            Unsubscribed newUnsubscribedCustomer = new Unsubscribed(id, dateOfBirth, name, surname, registrationDate);
            customers.add(newUnsubscribedCustomer);
            System.out.println("Unsubscribed customer added successfully.");
        }

    }



    /**
     * Deletes a customer by their ID.
     * @param customerId The unique ID of the customer to delete.
     */
    public void deleteCustomer(int customerId) {

        Customer customerToDelete = findCustomerById(customerId);


        if (customerToDelete != null) {
            customers.remove(customerToDelete);
            System.out.println("Customer deleted successfully.");
        }
        else {
            System.out.println("Customer with the ID number " + customerId + " does not exist.");
        }
    }



    /**
     * Displays the details of a customer given their unique ID.
     * If the customer ID does not exist, an error message is displayed.
     * @param customerID The unique ID of the customer.
     */
    public void getCustomerDetails(int customerID) {
        Customer customer = findCustomerById(customerID);



        if (customer != null) {
            System.out.println("Customer Details:");
            System.out.println("ID: " + customer.getID());
            System.out.println("Name: " + customer.getName());
            System.out.println("Surname: " + customer.getSurname());
            System.out.println("Registration Date: " + customer.getRegistrationDate());
            System.out.println("Total Number of Orders: " + customer.getOrders().size());
        }
        else {
            System.out.println("Error: Customer with ID " + customerID + " does not exist.");
        }
    }






    /**
     * Creates an order for a specific customer by prompting for order details and assigns
     * laundry items to employees randomly.
     * @param customerId The unique ID of the customer placing the order.
     */
    public void putOrder(int customerId) {
        Scanner input = new Scanner(System.in);

        try {
            // Find the customer by ID
            Customer customer = findCustomerById(customerId);

            // Check if the customer exists
            if (customer == null) {
                System.out.println("Customer with the ID number " + customerId + " does not exist.");
                return;
            }

            System.out.print("Enter Ordering Date (dd/MM/yyyy): ");
            Date orderingDate = parseDate(input.nextLine());
            System.out.print("Is the order paid? (Enter true for paid, false for unpaid): ");
            boolean isPaid = input.nextBoolean();
            input.nextLine();

            Order newOrder = new Order(orderingDate, isPaid);


            System.out.print("How many different types of laundry do you have?: ");
            int differentTypes = input.nextInt();
            input.nextLine();

            for (int i = 1; i <= differentTypes; i++) {
                System.out.println("\nLaundry Item [" + i + "]");
                System.out.print("Enter type of item: ");
                String type = input.nextLine();
                System.out.print("Enter quantity: ");
                int quantity = input.nextInt();
                input.nextLine(); // Consume newline
                System.out.print("Enter price per item: ");
                double price = input.nextDouble();
                input.nextLine(); // Consume newline
                System.out.print("If you have any special note for this item please enter. Otherwise keep this part empty: ");
                String specialNote = input.nextLine();
                System.out.print("Do you want wet cleaning or dry cleaning? (wet/dry): ");
                String cleaningType = input.nextLine().trim().toLowerCase();

                Employee assignedEmployee = getRandomEmployee();

                LaundryItem laundryItem;
                if (cleaningType.equals("dry")) {
                    laundryItem = new DryClean(type, quantity, price, specialNote, assignedEmployee);
                } else if (cleaningType.equals("wet")) {
                    laundryItem = new WetClean(type, quantity, price, specialNote, assignedEmployee);
                } else {
                    System.out.println("Invalid cleaning type. Skipping this laundry item.");
                    continue;
                }

                newOrder.setLaundryItem(laundryItem);
                System.out.println("Laundry item added successfully and assigned to employee: " + assignedEmployee.getName() + " " + assignedEmployee.getSurname() + " " + assignedEmployee.getID());
            }

            customer.putOrder(newOrder);
            System.out.println("Order created successfully for customer ID " + customerId);
        }catch (InputMismatchException e) {
            System.out.println("Invalid input! Please ensure all fields are correctly filled.");
        }
    }





    /**
     * Shows all orders for a customer on a given date, with details about each laundry item.
     * @param customerId The unique ID of the customer.
     * @param orderDate The date to search for orders.
     */
    public void getCustomerOrderDetails(int customerId, Date orderDate) {

        try {
            Customer customer = findCustomerById(customerId);

            if (customer == null) {
                System.out.println("Customer with the ID number " + customerId + " does not exist.");
                return;
            }

            //Converting the Date into a String to compare them.
            SimpleDateFormat dateForm = new SimpleDateFormat("dd/MM/yyyy");
            String targetDate = dateForm.format(orderDate);
            ArrayList<Order> foundedOrders = new ArrayList<>();

            // Find all orders on the given date
            for (Order tmpOrder : customer.getOrders()) {
                String tmpOrderDate = dateForm.format(tmpOrder.getOrderDate());
                if (tmpOrderDate.equals(targetDate)) {
                    foundedOrders.add(tmpOrder);
                }
            }

            //Displaying details if there is an order that is founded
            if (foundedOrders.isEmpty()) {
                System.out.println("There is no orders found for the customer with the ID number " + customerId + " on this date: " + targetDate);
            } else {


                System.out.println("\nCustomer ID: " + customerId);
                System.out.println("Order Date: " + targetDate);
                System.out.println("Total Orders on Date: " + foundedOrders.size());


                for (Order tmpOrder : foundedOrders) {
                    System.out.println("\n*****Order Details*****");
                    if (tmpOrder.isPaidStatus()) {
                        System.out.println("Order is paid.");
                    } else {
                        System.out.println("Order is unpaid.");
                    }

                    System.out.println("Laundry Items;");

                    for (LaundryItem tmpItem : tmpOrder.getLaundryItems()) {
                        System.out.println("Type: " + tmpItem.getType() + ", Quantity: " + tmpItem.getQuantity());
                    }
                }
            }
        } catch (InputMismatchException e) {
            System.out.println("Invalid input! Please enter correct data types.");
        }
    }





    /**
     * Calculates and displays the total cost of all orders for a specific customer on a particular date.
     * @param customerId The unique ID of the customer.
     * @param orderDate The date to search for orders.
     */
    public void getCustomerOrderTotalCost(int customerId, Date orderDate) {

        try {
            Customer customer = findCustomerById(customerId);

            if (customer == null) {
                System.out.println("Customer with the ID number " + customerId + " does not exist.");
                return;
            }


            //Converting the Date into a String to compare them.
            SimpleDateFormat dateForm = new SimpleDateFormat("dd/MM/yyyy");
            String targetDate = dateForm.format(orderDate);
            ArrayList<Order> matchingOrders = new ArrayList<>();


            // Find all orders on the given date and calculate total cost
            for (Order tmpOrder : customer.getOrders()) {
                String tmpOrderDate = dateForm.format(tmpOrder.getOrderDate());
                if (tmpOrderDate.equals(targetDate)) {
                    matchingOrders.add(tmpOrder);
                }
            }


            //Displaying details if there is an order that is founded
            if (matchingOrders.isEmpty()) {
                System.out.println("There is no orders found for customer with the ID number " + customerId + " on this date: " + targetDate);
            } else {
                System.out.println("\nCustomer ID: " + customerId);
                System.out.println("Order Date: " + targetDate);
                System.out.println("Total Orders on Date: " + matchingOrders.size());

                // Display the total cost for each order
                for (Order tmpOrder : matchingOrders) {
                    System.out.println("\n*****Order Details*****");
                    if (tmpOrder.isPaidStatus()) {
                        System.out.println("Order is paid.");
                    } else {
                        System.out.println("Order is unpaid.");
                    }
                    System.out.println("Total Cost for this Order: " + (tmpOrder.totalOrderCost() * (1-customer.calculateDiscount())));
                }
            }
        }catch (InputMismatchException e) {
            System.out.println("Invalid input! Please enter the correct data.");
        }
    }






    /**
     * Lists all employees in the system and their all details.
     */
    public void listEmployees() {
        if (employees.isEmpty()) {
            System.out.println("No employees found!");
        }
        else {
            System.out.println("\n***Employee List***");
            for (Employee tmpEmp : employees) {
                tmpEmp.displayEmployeeDetails();
                System.out.println();
            }
        }
    }


    /**
     * Lists all customers in the system and their all details.
     */
    public void listCustomers() {
        if (customers.isEmpty()) {
            System.out.println("No customers found!");
        }
        else {
            System.out.println("\n***Customer List***");
            for (Customer tmpCst : customers) {
                tmpCst.displayCustomerDetails();
                System.out.println();
            }
        }
    }




    /**
     * Adds a health inspection report for a specific employee.
     * @param empID The unique ID of the employee.
     * @param inspectionReport The text of the health inspection report.
     */
    public void addHealthInspection(int empID, String inspectionReport) {
        Employee employee = findEmployeeById(empID);

        if (employee == null) {
            System.out.println("Employee with the ID number " + empID + " already exist.");
            return;
        }

        Date currentDate = new Date();
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");

        // Format the current date to only include day month and year
        String formattedCurrentDate = dateFormat.format(currentDate);

        // Check if an inspection for the same formatted date already exists
        for (Date inspectionDate : employee.getHealthInspection().keySet()) {
            String formattedInspectionDate = dateFormat.format(inspectionDate);
            if (formattedCurrentDate.equals(formattedInspectionDate)) {
                System.out.println("An inspection for this date already exists.");
                return;
            }
        }

        // Add the health inspection if no inspection exists for the current date
        employee.addHealthInspection(currentDate, inspectionReport);
        System.out.println("Health inspection added successfully.");
    }



    /**
     * Compares the loyalty of two customers based on their total order income.
     * @param customerID1 The ID of the first customer.
     * @param customerID2 The ID of the second customer.
     */
    public void compareCustomerLoyalty(int customerID1, int customerID2) {
        Customer customer1 = findCustomerById(customerID1);
        if (customer1 == null) {
            System.out.println("Customer with the ID number " + customerID1 + " does not exist.");
            return;
        }

        Customer customer2 = findCustomerById(customerID2);
        if (customer2 == null) {
            System.out.println("Customer with the ID number " + customerID2 + " does not exist.");
            return;
        }

        // Comparing customers by using the compareTo method
        int comparisonResult = customer1.compareTo(customer2);

        System.out.println("Result of Customer Loyalty:");
        if (comparisonResult > 0) {
            System.out.println("Customer " + customer1.getID() + ", " + customer1.getName() + ", " + customer1.getSurname() + " brings more income.");
        }
        else if (comparisonResult < 0) {
            System.out.println("Customer " + customer2.getID() + ", " + customer2.getName() + ", " + customer2.getSurname() + " brings more income.");
        }
        else {
            System.out.println("Both customers bring the same income.");
        }
    }



    /**
     * Finds an employee by their unique ID.
     * @param empId The unique ID of the employee.
     * @return The Employee object if found, or null if not found.
     */
    public Employee findEmployeeById(int empId) {
        for (Employee tmpEmp : employees) {
            if (tmpEmp.getID() == empId) {
                return tmpEmp;
            }
        }
        return null;
    }


    /**
     * Finds a customer by their unique ID.
     * @param customerId The unique ID of the customer.
     * @return The Customer object if found, or null if not found.
     */
    public Customer findCustomerById(int customerId) {
        for (Customer tmpCst : customers) {
            if (tmpCst.getID() == customerId) {
                return tmpCst;
            }
        }
        return null;
    }


    /**
     * Parses a date from a string in the format "dd/MM/yyyy".
     * @param date The string representing the date.
     * @return The parsed Date object if successful, or null if the format is incorrect.
     */
    public Date parseDate(String date) {

        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");

        try {
            return dateFormat.parse(date);
        }

        catch (ParseException e) {
            System.out.println("You entered an invalid date format. Please enter in this format dd/MM/yyyy.");
            return null;
        }
    }


    /**
     * Randomly selects an employee from the list to assign to a laundry item.
     * @return The randomly selected Employee.
     */
    public Employee getRandomEmployee() {
        Random random = new Random();
        int employeeNumber = random.nextInt(employees.size());
        return employees.get(employeeNumber);
    }


    /**
     * Exits the program gracefully with a goodbye message.
     */
    public void exit() {
        System.out.println("Exiting the program. Goodbye!");
        System.exit(0);
    }


}