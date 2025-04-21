package dryclean.cyprusDryCleanInterfaces;


/**
 * Defines the cleaning style rates for laundry items.
 * These rates are used to calculate the total cost of laundry items based on the cleaning type.
 *
 *
 *
 * @author Ferhat Kasim Koc
 * @version 23.0
 */
public interface CleaningStyle {
    public double electricityRate = 1.05;
    public double waterRate = 1.01;
    public double ironingRate = 10.0;
}
