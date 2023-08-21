# 90-800 Tester Development (104252)
---
End of Project: September 2023
---
#### Instruction for T-XXX
1.  Plug in 5V power supply to the left hand side of the tester
2.  Wait until display shows "Waiting for Power"
3.  Place device under test on top of the tester using two screws diagnolly.  Make sure that the rocker switch of the device under test is in OFF position.
4.  Make connections from the tester to the device under test (Input of the transformer, output of the transformer, Fire Loop, Voltage Output 1, and Voltage Output 2 Connection)
5.  Lastly, insert main AC plug into the device
6.  Turn on the AC main switch
7.  Switch ON the rocker switch.  This will initiate the testing process.
8.  The tester display will show the Voltage Output measurements.  Adjust the output voltage via potentiometer to 24VDC (23 - 25VDC).  Push confirm button located on the right bottom side of the tester.
9.  Tester will go through Fire Loop functionality test next and upon completion, the tester will display the result.
10. If display shows "Test Good", turn off the AC power switch and remove the AC power connection on device under test.
11. Remove other wire connections and remove the device under test
---
#### Altium Project File
 - [Project File](https://detex-corporation.365.altium.com/designs/327D70DE-DD06-426B-8618-25C8A5CFA4D7#design)

---
#### Tester Development Note
- Tester is utilizing the 11-800 Logic Controller Enclosure and trandformer.
- [Custom made PCB mount](tester_with_cutout.3mf) that fits inside this enclosure 
- Using 3M screws as default
- 90 Degree 5V 5.5mm X 2.5mm US Plug
- 5V 1A power Adapter(typically used for LED strip etc)
  - [Used on this project](https://www.amazon.com/dp/B0C1NNZH87?psc=1&ref=ppx_yo2ov_dt_b_product_details)
