package dryclean.cyprusDryCleanApplication;

import dryclean.cyprusDryCleanEntities.*;
import dryclean.cyprusDryCleanInterfaces.*;


import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.text.*;
import java.util.*;
import javax.swing.*;



/**
 * The main class for the CyprusDryClean management system.
 * This class is responsible for storing and managing all employees and customers
 * in the system. It provides the main functionality to read and write data to files
 * and integrates with the graphical user interface (GUI) for user interaction.
 *
 * The system allows:
 * - Adding, deleting, and listing employees and customers.
 * - Managing orders for customers.
 * - Storing data for employees, subscribed customers, and unsubscribed customers
 *   in separate files.
 * - Reading stored data from files when the system starts.
 *
 * The data files include:
 * - employee.dat: Stores all employee information.
 * - subscribed.dat: Stores details of customers who are subscribed.
 * - unsubscribed.dat: Stores details of customers who are not subscribed.
 *
 * This class works closely with the GUI class `CyprusDryCleanGraphicalUserInterface`,
 * which allows the user to interact with the system using buttons, menus, and forms.
 *
 * The `main` method initializes the application by starting the GUI.
 *
 *
 * @author Ferhat Kasim Koc
 * @version 23.0
 */


public class CyprusDryClean {
    public static ArrayList<Employee> employees = new ArrayList< >();
    public static ArrayList<Customer> customers = new ArrayList<>();

    //File Names
    private static String EMPLOYEE_FILE = "employee.dat";
    private static String SUBSCRIBED_FILE = "subscribed.dat";
    private static String UNSUBSCRIBED_FILE = "unsubscribed.dat";



