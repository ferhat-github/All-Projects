package cyprusDryCleanApplication;

import cyprusDryCleanData.PopulateData;
import cyprusDryCleanEntities.Employee;
import cyprusDryCleanEntities.LaundryItem;
import cyprusDryCleanEntities.Order;
import cyprusDryCleanEntities.Customer;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;
import java.util.Random;



/**
 * The CyprusDryClean class manages a dry cleaning company's operations, including adding employees and customers,
 * processing orders, and listing details. It provides methods for adding, deleting, and listing employees and
 * customers, as well as managing orders and calculating costs for a customer on a given date.
 * This class is the main hub of the application, containing various helper methods for handling the main tasks needed by the company.
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
            choice = input.nextInt();
            System.out.println();

            if (choice == 1) {
                cyprusDryCleanApplication.addEmployee();
            }
            else if (choice == 2) {
                System.out.print("Enter Employee ID to delete: ");
                int employeeId = input.nextInt();
                cyprusDryCleanApplication.deleteUser(employeeId);
            }
            else if (choice == 3) {
                System.out.print("Enter Employee ID to view details: ");
                int employeeId = input.nextInt();
                cyprusDryCleanApplication.listEmployeeDetails(employeeId);
            }
            else if (choice == 4) {
                cyprusDryCleanApplication.addCustomer();
            }
            else if (choice == 5) {
                System.out.print("Enter Customer ID to delete: ");
                int customerId = input.nextInt();
                cyprusDryCleanApplication.deleteCustomer(customerId);
            }
            else if (choice == 6) {
                System.out.print("Enter Customer ID to view details: ");
                int customerId = input.nextInt();
                cyprusDryCleanApplication.getCustomerDetails(customerId);
            }
            else if (choice == 7) {
                System.out.print("Enter Customer ID to place an order: ");
                int customerId = input.nextInt();
                cyprusDryCleanApplication.putOrder(customerId);
            }
            else if (choice == 8) {
                System.out.print("Enter Customer ID: ");
                int customerId = input.nextInt();
                System.out.print("Enter Order Date (dd/MM/yyyy): ");
                String tmpDate = input.next();
                Date orderDate = cyprusDryCleanApplication.parseDate(tmpDate);
                if (orderDate != null) {
                    cyprusDryCleanApplication.getCustomerOrderDetails(customerId, orderDate);
                }
            }
            else if (choice == 9) {
                System.out.print("Enter Customer ID: ");
                int customerId = input.nextInt();
                System.out.print("Enter Order Date (dd/MM/yyyy): ");
                String tmpDate = input.next();
                Date orderDate = cyprusDryCleanApplication.parseDate(tmpDate);
                if (orderDate != null) {
                    cyprusDryCleanApplication.getCustomerOrderTotalCost(customerId, orderDate);
                }
            }
            else if (choice == 10) {
                cyprusDryCleanApplication.listEmployees();
            }
            else if (choice == 11) {
                cyprusDryCleanApplication.listCustomers();
            }
            else if (choice == 12) {
                cyprusDryCleanApplication.exit();
            }
            else {
                System.out.println("Your choice is invalid! Please try again.");
            }
        }

    }




    /**
     * Displays the main menu with available actions and asks the user to choose one.
     */
    public void menu() {

        System.out.println("\n\n-----CyprusDryClean-----");
        System.out.println("1) Add Employee");
        System.out.println("2) Delete Employee");
        System.out.println("3) List Employee Details");
        System.out.println("4) Add Customer");
        System.out.println("5) Delete Customer");
        System.out.println("6) Get Customer Details");
        System.out.println("7) Put Order");
        System.out.println("8) Get Customer Order Details");
        System.out.println("9) Get Customer Order Total Cost");
        System.out.println("10) List All Employees");
        System.out.println("11) List All Customers");
        System.out.println("12) Exit");
        System.out.print("Select an option: ");

    }


    /**
     * Adds a new employee to the system by prompting for details.
     * Ensures that each employee has a unique ID.
     */
    public void addEmployee() {

        Scanner input = new Scanner(System.in);
        System.out.print("Enter Employee ID: ");
        int id = input.nextInt();
        input.nextLine();

        //This loop will help us to check whether there is an employee with the given ID.
        for (Employee tmpEmployee : employees) {
            if (tmpEmployee.getEmployeeId() == id) {
                System.out.println("Employee with the ID number " + id + " already exist.");
                return;
            }
        }



        System.out.print("Enter Name: ");
        String name = input.nextLine();
        System.out.print("Enter Surname: ");
        String surname = input.nextLine();
        System.out.print("Enter Birth Date (dd/MM/yyyy): ");
        Date birthdayDate = parseDate(input.nextLine());
        System.out.print("Enter Starting Date (dd/MM/yyyy): ");
        Date startingDate = parseDate(input.nextLine());

        // With the help of this condition, we can check the validation of the dates.
        if (birthdayDate != null && startingDate != null) {
            Employee newEmployee = new Employee(id, name, surname, birthdayDate, startingDate);
            employees.add(newEmployee);
            System.out.println("Employee successfully added!");
        }
        else {
            System.out.println("Employee couldn't be added because the date format is invalid! Try again.");
        }
    }



    /**
     * Deletes an employee by their ID.
     * @param empId The unique ID of the employee to delete.
     */
    public void deleteUser(int empId) {

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
     * Lists details of a specific employee, including ID, name, surname, and dates.
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
     * The customer's registration date is set to the current date.
     */
    public void addCustomer() {

        Scanner input = new Scanner(System.in);
        System.out.print("Enter Customer ID: ");
        int customerId = input.nextInt();
        input.nextLine();


        // Checking whether there is a customer with the given ID number.
        for (Customer cust : customers) {
            if (cust.getCustomerId() == customerId) {
                System.out.println("Customer with the ID number " + customerId + " already exist.");
                return;
            }
        }



        System.out.print("Enter Name: ");
        String name = input.nextLine();
        System.out.print("Enter Surname: ");
        String surname = input.nextLine();
        Date registrationDate = new Date();


        Customer newCustomer = new Customer(customerId, name, surname, registrationDate);
        customers.add(newCustomer);
        System.out.println("Customer successfully added!");
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
     * Retrieves and displays details of a specific customer.
     * @param customerId The unique ID of the customer.
     */
    public void getCustomerDetails(int customerId) {
        Customer customer = findCustomerById(customerId);

        if (customer != null) {
            customer.displayCustomerDetails();
        }
        else {
            System.out.println("Customer with the ID number " + customerId + " does not exist.");
        }
    }



    /**
     * Creates an order for a specific customer by prompting for order details and assigns
     * laundry items to employees randomly.
     * @param customerId The unique ID of the customer placing the order.
     */
    public void putOrder(int customerId) {

        Scanner input = new Scanner(System.in);
        Customer customer = findCustomerById(customerId);

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


        for (int i = 0; i < differentTypes; i++) {

            System.out.println("\nLaundry Item [" + (i + 1) + "]");
            System.out.print("Enter type of item: ");
            String type = input.nextLine();
            System.out.print("Enter quantity: ");
            int quantity = input.nextInt();
            System.out.print("Enter price per item: ");
            double pricePerItem = input.nextDouble();
            input.nextLine();
            System.out.print("If you have any special note for this item please enter. Otherwise keep this part empty: ");
            String specialNote = input.nextLine();

            Employee assignedEmployee = getRandomEmployee();

            // Create a new LaundryItem and add it to the order
            LaundryItem newLaundryItem = new LaundryItem(type, quantity, pricePerItem, specialNote, assignedEmployee);
            newOrder.setLaundryItems(newLaundryItem);
            System.out.println("Laundry item is added and it is assigned to the employee with the ID number " + assignedEmployee.getEmployeeId());
        }

        customer.putOrder(newOrder);
        System.out.println("Order created successfully and added to customer ID: " + customerId);
    }




    /**
     * Shows all orders for a customer on a given date, with details about each laundry item.
     * @param customerId The unique ID of the customer.
     * @param orderDate The date to search for orders.
     */
    public void getCustomerOrderDetails(int customerId, Date orderDate) {

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
        }
        else {


            System.out.println("\nCustomer ID: " + customerId);
            System.out.println("Order Date: " + targetDate);
            System.out.println("Total Orders on Date: " + foundedOrders.size());


            for (Order tmpOrder : foundedOrders) {
                System.out.println("\n*****Order Details*****");
                if(tmpOrder.isPaid()) {
                    System.out.println("Order is paid.");
                }
                else {
                    System.out.println("Order is unpaid.");
                }

                System.out.println("Laundry Items;");

                for (LaundryItem tmpItem : tmpOrder.getLaundryItems()) {
                    System.out.println("Type: " + tmpItem.getType() + ", Quantity: " + tmpItem.getQuantity());
                }
            }
        }
    }




    /**
     * Calculates and displays the total cost of all orders for a specific customer on a particular date.
     * @param customerId The unique ID of the customer.
     * @param orderDate The date to search for orders.
     */
    public void getCustomerOrderTotalCost(int customerId, Date orderDate) {

        Customer customer = findCustomerById(customerId);

        if (customer == null) {
            System.out.println("Customer with the ID number " + customerId + " does not exist.");
            return;
        }



        //Converting the Date into a String to compare them.
        SimpleDateFormat dateForm = new SimpleDateFormat("dd/MM/yyyy");
        String targetDate = dateForm.format(orderDate);
        ArrayList<Order> matchingOrders = new ArrayList<>();


        double totalCost = 0.0;
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
        }
        else {
            System.out.println("\nCustomer ID: " + customerId);
            System.out.println("Order Date: " + targetDate);
            System.out.println("Total Orders on Date: " + matchingOrders.size());

            // Display the total cost for each order
            for (Order tmpOrder : matchingOrders) {
                System.out.println("\n*****Order Details*****");
                if(tmpOrder.isPaid()) {
                    System.out.println("Order is paid.");
                }
                else {
                    System.out.println("Order is unpaid.");
                }
                System.out.println("Total Cost for this Order: " + tmpOrder.totalOrderCost());
            }
        }
    }





    /**
     * Lists all employees in the system and their details.
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
     * Lists all customers in the system and their details.
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
     * Exits the program gracefully with a goodbye message.
     */
    public void exit() {
        System.out.println("Exiting the program. Goodbye!");
        System.exit(0);
    }




    /**
     * Finds an employee by their unique ID.
     * @param empId The unique ID of the employee.
     * @return The Employee object if found, or null if not found.
     */
    public Employee findEmployeeById(int empId) {
        for (Employee tmpEmp : employees) {
            if (tmpEmp.getEmployeeId() == empId) {
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
            if (tmpCst.getCustomerId() == customerId) {
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

}

