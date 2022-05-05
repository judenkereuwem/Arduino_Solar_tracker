# Arduino_Solar_tracker

System Hardware Components:
- Arduino as main controller.
- 4 Light Dependent Resistors for sensing sunlight intensity.
- 2 Servo motors as actuators to rotate the panel vertically and horizontally.
- B25 Voltage sensor to sense the voltage output from the Solar panel.
- 20x4 LCD sreen.
- 12v mini soalar panel.

Operation:
- The 4 LDRs are place to faced the four cardinal ponts (East, West, North and South). 
- If an LDR detects the highest intensity among the four, the servo moves the panel to that direction at angle suitable to capture the sunlight.
- The B25 voltage sensor senses continuouly the voltage from the the solar panel.
- Information from the system such as Panel voltage and Panel directions are displayed on a 16x2 LCD screen.  
