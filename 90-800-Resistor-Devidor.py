#Calculation Check:
	
# Using 120 to 24VAC Transformer and with rectification... Vin_max can be calculated as follow...
Vin_max = 24*1.414

# Finding the maximum allowed voltage for the microcontroller.  This particular microcontroller, SAMD12, has maximum value of 3.6V.

# Vout-to-MicrocontrollerPin = Vin * (10k / 110k)
# 3.6V / (10/110) = Vin
R1 = 100000
R2 = 10000


Vin = 3.6 / (R2/(R1+R2))


print("Maximum DC Converted from AC: %.2f VDC" %Vin_max)
print()
print("INPUT, %f-->[Regulator]-->[Output, 24V]-->OUTPUT" %Vin_max)
print()
print("Maximum Input Voltage wrt uC: %.2f VDC" %Vin)
print()

if (Vin > Vin_max) : print("It will be okay since Vin is greater than Vin_max.")



