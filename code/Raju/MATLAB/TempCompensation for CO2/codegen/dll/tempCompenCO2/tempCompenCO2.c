/*
 * The formulation and code is written by Raju Regmi
 *  For more details: Email: er.rajuremgi@gmail.com
 * Arguments    : double tempReading
 *                double CO2Reading
 * Return Type  : double
 */
double tempCompenCO2(double tempReading, double CO2Reading)
{
  double b_tempReading;

  /*  This function compensates CO2 content due to change in temperature in environment */
  /*  Input: */
  /*  tempReading -> Environment recorded temperature */
  /*  CO2Reading -> Uncompensated CO2 content */
  /*  Output:  */
  /*  compensatedCO2 -> Compensated CO2 content */
  
  if (tempReading < 25.15) {
    b_tempReading = 1.0873 * tempReading -10.8078;
  } else if (tempReading < 37.8) {
    b_tempReading = -0.0475 * tempReading + 17.3703;
  } else {
    b_tempReading = 1.6907 * tempReading -52.2736;
  }

  return CO2Reading * 100.0 / (b_tempReading + 100.0);
}