    /**
     * Default Constructor for CyprusDryClean that initializes empty lists for employees and customers.
     */
    public CyprusDryClean() {
        employees = new ArrayList< >();
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





    public static class CyprusDryCleanGraphicalUserInterface {

        public CyprusDryCleanGraphicalUserInterface() {
            readEmployeeData();
            readSubscribedData();
            readUnsubscribedData();



            JFrame GUIframe = new JFrame("CyprusDryClean");
            GUIframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            GUIframe.setSize(500,500);

            JPanel GUIlayout = new JPanel(new GridLayout(15,1,5,5));
            GUIlayout.setOpaque(true);
            GUIlayout.setBackground(Color.WHITE);

            JLabel mainLabel = new JLabel("----CyprusDryClean Management System----",JLabel.CENTER);
            mainLabel.setFont(new Font("Arial", Font.BOLD, 16));
            GUIlayout.add(mainLabel);


            JMenuBar menuBar = new JMenuBar();
            JMenu fileMenu = new JMenu("File");
            menuBar.add(fileMenu);
            JMenuItem setDataFolderItem = new JMenuItem("Set Data Folder");
            fileMenu.add(setDataFolderItem);

            GUIframe.setJMenuBar(menuBar);



            JButton addEmployeeButton=new JButton("1) Add Employee");
            JButton deleteEmployeeButton=new JButton("2) Delete Employee");
            JButton listEmployeeDetailsButton=new JButton("3) List Employee Details");
            JButton addCustomerButton=new JButton("4) Add Customer");
            JButton deleteCustomerButton=new JButton("5) Delete Customer");
            JButton getCustomerDetailsButton=new JButton("6) Get Customer Details");
            JButton addOrderButton=new JButton("7) Put Order");
            JButton getCustomerOrderDetailButton=new JButton("8) Get Customer Order Details");
            JButton getTotalOrderCostButton=new JButton("9) Get Customer Order Total Cost");
            JButton listEmployeesButton=new JButton("10) List Employees");
            JButton listCustomersButton=new JButton("11) List Customers");
            JButton addHealthInspectionButton=new JButton("12) Add Health Inspection");
            JButton compareCustomerIncomeButton=new JButton("13) Compare Customer Loyalty");
            JButton exitButton=new JButton("14) Exit");



            GUIlayout.add(addEmployeeButton);
            GUIlayout.add(deleteEmployeeButton);
            GUIlayout.add(listEmployeeDetailsButton);
            GUIlayout.add(addCustomerButton);
            GUIlayout.add(deleteCustomerButton);
            GUIlayout.add(getCustomerDetailsButton);
            GUIlayout.add(addOrderButton);
            GUIlayout.add(getCustomerOrderDetailButton);
            GUIlayout.add(getTotalOrderCostButton);
            GUIlayout.add(listEmployeesButton);
            GUIlayout.add(listCustomersButton);
            GUIlayout.add(addHealthInspectionButton);
            GUIlayout.add(compareCustomerIncomeButton);
            GUIlayout.add(exitButton);


            GUIframe.add(GUIlayout);
            GUIframe.setVisible(true);





            setDataFolderItem.addActionListener(new ActionListener() {
                /**
                 * This function runs when the "Set Data Folder" menu item is clicked.
                 * It opens a folder chooser dialog for the user to pick a folder.
                 * The selected folder will be used to save or load data files.
                 *
                 * @param e the action event when the menu item is clicked
                 */
                public void actionPerformed(ActionEvent e) {
                    JFileChooser folderChooser = new JFileChooser();
                    folderChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);

                    int returnValue = folderChooser.showOpenDialog(null);
                    if (returnValue == JFileChooser.APPROVE_OPTION) {
                        File selectedFolder = folderChooser.getSelectedFile();

                        //Updating the path
                        String dataDirectory = selectedFolder.getAbsolutePath();
                        updateDataPaths(dataDirectory);

                        JOptionPane.showMessageDialog(null, "Data folder set to: " + dataDirectory, "Folder Selected", JOptionPane.INFORMATION_MESSAGE);
                    } else {
                        JOptionPane.showMessageDialog(null, "No folder selected.", "Warning", JOptionPane.WARNING_MESSAGE);
                    }
                }
            });





            addEmployeeButton.addActionListener(new ActionListener() {
                /**
                 * This function runs when the "Add Employee" button is clicked.
                 * It opens a new window where the user can enter details for a new employee.
                 * The details include ID, name, surname, birth date, start date, nationality,
                 * and the work permit end date.
                 * After the user fills in the details and clicks "Add Employee", the program
                 * will check if all the details are correct and add the employee to the system.
                 *
                 * @param e the action event that happens when the button is clicked
                 */
                public void actionPerformed(ActionEvent e) {
                    JFrame empFrame = new JFrame("Add Employee");
                    empFrame.setSize(400, 400);
                    empFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

                    JPanel empPanel = new JPanel(new GridLayout(8, 2, 10, 10));
                    empPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

                    // Form fields
                    empPanel.add(new JLabel("Employee ID:"));
                    JTextField empIDField = new JTextField();
                    empPanel.add(empIDField);

                    empPanel.add(new JLabel("Employee Name:"));
                    JTextField empNameField = new JTextField();
                    empPanel.add(empNameField);

                    empPanel.add(new JLabel("Employee Surname:"));
                    JTextField empSurnameField = new JTextField();
                    empPanel.add(empSurnameField);

                    empPanel.add(new JLabel("Employee Birth Date (dd/MM/yyyy):"));
                    JTextField empBirthdayField = new JTextField();
                    empPanel.add(empBirthdayField);

                    empPanel.add(new JLabel("Employee Start Date (dd/MM/yyyy):"));
                    JTextField empStartingDateField = new JTextField();
                    empPanel.add(empStartingDateField);

                    empPanel.add(new JLabel("Employee Nationality:"));
                    JTextField empNationalityField = new JTextField();
                    empPanel.add(empNationalityField);

                    empPanel.add(new JLabel("Employee Work Permit End Date (dd/MM/yyyy):"));
                    JTextField empWorkPermitField = new JTextField();
                    empPanel.add(empWorkPermitField);

                    JButton submitButton = new JButton("Add Employee");
                    empPanel.add(submitButton);

                    empFrame.add(empPanel);
                    empFrame.setVisible(true);


                    submitButton.addActionListener(new ActionListener() {
                        /**
                         * This function runs when the "Add Employee" button in the new window is clicked.
                         * It checks if the details entered by the user are correct.
                         * If the employee ID is already used or if some details are missing, it shows an error message.
                         * If all the details are correct, it creates a new employee and adds them to the system.
                         *
                         * @param e the action event that happens when the button is clicked
                         */
                        public void actionPerformed(ActionEvent e) {
                            try {
                                int id = Integer.parseInt(empIDField.getText());
                                String name = empNameField.getText().trim();
                                String surname = empSurnameField.getText().trim();
                                String nationality = empNationalityField.getText().trim();
                                Date birthDate = parseDate(empBirthdayField.getText().trim());
                                Date startDate = parseDate(empStartingDateField.getText().trim());
                                Date workPermitEndDate = parseDate(empWorkPermitField.getText().trim());

                                //Checking whether the ID is unique or not.
                                if (findEmployeeById(id) != null) {
                                    JOptionPane.showMessageDialog(empFrame, "Employee ID already exists!", "Error", JOptionPane.ERROR_MESSAGE);
                                    return;
                                }

                                if (name.isEmpty() || surname.isEmpty() || nationality.isEmpty() || birthDate == null || startDate == null || workPermitEndDate == null) {
                                    JOptionPane.showMessageDialog(empFrame, "Please fill in all parts correctly.", "Error", JOptionPane.ERROR_MESSAGE);
                                    return;
                                }


                                Employee tmpEmployee = new Employee(id, birthDate, name, surname, startDate, nationality, workPermitEndDate);
                                employees.add(tmpEmployee);

                                JOptionPane.showMessageDialog(empFrame, "Employee added successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                                writeEmployeeData();

                                empFrame.dispose();
                            } catch (NumberFormatException ex) {
                                JOptionPane.showMessageDialog(empFrame, "Invalid ID format. Please enter a numeric ID.", "Error", JOptionPane.ERROR_MESSAGE);
                            } catch (Exception ex) {
                                JOptionPane.showMessageDialog(empFrame, "An error occurred. Please check your inputs.", "Error", JOptionPane.ERROR_MESSAGE);
                            }
                        }
                    });
                }
            });






            deleteEmployeeButton.addActionListener(new ActionListener() {
                /**
                 * This function runs when the "Delete Employee" button is clicked.
                 * It opens a small window where the user can type the ID of the employee they want to delete.
                 * After the user enters the ID and clicks "Delete," the program checks if the employee exists.
                 * If the employee exists, they are removed from the system. If not, an error message is shown.
                 *
                 * @param e the action event that happens when the button is clicked
                 */
                public void actionPerformed(ActionEvent e) {
                    JFrame deleteFrame = new JFrame("Delete Employee");
                    deleteFrame.setSize(300, 200);
                    deleteFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

                    JPanel deletePanel = new JPanel(new GridLayout(3, 1, 10, 10));
                    deletePanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

                    deletePanel.add(new JLabel("Enter Employee ID:"));
                    JTextField idInput = new JTextField();
                    deletePanel.add(idInput);

                    JButton deleteBtn = new JButton("Delete");
                    deletePanel.add(deleteBtn);

                    deleteFrame.add(deletePanel);
                    deleteFrame.setVisible(true);

                    deleteBtn.addActionListener(new ActionListener() {
                        /**
                         * This function runs when the "Delete" button in the delete window is clicked.
                         * It checks if the entered employee ID is correct and if the employee exists.
                         * If the employee exists, they are removed from the system, and a success message is shown.
                         * If not, an error message is shown to the user.
                         *
                         * @param e the action event that happens when the delete button is clicked
                         */
                        public void actionPerformed(ActionEvent e) {
                            try {
                                int id = Integer.parseInt(idInput.getText().trim());

                                Employee employeeToRemove = findEmployeeById(id);
                                if (employeeToRemove == null) {
                                    JOptionPane.showMessageDialog(deleteFrame, "No employee with ID " + id + " found.", "Error", JOptionPane.ERROR_MESSAGE);
                                    return;
                                }

                                employees.remove(employeeToRemove);
                                JOptionPane.showMessageDialog(deleteFrame, "Employee deleted successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                                writeEmployeeData();
                                deleteFrame.dispose(); // Close the delete window
                            } catch (NumberFormatException ex) {
                                JOptionPane.showMessageDialog(deleteFrame, "Invalid ID. Please enter a numeric value.", "Error", JOptionPane.ERROR_MESSAGE);
                            } catch (Exception ex) {
                                JOptionPane.showMessageDialog(deleteFrame, "An error occurred. Please try again.", "Error", JOptionPane.ERROR_MESSAGE);
                            }
                        }
                    });
                }
            });



            listEmployeeDetailsButton.addActionListener(new ActionListener() {
                /**
                 * This function runs when the "List Employee Details" button is clicked.
                 * It opens a small window where the user can type the ID of the employee they want to see details for.
                 * After the user enters the ID and clicks "Show Details," the program checks if the employee exists.
                 * If the employee exists, their details are shown in a pop-up window. If not, an error message is shown.
                 *
                 * @param e the action event that happens when the button is clicked
                 */
                public void actionPerformed(ActionEvent e) {
                    JFrame detailsFrame = new JFrame("List Employee Details");
                    detailsFrame.setSize(300, 200);
                    detailsFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

                    JPanel detailsPanel = new JPanel(new GridLayout(3, 1, 10, 10));
                    detailsPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

                    detailsPanel.add(new JLabel("Enter Employee ID:"));
                    JTextField idInput = new JTextField();
                    detailsPanel.add(idInput);

                    JButton showBtn = new JButton("Show Details");
                    detailsPanel.add(showBtn);

                    detailsFrame.add(detailsPanel);
                    detailsFrame.setVisible(true);

                    showBtn.addActionListener(new ActionListener() {
                        /**
                         * This function runs when the "Show Details" button in the details window is clicked.
                         * It checks if the entered employee ID is correct and if the employee exists.
                         * If the employee exists, their details are shown using a pop-up message.
                         * If the employee does not exist, an error message is shown.
                         *
                         * @param e the action event that happens when the show button is clicked
                         */
                        public void actionPerformed(ActionEvent e) {
                            try {
                                int id = Integer.parseInt(idInput.getText().trim());

                                Employee foundEmployee = findEmployeeById(id);
                                if (foundEmployee == null) {
                                    JOptionPane.showMessageDialog(detailsFrame, "No employee with ID " + id + " found.", "Error", JOptionPane.ERROR_MESSAGE);
                                    return;
                                }

                                JOptionPane.showMessageDialog(detailsFrame, foundEmployee.toString(), "Employee Details", JOptionPane.INFORMATION_MESSAGE);
                            } catch (NumberFormatException ex) {
                                JOptionPane.showMessageDialog(detailsFrame, "Invalid ID. Please enter a numeric value.", "Error", JOptionPane.ERROR_MESSAGE);
                            } catch (Exception ex) {
                                JOptionPane.showMessageDialog(detailsFrame, "An error occurred. Please try again.", "Error", JOptionPane.ERROR_MESSAGE);
                            }
                        }
                    });
                }
            });






            addCustomerButton.addActionListener(new ActionListener() {
                /**
                 * This function runs when the "Add Customer" button is clicked.
                 * It opens a window where the user can type in details for a new customer.
                 * The user can add information like the customer's ID, name, surname, date of birth,
                 * and subscription status. If the subscription status is "Yes," the user can also enter a deposit amount.
                 * After the details are filled, the customer is added to the system when the "Submit" button is clicked.
                 *
                 * @param e the action event that happens when the button is clicked
                 */
                public void actionPerformed(ActionEvent e) {
                    JFrame customerFrame = new JFrame("Add Customer");
                    customerFrame.setSize(400, 500);
                    customerFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

                    JPanel customerPanel = new JPanel(new GridLayout(8, 2, 10, 10));
                    customerPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

                    customerPanel.add(new JLabel("Customer ID:"));
                    JTextField idInput = new JTextField();
                    customerPanel.add(idInput);

                    customerPanel.add(new JLabel("Customer Name:"));
                    JTextField nameInput = new JTextField();
                    customerPanel.add(nameInput);

                    customerPanel.add(new JLabel("Customer Surname:"));
                    JTextField surnameInput = new JTextField();
                    customerPanel.add(surnameInput);

                    customerPanel.add(new JLabel("Customer Date of Birth (dd/MM/yyyy):"));
                    JTextField dobInput = new JTextField();
                    customerPanel.add(dobInput);

                    customerPanel.add(new JLabel("Is Subscribed? (Yes/No):"));
                    JComboBox<String> subscriptionBox = new JComboBox<>(new String[]{"Yes", "No"});
                    customerPanel.add(subscriptionBox);

                    JLabel depositLabel = new JLabel("Deposit Amount:");
                    JTextField depositInput = new JTextField();
                    depositLabel.setVisible(false);
                    depositInput.setVisible(false);
                    customerPanel.add(depositLabel);
                    customerPanel.add(depositInput);

                    subscriptionBox.addActionListener(new ActionListener() {
                        /**
                         * This function checks the subscription status when the user selects "Yes" or "No."
                         * If the user selects "Yes," the deposit field is shown. If "No," the deposit field is hidden.
                         *
                         * @param e the action event that happens when the subscription box is changed
                         */
                        public void actionPerformed(ActionEvent e) {
                            boolean isSubscribed = subscriptionBox.getSelectedItem().equals("Yes");
                            depositLabel.setVisible(isSubscribed);
                            depositInput.setVisible(isSubscribed);
                            customerFrame.revalidate();
                            customerFrame.repaint();
                        }
                    });

                    JButton submitBtn = new JButton("Submit");
                    customerPanel.add(submitBtn);

                    customerFrame.add(customerPanel);
                    customerFrame.setVisible(true);

                    submitBtn.addActionListener(new ActionListener() {
                        /**
                         * This function runs when the "Submit" button is clicked.
                         * It checks if the entered details are correct and complete.
                         * If all details are valid, a new customer is added to the system.
                         * If the subscription is "Yes," the deposit is also validated.
                         *
                         * @param e the action event that happens when the submit button is clicked
                         */
                        public void actionPerformed(ActionEvent e) {
                            try {
                                int id = Integer.parseInt(idInput.getText());
                                String name = nameInput.getText().trim();
                                String surname = surnameInput.getText().trim();
                                Date dob = parseDate(dobInput.getText().trim());
                                boolean isSubscribed = subscriptionBox.getSelectedItem().equals("Yes");

                                if (findCustomerById(id) != null) {
                                    JOptionPane.showMessageDialog(customerFrame, "Customer ID already exists!", "Error", JOptionPane.ERROR_MESSAGE);
                                    return;
                                }

                                if (name.isEmpty() || surname.isEmpty() || dob == null) {
                                    JOptionPane.showMessageDialog(customerFrame, "Please fill in all parts correctly.", "Error", JOptionPane.ERROR_MESSAGE);
                                    return;
                                }

                                if (isSubscribed) {
                                    double deposit = Double.parseDouble(depositInput.getText());
                                    if (deposit < customerManagement.minDeposit) {
                                        JOptionPane.showMessageDialog(customerFrame, "Deposit must be at least " + customerManagement.minDeposit + ".", "Error", JOptionPane.ERROR_MESSAGE);
                                        return;
                                    }
                                    Subscribed newCustomer = new Subscribed(id, dob, name, surname, new Date(), new Date(), deposit);
                                    customers.add(newCustomer);
                                    writeSubscribedData();
                                } else {
                                    Unsubscribed newCustomer = new Unsubscribed(id, dob, name, surname, new Date());
                                    customers.add(newCustomer);
                                    writeUnsubscribedData();
                                }

                                JOptionPane.showMessageDialog(customerFrame, "Customer added successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                                customerFrame.dispose();
                            } catch (NumberFormatException ex) {
                                JOptionPane.showMessageDialog(customerFrame, "Invalid input! Ensure ID and deposit are numeric.", "Error", JOptionPane.ERROR_MESSAGE);
                            } catch (Exception ex) {
                                JOptionPane.showMessageDialog(customerFrame, "An error occurred. Please try again.", "Error", JOptionPane.ERROR_MESSAGE);
                            }
                        }
                    });
                }
            });



            deleteCustomerButton.addActionListener(new ActionListener() {
                /**
                 * This function runs when the "Delete Customer" button is clicked.
                 * It opens a small window where the user can type the ID of the customer they want to delete.
                 * After the user enters the ID and clicks "Delete," the program checks if the customer exists.
                 * If the customer exists, they are removed from the system. If not, an error message is shown.
                 *
                 * @param e the action event that happens when the button is clicked
                 */
                public void actionPerformed(ActionEvent e) {
                    JFrame deleteFrame = new JFrame("Delete Customer");
                    deleteFrame.setSize(300, 200);
                    deleteFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

                    JPanel deletePanel = new JPanel(new GridLayout(3, 1, 10, 10));
                    deletePanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

                    deletePanel.add(new JLabel("Enter Customer ID:"));
                    JTextField idInput = new JTextField();
                    deletePanel.add(idInput);

                    JButton deleteBtn = new JButton("Delete");
                    deletePanel.add(deleteBtn);

                    deleteFrame.add(deletePanel);
                    deleteFrame.setVisible(true);

                    deleteBtn.addActionListener(new ActionListener() {
                        /**
                         * This function runs when the "Delete" button in the delete window is clicked.
                         * It checks if the entered customer ID is correct and if the customer exists.
                         * If the customer exists, they are removed from the system, and a success message is shown.
                         * If the customer does not exist, an error message is shown.
                         *
                         * @param e the action event that happens when the delete button is clicked
                         */
                        public void actionPerformed(ActionEvent e) {
                            try {
                                int id = Integer.parseInt(idInput.getText().trim());

                                Customer customerToRemove = findCustomerById(id);
                                if (customerToRemove == null) {
                                    JOptionPane.showMessageDialog(deleteFrame, "No customer with ID " + id + " found.", "Error", JOptionPane.ERROR_MESSAGE);
                                    return;
                                }

                                customers.remove(customerToRemove);
                                JOptionPane.showMessageDialog(deleteFrame, "Customer deleted successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);

                                if(customerToRemove instanceof Subscribed) {
                                    writeSubscribedData();
                                }
                                else {
                                    writeUnsubscribedData();
                                }

                                deleteFrame.dispose(); // Close the delete window
                            } catch (NumberFormatException ex) {
                                JOptionPane.showMessageDialog(deleteFrame, "Invalid ID. Please enter a numeric value.", "Error", JOptionPane.ERROR_MESSAGE);
                            } catch (Exception ex) {
                                JOptionPane.showMessageDialog(deleteFrame, "An error occurred. Please try again.", "Error", JOptionPane.ERROR_MESSAGE);
                            }
                        }
                    });
                }
            });




            getCustomerDetailsButton.addActionListener(new ActionListener() {
                /**
                 * This function runs when the "Get Customer Details" button is clicked.
                 * It opens a small window where the user can type the ID of the customer they want to view details for.
                 * After the user enters the ID and clicks "Show Details," the program checks if the customer exists.
                 * If the customer exists, their details are shown in a pop-up window. If not, an error message is shown.
                 *
                 * @param e the action event that happens when the button is clicked
                 */
                public void actionPerformed(ActionEvent e) {
                    JFrame detailsFrame = new JFrame("Get Customer Details");
                    detailsFrame.setSize(300, 200);
                    detailsFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

                    JPanel detailsPanel = new JPanel(new GridLayout(3, 1, 10, 10));
                    detailsPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

                    detailsPanel.add(new JLabel("Enter Customer ID:"));
                    JTextField idInput = new JTextField();
                    detailsPanel.add(idInput);

                    JButton showBtn = new JButton("Show Details");
                    detailsPanel.add(showBtn);

                    detailsFrame.add(detailsPanel);
                    detailsFrame.setVisible(true);

                    showBtn.addActionListener(new ActionListener() {
                        /**
                         * This function runs when the "Show Details" button in the details window is clicked.
                         * It checks if the entered customer ID is correct and if the customer exists.
                         * If the customer exists, their details are shown using a pop-up message.
                         * If the customer does not exist, an error message is shown.
                         *
                         * @param e the action event that happens when the show button is clicked
                         */
                        public void actionPerformed(ActionEvent e) {
                            try {
                                int id = Integer.parseInt(idInput.getText().trim());

                                Customer foundCustomer = findCustomerById(id);
                                if (foundCustomer == null) {
                                    JOptionPane.showMessageDialog(detailsFrame, "No customer with ID " + id + " found.", "Error", JOptionPane.ERROR_MESSAGE);
                                    return;
                                }

                                JOptionPane.showMessageDialog(detailsFrame, foundCustomer.toString(), "Customer Details", JOptionPane.INFORMATION_MESSAGE);
                            } catch (NumberFormatException ex) {
                                JOptionPane.showMessageDialog(detailsFrame, "Invalid ID. Please enter a numeric value.", "Error", JOptionPane.ERROR_MESSAGE);
                            } catch (Exception ex) {
                                JOptionPane.showMessageDialog(detailsFrame, "An error occurred. Please try again.", "Error", JOptionPane.ERROR_MESSAGE);
                            }
                        }
                    });
                }
            });





            addOrderButton.addActionListener(new ActionListener() {
                /**
                 * This function runs when the "Add Order" button is clicked.
                 * It opens a window where the user can enter details for a new order.
                 * The user can add the customer ID, order date, and payment status.
                 * Laundry items can also be added to the order using a separate button.
                 * After all details are entered, the user can submit the order.
                 *
                 * @param e the action event that happens when the button is clicked
                 */
                public void actionPerformed(ActionEvent e) {
                    JFrame orderFrame = new JFrame("Put Order");
                    orderFrame.setSize(500, 600);
                    orderFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

                    JPanel orderPanel = new JPanel(new GridLayout(10, 2, 10, 10));
                    orderPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

                    orderPanel.add(new JLabel("Enter Customer ID:"));
                    JTextField customerIdInput = new JTextField();
                    orderPanel.add(customerIdInput);

                    orderPanel.add(new JLabel("Order Date (dd/MM/yyyy):"));
                    JTextField orderDateInput = new JTextField();
                    orderPanel.add(orderDateInput);

                    orderPanel.add(new JLabel("Is Paid?"));
                    JMenuBar paymentMenuBar = new JMenuBar();
                    JMenu paymentMenu = new JMenu("Select Payment Status");
                    JMenuItem paidItem = new JMenuItem("True");
                    JMenuItem unpaidItem = new JMenuItem("False");
                    paymentMenu.add(paidItem);
                    paymentMenu.add(unpaidItem);
                    paymentMenuBar.add(paymentMenu);
                    orderPanel.add(paymentMenuBar);

                    JButton addItemsBtn = new JButton("Add Laundry Items");
                    orderPanel.add(addItemsBtn);

                    JButton submitOrderBtn = new JButton("Submit Order");
                    orderPanel.add(submitOrderBtn);

                    orderFrame.add(orderPanel);
                    orderFrame.setVisible(true);

                    ArrayList<LaundryItem> laundryItems = new ArrayList<>();
                    final boolean[] isPaid = {false}; // Default value for payment status

                    paidItem.addActionListener(new ActionListener() {
                        /**
                         * This function sets the payment status to "True" when selected.
                         *
                         * @param e the action event that happens when "True" is selected
                         */
                        public void actionPerformed(ActionEvent e) {
                            isPaid[0] = true;
                            paymentMenu.setText("True");
                        }
                    });

                    unpaidItem.addActionListener(new ActionListener() {
                        /**
                         * This function sets the payment status to "False" when selected.
                         *
                         * @param e the action event that happens when "False" is selected
                         */
                        public void actionPerformed(ActionEvent e) {
                            isPaid[0] = false;
                            paymentMenu.setText("False");
                        }
                    });

                    addItemsBtn.addActionListener(new ActionListener() {
                        /**
                         * This function opens a new window for adding laundry items to the order.
                         * The user can enter details like item type, quantity, price, special notes, and cleaning type.
                         * After the details are added, the item is saved to the order.
                         *
                         * @param e the action event that happens when the "Add Laundry Items" button is clicked
                         */
                        public void actionPerformed(ActionEvent e) {
                            JFrame itemsFrame = new JFrame("Add Laundry Item");
                            itemsFrame.setSize(400, 400);
                            itemsFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

                            JPanel itemsPanel = new JPanel(new GridLayout(6, 2, 10, 10));
                            itemsPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

                            itemsPanel.add(new JLabel("Item Type:"));
                            JTextField itemTypeInput = new JTextField();
                            itemsPanel.add(itemTypeInput);

                            itemsPanel.add(new JLabel("Quantity:"));
                            JTextField quantityInput = new JTextField();
                            itemsPanel.add(quantityInput);

                            itemsPanel.add(new JLabel("Price per Item:"));
                            JTextField priceInput = new JTextField();
                            itemsPanel.add(priceInput);

                            itemsPanel.add(new JLabel("Special Notes:"));
                            JTextArea notesInput = new JTextArea(3, 20);
                            notesInput.setLineWrap(true);
                            notesInput.setWrapStyleWord(true);
                            JScrollPane notesScrollPane = new JScrollPane(notesInput);
                            itemsPanel.add(notesScrollPane);

                            itemsPanel.add(new JLabel("Cleaning Type (wet/dry):"));
                            JComboBox<String> cleaningTypeBox = new JComboBox<>(new String[]{"Wet", "Dry"});
                            itemsPanel.add(cleaningTypeBox);

                            JButton saveItemBtn = new JButton("Save Item");
                            itemsPanel.add(saveItemBtn);

                            itemsFrame.add(itemsPanel);
                            itemsFrame.setVisible(true);

                            saveItemBtn.addActionListener(new ActionListener() {
                                /**
                                 * This function saves the laundry item details to the order.
                                 * It checks the input fields and creates a new laundry item if all details are valid.
                                 *
                                 * @param e the action event that happens when the "Save Item" button is clicked
                                 */
                                public void actionPerformed(ActionEvent e) {
                                    try {
                                        String type = itemTypeInput.getText().trim();
                                        int quantity = Integer.parseInt(quantityInput.getText().trim());
                                        double price = Double.parseDouble(priceInput.getText().trim());
                                        String notes = notesInput.getText().trim();
                                        String cleaningType = cleaningTypeBox.getSelectedItem().toString();

                                        Employee assignedEmployee = getRandomEmployee();

                                        LaundryItem item;
                                        if ("Dry".equalsIgnoreCase(cleaningType)) {
                                            item = new DryClean(type, quantity, price, notes, assignedEmployee);
                                        } else {
                                            item = new WetClean(type, quantity, price, notes, assignedEmployee);
                                        }

                                        laundryItems.add(item);
                                        JOptionPane.showMessageDialog(itemsFrame, "Laundry item added successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                                        itemsFrame.dispose();
                                    } catch (NumberFormatException ex) {
                                        JOptionPane.showMessageDialog(itemsFrame, "Invalid input! Please enter numeric values for quantity and price.", "Error", JOptionPane.ERROR_MESSAGE);
                                    } catch (Exception ex) {
                                        JOptionPane.showMessageDialog(itemsFrame, "An error occurred. Please try again.", "Error", JOptionPane.ERROR_MESSAGE);
                                    }
                                }
                            });
                        }
                    });

                    submitOrderBtn.addActionListener(new ActionListener() {
                        /**
                         * This function submits the order with all the entered details and items.
                         * It validates the customer ID and order date before saving the order.
                         *
                         * @param e the action event that happens when the "Submit Order" button is clicked
                         */
                        public void actionPerformed(ActionEvent e) {
                            try {
                                int customerId = Integer.parseInt(customerIdInput.getText().trim());
                                Date orderDate = parseDate(orderDateInput.getText().trim());

                                Customer customer = findCustomerById(customerId);
                                if (customer == null) {
                                    JOptionPane.showMessageDialog(orderFrame, "Customer with ID " + customerId + " not found.", "Error", JOptionPane.ERROR_MESSAGE);
                                    return;
                                }

                                Order order = new Order(orderDate, isPaid[0]);
                                for (LaundryItem item : laundryItems) {
                                    order.setLaundryItem(item);
                                }
                                customer.putOrder(order);

                                JOptionPane.showMessageDialog(orderFrame, "Order added successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                                orderFrame.dispose();
                            } catch (NumberFormatException ex) {
                                JOptionPane.showMessageDialog(orderFrame, "Invalid input! Please check your entries.", "Error", JOptionPane.ERROR_MESSAGE);
                            } catch (Exception ex) {
                                JOptionPane.showMessageDialog(orderFrame, "An error occurred. Please try again.", "Error", JOptionPane.ERROR_MESSAGE);
                            }
                        }
                    });
                }
            });






            getCustomerOrderDetailButton.addActionListener(new ActionListener() {
                /**
                 * This function runs when the "Get Customer Order Details" button is clicked.
                 * It opens a window where the user can enter a customer ID and an order date.
                 * After entering the details, the user clicks "Show Orders" to view orders placed by the customer on the given date.
                 * If no orders are found or the customer does not exist, an error message is displayed.
                 *
                 * @param e the action event that happens when the button is clicked
                 */
                public void actionPerformed(ActionEvent e) {
                    JFrame detailsFrame = new JFrame("Get Customer Order Details");
                    detailsFrame.setSize(400, 300);
                    detailsFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

                    JPanel detailsPanel = new JPanel(new GridLayout(4, 2, 10, 10));
                    detailsPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

                    detailsPanel.add(new JLabel("Enter Customer ID:"));
                    JTextField customerIdInput = new JTextField();
                    detailsPanel.add(customerIdInput);

                    detailsPanel.add(new JLabel("Enter Order Date (dd/MM/yyyy):"));
                    JTextField orderDateInput = new JTextField();
                    detailsPanel.add(orderDateInput);

                    JButton showOrdersBtn = new JButton("Show Orders");
                    detailsPanel.add(showOrdersBtn);

                    detailsFrame.add(detailsPanel);
                    detailsFrame.setVisible(true);

                    showOrdersBtn.addActionListener(new ActionListener() {
                        /**
                         * This function runs when the "Show Orders" button is clicked.
                         * It checks if the entered customer ID and order date are valid.
                         * If the customer exists, it searches for orders placed on the given date and displays them.
                         * If no orders are found or an error occurs, an appropriate message is shown.
                         *
                         * @param e the action event that happens when the show button is clicked
                         */
                        public void actionPerformed(ActionEvent e) {
                            try {
                                int customerId = Integer.parseInt(customerIdInput.getText().trim());
                                Date orderDate = parseDate(orderDateInput.getText().trim());

                                Customer customer = findCustomerById(customerId);
                                if (customer == null) {
                                    JOptionPane.showMessageDialog(detailsFrame, "Customer with ID " + customerId + " not found.", "Error", JOptionPane.ERROR_MESSAGE);
                                    return;
                                }

                                SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
                                String targetDate = dateFormat.format(orderDate);
                                ArrayList<Order> matchingOrders = new ArrayList<>();

                                for (Order order : customer.getOrders()) {
                                    String orderDateStr = dateFormat.format(order.getOrderDate());
                                    if (targetDate.equals(orderDateStr)) {
                                        matchingOrders.add(order);
                                    }
                                }

                                if (matchingOrders.isEmpty()) {
                                    JOptionPane.showMessageDialog(detailsFrame, "No orders found for the given date.", "No Orders", JOptionPane.INFORMATION_MESSAGE);
                                } else {
                                    StringBuilder details = new StringBuilder();
                                    details.append("Customer ID: ").append(customerId).append("\n");
                                    details.append("Order Date: ").append(targetDate).append("\n");
                                    details.append("Total Orders: ").append(matchingOrders.size()).append("\n\n");

                                    for (Order order : matchingOrders) {
                                        details.append("***** Order Details *****\n");
                                        details.append("Paid Status: ").append(order.isPaidStatus() ? "Paid" : "Unpaid").append("\n");
                                        details.append("Laundry Items:\n");

                                        for (LaundryItem item : order.getLaundryItems()) {
                                            details.append("- Type: ").append(item.getType()).append(", Quantity: ").append(item.getQuantity()).append("\n");
                                        }
                                        details.append("\n");
                                    }

                                    JOptionPane.showMessageDialog(detailsFrame, details.toString(), "Order Details", JOptionPane.INFORMATION_MESSAGE);
                                }
                            } catch (NumberFormatException ex) {
                                JOptionPane.showMessageDialog(detailsFrame, "Invalid input! Please ensure Customer ID is numeric.", "Error", JOptionPane.ERROR_MESSAGE);
                            } catch (Exception ex) {
                                JOptionPane.showMessageDialog(detailsFrame, "An error occurred. Please try again.", "Error", JOptionPane.ERROR_MESSAGE);
                            }
                        }
                    });
                }
            });




            getTotalOrderCostButton.addActionListener(new ActionListener() {
                /**
                 * This function runs when the "Get Customer Order Total Cost" button is clicked.
                 * It opens a window where the user can enter a customer ID and an order date.
                 * After entering the details, the user clicks "Calculate Total Cost" to view the total cost of orders
                 * placed by the customer on the given date. The total cost includes any discounts applied.
                 *
                 * @param e the action event that happens when the button is clicked
                 */
                public void actionPerformed(ActionEvent e) {
                    JFrame costFrame = new JFrame("Get Customer Order Total Cost");
                    costFrame.setSize(400, 300);
                    costFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

                    JPanel costPanel = new JPanel(new GridLayout(4, 2, 10, 10));
                    costPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

                    costPanel.add(new JLabel("Enter Customer ID:"));
                    JTextField customerIdInput = new JTextField();
                    costPanel.add(customerIdInput);

                    costPanel.add(new JLabel("Enter Order Date (dd/MM/yyyy):"));
                    JTextField orderDateInput = new JTextField();
                    costPanel.add(orderDateInput);

                    JButton calculateBtn = new JButton("Calculate Total Cost");
                    costPanel.add(calculateBtn);

                    costFrame.add(costPanel);
                    costFrame.setVisible(true);

                    calculateBtn.addActionListener(new ActionListener() {
                        /**
                         * This function runs when the "Calculate Total Cost" button is clicked.
                         * It checks if the entered customer ID and order date are valid.
                         * If the customer exists and has orders on the given date, it calculates the total cost
                         * with discounts applied and displays the details. If no orders are found, a message is shown.
                         *
                         * @param e the action event that happens when the calculate button is clicked
                         */
                        public void actionPerformed(ActionEvent e) {
                            try {
                                int customerId = Integer.parseInt(customerIdInput.getText().trim());
                                Date orderDate = parseDate(orderDateInput.getText().trim());

                                Customer customer = findCustomerById(customerId);
                                if (customer == null) {
                                    JOptionPane.showMessageDialog(costFrame, "Customer with ID " + customerId + " not found.", "Error", JOptionPane.ERROR_MESSAGE);
                                    return;
                                }

                                SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
                                String targetDate = dateFormat.format(orderDate);
                                ArrayList<Order> matchingOrders = new ArrayList<>();

                                for (Order order : customer.getOrders()) {
                                    String orderDateStr = dateFormat.format(order.getOrderDate());
                                    if (targetDate.equals(orderDateStr)) {
                                        matchingOrders.add(order);
                                    }
                                }

                                if (matchingOrders.isEmpty()) {
                                    JOptionPane.showMessageDialog(costFrame, "No orders found for the given date.", "No Orders", JOptionPane.INFORMATION_MESSAGE);
                                } else {
                                    double totalCost = 0;
                                    for (Order order : matchingOrders) {
                                        totalCost += order.totalOrderCost();
                                    }

                                    double discount = customer.calculateDiscount();
                                    double discountedCost = totalCost * (1 - discount);

                                    StringBuilder details = new StringBuilder();
                                    details.append("Customer ID: ").append(customerId).append("\n");
                                    details.append("Order Date: ").append(targetDate).append("\n");
                                    details.append("Total Orders: ").append(matchingOrders.size()).append("\n");
                                    details.append("Original Cost: ").append(String.format("%.2f", totalCost)).append("\n");
                                    details.append("Discount: ").append(String.format("%.0f", discount * 100)).append("%\n");
                                    details.append("Discounted Cost: ").append(String.format("%.2f", discountedCost)).append("\n");

                                    JOptionPane.showMessageDialog(costFrame, details.toString(), "Total Cost", JOptionPane.INFORMATION_MESSAGE);
                                }
                            } catch (NumberFormatException ex) {
                                JOptionPane.showMessageDialog(costFrame, "Invalid input! Please ensure Customer ID is numeric.", "Error", JOptionPane.ERROR_MESSAGE);
                            } catch (Exception ex) {
                                JOptionPane.showMessageDialog(costFrame, "An error occurred. Please try again.", "Error", JOptionPane.ERROR_MESSAGE);
                            }
                        }
                    });
                }
            });






            listEmployeesButton.addActionListener(new ActionListener() {
                /**
                 * This function runs when the "List All Employees" button is clicked.
                 * It opens a window and shows all employees in a table format.
                 * The table includes details like ID, name, surname, date of birth, start date, nationality, and work permit end date.
                 *
                 * @param e the action event that happens when the button is clicked
                 */
                public void actionPerformed(ActionEvent e) {
                    JFrame employeeFrame = new JFrame("List All Employees");
                    employeeFrame.setSize(600, 400);
                    employeeFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

                    String[] columns = {"ID", "Name", "Surname", "Date of Birth", "Start Date", "Nationality", "Work Permit End Date"};

                    Object[][] employeeData = new Object[employees.size()][7];

                    for (int i = 0; i < employees.size(); i++) {
                        Employee emp = employees.get(i);
                        employeeData[i][0] = emp.getID();
                        employeeData[i][1] = emp.getName();
                        employeeData[i][2] = emp.getSurname();
                        employeeData[i][3] = new SimpleDateFormat("dd/MM/yyyy").format(emp.getDateOfBirth());
                        employeeData[i][4] = new SimpleDateFormat("dd/MM/yyyy").format(emp.getStartDate());
                        employeeData[i][5] = emp.getNationality();
                        employeeData[i][6] = new SimpleDateFormat("dd/MM/yyyy").format(emp.getWorkPermitEndDate());
                    }

                    JTable table = new JTable(employeeData, columns);
                    JScrollPane tableScrollPane = new JScrollPane(table);
                    table.setFillsViewportHeight(true);

                    employeeFrame.add(tableScrollPane);
                    employeeFrame.setVisible(true);
                }
            });






            listCustomersButton.addActionListener(new ActionListener() {
                /**
                 * This function runs when the "List All Customers" button is clicked.
                 * It opens a window and shows all customers in a table format.
                 * The table includes details like ID, name, surname, date of birth, registration date, subscription status, and deposit amount.
                 *
                 * @param e the action event that happens when the button is clicked
                 */
                public void actionPerformed(ActionEvent e) {
                    JFrame customerFrame = new JFrame("List All Customers");
                    customerFrame.setSize(600, 400);
                    customerFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

                    String[] columns = {"ID", "Name", "Surname", "Date of Birth", "Registration Date", "Subscription Status", "Deposit Paid"};

                    Object[][] customerData = new Object[customers.size()][7];

                    for (int i = 0; i < customers.size(); i++) {
                        Customer cust = customers.get(i);
                        customerData[i][0] = cust.getID();
                        customerData[i][1] = cust.getName();
                        customerData[i][2] = cust.getSurname();
                        customerData[i][3] = new SimpleDateFormat("dd/MM/yyyy").format(cust.getDateOfBirth());
                        customerData[i][4] = new SimpleDateFormat("dd/MM/yyyy").format(cust.getRegistrationDate());

                        if (cust instanceof Subscribed) {
                            customerData[i][5] = "Subscribed";
                            customerData[i][6] = ((Subscribed) cust).getDepositPaid();
                        } else {
                            customerData[i][5] = "Unsubscribed";
                            customerData[i][6] = "N/A";
                        }
                    }

                    JTable table = new JTable(customerData, columns);
                    JScrollPane tableScrollPane = new JScrollPane(table);
                    table.setFillsViewportHeight(true);

                    customerFrame.add(tableScrollPane);
                    customerFrame.setVisible(true);
                }
            });






            addHealthInspectionButton.addActionListener(new ActionListener() {
                /**
                 * This function runs when the "Add Health Inspection" button is clicked.
                 * It opens a window where the user can enter an employee ID and a health inspection report.
                 * After entering the details, the user clicks "Add Inspection" to save the health inspection.
                 * If the employee ID is invalid or an inspection for the current date already exists, an error is shown.
                 *
                 * @param e the action event that happens when the button is clicked
                 */
                public void actionPerformed(ActionEvent e) {
                    JFrame inspectionFrame = new JFrame("Add Health Inspection");
                    inspectionFrame.setSize(400, 300);
                    inspectionFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

                    JPanel inspectionPanel = new JPanel(new GridLayout(4, 2, 10, 10));
                    inspectionPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

                    inspectionPanel.add(new JLabel("Enter Employee ID:"));
                    JTextField employeeIdInput = new JTextField();
                    inspectionPanel.add(employeeIdInput);

                    inspectionPanel.add(new JLabel("Enter Health Inspection Report:"));
                    JTextField reportInput = new JTextField();
                    inspectionPanel.add(reportInput);

                    JButton saveBtn = new JButton("Add Inspection");
                    inspectionPanel.add(saveBtn);

                    inspectionFrame.add(inspectionPanel);
                    inspectionFrame.setVisible(true);

                    saveBtn.addActionListener(new ActionListener() {
                        /**
                         * This function runs when the "Add Inspection" button is clicked.
                         * It checks if the entered employee ID is valid and if a health inspection
                         * already exists for the current date. If all checks pass, the inspection is saved.
                         *
                         * @param e the action event that happens when the save button is clicked
                         */
                        public void actionPerformed(ActionEvent e) {
                            try {
                                int employeeId = Integer.parseInt(employeeIdInput.getText().trim());
                                String report = reportInput.getText().trim();

                                //Checking whether the ID is valid.
                                Employee employee = findEmployeeById(employeeId);
                                if (employee == null) {
                                    JOptionPane.showMessageDialog(inspectionFrame, "Employee with ID " + employeeId + " not found.", "Error", JOptionPane.ERROR_MESSAGE);
                                    return;
                                }

                                //Checking whether an inspection for the current date already exists
                                Date currentDate = new Date();
                                SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
                                String today = dateFormat.format(currentDate);

                                for (Date inspectionDate : employee.getHealthInspection().keySet()) {
                                    String inspectionDateStr = dateFormat.format(inspectionDate);
                                    if (today.equals(inspectionDateStr)) {
                                        JOptionPane.showMessageDialog(inspectionFrame, "An inspection for this date already exists.", "Error", JOptionPane.ERROR_MESSAGE);
                                        return;
                                    }
                                }

                                employee.addHealthInspection(currentDate, report);
                                JOptionPane.showMessageDialog(inspectionFrame, "Health inspection added successfully!", "Success", JOptionPane.INFORMATION_MESSAGE);
                                inspectionFrame.dispose();
                            } catch (NumberFormatException ex) {
                                JOptionPane.showMessageDialog(inspectionFrame, "Invalid input! Please ensure the Employee ID is numeric.", "Error", JOptionPane.ERROR_MESSAGE);
                            } catch (Exception ex) {
                                JOptionPane.showMessageDialog(inspectionFrame, "An error occurred. Please try again.", "Error", JOptionPane.ERROR_MESSAGE);
                            }
                        }
                    });
                }
            });





            compareCustomerIncomeButton.addActionListener(new ActionListener() {
                /**
                 * This function runs when the "Compare Customer Loyalty" button is clicked.
                 * It opens a window where the user can enter two customer IDs.
                 * After entering the IDs, the user clicks "Compare" to check which customer has brought more income.
                 * If either ID is invalid, an error message is shown.
                 *
                 * @param e the action event that happens when the button is clicked
                 */
                public void actionPerformed(ActionEvent e) {
                    JFrame compareFrame = new JFrame("Compare Customer Loyalty");
                    compareFrame.setSize(400, 300);
                    compareFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

                    JPanel comparePanel = new JPanel(new GridLayout(4, 2, 10, 10));
                    comparePanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

                    comparePanel.add(new JLabel("Enter First Customer ID:"));
                    JTextField customerId1Input = new JTextField();
                    comparePanel.add(customerId1Input);

                    comparePanel.add(new JLabel("Enter Second Customer ID:"));
                    JTextField customerId2Input = new JTextField();
                    comparePanel.add(customerId2Input);

                    JButton compareBtn = new JButton("Compare");
                    comparePanel.add(compareBtn);

                    compareFrame.add(comparePanel);
                    compareFrame.setVisible(true);

                    compareBtn.addActionListener(new ActionListener() {
                        /**
                         * This function runs when the "Compare" button is clicked.
                         * It checks if the entered customer IDs are valid and compares their income.
                         * A message shows the result of the comparison: which customer brought more income or if they are equal.
                         *
                         * @param e the action event that happens when the compare button is clicked
                         */
                        public void actionPerformed(ActionEvent e) {
                            try {
                                int customerId1 = Integer.parseInt(customerId1Input.getText().trim());
                                int customerId2 = Integer.parseInt(customerId2Input.getText().trim());

                                //Checking whether the both ID is exist.
                                Customer customer1 = findCustomerById(customerId1);
                                Customer customer2 = findCustomerById(customerId2);

                                if (customer1 == null) {
                                    JOptionPane.showMessageDialog(compareFrame, "Customer with ID " + customerId1 + " not found.", "Error", JOptionPane.ERROR_MESSAGE);
                                    return;
                                }
                                if (customer2 == null) {
                                    JOptionPane.showMessageDialog(compareFrame, "Customer with ID " + customerId2 + " not found.", "Error", JOptionPane.ERROR_MESSAGE);
                                    return;
                                }

                                //Comparing Incomes
                                int comparisonResult = customer1.compareTo(customer2);
                                StringBuilder resultMessage = new StringBuilder();
                                if (comparisonResult > 0) {
                                    resultMessage.append("Customer ").append(customer1.getID()).append(" (")
                                            .append(customer1.getName()).append(" ").append(customer1.getSurname())
                                            .append(") has brought more income.");
                                } else if (comparisonResult < 0) {
                                    resultMessage.append("Customer ").append(customer2.getID()).append(" (")
                                            .append(customer2.getName()).append(" ").append(customer2.getSurname())
                                            .append(") has brought more income.");
                                } else {
                                    resultMessage.append("Both customers have brought the same income.");
                                }

                                JOptionPane.showMessageDialog(compareFrame, resultMessage.toString(), "Comparison Result", JOptionPane.INFORMATION_MESSAGE);
                            } catch (NumberFormatException ex) {
                                JOptionPane.showMessageDialog(compareFrame, "Invalid input! Please ensure both Customer IDs are numeric.", "Error", JOptionPane.ERROR_MESSAGE);
                            } catch (Exception ex) {
                                JOptionPane.showMessageDialog(compareFrame, "An error occurred. Please try again.", "Error", JOptionPane.ERROR_MESSAGE);
                            }
                        }
                    });
                }
            });





            exitButton.addActionListener(new ActionListener() {
                /**
                 * This function runs when the "Exit" button is clicked and it terminates the program.
                 *
                 * @param e the action event that happens when the button is clicked
                 */
                public void actionPerformed(ActionEvent e) {
                    System.exit(0);

                }
            });

        }



    }





    /**
     * Finds an employee by their unique ID.
     * @param empId The unique ID of the employee.
     * @return The Employee object if found, or null if not found.
     */
    public static Employee findEmployeeById(int empId) {
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
    public static Customer findCustomerById(int customerId) {
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
    public static Date parseDate(String date) {

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
    public static Employee getRandomEmployee() {
        Random random = new Random();
        int employeeNumber = random.nextInt(employees.size());
        return employees.get(employeeNumber);
    }







    /**
     * This method saves all employees to a file named "employee.dat".
     * Each employee's details are written in the file one by one.
     */
    public static void writeEmployeeData() {
        try (DataOutputStream out = new DataOutputStream(new FileOutputStream(EMPLOYEE_FILE))) {
            for (Employee emp : employees) {
                out.writeInt(emp.getID());
                out.writeUTF(emp.getName());
                out.writeUTF(emp.getSurname());
                out.writeUTF(emp.getNationality());
                out.writeLong(emp.getDateOfBirth().getTime());
                out.writeLong(emp.getStartDate().getTime());
                out.writeLong(emp.getWorkPermitEndDate().getTime());
            }
        } catch (IOException e) {
            System.out.println("Error writing employee data: " + e.getMessage());
        }
    }

    /**
     * This method saves all subscribed customers to a file named "subscribed.dat".
     * It writes the details of only subscribed customers.
     */
    public static void writeSubscribedData() {
        try (DataOutputStream out = new DataOutputStream(new FileOutputStream(SUBSCRIBED_FILE))) {
            for (Customer cust : customers) {
                if (cust instanceof Subscribed) {
                    Subscribed sub = (Subscribed) cust;
                    out.writeInt(sub.getID());
                    out.writeUTF(sub.getName());
                    out.writeUTF(sub.getSurname());
                    out.writeLong(sub.getDateOfBirth().getTime());
                    out.writeLong(sub.getRegistrationDate().getTime());
                    out.writeLong(sub.getSubscriptionDate().getTime());
                    out.writeDouble(sub.getDepositPaid());
                }
            }
        } catch (IOException e) {
            System.out.println("Error writing subscribed customer data: " + e.getMessage());
        }
    }

    /**
     * This method saves all unsubscribed customers to a file named "unsubscribed.dat".
     * It writes the details of only unsubscribed customers.
     */
    public static void writeUnsubscribedData() {
        try (DataOutputStream out = new DataOutputStream(new FileOutputStream(UNSUBSCRIBED_FILE))) {
            for (Customer cust : customers) {
                if (cust instanceof Unsubscribed) {
                    out.writeInt(cust.getID());
                    out.writeUTF(cust.getName());
                    out.writeUTF(cust.getSurname());
                    out.writeLong(cust.getDateOfBirth().getTime());
                    out.writeLong(cust.getRegistrationDate().getTime());
                }
            }
        } catch (IOException e) {
            System.out.println("Error writing unsubscribed customer data: " + e.getMessage());
        }
    }

    /**
     * This method reads all employees from the file "employee.dat".
     * It adds each employee to the employees list.
     */
    public static void readEmployeeData() {
        try (DataInputStream in = new DataInputStream(new FileInputStream(EMPLOYEE_FILE))) {
            while (in.available() > 0) {
                int id = in.readInt();
                String name = in.readUTF();
                String surname = in.readUTF();
                String nationality = in.readUTF();
                Date dob = new Date(in.readLong());
                Date startDate = new Date(in.readLong());
                Date workPermitEnd = new Date(in.readLong());

                employees.add(new Employee(id, dob, name, surname, startDate, nationality, workPermitEnd));
            }
        } catch (IOException e) {
            System.out.println("Error reading employee data: " + e.getMessage());
        }
    }

    /**
     * This method reads all subscribed customers from the file "subscribed.dat".
     * It adds each subscribed customer to the customers list.
     */
    public static void readSubscribedData() {
        try (DataInputStream in = new DataInputStream(new FileInputStream(SUBSCRIBED_FILE))) {
            while (in.available() > 0) {
                int id = in.readInt();
                String name = in.readUTF();
                String surname = in.readUTF();
                Date dob = new Date(in.readLong());
                Date registrationDate = new Date(in.readLong());
                Date subscriptionDate = new Date(in.readLong());
                double deposit = in.readDouble();

                customers.add(new Subscribed(id, dob, name, surname, registrationDate, subscriptionDate, deposit));
            }
        } catch (IOException e) {
            System.out.println("Error reading subscribed customer data: " + e.getMessage());
        }
    }

    /**
     * This method reads all unsubscribed customers from the file "unsubscribed.dat".
     * It adds each unsubscribed customer to the customers list.
     */
    public static void readUnsubscribedData() {
        try (DataInputStream in = new DataInputStream(new FileInputStream(UNSUBSCRIBED_FILE))) {
            while (in.available() > 0) {
                int id = in.readInt();
                String name = in.readUTF();
                String surname = in.readUTF();
                Date dob = new Date(in.readLong());
                Date registrationDate = new Date(in.readLong());

                customers.add(new Unsubscribed(id, dob, name, surname, registrationDate));
            }
        } catch (IOException e) {
            System.out.println("Error reading unsubscribed customer data: " + e.getMessage());
        }
    }



    /**
     * Updates the file paths for employee, subscribed, and unsubscribed data files.
     * This method uses the provided directory path to construct the full paths for
     * the data files, ensuring that they are stored in the chosen folder.
     *
     * @param directoryPath The directory where the data files will be stored.
     */
    private static void updateDataPaths(String directoryPath) {
        EMPLOYEE_FILE = directoryPath + File.separator + "employee.dat";
        SUBSCRIBED_FILE = directoryPath + File.separator + "subscribed.dat";
        UNSUBSCRIBED_FILE = directoryPath + File.separator + "unsubscribed.dat";
    }



    public static void main(String[] args) {

        CyprusDryCleanGraphicalUserInterface gui = new CyprusDryCleanGraphicalUserInterface();

    }

}