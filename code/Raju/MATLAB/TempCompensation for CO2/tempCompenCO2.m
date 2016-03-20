function compensatedCO2 = tempCompenCO2(tempReading,CO2Reading)
% The formulation and code is written by Raju Regmi 
% For more details: Email: er.rajuremgi@gmail.com

% This function compensates CO2 content due to change in temperature in environment

% Input:
% tempReading -> Environment recorded temperature
% CO2Reading -> Uncompensated CO2 content

% Output: 
% compensatedCO2 -> Compensated CO2 content

        m1 = 1.0873;
        c1 = -10.8078;
        m2 = -0.0475;
        c2 = 17.3703;
        m3 = 1.6907;
        c3 = -52.2736;

        if tempReading<25.15
            errVal = m1*tempReading+c1;
        elseif tempReading<37.8
            errVal = m2*tempReading+c2;
        else
            errVal = m3*tempReading+c3;
        end

        compensatedCO2 =CO2Reading*100/(errVal+100);
end