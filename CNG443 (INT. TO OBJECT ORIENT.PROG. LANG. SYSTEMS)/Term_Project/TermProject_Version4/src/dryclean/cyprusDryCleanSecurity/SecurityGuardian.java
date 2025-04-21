package dryclean.cyprusDryCleanSecurity;


import javax.swing.*;
import java.io.*;
import java.security.MessageDigest;


/**
 * The SecurityGuardian class checks if the customer data has been changed by someone.
 * It reads the saved customer data file and its hash file, and then compares them.
 * If the hash values are different, it shows a warning message.
 * This class uses threads to run the security check while the program is running.
 *
 * @author Ferhat Kasim Koc
 * @version 23.0
 */
public class SecurityGuardian extends Thread {

    //The file path name that stores customer data
    private String customerFileName;
    // The file path name that stores the hash (MD5) of the customer data
    private String hashFileName;


    /**
     * This is a constructor which creates a SecurityGuardian object with the paths for the customer and hash files.
     *
     * @param cstFileName the file path where customer data is stored
     * @param hashFilePath the file path where the hash of the customer data is stored
     */
    public SecurityGuardian(String cstFileName, String hashFilePath) {
        this.customerFileName = cstFileName;
        this.hashFileName = hashFilePath;
    }

    /**
     * This method starts the thread and checks if customer data is changed.
     * It compares the stored hash with the newly generated hash from the customer data file.
     */
    @Override
    public void run() {
        try {
            String tmpHashRecovered = MD5_Creator();
            String storedHash = hashFileReader();

            if (!tmpHashRecovered.equals(storedHash)) {
                JOptionPane.showMessageDialog(null, "Be Careful! Customer data is changed by someone!", "Security Alert", JOptionPane.ERROR_MESSAGE);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }



    /**
     * This method generates the MD5 hash from the customer data file.
     *
     * @return The generated hash as a String in hexadecimal format.
     * @throws Exception if there is an error reading the file or creating the hash.
     */
    private String MD5_Creator() throws Exception {

        //I deleted this part because when I try to create new file for the first starting of my program(because for
        // first starting, there won't be customer and hashKey files so this causes an exception error since my code needs them
        // to read), Error message appears in GUI
        // because somehow file's cursor moves forward and this causes unmatched hash key.

//        File cstFile = new File(customerFileName);
//        if (!cstFile.exists()) {
//            cstFile.createNewFile();
//        }

        FileInputStream fis = new FileInputStream(customerFileName);
        BufferedInputStream bis = new BufferedInputStream(fis);
        ByteArrayOutputStream baos = new ByteArrayOutputStream();

        int ch;
        while ((ch = bis.read()) != -1) {
            baos.write(ch);
        }
        bis.close();
        fis.close();


        byte[] buffer = baos.toByteArray();

        MessageDigest algorithm = MessageDigest.getInstance("MD5");
        algorithm.reset();
        algorithm.update(buffer);



        byte[] digest = algorithm.digest();
        StringBuilder hexString = new StringBuilder();
        for (int i = 0; i < digest.length; i++) {
            hexString.append(Integer.toHexString(0xFF & digest[i]));
        }
        return hexString.toString();
    }


    /**
     * This method basically reads the hash from the saved hash file.
     *
     * @return The hash value from the file as a String.
     * @throws IOException if the file cannot be read.
     */
    private String hashFileReader() throws IOException {

        //I deleted this part because when I try to create new file for the first starting of my program(because for
        // first starting, there won't be customer and hashKey files so this causes an exception error since my code needs them
        // to read), Error message appears in GUI
        // because somehow file's cursor moves forward and this causes unmatched hash key.

//        File hashFile = new File(hashFileName);
//        if (!hashFile.exists()) {
//            hashFile.createNewFile();
//        }

        try (BufferedReader reader = new BufferedReader(new FileReader(hashFileName))) {
            return reader.readLine();
        }
    }


}

